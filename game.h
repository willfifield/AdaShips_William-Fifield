using namespace std;

class Game{
  private:

  vector<Player> playerList;
  Helper helper;

  public:
  
  Game (vector<Player> &newPlayerList){
    playerList = newPlayerList;
    playerTurn();
  }

  void printPlayers(){
    for (Player player: playerList){
      player.printAllShips();
    }
  }

  void printLine(){
    cout << "\n";
    cout << string( 50, '-' );
  }

  void getShot(int playerNumber){
    int shotX;
    string shotY;
    int maxX = playerList[playerNumber].getX();
    int maxY = playerList[playerNumber].getY();
    if (playerList[playerNumber].getPlayerId() < 5){
      shotX = helper.collectX(maxX);
      shotY = helper.collectY(maxY);
    }else{  
      shotX = helper.shipCoordGen(maxX,0);
      shotY = helper.randomY(maxY,0);
    }
    vector<string> newMissile;
    newMissile.push_back(shotY);
    newMissile.push_back(to_string(shotX));

    compareShipLists(newMissile, playerNumber);
  }

  int opposite(int toSwap){
    if(toSwap==0){
      return 1;
    }
    return 0;
  }

  void compareShipLists(vector<string> missileCoords, int playerNumber){
    int count = 0;
    bool found = false;
    for (Ship firedAtShip : playerList[opposite(playerNumber)].getShipList()){
      for(vector<string> ship : firedAtShip.getShipCoord()){
        if(ship.at(0) == missileCoords.at(0) && ship.at(1) > missileCoords.at(1)){
          ship[2] = "#";
          cout << "\nSHIP FOUND AT: " << ship.at(0) << ship.at(1) << "\n";
          found = true;
        }
        else{
          ship[2] = "Ø";
        }
      }
      count++;
    }
    if (!found){
      for(vector<string> &ship : playerList[opposite(playerNumber)].getShipList()[count].getShipCoord()){
        if(ship.at(0) == missileCoords.at(0) && ship.at(0) > missileCoords.at(1)){
          ship[2] = "Ø";
          cout << "\nSHIP MISSED AT: " << ship.at(0) << ship.at(1) << "\n";
        }
      }
    }
  }


  void playerTurn(){
    int userChoice;
    int playerNumber = 0;
    string menuChoices[] = {"Shoot Missile","Quit Game"};
    do{
      cout <<"\nPlayer " << playerNumber+1 <<"'s turn\n";
      cout<<"\nThis is your board:\n";
      playerList[playerNumber].printBoard();
      printLine();
      cout<<"\n\nThis is the other players board:\n";
      playerList[opposite(playerNumber)].printBoard();
      cout << "\n\nWhere would you like to shoot?\n";
      vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
      helper.printMenu(vecOfStr);

      userChoice = helper.userNumberInput();
      
      switch(userChoice) {
        case 1: 
          getShot(playerNumber);
          playerNumber = opposite(playerNumber);
          break;
        case 0: 
          cout << "Exiting";
          break;
        default:
        cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
        break;
      }
      //helper.clearScreen(); ---------------------------------------------ADD BACK-----------------------
    }while (userChoice != 0);
  }

};