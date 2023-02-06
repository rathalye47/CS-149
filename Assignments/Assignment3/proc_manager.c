#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>

/*
Authors: Rohan Athalye and Anni Shao
Date: March 22, 2022
*/
int main(int argc, char *argv[]) {
    // If the user does not provide exactly 1 input file as an argument on the command line, output an error message and exit with 2.
    if (argc != 2) {
        printf("Please specify exactly 1 input file from which to execute commands.\n");
        exit(2);
    }

    FILE *fp; // File pointer.
    char *inputFile = argv[1]; // Stores the 2nd command line argument, which is the input file.
    char *line = NULL; // Points to each line in the input file.
    
    size_t len = 0; // Stores the size of the line.
    ssize_t read; // Reads the lines from the file.
    char commandWords[30][30]; // Array of strings to store each word in the file.
    int i, j, ctr;
    int numCommands = 0; // Stores the number of commands.

    fp = fopen(inputFile, "r"); // Opens the file.

    // If the file pointer is NULL, print an error message and exit with 2.
    if (fp == NULL) {
        printf("Range: cannot open file.\n");
        exit(2);
    }
    
    // Reads each line from the file.
    while ((read = getline(&line, &len, fp)) != -1) {
        // If the line ends in a new line '\n', replace it with '\0' (null).
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = 0;
        }
        
        numCommands++; // Increments the number of commands.                                   

        // Initializes the string array with 0s.
        for (i = 0; i < 30; i++) {
            for (j = 0; j < 30; j++) {
                commandWords[i][j] = 0;
            }
        }

        j = 0;                                      
        ctr = 0;                               

        for (i = 0; i <= strlen(line); i++) {
            // If there is a space or null-terminated character found, assign the null-terminated character into commandWords[ctr][j].
            if (line[i] == ' ' || line[i] == '\0') {
                commandWords[ctr][j] = '\0';
                ctr++;
                j = 0;
            }

            // Otherwise, assign line[i] into commandWords[ctr][j].
            else {
                commandWords[ctr][j] = line[i];
                j++;
            }
        }

        pid_t pid;
        pid = fork(); // Creates a child process.

        // Failure to create a child process.
        if (pid < 0) {
            fprintf(stderr, "Fork failed");
            exit(2);
        }

        // Child process.
        else if (pid == 0) {
            char *buf[ctr + 1];

            // Assigns all elements of commandWords[i] into an array of char pointers, which is needed as an argument to execvp().
            for (i = 0; i < ctr; i++) {
                buf[i] = commandWords[i];
            }

            buf[ctr] = NULL; // Marks the end of the array.

            char outputFile[30]; // Output file.
            char errorFile[30]; // Error file.

            // Stores PID.out and PID.err in the output and error files.
            sprintf(outputFile, "%d.out", (int) getpid());
            sprintf(errorFile, "%d.err", (int) getpid());

            // Opens the output and error files.
            int file_desc1 = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777);
            int file_desc2 = open(errorFile, O_RDWR | O_CREAT | O_APPEND, 0777);

            // Makes stdout go to PID.out and stderr to PID.err.
            dup2(file_desc1, 1);
            dup2(file_desc2, 2);

            // Runs the command.
            execvp(buf[0], buf);

            // If execvp() fails, an error message is written to stderr, and the child process exits with 2.
            perror(buf[0]);
            exit(2);
        }

        // Parent process.
        else {
            char outputFile[30]; // Output file.
            sprintf(outputFile, "%d.out", pid); // Stores PID.out in the output file.

            int file_desc1 = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777); // Opens the output file.
            dup2(file_desc1, 1); // Makes stdout go to PID.out.

            // The "Starting command..." message is logged to PID.out.
            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", numCommands, pid, (int) getpid());
            fflush(stdout);
        }
    }

    fclose(fp); // Closes the file.

    // Deallocates memory.
    if (line) {
        free(line);
    }

    int status;
    pid_t pid;

    // The parent process waits for all child processes to finish.
    while ((pid = wait(&status)) > 0) {
        char outputFile[30]; // Output file.
        char errorFile[30]; // Error file.

        // Stores PID.out and PID.err in the output and error files.
        sprintf(outputFile, "%d.out", pid);
        sprintf(errorFile, "%d.err", pid); 

        int file_desc1 = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777); // Opens the output file.
        dup2(file_desc1, 1); // Makes stdout go to PID.out.

        // The "Finished child..." message is logged to PID.out.
        fprintf(stdout, "Finished child %d pid of parent %d\n", pid, (int) getpid());
        fflush(stdout);

        int file_desc2 = open(errorFile, O_RDWR | O_CREAT | O_APPEND, 0777); // Opens the error file.
        dup2(file_desc2, 2); // Makes stderr go to PID.err.

        // If the child process terminated normally, the message "Exited with exitcode = X" is written to PID.err.
        if (WIFEXITED(status)) {
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }

        // If the child process was killed with a signal, the message "Killed with signal S" is written to PID.err.
        else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}