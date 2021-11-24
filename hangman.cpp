#include <iostream> //standard library for i/o
#include <string> //always include this when you use the string class
#include <fstream> //file input/ output
#include <cstdlib> //for exit()
using namespace std;

const int numGuesses = 6; //six guesses (head, body, arm1, arm2, leg1, leg2

class hangmanGame
{
public:
	string solution; //solution word
	string userGuess; //if the user guesses a correct letter, they can guess the word
	char hintWord[20] = ""; //hint word made of *
	char lettersGuessed[20] = ""; //letters guessed so far (right or wrong)
	int letterCount = 0; //number of letters guessed so far (right or wrong)
	int incorrectCount = 0; //number of incorrect letters guessed so far
	char currentLetter = ' '; //current letter guess
	int wordLength = 0; //length of the solution word
	bool correctLetter = false; //flag to set if the letter is in the word
	bool win = false; //flag to set if all the user won that round
};

void HangmanRules(const string& name);
//Precondition: name is defined
//Postcondition: The rules of hangman is displayed to the screen
//Description: provides instructions to the user on how to play the game

void SetUpOneRound(hangmanGame& activeGame, ifstream&);
//Precondition:activeGame class and ifstream is initialized
//Postcondition: activeGame class is defined and the file is open to be read
//Description:  Get the word from the file and reset all member variables

void CreateHintWord(hangmanGame& activeGame);
//Precondition:activeGame is initialized
//Postcondition: wordLengt and hintWord is defined
//Description:  creates the array of *

void PlayHangman(const string&, hangmanGame& activeGame);
//Precondition: name and activeGame is initialized
//Postcondition: Played a round of hangman
//Description:  Play one round of the hangman game

void GetLetterGuess(hangmanGame& activeGame);
//Precondition: activeGame is initialized
//Postcondition: hintword and letterGuessed is displayed to the screen
//Description:  Displays hint array and letters guessed asks and gets a current letter guess from
//the user and adds it to the letters guessed array

bool InterpretLetterGuess(hangmanGame& activeGame);
//Precondition: activeGame is initalized
//Postcondition: Results in true or false if the word guessed is in the solution or not
//Description:  Check if the letter guessed is in the solution and if it is, replace all * with that
//letter in the hintWord and return true, otherwise return false

void CorrectGuess(hangmanGame& activeGame, string name);
//Precondition: activeGame and name are defined
//Postcondition: Checks if the word was guessed correctly
//Description:  checks for the final correct letter and if it is not the final correct letter
//ask and get a word guess from the user if the user wants to guess the word

bool GameOver(const hangmanGame& activeGame);
//Precondition: activeGame is defined
//Postcondition: True or False if the guess matches the solution
//Description:  This function will return true if the hintWord matches the solution, you can use ==
//or if the userGuess matches the solution, you can use ==

void WonOrLostDisplay(const hangmanGame& activeGame, string name);
//Precondition: activeGame and name are defined
//Postcondition: Displays if the user won or not
//Description: Lets the user know if they won or lost the round

void DrawHangman(hangmanGame& activeGame);
//Precondition:activeGame is defined
//Postcondition: Displays the hangman and number of incorrect guesses
//Description:  Draw or describe the hangman drawing

int main()
{
	//declare variables
	string name;
	char response;
	ifstream in;
	hangmanGame activeGame;

	//connect to the input file
	in.open("inputWords.txt");

	//if file did not open correctly
	if(in.fail()){
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}

	//ask and get the users name
	cout << "Enter your first name: ";
	cin >> name;

	//Hangman rules
  HangmanRules(name);

	cout << "Do you want to play the hangman game? (y or n): ";
	cin >> response;

	//loop to continue to play another round
	while(response == 'Y' || response == 'y')
	{
		//set up the hangman round
		SetUpOneRound(activeGame, in);

		//play one round of hangman
		PlayHangman(name, activeGame);

		//again?
		cout << "Do you want to play the hangman game? (y or n): ";
		cin >> response;
	}

	return  0;
}

