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

  int returnVal(char x)
    {
      return (int)x - 64;
    }

  int alphaToNum(string toConvert){
    int converted;
    for (unsigned int i = 0; i < toConvert.length(); i++)
    {
      converted = returnVal(toConvert[i]);
    }
    return converted;
  }
  

  public:

  Player(int playerIdInput, int playerTypeInput, int numberOfShips, int playerBombCount){
      playerId = playerIdInput;
      playerType = playerTypeInput;
      numOfShips = numberOfShips;
      bombs = playerBombCount;
    }

  vector<Ship> getShipList(){return shipList;};
  int getX(){return playerBoard.getX();};
  int getY(){return playerBoard.getY();};
  string getYAlpha(){return playerBoard.getYAlpha();};

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
      if(alphaToNum(ship.at(0)) > getY() && ship.at(1) > to_string(getX())){
        return false;
      }
    }
    return true;
  }

  void addToList(Ship newShip){
    if(checkShipInBoard(newShip.getShipCoord()) && checkShipList(newShip.getName()) && compareShipLists(newShip.getShipCoord()) ){
      shipList.push_back(newShip);
      newShip.getDetails();
    }
    else if(!checkShipList(newShip.getName())){
      cout << "\nUnable to place: " << newShip.getName() << " as it already exists.\n";
    }
    else if(!compareShipLists(newShip.getShipCoord()){
      cout << "\nUnable to place: " << newShip.getName() << " as it overlaps current ships.\n";
    }
    else{
      cout << "\nUnable to place: " << newShip.getName() << " as it goes past the board boundary.\n";
    }
  }

  void resetBoard(){
    playerBoard = resetCopy;
  }
};