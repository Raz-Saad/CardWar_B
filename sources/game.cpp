#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
using namespace ariel;


void swap(int a, int b, Card (&deck)[52])
{ //swaping the cards place in the deck according to the random index we got
    Card temp = deck[a];
    deck[a] = deck[b];
    deck[b] = temp;
}
void Shuffle_Cards(Card (&deck)[52])
{//shuffle the cards in the deck 100 times
    std::random_device rnd;  // obtain a random number from hardware
    std::mt19937 gen(rnd());  // seed the generator
    std::uniform_int_distribution<> distr(0, 51); // define the range

    for (int i = 0; i < 100; i++)
        swap(distr(gen), distr(gen), deck); // swap cards spots
}

void Game::deal_cards(Player &player1, Player &player2)
{ //shuffling the card deck and dealing the cards to both players
    int index = 0;
    Card deck[52];//card deck that stores cards by value order
    for (int i = 1; i <= 13; i++)
    {//inserting cards to the deck array
        deck[index++] = Card(i, "Diamonds");
        deck[index++] = Card(i, "Clubs");
        deck[index++] = Card(i, "Hearts");
        deck[index++] = Card(i, "Spades");
    }

    Shuffle_Cards(deck); //shuffling the cards
    // now we have a shuffled deck
    for (size_t i = 0; i < 26; i++)
    {//dealing the cards to both players
        player1.Get_Cards_Deck().at(i) = deck[(2 * i)];
        player2.Get_Cards_Deck().at(i) = deck[(2 * i) + 1];
    }

}

void Game::Insert_into_Log(int p1_card, int p2_card, int winner)
{ // insert round info to the log file, winner= 1-player1 won, 2- player2 won, 3-draw
    ofstream MyFile("game_log" + Get_Game_ID() + ".txt", ios::app); // openning the log file in append mode
    string card_value_p1 = std::to_string(p1_card);// for converting a number like 1 to ace, 11 to Jack ....
    string card_type_p1 = player1.Get_Cards_Deck().at(player1.Get_Cards_Deck_Index()).GetType();
    string card_value_p2 = std::to_string(p2_card);
    string card_type_p2 = player2.Get_Cards_Deck().at(player2.Get_Cards_Deck_Index()).GetType();
    switch (p1_card)
    {
    case 1:
        card_value_p1 = "Ace";
        break;
    case 11:
        card_value_p1 = "Jack";
        break;
    case 12:
        card_value_p1 = "Queen";
        break;
    case 13:
        card_value_p1 = "King";
        break;
    }

    switch (p2_card)
    {
    case 1:
        card_value_p2 = "Ace";
        break;
    case 11:
        card_value_p2 = "Jack";
        break;
    case 12:
        card_value_p2 = "Queen";
        break;
    case 13:
        card_value_p2 = "King";
        break;
    }

    switch (winner)
    {//inserting into the file the round info
    case 1:
        MyFile << player1.getName() << " played " << card_value_p1 << " of " << card_type_p1 << " " << player2.getName() 
            << " played " << card_value_p2 << " of " << card_type_p2 << ". " << player1.getName() << " wins." << endl;
        break;
    case 2:
        MyFile << player1.getName() << " played " << card_value_p1 << " of " << card_type_p1 << " " << player2.getName() 
            << " played " << card_value_p2 << " of " << card_type_p2 << ". " << player2.getName() << " wins." << endl;
        break;
    case 3:
        MyFile << player1.getName() << " played " << card_value_p1 << " of " << card_type_p1 << " " << player2.getName() 
            << " played " << card_value_p2 << " of " << card_type_p2 << "."<< " Draw. ";
        break;
    }

    MyFile.close();//closing the file
}

