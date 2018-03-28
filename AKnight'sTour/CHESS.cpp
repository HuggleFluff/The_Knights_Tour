/*Ashley Faul
The Knight's Tour
Tom Rishel
csc 102
08 / 17 / 17
This is a program that will use fuctions and arrays to
create a chess board and a knight's peice.  The kight will
attempt to visit every square on the board once and only once.
The board will be displayed with the number of moves with each attempted run.
This assignmet is created to better familiarize ourselves with
arrays and functions.
PART 2, same thing but using an acessability heuristic
9 / 12 / 17 */

#include <iostream>
#include <iomanip>
using namespace std;

//functions!!
void displayBoard(int[][8]);
void startHere(int& row, int& column);
void isLegal(const int currentRow, const int currentColumn, const int vertical[], const int horizontal[], const int chessBoard[][8], bool legalMoves[]);
int move1(const bool legal[], const int currentRow, const int currentColumn, const int vertical[], const int horizontal[], const int access[][8]);
void Acess(const int firstBest, const bool legal[], const int currentRow, const int currentColumn, const int vert[], const int horiz[], int access[][8]);

int main()
{
	int Chessboard[8][8];
	const int horizontal[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	const int vertical[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };
	bool legalMoves[8] = { false };                  //boolean for legal moves
	int startRow = 0;		//starting Row
	int startCol = 0;     //starting column                    
	int currentRow, currentColumn;                             //current position of the knight
	int Move;                                         //stores first legal move
	int counter;                                         // le' counter     
	int finalCounter;

	for (int a = 1; a <= 64; a++)
	{
		int accessability[8][8] = { { 2, 3, 4, 4, 4, 4, 3, 2 },          //Acessability Heuristic        
		{ 3, 4, 6, 6, 6, 6, 4, 3 },
		{ 4, 6, 8, 8, 8, 8, 6, 4 },
		{ 4, 6, 8, 8, 8, 8, 6, 4 },
		{ 4, 6, 8, 8, 8, 8, 6, 4 },
		{ 4, 6, 8, 8, 8, 8, 6, 4 },
		{ 3, 4, 6, 6, 6, 6, 4, 3 },
		{ 2, 3, 4, 4, 4, 4, 3, 2 } };

		//set starting point
		currentRow = startRow;
		currentColumn = startCol;


		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Chessboard[i][j] = 0;
			}
		}

		Chessboard[currentRow][currentColumn] = 1;


		for (counter = 2; counter <= 64; counter++) //Counter was set to 2 because setting it to 1 caused the number 1 to appear multiple times.
		{

			isLegal(currentRow, currentColumn, vertical, horizontal, Chessboard, legalMoves); //Function call for islegal


			Move = move1(legalMoves, currentRow, currentColumn, vertical, horizontal, accessability); //Function call for Move

			//If no legal move can be made, the loop is broken
			if (Move == -1)
			{
				break;
			}


			Acess(Move, legalMoves, currentRow, currentColumn, vertical, horizontal, accessability); //Function call for acess

			//Move Knight
			currentRow += vertical[Move];
			currentColumn += horizontal[Move];
			Chessboard[currentRow][currentColumn] = counter;

		}

		if (counter == 65)
		{
			cout << endl << "TOUR COMPLETED!!" << endl;

		}



		displayBoard(Chessboard); //Displays the board



		startHere(startRow, startCol);

	}

	system("Pause");

	return 0;
}







//determine which of eight moves are legal
void isLegal(const int currentRow, const int currentColumn, const int vertical[], const int horizontal[], const int chessBoard[][8], bool legalMoves[])
{
	int moveNum = 0;
	while (moveNum < 8)
	{
		int tempRow = currentRow + vertical[moveNum];
		int tempColumn = currentColumn + horizontal[moveNum];

		if (tempRow >= 0 && tempRow <= 7 && tempColumn >= 0 && tempColumn <= 7)
		{
			if (chessBoard[tempRow][tempColumn] == 0)        //if there is a space with a zero and it is not out of bounds                      
			{
				legalMoves[moveNum] = true;                             //legal move = true   
			}
			else
			{
				legalMoves[moveNum] = false;                     //otherwise, there is no legal move        
			}
		}
		else
		{
			legalMoves[moveNum] = false;
		}
		++moveNum;
	}
}

//Find lowest accessibility heuristic
int move1(const bool legal[], const int currentRow, const int currentColumn, const int vertical[], const int horizontal[], const int access[][8])
{
	int VarAccess = 8;                                             //stores heuristic
	int move1 = -1;
	for (int moveNum = 0; moveNum < 8; moveNum++)         //for loop, goes through all moves
	{
		if (legal[moveNum] == false)                             //If move is illegal, skip further commands. 
		{
			continue;
		}
		int tempRow = currentRow + vertical[moveNum];                        //stores temp values 
		int tempColumn = currentColumn + horizontal[moveNum];

		if (access[tempRow][tempColumn] < VarAccess)
		{
			VarAccess = access[tempRow][tempColumn];
			move1 = moveNum;                              //Store first legal move with lowest accessibility
		}
	} //end for loop

	return move1;
}


void Acess(const int firstBest, const bool legal[], const int currentRow, const int currentColumn, const int vert[], const int horiz[], int acess[][8])
{
	for (int moveNumber = firstBest + 1; moveNumber < 8; moveNumber++)
	{
		if (legal[moveNumber] == false)                            //If move is illegal, skip further commands.
		{
			continue;
		}

		int tempRow = currentRow + vert[moveNumber];                       //stores temp values
		int tempColumn = currentColumn + horiz[moveNumber];

		--acess[tempRow][tempColumn];                                    //Decrement accessibility heuristic.

	}

}

//(heuristics confused me for so long ;-;)

void startHere(int& row, int& column) //increment starts here
{
	++column;
	if (column >= 8)
	{
		column = 0;
		++row;
	}
}


void displayBoard(int a[][8]) //function to display the chessboard
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			cout << setw(3) << a[i][j] << "  ";
		}
		cout << endl << endl;



	}

	cout << "\n" << endl;
}

//End program comments
/*This program took a lot of hard work, a lot of late nights, tutoring sessions, study groups
and coffee, lots and lots of coffee.  I am very grateful that we have a tutoring hall that
offers computer science help.  I was not the only one there for this program, but reaching out
and working with people has really helped.  Tenela taught me the great trick of
using a whiteboard to write down pseudocode, it was a big help.  There was so much reading and
learning and groupwork involved with this.  Truely the most frustrating program I have ever had to deal with. But
I am sure there will be more challenges to come*/