/*
This is the Ship Object.

Due to having multiple ships, an object would be best suited for this as it allows many to be created, with the same variables required. Inside of this class you will find the complete coordinates for the ship (due to length), along with other key variables, such as "alive" and "shipName"
*/

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

  // getDetails is a de-bugging function, allowing me to see this paricular ships key details
  void getDetails(){
    cout <<"\nUser X: " << xCoord << "\nUser Y: " << yCoord << "\nOrientation: " << orientation << "\nLength: " << length <<"\n";
    for(vector<string> coordx : shipCoord){
      for(string coordy : coordx){
        cout << coordy;
      }
      cout <<"\n";
    }
  }

  // This function is key for having the ship act as a ship, with the length of the ship in mind. Here we check which the orienation is, and place the following coordinates for that. Here we can go beyond the board limits, but it will be caught by the player create ship function.
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

  // Check destroyed is a main function to the game, checking the internal coordinates and making sure they haven't all been hit. If they have, the ship is no longer "alive", so it will set it's private variable to false
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

  // If a missile hits the ship, it replaces the id of that hit location with a hit marker, which can be displayed on the board. This marker allows us to count if the ship is destroyed or not
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
  
  // A ship initialization function, allowing external classes, like player, to create multiple instances of this class. This is key to this game as both player sides have multiple ships
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

  // Here are some standard getter functions. These are used to access the private variables of this class (such as shipCoord), and use that data for another funciton to test against
  string getName(){return shipName;}
  bool getAlive(){return alive;}
  bool getPlaced(){return placed;}
  string getShipId(){return shipId;}
  vector<vector<string>> getShipCoord(){return shipCoord;}

};