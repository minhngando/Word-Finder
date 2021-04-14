/*
 * assignment1.cpp
 *
 * This program reads in a text file that represents a puzzle, and outputs it. It then reads in a text file with a list of words. 
 * The program then takes that list of words and searches for the words in the puzzle file, if the word was found then the program will output the name of the word and where it was found 
 * if the word wasn't found then it outputs a statement informing the user that the word was not found in the puzzle.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

enum direction {

	LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP

};

const int MAX = 50;

struct wordGame
{
	int version;
	int numberRows;
	int numberColumns;
	char puzzle[MAX][MAX];

};

struct wordFind
{
	int row;
	int column; 
	string word;
	bool found;
	direction where;


};

// function prototypes go here

// read the puzzle from the input file and update the wordGame structure.
bool readPuzzle(wordGame &game, string inputFileName);

// display the contents of the puzzle
void displayPuzzle(wordGame &game);

// If the word is found the wordFind structure will be updated.
void findWord(wordGame &game, wordFind &theFind);


// helper functions that checks for matches in the 8 different directions
bool matchLeftRight(wordGame &game, string word, int r, int c);
bool matchRightLeft(wordGame &game, string word, int r, int c);
bool matchUp(wordGame &game, string word, int r, int c);
bool matchDown(wordGame &game, string word, int r, int c);
bool matchUpRight(wordGame &game, string word, int r, int c);
bool matchUpLeft(wordGame &game, string word, int r, int c);
bool matchDownRight(wordGame &game, string word, int r, int c);
bool matchDownLeft(wordGame &game, string word, int r, int c);


// driver function
int main()
{


	wordGame game;
	wordFind theFind;

	string puzzleFileName; 
	string wordFileName;

	cin >> puzzleFileName;

	if (readPuzzle(game, puzzleFileName)) {
		cout << "The puzzle from file \"" << puzzleFileName << "\"" << endl;
		displayPuzzle(game);

		cin >> wordFileName; 

		ifstream wordFile(wordFileName.c_str());

		if (wordFile) {
			

			while (!wordFile.eof()) {
				wordFile >> theFind.word;
				findWord(game, theFind);
				if (theFind.found == true) {
					cout << "The word " << theFind.word << " was found at (" << theFind.row << ", " << theFind.column << ") - " << theFind.where << endl;
				}
				else
				{
					cout << "The word " << theFind.word << " was not found" << endl;
				}
			}
				

			
			
		}
		else {
			cout << "The puzzle file \"" << wordFileName << "\" could not be opened or is invalid" << endl;
		}


	}
	else {

		cout << "The puzzle file \"" << puzzleFileName << "\" could not be opened or is invalid" << endl;
	}

	



	system("pause");
	return 0;
}

/*
 *  reads a text file representing a word search 
 * if the file opened successfully, returns true 
 */
bool readPuzzle(wordGame &game, string inputFileName) {

	
	bool worked;

	ifstream puzzleFile; 
	puzzleFile.open(inputFileName.c_str());

	// if the file has been opened successfully, read in the values on the first line & update the numberRows & numberColumns values in the wordGame struct
	if (puzzleFile) {


		puzzleFile >> game.numberRows >> game.numberColumns;

		// while it is not the end of the file, loop through the rows and columns and process the contents of the file into the 2d char array in the wordGame struct
		while (!puzzleFile.eof()) {
			for (int i = 0; i < game.numberRows; i++) {
				for (int j = 0; j < game.numberColumns; j++) {

					puzzleFile >> (game.puzzle[i][j]);

				}
			}


			
		}

		worked = true;
		game.version = 1;
	}
	else {

		game.version = 1;
		worked = false;

	}
		

	// close the file when done
	puzzleFile.close();
	return worked;
}

/*
 * 
 * Goes through the wordGame struct and outputs the contents of the puzzle 
 */
void displayPuzzle(wordGame &game) {

	for (int i = 0; i < game.numberRows; i++) {

		for (int j = 0; j < game.numberColumns; j++) {
			
			cout << game.puzzle[i][j];

		}

		cout << endl;
	}

}

/*
 * 
 *
 *
 */
void findWord(wordGame &game, wordFind &theFind) {


	// nested for loops that go through the entire array
	for (int i = 0; i < game.numberRows; i++) {
		for (int j = 0; j < game.numberColumns; j++) {

			// each if statement calls a helper function that tests for matches in the characters of the word in a certain direction from the (i,j) point
			// if the helper function didn't find a match, nothing happens for that (i,j) point and it moves onto the next helper function that checks for the next direction
			// if the helper function does find a match, it updates the wordFind struct and returns so that the other if statements aren't called
			if (matchLeftRight(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i+1;
				theFind.column = j+1;
				theFind.where = LEFT_RIGHT;
				return;
			}

			
			if (matchRightLeft(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = RIGHT_LEFT;
				return;
			}

			if (matchDownRight(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = RIGHT_DOWN;
				return;
			}

			if (matchDownLeft(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = LEFT_DOWN;
				return;
			}

			if (matchUp(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = UP;
				return;
			}
			if (matchDown(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = DOWN;
				return;
			}

			if (matchUpRight(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = RIGHT_UP;
				return;
			}

			if (matchUpLeft(game, theFind.word, i, j)) {
				theFind.found = true;
				theFind.row = i + 1;
				theFind.column = j + 1;
				theFind.where = LEFT_UP;
				return;
			}
			

		}
	}



}

/*
 * 
 */
bool matchLeftRight(wordGame &game, string word, int r, int c) {


	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c;


	

	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}

	// represents the movement of the direction 
	row += 0;
	col += 1;
}


/*
 *
 */
bool matchRightLeft(wordGame &game, string word, int r, int c) {
	
	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c; 

	
	

	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}
	// represents the movement of the direction 

	row += 0;
	col -= 1;
}


/*
 *
 */
bool matchUp(wordGame &game, string word, int r, int c) {
	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c; 

	

	
	

	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}
	// represents the movement of the direction 
	row -= 1; 
	col += 0;
}

/*
 *
 */
bool matchDown(wordGame &game, string word, int r, int c) {
	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c; 


	
	

	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]){
			return false;
		}
		else {
			return true;
		}
	}
	// represents the movement of the direction 
	row += 1; 
	col += 0;
}

/*
 *
 */
bool matchUpRight(wordGame &game, string word, int r, int c) {
	int wordLen = static_cast<int>(word.length());
	
	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c;

	

	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}
	// represents the movement of the direction 
	row -= 1;
	col += 1;
}

/*
 *
 */
bool matchUpLeft(wordGame &game, string word, int r, int c) {
	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c;

	
	
	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}
	// represents the movement of the direction 
	row -= 1;
	col -= 1;

}

/*
 *
 */
bool matchDownRight(wordGame &game, string word, int r, int c) {

	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c;

	

	
	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}

	// represents the movement of the direction 
		row += 1;
		col += 1;

}

/*
 *
 */
bool matchDownLeft(wordGame &game, string word, int r, int c) {
	int wordLen = static_cast<int>(word.length());

	// (r, c) is the starting point
	// initializes row and col as the starting points, they will be incremented later to represent the direction movement starting from (r,c)
	int row = r;
	int col = c;

	

	

	for (int w = 0; w < wordLen; w++) {
		if (word[w] != game.puzzle[row][col]) {
			return false;
		}
		else {
			return true;
		}
	}
	// represents the movement of the direction 
		row += 1;
		col -= 1;
}
