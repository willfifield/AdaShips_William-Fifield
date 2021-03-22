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

    int returnVal(char x)
    {
      return (int)x - 64;
    }

    int alphaToNum(string toConvert){
      int converted;
      for (unsigned int i = 0; i < toConvert.length(); i++)
      {
        converted = returnVal(toConvert[i]);
      }
      return converted;
    }


  public:

    int getX(){return x;};
    int getY(){return y;};
    string getYAlpha(int number){return nth_letter(y);};

    void setBoard(int userX, int userY){
      y = userY;
      x = userX;
    }

    string checkShip(int counti, int countj,vector<vector<string>> ships){
      for(vector<string> ship : ships){
        if(alphaToNum(ship.at(0)) == countj && ship.at(1) == to_string(counti)){
          return ship.at(2);
        }
      }
      return "~";
    }

    void printPlayerBoard(vector<vector<string>> &activeShips){
      for(int i = 1; i <= y; i++){
        cout << "\t" <<nth_letter(i);
      }
      for(int i = 1; i <= y; i++){
        cout << "\n" << i << "\t";
        for(int j = 1; j <= x; j++){
          cout << checkShip(i,j,activeShips) << "\t";
        }
      }
    }

};