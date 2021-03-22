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


  

};