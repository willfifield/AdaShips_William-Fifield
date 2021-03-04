#include <iostream>
#include <limits>
#include <vector>
#include <assert.h>

using namespace std;

void clearScreen(){
    cout << string( 100, '\n' );
  }

class Board{
  private:
    vector<vector<string>> board;
    int y;
    int x;
    
    string nth_letter(int n)
    {
      assert(n >= 1 && n <= 104);
      if (n>=27 && n<=52){ 
        string s(1,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(n-26)-1]);
        return ("A"+ s);
      }
      else if (n>=52 && n<=78){ 
        string s(1,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(n-52)-1]);
        return ("B"+ s);
      }
      else if (n>=78 && n<=104){ 
        string s(1,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(n-78)-1]);
        return ("C"+ s);
      }
      else{
        string s(1,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[n-1]);
        return s;
      }
    }

  public:

    void setBoard(int userX, int userY){
      y = userY;
      x = userX;
    }

    void generateBoard(){
      vector<string> lineCreate;
      for (int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
          lineCreate.push_back("~");
        }
        board.push_back(lineCreate);
        lineCreate.clear();
      }
    }

    void printBoard(){
      int countX = 1;
      int countY = 1;
      for(vector<string> lineY: board){
        cout << "\t" <<nth_letter(countX);
        countX++;
      }
      for(vector<string> lineY : board){
        cout << "\n" << countY << "\t";
        for(string lineX: lineY){
          cout << lineX << "\t";
        }
        countY++;
      }
    }
};

void printMenu(vector<string> choices){
  cout << "\n\nPlease enter one of the options below:\n";
  int count = 1;
  for (string choice : choices){
    if (choice == "Quit"){
      cout <<"0: " << choice << "\n";
    }
    else{
      cout <<count << ": " << choice << "\n";
    count++;
    }
  }
}

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

  void resetBoard(){
    playerBoard = resetCopy;
  }
};

auto userCoods(string question){
  cout << question;
  int userChoice;
  cin.clear();
  cin >> userChoice;
  if (isdigit(userChoice)){

  }
  else{

  }
}

int userNumberInput(){

  int userChoice;
  cin.clear();
  cin >> userChoice;
  return userChoice;
}

int collectX(){
  cout << question;
  return userChioce;
}

void setupGame(){
  Player userPlayer;
  userPlayer.createBoard(10, 10);
  
  
  int userChoice;
  string menuChoices[] = {"Place ship myself","Auto-place", "Continue", "Reset", "Quit"};
  do{
    clearScreen();
    cout << "\n\nGame Set-up\n\n";
    userPlayer.printBoard();
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);
    
    cin.clear();
    cin >> userChoice;
    
    switch(userChoice) {
			case 1: 
        cout << "\nPlace Ships\n";
        //setupGame();
        break;
      case 2: 
        cout << "\nAuto-place\n";
        //setupGame();
        break;
      case 3: 
        cout << "\nContinue\n";
        //setupGame();
        break;
      case 4: 
        cout << "\nReset\n";
        userPlayer.resetBoard();
        break;
			case 0: 
        cout << "Exiting";
        break;
			default:
			cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
			break;
    }
  }while (userChoice != 0);

}

void playGame(){


}

void mainMenu(){
  int userChoice;
  string menuChoices[] = {"One player vs Computer","Quit"};
  do{
    cout << "\n\nWelcome to the AdaShips\n";
    vector <string> vecOfStr(menuChoices,menuChoices +sizeof(menuChoices) / sizeof(string));
    printMenu(vecOfStr);
    cin.clear();
    cin >> userChoice;
    
    switch(userChoice) {
			case 1: 
        setupGame();
        break;
			case 0: 
        cout << "Exiting";
        break;
			default:
			cout << "\n'" << userChoice << "' is an invalid option  - please try again.";
			break;
    }
  }while (userChoice != 0);
}

int main() {
  mainMenu();
}