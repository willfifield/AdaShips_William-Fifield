using namespace std;

#include "board.h"
#include "ship.h"

class Player{
  private:
  Board playerBoard;
  Board resetCopy;
  vector<Ship> shipList;
  

  public:

  void printBoard(){
    playerBoard.printBoard();
  }

  void createBoard(int x, int y){
    playerBoard.setBoard(x,y);
    playerBoard.generateBoard();
    resetCopy = playerBoard;
  }

  void placeShip(int x, string y, string shipName, string orientation){
    Ship newShip;
    newShip.generateShip(x,y,shipName,orientation);
    shipList.push_back(newShip);
    newShip.getDetails();
  }


  int getX(){return playerBoard.getX();};
  int getY(){return playerBoard.getY();};
  //int getYAlpha(){return playerBoard.getYAlpha();};

  void resetBoard(){
    playerBoard = resetCopy;
  }
};