/***********************************************************************
* Program:
*    Assignment #1d Password Strength Analyzer
*    Brother Helfrich, CS470
* Author:
*    Taylor Skinner
* Summary: 
*    Password strength analyzer
*    Uses a bit strength formula logbase2(alphabetsize^length)
*      Its in wikipedia password strength:random passwords
************************************************************************/

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include <cmath>

using namespace std;

/************************************************************************
 * Prompt for password
 ************************************************************************/
string getPassword()
{
   string password;
   cout << "Please enter the password: ";
   cin >> password;
   return password;
}

/************************************************************************
 * Determine the size of the passwords alphabet
 ************************************************************************/
int getAlphaSize(string &password)
{
   int len = password.length();
   const char * c = password.c_str();
   int num = 0;
   int alpha[] = {0, 26, 26, 52, 10, 36, 36, 62, // possible alphabet sizes
                  32, 58, 58, 84, 42, 68, 68, 94};  
   for (int i = 0; i < len; i++, c++)
   {
      if (isupper(*c))// Uppercase Letter
      {
         num = num | 1; // 26
      }
      else if (islower(*c)) // Lower case Letter
      {
         num = num | 2; // 26
      }
      else if (isdigit(*c)) // Number
      {
         num = num | 4; // 10
      }
      else 
      {
         num = num | 8; // 32   // Other symbol
      }
   } 
   return alpha[num];
}

/************************************************************************
 * Compute number of all possible passwords given alphabet size and length
 ************************************************************************/
long getNumberOfCombos(int length, int alpha) 
{                                      
   return pow(alpha, length);  // alpabetsize^length
}

/************************************************************************
 * Compute bit strength of password
 ************************************************************************/
int getBitStrength(long long combos)
{
   return (floor(log10(combos)/log10(2))); // floor of logbase 2 of numCombos
}

/************************************************************************
 * Display results
 ************************************************************************/
void display(long long combos, int strength)
{
   cout << "There are " << combos << " combinations" << endl;
   cout << "That is equivalent to a key of " << strength << " bits" << endl;
}

/************************************************************************
 * Main - he runs things around here
 ************************************************************************/
int main()
{
   string password = getPassword();
   int alphaSize = getAlphaSize(password);
   assert(alphaSize != 0); // should never be zero
   long long numCombos = getNumberOfCombos(password.length(), alphaSize);
   int strength = getBitStrength(numCombos);
   display(numCombos, strength);
   return 0;
}

