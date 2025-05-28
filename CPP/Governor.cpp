//noamglikman1@gmail.com
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"


using namespace std;

namespace coup{
/**
 * @brief Override the undo method for the Governor class, which allows undoing the last "tax" action made by another player.
 *
 * This function enables the Governor to cancel a "tax" action previously performed by another player,
 * if certain conditions are met. The player loses 2 coins as a result.
 *
 * @param player The player whose "tax" move is being undone.
 *
 * @throws std::runtime_error If the game is over.
 * @throws std::runtime_error If the Governor is not active.
 * @throws std::runtime_error If the last move of the target player is not "tax".
 * @throws std::runtime_error If the Governor has 10 or more coins (must coup instead).
 * @throws std::runtime_error If the Governor tries to undo their own move.
 * @throws std::runtime_error If the target player has fewer than 2 coins.
 *
 * @return void
 */
void Governor::undo(Player &player){
    // Check if the game is over
    if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
    // Check if the player is active
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    // Check if it's the player's turn
    if(player.LastMove_of_each_player()!="tax"){
        throw runtime_error("Governor can undo only tax and if someone did undo before");
    }
    // Check if the player has 10 or more coins
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    // Check if the player is trying to undo their own move
    if(player==*this){
       throw runtime_error("you cant activate this action on yourself");
    }
    cout<< "Governor undo tax" << endl;
    // Check if the player has at least 2 coins to undo the tax
    if(player.coins() < 2){
        throw runtime_error("You can't undo a tax if the player has less than 2 coins ");
    }
    // Perform the undo action
    player.remove_coins(2);
    player.add_move("undo");
    add_move("undo");
    
}

}