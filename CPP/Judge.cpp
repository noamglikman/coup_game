#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Judge.hpp"
using namespace std;

namespace coup{
    
void Judge::undo_bribe(Player &player){
    if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    if(player.LastMove_of_each_player()!="bribe"){
        throw runtime_error("Judge can undo only bribe");
    }
    player.add_move("undid_bribe"); // Update the last move of the player
    player.set_cant_bribe(true);//שחקן חסום כלומר אינו יכול לעשות bribe
    _game.next_turn();
    add_move("undo_bribe");
    cout<< _name << " undid bribe of "<<player.role() << endl;
}
}