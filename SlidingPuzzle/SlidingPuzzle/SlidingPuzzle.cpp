#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;

void printBoard(int size, int** b) {
	cout << " " << endl;
	for (size_t col = 0; col < size; col++)
	{
		cout << "|";

		for (size_t row = 0; row < size; row++)
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
	cout << " " << endl;
}

void shuffleBoard(int shuffleAmount, int size, int** b) {
	cout << "SHUFFLE" << endl;
	int shuffleCount = 0;
	srand(time(NULL));
	while (shuffleCount < shuffleAmount) {
		for (size_t col = 0; col < size; col++)
		{
			for (size_t row = 0; row < size; row++)
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
						if (col + 1 != size) {
							cout << "DOWN" << endl;
							b[col][row] = b[col + 1][row];
							b[col + 1][row] = 0;
						}
						break;
					case 3:
						if (row + 1 != size) {
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

bool solveBoard(int size, int** b, int** solvedB) {

	int solveCount = 0;
	bool solved = false;
	int colPos = size - 1;
	int rowPos = size - 1;
	int moves[4] = { 0,0,0,0 };

	for (size_t col = 0; col < size; col++)
	{
		for (size_t row = 0; row < size; row++)
		{
			if (b[col][row] == solvedB[col][row]) {
				solveCount++;
			}
			else if(b[col][row] == 0){
				colPos = col;
				rowPos = row;
				if (col - 1 != -1) {
					//cout << "UP" << endl;
					moves[0] = abs(b[col - 1][row] - solvedB[col][row]);
					if (b[col - 1][row] == solvedB[col - 1][row]) {
						moves[0] = -1;
					}
				}
				else {
					moves[0] = -1;
				}

				if (row - 1 != -1) {
					//cout << "LEFT" << endl;
					moves[1] = abs(b[col][row - 1] - solvedB[col][row]);
					if (b[col][row - 1] == solvedB[col][row - 1]) {
						moves[1] = -1;
					}
				}
				else {
					moves[1] = -1;
				}

				if (col + 1 != size) {
					//cout << "DOWN" << endl;
					moves[2] = abs(b[col + 1][row] - solvedB[col][row]);
					if (b[col + 1][row] == solvedB[col + 1][row]) {
						moves[2] = -1;
					}
				}
				else {
					moves[2] = -1;
				}

				if (row + 1 != size) {
					//cout << "RIGHT" << endl;
					moves[3] = abs(b[col][row + 1] - solvedB[col][row]);
					if (b[col][row + 1] == solvedB[col][row + 1]) {
						moves[3] = -1;
					}
				}
				else {
					moves[3] = -1;
				}
			}
		}
	}
	if (solveCount == size * size) {
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

bool recursiveSolve(int** b) {
	//check if solved
	//foreach possible move, move, call function again, use for loop
	//1 2,4 3,5 6,8 7,13 9, 14 10, 12 11 15

	return true;
}

int main() {
	bool play = true;

	int **board;
	int **solvedBoard;

	int boardWidth = 4;
	int shuffleCount = 5;

	bool shuffle = false;

	cout << "Bourd Size?" << endl;

	cin >> boardWidth;

	board = new int*[boardWidth];
	solvedBoard = new int*[boardWidth];
	for (size_t i = 0; i < boardWidth; i++)
	{
		board[i] = new int[boardWidth];
		solvedBoard[i] = new int[boardWidth];
	}

	int num = 1;

	//Creates board
	for (size_t col = 0; col < boardWidth; col++)
	{
		for (size_t row = 0; row < boardWidth; row++)
		{
			if (num == boardWidth * boardWidth) {
				num = 0;
			}
			board[col][row] = num;
			solvedBoard[col][row] = num;
			num++;
		}
	}

	cout << "Sliding Puzzle:" << endl;

	printBoard(boardWidth, board);

	while (play) {
		cout << "print, " << "shuffle, " << "solve, " << " or exit" << endl;
		char userInput[8] = {};
		cin >> userInput;

		if (strcmp(userInput, "print") == 0) {
			printBoard(boardWidth, board);
		}

		if(strcmp(userInput, "shuffle") == 0) {
			cout << "shuffle count" << endl;
			cin >> shuffleCount;
			shuffleBoard(shuffleCount, boardWidth, board);
			printBoard(boardWidth, board);
			cout << "shuffled" << endl;
		}
		
		if (strcmp(userInput, "solve") == 0) {
			while (!solveBoard(boardWidth, board, solvedBoard)) {
				cout << "solving" << endl;
				printBoard(boardWidth, board);
			}
			cout << "solved board" << endl;
		}

		if (strcmp(userInput, "exit") == 0) {
			play = false;
		}
	}

	for (size_t i = 0; i < boardWidth; i++)
	{
		delete[] board[i];
	}

	delete[] board;

	return 0;
}