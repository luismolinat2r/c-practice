#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int globalRows, globalColumns;
int globalHigh, globalLow;
#define null -1

typedef struct bool
{
	unsigned val : 1;
} bool;

void printMatrix(int** matrix)
{ 
	for (int i = 0; i < globalRows; i++)
		for (int j = 0; j < globalColumns; j++)
			printf("%d ", matrix[i][j]);

		printf("\n");
}

int getMinRotations(int rotations, int columns, int rows)
{
	int minRotations = (2 * (columns + rows)) - 4;

	if (rotations > minRotations)
	{
		int additionalRotations = rotations % minRotations;
		return minRotations + additionalRotations;
	}
	else
	{
		return rotations; 
	}
}
 
void rotateMatrix(int** matrix, int top, int right, int left, int bottom, int rotations)
{ 
	int dimensions = (right / 2) < (bottom / 2) ? right / 2 : bottom / 2; 
	 
	int columns = bottom; 
	int rows = right; 

	while (dimensions > 0)
	{
		int minRotationsByDimension = getMinRotations(rotations, rows, columns);

		//Calculate minimum amount of rotations for this dimension 
		while ((minRotationsByDimension--) > 0)
		{
			int rowScan = 0;
			int columnScan = 0;

			//Custom Stack FIFO
			int high = -1;
			int low = -1;
			globalHigh = -1;
			globalLow = -1;
			bool bit;
			bit.val = 0;

			//Scanning left side
			int i = top;
			int j = left;
			while (columnScan != 1)
			{
				if ((i + 1) >= bottom)
				{
					columnScan = 1;
				}
				else
				{
					if (high == null)
					{
						high = matrix[i + 1][j];
						bit.val = 1;
					}
					else if (low == null)
					{
						low = matrix[i + 1][j];
						bit.val = 0;
					}

					if (i == top)
					{
						matrix[i + 1][j] = matrix[i][j];
					}
					else if (high != null && bit.val == 0)
					{
						matrix[i + 1][j] = high;
						high = null;
					}
					else if (low != null && bit.val == 1)
					{
						matrix[i + 1][j] = low;
						low = null;
					}
					i++;
				}
			}

			//Scanning bottom side 
			i = bottom - 1;
			j = j + 1;
			int start = 1;
			while (rowScan != 1)
			{
				if ((j + 1) >= right)
				{
					rowScan = 1;
				}
				else
				{
					if (high == null)
					{
						high = matrix[i][j];
						bit.val = 1;
					}
					else if (low == null)
					{
						low = matrix[i][j];
						bit.val = 0;
					}

					if (j == left)
					{
						matrix[i][j] = matrix[i][j];
					}
					else if (high != null && bit.val == 0)
					{
						matrix[i][j] = high;
						high = null;
					}
					else if (low != null && bit.val == 1)
					{
						matrix[i][j] = low;
						low = null;
					}
					j++;
				}

			}

			columnScan = 0;
			rowScan = 0;

			//Scanning Right side 
			while (columnScan != 1)
			{
				if ((i - 1) < left)
				{
					columnScan = 1;
				}
				else
				{
					if (high == null)
					{
						high = matrix[i][j];
						bit.val = 1;
					}
					else if (low == null)
					{
						low = matrix[i][j];
						bit.val = 0;
					}

					if (i == top)
					{
						matrix[i][j] = matrix[i][j];
					}
					else if (high != null && bit.val == 0)
					{
						matrix[i][j] = high;
						high = null;
					}
					else if (low != null && bit.val == 1)
					{
						matrix[i][j] = low;
						low = null;
					}
					i--;
				}
			}

			//Scanning top side 
			while (rowScan != 1)
			{
				if ((j - 1) < left)
				{
					rowScan = 1;
				}
				else
				{
					if (high == null)
					{
						high = matrix[i][j];
						bit.val = 1;
					}
					else if (low == null)
					{
						low = matrix[i][j];
						bit.val = 0;
					}


					if (high != null && bit.val == 0)
					{
						matrix[i][j] = high;
						high = null;
					}
					else if (low != null && bit.val == 1)
					{
						matrix[i][j] = low;
						low = null;
					}
					j--;
				}
			}

			matrix[top][left] = high != null ? high : low; 
		}

		top++;
		left++;
		bottom--;
		right--;
		rows -= 2; 
		columns -= 2;
		dimensions--;
	}
}
 
int main()
{
	//-- Declaring variables
	int rows, columns, rotations;

	//-- Initializing variables
	rows = 0;
	columns = 0;
	rotations = 0;

	//-- Scanning parameters and adding them to the stdin buffer
	scanf("%d %d %d", &rows, &columns, &rotations);

	globalRows = rows;
	globalColumns = columns;

	//-- Initializing 2D array to save the Matrix values allocating space in memory
	int **matrix = (int**)malloc(rows * sizeof(int*));

	//-- Initializing each allocated pointer to each column size
	for (int i = 0; i < rows; i++)
		matrix[i] = malloc(columns * sizeof(int));

	//-- Scanning Matrix values and saving them into stdin buffer
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			scanf("%d", &matrix[i][j]);
		 
	rotateMatrix(matrix, 0, columns, 0, rows, rotations);
	 
	printMatrix(matrix);
  
	return 0;
}
