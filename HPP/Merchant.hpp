//noamglikman1@gmail.com
#ifndef MERCHANT_HPP
#define MERCHANT_HPP
#include "Player.hpp"
using namespace std;
namespace coup {
    class merchant: public Player {;
    private:
        /* data */
    public:
    merchant(Game &game, const string &name): Player(game, name) {
        _role = "Merchant";
    }
        string role() const{
            return _role;
        };
        string getName(){
            return _name;
        };
        void undo(const Player &player){}
        ~merchant(){}
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
        void start(){
            if(coins()>=3){
                _coinNum+=1;
                cout<<_role<<"got 1 coin extra"<<endl;
            }
        }
        
};
    
}
#endif 