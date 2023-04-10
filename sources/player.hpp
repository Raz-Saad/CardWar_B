#pragma once
#include <iostream>
#include <array>
#include "card.hpp"
using namespace std;
namespace ariel{

class Player{
    string name;//name of the player 
    size_t cards_deck_index = 0;//index of the top card of the players deck
    int cards_counter=0;//counts how many cards are left in the deck to play
    int cards_won_counter=0;//counts how many cards the player has won
    static constexpr int amount_of_cards=26;
    array<Card,amount_of_cards> cards_deck;//player's playing card deck
    public:
        Player(){};
        Player(string name);
        int stacksize();//return how many cards the player has to play with
        int cardesTaken();//return how many cards the player won
        array<Card,amount_of_cards>& Get_Cards_Deck();//return card_deck array 
        //getters and setters for the class members
        string getName();
        size_t Get_Cards_Deck_Index();
        int Get_Cards_Counter();
        int Get_Cards_Won_Counter();
        void Set_Cards_Deck_Index(size_t num);
        void Set_Cards_Counter(int num);
        void Set_Cards_Won_Counter(int num);
        
        
        
};
};

