main : main.o BoundedQueue.o
	g++ -g -Wall -o main main.o BoundedQueue.o

.PHONY: clean

clean:
	@rm -f BoundedQueueKPCB main.o BoundedQueue.o core