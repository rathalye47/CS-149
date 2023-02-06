#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

/*
Author: Rohan Athalye
Date: April 4, 2022
*/
int main(int argc, char *argv[]) {
    // If less than 2 arguments are provided by the user, exit with 0.
    if (argc < 3) {
        exit(0);
    }

    // Gets the last command line argument, which is the number of columns.
    char *colsStr = argv[argc - 1];

    // If the last command line argument can't be converted to an integer, exit with 0.
    if (atoi(colsStr) == 0) {
        exit(0);
    }

    // Converts the last command line argument to an integer.
    int cols = atoi(colsStr);

    // Stores the total sum.
    int totalSum = 0;

    // Creates a memory mapping.
    int *mem;
    mem = (int*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, 1, 0);

    // Starts the child processes (one per file).
    for (int i = 1; i < argc - 1; i++) {
        pid_t p;

        // Creates a child process.
        p = fork();
 
        // Failure to create a child process.
        if (p < 0) {
            fprintf(stderr, "Fork failed");
            exit(1);
        }

        // Child process.
        else if (p == 0) {
            int sum = 0;

            // Opens the file.
            FILE *fp = fopen(argv[i], "r");

            // If the child process fails to open a file, prints an error message and exits with 1.
            if (fp == NULL) {
                printf("range: cannot open file\n");
                exit(1);
            }

            else {
                // If the memory mapping fails, writes an error message to stderr and exits with 1.
                if (mem == MAP_FAILED) {
                    fprintf(stderr, "mmap() failed");
                    exit(1);
                }

                mem[0] = cols; // Stores the number of columns in the memory map.

                char str[5000];

                // Goes through the file line by line.
                while (fgets(str, 5000, fp) != NULL) {
                    // If the line ends in a new line '\n', replace it with '\0' (null).
                    if (str[strlen(str) - 1] == '\n') {
                        str[strlen(str) - 1] = 0;
                    }

                    char *data = str;
                    int offset;
                    int num;

                    // Reads up to N numbers, and then goes to the next line once finished.
                    for (int i = 0; i < mem[0] && sscanf(data, " %d%n", &num, &offset) == 1; i++) {
                        // If a number is less than 0, set it to 0 and print a warning message to stderr.
                        if (num < 0) {
                            fprintf(stderr, "Warning: Value %d found.\n", num);
                            num = 0;
                        }

                        sum += num; // Adds the number to the matrix sum.
                        data += offset; // Goes to the next number in the line.
                    }
                }
            }

            mem[i] = sum; // Stores the matrix sum in the memory map.

            // Closes the file.
            fclose(fp);

            // Removes the memory mapping.
            munmap(mem, 4096);

            exit(0);
        }

        else {
            wait(NULL); // Waits for the child process to finish.
            totalSum += mem[i]; // Adds the matrix sum stored in the memory map to the total sum.
        }
    }

    printf("Sum: %d\n", totalSum); // Prints the total sum from all of the matrices.
    exit(0);
}