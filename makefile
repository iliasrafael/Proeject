OBJS1 = list_node.o Buffer.o NodeIndex.o Graph.o list.o main.o 
OBJS2 = list_node.o Buffer.o NodeIndex.o Graph.o list.o testing.o
SOURCE = list_node.cpp Buffer.cpp NodeIndex.cpp Graph.cpp list.cpp main.cpp testing.cpp
HEADER = list_node.h Buffer.h NodeIndex.h Graph.h list.h
OUT1 = out
OUT2 = testing
CC = g++
FLAGS = -g -c

all: $(OUT1) $(OUT2)

$(OUT1): $(OBJS1)
	$(CC) -g $(OBJS1) -o $@

$(OUT2): $(OBJS2)
	$(CC) -g $(OBJS2) -o $@

list_node.o: list_node.cpp
	$(CC) $(FLAGS) list_node.cpp list_node.h

Buffer.o: Buffer.cpp Buffer.h
	$(CC) $(FLAGS) Buffer.cpp

NodeIndex.o: NodeIndex.cpp NodeIndex.h
	$(CC) $(FLAGS) NodeIndex.cpp

Graph.o: Graph.cpp Graph.h
	$(CC) $(FLAGS) Graph.cpp

list.o: list.cpp list.h
	$(CC) $(FLAGS) list.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

testing.o: testing.cpp
	$(CC) $(FLAGS) testing.cpp

clean :
	rm -f $(OBJS1) testing.o $(OUT1) $(OUT1)

count :
	wc $(SOURCE) $(HEADER)

