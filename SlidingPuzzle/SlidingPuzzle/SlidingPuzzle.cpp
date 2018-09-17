#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;

void printBoard(int** b) {
	cout << "--------------" << endl;
	for (size_t col = 0; col < 4; col++)
	{
		cout << "|";

		for (size_t row = 0; row < 4; row++)
		{
			if (b[col][row] != -1) {
				cout << b[col][row];
				cout << " ";
				if (b[col][row] < 10) {
					cout << " ";
				}
			}
			else {
				cout << "   ";
			}
		}

		cout << "|" << endl;
	}
	cout << "--------------" << endl;
}

void shuffleBoard(int** b) {
	cout << "SHUFFLE" << endl;
	int shuffleCount = 0;
	srand(time(NULL));
	while (shuffleCount < 15) {
		for (size_t col = 0; col < 4; col++)
		{
			for (size_t row = 0; row < 4; row++)
			{
				if (b[col][row] == 0) {
					int randDir = rand() % 4;
					switch (randDir)
					{
					case 0:
						if (col - 1 != -1) {
							cout << "UP" << endl;
							b[col][row] = b[col - 1][row];
							b[col - 1][row] = 0;
						}
						break;
					case 1:
						if (row - 1!= -1) {
							cout << "LEFT" << endl;
							b[col][row] = b[col][row - 1];
							b[col][row - 1] = 0;
						}
						break;
					case 2:
						if (col + 1 != 4) {
							cout << "DOWN" << endl;
							b[col][row] = b[col + 1][row];
							b[col + 1][row] = 0;
						}
						break;
					case 3:
						if (row + 1 != 4) {
							cout << "RIGHT" << endl;
							b[col][row] = b[col][row + 1];
							b[col][row + 1] = 0;
						}
						break;
					}
				}
			}
		}
		shuffleCount++;
	}
}

bool solveBoard(int** b) {
	int solution[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

	int solveCount = 0;
	bool solved = false;
	int colPos = 3;
	int rowPos = 3;
	int moves[4] = { 0,0,0,0 };

	for (size_t col = 0; col < 4; col++)
	{
		for (size_t row = 0; row < 4; row++)
		{
			if (b[col][row] == solution[4 * col + row]) {
				solveCount++;
			}
			else if(b[col][row] == 0){
				colPos = col;
				rowPos = row;
				if (col - 1 != -1) {
					//cout << "UP" << endl;
					moves[0] = abs(b[col - 1][row] - solution[4 * (col) + row]);
				}
				else {
					moves[0] = -1;
				}

				if (row - 1 != -1) {
					//cout << "LEFT" << endl;
					moves[1] = abs(b[col][row - 1] - solution[4 * col + (row)]);
				}
				else {
					moves[1] = -1;
				}

				if (col + 1 != 4) {
					//cout << "DOWN" << endl;
					moves[2] = abs(b[col + 1][row] - solution[4 * (col) + row]);
				}
				else {
					moves[2] = -1;
				}

				if (row + 1 != 4) {
					//cout << "RIGHT" << endl;
					moves[3] = abs(b[col][row + 1] - solution[4 * col + (row)]);
				}
				else {
					moves[3] = -1;
				}
			}
		}
	}
	if (solveCount == 16) {
		solved = true;
	}
	else {
		cout << "NOT SOLVED: " << colPos << " " << rowPos << endl;
		bool stuck = false;
		for (size_t i = 0; i < 4; i++)
		{
			cout << moves[i] << endl;
		}
		bool movement = false;
		int spotToMove = 0;
		while (!movement) {
			for (size_t i = 0; i < 4; i++)
			{
				if (moves[i] == spotToMove && movement == false) {
					movement = true;
					switch (i)
					{
					case 0:
						//cout << "UP" << endl;
						b[colPos][rowPos] = b[colPos - 1][rowPos];
						b[colPos - 1][rowPos] = 0;
						break;
					case 1:
						//cout << "LEFT" << endl;
						b[colPos][rowPos] = b[colPos][rowPos - 1];
						b[colPos][rowPos - 1] = 0;
						break;
					case 2:
						//cout << "DOWN" << endl;
						b[colPos][rowPos] = b[colPos + 1][rowPos];
						b[colPos + 1][rowPos] = 0;
						break;
					case 3:
						//cout << "RIGHT" << endl;
						b[colPos][rowPos] = b[colPos][rowPos + 1];
						b[colPos][rowPos + 1] = 0;
						break;
					}
				}
			}
			spotToMove++;
		}
	}

	return solved;
}

bool recursiveSolve(int** b, int depth) {
	depth++;
	//check if solved
	//foreach possible move, move, call function again, use for loop
}

int main() {

	int **board;

	board = new int*[4];
	for (size_t i = 0; i < 4; i++)
	{
		board[i] = new int[4];
	}

	int num = 1;

	//Creates board
	for (size_t col = 0; col < 4; col++)
	{
		for (size_t row = 0; row < 4; row++)
		{
			if (num == 16) {
				num = 0;
			}
			board[col][row] = num;
			num++;
		}
	}

	cout << "Sliding Puzzle:" << endl;

	printBoard(board);

	shuffleBoard(board);

	printBoard(board);


	while (!solveBoard(board)) {
		cout << "Solving" << endl;
		printBoard(board);
	}
	cout << "Solved Board" << endl;
	
	for (size_t i = 0; i < 4; i++)
	{
		delete[] board[i];
	}

	delete[] board;

	return 0;
}