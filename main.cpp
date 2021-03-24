/*
This is a main class.

This class is where the user starts off. In this is the bulk of the setting up menus, and feeds down into the Player class for easy setup from one class. From here, once fully set up, you will continue to the game class. In this class I also read the config file, allowing for configured games.
*/

#include <iostream>
#include <limits>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cctype>
#include <random>

#include "ini.h"
#include "helper.h"
#include "player.h"
#include "game.h"

using namespace std;

Helper helper;

vector<Player> playerList;
vector<string> shipsAvalible;
int uniquePlayer1Id;
int uniquePlayer2Id;

// This is getting the generic file for other methods to use and get data from. This is using a .ini file library
mINI::INIStructure GetSettingsFile(){
  mINI::INIFile file("adaship_config.ini"); // create a file instance
  mINI::INIStructure ini;// create a data structure
  file.read(ini);// now we can read the file
  return ini;
}

// Using the settings file, I can pull the ship length from the .ini file
int getShipLength(string shipName){
  mINI::INIStructure ini = GetSettingsFile();
  return stoi(ini["Ships"][shipName]);
}

// Using the settings file, I can pull the board size from the .ini file
int getBoardFile(string coord){
  mINI::INIStructure ini = GetSettingsFile();
  return stoi(ini["Board"][coord]);
}

// This class is key to the game. This allows for a custom location of a placement of a ship, using a variety of helper class functions, and finally the Ship object
void placeShip(string shipName, Player &currentPlayer){
  int playerX = helper.collectX(currentPlayer.getX());
  string playerY = helper.collectY(currentPlayer.getY());
  string playerOr = helper.collectOr();
  int shipLength = getShipLength(shipName);
  string shipId = to_string(uniquePlayer1Id++);
  currentPlayer.addToList(Ship(playerX, playerY, shipLength, playerOr, shipName,shipId));
}

// This function allows me to pull all of the data from under the "ships" header in the .ini file.
vector<string> readShipsAvalible(){
  vector<string> ships;
  for (auto const& it : GetSettingsFile())
  {
	  auto const& section = it.first;
	  auto const& collection = it.second;
    if (section == "ships"){
      for (auto const& it2 : collection)
	    {
		    auto const& key = it2.first;
		    ships.push_back(key); 
	    }
    }
  }
  return ships;
}

// This is the place ship menu. This method allows the user to place their different ships, with an option to back out at any time.
void placeShipsMenu(Player &currentPlayer){
  vector<string> ships = readShipsAvalible();
  ships.push_back("Back");
  int userChoice;

  do{
    cout << "\n\nWhich Ships would you like to place?\n";
    helper.printMenu(ships);

    userChoice = helper.userNumberInput();
    
    switch(userChoice) {
			case 1: 
        placeShip("carrier", currentPlayer);
        break;
      case 2: 
        placeShip("battleship", currentPlayer);
        break;
      case 3: 
        placeShip("destroyer", currentPlayer);
        break;
      case 4: 
        placeShip("submarine", currentPlayer);
        break;
      case 5: 
        placeShip("patrol_boat", currentPlayer);
        break;
			case 0: 
        cout << "Exiting";
        break;
			default:
			cout << "\n'" << userChoice << "' is an invalid option  - please try again."; // If you type beyond the option range, you will be told to try again
			break;
    }
  }while (userChoice != 0);
}

// This funtion generates an AI ships, using just this ship name. This has validation in here also, if the AI ship is off the board, or overlapping, it will repeat until it is no longer
void generateAiShips(Player &computerPlayer, string shipName){
  string shipId;
  if(computerPlayer.getPlayerId() <= 5){
    shipId = to_string(uniquePlayer1Id++);
  }else{
    shipId = to_string(uniquePlayer2Id++);
  }
  bool testOrientation = false;
  do{
    Ship aiShip = computerPlayer.createShip(helper.shipCoordGen(computerPlayer.getX(),getShipLength(shipName)),helper.randomY(computerPlayer.getY(), getShipLength(shipName)), getShipLength(shipName),helper.randomOrientation(), shipName,shipId);
    testOrientation = computerPlayer.autoAdd(aiShip);
  }while(!testOrientation);
}


//This is the for loop of how the program generates all the ships and places them. If a user wants to place certain ones, then auto-place the rest, this function will allow for that.
void computerGenerate(Player &computerPlayer){
  vector<string> computerList = readShipsAvalible();
  vector<string> currentList = computerPlayer.returnShipNames();
  int count = 0;
  for(string ship : computerPlayer.returnShipNames()){
    for (string shipName : computerList){
      if (shipName == ship){
        computerList.erase(computerList.begin() + count);
      }
      count++;
    }
  }
  for (string shipName : computerList){
    generateAiShips(computerPlayer, shipName);
  }
}

