CFLAGS= -c -std=c++11

all: linkedlist

linkedlist: main
	$(CXX) main.o -o libLinkedlist.so

main: main.cpp util/list.h util/linkedlist.h
	$(CXX) $(CFLAGS) util/list.h util/linkedlist.h main.cpp

clean:
	rm -rf *.o libLinkedlist.so