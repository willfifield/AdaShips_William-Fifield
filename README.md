# AdaShips | William Fifield
An Assignment to recreate the classic Battleships game, through the console.

In this code base is the classic battleships game, with additional work done towards higher grade boundaries. Overall this is to be completed for the "Advanced Programming" module.

github: https://github.com/willfifield/AdaShips_William-Fifield

Inside of this program you will see an object-oriented approach to the problem. Using multiple players, with multiple ships and boards. This is best done using an object-oriented approach for code reusability and efficiency.


# Challenge Outline
- [x] Written summary and review of the problem
- [x] UML style diagram for initial solution
- [x] Written work plan, with approach & development strategy
- [x] Breakdown above plan into storys/epics for object-oriented designs

# UML
Please follow the link below to see the mock design UML for the project. This gives a bried understanding of what needs to be created within the object-oriented project.

https://docs.google.com/drawings/d/1H_1S100Jxa762ZXFiUBqWA2gCyhnFs1ICksuH77g2ao/edit?usp=sharing

An updated UML will be published here when the project is complete. This will allow the whole project to be seen in this way. 



# Breakdown of Tasks to complete - Work Plan
This is the breakkdown and plan of how I will take on this project. I have broken tasks down into steps, of which when fully completed there will be a working game.

This approach allows me to further think, such as input validation, as these elemts will be used multiple times within the project.

- [x] Create a main-menu system
  - [x] going to sub-menu
- [x] ~~User a map (map[[0,0],[0,0]]) to build and print out a boards~~
  -  Later updated for better memory storage capabilities
- [x] Pull in data from .ini file, as a cofiguration for the whole game
  - [x] Store this list for objects to use as reference
- [x] Create a number input system that verifies the users response (check validation)
- [x] Create a character input system for further validation
- [x] Create new ship based on the users input coordinates
  - [x]  Validate that the users ship does not overlap a current ship/go off the board
- [x] Create a random x and y chooser for the computer player / auto place function
  - [x] Use the same validation for when placing ships, not allowing overlaps/off board etc
- [x] Impliment the auto-place function for the AI player
- [x] Create new menu system now with turn based prompts
- [x] Print both the board to attack, and my own board
- [x] Collect another coordinate from the users
  - [x] Validate this coordinate to see if it's already hit. Loop if failing
- [x] Have the fired shot effect the ship location
- [ ] Notify if this is a hit or a miss, printing this within the of the other players board (where you're shooting)
- [ ] Have an auto-fire option using the auto-select function
  - [ ] Validate again to ensure shots are not wasted on the same already shot at location
- [ ] Notify where the user has been shot, through their board
- [ ] Have options to "quit game" and "end turn".
- [ ] After every turn check if all ships have been destroyed 
  - [ ] If yes, end the game with the winner being shown on the screen
  - [ ] If no, repeat the turn based game until this criteria is filled.
- [ ] Go back to main-menu when game is complete.

# Housekeeping
- [ ] Refactor code, ensuring there is no duplicate. 
  - [ ] If there is duplicate, see where it is best to be stored, and use OOP functionality.
- [ ] Remove any "code smells", ensuring code is easy and efficient
- [ ] Ensure the code is well commented, explaining what classes/functions/code does within the software. Make it readable, as if a document were to be made from it and you can understand the whole project through this C++ comment doc.