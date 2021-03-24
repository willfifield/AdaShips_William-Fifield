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

  void checkDestroyed(){
    vector<string> checkDes;
    for (vector<string> ship : shipCoord){
      checkDes.push_back(ship.at(2));
    }
    bool check = find(checkDes.begin(), checkDes.end(), shipId) != checkDes.end();
    if(!check){
      alive = false;
    }
  }

  void missileHit(vector<string> missileCoords, bool hitOrMiss){
    int count = 0;
    for(vector<string> shotShip : shipCoord){
      if(shotShip.at(0) == missileCoords.at(0) && shotShip.at(1) == missileCoords.at(1)){
        if(hitOrMiss){
          shipCoord.at(count).at(2) = "#";
        }
      }
      count++;
    }
  }
  

  Ship(int userX, string userY, int shipLength, string playerOr, string name, string userShipId){
    xCoord = userX;
    yCoord = userY;
    orientation = playerOr;
    length = shipLength;
    shipName = name;
    shipId = userShipId;
    if (name == "missed"){
      alive = false;
    }
    else{
      alive = true;
    }
    placed = true;
    generateCoords();
  }

  string getName(){return shipName;}
  bool getAlive(){return alive;}
  bool getPlaced(){return placed;}
  string getShipId(){return shipId;}
  vector<vector<string>> getShipCoord(){return shipCoord;}

};