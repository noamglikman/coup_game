#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "Baron.hpp"


using namespace std;

namespace coup{
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
    add_move("invest");
    LastMove_of_each_player()="invest";
    _moves_of_each_player.push_back("invest");
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
}
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