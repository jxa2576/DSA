//Jeb Atkinson
//Sliding Puzzle Homework
//DSA2
//For viewing purposes the blank space is represented by a zero

#include <iostream>
#include <time.h>
#include <cmath>

#include "SlidingPuzzle.h"

using namespace std;


int main() {
	//Bool for game loop;
	bool play = true;

	//2D array for play board and a solved board;
	int **board;
	int **solvedBoard;

	int boardWidth = 4;
	int shuffleCount = 5;

	bool shuffle = false;

	cout << "Bourd Size?" << endl;

	cin >> boardWidth;

	//set up 2d arrays
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

	//Game loop
	while (play) {
		cout << "print, " << "shuffle, " << "solve, " << "solver, "<< " or exit" << endl;
		char userInput[8] = {};
		cin >> userInput;

		if (strcmp(userInput, "print") == 0) {
			printBoard(boardWidth, board);
		}

		if (strcmp(userInput, "shuffle") == 0) {
			cout << "how many shuffles?" << endl;
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

		if (strcmp(userInput, "solver") == 0) {
			cout << "recursive solver" << endl;
			bool solved = false;

			int depth = 0;

			solved = recursiveSolve(boardWidth, depth, shuffleCount, board, solvedBoard, solved);
			printBoard(boardWidth, board);

			if (solved == true) {
				printBoard(boardWidth, board);
				cout << "recursive solve" << endl;
			}
		}

		if (strcmp(userInput, "exit") == 0) {
			play = false;
		}
	}

	for (size_t i = 0; i < boardWidth; i++)
	{
		delete[] board[i];
		delete[] solvedBoard[i];
	}

	delete[] board;
	delete[] solvedBoard;

	return 0;
}

//Prints board using a for loop to go through its vertices
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

//Shuffles the board, tracks the empty space, randomly picks a direction, moves it if it can
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
							//Moves the piece and blank spot to each others position
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

// Hill CLimb, BFS, 
// Solves the board by tracking the blank spot, taking the number that should be there and subtracting it from the possible moves around it, selecting the piece that is the lowest cost
// or closest to its "home." Doesnt work great, easily caught in loops
bool solveBoard(int size, int** b, int** solvedB) 
{
	int solveCount = 0;
	bool solved = false;
	int colPos = size - 1;
	int rowPos = size - 1;
	//Stores the cost of moves
	int moves[4] = { 0,0,0,0 };

	//Finds if the board is solved and sets up movement for the blank space
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
		//Picks the next place to move to and moves it
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

//DFS, quadtree, uses recursion to test out every possible move for the blank space given the amount of shuffles
bool recursiveSolve(int size, int depth, int maxDepth, int** b, int** solvedB, bool solved) 
{
	int solveCount = 0;
	int colPos = size - 1;
	int rowPos = size - 1;

	printBoard(size, b);

	//Checks for solved state and sets the cordinates of the blank space
	for (size_t col = 0; col < size; col++)
	{
		for (size_t row = 0; row < size; row++)
		{
			if (b[col][row] == solvedB[col][row])
			{
				solveCount++;
			}
			
			if (b[col][row] == 0)
			{
				colPos = col;
				rowPos = row;
			}
		}
	}

	//if solved skip over new recursive calls 
	if (solveCount == size * size) {
		solved = true;
	}
	else {
		solveCount = 0;
	}


	if (solved == true) {

	}
	else 
	{
		//For loop represents the potential moves the blank space could make
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t col = 0; col < size; col++)
			{
				for (size_t row = 0; row < size; row++)
				{
					if (b[col][row] == solvedB[col][row])
					{
						solveCount++;
					}

					if (b[col][row] == 0)
					{
						colPos = col;
						rowPos = row;
					}
				}
			}

			if (solveCount == size * size) {
				solved = true;
			}
			else {
				solveCount = 0;
			}

			if (solved == true || depth > maxDepth)
			{

			}
			else 
			{
				//Moves the blank space
				switch (i)
				{
				case 0:
					if (colPos - 1 != -1) 
					{
						//cout << "UP" << endl;
						b[colPos][rowPos] = b[colPos - 1][rowPos];
						b[colPos - 1][rowPos] = 0;
					}
					break;
				case 1:
					if (rowPos - 1 != -1) 
					{
						//cout << "LEFT" << endl;
						b[colPos][rowPos] = b[colPos][rowPos - 1];
						b[colPos][rowPos - 1] = 0;
					}
					break;
				case 2:
					if (colPos + 1 != size) 
					{
						//cout << "DOWN" << endl;
						b[colPos][rowPos] = b[colPos + 1][rowPos];
						b[colPos + 1][rowPos] = 0;
					}
					break;
				case 3:
					if (rowPos - 1 != -1) 
					{
						//cout << "RIGHT" << endl;
						b[colPos][rowPos] = b[colPos][rowPos + 1];
						b[colPos][rowPos + 1] = 0;
					}
					break;
				}
				depth++;
				//Goes to next move
				solved = recursiveSolve(size, depth, maxDepth, b, solvedB, solved);
				if (solved == true) 
				{

				}
				else 
				{
					//Undoes last move if not solved
					switch (i)
					{
					case 0:
						if (colPos - 1 != -1)
						{
							//cout << "UP" << endl;
							b[colPos - 1][rowPos] = b[colPos][rowPos];
							b[colPos][rowPos] = 0;
						}
						break;
					case 1:
						if (rowPos - 1 != -1)
						{
							//cout << "LEFT" << endl;
							b[colPos][rowPos - 1] = b[colPos][rowPos];
							b[colPos][rowPos] = 0;
						}
						break;
					case 2:
						if (colPos + 1 != size)
						{
							//cout << "DOWN" << endl;
							b[colPos + 1][rowPos] = b[colPos][rowPos];
							b[colPos][rowPos] = 0;
						}
						break;
					case 3:
						if (rowPos - 1 != -1)
						{
							//cout << "RIGHT" << endl;
							b[colPos][rowPos + 1] = b[colPos][rowPos];
							b[colPos][rowPos] = 0;
						}
						break;
					}
					depth--;
				}
			}
		}
	}
	return solved;
}