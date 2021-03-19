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

  void setPlayerId(int id){playerId = id;}
  int getPlayerId(){return playerId;}

  void setPlayerType(int type){playerType = type;}
  int getPlayerType(){return playerType;}
  
  void setNumberOfShips(int noShips){numOfShips = noShips;}
  int getNumberOfShips(){return numOfShips;}

  void setBombs(int userBombs){bombs = userBombs;}
  int getBombs(){return bombs;}
  

  void printBoard(){
    playerBoard.printBoard();
  }

  void printAllShips(vector<Ship> newShipList){
    cout <<"DEBUGGING\n";
    cout << newShipList.size() << " SIZE\n";
    newShipList.at(0).getDetails();
    for(auto ship = newShipList.begin(); ship != newShipList.end(); ++ship){
      cout <<"\nDEBUGGING2";
      ship -> getDetails();
    }
  }

  void printAllShips(){
    cout <<"DEBUGGING\n";
    cout << shipList.size() << " SIZE\n";
    shipList.at(0).getDetails();
    for(auto ship = shipList.begin(); ship != shipList.end(); ++ship){
      cout <<"\nDEBUGGING2";
      ship -> getDetails();
    }
  }

  void createBoard(int x, int y){
    playerBoard.setBoard(x,y);
    playerBoard.generateBoard();
    resetCopy = playerBoard;
  }

  void deleteShip(string shipName){
    int i = 0;
    for(auto ships : shipList){
      if(ships.getName() == shipName){
        shipList.erase(shipList.begin()+i);
      }
      i++;
    }
  }

  bool checkShipList(string shipName){
    for (Ship ship : shipList){
      cout << "\nTHIS IS SHIP NAME" << ship.getName() <<"\n\n";
      if (ship.getName() == shipName){
        return false;//found in our list
      }
    }
    return true;//not found in our list
  }

  void addToList(Ship newShip){
    shipList.push_back(newShip);
    shipList.at(0).getDetails();
  }

  void addNewShips(vector<Ship> newShipList){
    
    for (Ship ship : newShipList){
      if(checkShipList(ship.getName())){
        shipList.push_back(ship);
      }
      else{
        cout << "\nUnable to place: " << ship.getName() << " as it already exists.\n";
      }
      
    }
  }

  void placeShip(int x, string y, int shipLength, string orientation, string shipName){
    
    if (checkShipList(shipName)){
      shipList.push_back(Ship(x, y, shipLength, orientation, shipName));
      cout << "\ninside If\n";
      //newShip.generateShip(x, y, shipLength, orientation, shipName);
      
      //newShip.getDetails();
      shipList.at(0).getDetails();
      printAllShips(shipList);
      
    }
    else{
      cout << "\nYou have already placed this ship";
    }
  }

  vector<Ship> getShipList(){return shipList;};

  int getX(){return playerBoard.getX();};
  int getY(){return playerBoard.getY();};
  //int getYAlpha(){return playerBoard.getYAlpha();};

  void resetBoard(){
    playerBoard = resetCopy;
  }
};