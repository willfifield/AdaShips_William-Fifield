using namespace std;

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