void Game::playTurn()
{//Playing a turn untill someone wins or we are out of cards

    if (&player1 == &player2)
    {//checking if the same players tried to played against himself
        throw std::runtime_error("Same player can not play a game by himself");
    }
    else
    {
        if (player1.Get_Cards_Counter() != 0 && player2.Get_Cards_Counter()!=0)
        {
            //stores the values of the playing cards of both players
            int p1_card = player1.Get_Cards_Deck().at(player1.Get_Cards_Deck_Index()).GetValue();
            int p2_card = player2.Get_Cards_Deck().at(player2.Get_Cards_Deck_Index()).GetValue();
            static int times_we_called_func = 0; // amount of times we called the playturn func/we draw,helps when players draw
            
            if(times_we_called_func==0)
            {//increasing the round counter by 1 when a new round occurs (if its a draw, we are at the same round until someone wins)
                Set_Number_Of_Rounds(Get_Number_Of_Rounds()+1);
            }

            if (p1_card == 1 && p2_card == 2)
            {//ace is losing to 2
                Insert_into_Log(p1_card, p2_card, 2);//insert round data into the log
                player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 1);//increase the card index by 1 (help us know which card is at the top of the deck )
                player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);//decrease card counter by 1, because the played used 1 card this round

                Set_Player2_Wins(Get_Player2_Wins()+1);//increasing player2 winning counter by 1 because he won this round
                player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 1);
                player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);
                player2.Set_Cards_Won_Counter(player2.Get_Cards_Won_Counter() + ((4 * times_we_called_func) + 2)); //increasing player2 winning_cards counter. 4*times+2 because thats how its increase

                times_we_called_func = 0;//after the round ended we want to zero this var
                return;
            }

            if (p1_card == 2 && p2_card == 1)
            {
                Insert_into_Log(p1_card, p2_card, 1);
                player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 1);
                player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);
                player1.Set_Cards_Won_Counter(player1.Get_Cards_Won_Counter() + ((4 * times_we_called_func) + 2));
                Set_Player1_Wins(Get_Player1_Wins()+1);

                player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 1);
                player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);

                times_we_called_func = 0;
                return;
            }

            if (p1_card == 1 && p2_card > 2)
            {
                Insert_into_Log(p1_card, p2_card, 1);
                player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 1);
                player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);
                player1.Set_Cards_Won_Counter(player1.Get_Cards_Won_Counter() + ((4 * times_we_called_func) + 2));
                Set_Player1_Wins(Get_Player1_Wins()+1);

                player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 1);
                player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);

                times_we_called_func = 0;
                return;
            }

            if (p1_card > 2 && p2_card == 1)
            {
                Insert_into_Log(p1_card, p2_card, 2);
                player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 1);
                player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);
                
                Set_Player2_Wins(Get_Player2_Wins()+1);
                player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 1);
                player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);
                player2.Set_Cards_Won_Counter(player2.Get_Cards_Won_Counter() + ((4 * times_we_called_func) + 2));
                
                times_we_called_func = 0;
                return;
            }

            if (p1_card > p2_card)
            {
                Insert_into_Log(p1_card, p2_card, 1);
                player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 1);
                player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);
                player1.Set_Cards_Won_Counter(player1.Get_Cards_Won_Counter() + ((4 * times_we_called_func) + 2));
                Set_Player1_Wins(Get_Player1_Wins()+1);
                
                player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 1);
                player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);

                times_we_called_func = 0;
                return;
            }

            if (p1_card < p2_card)
            {
                Insert_into_Log(p1_card, p2_card, 2);
                player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 1);
                player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);

                Set_Player2_Wins(Get_Player2_Wins()+1);
                player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 1);
                player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);
                player2.Set_Cards_Won_Counter(player2.Get_Cards_Won_Counter() + ((4 * times_we_called_func) + 2));
                times_we_called_func = 0;
                return;
            }

            if (p1_card == p2_card)
            {//draw occurs
                Insert_into_Log(p1_card, p2_card, 3);//insert into log that a draw occurs
                Set_Number_Of_Draws(Get_Number_Of_Draws() + 1); // increase draws counter by 1

                if (player1.Get_Cards_Counter() > 2)
                {//if the players have more than 2 cards in their deck, they can keep play the turn
                    times_we_called_func++;//increase the amount of times we called the turn func by 1, it helps us calculate how many cards the winner will get
                    player1.Set_Cards_Deck_Index(player1.Get_Cards_Deck_Index() + 2);//increase index deck by 2,becuase we played 1 card and the we put down another card
                    player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 2);

                    player2.Set_Cards_Deck_Index(player2.Get_Cards_Deck_Index() + 2);
                    player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 2);

                    playTurn();//play the turn one more time
                }
                //if both players have 2 cards or less in their deck, they can not keep playing the turn and need to slplit the cards
                else if (player1.Get_Cards_Counter() == 2)
                {
                    
                    player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 2);
                    player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 2);
                    // if there are no cards left to play, we split the "winning deck" equally between both players
                    player1.Set_Cards_Won_Counter(player1.Get_Cards_Won_Counter() + (((4 * times_we_called_func) / 2) + 2));
                    player2.Set_Cards_Won_Counter(player2.Get_Cards_Won_Counter() + (((4 * times_we_called_func) / 2) + 2));
                }
                else
                {
                    
                    player1.Set_Cards_Counter(player1.Get_Cards_Counter() - 1);
                    player2.Set_Cards_Counter(player2.Get_Cards_Counter() - 1);

                    player1.Set_Cards_Won_Counter(player1.Get_Cards_Won_Counter() + (((4 * times_we_called_func) / 2) + 1));
                    player2.Set_Cards_Won_Counter(player2.Get_Cards_Won_Counter() + (((4 * times_we_called_func) / 2) + 1));
                }
                return;
            }
        }
        else
        {//if we try to play another turn when both players dont have any cards left to play with
            throw std::runtime_error("No more cards left to play with");
        }
    }
}

