/*************************************************
 ** File: proj1.cpp
 ** Project: CMSC 202 Project 1, Winter 2019
 ** Author: Steven Ryan
 ** Date: 2/18/19
 ** Lab Section 12. Lecture section 11
 ** E-mail: sryan6@umbc.edu
 **
 ** This project will be implementing a system
 ** to display ASCII art and create ASCII art
 ** all in one program.
 *************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

const int ARRAY_SIZE = 75;
const int EXIT_VALUE = 6;
const int FIRST_OPTION = 1;
const int SECOND_OPTION = 2;

//Function Prototypes:
void displayMenu();
int validateInput(int choice, int minVal, int maxVal);
void loadFile(char array[ARRAY_SIZE][ARRAY_SIZE]);
void displayArt(char array[ARRAY_SIZE][ARRAY_SIZE]);
void rotateImage(char array[ARRAY_SIZE][ARRAY_SIZE]);
void createImage(char array[ARRAY_SIZE][ARRAY_SIZE]);
void invertImage(char array[ARRAY_SIZE][ARRAY_SIZE]);

int main(){


  //determines what the user will do
  int choice;
  //The coordinate plane that the ASCII goes on
  char plane[ARRAY_SIZE][ARRAY_SIZE] = {};

  //Welcomes user
  cout << "Welcome to the ASCII Art Tool" << endl;
  displayMenu();
  
  cin >> choice;
  //Validates input by prompting again if proper input is not entered
  while(((choice < FIRST_OPTION) || (choice > SECOND_OPTION)) && choice != EXIT_VALUE){
    cout << "\nPlease load your ASCII art from a file" << endl;
    cout << "or create your own to start." << endl;
    displayMenu();
    cin >> choice;
  }
  //Only stops promping the user to do something if exit is chosen
  while(choice != EXIT_VALUE){
    //makes decisions based on the choice
    switch(choice){
    //Loads the ASCII Art from a file  
    case 1:
      loadFile(plane);
      displayMenu();
      cin >> choice;
      choice = validateInput(choice, FIRST_OPTION, EXIT_VALUE);
      break;
    //Allows the user to create the art manually
    case 2:
      createImage(plane);
      displayMenu();
      cin >> choice;
      choice = validateInput(choice, FIRST_OPTION, EXIT_VALUE);
      break;
    //prints out the array with the art
    case 3:
      displayArt(plane);
      displayMenu();
      cin >> choice;
      choice = validateInput(choice, FIRST_OPTION, EXIT_VALUE);
      break;
    //rotates the art
    case 4:
      rotateImage(plane);
      displayMenu();
      cin >> choice;
      choice = validateInput(choice, FIRST_OPTION, EXIT_VALUE);
      break;
    //inverts the art horizontally or vertically
    case 5:
      invertImage(plane);
      displayMenu();
      cin >> choice;
      choice = validateInput(choice, FIRST_OPTION, EXIT_VALUE);
      break;
    //exits the program
    case 6:
      choice = EXIT_VALUE;
      break;
    }
  }
  
  return 0;
}

//-------------------------------------------------
// Name: displayMenu
// Precondition: None
// PostCondition: Prints out the menu
//-------------------------------------------------
void displayMenu(){
  cout << "What would you like to do?" << endl;
  cout << "1. Load ASCII Art from File" << endl;
  cout << "2. Create ASCII Art Manually" << endl;
  cout << "3. Display Art" << endl;
  cout << "4. Rotate Art" << endl;
  cout << "5. Invert Art" << endl;
  cout << "6. Exit" << endl;
}

//------------------------------------------------
// Name: validateInput
// Precondition: Must recieve an integer choice to
// be tested for validity as an option with the
// minimum and maximum value to validate with.
// PostCondition: Returns the validated value for
// choice
//------------------------------------------------
int validateInput(int choice, int minVal, int maxVal){
  // Validates whether the choice made is within
  // the bounds
  while((choice < minVal) || (choice > maxVal)){
    cout << "That's not a valid option. " << endl;
    cout << "Please pick an option from " << minVal
	 << "-" << maxVal << endl;
    displayMenu();
    cin >> choice;
  }
  return choice;
}

//------------------------------------------------
// Name: loadFile
// Precondition: Must have the 2d array passed in
// to give the ASCII Art.
// Postcondition: Updates Array to include the
// art loaded.
//------------------------------------------------
void loadFile(char array[ARRAY_SIZE][ARRAY_SIZE]){
  char fileName[ARRAY_SIZE];
  int xCoord;
  int yCoord;
  char asciiChar;
  cout << "What is the name of the data file to import? " << endl;
  //peeks to interface with getline in order to
  //get rid of the escape sequence in the input
  //buffer.
  if(cin.peek() == '\n'){
    cin.ignore();
  }
  cin.getline(fileName, ARRAY_SIZE);
  ifstream inputFile(fileName);
  //checks to see if the file opened properly
  if(inputFile.is_open()){
    //fills the array with values from the files
    while(inputFile >> xCoord){
      inputFile >> yCoord;
      inputFile >> asciiChar;
      array[xCoord][yCoord] = asciiChar;
    }
    cout << "Done\n";
  }
  //If the file cannot be opens, responds with
  //an error message
  else{
    cerr << "File is unable to be opened.\n";
  }
  inputFile.close();
}

//-----------------------------------------------
// Name: displayArt
// Precondition: Needs to be sent a 2d array of
// Ascii Art of size 75x75 to print
// Postcondition: prints out the art
//-----------------------------------------------
void displayArt(char array[ARRAY_SIZE][ARRAY_SIZE]){
  //prints out the ascii in the array
  for(int i = 0; i < ARRAY_SIZE; i++){
    for(int u = 0; u < ARRAY_SIZE; u++){
      //turns null values into spaces
      if(array[i][u] == 0){
	cout << " ";
      }
      else{
	cout << array[i][u];
      }
    }
    cout << "\n";
  }
}
//-----------------------------------------------
// Name: rotateImage
// Precondition: Must be passed a 2d array with
// a length of 75 and ASCII art within it to
// rotate clockwise.
// Postcondition: Updates the array to move all
// the ASCII into a clockwise position
//-----------------------------------------------
void rotateImage(char array[ARRAY_SIZE][ARRAY_SIZE]){
  char placeholderArray[ARRAY_SIZE][ARRAY_SIZE] = {};
  //uses a placeholder array to transfer values into
  //their rotated position.
  for(int i = 0; i < ARRAY_SIZE; i++){
    for(int u = 0; u < ARRAY_SIZE; u++){
      placeholderArray[u][ARRAY_SIZE - i - 1] = array[i][u];
      array[i][u] = ' ';
    }
  }
  for(int i = 0; i < ARRAY_SIZE; i++){
    for(int u = 0; u < ARRAY_SIZE; u++){
      array[i][u] = placeholderArray[i][u];
    }
  }
}
//-----------------------------------------------
// Name: createImage
// Precondition: Must be sent the array to add to
// Postcondition: Updates the array with user
// input.
//-----------------------------------------------
void createImage(char array[ARRAY_SIZE][ARRAY_SIZE]){
  int xCoord;
  int yCoord;
  char pixel;
  cout << "This will modify the current art" << endl;
  cout << "Enter the x coordinate between 0 and 74" << endl;
  cin >> xCoord;
  //validates input
  while((xCoord < 0) || (xCoord > 74)){
    cout << "Please choose a valid coordinate between 0 and 74" << endl;
    cin >> xCoord;
  }
  cout << "Enter the y coordinate between 0 and 74" << endl;
  cin >> yCoord;
  //validates input
  while((yCoord < 0) || (yCoord > 74)){
    cout << "Please choose a valid coordinate between 0 and 74" << endl;
    cin >> yCoord;
  }
  cout << "Enter the character for that location: " << endl;
  cin >> pixel;
  //places the pixel that the user inputs.
  array[xCoord][yCoord] = pixel;
}
//-----------------------------------------------
// Name: invertImage
// Precondition: Must be sent the 2d array being
// modified.
// Postcondition: Based on the user's input, it
// inverts the image horizontally or vertically.
//-----------------------------------------------
void invertImage(char array[ARRAY_SIZE][ARRAY_SIZE]){
  cout << "Would you like to invert it horizontally or vertically?" << endl;
  cout << "1. Vertical" << endl;
  cout << "2. Horizontal" << endl;
  int invertChoice;
  char placeholderArray[ARRAY_SIZE][ARRAY_SIZE] = {};
  cin >> invertChoice;
  //validates input
  while((invertChoice < FIRST_OPTION) || (invertChoice > SECOND_OPTION)){
    cout << "Please choose a valid option 1-2" << endl;
    cin >> invertChoice;
  }
  //to invert the image vertically, it is rotated twice
  if(invertChoice == FIRST_OPTION){
    rotateImage(array);
    rotateImage(array);
  }
  //to invert the image horizontally, a placeholder array
  //is used to place each ascii character in a mirrored
  //position.
  else if(invertChoice == SECOND_OPTION){
    for(int i = 0; i < ARRAY_SIZE; i++){
      for(int u = 0; u < ARRAY_SIZE; u++){
	placeholderArray[i][u] = array[i][ARRAY_SIZE - u];
      }
    }
    for(int i = 0; i < ARRAY_SIZE; i++){
      for(int u = 0; u < ARRAY_SIZE; u++){
	array[i][u] = placeholderArray[i][u];
      }
    }
  }
}
