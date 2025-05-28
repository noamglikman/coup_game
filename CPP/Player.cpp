//noamglikman1@gmail.com
#include "Game.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Game.hpp"
#include "Player.hpp"

using namespace std;
namespace coup{
    /**
     * @brief Constructs a new Player object.
     * @param game Reference to the game the player is participating in.
     * @param name The name of the player.
     */
    Player::Player(Game &game, const string &name): _game(game), _name(name), _role(""), _is_active(true), _coinNum(0) {
        if (_name.empty()) {
            throw invalid_argument("Player name cannot be empty");
        }
        if (_game.players().size() >= 6) {
            throw runtime_error("Game is full");
        }
        for(int i=0;i<game.players().size();i++){
            if(name==game.getNameini(i)){
                cout<<"name is already exist"<<endl;
                throw runtime_error("name is already exist");
                
            }
        }
        _game.add_player(this);
        
    }

    void Player::gather() {
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }
        start();
        if(_role=="Baron"&&_sanctioned==true){
            cout<< _name << " gother but he was sanctioned so his coins stay the same "<<_role << endl;
            if(LastMove_of_each_player()!="bride"){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
            }
            if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
                _cant_bribe=false;
                cout<<_name<<" can bribe now"<<endl;
            }
        add_move("gather");
        LastMove_of_each_player()="gather";
        _moves_of_each_player.push_back("gather");
        }else{if(one_turn_is_over==0 && _sanctioned==true){
            throw runtime_error("You can't gather after you have been sanctioned");
        }
        else{
            cout<< _name << " gathered coins " << endl;
            _coinNum++;
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
               _game.next_turn();
               set_Blocked(false);
            }
            if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
                _cant_bribe=false;
                cout<<_name<<" can bribe now"<<endl;
            }
        add_move("gather");
        LastMove_of_each_player()="gather";
        _moves_of_each_player.push_back("gather");
    }}
        
        } 
    void Player::tax(){
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }
        if(one_turn_is_over==0&&_sanctioned==true){
            throw runtime_error("You can't tax after you have been sanctioned");
        }
        if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }
        start();
        if(_role=="Governor"&&_sanctioned==false){
        _coinNum+=3;
        cout<< _name << " taxed "<<_role << endl;
        if(LastMove_of_each_player()!="bribe"){
            _game.add_last_played(this);
            _game.next_turn();
            set_Blocked(false);
            }
        if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){
            _game.add_last_played(this);
            _game.next_turn();
            set_Blocked(false);
            _cant_bribe=false;
            cout<<_name<<" can bribe now"<<endl;
            }
        add_move("tax");
        }else{
            cout<< _name << "taxed"<<_role << endl;
            _coinNum+=2;
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
             }
             if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
                _cant_bribe=false;
                cout<<_name<<" can bribe now"<<endl;
            }
             add_move("tax");
        }
    //}
        
    }
