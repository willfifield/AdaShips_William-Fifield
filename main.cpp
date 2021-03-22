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
int uniqueId;

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
  // create a file instance
  mINI::INIFile file("adaship_config.ini");

  // create a data structure
  mINI::INIStructure ini;

  // now we can read the file
  file.read(ini);
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
  string shipId = to_string(uniqueId++);
  currentPlayer.addToList(Ship(playerX, playerY, shipLength, playerOr, shipName,shipId));
}

// void placeShipTest(string shipName, Player &currentPlayer){
//   currentPlayer.addToList(Ship(3, "H", 5, "H", "carrier","0"));
//   //currentPlayer.addToList(Ship(2, "G", 4, "H", "battleship","1"));
//   //currentPlayer.addToList(Ship(6, "C", 4, "V", "destroyer","2"));
// }

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
        //placeShipTest("carrier", currentPlayer); 
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

int generatePickedNumber(int maxNumber) {
    // generating random number based on random device
    random_device rdev;
    mt19937 rgen(rdev());
    // Distribute by defining a minimum number and max number.
    std::uniform_int_distribution<int> idist(1, maxNumber); //(inclusive, inclusive)
    return idist(rgen);
}

string randomY(int maxNumber, Player computerPlayer){
  
}

void computerGenerate(Player &computerPlayer){
  while(computerPlayer.getShipList().size()<5){
    computerPlayer.addToList(Ship(generatePickedNumber(computerPlayer.getX()), "H", 5, "H", "carrier","0"));
  }
  
}


bool setupGame(){
  playerList.push_back(Player(1,1,5,0));
  playerList.push_back(Player(2,0,5,0));
  playerList[0].createBoard(getBoardFile("sizex"), getBoardFile("sizey"));
  playerList[1].createBoard(getBoardFile("sizex"), getBoardFile("sizey"));

  computerGenerate(playerList[1]);
  
  bool continuePlay = false;
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
        placeShipsMenu(playerList[0]);
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