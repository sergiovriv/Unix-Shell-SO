## Welcome! ##

This is our Unix Command Line Console repository! This project was created by two classmates as a way to improve our skills in C programming and Unix systems. The console offers a variety of commands for users to interact with their Unix system, including options for file manipulation, system information, and more. We hope that you find this project useful and we welcome any contributions or feedback you may have.

The project was developed over the course of a semester, with four distinct deliverables. During each deliverable, we worked hard to ensure that the console was functional and user-friendly. We received good grades on each deliverable, which encouraged us to keep improving it.

Throughout the development of this project, we learned a lot about C programming and Unix systems. We are proud of the final product and hope that it will be useful for other users.

## Deliverables ##
```
ayuda [cmd] ayuda displays a list of available commands. ayuda cmd gives a brief
help on the usage of comand cmd.
```
### D0 ###
The first deliverable of this project focused on implementing basic commands and a command history for the console. The command history allowed users to view and access previously entered commands. These features formed the foundation of the console and were essential for its functionality.
```
autores: Prints the names and logins of the program authors.
pid: Prints the pid of the process executing the shell.
carpeta: [direct] Changes the current working directory of the shell to direct.
fecha: prints the current date in the format DD/MM/YYYY.
time: prints the current time in the format hh:mm:ss.
hist: Shows/clears the historic of commands executed by this shell.
comando N: Repeats command number N (from historic list).
infosis: Prints information on the machine running the shell
ayuda [cmd]: displays a list of available commands.
fin: Ends the shell
salir: Ends the shell
bye: Ends the shell

```

### D1 ###
The second deliverable of this project focused on improving the functionality of the console by adding commands for managing directories and files.

```
create: creates files or directories
stat: gives information on files or directories
list: lists directories contents
delete: deletes files and/or empty directories
deltree: deletes files and/pr non empty directories recursively
```

### D2 ###
The third deliverable of this project focused on the management of memory in the console. This included implementing features such as the ability to allocate and deallocate memory dynamically, as well as to track and display information about the memory usage of the console.
```
allocate: allocates a block of memory and adds it to the list of memory blocs
deallocate: deallocates a block of memory a removes it from the list of memory blocks
i-o: performs input output from disk to memory and viceversa
memdump: dumps the contents of memory to the screen
memfill: fills the memory with one character
memory: shows information on the memory of the process
recurse: executes a recursive function
```
Overall, the third deliverable was an important step in the development of the console, as it ensured that the console was able to handle memory in a reliable and efficient way.

### D3 ###
The final deliverable of this project focused on the management of processes and the integration of the Unix default shell into the console to make it more functional.
One of the main features we implemented in this deliverable was the ability to create and manage processes within the console.

```
priority: views (or changes) the priority of a process
showvar: shows the value of an environment variable
changevar: changes the value of an environment variable
showenv: shows the process environment
fork: the shell does the fork system call and waits for its child to end
execute: executes a program (with arguments) without creating a new process
listjobs: lists background processes
deljobs: deletes background processes from the list
job: shows info on a background process. Can change it to foreground
```
In addition to the process management features, we also integrated the Unix default shell into the console. This allowed us to leverage the functionality of the default shell and use it in combination with the features of our console. This made the console much more powerful and functional, allowing users to use a wide range of commands and features within a single interface.

## Linked List ##

One of the tools that we used in the development of this project was a linked list with a head node. A linked list is a linear data structure in which each element is stored in a node, and each node points to the next node in the list. A head node is a special node that marks the beginning of the linked list.

We used a linked list with a head node to store and manage the various tasks that the console needed to perform. For example, we used a linked list to keep track of the available commands, as well as to store the command history for the console.

The use of a linked list allowed us to easily add, remove, and access elements in the list, as well as to keep track of the size of the list. It also allowed us to implement advanced features such as piping and redirection, which required the ability to manipulate the list in real-time.

Overall, the use of a linked list with a head node was an important part of the development of the console, and contributed to its functionality and efficiency.

# Authors #

Claudia Maciel and Sergio Vila

We hope that our Unix Command Line Console will be useful for you and that it will help you to interact with your Unix system in a more efficient and convenient way. We welcome any feedback or contributions that you may have, and we hope that you find this project useful. Thank you for using our console!
