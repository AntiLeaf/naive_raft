# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/antileaf/桌面/raft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antileaf/桌面/raft/build

# Include any dependencies generated for this target.
include protos/CMakeFiles/proto_svr.dir/depend.make

# Include the progress variables for this target.
include protos/CMakeFiles/proto_svr.dir/progress.make

# Include the compile flags for this target's objects.
include protos/CMakeFiles/proto_svr.dir/flags.make

protos/Raft.grpc.pb.cc: ../protos/Raft.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/antileaf/桌面/raft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running gRPC C++ protocol buffer compiler on /home/antileaf/桌面/raft/protos/Raft.proto"
	cd /home/antileaf/桌面/raft/build/protos && protoc --grpc_out=/home/antileaf/桌面/raft/build/protos --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin -I /home/antileaf/桌面/raft/protos /home/antileaf/桌面/raft/protos/Raft.proto

protos/Raft.grpc.pb.h: protos/Raft.grpc.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate protos/Raft.grpc.pb.h

protos/Raft.pb.cc: ../protos/Raft.proto
protos/Raft.pb.cc: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/antileaf/桌面/raft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Running C++ protocol buffer compiler on /home/antileaf/桌面/raft/protos/Raft.proto"
	cd /home/antileaf/桌面/raft/build/protos && /usr/local/bin/protoc --cpp_out=/home/antileaf/桌面/raft/build/protos -I /home/antileaf/桌面/raft/protos /home/antileaf/桌面/raft/protos/Raft.proto

protos/Raft.pb.h: protos/Raft.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate protos/Raft.pb.h

protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o: protos/CMakeFiles/proto_svr.dir/flags.make
protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o: protos/Raft.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antileaf/桌面/raft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o"
	cd /home/antileaf/桌面/raft/build/protos && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o -c /home/antileaf/桌面/raft/build/protos/Raft.grpc.pb.cc

protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.i"
	cd /home/antileaf/桌面/raft/build/protos && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antileaf/桌面/raft/build/protos/Raft.grpc.pb.cc > CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.i

protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.s"
	cd /home/antileaf/桌面/raft/build/protos && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antileaf/桌面/raft/build/protos/Raft.grpc.pb.cc -o CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.s

protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.requires:

.PHONY : protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.requires

protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.provides: protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.requires
	$(MAKE) -f protos/CMakeFiles/proto_svr.dir/build.make protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.provides.build
.PHONY : protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.provides

protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.provides.build: protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o


# Object files for target proto_svr
proto_svr_OBJECTS = \
"CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o"

# External object files for target proto_svr
proto_svr_EXTERNAL_OBJECTS =

protos/libproto_svr.a: protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o
protos/libproto_svr.a: protos/CMakeFiles/proto_svr.dir/build.make
protos/libproto_svr.a: protos/CMakeFiles/proto_svr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/antileaf/桌面/raft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libproto_svr.a"
	cd /home/antileaf/桌面/raft/build/protos && $(CMAKE_COMMAND) -P CMakeFiles/proto_svr.dir/cmake_clean_target.cmake
	cd /home/antileaf/桌面/raft/build/protos && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proto_svr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
protos/CMakeFiles/proto_svr.dir/build: protos/libproto_svr.a

.PHONY : protos/CMakeFiles/proto_svr.dir/build

protos/CMakeFiles/proto_svr.dir/requires: protos/CMakeFiles/proto_svr.dir/Raft.grpc.pb.cc.o.requires

.PHONY : protos/CMakeFiles/proto_svr.dir/requires

protos/CMakeFiles/proto_svr.dir/clean:
	cd /home/antileaf/桌面/raft/build/protos && $(CMAKE_COMMAND) -P CMakeFiles/proto_svr.dir/cmake_clean.cmake
.PHONY : protos/CMakeFiles/proto_svr.dir/clean

protos/CMakeFiles/proto_svr.dir/depend: protos/Raft.grpc.pb.cc
protos/CMakeFiles/proto_svr.dir/depend: protos/Raft.grpc.pb.h
protos/CMakeFiles/proto_svr.dir/depend: protos/Raft.pb.cc
protos/CMakeFiles/proto_svr.dir/depend: protos/Raft.pb.h
	cd /home/antileaf/桌面/raft/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antileaf/桌面/raft /home/antileaf/桌面/raft/protos /home/antileaf/桌面/raft/build /home/antileaf/桌面/raft/build/protos /home/antileaf/桌面/raft/build/protos/CMakeFiles/proto_svr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : protos/CMakeFiles/proto_svr.dir/depend

