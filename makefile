SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

all: $(OBJS)
	g++ -g $(OBJS) -o cube_zone $(LIBS)

.cpp.o:
	g++ -g -c -o $@ $<

clean:
	rm *.o cube_zone