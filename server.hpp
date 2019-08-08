#include <vector>
#include <string>
#include <memory>

#include "protos/Raft.pb.h"
#include "protos/Raft.grpc.pb.h"
#include "node.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
// using RaftRpc::Message;
