OBJS1 = list_node.o Buffer.o NodeIndex.o Graph.o ArrayList.o Stack.o Components.o hashlist.o main3.o SCC.o GrailIndex.o CC.o JobScheduler.o JobList.o Job.o
OBJS2 = list_node.o Buffer.o NodeIndex.o Graph.o hashlist.o ArrayList.o Stack.o Components.o testing.o SCC.o GrailIndex.o CC.o
SOURCE = list_node.cpp hashlist.cpp Buffer.cpp NodeIndex.cpp Graph.cpp ArrayList.cpp Stack.cpp Components.cpp main3.cpp testing.cpp SCC.cpp GrailIndex.cpp CC.cpp JobScheduler.cpp JobList.cpp Job.cpp
HEADER = list_node.h Buffer.h hashlist.h NodeIndex.h Graph.h ArrayList.h Components.h Stack.h SCC.h GrailIndex.h CC.h JobScheduler.h JobList.h Job.h
OUT1 = out 
OUT2 = testing
CC = g++
FLAGS = -g -c

all: $(OUT1) $(OUT2)

$(OUT1): $(OBJS1)
	$(CC) -g -pthread $(OBJS1) -o $@

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

ArrayList.o: ArrayList.cpp ArrayList.h
	$(CC) $(FLAGS) ArrayList.cpp

hashlist.o: hashlist.cpp hashlist.h
	$(CC) $(FLAGS) hashlist.cpp

Stack.o: Stack.cpp Stack.h
	$(CC) $(FLAGS) Stack.cpp

SCC.o: SCC.cpp SCC.h
	$(CC) $(FLAGS) SCC.cpp

CC.o: CC.cpp CC.h
	$(CC) $(FLAGS) CC.cpp

GrailIndex.o: GrailIndex.cpp GrailIndex.h
	$(CC) $(FLAGS) GrailIndex.cpp

Components.o: Components.cpp Components.h
	$(CC) $(FLAGS) Components.cpp

main3.o: main3.cpp
	$(CC) $(FLAGS) main3.cpp

testing.o: testing.cpp
	$(CC) $(FLAGS) testing.cpp

JobScheduler.o: JobScheduler.cpp JobScheduler.h
	$(CC) $(FLAGS) JobScheduler.cpp

JobList.o: JobList.cpp JobList.h
	$(CC) $(FLAGS) JobList.cpp

Job.o: Job.cpp Job.h
	$(CC) $(FLAGS) Job.cpp

clean :
	rm -f $(OBJS1) testing.o $(OUT1) $(OUT2)

count :
	wc $(SOURCE) $(HEADER)

