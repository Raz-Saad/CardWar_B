#include "card.hpp"
#include <iostream>
using namespace ariel;

Card::Card(int value,string type)
{//constructor of Card
    this->value=value;
    this->type=type;
}
//getters
int Card::GetValue()
{
    return value;
}

string Card::GetType()
{
    return type;
}

