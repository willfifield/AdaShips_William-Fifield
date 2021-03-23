using namespace std;

class Ship{

  private:
  int xCoord;
  string yCoord;
  string shipId;
  int length;
  string orientation;
  string shipName;
  bool alive;
  bool placed;
  vector<vector<string>> shipCoord;

  Helper helper;

  public:

  void getDetails(){
    cout <<"\nUser X: " << xCoord << "\nUser Y: " << yCoord << "\nOrientation: " << orientation << "\nLength: " << length <<"\n";
    for(vector<string> coordx : shipCoord){
      for(string coordy : coordx){
        cout << coordy;
      }
      cout <<"\n";
    }
  }

  void generateCoords(){
    vector<string> tempCoords;
    tempCoords.push_back(yCoord);
    tempCoords.push_back(to_string(xCoord));
    tempCoords.push_back(shipId);
    shipCoord.push_back(tempCoords);
    tempCoords.clear();

    for (int i = 1; i < length; i++){
      if (orientation == "V"){
        tempCoords.push_back(yCoord);
        tempCoords.push_back(to_string(xCoord+i));
        tempCoords.push_back(shipId);
        shipCoord.push_back(tempCoords);
        tempCoords.clear();
      }
      else{
        tempCoords.push_back(helper.nth_letter((helper.alphaToNum(yCoord)+i)));
        tempCoords.push_back(to_string(xCoord));
        tempCoords.push_back(shipId);
        shipCoord.push_back(tempCoords);
        tempCoords.clear();
      }
    }
  }

  Ship(int userX, string userY, int shipLength, string playerOr, string name, string userShipId){
    xCoord = userX;
    yCoord = userY;
    orientation = playerOr;
    length = shipLength;
    shipName = name;
    shipId = userShipId;
    alive = true;
    placed = true;
    generateCoords();
  }

  string getName(){return shipName;}
  bool getAlive(){return alive;}
  bool getPlaced(){return placed;}
  string getShipId(){return shipId;}

  vector<vector<string>> getShipCoord(){return shipCoord;}


};