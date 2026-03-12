
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
