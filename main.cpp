#include <iostream>
#include <limits>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cctype>


#include "player.h"

using namespace std;

void clearScreen(){
    cout << string( 100, '\n' );
  }

void printMenu(vector<string> choices){
  cout << "\n\nPlease enter one of the options below:\n";
  int count = 1;
  for (string choice : choices){
    if (choice == "Quit" || choice == "Back"){
      cout <<"0: " << choice << "\n";
    }
    else{
      cout <<count << ": " << choice << "\n";
    count++;
    }
  }
}

int userNumberInput(){
  int userChoice;
  bool inputCheck = false;
  do{
    cin.clear();
    if (cin >> userChoice){
      inputCheck = true;
      break;
    }
    else{
      cout <<"\nPlease enter a valid digit:\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }while(!inputCheck);
  return userChoice;
}

int collectX(Player currentPlayer){
  bool inputCheck = false;
  int userChoice;
  do{
    cout << "\nPlease enter your X coordinates (1,2,3...): ";

    userChoice = userNumberInput();

    if(userChoice >= 1 && userChoice <= currentPlayer.getX()){
      inputCheck=true;
    }
    else{
      cout << "\nPlease enter a valid coordinate:";
    }
  }while (!inputCheck);
  return userChoice;
}

bool isLetters(string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]); //converting the character to upper case
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //if character is not A-Z
		{
			return false;
		}
	}
	return true; //Return true if characters within A-Z
}

string uppercaseConvert(string toConvert){
  string converted = toConvert;
  transform(converted.begin(), converted.end(), converted.begin(),[](unsigned char c){ return toupper(c);});
  return converted;
}


string collectY(Player currentPlayer){
  bool inputCheck = false;
  string userChoice;
  do{
    cout << "\nPlease enter your Y coordinates (A,B,C...): ";

    cin.ignore();
    getline(cin,userChoice);

    if(isLetters(userChoice)){
      inputCheck=true;
    }
    else{
      cout << "\nPlease enter a valid coordinate:";
    }
  }while (!inputCheck);
  return uppercaseConvert(userChoice);
}

string collectOr(Player currentPlayer){
  bool inputCheck = false;
  string userChoice;
  do{
    cout << "\nPlease enter your Orientation Horizontal/Vertical (H / V): ";

    getline(cin,userChoice);
    cout <<userChoice;
    userChoice = uppercaseConvert(userChoice);

    if(isLetters(userChoice) && (userChoice == "H" || userChoice == "V")){
      
      inputCheck=true;
    }
    else{
      cout << "\nPlease enter a valid orientation:";
    }
  }while (!inputCheck);
  return userChoice;
}

void placeShip(string shipName, Player currentPlayer){
  int playerX = collectX(currentPlayer);
  string playerY = collectY(currentPlayer);
  string playerOr = collectOr(currentPlayer);
  currentPlayer.placeShip(playerX, playerY, shipName, playerOr);
}


void placeShipsMenu(Player currentPlayer){
  string menuChoices[] = {"Place Carrier","Place Battleship", "Place Destroyer", "Place Submarine", "Place Patrol Boat", "Back"};
  int userChoice;

  do{
    cout << "\n\nPlace Ships\n\n";
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);

    userChoice = userNumberInput();
    
    switch(userChoice) {
			case 1: 
        
        placeShip("carrier", currentPlayer);
        break;
      case 2: 
        
        //setupGame();
        break;
      case 3: 
        
        //setupGame();
        break;
      case 4: 
        
        break;
			case 0: 
        cout << "Exiting";
        break;
			default:
			cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
			break;
    }
  }while (userChoice != 0);

}


bool setupGame(){
  Player userPlayer;
  userPlayer.createBoard(10, 10);
  
  bool continuePlay = false;
  int userChoice;
  string menuChoices[] = {"Place ship myself","Auto-place", "Continue", "Reset", "Quit"};
  do{
    
    cout << "\n\nGame Set-up\n\n";
    userPlayer.printBoard();
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);
    
    userChoice = userNumberInput();
    
    switch(userChoice) {
			case 1: 
        placeShipsMenu(userPlayer);
        break;
      case 2: 
        cout << "\nAuto-place\n";
        //setupGame();
        break;
      case 3: 
        cout << "\nContinue\n";
        continuePlay = true;
        userChoice = 0;
        break;
      case 4: 
        cout << "\nReset\n";
        userPlayer.resetBoard();
        break;
			case 0: 
        cout << "Exiting";
        break;
			default:
			cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
			break;
    }
  }while (userChoice != 0);
  return continuePlay;
}

void playGame(){
  cout << "PLAY GAME";

}

void mainMenu(){
  int userChoice;
  string menuChoices[] = {"One player vs Computer","Quit"};
  do{
    cout << "\n\nWelcome to the AdaShips\n";
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);

    userChoice = userNumberInput();
    
    switch(userChoice) {
			case 1: 
        clearScreen();
        if(setupGame()){
          playGame();
        }
        break;
			case 0: 
        cout << "Exiting";
        break;
			default:
			cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
			break;
    }
  }while (userChoice != 0);
}

int main() {
  mainMenu();
}