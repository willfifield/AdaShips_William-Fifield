using namespace std;

class Ship{

  private:
  int xCoord;
  string yCoord;
  int length;
  string orientation;
  string shipName;
  bool alive;

  public:

  void getDetails(){
    cout <<"\nUser X: " << xCoord << "\nUser Y: " << yCoord << "\nOrientation: " << orientation << "\nLength: " << length <<"\n";
  }

  Ship(int userX, string userY, int shipLength, string playerOr, string name){
    xCoord = userX;
    yCoord = userY;
    orientation = playerOr;
    length = shipLength;
    shipName = name;
    alive = true;
  }

  string getName(){return shipName;}


};