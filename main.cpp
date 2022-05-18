#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <limits>

using namespace std;

//Changes since last iteration. I was able to successfully read in the new line by resetting the
//string that is going to be passed in when the function is called in the main. When comparing the
//string to the keyword list I also predefined the size larger than needed to be able to add more
//keywords in the future. Instead of comparing the characters that are being read in to the notkeyword
//address I compared the characters to the actual character being looked for, that way there are no bugs
//if the notkeyword is expanded. I also removed some holder variables that didnt need to be assigned when iterating through
//the loop.




//Since this is a lexical analyzer and my main objective is to read a file line by line,
//im going to specify what is a key word and what is not. Below are not keywords *important* including spaces
//One fix that I made from the initial submission was instead of looking for things by address of the list, I used the ' ! ' to look for the specific character.
//This would eliminate any potential problem of adding new characters to the list and changing the address location.

char notKeywordsSeps[22] =
{
  '-','=','*','+','/','>','<','(','\'','%',')','{','}','[',']',',','.',':',';','!',' ', '"'
};

string importantKeywords[20]={"input", "else", "if", "bool", "float", "while", "do", "then", "for", "function", "doend", "whileend", "and", "or" , "do ", "break", "int", "forend", "output","not"};

//After stating what is going to be looked for within the input file that will be implemented with fstream, now its time to implement the functions
//that will actually be comparing where the iterator is at, to each of these non keywords and keywords




//function prototpes that will be used later in the program
void displaythecharacters(char ch);
void displaytheposition(string holder);
int testing(char kar, int currplace);

//Vector is global so it can be used and accessed wherever in the program, I used a vector specifically because its easy to iterate through and I dont
//have a predefined size for the characters that are being read from the inputfile.
vector <pair <string, string> > output;

//first function made to test the every line of the text file, first testing if it is a alphabetic character and placing it within the Matrix,
//if not a character than a digit is tested. Also is testing specifically if the character is a exclamation point for comments, and for a blank or white space.


int Matrix[6][7] = {1,2,4,0,0,0,0,  1,1,4,0,0,0,0,  5,2,4,0,3,0,0,  5,3,4,0,5,0,0,  4,4,0,4,4,4,4,  0,0,0,0,0,0,0,};

//The matrix is used for a finate state machine.. it works similar to the vending machine diagram given in class, with the digits from 0-5
//corressponding to whether the character is a digit.. comment.. letter.. or to initiate and start it. Diagram available in the documentation.

//this function is displaying the current position of each character (integer, identifier) after being tested. More importantly it is taking every line read, creating
//a temporary variable to pass in, and pushing it into the vector.
void displaytheposition(string holder)
{


   if (holder != "")

   {

    //If the sized array increment or decrements than this loop has to also increase
    //or decrease, because the holder that is being passed into the function, after reading
    //the file, is being compared to the keyword list.

    for (int i = 0; i < 25; i++)
   {

     if (holder == importantKeywords[i])
     {
       output.push_back(pair<string, string>("Keyword:        ", holder));
       return;
     }
  }


    //If the holder is not a
    if (isalpha(holder[0]))
    {
      output.push_back(pair<string, string>("Identifier:      ", holder));
      return;
    }


      if (isdigit(holder[0]))
      {

        output.push_back(pair<string, string>("Integer:        ",holder));
         return;

      }

  }

}


//}
//this is specifically displaying the characters that fall under the operator and separator category.
void displaythecharacters (char character)
{
  //Notice instead of having to search through the full list I specifically set it to only look for seperators and operators at the index they begin and end at
  string hold = string(1, character);

  for (int i = 0; i < 8; i++)
  {
    if (character == notKeywordsSeps[i])
    {
      output.push_back(pair<string, string>("Operator:       ", hold));
    }
  }

  for (int i = 8; i <22; i ++)
  {
    if ( !isspace (character) && character != '!' && character == notKeywordsSeps[i])
    {
      output.push_back(pair<string, string>("Separator:       ", hold));
    }
  }
}


int testing( char character , int currplace)
{
 int currState = currplace;



 if (isalpha(character))
 {
     currState = Matrix[currState][0];


     return currState;

 }


 else if ( character == '$' || isdigit(character) )
 {
   currState = Matrix[currState][1];



   return currState;
 }

 //instead of finding the specific parameter in the list, I set it equal to a specific character
 //this will not crash the program if a user enters a new character in the list.
 else if (character == '!')
 {
   currState = Matrix[currState][2];
   return currState;
 }


 else if ( character == '$' || isdigit(character) )
 {
   currState = Matrix[currState][1];




   return currState;
 }


 else if (isspace(character))
 {
   currState = Matrix[currState][6];
 }

//Trying to find a specific character instead of a index in a list
 else if (character == ']')
 {
   currState = Matrix[currState][4];
   return currState;
 }

 else
 {
   int z = 0;

   for (z=0;z<8;z++)
   {
     if ( isspace(character) || character == notKeywordsSeps[z])
     {
       currState = Matrix[currState][5];
       return currState;
     }
   }
   for (z=8;z<22;z++)
   {
     if (isspace(character) || character == notKeywordsSeps[z] )
     {
       currState = Matrix[currState][3];
       return currState;
     }
   }
 }

}




int main ()
{
  //temporary variables that will be used when reading in from file and going to used to place information into vector
  char character;
  string fileinputed;
  int totalLength = 0;
  int currState = 0;
  string temporary;
  string blank = "";

  cout << "Enter one of the three txt files that will be tested: ";

  cin >> fileinputed;
  //both of the stream objects for the input and output
  string fileoutput = "outputfile.txt";
  ifstream inFile(fileinputed);
  ofstream outFile(fileoutput);

  //condition made to check if any error is made when entering the inputed file.
  if(!inFile.is_open())
  {
    cout << "File was not detected, enter a valid file from the directory " << endl;
    return 1;
  }


  cout << "Testing has successfully begun " << endl << endl << endl;
  cout << "Token    Result  " << endl << "........................" << endl << endl;


  while (getline(inFile,blank))
  {

    for (int i = 0; i < blank.length(); i++)
    {

      character = blank[i];

      if (currState != 4)

      {

        currState = testing(character, currState);
        switch(currState)
        {
         case 0:
               displaytheposition(temporary);
               displaythecharacters(character);
               temporary = "";
               break;
         case 1:
               temporary += character;
               break;
         case 2:
               temporary += character;
               break;
         case 3:
               temporary += character;
               break;
         case 4:
               displaytheposition(temporary);
               temporary = "";
               break;
         case 5:
               displaytheposition(temporary);
               displaythecharacters(character);
               temporary = "";
               break;

        }
      }

      else if (currState == 4 && character == '!' )
      {
        currState = Matrix[currState][2];
      }


    }
    displaytheposition(temporary);
    temporary = "";
  }



    cout << endl;




    for (int i = 0; i < output.size(); i++)
    {
      cout << output[i].first << "         " << output[i].second << endl;

    }




    for(int z = 0; z < output.size(); z++)
    {
      outFile << output[z].first << "          " << output[z].second << endl;
    }

    cout << endl << endl;
    inFile.close();
    outFile.close();

    cout << endl << endl;
    cout << "The final product has been printed out in th outputfile.txt the process has ended successfully " << endl;




  }
