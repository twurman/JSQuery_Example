# Set Boost path
BOOST_LOCATION = /usr/local/boost_1_58_0
BOOST_LIB = /usr/local/boost_1_58_0/stage/lib

CXX = g++
# Needed for linking
GEN_DIR = ./gen-cpp

CXX_FLAGS = -I$(BOOST_LOCATION)
LINK_FLAGS = -L$(BOOST_LIB) -lboost_program_options -lboost_filesystem -lboost_system -lboost_thread -lboost_regex -lthrift

TARGET_SERVER = server
OBJECTS = $(GEN_DIR)/types_types.cpp $(GEN_DIR)/IPAService.cpp $(GEN_DIR)/SchedulerService.cpp IPAServer.cpp

all: clean thrift $(TARGET_SERVER)

thrift:
	thrift -r --gen cpp ../service.thrift

$(TARGET_SERVER): $(OBJECTS_SERVER)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) -o $(TARGET_SERVER) $(LINK_FLAGS)

clean:
	rm -rf $(TARGET_SERVER) *.o

.PHONY:	all
