// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(string word, int wordSize, string userGuess, set<string> dict, std::string floating, std::string floatingCopy, int dashes, set<string>& possibleAnswers);
bool containsFloatingChars (std::string userGuess, std::string floatingChars);
void constraintCheck(std::string possibleWord, std::string floatingChars, std::set<std::string> dict, std::set<std::string> &answers);  


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  int dashes =0;
  for (int i=0; i<in.size(); i++){
    if (in[i] == '-'){
      dashes++;
    }
  }
  std::set<std::string> possibleAnswers; //set of possible answers to the wordle based off user's guess & floating char
  wordleHelper("", in.size(), in, dict, floating, floating, dashes, possibleAnswers);
  return possibleAnswers;
}

// Define any helper functions here

void wordleHelper(string word, int wordSize, string userGuess, set<string> dict, std::string floating, std::string floatingCopy, int dashes, set<string>& possibleAnswers)
{
  if(word.size() == wordSize ){//base case: combination has reached approriate length
    floatingCopy = floating; //reset floating; //change the actual floatingCopy for next recursions...
    constraintCheck(word, floating, dict, possibleAnswers);
    return;
  }    
  else { //n length not reached, continue appending letters

    if (userGuess[word.size()] != '-'){ //at this current element, there is a fixed letter
    word += userGuess[word.size()]; 
    wordleHelper(word, wordSize, userGuess, dict, floating, floatingCopy, dashes, possibleAnswers);
    }
    else { //no fixed letter at this element
      if (floatingCopy.size() > dashes ) { //can't possibily be a valid guess
        return;
      }
      else { //still could be a valid guess
        dashes--;
        for(char i= 'a'; i <= 'z'; i++){
          if (floatingCopy.find(i) != std::string::npos){//this letter i is one of the floating chars
            floatingCopy.erase(floatingCopy.find(i),1); //remove this letter from the floating string since we are now accounting for it
            }
          if (containsFloatingChars(word, floatingCopy)){
          }else {
            if (floatingCopy.size() > dashes ) { //there are more floating chracters, but no open indicies for them-- cant be valid
            continue;
            }
          }
          wordleHelper(word+i,wordSize, userGuess, dict, floating, floatingCopy, dashes, possibleAnswers); //attaches b to a 
          floatingCopy = floating; //reset floating copy for next iteration
        }  
      }
    } //end of else "no fixed letter at this element"
  }
  return;
}

bool containsFloatingChars (std::string userGuess, std::string floatingChars)
{
  bool containsFloatingChars = true;
  for (int i=0; i< floatingChars.size(); i++){ //checking if generated word contains all floating characters 
    if (userGuess.find( floatingChars[i] ) == std::string::npos){ //this floating char is NOT in the generated word 
      containsFloatingChars = false;
    }
  }
  return containsFloatingChars; //returns true if all the floating chars are in the string, and false if not.
}

void constraintCheck(std::string possibleWord, std::string floatingChars, std::set<std::string> dict, std::set<std::string>& answers)
{
  
    if (containsFloatingChars(possibleWord, floatingChars) ){ //if string contains all floating chars
    if (dict.find(possibleWord) != dict.end() ){ //if string is a valid English word
      answers.insert(possibleWord); //then add it to possible answers 
    }
  }
}


