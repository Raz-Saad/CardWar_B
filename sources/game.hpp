#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include "player.hpp"
using namespace std;

namespace ariel{
class Game{
    static constexpr int amount_of_cards=26;//amount of cards in a players deck
    static constexpr int random_chars_arr=36;//amount of chars in the random id generator
    static constexpr int arr_lower_bound=0;//lower bound of the random generator
    static constexpr int arr_upper_bound=35;//upper bound of the random genarator
    Player &player1;//reference to player1
    Player &player2;//reference to player2
    string game_id="_";//the id of a specific game. tidy doesnt let me initialize it to ""
    int player1_wins=0;//counts how many times player1 won
    int player2_wins=0;//counts how many times player2 won
    int number_of_draws=0;//counts how many times there was a draw
    int number_of_rounds=0;//counts how many rounds played untill the game was over
    
    
    public:
        
        Game(Player &pp1,Player &pp2):player1(pp1),player2(pp2)
        {//constructor
            Game::deal_cards(this->player1,this->player2);//shuffling the cards and dealing them to both players equally
            player1.Set_Cards_Counter(amount_of_cards);//initialize cards counter to 26
            player2.Set_Cards_Counter(amount_of_cards);//initialize cards counter to 26
            
            //generaing a random id for the game
            array<char,random_chars_arr> id_random_chars={'0','1','2','3','4','5','6','7','8','9','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                     'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                     's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
            std::random_device rnd;                       
            std::mt19937 gen(rnd());                       
            std::uniform_int_distribution<> distr(arr_lower_bound, arr_upper_bound); 
            for(int i=0;i<4;i++)
            {
                game_id+=id_random_chars.at(size_t(distr(gen)));   
            }
            // creating a log file for the game
            ofstream MyFile("game_log"+game_id+".txt"); 
            MyFile.close();
        }

        void playTurn();//playing a turn of the game
        void printLastTurn();//prints last turn info
        void playAll();//plays the whole game
        void printWiner();//prints the winner of the game
        void printLog();//prints the info of all the rounds of the game
        void printStats();//prints basic stats of the game
        void deal_cards(Player &player1,Player &player2);//shuffling and dealing cards to both players
        void Insert_into_Log(int p1_card,int p2_card,int winner);//insert round info to the game log
        //getters and setters for the class members
        Player GetPlayer1();
        Player GetPlayer2();
        string Get_Game_ID();
        int Get_Player1_Wins();
        int Get_Player2_Wins();
        int Get_Number_Of_Draws();
        int Get_Number_Of_Rounds();
        void Set_Player1_Wins(int num);
        void Set_Player2_Wins(int num);
        void Set_Number_Of_Draws(int num);
        void Set_Number_Of_Rounds(int num);
        
     
};
};

