SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

all: $(OBJS)
	g++ $(OBJS) -o cube_zone $(LIBS)

.cpp.o:
	g++ -c -o $@ $<

clean:
	rm *.o cube_zone