//noamglikman1@gmail.com
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Baron.hpp"


using namespace std;

namespace coup{
    /**
 * @brief Override the invest method for the Baron class, which allows the Baron to exchange 3 coins for 6.
 *        This action is only possible if the Baron has more than 3 coins.
 * 
 * @throws std::runtime_error if the game is over.
 * @throws std::runtime_error if the player is not active.
 * @throws std::runtime_error if it is not the player's turn.
 * @throws std::runtime_error if the player has 10 or more coins (must coup instead).
 * @throws std::runtime_error if the player has 3 or fewer coins.
 * 
 * @return void
 */
void Baron::invest(){
    if(_game.is_game_over()) {
        throw runtime_error("Game is over, you can't gather");
    }
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    if( _game.turn() != _name) {
        throw runtime_error("It's not your turn");
    }
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    if(coins()<3){
        throw runtime_error("Baron can invest only if he has more than 3 coins");
    }
    cout<<coins()<<endl;
    if(!coins()>3){
        throw runtime_error("Baron can invest only if he has more than 3 coins");
    }
    add_coins(3);
    cout<<"Baron traded its 3 coins and got 6"<<endl;
    LastMove_of_each_player()="invest";
    if(LastMove_of_each_player()!="bride"){
        _game.next_turn();
        set_Blocked(false);
    }
     if(LastMove_of_each_player()=="bribe"&&_cant_bribe==false){
        _game.next_turn();
        set_Blocked(false);
        _cant_bribe=true;
        cout<<_name<<" can bribe now"<<endl;
    }
    add_move("invest");
}
/**
 * @brief Override the invest method for the Baron class, which allows the Baron to exchange 3 coins for 6.
 *        This action is only possible if the Baron has more than 3 coins.
 * 
 * @throws std::runtime_error if the game is over.
 * @throws std::runtime_error if the player is not active.
 * @throws std::runtime_error if it is not the player's turn.
 * @throws std::runtime_error if the player has 10 or more coins (must coup instead).
 * @throws std::runtime_error if the player has 3 or fewer coins.
 * 
 * @return void
 */
void Baron::tax(){
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }
        if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }
        if(one_turn_is_over==0&&_sanctioned==true){
            _coinNum+=1;
            cout<< _name << " taxed "<<_role << endl;
            if(LastMove_of_each_player()!="bride"){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
                LastMove_of_each_player()="tax";
                 _moves_of_each_player.push_back("tax");
                add_move("tax");
        }
        }else{start();
         _coinNum+=2;
        cout<< _name << " taxed "<<_role << endl;
        if(LastMove_of_each_player()!="bride"){
            _game.add_last_played(this);
            _game.next_turn();
            set_Blocked(false);
            LastMove_of_each_player()="tax";
            _moves_of_each_player.push_back("tax");
            add_move("tax");}
        
    }
}
}