//Chad Huntebrinker
//crh92d@umsystem.edu
//CS 201R


#include <iostream>
#include <vector>

using namespace std;

bool CalculatePath(const int numTurns, const int tokenGoal, int currTokens, int turnNumber,
					vector<char> &Vector);
void UserChoice(const int numTurns, const int tokenGoal, int currTokens, int turnNumber, 
				vector<char> Vector);

int main() {
	int numberOfTurns, tokenGoal, turnNumber = 0, currentTokens = 13;
	vector<char> orderOperations(150);
	char userInput;
	bool possible = true;

	cout << "Enter the number of tokens you wish to reach" << endl;
	cin >> tokenGoal;
	cout << endl;
	cout << "Enter the number of turns you will have to reach your goal number of tokens" << endl;
	cin >> numberOfTurns;
	cout << endl;

	cout << "Would you like to do a search of a possible path to the desired number of tokens?";
	cout << " If yes, enter y.  If no, enter n." << endl;
	cin >> userInput;

	//This if statement executes if the user enters y and stores the result (true/false)
	//in the variable possible.
	if (userInput == 'y') {
		possible = CalculatePath(numberOfTurns, tokenGoal, currentTokens, turnNumber, orderOperations);
	}

	if (possible == false) {
		cout << "Not possible" << endl;
	}

	//If it is possible to reach that number, the vector will print out the ultimate
	//plan to reach the number of tokens.
	else {
		for (int i = 0; i < orderOperations.size(); ++i) {
			cout << orderOperations.at(i) << " ";
		}
		cout << endl << endl;
	}
	//This if statement will execute if it is possible to reach that number of tokens or
	//if the user didn't want to see the program can reach the number.
	//In other words, if the user entered anything other than 'y' on line 31, it will run.
	//The program will let the user try, but will not output any advice because the function didn't run.
	if (possible != false) {
		cout << "Current Tokens , Token Goal , Turn Number , Total Turns" << endl;

		UserChoice(numberOfTurns, tokenGoal, currentTokens, turnNumber, orderOperations);
	}
	//If it is not possible, then the user will not be able to try and the program is done.
	//The user WILL be able to put his/her input in if he/she did not want to see if 
	//the program can reach the number (in other words, if the user entered anything
	//other than 'y' on line 31).  Then the program will let the user try, but will
	//not output any advice because the function didn't run.
	else {
		cout << "It is not possible to get to that number in that amount of turns" << endl;
	}

	return 0;
}
/*
This function calculates if it is possible for the user to get to the amount of tokens specified.
The function will always try to add 25 first, all the way to the max number of turns allowed. If that  
is not the number, it will undo the previous action of adding 25 by -25 from the current tokens 
and -1 turn from the current turn.  It will then see if the number can be divided by 2.  If it can, it
will try that and if it can not, it will go back another turn.  This continues until either the current
number of tokens is found or if the max number of turns have been used and the current number of
tokens != the token goal.  Throughout this process, a vector will continue to mark the progress of the 
program with a '+' or a '/'.  If the function needs to back up a step, the vector will replace the
original mark of '+' or '/' with a ' ' so that it won't confuse the user. If at any point
the function has the current tokens = token goal, then it will return true and there will be no need
for the function to continue trying new operations.
*/
bool CalculatePath(const int numTurns, const int tokenGoal, int currTokens, int turnNumber,
					vector<char> &Vector) {
	bool possible;
	if (currTokens == tokenGoal) {
		return true;
	}
	else {
		if (turnNumber != numTurns) {
			currTokens = currTokens + 25;
			Vector.at(turnNumber) = '+';
			++turnNumber;
			possible = CalculatePath(numTurns, tokenGoal, currTokens, turnNumber, Vector);
			if (possible == false) {
				currTokens = currTokens - 25;
				Vector.at(turnNumber - 1) = ' ';
				--turnNumber;
			}
			else {
				return true;
			}
			if (currTokens % 2 == 0) {
				currTokens = currTokens / 2;
				Vector.at(turnNumber) = ('/');
				++turnNumber;
				possible = CalculatePath(numTurns, tokenGoal, currTokens, turnNumber, Vector);
				if (possible == false) {
					currTokens = currTokens * 2;
					Vector.at(turnNumber - 1) = ' ';
					--turnNumber;
				}
				else {
					return true;
				}
			}
			return false;
		}
		else if(numTurns == turnNumber) {
			return false;
		}
	}
}
/*
This function takes in the user's input.  It will always have the vector show what the
user needs to do to get to that number each turn if the user entered 'y' on line 31 and it was
possible to reach that number. Once the user reaches the goal, the program will
stop and if the user hasn't reached the amount of tokens, then it will run the function again if
the max turns have not been reached.
*/
void UserChoice(const int numTurns, const int tokenGoal, int currTokens, int turnNumber, 
				vector<char> Vector) {
	char userInput;
	//"Current Tokens , Token Goal , Turn Number , Total Turns"
	cout << currTokens << " , " << tokenGoal << " , " << turnNumber << " , " << numTurns << endl << endl;
	cout << "Suggested move: (" << Vector.at(turnNumber) << ")" << endl;
	if (tokenGoal == currTokens) {
		cout << currTokens << " , " << tokenGoal << " , " << turnNumber << " , " << numTurns << endl;
		cout << "Congratulations! You won!" << endl;
	}
	else {

		//This is only used to see if the user entered 13 as their number
		if (currTokens % 2 != 0 && turnNumber == 0) {
			cout << "Enter (+) to add 25 to the tokens";
			cin >> userInput;
			cout << endl;
			currTokens = currTokens + 25;
		}
		else {
			cout << "Enter (+) to add 25 to the tokens or (/) to divide the current tokens by 2";
			cin >> userInput;
			cout << endl;
			if (userInput == '+') {
				currTokens = currTokens + 25;
			}
			else if (userInput == '/') {
				currTokens = currTokens / 2;
			}
		}
		++turnNumber;
	}
	
	if (tokenGoal == currTokens  && turnNumber > 0) {
		cout << currTokens << " , " << tokenGoal << " , " << turnNumber << " , " << numTurns << endl;
		cout << "Congratulations! You won!" << endl;
	}
	else if(tokenGoal != currTokens && turnNumber != numTurns) {
		UserChoice(numTurns, tokenGoal, currTokens, turnNumber, Vector);
	}
	else {
		cout << "Game Over!" << endl;
	}
}
