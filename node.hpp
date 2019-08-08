#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "protos/Raft.pb.h"
#include "protos/Raft.grpc.pb.h"

#include "utility.hpp"
// #include "server.hpp"
// #include "client.hpp"

using grpc::Server;
using grpc::Status;
// using RaftRpc::Message;

enum node_type {
    universal_node, follower, candidate, leader
};

class node final {

private:
	
	class ServiceImpl final : public RaftRpc::Service {
		
		friend class node;
	
	private:
		
		node *w;
	
	public:
		
		ServiceImpl(node *x): w(x) {
			// pass
		}
		
		Status send_message(grpc::ServerContext *context, const Message *message, Message *reply) override {
			std::cerr << "w = " << w <<  std::endl;
			*reply = w->handle_message(*message);
			return Status();
		}
		
	};
	
	std::unique_ptr<Server> CreateServer(std::string addr, node *p) { // CONTINUE WORKING HERE
		auto service = new ServiceImpl(p);
		
		grpc::ServerBuilder builder;
		builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
		builder.RegisterService(service);
		auto server = builder.BuildAndStart();
		
		// server->Wait();
		
		return server;
	}
	
	class Client {
	
	private:
		
		std::unique_ptr<RaftRpc::Stub> stub_;
	
	public:
		
		Client(std::shared_ptr<grpc::Channel> channel): stub_(RaftRpc::NewStub(channel)) {}
		
		Message send_message(Message request) {
			std::cerr << "send_message() this = " << this << std::endl;
			std::cerr << "stub_ = " << stub_.get() << std::endl;
			Message reply;
			grpc::ClientContext context;
			Status status = stub_->send_message(&context, request, &reply);
			std::cerr << "*******" << std::endl;
			
			if (status.ok())
				return reply;
			else {
				std::cerr << status.error_code() << " : " << status.error_message() << std::endl;
				reply.set_type(Message_message_type_universal_t);
				return reply;
			}
		}
		
	};
	
public:
	
	static int node_count;

private:

	node_type type;

	int id;
 
	std::chrono::high_resolution_clock::duration election_timeout, heartbeat_timeout;

	int leader, voted_to;

	int current_term, voted_term, vote_count;
	
	bool cancelled;

	std::shared_ptr<Server> server; // ***

	std::vector<Client*> clients; // ***
	
	std::thread election, receiving;

public:

	node(int id): type(universal_node), id(id), leader(0), voted_to(0), current_term(0) {
		server = CreateServer("0.0.0.0:5005" + std::to_string(id), this);
		std::cerr << "address:" << "0.0.0.0:5005" + std::to_string(id) << std::endl;
    }
    
    ~node() {
		if (election.joinable())
			election.join();
		if (receiving.joinable())
			receiving.join();
		server->Shutdown();
	}
    
    void start_server();
	
	void set_receiving(std::thread&&);
	
	void init_clients(std::vector<std::shared_ptr<grpc::Channel>>&);
	
	Message send_to(Message_message_type, int, int);
	
	std::vector<Message> send_to_all(Message_message_type, int);
	
	Message handle_message(Message);
	
	void become_follower(int);
	
	bool become_candidate();
	
	bool become_leader();
	
	void receiving_loop();
	
	void election_loop();
	
	void hajimemashou(); // ゲームを始める
	

};

int node::node_count = 0;

std::vector<node*> nodes;

void node::start_server() {
	
	server->Wait();
	//for(;;);
}

void node::set_receiving(std::thread &&t) {
	receiving = std::move(t);
	// receiving.join(); // ??
}

void node::init_clients(std::vector<std::shared_ptr<grpc::Channel>> &v) {
	std::cerr << "v.size() = " << v.size() << std::endl;
	clients.push_back(nullptr);
	std::cerr << "???" << std::endl;
	for (int i = 1; i <= node_count; i++)
		clients.push_back(new Client(v[i - 1]));
}

Message node::send_to(Message_message_type message_type, int value, int id_to) {
	Message message;
	message.set_id_from(id);
	message.set_id_to(id_to);
	message.set_type(message_type);
	message.set_value(value);
	
	return clients[id_to]->send_message(message);
}

