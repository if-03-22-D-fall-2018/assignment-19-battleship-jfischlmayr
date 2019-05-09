/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

CellContent my_field[FIELDSIZE][FIELDSIZE];
CellContent op_field[FIELDSIZE][FIELDSIZE];
CellContent my_guess_field[FIELDSIZE][FIELDSIZE];

void load_game() {
    FILE* fd_my = fopen("battleship.my", "r");
    FILE* fd_op = fopen("battleship.op", "r");

    for (int i = 0; i < FIELDSIZE; ++i) {
        for (int j = 0; j < FIELDSIZE; ++j) {
            fread(&my_field[i][j], sizeof(CellContent), 1, fd_my);
            fread(&op_field[i][j], sizeof(CellContent), 1, fd_op);
            my_guess_field[i][j] = Unknown;
        }
    }

}

CellContent get_shot(int row, int col) {
    if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0) return OutOfRange;
    return my_field[row][col];
}

bool shoot(int row, int col) {
    if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0) return false;

    if (op_field[row][col] == Boat) {
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if(i == 0 && j == 0) {
                    my_guess_field[row][col] = Boat;
                } else {
                    if (!(row + i >= FIELDSIZE || col + j >= FIELDSIZE || row + i < 0 || col + j < 0))
                        my_guess_field[row + i][col + j] = Water;
                }
            }
        }
    } else {
        my_guess_field[row][col] = Water;
    }
    return true;
}

CellContent get_my_guess(int row, int col) {
    if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0) return OutOfRange;
    return my_guess_field[row][col];
}