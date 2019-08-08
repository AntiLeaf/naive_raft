#include <vector>
#include <memory>
#include <string>
#include <iostream>

// #include <grpcpp/grpcpp.h>
#include <protos/Raft.pb.h>
#include "protos/Raft.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using RaftRpc::Message;
