OBJS = list_node.o Buffer.o NodeIndex.o Graph.o main.o
SOURCE = list_node.cpp Buffer.cpp NodeIndex.cpp Graph.cpp main.cpp
HEADER = list_node.h Buffer.h NodeIndex.h Graph.h
OUT = out
CC = g++
FLAGS = -g -c

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

list_node.o: list_node.cpp
	$(CC) $(FLAGS) list_node.cpp

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp

NodeIndex.o: NodeIndex.cpp
	$(CC) $(FLAGS) NodeIndex.cpp

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