//This is the for loop of how the program checks to see what ships they have left to palce
void shipsLeftToPlace(Player &computerPlayer){
  cout <<"\n\nCurrent non-placed ships:\n";
  vector<string> computerList = readShipsAvalible();
  vector<string> currentList = computerPlayer.returnShipNames();
  int count = 0;
  for(string ship : computerPlayer.returnShipNames()){
    for (string shipName : computerList){
      if (shipName == ship){
        computerList.erase(computerList.begin() + count);
      }
      count++;
    }
  }
  for (string shipName : computerList){
    cout << "\t" << shipName << "\n" ;
  }
}

// The main setting-up menu, in here the player objects are created, along with their boards. This function will repeat until the user either continues with the game, or quits. There is polymorphism in this class, allowing both for 1 real player vs computer, and then 1 real player vs another real player.
bool setupGame(int player1, int player2){
  playerList.push_back(Player(player1,1,5,0));
  playerList.push_back(Player(player2,0,5,0));
  playerList[0].createBoard(getBoardFile("sizex"), getBoardFile("sizey"));
  playerList[1].createBoard(getBoardFile("sizex"), getBoardFile("sizey"));
  shipsAvalible = readShipsAvalible();
  bool computerPlay = false;

  if(playerList[1].getPlayerId() >= 5){
    computerGenerate(playerList[1]);
    computerPlay = true;
  }
  
  bool continuePlay = false;
  bool playerTwoReady = false;
  
  bool placed = false;
  int userChoice;
  int playerNumber = 0;
  string menuChoices[] = {"Place ship myself","Auto-place", "Continue", "Reset", "Quit"};// This is setting up the menu choices so it's not needed to be printed out in a block in this class
  do{
    cout << "\n\nGame Set-up\n";
    cout << "Player "<< playerNumber+1 <<"\n\n";
    playerList[playerNumber].printBoard(true);// This "true" allows the user to see their board. This is key for battleships gameplay, as traditionally you can't see the other players ships.
    if(playerList[playerNumber].getShipList().size() <= shipsAvalible.size()){
      shipsLeftToPlace(playerList[playerNumber]);
    }
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    helper.printMenu(vecOfStr);
    
    userChoice = helper.userNumberInput();
    
    switch(userChoice) {
			case 1: //This if statement is validating wether all of the users ships have been placed
        if(!placed || playerList[playerNumber].getShipList().size() < shipsAvalible.size()){
          placeShipsMenu(playerList[playerNumber]);
          placed = true;
        }else{
          cout << "\n You have already placed all ships.\n";
        }
        break;
      case 2: //This if statement is doing a similar, but with another desired outcome, and it wasn't viable enough to become refactored
        if(!placed || playerList[playerNumber].getShipList().size() < shipsAvalible.size()){
          cout << "\nAuto-place\n";
          uniquePlayer1Id = 0;
          computerGenerate(playerList[playerNumber]);
          placed = true;
        }else{
          cout << "\n You have already placed all ships.\n";
        }
        break;
      case 3: //This if statement is ensuring that the user has placed all of his required ships, and if two players are playing, then will continue and adapt to change the second players settings
        if(playerList[playerNumber].getShipList().size() >= shipsAvalible.size()){
          cout << "\nContinue\n";
          if (computerPlay || playerTwoReady){
            continuePlay = true;
            userChoice = 0;
          }
          else{
            helper.clearScreen();
            playerNumber = helper.opposite(playerNumber);
            placed = false;
            playerTwoReady = true;
          }
        }else{
          cout <<"\nYou haven't placed all of your ships\n";
        }
        
        break;
      case 4: 
        cout << "\nReset\n";
        playerList[playerNumber].resetBoard();//Using a function of the Player class to clear the board of placed ships
        placed = false;
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

// A simple play game funtion, starting once the user has fully completed their set-up
void playGame(){
  Game Game(playerList);
}

// The main menu. This allows the user to select what type of game they want to play. Using the same print menu system, this allows the user to start a new game very easily
void mainMenu(){
  int userChoice;
  string menuChoices[] = {"One player vs Computer","Two Player Game","Quit"};
  do{
    cout << "\n\nWelcome to the AdaShips\n";
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    helper.printMenu(vecOfStr);

    userChoice = helper.userNumberInput();
    
    switch(userChoice) {
			case 1: 
        helper.clearScreen();
        if(setupGame(1,5)){
          playGame();
        }
        break;
      case 2: 
        helper.clearScreen();
        if(setupGame(1,2)){
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

// This is the starter function, a standard part of C++
int main() {
  mainMenu();
}