// function that helps to the "printLastTurn" function, this function gets the last line from a file
string getLastLine(ifstream &MyFile)
{
    string line;
    while (MyFile >> std::ws && getline(MyFile, line)); // skip empty lines

    return line;
}

void Game::printLastTurn()
{//prints last turn info
    if (&player1 == &player2)
    {
        throw std::runtime_error("Same player can not play a game by himself");
    }
    else if(Get_Number_Of_Rounds()>0)
    {//prints the info only if atleast 1 turn played
        ifstream MyFile("game_log" + Get_Game_ID()+ ".txt");

        if (MyFile)
        {
            cout << getLastLine(MyFile) << endl;
        }
        else
        {
            cout << "Could not open the file." << endl;
        }
    }
    else
    {
        throw std::runtime_error("No round has been played yet");
    }
}

void Game::playAll()
{//playing the whole game
    while ((player1.Get_Cards_Counter() > 0)&&(player2.Get_Cards_Counter() > 0))
    {//keep playing untill both players are out of cards to play with
        playTurn();
    }
}

void Game::printWiner()
{//prints the winner of the game
    if (&player1 == &player2)
    {
        throw std::runtime_error("Same player can not play a game by himself");
    }
    else if(Get_Number_Of_Rounds()>0)
    {
        if (player1.Get_Cards_Won_Counter() > player2.Get_Cards_Won_Counter())
        {
            cout << "The winner is " << player1.getName()<<endl;
        }
        else if (player1.Get_Cards_Won_Counter() < player2.Get_Cards_Won_Counter())
        {
            cout << "The winner is " << player2.getName()<<endl;
        }
        else
        {
            cout << "The game ended in a draw" <<endl;
        }
    }
    else
    {
        throw std::runtime_error("No round has been played yet");
    }
}

void Game::printLog()
{//prints the whole game log
    if (&player1 == &player2)
    {
        throw std::runtime_error("Same player can not play a game by himself");
    }
    else if(Get_Number_Of_Rounds()>0)
    {
        string line;

        // Read from the text file
        ifstream MyFile("game_log" + Get_Game_ID() + ".txt");

        // Use a while loop together with the getline() function to read the file line by line
        while (getline(MyFile, line))
        {
            // Output the text from the file
            cout << line << endl;
        }

        // Close the file
        MyFile.close();
    }
    else
    {
        throw std::runtime_error("No round has been played yet");
    }
}

void Game::printStats()
{//prints basic stats about the game
    if (&player1 == &player2)
    {
        throw std::runtime_error("Same player can not play a game by himself");
    }
    if(Get_Number_Of_Rounds()>0)
    {
        double player1_winrate=(double(Get_Player1_Wins())/double(Get_Number_Of_Rounds()))*100;
        double player2_winrate=(double(Get_Player2_Wins())/double(Get_Number_Of_Rounds()))*100;
        double draw_rate=(double(Get_Number_Of_Draws())/double(Get_Number_Of_Rounds()))*100;
        std::cout << std::setprecision(2) << std::fixed;
        cout<<"\n-------------------------------"<<endl;
        cout<<"Stats:"<<endl;
        cout<<"The game lasted "<<Get_Number_Of_Rounds()<<" rounds."<<endl;
        cout<<player1.getName()<<" win rate is: "<<player1_winrate<<"%, "<<player1.getName()
            <<" won "<<player1.Get_Cards_Won_Counter()<<" cards"<<endl;

        cout<<player2.getName()<<" win rate is: "<<player2_winrate<<"%, "<<player2.getName()
            <<" won "<<player2.Get_Cards_Won_Counter()<<" cards"<<endl;

        cout<<"Draw rate is: "<<draw_rate<<"%, amount of draws: "<<Get_Number_Of_Draws()<<endl;
        cout<<"-------------------------------"<<endl;
    }
    else
    {
        throw std::runtime_error("No round has been played yet");
    }
}
//getters and setters
Player Game::GetPlayer1()
{
    return player1;
}
Player Game::GetPlayer2()
{
    return player2;
}
string Game::Get_Game_ID()
{
    return game_id;
}

int Game::Get_Player1_Wins()
{
    return player1_wins;
}

int Game::Get_Player2_Wins()
{
    return player2_wins;
}

int Game::Get_Number_Of_Draws()
{
    return number_of_draws;
}

int Game::Get_Number_Of_Rounds()
{
    return number_of_rounds;
}

void Game::Set_Player1_Wins(int num)
{
    player1_wins = num;
}

void Game::Set_Player2_Wins(int num)
{
    player2_wins = num;
}

void Game::Set_Number_Of_Draws(int num)
{
    number_of_draws = num;
}
void Game::Set_Number_Of_Rounds(int num)
{
    number_of_rounds=num;
}