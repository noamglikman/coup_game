#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"


using namespace std;

namespace coup{

void Governor::undo(Player &player){
    if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    if(player.LastMove_of_each_player()!="tax"){
        throw runtime_error("Governor can undo only tax and if someone did undo before");
    }
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    cout<< "Governor undo tax" << endl;
    if(player.coins() < 2){
        throw runtime_error("You can't undo a tax if the player has less than 2 coins ");
    }
    player.remove_coins(2);
    player.add_move("undo");
    LastMove_of_each_player()="undo";
    _moves_of_each_player.push_back("undo");
    add_move("undo");
    
}
// void Governor:: tax(){
//     if (!_is_active) {
//         throw runtime_error("Player is not active");
//     }
//     if( _game.turn() != _name) {
//         throw runtime_error("It's not your turn");
//     }
//     cout<< _name << " taxed" << endl;
//     _coinNum+=3;
//     if(LastMove_of_each_player()!="bride"){
//         _game.next_turn();
//     }
//     if(LastMove_of_each_player()=="bribe"&&_can_bride==false){
//         _game.next_turn();
//         _can_bride=true;
//         cout<<_name<<" can bribe now"<<endl;
//     }
//     _moves_of_each_player.push_back("tax");
// }

}