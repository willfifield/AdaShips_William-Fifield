using namespace std;

#include "board.h"
#include "ship.h"

class Player{
  private:
  Board playerBoard;
  Board resetCopy;
  vector<Ship> shipList;
  Ship newShip;
  

  public:

  void printBoard(){
    playerBoard.printBoard();
  }

  void printAllShips(){
    cout <<"DEBUGGING";
    shipList[0].getDetails();
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
    for (auto ships : shipList){
      cout << "\nTHIS IS SHIP NAME" << ships.getName() <<"\n\n";
      if (ships.getName() == shipName){
        return false;//found in our list
      }
    }
    return true;//not found in our list
  }

  void placeShip(int x, string y, int shipLength, string orientation, string shipName){
    if (checkShipList(shipName)){
      //Ship newShip;
      newShip.generateShip(x, y, shipLength, orientation, shipName);
      shipList.push_back(newShip);
      newShip.getDetails();
      shipList[0].getDetails();
      
    }
    else{
      cout << "\nYou have already placed this ship";
    }
  }



  int getX(){return playerBoard.getX();};
  int getY(){return playerBoard.getY();};
  //int getYAlpha(){return playerBoard.getYAlpha();};

  void resetBoard(){
    playerBoard = resetCopy;
  }
};