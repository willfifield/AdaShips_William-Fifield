using namespace std;

#include "board.h"

class Player{
  private:
  Board playerBoard;
  Board resetCopy;

  public:

  void printBoard(){
    playerBoard.printBoard();
  }

  void createBoard(int x, int y){
    playerBoard.setBoard(x,y);
    playerBoard.generateBoard();
    resetCopy = playerBoard;
  }

  int getX(){return playerBoard.getX();};
  int getY(){return playerBoard.getY();};

  void resetBoard(){
    playerBoard = resetCopy;
  }
};