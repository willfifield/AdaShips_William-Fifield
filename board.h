/*
This is a Board class onject.

This object allows the user to have their own board printed and displayed in a nice way. Each board is unique, but it somewhat acts as a helper class with printing the board. This is where formatting of strongs take place.
*/

using namespace std;

class Board{
  private:

    // The local x and y variables
    int y;
    int x;
    Helper helper;

  public:

    // Below are some standard set up functions, allowing the board to be set from another class
    int getX(){return x;};
    int getY(){return y;};
    string getYAlpha(int number){return helper.nth_letter(y);};

    void setBoard(int userX, int userY){
      y = userY;
      x = userX;
    }

    // This checkShip class is used when displaying out to the board, ensuring the correct symbol is shown for their ships
    string checkShip(int counti, int countj,vector<vector<string>> ships){
      for(vector<string> ship : ships){
        if(helper.alphaToNum(ship.at(0)) == countj && ship.at(1) == to_string(counti)){
          return ship.at(2);
        }
      }
      return "~";
    }

    //This printPlayerBoard funtion takes the active ships from the player class, and displays them in the board constraits. I had originally stored the entire board, with blanks where there weren't ships. I later changed this and adapted a more memory and storage friendly approach. Inside of this function we also change colours or hit/missed ships, to make them stand out more
    void printPlayerBoard(vector<vector<string>> &activeShips, bool view){
      for(int i = 1; i <= y; i++){
        cout << "\t" <<helper.nth_letter(i);
      }
      for(int i = 1; i <= y; i++){
        cout << "\n" << i << "\t";
        for(int j = 1; j <= x; j++){
          if(checkShip(i,j,activeShips) == "#"){
            cout <<"\033[1;31m"<< checkShip(i,j,activeShips) <<"\033[0m"  << "\t";
          }
          else if(checkShip(i,j,activeShips) == "Ø"){
            cout <<"\033[1;33m"<< checkShip(i,j,activeShips) <<"\033[0m"  << "\t";
          }
          else{
            if(view){
              cout << checkShip(i,j,activeShips) << "\t";
            }
            else{
              cout << "~"  << "\t";
            }
          }
        }
      }
    }

};