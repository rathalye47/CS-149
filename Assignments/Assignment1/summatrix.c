#include <stdio.h>
#include <stdlib.h>

/*
Authors: Rohan Athalye and Anni Shao
Date: February 16, 2022
*/
int main(int argc, char *argv[]) {
    // If the number of arguments is 1 or greater than 2, print an error message to stderr and exit with 2.
    if (argc == 2 || argc > 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        exit(2);
    }

    // If no arguments are provided, exit with 0.
    if (argc == 1) {
        exit(0);
    }

    // Opens the file.
    // If the file pointer returns NULL, print an error message and exit with 1.
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("range: cannot open file\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END); // Goes to the end of the file.
    
    // If the file is empty with no numbers, exit with 0.
    if (ftell(fp) == 0) {
        exit(0);
    }

    fseek(fp, 0, SEEK_SET); // Goes to the beginning of the file.

    char str[300]; // Stores the lines in the file.
    int cols = atoi(argv[2]); // Stores the 2nd command line argument, which is the number of columns.
    int total; // Keeps track of the running sum.

    // Goes through the file line by line.
    while (fgets(str, 300, fp) != NULL) {
        char *data = str;
        int offset;
        int num;

        // Reads up to N numbers, and then goes to the next line once finished.
        for (int i = 0; i < cols && sscanf(data, " %d%n", &num, &offset) == 1; i++) {
            // If the number is less than 0, set it to 0 and print a warning message to stderr.
            if (num < 0) {
                fprintf(stderr, "Warning - Value %d found.\n", num);
                num = 0;
            }

            total += num; // Adds the number to the running sum.
            data += offset; // Goes to the next number in the line.
        } 
    }

    printf("Sum: %d\n", total); // Prints the sum.
    fclose(fp); // Closes the file.
    exit(0); // Exits with 0.
}