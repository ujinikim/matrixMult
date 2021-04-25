//Eo Jin Kim
//CS 4348
//g++ -pthread matrixMult.cpp
//./a.out 5 9 3 input_5x9.txt input_9x3.txt output.txt threads
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <thread>
using namespace std;

int matC[100]; //saves the each dot product results temporarily

struct args //struct to pass in pthread_create
{
    int location; // location to store calculated value
    int *matArray; // array storing matrix values to be calculated
    //matArray[0] is always the length of matrix (number of columns of matrix 1)
};

void *mult(void *dataSet) //function to be called when pthread is created
{
    int accum = 0; //accumulates the multiplied values
    int *data = ((struct args *)dataSet)->matArray; //struct
    int loc = ((struct args *)dataSet)->location; //struct

    int x = data[0];
    for (int i = 1; i <= x; i++)
        accum += data[i] * data[i + x]; //dot product by splitting array into two parts, matrix 1 * matrix 2

    matC[loc] = accum; //stores final accum value into temp array for final matrix
    pthread_exit(NULL); //exit out of pthread
}

int main(int argc, char **argv)
{

    errno = 0;
    const int u = strtol(argv[1], NULL, 10);
    const int v = strtol(argv[2], NULL, 10);
    const int w = strtol(argv[3], NULL, 10);
    if (errno != 0) //checks if user inserted int value for u, v, and w
    {
        cout << "ERROR: Invalid input for size of matrices"
             << "\n";
        return 1;
    }
    if (u < 1 || v < 1 || w < 1) // checks if size of matrix is less than 1
    {
        cout << "ERROR: Invalid input for size of matrices\n NOTE: The size of a matrix must be greater than 0"
             << "\n";
        return 1;
    }

    int matA[u][v]; //initialize matrix 1 and 2
    int matB[v][w];

    ifstream readFile1(argv[4]); //Opens txt file for the first matrix and saves into matA
    ifstream readFile2(argv[5]); //Opens txt file for the second matrix and saves into matB
    ofstream writeFile(argv[6]); //Opens txt file to be written for result matrix
    if (!readFile1.is_open())
    {
        cout << "ERROR: File 1 does not exist\n";
        return 1;
    }
    if (!readFile2.is_open())
    {
        cout << "ERROR: File 2 does not exist\n";
        return 1;
    }
    if (!writeFile.is_open())
    {
        cout << "ERROR: Write file does not exist\n";
        return 1;
    }

    //read from files and store values into each 2d array matrix
    for (int i = 0; i < u; i++)
        for (int j = 0; j < v; j++)
        {
            readFile1 >> matA[i][j];
        }
    for (int i = 0; i < v; i++)
        for (int j = 0; j < w; j++)
        {
            readFile2 >> matB[i][j];
        }
    readFile1.close();
    readFile2.close();
    
    // Displays First Matrix
    cout << endl
         << "\nFirst Matrix" << endl;
    for (int i = 0; i < u; i++)
    {
        for (int j = 0; j < v; j++)
            cout << matA[i][j] << " ";
        cout << endl;
    }

    // Displays SEcond Matrix
    cout << endl
         << "\nSecond Matrix" << endl;
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < w; j++)
            cout << matB[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    errno = 0;
    const int NUMBER_OF_THREADS = strtol(argv[7], NULL, 10); //the number of threads to be used by user input
    const int NUMBER_OF_ELEMENTS = u*w; // the number of elements in the final matrix
    if (errno != 0)
    {
        cout << "ERROR: Invalid input for number of threads\n";
        return 1;
    }

    pthread_t *threads;
    threads = (pthread_t *)malloc(NUMBER_OF_THREADS * sizeof(pthread_t));

    int locCounter = 0;
    int threadCount = 0;
    int *data = NULL;

    for (int i = 0; i < u; i++)
        for (int j = 0; j < w; j++)
        {
            struct args *dataSet = (struct args *)malloc(sizeof(struct args));
            data = (int *)malloc((v*2+1) * sizeof(int));
            data[0] = v; //stores number of multiplication needed for later use on in the mult function
            for (int k = 0; k < v; k++)
            {
                data[k + 1] = matA[i][k];     //put the each columns of matA
                data[k + v + 1] = matB[k][j]; //put the each rows of matB
            }
            dataSet->matArray = data;
            dataSet->location = locCounter++;

            pthread_create(&threads[threadCount++], NULL, mult, (void *)(dataSet));
            if (threadCount == NUMBER_OF_THREADS) //if all the threads are created, then wait for them to finish
            {
                for (int z = 0; z < NUMBER_OF_THREADS; z++)
                {
                    pthread_join(threads[z], NULL);
                }
                threadCount = 0; //goes back to the first thread
            }
        }
    cout << "FINAL JOINING HAPPENED\n";
    for (int z = 0; z < NUMBER_OF_THREADS; z++) // closes all the threads after using them
        pthread_join(threads[z], NULL);

    //writes final matrix into a file
    for (int i = 1; i <= NUMBER_OF_ELEMENTS; i++)
    {
        writeFile << matC[i - 1];
        if (i % w == 0)
            writeFile << "\n";
        else
            writeFile << " ";
    }
    writeFile.close();

    return 0;
}
