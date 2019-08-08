#ifndef UTILITY_HPP
#define UTILITY_HPP

#include //*<memory>
#include <thread>
#include <list>
#include <queue>

// message

enum message_type {
	// incompleted
	request_vote, vote, set_leader;
};

class message {

private:

	message_type type;
	
	node *from, *to;
	
	int value;

public:

	message(message_type type, node *from, node *to, int value):
		type(type), from(from), to(to), value(value) { }
	
	message_type get_type() const {
		return type;
	}
	
};

// node

enum node_type {
	follower, candidate, leader;
};

class node {

private:
	
	node_type type;

	int election_timeout, heartbeat_timeout;

	node *leader, *voted_to;

	int current_term, voted_to, vote_count;

	std::list<node*>::iterator iter;

	std::queue<message> q;

	// rpc

	string address;
	
public:

	node(): type(follower), leader(nullptr), voted_to(nullptr) { }

	void erase_self();

	void set_iter(std::list<node*>::iterator);

	void send_to(message_type, int, node*) const;

	void send_to_all(message_type, int) const;

	void receive_message(message);

	message next_message();

	void handle_message();

	void become_follower(node*);

	void become_candidate();

	bool become_leader();
	
};

std::list<node*> node_list;

int node_count;

void node::erase_self() {
	node_list.erase(iter);
}

void node::set_iter(std::list<node*>::iterator iter) {
	this->iter = iter;
}

void node::send_to(message_type type, int value, node *to) {
	to->receive_message(message(type, value, this, to));
}

void node::send_to_all(message_type type, int value) {
	for(auto to : node_list)
		if (to != this)
			this->send_to(type, value, to);
}

void node::receive_message(message m) {
	q.push(m);
}

message node::next_message() {
	message m = q.front();
	q.pop();
	return m;
}

void node::handle_message(message m) {
	if (m.get_type() == request_vote) {
		if (type == follower) {
			voted_to = m.from;
			send_to(vote, 0, m.from);
		}
	}

	else if (m.get_type() == vote) {
		vote_count++;
		// pass
	}

	else if (m.get_type() == set_leader) {
		become_follower(m.from);
		// TODO: check to be a candidate a moment later
	}
}

void node::become_follower(node *leader) {
	this->leader = leader;
	voted_to = nullptr;
	// TODO: check to be a candidate a moment later
}

void node::become_candidate() {
	if (voted_to != nullptr)
		return;

	vote_count = 0;
	send_to_all(request_vote, 0);
}

bool node::become_leader() {
	if (type != candidate || vote_count * 2 <= vote_count)
		return;

	leader = this;
	send_to_all(set_leader, 0);
}

#endif
