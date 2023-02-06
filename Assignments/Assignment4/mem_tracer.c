/*
Authors: Rohan Athalye and Anni Shao
Date: April 11, 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// TRACE_NODE_STRUCT is a linked list of pointers to function identifiers.
// TRACE_TOP is the head of the list and is the top of the stack.
struct TRACE_NODE_STRUCT {
  int index; // Line index: the number in the input file.
  char* functionid; // Pointer to function identifier (a function name).
  struct TRACE_NODE_STRUCT* next; // Pointer to next frame.
};

typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;  // Pointer to the top of the stack.

/* 
The purpose of this stack is to trace the sequence of function calls, just like the stack in your computer would do. 
The "global" string denotes the start of the function call trace.
*/
void PUSH_TRACE(char* p) // Push p on the stack.
{
  TRACE_NODE* tnode;
  static char glob[] = "global";

  if (TRACE_TOP == NULL) {
    // Initialize the stack with "global" identifier.
    TRACE_TOP = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // No recovery needed if allocation failed, this is only used in debugging, not in production.
    if (TRACE_TOP == NULL) {
      printf("PUSH_TRACE: memory allocation error\n");
      exit(1);
    }

    TRACE_TOP->functionid = glob;
    TRACE_TOP->next = NULL;
  }

  // Create the node for p.
  tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

  // No recovery needed if allocation failed, this is only used in debugging, not in production.
  if (tnode == NULL) {
    printf("PUSH_TRACE: memory allocation error\n");
    exit(1);
  }

  tnode->functionid = p;
  tnode->next = TRACE_TOP; // Insert fnode as the first in the list.
  TRACE_TOP = tnode; // Point TRACE_TOP to the first node.
}

/* 
Pop a function call from the stack 
*/
void POP_TRACE() // Remove the top of the stack.
{
  TRACE_NODE* tnode;
  tnode = TRACE_TOP;
  TRACE_TOP = tnode->next;
  free(tnode);
}