void HangmanRules(const string& name)
//Description:  provides instructions to the user on how to play the game
{
	cout << "\n\t\t\t" << name << ", WELCOME TO HANGMAN!\n\n";
	cout << "\tPlease read the following instructions before you play.\n\n";
  cout << "\t-You will be presented with a word to be guessed\n";
  cout << "\t-Guess letters one at a time\n";
  cout << "\t-You can have up to six incorrect letter guesses\n";
  cout << "\t-You can only guess the word when you have made a correct letter guess\n";
  cout << "\t-The game will be OVER when you have guessed the word correctly\n";
  cout << "\t\tOr when you have guessed letters incorrectly SIX times.\n\n\tHAVE FUN!\n\n";
}

void SetUpOneRound(hangmanGame& activeGame, ifstream& in)
//Description:  Get the word from the file and reset all member variables
{
	activeGame.solution = ""; //clear the solution word
	activeGame.userGuess = ""; //clear userGuess string
	activeGame.hintWord[0] = '\0'; //clear the star array
	activeGame.lettersGuessed[0] = '\0'; //clear the lettersGuessed array
	activeGame.letterCount = 0; //letter count starts back at 0
	activeGame.incorrectCount = 0;//reset the incorrectCount
	activeGame.correctLetter = false; //reset correctLetter to false
	activeGame.win = false;//reset win to false

	//get a word form the file
	in >> activeGame.solution;

	//create the hint word
	CreateHintWord(activeGame);
}

void CreateHintWord(hangmanGame& activeGame)
//Description: creates the array of *
{
	//get the length of the word
  activeGame.wordLength = activeGame.solution.length();

	//let the user know how many letters are in the word
	cout << "\nWord has " << activeGame.wordLength << " letters\n";
	cout << "-----------------------------------------\n";

	//use a loop to create the array of *
	for(int i = 0; i < activeGame.wordLength; i++){
		activeGame.hintWord[i] = '*';
	}

	//add the null ('\0') character
	activeGame.hintWord[activeGame.wordLength] = '\0';

}

void PlayHangman(const string& name, hangmanGame& activeGame)
//Description:  Play one round of the hangman game
{

	while((activeGame.incorrectCount < numGuesses) && (activeGame.win == false))
	{
		//GetLetterGuess
		GetLetterGuess(activeGame);

		if (InterpretLetterGuess(activeGame))//If letter is in solution
		{
			//the user guessed a correct letter
			cout << "\nThe letter was in the word!\n";
			CorrectGuess(activeGame, name);
		}
		else //If letter is not in solution
		{
			//the user did not guess a correct letter
			cout << "\n" << name << ", your letter was not in the word\nYou have added a body part!\n";
			activeGame.incorrectCount++;
		}
		//Draw(tell the user how many incorrect guesses so far)
		if(activeGame.win != true)
			DrawHangman(activeGame);
	}

	//WonOrLostDisplay - lets the user know if they won or lost
	WonOrLostDisplay(activeGame, name);
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;

}

void GetLetterGuess(hangmanGame& activeGame)
//Description:  Displays hint array and letters guessed asks and gets a current letter guess from
//the user and adds it to the letters guessed array
{
	//display the hint array
	cout << "Here is the word so far\n\n\t";
	cout << activeGame.hintWord;
	cout << "\n----------------------------------------- \n";

	//display the letters that have been guessed so far
	cout << "Here are the letters guessed so far\n\n\t";
	cout << activeGame.lettersGuessed << endl;

	//ask and get a letter guess from the user
	cout << "\nEnter a letter: ";
	cin >> activeGame.currentLetter;

	//Add the letter guessed to the letters array
	activeGame.lettersGuessed[activeGame.letterCount] = activeGame.currentLetter;

	//update the letterCount
	activeGame.letterCount++;

	//add the '\0' character
	activeGame.lettersGuessed[activeGame.letterCount] = '\0';
}

