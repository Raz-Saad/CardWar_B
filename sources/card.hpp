#pragma once
#include <iostream>
using namespace std;
namespace ariel{
class Card{
    int value=0;//the number that are on the card
    string type="Diamonds";//the type of the card, Diamonds/Clubs/Hearts/Spades
    public:
        Card(){}
        Card(int value,string type);
        int GetValue();
        string GetType();
};
};