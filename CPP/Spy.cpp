//noamglikman1@gmail.com
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"


using namespace std;

namespace coup{
    /**
     * @brief Spy constructor initializes the Spy player with a game reference and a name.
     * 
     * @param game Reference to the game instance.
     * @param name Name of the player.
     */
    int Spy:: get_coins(Player &player){
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        return player.coins();
    }
    /**
     * @brief Blocks another player.
     * 
     * This method allows the Spy to block a player's action, it is means that in
     *  this player next turn he is block for arrest.
     * It also updates the game state and the blocked player's status.
     * @param player The player to be blocked.
     * @throws runtime_error If the game is over or if the player tries to block themselves.
     */
    void Spy::block(Player &player) {
        if (_game.is_game_over()) {
            throw runtime_error("Game is over, you can't block");
        }
        if(player==*this){
            throw runtime_error("you cant activate this action on yourself");
        }
        add_move("block");
        player.add_move("block");
        player.set_Blocked(true);
        cout << _name << " blocked " << player.getName() << endl;
}    
}