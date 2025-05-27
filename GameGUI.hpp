#ifndef GAMEGUI_HPP
#define GAMEGUI_HPP
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
using namespace std;
using namespace coup;
namespace coup {
    class Player;
}
    Player* createPlayers(Game& game, std::string playerName, int numPlayers);

void runGameSetup(std::vector<std::string>& playerNames);
void showMainMenu(std::vector<std::string>& playerNames);
#endif // GAMEGUI_HPP