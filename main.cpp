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

using namespace std;

Helper helper;

vector<Player> playerList;
vector<string> shipsAvalible;
int uniquePlayer1Id;
int uniquePlayer2Id;

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

int collectX(Player currentPlayer){
  bool inputCheck = false;
  int userChoice;
  do{
    cout << "\nPlease enter your X coordinates (1,2,3...): ";

    userChoice = helper.userNumberInput();

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
  int playerX = collectX(currentPlayer);
  string playerY = collectY(currentPlayer);
  string playerOr = collectOr(currentPlayer);
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
    printMenu(ships);

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
  if(computerPlayer.getPlayerId() != 5){
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


bool setupGame(){
  playerList.push_back(Player(1,1,5,0));
  playerList.push_back(Player(5,0,5,0));
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
    printMenu(vecOfStr);
    
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
  cout << "PLAY GAME";

}

void mainMenu(){
  int userChoice;
  string menuChoices[] = {"One player vs Computer","Quit"};
  do{
    cout << "\n\nWelcome to the AdaShips\n";
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);

    userChoice = helper.userNumberInput();
    
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