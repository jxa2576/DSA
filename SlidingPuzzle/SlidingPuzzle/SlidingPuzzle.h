#pragma once

void printBoard(int size, int** b);
void shuffleBoard(int shuffleAmount, int size, int** b);
bool solveBoard(int size, int** b, int** solvedB);
bool recursiveSolve(int size, int depth, int maxDepth, int** b, int** solvedB, bool solved);
