# Sparse Matrix Operations

This C++ repository provides implementations for various operations on sparse matrices using both arrays and linked lists. The operations include addition, multiplication, and transpose.

## Sparse Matrix Representation

### Array Representation

The array representation uses a vector of `rcv` (row-col-value) objects to store non-zero elements. Each `rcv` object represents a non-zero element in the matrix and includes information about its row, column, and value.

### Linked List Representation

The linked list representation uses a custom `LinkedList` class to maintain a linked list of `rcv` objects. Each node in the linked list represents a non-zero element, and the nodes are connected based on their positions in the matrix.

## Operations

### 1. Addition

#### Array Representation

To perform addition on sparse matrices represented as arrays, the `addArr` function takes two vectors of `rcv` objects and outputs the result as a new vector.

#### Linked List Representation

To perform addition on sparse matrices represented as linked lists, the `addList` function takes two linked lists of `rcv` nodes and outputs the result as a new linked list.

### 2. Transpose

#### Array Representation

To compute the transpose of a sparse matrix represented as an array, the `transposeArr` function swaps the rows and columns of each `rcv` object and outputs the transposed matrix.

#### Linked List Representation

To compute the transpose of a sparse matrix represented as a linked list, the `transposeList` function swaps the rows and columns of each `rcv` node and outputs the transposed matrix as a linked list.

### 3. Multiplication

#### Array Representation

To perform multiplication on sparse matrices represented as arrays, the `multiplyArr` function takes two vectors of `rcv` objects and outputs the result as a new vector.

#### Linked List Representation

To perform multiplication on sparse matrices represented as linked lists, the `multiplyList` function takes two linked lists of `rcv` nodes and outputs the result as a new linked list.

## Input Format

The program takes queries as input, where each query specifies the choice of data structure (array or linked list) and the operation to be performed (addition, multiplication, or transpose). The input matrices are then provided, and the corresponding operation is executed.

