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
    int Spy:: get_coins(Player &player){
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        return player.coins();
    }
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