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

mINI::INIStructure GetSettingsFile(){
  mINI::INIFile file("adaship_config.ini"); // create a file instance
  mINI::INIStructure ini;// create a data structure
  file.read(ini);// now we can read the file
  return ini;
}

int getShipLength(string shipName){
  mINI::INIStructure ini = GetSettingsFile();
  return stoi(ini["Ships"][shipName]);
}

int getBoardFile(string coord){
  mINI::INIStructure ini = GetSettingsFile();
  return stoi(ini["Board"][coord]);
}

void placeShip(string shipName, Player &currentPlayer){
  int playerX = helper.collectX(currentPlayer.getX());
  string playerY = helper.collectY(currentPlayer.getY());
  string playerOr = helper.collectOr();
  int shipLength = getShipLength(shipName);
  string shipId = to_string(uniquePlayer1Id++);
  currentPlayer.addToList(Ship(playerX, playerY, shipLength, playerOr, shipName,shipId));
}

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
			cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
			break;
    }
  }while (userChoice != 0);
}


void generateAiShips(Player &computerPlayer, string shipName){
  string shipId;
  if(computerPlayer.getPlayerId() >= 5){
    shipId = to_string(uniquePlayer1Id++);
  }else{
    shipId = to_string(uniquePlayer2Id++);
  }
  
  bool testOrientation = false;
  do{
    testOrientation = computerPlayer.autoAdd(Ship(helper.shipCoordGen(computerPlayer.getX(),getShipLength(shipName)), helper.randomY(computerPlayer.getY(), getShipLength(shipName)), getShipLength(shipName), helper.randomOrientation(), shipName,shipId));
  }while(!testOrientation);
}

void computerGenerate(Player &computerPlayer){
  vector<string> computerList = readShipsAvalible();
  for (string shipName : computerList){
    generateAiShips(computerPlayer, shipName);
  }
}


bool setupGame(int player1, int player2){
  playerList.push_back(Player(player1,1,5,0));
  playerList.push_back(Player(player2,0,5,0));
  playerList[0].createBoard(getBoardFile("sizex"), getBoardFile("sizey"));
  playerList[1].createBoard(getBoardFile("sizex"), getBoardFile("sizey"));
  shipsAvalible = readShipsAvalible();

  computerGenerate(playerList[1]);
  playerList[1].printBoard();// -----------------------REMOVE WHEN READY TO PLAY-------------------------
  
  bool continuePlay = false;
  bool placed = false;
  int userChoice;
  string menuChoices[] = {"Place ship myself","Auto-place", "Continue", "Reset", "Quit"};
  do{
    
    cout << "\n\nGame Set-up\n\n";
    playerList[0].printBoard();
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    helper.printMenu(vecOfStr);
    
    userChoice = helper.userNumberInput();
    
    switch(userChoice) {
			case 1: 
        if(!placed || playerList[0].getShipList().size() < shipsAvalible.size()){
          placeShipsMenu(playerList[0]);
          placed = true;
        }else{
          cout << "\n You have already placed all ships.\n";
        }
        break;
      case 2: 
        if(!placed){
          cout << "\nAuto-place\n";
          computerGenerate(playerList[0]);
          placed = true;
        }else{
          cout << "\n You have already placed all ships.\n";
        }
        break;
      case 3: 
        cout << "\nContinue\n";
        continuePlay = true;
        userChoice = 0;
        break;
      case 4: 
        cout << "\nReset\n";
        playerList[0].resetBoard();
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
  Game Game(playerList);
}

void mainMenu(){
  int userChoice;
  string menuChoices[] = {"One player vs Computer","Quit"};
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