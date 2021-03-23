using namespace std;

class Game{
  private:

  vector<Player> playerList;
  Helper helper;
  vector<vector<string>> shotAreasP1;
  vector<vector<string>> shotAreasP2;


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

  bool alreadyShot(vector<string> newShot, int playerNumber){
    if(playerNumber == 0){
      for (vector<string> oldCoord : shotAreasP1){
        if(oldCoord.at(0) == newShot.at(0) && oldCoord.at(1) == newShot.at(1)){
          return false;
        }
      }
    }else{
      for (vector<string> oldCoord : shotAreasP2){
        if(oldCoord.at(0) == newShot.at(0) && oldCoord.at(1) == newShot.at(1)){
          return false;
        }
      }
    }
    return true;
  }

  void getShot(int playerNumber, bool ifAuto){
    int shotX;
    string shotY;
    bool shotLoop = true;
    vector<string> newMissile;
    do{
      newMissile.clear();
      int maxX = playerList[playerNumber].getX();
      int maxY = playerList[playerNumber].getY();
      if (ifAuto){
        shotX = helper.shipCoordGen(maxX,0);
        shotY = helper.randomY(maxY,0);
      }else{  
        shotX = helper.collectX(maxX);
        shotY = helper.collectY(maxY);
      }
      newMissile.push_back(shotY);
      newMissile.push_back(to_string(shotX));

      if(alreadyShot(newMissile, playerNumber)){
        shotLoop = false;
      }
      else{
        cout << "\n This area has already been shot at.\n";
      }
    }while(shotLoop);

    if(playerNumber == 0){
      shotAreasP1.push_back(newMissile);
    }
    else{
      shotAreasP2.push_back(newMissile);
    }

    compareShipLists(newMissile, playerNumber);
  }

  int opposite(int toSwap){
    if(toSwap==0){
      return 1;
    }
    return 0;
  }

  void compareShipLists(vector<string> missileCoords, int playerNumber){
    playerList[opposite(playerNumber)].missileShot(missileCoords);
  }

  // bool checkIfWon(int playerNumber){
  //   for(Ship shipCheck : playerList[playerNumber].getShipList()){
  //     for (vector<string> shipIdCheck : shipCheck.getShipCoord()){
  //       if (shipIdCheck.at(2) != "#" || shipIdCheck.at(2) != "Ø"){
  //         cout <<"\nCHECKED IF WON\n";
  //         return false;
  //       }
  //     }
  //   }
  //   cout <<"\n\n--------------------GAME WON-----------------------\n\n";
  //   return true;
  // }


  void playerTurn(){
    int userChoice;
    int playerNumber = 0;
    bool gameActive = true;
    bool hasWon = false;
    string menuChoices[] = {"Shoot Missile","Auto-Shot","Quit"};
    do{
      cout <<"\nPlayer " << playerNumber+1 <<"'s turn\n";
      cout<<"\nThis is your board:\n";
      playerList[playerNumber].printBoard();
      printLine();
      cout<<"\n\nThis is the other players board:\n";
      playerList[opposite(playerNumber)].printBoard();

      if(playerList[playerNumber].getPlayerId() >= 5){
        getShot(playerNumber, true);
        cout << "\n\nPlease enter 1 to continue from computers turn\n";
        //userChoice = helper.userNumberInput();
      }else{
        cout << "\n\nWhere would you like to shoot?\n";
        vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
        helper.printMenu(vecOfStr);

        bool loopCheck = true;
        do{
          userChoice = helper.userNumberInput();
          
          switch(userChoice) {
            case 1: 
              getShot(playerNumber,false);
              loopCheck = false;
              break;
            case 2: 
              getShot(playerNumber,true);
              loopCheck = false;
              break;
            case 0: 
              cout << "Exiting";
              loopCheck = false;
              gameActive = false;
              break;
            default:
            cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
            break;
          }
        }while (loopCheck);
      }
      playerNumber = opposite(playerNumber);
      hasWon = playerList[playerNumber].checkIfWon();
      //helper.clearScreen(); ---------------------------------------------ADD BACK-----------------------
    }while (gameActive || !hasWon);
  }

};