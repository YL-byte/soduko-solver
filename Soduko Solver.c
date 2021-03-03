#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define N 3
#define EMPTY_SPACE 0
#define NO_NUMBER -1

bool solveSoduko(int soduko[N*N][N*N]);

bool aux(int soduko[N*N][N*N], int depth);

void printBoard(int soduko[N*N][N*N]);

bool isValid(int soduko[N*N][N*N]);

int main(){

   int soduko[N*N][N*N] = { //52 empty cells
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    bool result = solveSoduko(soduko);

    if (result)
        printBoard(soduko);

}

bool solveSoduko(int soduko[N*N][N*N]){

    return aux(soduko, 0);

}

bool aux(int soduko[N*N][N*N], int depth){

    //We reached a solution
    if (depth == N*N*N*N)
        return true;

    int current_row = depth / (N*N), current_col = depth % (N*N);

    bool result = false;

    //No need to try adding a number to a non-empty spot
    if (soduko[current_row][current_col] == EMPTY_SPACE){

        for (int number = 1; number <= N*N; number++){

            result = false;

            soduko[current_row][current_col] = number;

            //This is a valid solution
            if(isValid(soduko))
                result = aux(soduko, depth + 1);

            //We found a solution
            if (result)
                return true;

            //This number in this current location has no solution
            soduko[current_row][current_col] = EMPTY_SPACE;

        }

    }

    else
        result = aux(soduko, depth + 1);

    return result;

}

void printBoard(int soduko[N*N][N*N]){

    for (int row = 0; row < N*N; row++){

        printf("| ");

        for (int col = 0; col < N*N; col++){

            printf("%d | ", soduko[row][col]);

        }

        printf("\n");

    }

}

bool isValid(int soduko[N*N][N*N]){

    //Check if we've seen this number
    bool hist[N*N] = { false };

    //Check Rows
    for (int row = 0; row < N*N; row++){

        for (int i = 0; i < N*N; i++)
            hist[i] = false;

        for (int col = 0; col < N*N; col++){

            int current_number = soduko[row][col] - 1;

            //There can't be 2 appearances of this number
            if (current_number > NO_NUMBER && hist[current_number])
                return false;

            //We've seen this number -> turn hist to true
            if (current_number != NO_NUMBER)
                hist[current_number] = true;

        }

    }

    //Check Columns
    for (int col = 0; col < N*N; col ++){

        //Check if we've seen this number
        for (int i = 0; i < N*N; i++)
            hist[i] = false;

        for (int row = 0; row < N*N; row++){

            int current_number = soduko[row][col] - 1;

            //There can't be 2 appearances of this number
            if (current_number > NO_NUMBER && hist[current_number] == true)
                return false;

            //We've seen this number -> turn hist to true
            if (current_number != NO_NUMBER)
                hist[current_number] = true;

        }

    }

    //Check current box
    for (int start_row = 0; start_row < N*N; start_row += N){

        for (int start_col = 0; start_col < N*N; start_col += N){

        for (int i = 0; i < N*N; i++)

            hist[i] = false;

            for (int row = start_row; row < start_row + N; row++){

                for (int col = start_col; col < start_col + N; col++){

                    int current_number = soduko[row][col] - 1;

                    if (current_number != NO_NUMBER && hist[current_number] == true)
                        return false;

                    if (current_number != NO_NUMBER)
                        hist[current_number] = true;

                }

            }

        }

    }

    return true;

}
