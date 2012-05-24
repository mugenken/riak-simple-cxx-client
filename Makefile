CXX = g++
CXXFLAGS = -Wall -O1
TARGET = riak-sc
DEBUG = -g
PROTOC = protoc
SRC = ./src/
PROTO_SRC = ./proto/riak.proto
LIBS = -lprotobuf -lpthread

PROTOC_OPTS = --cpp_out=$(SRC) $(PROTO_SRC)

.PHONY: proto clean vim_mode

all: $(TARGET)

$(TARGET): proto Connection.o Message.o riak.pb.o main.o
	@mkdir -p ./build/debug
	$(CXX) $(LIBS) $(CXXFLAGS) -o ./build/debug/$(TARGET) ./build/debug/main.o ./build/debug/Connection.o ./build/debug/riak.pb.o ./build/debug/Message.o

proto:
	$(PROTOC) $(PROTOC_OPTS)

main.o:
	@mkdir -p ./build/debug
	$(CXX) -g -c $(CXXFLAGS) -o ./build/debug/main.o src/main.cpp

Connection.o:
	@mkdir -p ./build/debug
	$(CXX) -g -c $(CXXFLAGS) -o ./build/debug/Connection.o src/riaksimpleclient/Connection.cpp

Message.o:
	@mkdir -p ./build/debug
	$(CXX) -g -c $(CXXFLAGS) -o ./build/debug/Message.o src/riaksimpleclient/Message.cpp

riak.pb.o:
	@mkdir -p ./build/debug
	$(CXX) -g -c -I$(SRC) $(CXXFLAGS) -o ./build/debug/riak.pb.o src/proto/riak.pb.cc

clean:
	@rm -r $(SRC)/proto
	@rm -r ./build/debug

vim_mode: proto
	@echo "// vim: set ft=cpp:" >> $(SRC)/proto/riak.pb.h
	@echo "// vim: set ft=cpp:" >> $(SRC)/proto/riak.pb.cc
	@echo "added vim modelines to protobuffer sources"

