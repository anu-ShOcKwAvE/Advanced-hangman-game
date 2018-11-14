/*
My version of the HangMan(Guess the country) game.
Addition to the core hangman game this version has many functionalities:-
1)mechanism to give life by judging how long the countries name is.
2) An AntiCheat Mechanism against CheatEngine
3)No reduction of life for a repeated guess
-----------------------------------------------------------------------------------
*/

//hangman_v2.cpp
//Written by: Anu Panicker
//Insta: middle.finger.is.my.peace.sign

#include <iostream>
#include <vector>
#include <string>
#include <random> 
#include <ctime>

using namespace std;

string getCountry(); 
string getAstrick(int);
int getXtraLife(int);
bool getGuessAnalysis(bool,bool);
int antiCheat(int,int);

int main()
{
 cout<<"Lets play a game.\n";
 cout<<"I have guessed a country's name\n";
 cout<<"Try and guess the name correctly\n";
 cout<<"The country's name is currently represented using '*'s\n";
 cout<<"Try to unveil the letters behind the astricks\n\n";
 
 for(;;)
  {
  	
 string country{getCountry()}; 
 const int effectiveIndex{country.size()};
 country.resize(effectiveIndex);
 string astrick{getAstrick(effectiveIndex)}; 
 astrick.resize(effectiveIndex);
 
 int life{effectiveIndex+getXtraLife(effectiveIndex)}; 
 char guess;
 int guessNum{1};
 mt19937 mersenne(time(0));
 const int ac_Seed{mersenne()%2048+1024};
 int ac_Crypto{(ac_Seed+life)*(-1)}; 
 
 for(;life>0;) 
 {
 bool lifeDrain{true},rightGuess{false},wrongGuess{false}; 
 if(life==effectiveIndex+3){cout<<"You have a total of "<<life<<" lifes.\n";}
 else if(life<effectiveIndex+3){cout<<"You have "<<life<<" lifes remaining.\n";}
 cout<<"The country's name: "<<astrick;
 if(life>1){cout<<"\n#Guess: "<<guessNum;}
 else if(life==1){cout<<"\n#Final guess";}
 cout<<"\nGuess a letter: ";
 cin>>guess;
 cout<<"\n";
 ++guessNum;
 
 if (astrick.find(guess) != string::npos)
 {cout<<"ooops.That's a repeated guess.Don't worry you won't loss any life\n\n";} 
 else
 {
 for(int astrick_overwrite{0};astrick_overwrite<effectiveIndex;++astrick_overwrite)
 {
 if (guess==country.at(astrick_overwrite))
  {     
  astrick.at(astrick_overwrite)=country.at(astrick_overwrite);
    rightGuess=true;
  }
     else if (guess!=country.at(astrick_overwrite))
     {wrongGuess=true;} 
 }
 
 bool guessAnalysis{getGuessAnalysis(rightGuess,wrongGuess)};
 if(guessAnalysis){cout<<"ooops.Wrong Letter! Try again\n\n";}
  
 if(astrick.compare(country) == 0)
 {cout<<"CONGRATULATIONS.YOU WIN DEAR:)\n\n";break;} 
     else {
 if(lifeDrain){++ac_Crypto;}
 life=antiCheat(ac_Seed,ac_Crypto);
 }
 }
 if(life==0)
 {
 cout<<"Sorry to tell you its GAMEOVER for now:(\n"; 
 cout<<"The country was: "<<country<<"\n\n";
 }
 }
 if(life!=0||life==0)
 {
 for(;;)
  {
 cout<<"Do u wish to play again(y/n)?\n";
 char revenge;
 cin>>revenge;
 if(revenge=='y'){cout<<"\n\n";break;}
 else if (revenge=='n'){exit(0);}
 cout<<"\n";
  } 
    }
  }
}
string getCountry()
{
mt19937 mersenne(time(0)); 
vector <string> countries =
 {
"india","japan","china","america","europe","chile","egypt","butan",
"australia","cuba","russia","brazil","belize","panama","hungary","niger",
"armenia","yemen","england","france","germany","italy","israil",
"antigua","australia","srilanka"
 };
return(countries[mersenne()%(countries.size())+0]);
}

string getAstrick(const int effectiveIndex) 
{
	string charPermuter; charPermuter.replace(charPermuter.begin(),charPermuter.end(),effectiveIndex,'*');
    return charPermuter;
}

int getXtraLife(int effectiveIndex)
{
 if(effectiveIndex>0&&effectiveIndex<6){return 2;}
 else if(effectiveIndex>5&&effectiveIndex<10){return 3;}
 else if(effectiveIndex>9&&effectiveIndex<15){return 4;}
 else if(effectiveIndex>14&&effectiveIndex<20){return 5;}
}

bool getGuessAnalysis(bool rightGuess,bool wrongGuess)
{
 bool guessCheck{true};
 if(rightGuess==guessCheck&&wrongGuess==guessCheck){return false;}
 else if(rightGuess==guessCheck&&wrongGuess!=guessCheck){return false;}
 else if(rightGuess!=guessCheck&&wrongGuess==guessCheck){return true;}
}

int antiCheat(int ac_Seed,int ac_Crypto)
{
 int ac_Value{(ac_Crypto+ac_Seed)*(-1)};
 return ac_Value;
}