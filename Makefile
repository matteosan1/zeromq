CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=
LDLIBS=-lzmq

SRCS := $(wildcard *.cpp)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXEC = $(patsubst %.cpp,%,$(SRCS))

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CPFLAGS) $(LDFLAGS) $(LDLIBS) -c $<

clean: $(EXEC)
	$(RM)
