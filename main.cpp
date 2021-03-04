#include <iostream>
#include <limits>
#include <vector>
#include <assert.h>
#include "player.h"

using namespace std;

void clearScreen(){
    cout << string( 100, '\n' );
  }

void printMenu(vector<string> choices){
  cout << "\n\nPlease enter one of the options below:\n";
  int count = 1;
  for (string choice : choices){
    if (choice == "Quit"){
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
    cin >> userChoice;
    if (isdigit(userChoice)){
      inputCheck = true;
    }
    else{
      cout <<"\nPlease enter a valid digit:\n";
    }
  }while(!inputCheck);
  return userChoice;
}

int collectX(Player currentPlayer){
  bool inputCheck = false;
  int userChoice;
  do{
    cout << "\nPlease enter your X coordinates (1,2,3...): ";
    cin.clear();
    cin >> userChoice;
    if(userChoice >= 1 && userChoice <= currentPlayer.getX()){
      inputCheck=true;
    }
    else{
      cout << "\nPlease enter a valid coordinate:";
    }
  }while (!inputCheck);
  return userChoice;
}

void userCoords(Player currentPlayer){
  collectX(currentPlayer);
}

void placeShip(int length){
  
}


void placeShipsMenu(Player currentPlayer){
  string menuChoices[] = {"Place Carrier","Place Battleship", "Place Destroyer", "Place Submarine", "Place Patrol Boat", "Quit"};
  int userChoice;

  do{
    cout << "\n\nPlace Ships\n\n";
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);
    
    cin.clear();
    cin >> userChoice;
    
    switch(userChoice) {
			case 1: 
        
        //setupGame();
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
    clearScreen();
    cout << "\n\nGame Set-up\n\n";
    userPlayer.printBoard();
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);
    
    cin.clear();
    cin >> userChoice;
    
    switch(userChoice) {
			case 1: 
        cout << "\nPlace Ships\n";
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

    cin.clear();
    cin >> userChoice;
    
    switch(userChoice) {
			case 1: 
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