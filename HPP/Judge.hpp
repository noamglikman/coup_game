#ifndef JUDGE_HPP
#define JUDGE_HPP
#include "Player.hpp"
#include "Game.hpp"
using namespace std;
namespace coup {
    class Judge: public Player {;
    private:
        /* data */
    public:
    Judge(Game &game, const string &name): Player(game, name) {
        _role = "Judge";
    }
        string role() const{
            return _role;
        };
        string getName(){
            return _name;
        };
        // void gather(){}
        //void tax(){}
        //void bride(const Player &player){}
        //void arrest(const Player &player){}
        //void sanction(const Player &player){}
        //void coup(const Player &player);
        void undo_bribe(Player &player);
        ~Judge(){}
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
};
    
}
#endif // SPY_HPP