void Player::coup(Player &player,bool using_gui){

    if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    if( _game.turn() != _name) {
        throw runtime_error("It's not your turn");
    }
    if(_coinNum<7){
        throw runtime_error("You need 7 coins to coup");
    } 
    if(player==*this){
       throw runtime_error("you cant activate this action on yourself");
    }
     start();
    cout<< player.getName() << " couped" << endl;
    _coinNum-=7;
    //player.set_active(false);
    _game.remove_player(player,using_gui);
    
    _couped = player.getName();
    _game.set_last_couped_player(&player);
    cout<<_game.get_last_couped_player()->getName()<<" is the last player that was couped"<<endl;
    if(LastMove_of_each_player()!="bribe"){
        _game.next_turn();
        player.set_Blocked(false);
    }
    if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){// חסום למרות שעשה bribe
    _game.add_last_played(this);
    _game.next_turn();
    player.set_Blocked(false);
    _cant_bribe=false;//כבר לא חסום
    cout<<_name<<" can bribe now"<<endl;
    }
    add_move("coup");
    one_turn_is_over=1;
    _sanctioned==false;
}
    string Player::_get_couped(){
        return _couped;
    }
    void Player:: bribe(){
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }
        if(coins() < 4){
            throw runtime_error("You can't bribe  with less then 4 coins,try someone else...");
        }
        if ((is_sanctioned() &&get_Blocked() == true && coins() <3 )||is_sanctioned() 
        && _game.get_can_do_arrest(_game.get_players(),this)==false)
        {
             std::cout << getName() << " is stuck! Turn is over automatically." << std::endl;
            _game.next_turn(); 
        }
        start();
        _coinNum-=4;
        add_move("bribe");
        _moves_of_each_player.push_back("bribe");
        one_turn_is_over=0;
        //_sanctioned==false;
    }


    void Player:: arrest(Player &player){
    if(_game.is_game_over()) {
        throw runtime_error("Game is over, you can't gather");
    }
        if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    if (_game.turn() != _name) {
        throw runtime_error("It's not your turn");
    }
    if (get_Blocked()) {
        throw runtime_error("You are blocked and cannot arrest others");
    }
    if(player==*this){
       throw runtime_error("you cant activate this action on yourself");
    }
    if (_game.get_last_arrested() == player.getName()) {
        throw runtime_error("You can't arrest the same player twice in a row");
    }
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
        start();
        if(player.role() == "General"&&player.is_active()==true){
            cout<<"arrested general thats why nothing happened"<<endl;
            _game.add_last_arrested(player.getName());
            _moves_of_each_player.push_back("arrest");
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
                LastMove_of_each_player()="arrest";
                //add_move("arrest");
                _game.set_can_do_arrest(true);
                _game.next_turn();
                player.set_Blocked(false);
                }
            one_turn_is_over=1;
            _sanctioned==false;}else{if(player.role()=="Merchant"&&player.is_active()==true){
            cout<< player.getName() << " arrested" << endl;
            _game.add_last_arrested(player.getName());
            _game.set_can_do_arrest(true);
            player.set_coins(player.coins()-2);
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
                _game.next_turn();
                player.set_Blocked(false);
            }
            add_move("arrest");
            one_turn_is_over=1;
            _sanctioned==false;}
        else{
            if(player.coins() > 0&&player.is_active()==true){
            cout<< player.getName() << " arrested" << endl;
            _game.add_last_arrested(player.getName());
            player.set_coins(player.coins()-1);
            _coinNum+=1;
            _game.set_can_do_arrest(true);
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
                _game.next_turn();
                player.set_Blocked(false);
            }
            add_move("arrest");
            one_turn_is_over=1;
            _sanctioned==false;
            //_game.set_can_do_arrest(true);
            }else{
                throw runtime_error("You can't arrest a player with 0 coins or if he is dead");
            }
        }}
                
}
    void Player:: sanction(Player &player){
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }start();
        if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }
        if(player==*this){
        throw runtime_error("you cant activate this action on yourself");
        }
        if(player.role()=="Judge"&&player.is_active()==true){
            if(_coinNum<4){
                throw runtime_error("You need 4 coins to sanction a judge");
            }
            cout<< player.getName() << " sanctioned" << endl;
            player._sanctioned=true;
            player.set_one_turn_is_over();
            _coinNum-=4;
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
                _game.next_turn();
                player.set_Blocked(false);
             }
            add_move("sanction");
            //one_turn_is_over=1;
            _sanctioned==false;
        }else{

            if(_coinNum<3){
                throw runtime_error("You need 3 coins to sanction a player");
            }
            if(player.is_active()==true){
                cout<< player.getName() << " sanctioned" << endl;
            player._sanctioned=true;
            _coinNum-=3;
            
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
                _game.next_turn();
                player.set_Blocked(false);
             }
            add_move("sanction");
            one_turn_is_over=1;
            _sanctioned=false;}
            else{throw runtime_error("You can't sanction a player  if he is dead");}
            }
            
    }
    void Player ::start(){}; 
}
