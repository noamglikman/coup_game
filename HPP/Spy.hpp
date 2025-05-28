//noamglikman1@gmail.com
#ifndef SPY_HPP
#define SPY_HPP
#include "Player.hpp"
using namespace std;
namespace coup {
    class Spy: public Player {;
    private:
        /* data */
    public:
    Spy(Game &game, const string &name): Player(game, name) {
        _role = "Spy";
    }
        string role() const{
            return _role;
        };
        string getName(){
            return _name;
        };
        int get_coins(Player &player);
        void block(Player &player);
        ~Spy(){}
        // Destructor
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
        void remove_coins(int coins)override{
            _coinNum -= coins;
        }
};
    
}
#endif // SPY_HPP