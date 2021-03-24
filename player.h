using namespace std;

#include "board.h"
#include "ship.h"

class Player{
  private:

  // These are the storage varaibles within the Player object. Each of these elements are unique for each object
  int playerId;
  int playerType;
  Board playerBoard;
  vector<Ship> shipList; // This is the players ships (list of Ship objects)
  Helper helper; // This allows me to access the public helper class 

  // These variables are preparing for later development tasks
  int shotsPerRound;
  int numOfShips;
  int bombs; 

  public:

  // This is a player initializer. This sets up the player with some essential variables
  Player(int playerIdInput, int playerTypeInput, int numberOfShips, int playerBombCount){
    playerId = playerIdInput;
    playerType = playerTypeInput;
    numOfShips = numberOfShips;
    bombs = playerBombCount;
  }

  // This is how I create a ship in this class
  Ship createShip(int userX, string userY, int shipLength, string playerOr, string name, string userShipId){
    return Ship(userX, userY, shipLength, playerOr, name, userShipId);
  }

  // Below are a variety of getters and setters for the Player object. These getters allow me to see data from outside of this class
  vector<Ship> getShipList(){return shipList;}
  int getX(){return playerBoard.getX();}
  int getY(){return playerBoard.getY();}
  string getYAlpha(int number){return playerBoard.getYAlpha(number);}

  void setPlayerId(int id){playerId = id;}
  int getPlayerId(){return playerId;}

  void setPlayerType(int type){playerType = type;}
  int getPlayerType(){return playerType;}

  void setNumberOfShips(int noShips){numOfShips = noShips;}
  int getNumberOfShips(){return numOfShips;}

  void setBombs(int userBombs){bombs = userBombs;}
  int getBombs(){return bombs;}

  // Using the Players individual board, I can print using the Board class, passing in the players local ships. There is a bool being brought in also, this is if the user can/can't see their ships (traditionaly with the battleships game you can't see the other players ships)
  void printBoard(bool view){
    vector<vector<string>> temp;
    for (Ship ship : shipList){
      for(vector<string> coord : ship.getShipCoord()){
        temp.push_back(coord);
      }
    }
    playerBoard.printPlayerBoard(temp, view);
  }


  //This is checking if a missile has hit one of the players local ships. In this we can see it itterates through our ship coordinates against the missile, and if it misses it creates a new "Ship" class, so it can be shown on the player boards
  void missileShot(vector<string> missileCoords){
    bool found = false;
    for (Ship &firedAtShip : shipList){
      for(vector<string> &ship : firedAtShip.getShipCoord()){
        if(ship.at(0) == missileCoords.at(0) && ship.at(1) == missileCoords.at(1)){
          firedAtShip.missileHit(missileCoords, true);
          found = true;
        }
      }
    }
    if(!found){
      addToList(createShip(stoi(missileCoords.at(1)),missileCoords.at(0), 0, "H", "missed","Ø"));
    }
  }

  // This function checks if all of the ships "alive" variable are all checked to true. Once they are all no longer alive, the game is won
  bool checkIfWon(){
    int winCheck = 0;
    for(Ship shipCheck : shipList){
      shipCheck.checkDestroyed();
      if (shipCheck.getAlive()){
        winCheck++;
      }
    }
    if(winCheck == 0){
      return true;
    }
    return false;
  }

  // A simple function used in de-bugging, allowing me to see all ships within this player class
  void printAllShips(){
    for(auto ship = shipList.begin(); ship != shipList.end(); ++ship){
      ship -> getDetails();
    }
  }

  // This creates the local instance of the player board, allowing the x and y to be set
  void createBoard(int x, int y){
    playerBoard.setBoard(x,y);
  }


  // This compare ship list is to ensure the new ship isn't overlapping current ships
  bool compareShipLists(vector<vector<string>> ships){
    for (vector<string> newCoords : ships){
      for (Ship currentShip : shipList){
        for(vector<string> ship : currentShip.getShipCoord()){
          if(ship.at(0) == newCoords.at(0) && ship.at(1) > newCoords.at(1)){
            return false;
          }
        }
      }
    }
    return true;
  }

  // Another ship check, this is checking there are no duplicate ships within the board, before being placed down
  bool checkShipList(string shipName){
    for (Ship ship : shipList){
      if (ship.getName() == shipName){
        return false;//found in our list
      }
    }
    return true;//not found in our list
  }

  // A final validation check, ensuring the ship is within the bounds of the board when placed (as the starter point may be, but the rest may fall out of the play area)
  bool checkShipInBoard(vector<vector<string>> ships){
    for(vector<string> ship : ships){
      if(helper.alphaToNum(ship.at(0)) > getY() && ship.at(1) > to_string(getX())){
        return false;
      }
    }
    return true;
  }

  // Using those checks, we can pass them through this filter, and if they pass all of them, they'll be added to the shipList
  void addToList(Ship newShip){
    if( newShip.getName() == "missed" || (checkShipInBoard(newShip.getShipCoord()) && checkShipList(newShip.getName()) && compareShipLists(newShip.getShipCoord()))){ //Not checking "missed" items
      shipList.push_back(newShip);
    }else if(!checkShipList(newShip.getName())){
      cout << "\nUnable to place: " << newShip.getName() << " as it already exists.\n";
    }else if(!compareShipLists(newShip.getShipCoord())){
      cout << "\nUnable to place: " << newShip.getName() << " as it overlaps current ships.\n";
    }
    else{
      cout << "\nUnable to place: " << newShip.getName() << " as it goes past the board boundary.\n";
    }
  }

  // An autonomous add ship method, without the string outputs. This is used when the computer places a ship, either for the player or for itself
  bool autoAdd(Ship newShip){
    if(checkShipInBoard(newShip.getShipCoord()) && checkShipList(newShip.getName()) && compareShipLists(newShip.getShipCoord()) ){
      shipList.push_back(newShip);
      return true;
    }else {
      return false;
    }
  }

  // This function is used in conjection with the auto-placer in the main function. This allows the player to not get duplicate ships when autonomusly placing down the rest of them
  vector<string> returnShipNames(){
    vector<string> activeShipNames;
    for(Ship ship : shipList){
      activeShipNames.push_back(ship.getName());
    }
    return activeShipNames;
  }

  // A simple reset, allowing the user to re-add the ships once they're removed
  void resetBoard(){
    shipList.clear();
  }

};