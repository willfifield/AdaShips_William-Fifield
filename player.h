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

  vector<vector<string>> allShips(){
    vector<vector<string>> temp;
    for (Ship ship : shipList){
      for(vector<string> coord : ship.getShipCoord()){
      temp.push_back(coord);
      }
    }
    return temp;
  }
  

  void printBoard(){
    playerBoard.printPlayerBoard(allShips());
  }

  void printAllShips(){
    for(auto ship = shipList.begin(); ship != shipList.end(); ++ship){
      ship -> getDetails();
    }
  }

  void createBoard(int x, int y){
    playerBoard.setBoard(x,y);
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
      if (ship.getName() == shipName){
        return false;//found in our list
      }
    }
    return true;//not found in our list
  }

  void addToList(Ship newShip){
    if(checkShipList(newShip.getName())){
      shipList.push_back(newShip);
      newShip.getDetails();
    }
    else{
      cout << "\nUnable to place: " << newShip.getName() << " as it already exists.\n";
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