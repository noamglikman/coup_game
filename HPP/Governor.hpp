//noamglikman1@gmail.com
#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP
#include "Player.hpp"
#include "Game.hpp"
using namespace std;
namespace coup {
    class Governor: public Player {;
    private:
        /* data */
    public:
    Governor(Game &game, const string &name): Player(game, name) {
        _role = "Governor";
    }
        string role() const override {
            return _role;
        }
        string getName(){
            return _name;
        };
        void undo(Player &player);
        ~Governor(){}
        bool is_active() const{
            return _is_active;
        }
        void set_active(bool is_active,bool using_gui=false){
            _is_active = is_active;
        }
        // void set_active(bool is_active){
        //     _is_active = is_active;
        // }
        int coins() const{
            return _coinNum;
        }
        void set_coins(int coins){
            _coinNum = coins;
        }
        void add_coins(int coins){
            _coinNum += coins;
        }
        void remove_coins(int coins){
            _coinNum -= coins;
        }
        // Destructor
};
    
}

#endif // PLAYER_HPP