# AdaShips | William Fifield
An Assignment to recreate the classic Battleships game, through the console.

In this code base is the classic battleships game, with additional work done towards higher grade boundaries. Overall this is to be completed for the "Advanced Programming" module.

github: https://github.com/willfifield/AdaShips_William-Fifield

replit: https://replit.com/@willfifield/AdaShipsWilliam-Fifield

Inside of this program you will see an object-oriented approach to the problem. Using multiple players, with multiple ships and boards. This is best done using an object-oriented approach for code reusability and efficiency.


# Challenge Outline

This assignment comes with many challenges, and through taking a planned and structured approach I will be able to build this project gradually, with small OOP methods, to reeach the desired outcome. Using objects will be key to a satisfactory development, as there are many elemets in this game that need to be repeated such as: the players, the boards, and the ships. Each of these together build the foundation of the game, along with helper methods, menu systems and imported libraries along the way.

Below is a breakdown of the general plan of development, including a breakdown of the tasks in an agile manner, a UML diagram to give me some structure of what the project classes should look like, and a work plan to help build an understanding of overall objectives per stage in this projects development.
- [x] Written summary and review of the problem
- [x] UML style diagram for initial solution
- [x] Written work plan, with approach & development strategy
- [x] Breakdown above plan into storys/epics for object-oriented designs

# UML
Please follow the link below to see the mock design UML for the project. This gives a bried understanding of what needs to be created within the object-oriented project.

https://docs.google.com/drawings/d/1H_1S100Jxa762ZXFiUBqWA2gCyhnFs1ICksuH77g2ao/edit?usp=sharing

An updated UML is posted below, allowing the whole project to be seen in this way. This detail UML diagram includes the whole project in greater detail.

https://drive.google.com/file/d/1Or53_4oIGGS_oCJcN9_8N7WlzYXksh0Q/view?usp=sharing

# Work Plan

Inside of this work plan you will find what methods I will be using to develop my project, and what sort of structure I will take when completing these larger tasks.

**Development Approach**
Breaking down each task is key to building a project gradually. Using the correct plan will allow for steady development, and for later tasks to be easier to complete. At this stage, quality and robustness is key, as we hope to not come back to this code later in development. Forward thinking will allow me to build my software in a clear, concise, and effective manner.

Below the workplan you can see the breakdown of the tasks to complete. Inside of here are greater headings, with smaller tasks within them. This layered approach will allow me to work through this list, and end with a final working project.

**Completion Quality & Completion**
Throughout the development stage, there will always be forward thinking. I am taking this approach as it will help in the later tasks, allowing for more efficient development. After each stage I will go back and refactor any code that requires it, keeping repeating lines to a bare minimum (in most cases can be removed entirely). This quality and completion approach will give me confidence that I can use repeated classes later on, and not have to worry about validating the outcome, or refactoring too much code agin.

Due to working towards an assignment brief, having this document open and checked at this stage will allow me to only use this readme as a reference, and to ensure I fully understand what the brief is asking me to do. 



# Breakdown of Tasks to complete
This is the breakkdown and plan of how I will take on this project. I have broken tasks down into steps, of which when fully completed there will be a working game.

This approach allows me to further think, such as input validation, as these elemts will be used multiple times within the project.

- [x] **Main Menu System**
  - [x] Create a main-menu system
    -  [x] One Player VS Computer
    -  [x] Two Player Game
    -  [ ] One Player VS Computer (salvo)
    -  [ ] Two player game (salvo)
    -  [ ] One player v computer (hidden mines)
    -  [ ] Two player game (hidden mines)
    -  [ ] Computer v computer (hidden mines)
  - [x] Going to further sub-menu
  - [x] Create new menu system now with turn based prompts


- [x] **File Intergration**
  - [x] Pull in data from .ini file, as a cofiguration for the whole game
    - [x] Store this list for objects to use as reference


- [x] **User Interaction**
  - [x] Create a number input system that verifies the users response (check validation)
  - [x] Create a character input system for further validation


- [x] **Validation**
  - [x] Create new ship based on the users input coordinates
      - [x]  Validate that the users ship does not overlap a current ship/go off the board
  - [x] Create a random x and y chooser for the computer player / auto place function
    - [x] Use the same validation for when placing ships, not allowing overlaps/off board etc
  - [x] Impliment the auto-place function for the AI player


- [x] **Board Mapping**
  - [x] ~~User a map (map[[0,0],[0,0]]) to build and print out a boards~~
    -  Later updated for better memory storage capabilities


- [x] **Gameplay**
  - [x] Print both the board to attack, and my own board
  - [x] Collect another coordinate from the users
    - [x] Validate this coordinate to see if it's already hit. Loop if failing
  - [x] Have the fired shot effect the ship location
  - [x] Notify if this is a hit or a miss, printing this within the of the other players board (where you're shooting)
  - [x] Have an auto-fire option using the auto-select function
    - [x] Validate again to ensure shots are not wasted on the same already shot at location
  - [x] Notify where the user has been shot, through their board
  - [x] Have options to "quit game" and "end turn"
  - [x] After every turn check if all ships have been destroyed 
    - [x] If yes, end the game with the winner being shown on the screen
    - [x] If no, repeat the turn based game until this criteria is filled
  - [x] Run through computers/player 2's turn, using auto-generated missiles for the computer, and the same output if the 2nd player is a real person
  - [x] Go back to main-menu when game is complete.
- [ ] **Salvo Gameplay**
  - [ ] Using the same gameplay method from above, count the players active ships and allow them to shoot the amount of missiles for the amount of active ships
  - [ ] If the player looses a ship, then decrease teh amount of missiles allowed
- [ ] **Hidden Mines Gameplay**
  - [ ] Allow randomly generated mines to spawn on the player board
  - [ ] If hit, it will destroy not only the coordinate chosen, but the 8 surrounding it also.
  - [ ] **Computer vs Computer Gameplay**
    - [ ] Under the hidden mines gameplay is this computer vs computer game, allowing both players to be computers, using the auto-function for each input

# Final Housekeeping
- [x] Refactor code, ensuring there is no duplicate. 
  - [x] If there is duplicate, see where it is best to be stored, and use OOP functionality.
- [x] Remove any "code smells", ensuring code is easy and efficient
- [x] Ensure the code is well commented, explaining what classes/functions/code does within the software. Make it readable, as if a document were to be made from it and you can understand the whole project through this C++ comment doc.