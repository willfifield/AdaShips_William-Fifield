using namespace std;

class Ship{

  private:
  int xCoord;
  string yCoord;
  int length;
  string orientation;

  public:

 

  void getDetails(){
    cout <<"\nUser X: " << xCoord << "\nUser Y: " << yCoord << "\nOrientation: " << orientation <<"\n";
  }

  void generateShip(int userX, string userY, string shipType, string playerOr){
    xCoord = userX;
    yCoord = userY;
    orientation = playerOr;
    if (shipType == "carrier"){
      length = 5;
    }
  }


};