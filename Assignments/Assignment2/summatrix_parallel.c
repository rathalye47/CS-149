#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*
Authors: Rohan Athalye and Anni Shao
Date: March 7, 2022
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

    // Starts the child processes (one per file).
    for (int i = 1; i < argc - 1; i++) {
        int fd1[2]; // First pipe used to send the number of columns to calculate the sum of each matrix.
        int fd2[2]; // Second pipe used to send the sum of each matrix to the total sum.
        pid_t p;

        // Failure to initialize the first pipe.
        if (pipe(fd1) == -1) {
            fprintf(stderr, "Pipe failed");
            exit(1);
        }

        // Failure to initialize the second pipe.
        if (pipe(fd2) == -1) {
            fprintf(stderr, "Pipe failed");
            exit(1);
        }

        // Creates a child process.
        p = fork();

        // Failure to create a child process.
        if (p < 0) {
            fprintf(stderr, "Fork failed");
            exit(1);
        }

        // Parent process.
        else if (p > 0) {
            int sum;

            // Closes the reading end of the first pipe.
            close(fd1[0]);

            // Writes the number of columns and closes the writing end of the first pipe.
            write(fd1[1], &cols, sizeof(cols));
            close(fd1[1]);

            // Waits for the child process to send its matrix sum value.
            wait(NULL);
            
            // Closes the writing end of the second pipe.
            close(fd2[1]);

            // Reads the matrix sum from the child process.
            read(fd2[0], &sum, sizeof(sum));
            
            // Adds the matrix sum to the total sum.
            totalSum += sum;

            // Closes the reading end of the second pipe.
            close(fd2[0]); 
        }

        // Child process.
        else {
            // Closes the writing end of the first pipe.
            close(fd1[1]);

            int sum = 0;

            // Reads the number of columns using the first pipe.
            read(fd1[0], &cols, sizeof(cols));
            int numCols = cols;

            // Opens the file.
            FILE *fp = fopen(argv[i], "r");

            // If the child process fails to open a file, prints an error message, writes the matrix sum, and exits with 1.
            if (fp == NULL) {
                printf("range: cannot open file\n");
                write(fd2[1], &sum, sizeof(sum));
                exit(1);
            }

            else {
                fseek(fp, 0, SEEK_END); // Goes to the end of the file.

                // If the file is empty with no numbers, writes the matrix sum, and exits with 0.
                if (ftell(fp) == 0) {
                    write(fd2[1], &sum, sizeof(sum));
                    exit(0);
                }

                fseek(fp, 0, SEEK_SET); // Goes to the beginning of the file.

                char str[5000]; // Stores the lines in the file.

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
                    for (int i = 0; i < numCols && sscanf(data, " %d%n", &num, &offset) == 1; i++) {
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

            // Closes the file.
            fclose(fp);

            // Closes both of the reading ends.
            close(fd1[0]);
            close(fd2[0]);

            // Writes the matrix sum and closes the writing end of the second pipe.
            write(fd2[1], &sum, sizeof(sum));
            close(fd2[1]);

            exit(0);
        }
    }

    printf("Sum: %d\n", totalSum); // Prints the total sum from all of the matrices.
    exit(0);
}