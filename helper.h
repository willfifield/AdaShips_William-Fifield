using namespace std;

class Helper{
  public:
  

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


  

};