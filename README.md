# Linux-IPC--Pipes
Linux-IPC-Pipes


# Ex03-Linux IPC - Pipes

# AIM:
To write a C program that illustrate communication between two process using unnamed and named pipes

# DESIGN STEPS:

### Step 1:

Navigate to any Linux environment installed on the system or installed inside a virtual environment like virtual box/vmware or online linux JSLinux (https://bellard.org/jslinux/vm.html?url=alpine-x86.cfg&mem=192) or docker.

### Step 2:

Write the C Program using Linux Process API - pipe(), fifo()

### Step 3:

Testing the C Program for the desired output. 

# PROGRAM:

## C Program that illustrate communication between two process using unnamed pipes using Linux API system calls
nanp pipe.c
```
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello";
    char buffer[100];
    pipe(fd);  // Create pipe
    pid = fork();
    
    if(pid == 0) {
        // Child - read from pipe
        close(fd[1]);  // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);
        close(fd[0]);
    }
    else {
        // Parent - write to pipe
        close(fd[0]);  // Close read end
        write(fd[1], message, strlen(message)+1);
        printf("Parent wrote: %s\n", message);
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}

```
gcc pipe.c -o pipe

./pipe



## OUTPUT

![Alt text](unamedpipes.png)

## C Program that illustrate communication between two process using named pipes using Linux API system calls

nano named_pipe
```
 #include <stdio.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <string.h>
 #include <sys/wait.h>

int main() {
    int fd;
    char *fifo = "myfifo";
    char message[] = "Hello Rohith";
    char buffer[100];
    pid_t pid;
    
    // Create named pipe
    mkfifo(fifo, 0666);
    
    pid = fork();
    
    if(pid == 0) {
        // Child process - Reader
        fd = open(fifo, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd);
    } 
    else {
        // Parent process - Writer
        fd = open(fifo, O_WRONLY);
        write(fd, message, strlen(message) + 1);
        printf("Parent sent: %s\n", message);
        close(fd);
        wait(NULL);
        unlink(fifo); // Remove named pipe
    }
    
    return 0;
}

```
gcc named_pipe.c -o named_pipe

./named_pipe



## OUTPUT

![Alt text](namedpipes.png)

# RESULT:
The program is executed successfully.
