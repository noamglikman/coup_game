//noamglikman1@gmail.com
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Judge.hpp"
using namespace std;

namespace coup{
    /**
 * @brief Allows the Judge to undo a bribe made by another player.
 *
 * This method enables a Judge to cancel the effect of a bribe previously performed by another player.
 * It marks the bribing player as blocked from bribing again and forces a turn advancement.
 *
 * @param player The player whose bribe action is being undone.
 *
 * @throws std::runtime_error If the game is over.
 * @throws std::runtime_error If the Judge is not active.
 * @throws std::runtime_error If the Judge has 10 or more coins (must perform a coup).
 * @throws std::runtime_error If the Judge attempts to undo their own action.
 * @throws std::runtime_error If the target player's last move was not "bribe".
 *
 * @return void
 */
    
void Judge::undo_bribe(Player &player){
    // Check if the game is over
    if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
    // Check if the player is active
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    //Check if he has 10 or more coins
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    // Check if the player is trying to undo their own move
    if(player==*this){
       throw runtime_error("you cant activate this action on yourself");
    }
    // Check if the last move of the player was a bribe
    if(player.LastMove_of_each_player()!="bribe"){
        throw runtime_error("Judge can undo only bribe");
    }
    // Perform the undo action
    player.add_move("undid_bribe"); // Update the last move of the player
    player.set_cant_bribe(true);//שחקן חסום כלומר אינו יכול לעשות bribe
    _game.next_turn();
    add_move("undo_bribe");
    cout<< _name << " undid bribe of "<<player.role() << endl;
}
}