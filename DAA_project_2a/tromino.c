/*
 ============================================================================
 Name        : tromino.c
 Author      : Chetan
 Email       : cgajare1@binghamton.edu
 Created on  : Mar 15, 2017
 Description : 
 ============================================================================
 */

#include <stdio.h>
#include <math.h>

int counter = 1;
void tromino(int, int, int, int, int, int size, int board[][size]);
void print(int size, int board[][size]);

int main(int argc, char *args[])
{
	int k;
	k = atoi(args[1]);
	int size= pow(2, k);
	int board[size][size];
	int i, j;
	int x_hole, y_hole;

	x_hole = atoi(args[2]);
	y_hole = atoi(args[3]);

	printf("\n k : %d  size:%d x:%d y:%d \n " ,k,size,x_hole,y_hole);
	if ((k < 1) || (x_hole > size) || (y_hole > size) || (x_hole < 0) || (y_hole < 0))
	{
		printf(".....Wrong Input.....\n");
	}
	else
	{
		for (i = 0; i < size; ++i)
			for (j = 0; j < size; ++j)
				board[i][j] = 0;

		board[x_hole][y_hole] = 0;
		tromino(size, x_hole, y_hole, 0, 0, size, board);
		print(size, board);
	}
	return 0;
}
void tromino(int newSize, int x_hole, int y_hole, int x_tile, int y_tile, int size, int board[][size])
{
	int i, j;
	int x_center, y_center;
	int x_01, y_01, x_00, y_00, x_11, y_11, x_10, y_10;

	if (newSize == 2)
	{
		for (i = x_tile; i < (newSize + x_tile); i++)
			for (j = y_tile; j < (newSize + y_tile); j++)
				if ((i != x_hole) || (j != y_hole))
					board[i][j] = counter;
		counter++;
	}
	else
	{
		newSize = newSize / 2;
		x_center = x_tile + newSize;
		y_center = y_tile + newSize;

		if (x_hole < x_center)
		{
			board[x_center][y_center - 1] = counter;
			board[x_center][y_center] = counter;
			if (y_hole < y_center)
			{
				board[x_center - 1][y_center] = counter;
				x_00 = x_hole;
				y_00 = y_hole;
				x_01 = x_center - 1;
				y_01 = y_center;
				x_10 = x_center;
				y_10 = y_center - 1;
				x_11 = x_center;
				y_11 = y_center;
			}
			else
			{
				board[x_center - 1][y_center - 1] = counter;
				x_00 = x_center - 1;
				y_00 = y_center - 1;
				x_01 = x_hole;
				y_01 = y_hole;
				x_10 = x_center;
				y_10 = y_center - 1;
				x_11 = x_center;
				y_11 = y_center;
			}
		}
		else if (x_hole >= x_center)
		{
			board[x_center - 1][y_center - 1] = counter;
			board[x_center - 1][y_center] = counter;

			if (y_hole < y_center)
			{
				board[x_center][y_center] = counter;
				x_00 = x_center - 1;
				y_00 = y_center - 1;
				x_01 = x_center - 1;
				y_01 = y_center;
				x_10 = x_hole;
				y_10 = y_hole;
				x_11 = x_center;
				y_11 = y_center;
			}
			else
			{
				board[x_center][y_center - 1] = counter;
				x_00 = x_center - 1;
				y_00 = y_center - 1;
				x_01 = x_center - 1;
				y_01 = y_center;
				x_10 = x_center;
				y_10 = y_center - 1;
				x_11 = x_hole;
				y_11 = y_hole;
			}
		}
		counter++;
		tromino(newSize, x_00, y_00, x_tile, y_tile, size, board);
		tromino(newSize, x_01, y_01, x_tile, y_tile + newSize, size, board);
		tromino(newSize, x_10, y_10, x_tile + newSize, y_tile, size, board);
		tromino(newSize, x_11, y_11, x_tile + newSize, y_tile + newSize, size, board);
	}
}
void print(int size, int board[][size])
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] != 0)
				printf("%d\t", board[i][j]);
			else
				printf("X\t");
		}
		printf("\n");
	}
}
