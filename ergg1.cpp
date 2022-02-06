#include <iostream>
#include <time.h>
#include <string>
using namespace std;

/*
E -> (Y)
Y -> AB
A -> v
A -> E
B -> -Y
B -> +Y
B -> ε
*/

void E_production(string S);
void Y_production(string S);
void A_production(string S);
void B_production(string S);



int NonTerminal(string y)   //Finds the first Non-Terminal
{
    for (int i=0; i< y.length(); i++)
    {
        if (isupper(y[i]))
        { 
            return i;
        }
    }
    return 0;
}


bool FindNonTerm(string y)  //Finds if there is a Non-Terminal
{
    for (int i=0; i< y.length(); i++)
    {
        if (isupper(y[i]))
        { 
            return true;
        }
    }
    return false;
}


void E_production(string S)
{    
    if (S=="E")
    {    
        cout<< S + " -> ";
        S= "(Y)";
        cout<< S;
        
        Y_production(S);
    }
    else
    {
        S= S.replace(NonTerminal(S),1,"(Y)");   //Replace E with (Y)
        cout<< " -> " + S;
        
        Y_production(S);           
    }
    
}

void Y_production(string S)
{
    S= S.replace(NonTerminal(S),1,"AB");
    cout<< " -> " + S;

    A_production(S);       
}

void A_production(string S)
{
    switch(rand() % 2)  //Randomly chooses 'v' or 'E' 
    {
    case 0:    
        S= S.replace(NonTerminal(S),1,"v");
        cout<< " -> " + S;

        B_production(S);
    break;
    case 1:
        E_production(S);
    break;
    }
}

void B_production(string S)
{
    switch(rand() % 20)  //Uneven random, most likely to choose 'ε', so the program does not run forever
    {                   
    case 0:
        S= S.replace(NonTerminal(S),1,"-Y");
        cout<< " -> " + S;

        Y_production(S); 
    break;  
    case 1:
        S= S.replace(NonTerminal(S),1,"+Y");
        cout<< " -> " + S;
        
        Y_production(S);
    break;
    default:  //case 2,3,4,5...19
        S= S.replace(NonTerminal(S),1,"e"); //Print with ε
        cout<< " -> " + S;
        
        S.replace(S.find('e'),1,"");
        cout<< " -> " + S;   //Print w/o ε

        if (FindNonTerm(S) == true) B_production(S);    //If there is a Non terminal symbol, then it is B
    }
}



int main()
{
    srand(time(NULL));  //So it generates different randoms

    string S= "E";
    E_production(S);

    
    return 0;
};