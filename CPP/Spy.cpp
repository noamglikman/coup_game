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

    LastMove_of_each_player() = "block";
    _moves_of_each_player.push_back("block");
    player.LastMove_of_each_player() = "blocked";
    player.set_Blocked(true);

    cout << _name << " blocked " << player.getName() << endl;

    // בדוק אם השחקן "תקוע" לאחר החסימה
    if (player.is_sanctioned() && player.get_Blocked() && player.coins() == 0) {
        cout << player.getName() << " is stuck after being blocked! Turn is over automatically." << endl;
        _game.next_turn(); // העבר את התור לשחקן הבא
    }
}
    
    
}