SRCS = $(wildcard ../src/*.cpp)
OBJS = $(SRCS:../src/%.cpp=../obj/%.o)
LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
OPTS = -g --std=c++11

all: $(OBJS)
	g++ -I../src main.cpp $(OBJS) -o cube_zone $(LIBS) $(OPTS)

../obj/%.o: ../src/%.cpp
	g++ -c -I../src -o $@ $< $(OPTS)

clean:
	rm *.o ../obj/*.o cube_zone