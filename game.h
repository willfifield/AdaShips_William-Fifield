using namespace std;

class Game{
  private:

  vector<Player> playerList;
  Helper helper;
  vector<vector<string>> shotAreasP1;
  vector<vector<string>> shotAreasP2;

  public:
  
  // Starting the game function, setting the players so we can refernece them easily
  Game (vector<Player> &newPlayerList){
    playerList = newPlayerList;
    playerTurn();
  }

  // A nice to have, this function puts a seperation line in the console
  void printLine(){
    cout << "\n";
    cout << string( 50, '-' );
  }

  // This is checking if a location has already been shot, using local vectors for each player
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

  // This get shot function uses the players identifier, and an AI option to decide of where to shoot. Using the helper method for collecting x and y, and the auto generator also in the helper. Whilst in a loop, this will ensure that the shot isn't a duplicate, and will be asked again until a valid answer is given. Once it is, it adds it to the local list, and also that players ship list, so it can be shown in the board.
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

  // This function sends the missile to the opposites player object, checking if it has hit any of the opponents ships
  void compareShipLists(vector<string> missileCoords, int playerNumber){
    playerList[helper.opposite(playerNumber)].missileShot(missileCoords);
  }

  // A simple key for the user to see what to look out for in the board. These are coloured also, like they are when on the active board
  void printKey(){
    cout <<"\n\t\033[1;31m"<< "#" <<"\033[0m" << ": Ship Hit\t\t\t";
    cout <<"\033[1;33m"<< "Ø" <<"\033[0m" << ": Ship Missed\t\n";
  }

  // Another menu system, flicking between the two players. This menu is build to be expandable, with the later tasks. In this we print both ours and the opponents board (hiding the opponents ships), validating shots (from player or computer), and can be played with 2 human players with no changes to the code. This will loop over and over until the win condition is met, which is all ships of the opponent has been destroyed
  void playerTurn(){
    int userChoice;
    int playerNumber = 0;
    bool gameActive = true;
    string menuChoices[] = {"Shoot Missile","Auto-Shot","Quit"};
    do{
      helper.clearScreen();
      cout <<"\nPlayer " << playerNumber+1 <<"'s turn\n";
      cout<<"\nThis is your board:\n";
      playerList[playerNumber].printBoard(true);
      printLine();
      cout<<"\n\nThis is the other players board:\n";
      playerList[helper.opposite(playerNumber)].printBoard(false);// CHANGE THIS TO TRUE TO SEE OTHER PLAYERS SHIPS
      printKey();
      if(playerList[playerNumber].getPlayerId() >= 5){
        getShot(playerNumber, true);
        cout << "\n\nPlease enter 1 to continue from computers turn\n";
        userChoice = helper.userNumberInput();
      }else{
        cout << "\n\nWhere would you like to shoot?\n";
        vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
        helper.printMenu(vecOfStr);

        bool loopCheck = true;
        do{
          userChoice = helper.userNumberInput();
          int userContinue;
          switch(userChoice) {
            case 1: 
              getShot(playerNumber,false);
              loopCheck = false;
              cout << "\n\nPlease enter 1 to continue from your turn\n";
              userContinue = helper.userNumberInput();//Collect user continue
              break;
            case 2: 
              getShot(playerNumber,true);
              loopCheck = false;
              cout << "\n\nPlease enter 1 to continue from your turn\n";
              userContinue = helper.userNumberInput();
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
      playerNumber = helper.opposite(playerNumber);
      if(playerList[playerNumber].checkIfWon()){
        gameActive = false;
      }
    }while (gameActive);
    // Congratulating the player who wins the game
    cout << "\n\nCongratulations Player " << helper.opposite(playerNumber)+1 <<", you WON!\n\n";
  }

};