using namespace std;

class Board{
  private:
    vector<vector<string>> board;
    int y;
    int x;
    
    string nth_letter(int n){
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

    int getX(){return x;};
    int getY(){return y;};
    //string getYAlpha(){return nth_letter(y);};

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

    void printPlayerBoard(vector<vector<string>> activeShips){
      vector<string> allShipsY;
      vector<string> allStringX;
      cout << activeShips.size() << "THIS IS SIZE";
      for(int i = 1; i < y; i++){
        cout << "\t" <<nth_letter(i);
      }
      for(vector<string> ship : activeShips){
        allShipsY.push_back(ship.at(0));
        cout<<ship[0] << "THIS IS SHIP";
      }
      for(vector<string> ship : activeShips){
        allStringX.push_back(ship.at(1));
        cout<<ship[1];
      }
      for(int i = 1; i < y; i++){
        cout << "\n" << i << "\t";
        for(int j = 1; j < x; j++){
          // cout << "THIS IS ACTIVE SHIPS " << activeShips.at(i).at(j)<<"\n";
          //cout << "THIS IS TO STRING " << j<<"\n";
          if (find(allStringX.begin(), allStringX.end(), to_string(j)) != allShipsY.end()){
            cout << "0" << "\t";
          }
          else{
            cout << "~" << "\t";
          }
        }
      }
    }

    // void printBoard(vector<vector<string>> activeShips){
    //   int countX = 1;
    //   int countY = 1;
    //   for(vector<string> lineY: board){
    //     cout << "\t" <<nth_letter(countX);
    //     countX++;
    //   }
    //   for(vector<string> lineY : board){
    //     cout << "\n" << countY << "\t";
    //     for(string lineX: lineY){
    //       cout << "THIS IS ACTIVE SHIPS " << activeShips[countX][countY]<<"\n";
    //       cout << "THIS IS TO STRING " << countX<<"\n";
    //       if (activeShips[countX][countY] == to_string(countX)){
    //         cout << "0" << "\t";
    //       }
    //       else{
    //         cout << lineX << "\t";
    //       }
    //     }
    //     countY++;
    //   }
    // }

    // void printBoard(){
    //   int countX = 1;
    //   int countY = 1;
    //   for(vector<string> lineY: board){
    //     cout << "\t" <<nth_letter(countX);
    //     countX++;
    //   }
    //   for(vector<string> lineY : board){
    //     cout << "\n" << countY << "\t";
    //     for(string lineX: lineY){
    //       cout << lineX << "\t";
    //     }
    //     countY++;
    //   }
    // }
};