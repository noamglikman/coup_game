//noamglikman1@gmail.com
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"

using namespace std;

namespace coup{
    /**
 * @brief Adds a player to the game and updates the current turn to that player.
 * 
 * @param player Pointer to the player to be added to the game.
 * 
 * @return void
 */
    void Game::add_player(Player* player){
        _players.push_back(player);
        _turn = player->getName();  
    }
    /**
 * @brief Removes a player from the game by marking them as inactive.
 *        This function also optionally supports GUI-related behavior.
 * 
 * @param player The player to be removed.
 * @param using_gui A boolean indicating whether GUI-specific behavior should be used.
 * 
 * @return void
 */
    void Game:: remove_player(Player& player,bool using_gui){
        for(int i=0; i<_players.size(); i++){
            if(_players[i]->getName() == player.getName()){
                cout<< player.getName() << " is out of the game" << endl;

                player.set_active(false,using_gui);

                break;
            }
        }
    } 
    /**
 * @brief Retrieves a player from the internal list by their index.
 * 
 * @param i The index of the player to retrieve.
 * 
 * @throws std::out_of_range if the index is not valid.
 * 
 * @return Pointer to the player at the given index.
 */
    Player* Game::getPlayerByindex(int i){
        if (i < 0 || i >= _players.size()) {
            throw out_of_range("Index out of range");
        }
        return _players[i];
    }
    /**
 * @brief Assignment operator for the Game class. Copies the state of another game into this one.
 * 
 * @param other The other game instance to copy from.
 * 
 * @return Reference to the updated game instance (*this).
 */
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