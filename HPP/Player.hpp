#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace coup {

    class Game; // Forward declaration of the Game class

    class Player {
    public:
        Player(Game &game, const string &name);
        Player(const Player &other): _game(other._game), _name(other._name), _role(other._role),_is_active(other._is_active), _coinNum(other._coinNum) {
            // Copy constructor
        }
        virtual string role() const=0;
        virtual string getName(){
            return _name;
        }
        
        virtual void gather();
        virtual void tax();
        virtual void bribe();
        virtual void arrest(Player &player);
        virtual void sanction(Player &player);
        virtual void coup( Player &player,bool using_gui=false);
        virtual void undo(const Player &player){}
        virtual bool is_active() const{
            return _is_active;
        }
        virtual void set_active(bool is_active,bool using_gui=false){
        
            _is_active = is_active;
        }
        virtual int coins() const{
            return _coinNum;
        }
        virtual void set_coins(int coins){
            _coinNum = coins;
        }
        virtual void add_coins(int coins){
            _coinNum += coins;
        }
        virtual void remove_coins(int coins){
            _coinNum -= coins;
        }
        virtual string LastMove_of_each_player() const {
            if (_moves_of_each_player.empty()) {
                return ""; 
            }
            return _moves_of_each_player.back(); 
        }
        virtual void add_move(const string &move){
            _moves_of_each_player.push_back(move);
        }
        virtual void set_Blocked(bool Blocked){
            _Blocked = Blocked;
        }
        virtual bool get_Blocked() const{
            return _Blocked;
        }

        virtual void set_is_active(bool is_active){
            _is_active = is_active;
        }
        virtual void start(); 
        virtual string _get_couped();
        virtual void set_cant_bribe(bool cant_bribe){
            _cant_bribe = cant_bribe;
        }
        virtual string getName_of_couped(){
            return _couped;
        }
        Player& operator=(const Player& other) {
            if (this == &other) {
                return *this; // בדיקה עצמית
            }

            // העתקת משתנים פשוטים
            _name = other._name;
            _coinNum = other._coinNum;
            _is_active = other._is_active;
            

            return *this;
        }
        bool is_sanctioned() const{
            return _sanctioned;
        }
        void set_sanctioned(bool sanctioned){
            _sanctioned = sanctioned;
        }
        
        void set_one_turn_is_over(){
            one_turn_is_over = 0;
        }
        
        ~Player(){}


    protected:
        Game &_game;
        string _name;
        string _role;
        bool _is_active;
        int _coinNum;
        bool _sanctioned=false;
        int one_turn_is_over=0;
        bool _Blocked=false;
        bool _cant_bribe=false;//לא חסום
        vector<string>_moves_of_each_player;
        string _couped="";
    };
}













#endif