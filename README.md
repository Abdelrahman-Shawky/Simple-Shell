# Simple Shell
C program that takes keyboard commands via terminal, and executes the corresponding system call.

## What Is A Shell
A shell is a command-line interpreter, it is the computer program that provides a user interface to access the services of the operating system.

## Some of The Allowed Functions
- ```cd``` -- change directory
- ```pwd``` -- print working directory
- ```ls``` -- list all files and sub-directories in a directory
- ```stat``` -- display information about a file
- ```rm``` -- remove (i.e. delete) a file
- ```cp``` -- copy a file
- ```cat, more, less``` -- list the contents of a file
- ```chmod``` -- change file mode, i.e. file permissions
- ```ln``` -- create a link
- ```wc``` -- count words
- ```mkdir``` -- create a new directory
- ```head``` -- output only the first lines of a file
- ```tail``` -- output only the last lines of a file
- ```grep``` -- find a word in one or more files
- ```ps``` -- process status (lists running processes, often run as ps aux for the most information)
- ```cut``` -- extract a column from a file
- ```sort``` -- sort a file alphabetically
- ```uniq``` -- remove adjacent duplicate lines
- ```find``` -- find files and directories and perform subsequent operations on them
- ```clear``` -- clears screen
- ```exit``` terminating the shell
- (program loading) --> blocking 
- (program loading) & --> non-blocking
- blocks empty commands

## Example Commands

```
/home/abdelrahman:$ ls
Desktop  Documents  Downloads  Music  Pictures	Public	snap  Templates  Videos
/home/abdelrahman:$ stat Desktop
  File: Desktop
  Size: 4096      	Blocks: 8          IO Block: 4096   directory
Device: 805h/2053d	Inode: 450787      Links: 6
Access: (0755/drwxr-xr-x)  Uid: ( 1000/abdelrahman)   Gid: ( 1000/abdelrahman)
Access: 2022-01-20 03:52:29.743072441 +0200
Modify: 2022-01-10 23:52:41.771663407 +0200
Change: 2022-01-10 23:52:41.771663407 +0200
 Birth: -
/home/abdelrahman:$ pwd
/home/abdelrahman
/home/abdelrahman:$ cd Desktop
/home/abdelrahman/Desktop:$ 
```

## Running
Run the following command to compile and run from the terminal inside the directory
```
gcc main.c -o main && ./main
```

## What I Learned
- Working in a UNIX environment 
- How a terminal executes commands
- Difference between functions and system calls
- The concept of forking and child process manipulation
- Process images and how not to overwrite using child processes
- Signal handlers using SIGCHLD signal and asynchronus execution
- Executing systeam calls using execvp()
