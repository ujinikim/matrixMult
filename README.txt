
### General Info
***

matrixMult is a multithreaded program that is designed to perform multiplication between two matrices concurrently.
User can pick the number of threads to be used for calculation, and the result matrix will be return as a text file.
Each thread will perform a multiplication between a single row of the first matrix and a single column of the second matrix.
Once all of the threads are created and is running, it will wait for them to finish their calculation, then all of the threads
will be created and started passing in the arguments that contains structured dataset.
The argument passed into each thread contains index of final matrix where needs to be inserted and an array that contains
integer values to be calculated. The first value (array[0]) denotes the length of the array divided by two. This value is used
to iterate and multiply each values in the array until it reaches the end of the array. 
 

## Technologies
***

A list of technologies used within the project:
Microsoft Visual Studio Code
C++ language


## Instructions
***

The program will read two specified text files which has a matrix, and then it creates a text file if not yet exist.
The result matrix will be written into the specified output file. The user can name the file however they want as long
as it is text file.
Every text files to be used as matrix has to be formatted with a space between every element or value, and new rows must
be written in a new line.
For example, 3x3 matrix must be written as follow
Inside (input1.txt)
[
1   2   3
4   5   6
7   8   9
]
The final result text file will formatted in the same format as above.
Please note that maximum elements in the result matrix cannot exceed 100. However, you may change the value to any integer value
in the source code (matC[x]).


## Formatting instructions on execution
> User must use "make" command to create an executable file.
> The executable file "matrixMult" will be created after makeFile.
> In the directory where the exectuable file is stored
> User must format their input as follow
> ./matmult u v w input1.txt input2.txt output.txt threads
> u - number of rows of the first matrix
> v - number of columns of the first matrix & number of rows of the second matrix
> w - number of colums of the second matrix
> In order to complete multiplication of two matrices, the number of columns of the first matrix and the number of the rows
of the second matrix must be the same. Otherwise multiplication cannot be done.
> input1.txt - user-defined text file with the first matrix
> input2.txt - user-defined text file with the second matrix
> output.txt - user-defined name of a text file where result matrix to be inserted
> threads - integer value representing number of threads to be used

