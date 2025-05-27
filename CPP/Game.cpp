#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"

using namespace std;

namespace coup{
    void Game::add_player(Player* player){
        _players.push_back(player);
        _turn = player->getName();
        
    }
    void Game:: remove_player(Player& player,bool using_gui){
        for(int i=0; i<_players.size(); i++){
            if(_players[i]->getName() == player.getName()){
                cout<< player.getName() << " is out of the game" << endl;

                player.set_active(false,using_gui);

                break;
            }
        }
    } 
    Player* Game::getPlayerByindex(int i){
        if (i < 0 || i >= _players.size()) {
            throw out_of_range("Index out of range");
        }
        return _players[i];
    }
    Game& Game::operator=(const Game& other) {
            if (this == &other) {
                return *this; 
            }
            _turn = other._turn;
            _game_over = other._game_over;
            index = other.index;

            _players = other._players;
            last_arrested = other.last_arrested;
            _players_is_out_of_game = other._players_is_out_of_game;

            return *this;
        }
        
}