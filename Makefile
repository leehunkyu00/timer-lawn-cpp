CXX			= g++
CXXFLAGS	= -Wall -std=c++17 -g  -O3
SRCS		= $(wildcard *.cpp) $(wildcard *.c)
OBJS		= $(SRCS:.cpp=.o)
TARGET 		= out
LIBS		= -lz -lpthread 
LIB_DIRS	= -Llib
INC			= -Iinclude \


all:clean $(TARGET) 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIB_DIRS) $(INC) $(LIBS)



$(TARGET):$(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS) $(INC) $(LIB_DIRS) $(LIBS)

clean:
	rm -f $(TARGET)
	rm -rf *.o

