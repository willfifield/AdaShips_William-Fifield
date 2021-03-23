/*
This is a public helper class.

Inside of this class you will see generic code being passed through. The use of this class is to enable code to be reused in a good fashion, and not to have any duplicate code.
*/
using namespace std;

class Helper{
  private:

  int returnVal(char x)
    {
      return (int)x - 64;
    }

  bool isLetters(string input){
    for (int i = 0; i < input.size(); i++){
      int uppercaseChar = toupper(input[i]); //converting the character to upper case
      if (uppercaseChar < 'A' || uppercaseChar > 'Z'){ //if character is not A-Z
        return false;
      }
    }
    return true; //Return true if characters within A-Z
  }

  string uppercaseConvert(string toConvert){
    string converted = toConvert;
    transform(converted.begin(), converted.end(), converted.begin(),[](unsigned char c){ return toupper(c);});
    return converted;
  }

  public:

  int collectX(int xMax){
    bool inputCheck = false;
    int userChoice;
    do{
      cout << "\nPlease enter your X coordinates (1,2,3...): ";

      userChoice = userNumberInput();

      if(userChoice >= 1 && userChoice <= xMax){
        inputCheck=true;
      }
      else{
        cout << "\nPlease enter a valid coordinate:";
      }
    }while (!inputCheck);
    return userChoice;
  }

  string collectY(int yMax){
    bool inputCheck = false;
    string userChoice;
    do{
      cout << "\nPlease enter your Y coordinates (A,B,C...): ";

      cin.ignore();
      getline(cin,userChoice);

      if(isLetters(userChoice) && alphaToNum(userChoice) >= 0 && alphaToNum(userChoice) <= yMax){
        inputCheck=true;
      }
      else{
        cout << "\nPlease enter a valid coordinate:";
      }
    }while (!inputCheck);
    return uppercaseConvert(userChoice);
  }

  string collectOr(){
    bool inputCheck = false;
    string userChoice;
    do{
      cout << "\nPlease enter your Orientation Horizontal/Vertical (H / V): ";

      getline(cin,userChoice);
      cout <<userChoice;
      userChoice = uppercaseConvert(userChoice);

      if(isLetters(userChoice) && (userChoice == "H" || userChoice == "V")){
        inputCheck=true;
      }
      else{
        cout << "\nPlease enter a valid orientation:";
      }
    }while (!inputCheck);
    return userChoice;
  }

  void clearScreen(){
    cout << string( 100, '\n' );
  }

  void printMenu(vector<string> choices){
    cout << "\n\nPlease enter one of the options below:\n";
    int count = 1;
    for (string choice : choices){
      if (choice == "Quit" || choice == "Back"){
        cout <<"0: " << choice << "\n";
      }
      else{
        cout <<count << ": " << choice << "\n";
      count++;
      }
    }
  }

  int alphaToNum(string toConvert){
    int converted;
    for (unsigned int i = 0; i < toConvert.length(); i++)
    {
      converted = returnVal(toConvert[i]);
    }
    return converted;
  }

  int userNumberInput(){
    int userChoice;
    bool inputCheck = false;
    do{
      cin.clear();
      if (cin >> userChoice){
        inputCheck = true;
        break;
      }
      else{
        cout <<"\nPlease enter a valid digit:\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
    }while(!inputCheck);
    return userChoice;
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

  int generatePickedNumber(int maxNumber) {
  // generating random number based on random device
  random_device rdev;
  mt19937 rgen(rdev());
  // Distribute by defining a minimum number and max number.
  uniform_int_distribution<int> idist(1, maxNumber); //(inclusive, inclusive)
  return idist(rgen);
  }

  int shipCoordGen(int max, int shipLength){
    int random;
    do{
      random = generatePickedNumber(max);
    }while(random > (max-shipLength));
    return random;
  }

  string randomOrientation(){
    int random = generatePickedNumber(2);
    if(random == 1){return "H";}
    else {return "V";}
  }

  string randomY(int maxNumber, int length){
    int random = shipCoordGen(maxNumber,length);
    return nth_letter(random);
  }

};