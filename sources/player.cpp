
#include <iostream>
#include <array>
#include "player.hpp"
using namespace std;
using namespace ariel;
static constexpr int amount_of_cards=26;

Player::Player(string name)
{//constructor of player
    this->name=name;
}

int Player::stacksize()
{//how many cards left in the stack
    return cards_counter;
}

int Player::cardesTaken()
{//how many cards the player won
    return cards_won_counter;
}

//getters and setters
string Player::getName()
{//the name of the player
    return name;
}

size_t Player::Get_Cards_Deck_Index()
{
    return cards_deck_index;
}

int Player::Get_Cards_Counter()
{
    return cards_counter;
}

int Player::Get_Cards_Won_Counter()
{
    return cards_won_counter;
}

void Player::Set_Cards_Deck_Index(size_t num)
{
    cards_deck_index=num;
}

void Player::Set_Cards_Counter(int num)
{
    cards_counter=num;
}
void Player::Set_Cards_Won_Counter(int num)
{
    cards_won_counter=num;
}

array<Card,amount_of_cards>& Player::Get_Cards_Deck()
{
    return cards_deck;
}