std::vector<Message> node::send_to_all(Message_message_type message_type, int value) {
	std::vector<Message> v;
	for (int i = 1; i <= node_count; i++)
		if (i != id) {
			std::cerr << id << " try to send to " << i << std::endl;
			v.push_back(send_to(message_type, value, i));
		}
	return v;
}

Message node::handle_message(Message m) {
	std::cerr << "handling..." << std::endl;
	Message reply;
	if (m.type() == Message_message_type_request_vote_t) {
		cancelled = true;
		if (true || type == follower) {
			type = follower;
			cancelled = true;
			reply.set_type(Message_message_type_vote_t);
			if(!voted_to)
				voted_to = m.id_from();
			reply.set_value(voted_to);
			std::cerr << id << " replys to " << m.id_from() << "!" << std::endl;
		}
		else {
			reply.set_type(Message_message_type_universal_t);
		}
	}
	
	else if (m.type() == Message_message_type_set_leader_t) {
		become_follower(m.id_from());
		cancelled = true;
		reply.set_type(Message_message_type_universal_t);
	}
	
	else if (m.type() == Message_message_type_universal_t && m.value() == 1) {
		cancelled = true;
		// TODO: DO SOMETHING UPON RECEIVING HEARTBEAT
	}
	
	reply.set_id_to(reply.id_from());
	reply.set_id_from(id);
	
	return reply;
}

void node::become_follower(int leader) {
	this->leader = leader;
	voted_to = 0;
	voted_term = nodes[leader]->current_term;
}

bool node::become_candidate() {
	if (cancelled)
		return false;
	
	vote_count = 0;
	type = candidate;
	std::cerr << id << " sending..." << std::endl;
	auto v = send_to_all(Message_message_type_request_vote_t, 0);
	std::cerr << id << " sent!" << std::endl;
	for (auto &x : v)
		if (x.value() == id)
			vote_count++;
	
	vote_count++;
	std::cerr << id << "'s vote_count = " << vote_count << std::endl;
	return true;
}

bool node::become_leader() {
	if (type != candidate || vote_count * 2 <= node_count)
		return false;
	
	leader = id;
	std::cerr << "Node #%d becomes leader." << std::endl;
	send_to_all(Message_message_type_set_leader_t, 0);
	return true;
}

void node::receiving_loop() {
	for (;;) {
		// TODO: COMPLETE THIS
	}
}

void node::election_loop() {
	std::cerr << "loooooooooop!!" << std::endl;
	for(;;) {
		election_timeout = std::chrono::duration<int, std::milli>(get_election_timeout());
		cancelled = false;
		std::this_thread::sleep_for(election_timeout);
		// std::cerr << "HAHAHAHAHA!!!" << std::endl;
		if(become_candidate()) {
			std::cerr << id << " becomes candidate" << std::endl;
			if(become_leader()) {
				std::cerr << id << " becomes leader!!!!!" << std::endl;
				abort();
				heartbeat_timeout = std::chrono::duration<int, std::milli>(get_heartbeat_timeout());
				for(;;) {
					std::this_thread::sleep_for(heartbeat_timeout);
					send_to_all(Message_message_type_universal_t, 1);
				}
			}
			else
				continue;
		}
		else {
			continue;
			// TODO: CONTINUE WORKING HERE
		}
	}
}

void node::hajimemashou() {
	// TODO: let it start working
	std::cerr << "GAME Hajimeyo" << std::endl;
	election = std::thread(&node::election_loop, this);
}

void initialize(int n) {
	nodes.push_back(nullptr);
	node::node_count = n;
	std::vector<std::shared_ptr<grpc::Channel>> v;
	for (int i = 1; i <= n; i++) {
		std::cerr << "i = " +  std::to_string(i) << " n = " << n << std::endl;
		node *x = new node(i);
		x->set_receiving(std::thread(&node::start_server, x));
		std::cerr << "test" << std::endl;
		nodes.push_back(x);
		v.push_back(grpc::CreateChannel("localhost:5005" + std::to_string(i), grpc::InsecureChannelCredentials()));
	}
	for (int i = 1; i <= n; i++) {
		nodes[i]->init_clients(v);
		std::cerr << std::to_string(i) + " init_clients OK" << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(2000));
	for (int i = 1; i <= n; i++)
		nodes[i]->hajimemashou();
	
	for(;;);
}

#endif