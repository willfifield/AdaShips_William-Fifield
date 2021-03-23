using namespace std;

class Game{
  private:

  vector<Player> playerList;
  Helper helper;

  public:
  
  Game (vector<Player> &newPlayerList){
    playerList = newPlayerList;
    printPlayers();
  }

  void printPlayers(){
    for (Player player: playerList){
      player.printAllShips();
    }
  }


  void playerTurn(int playerId){
    int userChoice;
    string menuChoices[] = {"Shoot Missile","Quit Game"};
    do{
      playerList[0].printBoard();
      playerList[1].printBoard();
      cout << "\nWhere would you like to shoot?\n";
      vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
      // helper.printMenu(vecOfStr);

      // userChoice = helper.userNumberInput();
      
      // switch(userChoice) {
      //   case 1: 
      //     helper.clearScreen();
      //     if(setupGame(1,5)){
      //       playGame();
      //     }
      //     break;
      //   case 0: 
      //     cout << "Exiting";
      //     break;
      //   default:
      //   cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
      //   break;
      // }
    }while (userChoice != 0);
  }

};