/* Function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC */
/* Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
  int depth = 50; // A max of 50 levels in the stack will be combined in a string for printing out.
  int i, length, j;
  TRACE_NODE* tnode;
  static char buf[100];

  if (TRACE_TOP == NULL) { // Stack not initialized yet, so we are still in the 'global' area.
    strcpy(buf,"global"); 
    return buf;
  }

  // Peek at the depth(50) top entries on the stack, but do not go over 100 chars and do not go over the bottom of the stack. 
  sprintf(buf,"%s",TRACE_TOP->functionid);
  length = strlen(buf); // Length of the string so far.
  for(i = 1, tnode = TRACE_TOP->next;
                        tnode != NULL && i < depth;
                                  i++, tnode = tnode->next) {
    j = strlen(tnode->functionid); // Length of what we want to add.
    if (length + j + 1 < 100) {  // Total length is ok.
      sprintf(buf + length,":%s",tnode->functionid);
      length += j + 1;
    }else // It would be too long.
      break;
  }
  return buf;
}

// Function REALLOC calls realloc.
// TODO REALLOC should also print info about memory usage.
// For instance, example of print out: "File tracemem.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p, int t, char* file, int line)
{
	p = realloc(p, t);
  printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, PRINT_TRACE(), p, t);
	return p;
}

// Function MALLOC calls malloc.
// TODO MALLOC should also print info about memory usage.
// For instance, example of print out: "File tracemem.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t, char* file, int line)
{
	void* p;
	p = malloc(t);
  printf("File %s, line %d, function %s allocated new memory segment at address %p to size %d\n", file, line, PRINT_TRACE(), p, t);
	return p;
}

// Function FREE calls free.
// TODO FREE should also print info about memory usage.
// For instance, example of print out: "File tracemem.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p, char* file, int line)
{
	free(p);
  printf("File %s, line %d, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);
}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)

// Function create_array will create the 2d array of chars.
// Returns the created array.
char** create_array(char** arr, int rows, int columns) {
  PUSH_TRACE("create_array");
	int i;
  arr = (char**) malloc(sizeof(char*) * rows);

  for(i = 0; i < rows; i++) {
    arr[i] = (char*) malloc(sizeof(char) * columns);
	}

	POP_TRACE();
  return arr;
}

// Function add_column will add an extra column to a 2d array of chars.
// Returns the array (updated).
char** add_column(char** arr, int rows, int columns)
{
	PUSH_TRACE("add_column");
	int i;
  arr = (char**) realloc(arr, sizeof(char*) * rows);

	for(i = 0; i < rows; i++) {
    arr[i] = (char*) realloc(arr[i], sizeof(char) * (columns+1));
	}

	POP_TRACE();
  return arr;
}

// Function add_row will add an extra row to a 2d array of chars.
// Returns the array (updated).
char** add_row(char** arr, int rows, int columns) {
  PUSH_TRACE("add_row");
	int i;
  arr = (char**) realloc(arr, sizeof(char*) * rows);

  for(i = 0; i < rows; i++) {
    arr[i] = (char*) realloc(arr[i], sizeof(char) * columns);
	}

	POP_TRACE();
  return arr;
}

// Creates a new node containing the line and line index, and appends it to the linked list.
void create_node(TRACE_NODE **head, char *command, int index) {
  PUSH_TRACE("create_node");

  TRACE_NODE *newNode = (TRACE_NODE *) malloc(sizeof(TRACE_NODE)); // Allocates the new node on the heap.
  newNode->functionid = (char *) malloc(strlen(command) + 1); // Allocates the new node's function name. Makes sure to include the null terminator.
  strcpy(newNode->functionid, command); // Copies the contents of the 'command' parameter to the new node's function name. The null terminator is copied over as well.

  newNode->index = index; // Sets the line index of the node.
  newNode->next = NULL; // The new node is the last node in the linked list, so it does not have anything after it.

  // If the linked list is empty, then make the new node as the head.
  if (*head == NULL) {
    *head = newNode;
  }

  // Otherwise, traverse the linked list and append the new node.
  else {
    TRACE_NODE *currentNode = *head;

    while (currentNode->next != NULL) {
      currentNode = currentNode->next;
    }

    currentNode->next = newNode;
  }

  POP_TRACE();
}

// Frees the linked list.
void delete_nodes(TRACE_NODE **head) {
  PUSH_TRACE("delete_nodes");

  TRACE_NODE *currentNode = *head; // Stores the current node in the linked list.
  TRACE_NODE *nextNode; // Keeps track of the next node in the linked list.

  while (currentNode != NULL) {
    *nextNode = currentNode->next; // Updates the next node in the linked list.
    free(currentNode); // Frees the current node.
    free(currentNode->functionid); // Frees the current node's function name.
    currentNode = nextNode; // Updates the current node.
  }

  POP_TRACE();
}

// Recursively prints the index numbers and lines of all the nodes in the linked list.
void print_nodes(TRACE_NODE *node) {
  PUSH_TRACE("print_nodes");

  if (node != NULL) {
    printf("Index: %d, Line: %s", node->index, node->functionid);
    node = node->next;
    print_nodes(node);
  }

  POP_TRACE();
}

/**
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
void make_extend_array()
{
       PUSH_TRACE("make_extend_array");
	int i, j;
        int **array;
        int ROW = 4;
        int COL = 3;

        //make array
	array = (int**) malloc(sizeof(int*)*4);  // 4 rows
	for(i=0; i<ROW; i++) {
	 array[i]=(int*) malloc(sizeof(int)*3);  // 3 columns
	 for(j=0; j<COL; j++)
	  array[i][j]=10*i+j;
	}

        //display array
	for(i=0; i<ROW; i++)
	 for(j=0; j<COL; j++)
	  printf("array[%d][%d]=%d\n",i,j,array[i][j]);

	// and a new column
	int NEWCOL = add_column(array,ROW,COL);

	// now display the array again
        for(i=0; i<ROW; i++)
	 for(j=0; j<NEWCOL; j++)
	  printf("array[%d][%d]=%d\n",i,j,array[i][j]);

	 //now deallocate it
	 for(i=0; i<ROW; i++)
		 free((void*)array[i]);
	 free((void*)array);

	 POP_TRACE();
         return;
}//end make_extend_array
*/

int main(int argc, char *argv[])
{
  PUSH_TRACE("main");

  // If the user does not provide exactly 1 input file as an argument on the command line, output an error message and exit with 1.
  if (argc != 2) {
    printf("Please specify exactly 1 input file.\n");
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


  POP_TRACE();
  return(0);
}