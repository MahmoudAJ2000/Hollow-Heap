CFLAGS = -O
CC = g++

dijkstra: main.o hollowHeap.o node.o item.o
		$(CC) main.o hollowHeap.o node.o item.o -o dijkstra.out

main.o: main.cpp
		$(CC) -c main.cpp

hollowHeap.o: hollowHeap.cpp
		$(CC) -c hollowHeap.cpp

node.o: node.cpp
		$(CC) -c node.cpp

item.o: item.cpp
		$(CC) -c item.cpp

clean:
		rm -f core *.o