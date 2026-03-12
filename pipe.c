#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[100];
    
    // Create pipe with error checking
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if(pid == 0) {
        // Child process
        close(fd[1]);  // Close unused write end
        
        ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Null terminate
            printf("Child read (%ld bytes): %s\n", bytes_read, buffer);
        }
        
        close(fd[0]);
    }
    else {
        // Parent process
        close(fd[0]);  // Close unused read end
        
        ssize_t bytes_written = write(fd[1], message, strlen(message) + 1);
        printf("Parent wrote (%ld bytes): %s\n", bytes_written, message);
        
        close(fd[1]);
        wait(NULL);  // Wait for child to finish
    }
    
    return 0;
}
