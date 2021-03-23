using namespace std;

#include "board.h"
#include "ship.h"

class Player{
  private:
  int playerId;
  int playerType;

  Board playerBoard;
  Board resetCopy;
  vector<Ship> shipList;
  Helper helper;

  int shotsPerRound;
  int numOfShips;
  int bombs; 

  public:

  Player(int playerIdInput, int playerTypeInput, int numberOfShips, int playerBombCount){
    playerId = playerIdInput;
    playerType = playerTypeInput;
    numOfShips = numberOfShips;
    bombs = playerBombCount;
  }

  Ship createShip(int userX, string userY, int shipLength, string playerOr, string name, string userShipId){
    return Ship(userX, userY, shipLength, playerOr, name, userShipId);
  }

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
  
  void printBoard(){
    vector<vector<string>> temp;
    for (Ship ship : shipList){
      for(vector<string> coord : ship.getShipCoord()){
        temp.push_back(coord);
      }
    }
    playerBoard.printPlayerBoard(temp);
  }

  void missileShot(vector<string> missileCoords){
    bool found = false;
    for (Ship &firedAtShip : shipList){
      for(vector<string> &ship : firedAtShip.getShipCoord()){
        if(ship.at(0) == missileCoords.at(0) && ship.at(1) == missileCoords.at(1)){
          firedAtShip.missileHit(missileCoords, true);
          cout << "\nSHIP FOUND AT: " << ship.at(0) << ship.at(1) << "\n";
          found = true;
        }
      }
    }
    if(!found){//int userX, string userY, int shipLength, string playerOr, string name, string userShipId
      cout <<"\n"<< missileCoords.at(0) << ": ThIS IS MISSILE 0\n";
      //int convert = stoi(missileCoords.at(0));
      addToList(createShip(stoi(missileCoords.at(1)),missileCoords.at(0), 0, "H", "missed","Ø"));
      //cout << "\nBEYOND IF NOT FOUND\n";
    }
  }

  bool checkIfWon(){
    int winCheck = 0;
    for(Ship shipCheck : shipList){
      if (shipCheck.getAlive()){
        winCheck++;
      }
    }
    if(winCheck == 0){
      cout << "\n---------------WINNER--------------\n";
      return true;
    }
    cout << "\n  WINNER CHECK  \n";
    return false;
  }

  void printAllShips(){
    for(auto ship = shipList.begin(); ship != shipList.end(); ++ship){
      ship -> getDetails();
    }
  }

  void createBoard(int x, int y){
    playerBoard.setBoard(x,y);
  }

  void deleteShip(Ship removedShip){
    int i = 0;
    for(auto ships : shipList){
      if(ships.getShipId() == removedShip.getShipId()){
        shipList.erase(shipList.begin()+i);
      }
      i++;
    }
  }

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

  bool checkShipList(string shipName){
    for (Ship ship : shipList){
      if (ship.getName() == shipName){
        return false;//found in our list
      }
    }
    return true;//not found in our list
  }

  bool checkShipInBoard(vector<vector<string>> ships){
    for(vector<string> ship : ships){
      if(helper.alphaToNum(ship.at(0)) > getY() && ship.at(1) > to_string(getX())){
        return false;
      }
    }
    return true;
  }

  void addToList(Ship newShip){
    if( newShip.getName() == "missed" || (checkShipInBoard(newShip.getShipCoord()) && checkShipList(newShip.getName()) && compareShipLists(newShip.getShipCoord()))){ //Not checking "missed" items
      shipList.push_back(newShip);
      newShip.getDetails();
    }else if(!checkShipList(newShip.getName())){
      cout << "\nUnable to place: " << newShip.getName() << " as it already exists.\n";
    }else if(!compareShipLists(newShip.getShipCoord())){
      cout << "\nUnable to place: " << newShip.getName() << " as it overlaps current ships.\n";
    }
    else{
      cout << "\nUnable to place: " << newShip.getName() << " as it goes past the board boundary.\n";
    }
  }

  bool autoAdd(Ship newShip){
    if(checkShipInBoard(newShip.getShipCoord()) && checkShipList(newShip.getName()) && compareShipLists(newShip.getShipCoord()) ){
      shipList.push_back(newShip);
      newShip.getDetails();// -----------------------REMOVE WHEN READY TO PLAY-------------------------
      return true;
    }else {
      return false;
    }
  }

  void resetBoard(){
    playerBoard = resetCopy;
  }

};