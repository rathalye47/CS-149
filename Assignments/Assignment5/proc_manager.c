/*
Authors: Rohan Athalye and Anni Shao
Date: April 27, 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <time.h>

// Hash table entry.
struct nlist {
    struct nlist *next; // Next entry in chain.
    struct timespec start; // Start time.
    struct timespec finish; // Finish time.
    int index; // Line index in input text file.
    int pid; // Process id.
    char *command; // Command.
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // Pointer table.

// Hash function: pid % HASHSIZE.
unsigned hash(int pid) {
    return pid % HASHSIZE;
}

// Looks for an entry by pid.
// Traverses the linked list under a slot of the hash table.
// The array position to look in is returned by the hash function.
struct nlist *lookup(int pid) {
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next)
        if (pid == np->pid) 
            return np;
    return NULL;
}

// Inserts the information for a new pid and command into the hash table.
struct nlist *insert(char *command, int pid, int index) {
    struct nlist *np;
    unsigned hashval;

    // Does lookup by pid.
    // If the pid is not found, create it with malloc.
    // Then, set the pid, command, and index.
    if ((np = lookup(pid)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->command = strdup(command)) == NULL) {
            return NULL;
        }

        np->pid = pid;
        np->index = index;

        hashval = hash(pid);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }

    // Else, the pid is already there in the hashslot.
    // Sets the command and index again.
    else {
        free((void *) np->command);

        if ((np->command = strdup(command)) == NULL) {
            return NULL;
        }

        np->index = index;
    }

    return np;
}

// Executes execvp().
void runExecvp(char commandLine[], int lineNum, int restart) {
    // If restart is true, print "RESTARTING" to stdout.
    if (restart) {
        fprintf(stdout, "RESTARTING\n");
    }
    
    char outputFile[30]; 
    sprintf(outputFile, "%d.out", getpid()); // Stores PID.out in output file.

    int file_desc1 = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777); // Opens output file.
    dup2(file_desc1, 1); // Makes stdout go to PID.out.

    fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", lineNum, getpid(), getppid());
    fflush(stdout);

    int i = 0;
    char *buf[strlen(commandLine)]; // Used in execvp().
    
    char *token;
    token = strtok(commandLine, " \n"); // Splits the line by " \n".

    // Copies contents of token into buf, which will be passed into execvp().
    while (token != NULL) {
        buf[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    
    buf[i] = NULL;
    
    // Runs the command.
    execvp(buf[0], buf);
    
    // If execvp() fails, an error message is written to stderr, and the child process exits with 2.
    perror(buf[0]);
    exit(2);
}

int main(int argc, char *argv[]) {
    // If the user does not provide exactly 1 input file as an argument on the command line, output an error message and exit with 1.
    if (argc != 2) {
        printf("Please specify exactly 1 input file from which to execute commands.\n");
        exit(1);
    }

    FILE *fp; // File pointer.
    char *inputFile = argv[1]; // Stores the 2nd command line argument, which is the input file.

    fp = fopen(inputFile, "r"); // Opens the file.

    // If the file pointer is NULL, print an error message and exit with 1.
    if (fp == NULL) {
        printf("Range: cannot open file.\n");
        exit(1);
    }

    char *line = NULL; // Points to each line in the input file.
    size_t len = 0; // Stores the size of the line.
    ssize_t read; // Reads the lines from the file.
    int numCommands = 0; // Stores the number of commands.

    struct timespec start;
    struct timespec finish;

    // Reads each line from the input file.
    while ((read = getline(&line, &len, fp)) != -1) {
        // If the line ends in a new line '\n', replace it with '\0' (null).
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        
        numCommands++; // Increments the number of commands. 
        clock_gettime(CLOCK_MONOTONIC, &start); // Marks the start time.

        int pid;
        pid = fork(); // Creates child process.

        // Failure to create a child process.
        if (pid < 0) {
            fprintf(stderr, "Fork failed");
            exit(2);
        }

        // Child process.
        else if (pid == 0) {
            runExecvp(line, numCommands, 0); // Executes command.
            exit(0);
        }

        // Parent process.
        else {
            struct nlist* my_node = insert(line, pid, numCommands); // Inserts new pid into hash table.
            my_node->start = start; // Records the new start time.
        }
    }

    fclose(fp);

    // Deallocation of memory.
    if (line) {
        free(line);
    }

    int status;
    pid_t pid;
    double elapsed_time;
    struct nlist* entry;

    // The parent process waits for all child processes to finish.
    while ((pid = wait(&status)) >= 0) {
        clock_gettime(CLOCK_MONOTONIC, &finish); // Marks the finish time.
        entry = lookup(pid); // Looks up hash table entry by pid.

        // Null entry error.
        if (entry == NULL) {
            printf("Entry is NULL\n");
        }

        // Records the finish time and calculates the elapsed time.
        else {
            entry->finish = finish;
            double finish_time = (double)entry->finish.tv_sec + 1.0e-9 * entry->finish.tv_nsec;
            double start_time = (double)entry->start.tv_sec + 1.0e-9 * entry->start.tv_nsec;
            elapsed_time = finish_time - start_time;
        }

        char outputFile[30];
        sprintf(outputFile, "%d.out", pid); // Stores PID.out in output file.
        
        int file_desc1 = open(outputFile, O_RDWR | O_CREAT | O_APPEND, 0777); // Opens the output file.
        dup2(file_desc1, 1); // Makes stdout go to PID.out.
        
        fprintf(stdout, "Finished child %d pid of parent %d\n", pid, (int) getpid());
        fprintf(stdout, "Finished at %ld, runtime duration %.5f", entry->finish.tv_nsec, elapsed_time);
        fflush(stdout);

        char errorFile[30];
        sprintf(errorFile, "%d.err", pid); // Stores PID.err in error file.

        int file_desc2 = open(errorFile, O_RDWR | O_CREAT | O_APPEND, 0777); // Opens the error file.
        dup2(file_desc2, 2); // Makes stderr go to PID.err.

        // If the child process terminated normally, the message "Exited with exitcode = X" is written to PID.err.
        if (WIFEXITED(status)) {
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));

            // If the process completed in less than 2 seconds, a "Spawning too fast" message is written to stderr.
            if (elapsed_time <= 2) {
                fprintf(stderr, "Spawning too fast");
            }
        }

        // If the child process was killed with a signal, the message "Killed with signal S" is written to PID.err.
        else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));

            // If the process completed in less than or equal to 2 seconds, a "Spawning too fast" message is written to stderr.
            if (elapsed_time <= 2) {
                fprintf(stderr, "Spawning too fast");
            }
        }

        // The command took more than 2 seconds to complete.
        if (elapsed_time > 2) {
            clock_gettime(CLOCK_MONOTONIC, &start); // Marks the start time.

            int pid;
            pid = fork(); // Creates a child process.

            // Failure to create child process.
            if (pid < 0) {
                fprintf(stderr, "Fork failed");
                exit(1);
            }

            // Child process.
            else if (pid == 0) {
                runExecvp(entry->command, entry->index, 1); // Run execvp().
            }

            // Parent process.
            else {
                struct nlist* new_entry = insert(entry->command, pid, entry->index); // Insert the new pid into the hash table.
                new_entry->start = start; // Records the new start time.
            }
        }
    }

    return 0;
}