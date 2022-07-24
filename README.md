PURPOSE OF THE PROGRAM:

It is a program which establiches a communication between a server process and client process. Client process creates an array with 1000 elements every 10ms and client sends an array and process_id to the server with message passing. In server process, main_thread takes a message with message passing and creates an worker_thread to sorts the array. Worker_thread takes an array from main_thread. After sorting, the worker thread writes the sorted array to the file as PID.txt with the client process_id and then sends a sorted signal to the client.
Main_thread assigns a task to the worker_thread, then waits for worker thread to finish its task. Meanwhile main_thread is blocked until worker_thread finish its task.

-----------------------------------------------------------

1- How to compile server.c:

gcc server.c -lpthread -o server.o

2- How to compile client.c:

gcc client.c -o client.o

3- To run the client:

./client.o  

4- To run the server:

./server.o 


