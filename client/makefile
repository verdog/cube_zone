SRCS = $(wildcard ../src/*.cpp)
OBJS = $(SRCS:../src/%.cpp=../obj/%.o)
LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

all: $(OBJS)
	g++ -g -I../src main.cpp $(OBJS) -o cube_zone $(LIBS)

../obj/%.o: ../src/%.cpp
	g++ -g -c -I../src -o $@ $<

clean:
	rm *.o ../obj/*.o cube_zone