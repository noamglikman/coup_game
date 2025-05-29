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
        // Validate the player's name and game state
        if (_name.empty()) {
            throw invalid_argument("Player name cannot be empty");
        }
        // Check if the game is already full
        if (_game.players().size() >= 6) {
            throw runtime_error("Game is full");
        }
        // Check if the player's name already exists in the game
        for(int i=0;i<game.players().size();i++){
            if(name==game.getNameini(i)){
                cout<<"name is already exist"<<endl;
                throw runtime_error("name is already exist");
                
            }
        }
        _game.add_player(this);
        
    }
    /**
     * @brief Returns the name of the player.
     * @return The name of the player.
     */
    void Player::gather() {
        // Check if the game is over
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        // Check if the player is active
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        // Check if it's the player's turn
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }
        //Check if he has 10 or more coins
        if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }
        start();
        //Baron situation
        if(_role=="Baron"&&_sanctioned==true){
            cout<< _name << " gother but he was sanctioned so his coins stay the same "<<_role << endl;
            //if we are not in bribe we can move turn
            if(LastMove_of_each_player()!="bride"){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
            }
            //if we are in bribe butblocked by judge we can move turn
            if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
                _cant_bribe=false;
                cout<<_name<<" can bribe now"<<endl;
            }
        add_move("gather");
        }else{
            // If the player is not sanctioned, they can gather coins
            if(one_turn_is_over==0 && _sanctioned==true){
            throw runtime_error("You can't gather after you have been sanctioned");
        }
        else{
            cout<< _name << " gathered coins " << endl;
            _coinNum++;
            // If the last move was not a bribe, proceed to the next turn
            if(LastMove_of_each_player()!="bribe"){
                _game.add_last_played(this);
               _game.next_turn();
               set_Blocked(false);
            }
            // If the last move was a bribe and the player is blocked
            if(LastMove_of_each_player()=="bribe"&&_cant_bribe==true){
                _game.add_last_played(this);
                _game.next_turn();
                set_Blocked(false);
                _cant_bribe=false;
                cout<<_name<<" can bribe now"<<endl;
            }
        add_move("gather");
    }}
        
        } 
    void Player::tax(){
        // Check if the game is over
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        // Check if the player is active
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        // Check if it's the player's turn
        if( _game.turn() != _name) {
            throw runtime_error("It's not your turn");
        }
        // Check if the player is sanctioned and one turn is not over yet
        if(one_turn_is_over==0&&_sanctioned==true){
            throw runtime_error("You can't tax after you have been sanctioned");
        }
        // Check if the player has 10 or more coins
        if(_coinNum>=10){
            throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
        }

        start();
        // If the player is a Governor and not sanctioned, they can tax
        if(_role=="Governor"&&_sanctioned==false){
        _coinNum+=3;
        cout<< _name << " taxed "<<_role << endl;
        // If the last move was not a bribe, proceed to the next turn
        if(LastMove_of_each_player()!="bribe"){
            _game.add_last_played(this);
            _game.next_turn();
            set_Blocked(false);
            }
        // If the last move was a bribe and the player is blocked
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
//*
    /**
     * @brief Coup another player, removing them from the game.
     * @param player The player to be couped.
     * @param using_gui Indicates if the action is being performed through a GUI.
     * @throws runtime_error If the game is over, the player is not active, or it's not the player's turn.
     */
void Player::coup(Player &player,bool using_gui){
    // Check if the game is over
    if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
    // Check if the player is active
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    //if the player is sanctioned and one turn is not over yet
    if(one_turn_is_over==0&&_sanctioned==true){
        throw runtime_error("You can't coup after you have been sanctioned");
    }
    // Check if it's the player's turn
    if( _game.turn() != _name) {
        throw runtime_error("It's not your turn");
    }
    //if he has less then 7 coins
    if(_coinNum<7){
        throw runtime_error("You need 7 coins to coup");
    }
    //cant do action on himself
    if(player==*this){
       throw runtime_error("you cant activate this action on yourself");
    }
     start();
    cout<< player.getName() << " couped" << endl;
    _coinNum-=7;
    //player.set_active(false);
    _game.remove_player(player,using_gui);
    // Update the last couped player
    _couped = player.getName();
    // Set the last couped player in the game
    _game.set_last_couped_player(&player);
    cout<<_game.get_last_couped_player()->getName()<<" is the last player that was couped"<<endl;
    //if we are not in bribe we can move turn
    if(LastMove_of_each_player()!="bribe"){
        _game.next_turn();
        player.set_Blocked(false);
    }
    //if we are in bribe but blocked by judge we can move turn
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
 
void Player:: bribe(){
    // Check if the game is over
    if(_game.is_game_over()) {
        throw runtime_error("Game is over, you can't gather");
    }
    // Check if the player is active
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    // Check if it's the player's turn
    if( _game.turn() != _name) {
        throw runtime_error("It's not your turn");
    }
    // Check if the player is sanctioned and one turn is not over yet
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    // Check if the player has enough coins to bribe
    if(coins() < 4){
        throw runtime_error("You can't bribe  with less then 4 coins,try someone else...");
    }
    //check if player is sanctioned blocked by spy have no coins and cant do arrest or is sanctioned and can not arrest
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

//*
    /**
     * @brief Starts the player's turn, resetting the one_turn_is_over flag.
     */
string Player::_get_couped(){
    return _couped;
}
/**
 * @brief Arrests another player, reducing their coins.
 * @param player The player to be arrested.
 * @throws runtime_error If the game is over, the player is not active, or it's not the player's turn.
 * @throws runtime_error If the player is blocked from arresting others.
 * @throws runtime_error If the player tries to arrest themselves.
 * @throws runtime_error If the last arrested player is the same as the current player.
 * @throws runtime_error If the player has 10 or more coins and must perform a coup instead.
 * @throws runtime_error If the player tries to arrest a player with 0 coins or if the player is dead.
 * @return void
 */
void Player:: arrest(Player &player){
// Check if the game is over
if(_game.is_game_over()) {
    throw runtime_error("Game is over, you can't gather");
}
// Check if the player is active
if (!_is_active) 
{
    throw runtime_error("Player is not active");
}
// Check if it's the player's turn
if (_game.turn() != _name) {
    throw runtime_error("It's not your turn");
}
// Check if the player is blocked from arresting others
if (get_Blocked()) {
    throw runtime_error("You are blocked and cannot arrest others");
}
if(player.coins()==0){
    throw runtime_error("you cant arrest someone with 0 coins");
}
//cant arrest themself
if(player==*this){
    throw runtime_error("you cant activate this action on yourself");
}
// Check if the last arrested player is the same as the current player
if (_game.get_last_arrested() == player.getName()) {
    throw runtime_error("You can't arrest the same player twice in a row");
}
// Check if the player has 10 or more coins and must perform a coup instead
if(_coinNum>=10){
    throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
}
    start();
// Check if the player is a General and is active
    if(player.role() == "General"&&player.is_active()==true){
        cout<<"arrested general thats why nothing happened"<<endl;
        _game.add_last_arrested(player.getName());
        if(LastMove_of_each_player()!="bribe"){
            _game.add_last_played(this);
            LastMove_of_each_player()="arrest";
            _game.set_can_do_arrest(true);
            _game.next_turn();
            player.set_Blocked(false);
            }
        add_move("arrest");
        one_turn_is_over=1;
        _sanctioned==false;}else{
        if(player.role()=="Merchant"&&player.is_active()==true){
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
    }
}
            
}
/**
 * @brief Sanctions another player, blocking them from performing certain actions.
 * @param player The player to be sanctioned.
 * @throws runtime_error If the game is over, the player is not active, or it's not the player's turn.
 * @throws runtime_error If the player has 10 or more coins and must perform a coup instead.
 * @throws runtime_error If the player tries to sanction themselves.
 * @throws runtime_error If the player is a Judge and has less than 4 coins.
 * @throws runtime_error If the player has less than 3 coins to sanction another player.
 * @return void
 */
void Player:: sanction(Player &player){
    // Check if the game is over
    if(_game.is_game_over()) {
        throw runtime_error("Game is over, you can't gather");
    }
    // Check if the player is active
    if (!_is_active) {
        throw runtime_error("Player is not active");
    }
    // Check if it's the player's turn
    if( _game.turn() != _name) {
        throw runtime_error("It's not your turn");
    }start();
    //Checl if the player have 10 or more coins
    if(_coinNum>=10){
        throw runtime_error("you must coup someone because you have more then 10 coins,choose player to coup");
    }
    //cant activate themself
    if(player==*this){
    throw runtime_error("you cant activate this action on yourself");
    }
    // Check if the player is a Judge and has less than 4 coins
    if(player.role()=="Judge"&&player.is_active()==true){
        if(_coinNum<4){
            throw runtime_error("You need 4 coins to sanction a judge");
        }

        cout<< player.getName() << " sanctioned" << endl;
        player._sanctioned=true;
        player.set_one_turn_is_over();
        _coinNum-=4;
        // If the last move was not a bribe, proceed to the next turn
        if(LastMove_of_each_player()!="bribe"){
            _game.add_last_played(this);
            _game.next_turn();
            player.set_Blocked(false);
            }
        add_move("sanction");
        //one_turn_is_over=1;
        _sanctioned==false;
    }else{
         // Check if the player has less than 3 coins to sanction another player
        if(_coinNum<3){
            throw runtime_error("You need 3 coins to sanction a player");
        }
        if(player.is_active()==true){
            cout<< player.getName() << " sanctioned" << endl;
        player._sanctioned=true;
        _coinNum-=3;
        // If the last move was not a bribe, proceed to the next turn
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
