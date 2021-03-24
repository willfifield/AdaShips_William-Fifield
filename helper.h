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

  //This is validating that an input is an allowed character
  bool isLetters(string input){
    for (int i = 0; i < input.size(); i++){
      int uppercaseChar = toupper(input[i]); //converting the character to upper case
      if (uppercaseChar < 'A' || uppercaseChar > 'Z'){ //if character is not A-Z
        return false;
      }
    }
    return true; //Return true if characters within A-Z
  }

  //This converts the input string to all uppercase, by iterating through the string
  string uppercaseConvert(string toConvert){
    string converted = toConvert;
    transform(converted.begin(), converted.end(), converted.begin(),[](unsigned char c){ return toupper(c);});
    return converted;
  }

  public:

  // This is a simple function used to switch between players. It is used multiple times in the project, as to why it is now in the helper class
  int opposite(int toSwap){
    if(toSwap==0){
      return 1;
    }
    return 0;
  }

  //collect X is self explanitory, validating the input int with the max/min size of the board
  int collectX(int xMax){
    bool inputCheck = false;
    int userChoice;
    do{
      cout << "\nPlease enter your X coordinates (1,2,3...): ";

      userChoice = userNumberInput();// This uses another class to validate that the input is a number

      if(userChoice >= 1 && userChoice <= xMax){
        inputCheck=true;
      }
      else{
        cout << "\nPlease enter a valid coordinate:";
      }
    }while (!inputCheck);
    return userChoice;
  }

  // collect Y is self explanitory again, validating the input string, ensuring it's within the min/max of the board
  string collectY(int yMax){
    bool inputCheck = false;
    string userChoice;
    do{
      cout << "\nPlease enter your Y coordinates (A,B,C...): ";

      cin.ignore();
      getline(cin,userChoice);
      userChoice = uppercaseConvert(userChoice);

      if(isLetters(uppercaseConvert(userChoice)) && alphaToNum(userChoice) >= 0 && alphaToNum(userChoice) <= yMax){
        inputCheck=true;
      }
      else{
        cout << "\nPlease enter a valid coordinate:";
      }
    }while (!inputCheck);
    return uppercaseConvert(userChoice);
  }

  // Again used multiple times in the code, this orientation selector has only 2 valid options, using similar methods as the "collectY"
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
  
  // A very simple clear screen method, allowing the user to see their board on the screen, with no clutter above
  void clearScreen(){
    cout << string( 100, '\n' );
  }

  // This print menu system is used throughout the project. It allows an list to be put in, and those being the options for the menu. This saves time printing each menu every time
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

  // Another simple method, turning the inputted string to an int. This uses ACSII
  int alphaToNum(string toConvert){
    int converted;
    for (unsigned int i = 0; i < toConvert.length(); i++)
    {
      converted = returnVal(toConvert[i]);
    }
    return converted;
  }


  // This is a generic int validator, allowing the user to only enter valid digits
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

  //This is an alphabet approach, again to be used more further along in the project. This is how the board Y axis is printed
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

  // Using "random_device", I'm able to get a random number. As this is used in different ways, the number it is between is inputted, allowing me to have the max range custom
  int generatePickedNumber(int maxNumber) {
    // generating random number based on random device
    random_device rdev;
    mt19937 rgen(rdev());
    // Distribute by defining a minimum number and max number.
    uniform_int_distribution<int> idist(1, maxNumber); //(inclusive, inclusive)
    return idist(rgen);
  }

  // Using the above method, this random generator allows the player to generate a coordinate using the board size
  int shipCoordGen(int max, int shipLength){
    int random;
    do{
      random = generatePickedNumber(max);// Going to the random function
    }while(random > (max-shipLength));
    return random;
  }

  // Even more simple, this method returns one of two options: Horizontal or Vertical, using the random method
  string randomOrientation(){
    int random = generatePickedNumber(2); // Using random method
    if(random == 1){return "H";}
    else {return "V";}
  }

  // This randon Y method is similar to the above, but converts the return using another method inside of this class
  string randomY(int maxNumber, int length){
    int random = shipCoordGen(maxNumber,length);// Using random method
    return nth_letter(random);// Using "to alphabet" method
  }

};