bool InterpretLetterGuess(hangmanGame& activeGame)
//Description:  Check if the letter guessed is in the solution and if it is, replace all * with that
//letter in the hintWord and return true, otherwise return false
{
	bool rv = false;

	//uses a loop to search the solution word
	//if the letter is found replace the letters in the starword and set the rv to true
	for(int i = 0; i < activeGame.wordLength; i++){
		if(activeGame.solution[i] == activeGame.currentLetter){
			activeGame.hintWord[i] = activeGame.currentLetter;
			rv = true;
		}
	}

	return rv;

}

void CorrectGuess(hangmanGame& activeGame, string name)
//Description: checks for the final correct letter and if it is not the final correct letter
//ask and get a word guess from the user if the user wants to guess the word
{
	char guess;
	cout << "-----------------------------------------\n";

	//display the starword
	cout << activeGame.hintWord << endl;

	if (GameOver(activeGame)) //the correct letter completed the starword
	{
		activeGame.win = true;//they won the round by entering all the letters
	}
	else //the user entered a correct letter but it was not the final correct letter
	{
		//ask and get a response (y or n) if they want to guess the word
		cout << "\nIT WILL NOT COUNT AGAINST YOU IF YOU DO NOT GET THE CORRECT WORD!\n";

		//the user can now guess the word (if they want)
		cout << name << ", would you like to guess the FULL word (y or n)? ";
		cin >> guess;

		if (guess == 'y')
		{
			//prompt for the word
			cout << "\nWhat is the word: ";
			//get the word from the user
			cin >> activeGame.userGuess;
			//see if the game is over
			if (GameOver(activeGame)) //the correct letter completed the starword
			{
				activeGame.win = true; //they won the round by entering all the letters
			}
			else{
				cout << "\nTHAT WAS NOT THE CORRECT WORD!\n";
			}
		}
	}

}

bool GameOver(const hangmanGame& activeGame)
//Description:  This function will return true if the hintWord matches the solution
{
	return activeGame.solution == activeGame.hintWord || activeGame.userGuess == activeGame.solution;
}

void WonOrLostDisplay(const hangmanGame& activeGame, string name)
//Description: Lets the user know if they won or lost the round
{
	if (activeGame.win)
	{
		//tell the user they won that round
		cout << "\n" << name << ", you have solved the word without being hung!\nYOU WIN!\n";
	}
	else
	{
		//tell the user they did not win that round
		cout << "Sorry " << name << " you did not win that round!\n";

		//display the solution word
		cout << "\nThe word was " << activeGame.solution << endl;
	}
}

void DrawHangman(hangmanGame& activeGame)
//Description:  Draw or describe the hangman drawing
{
	cout << "\n------------------------------------------------------";
	cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
	cout << "\n------------------------------------------------------";

	if (activeGame.incorrectCount == 0)
	{
		cout << "\nYou have no incorrect guesses yet! O-|--<";
	}
	else if (activeGame.incorrectCount == 1)
	{
		cout << "\nHEAD\n - 1 of 6 incorrect guesses!";
	}
	else if (activeGame.incorrectCount == 2)
	{
		cout << "\nHEAD\nBODY\n - 2 of 6 incorrect guesses!";
	}
	else if (activeGame.incorrectCount == 3)
	{
		cout << "\nHEAD\nBODY\nARM 1\n - 3 of 6 incorrect guesses!";
	}
	else if (activeGame.incorrectCount == 4)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\n - 4 of 6 incorrect guesses!";
	}
	else if (activeGame.incorrectCount == 5)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\nLEG 1\n - 5 of 6 incorrect guesses!";
	}
	else if (activeGame.incorrectCount == 6)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\nLEG 1\n LEG 2\n - 6 of 6 incorrect guesses!\nGAME OVER\n";
	}
}
