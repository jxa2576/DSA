#include <iostream>

using namespace std;

void printBoard(int** b) {
	cout << "Sliding Puzzle:" << endl;
	cout << "--------------" << endl;
	for (size_t col = 0; col < 4; col++)
	{
		cout << "|";

		for (size_t row = 0; row < 4; row++)
		{
			if (b[col][row] != 0) {
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
	while (shuffleCount < 5) {
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

	printBoard(board);

	shuffleBoard(board);

	printBoard(board);

	cin.get();

	delete[] board;

	return 0;
}