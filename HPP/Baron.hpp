//noamglikman1@gmail.com
#ifndef BARON_HPP
#define BARON_HPP
#include "Player.hpp"
using namespace std;
namespace coup {
    // Baron.hpp
    class Baron: public Player {;
    private:
        /* data */
    public:
    Baron(Game &game, const string &name): Player(game, name) {
        _role = "Baron";
    }
        string role() const{
            return _role;
        }
        string getName(){
            return _name;
        }
        void tax();
        void undo(const Player &player){}
        void invest();
        bool is_active() const{
            return _is_active;
        }
        void set_active(bool is_active,bool using_gui=false){
            _is_active = is_active;
        }
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
        ~Baron(){}
        // Destructor
};
    
}
#endif // BARON_HPP