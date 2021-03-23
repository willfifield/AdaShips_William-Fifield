using namespace std;



class Board{
  private:
    vector<vector<string>> board;
    int y;
    int x;
    Helper helper;

  public:

    int getX(){return x;};
    int getY(){return y;};
    string getYAlpha(int number){return helper.nth_letter(y);};

    void setBoard(int userX, int userY){
      y = userY;
      x = userX;
    }

    string checkShip(int counti, int countj,vector<vector<string>> ships){
      for(vector<string> ship : ships){
        if(helper.alphaToNum(ship.at(0)) == countj && ship.at(1) == to_string(counti)){
          return ship.at(2);
        }
      }
      return "~";
    }

    void printPlayerBoard(vector<vector<string>> &activeShips){
      for(int i = 1; i <= y; i++){
        cout << "\t" <<helper.nth_letter(i);
      }
      for(int i = 1; i <= y; i++){
        cout << "\n" << i << "\t";
        for(int j = 1; j <= x; j++){
          cout << checkShip(i,j,activeShips) << "\t";
        }
      }
    }

};