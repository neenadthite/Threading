# Threading 
Use "gcc -pthread -o binaryname filename.c" to create executable
1. twothreads -> X and Y threads are created and passed a counter value. The thread then executes its main function by passing these values as arguments.
2. threadswithmutex -> Mutex concept is used to lock thread X with a time condition wait and its release signal will be given from thread Y. 
