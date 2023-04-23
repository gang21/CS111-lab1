## UID: 005677251
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

## Pipe Up

This code is meant to replace the pipe operator ```|``` in shells. Users will pass in executable names as command line arguments and the program will execute each one in a new process.

## Building

To build the program, import pipe.c and the Makefile. Then type in the following commands that will create an executable function called pipe. 
```
make
```

## Running

Show an example run of your program, using at least two additional arguments, and what to expect

To run the program, enter the `./pipe ` command followed by however many arguments you want. The arguments that follow should be processes that can be run on the shell such as `cat` or `ls`.

```
./pipe ls cat wc
```
is equivalent to: 
``` 
ls | cat | wc
```

## Cleaning up

To clean up all binary files, run the following command:
```make clean```
