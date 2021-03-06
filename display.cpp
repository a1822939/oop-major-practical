#include "Display.h"
#include "Game.h"
#include <stdlib.h>
#include <chrono>
#include <thread>


// Default constructor for display
Display::Display() {}

// Constructor allowing use of game functions
Display::Display(Game *game) { this->game = game; }

// Displays the main menu
void Display::menu()
{
    //Displays the opening title screen for user
    system("clear");
    std::cout << "Welcome to Mortal OOPbat! \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    system("clear");

    std::cout << "Menu: \n"
              << "1. Play\n"
              << "2. Quit\n"
              << std::endl;
    int input = game->getInput(2);
    switch (input)
    {
    case 1:
        system("clear");
        characterSelection();
        break;

    case 2:
        exit(0);
        break;

    default:
        break;
    }
}

// Displays the character options to each player
void Display::characterSelection()
{

    //Asks user for their name
    game->inputPlayerNames();

    system("clear");

    std::cout << "Select character for " << game->getPlayer(0)->getPlayerName() << " out of the list below: "
              << "\n"
              << std::endl;

    displayCharacterStats(); //Displays the current list of characters avaliable for the user

    int index = game->getInput(game->getNumCharacters()) - 1; // initialises index by requesting input from user
    game->getPlayer(0)->applyCharacter(game->getCharacter(index)); // applies the chosen character to the first player
    system("clear");

    std::cout << game->getPlayer(0)->getPlayerName() << " has chosen " << game->getCharacter(index).getName() << "\n"
              << std::endl;

    game->deleteCharacter(index); // removes chosen character from list

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::cout << "Select character for " << game->getPlayer(1)->getPlayerName() << " out of the list below: "
              << "\n"
              << std::endl;

    displayCharacterStats(); //Displays the current list of characters avaliable for the user

    index = game->getInput(game->getNumCharacters()) - 1;
    game->getPlayer(1)->applyCharacter(game->getCharacter(index)); // applies the chosen character to the second player
    system("clear");

    std::cout << game->getPlayer(1)->getPlayerName() << " has chosen " << game->getCharacter(index).getName() << "\n"
              << std::endl;

    game->deleteCharacter(index); // removes chosen character from list

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    system("clear");
    std::cout << "Fight!\n"
              << std::endl;
    fight();
}

// Displays the stats of each character
void Display::displayCharacterStats()
{
    for (int i = 0; i < game->getNumCharacters(); i++) // loops through number of characters 
    {
        std::cout << i + 1 << ". " << game->getCharacter(i).getName() << std::endl;
        std::cout << "\tHP:\t\t" << game->getCharacter(i).getHP() << std::endl;
        std::cout << "\tSpeed:\t\t" << game->getCharacter(i).getSpeed() << std::endl;
        std::cout << "\tStrength:\t" << game->getCharacter(i).getStrength() << std::endl;
        std::cout << "\n";
    }
}

// Checks each player's health and declares a winner
bool Display::displayCurrentStats(int p1MoveChoice, int p2MoveChoice)
{
    system("clear");

    if (game->getPlayer(0)->getHP() == 0)
    {
        HUD();
        std::cout << "\n"
                  << game->getPlayer(1)->getPlayerName() << " wins!!!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        return 1;
    }
    else if (game->getPlayer(1)->getHP() == 0)
    {
        HUD();
        std::cout << "\n"
                  << game->getPlayer(0)->getPlayerName() << " wins!!!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        return 1;
    }
    else
    {

        HUD();

        return 0;
    }
}

// Displays and initiates the fight sequence
void Display::fight()
{

    bool GameOver = 0;

    while (GameOver == 0)
    {
        //
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "Choose move for " << game->getPlayer(0)->getPlayerName() << ": \n"
                  << "1. Attack\n"
                  << "2. Heal\n"
                  << std::endl;

        int p1MoveChoice = game->getInput(2);

        std::cout << "\nChoose move for " << game->getPlayer(1)->getPlayerName() << ": \n"
                  << "1. Attack\n"
                  << "2. Heal\n"
                  << std::endl;

        int p2MoveChoice = game->getInput(2);

        game->executeTurn(p1MoveChoice, p2MoveChoice);
        GameOver = displayCurrentStats(p1MoveChoice, p2MoveChoice);

        // display fight results
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}

// Displays updated health bar of each player.
void Display::HUD()
{

    system("clear");

    std::cout << game->getPlayer(0)->getPlayerName() << " HP: " << game->getPlayer(0)->getHP()
              << "/" << game->getPlayer(0)->getFullHP();

    std::cout << "\t" << game->getPlayer(1)->getPlayerName() << " HP: " << game->getPlayer(1)->getHP()
              << "/" << game->getPlayer(1)->getFullHP()
              << "\n\n";
}

// Destructor
Display::~Display()
{
}