using namespace std;

class Ship{

  private:
  int xCoord;
  string yCoord;
  int length;
  string orientation;
  string shipName;
  bool alive;
  bool placed;
  vector<vector<string>> shipCoord;


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
    shipCoord.push_back(tempCoords);
    tempCoords.clear();

    for (int i = 1; i < length; i++){
      if (orientation == "V"){
        tempCoords.push_back(yCoord);
        tempCoords.push_back(to_string(xCoord+i));
        shipCoord.push_back(tempCoords);
        tempCoords.clear();
      }
      else{
        tempCoords.push_back(nth_letter((alphaToNum(yCoord)+i)));
        tempCoords.push_back(to_string(xCoord));
        shipCoord.push_back(tempCoords);
        tempCoords.clear();
      }
    }
  }

  Ship(int userX, string userY, int shipLength, string playerOr, string name){
    xCoord = userX;
    yCoord = userY;
    orientation = playerOr;
    length = shipLength;
    shipName = name;
    alive = true;
    placed = true;
    generateCoords();
  }

  string getName(){return shipName;}
  bool getAlive(){return alive;}
  bool getPlaced(){return placed;}

  vector<vector<string>> getShipCoord(){return shipCoord;}


};