//noamglikman1@gmail.com
#ifndef GAME_HPP
#define GAME_HPP
// Game.hpp
#include <iostream>
#include <vector>
#include "Player.hpp"

using namespace std;
namespace coup {
    //class Player;
    class Game {
    public:
        Game(){}
        string turn(){
            if (_players.empty()) {
                throw runtime_error("No players in the game");
            }
            return _players[index%_players.size()]->getName();
        }
        // Returns the name of the current players
        vector<string> players(){
            vector<string> player_names;
            for(int i=0; i<_players.size(); i++){
                if(_players[i]->is_active() != false){
                    player_names.push_back(_players[i]->getName());
                }
            }
            return player_names;
        }
        // Returns the name of the current players
        string getNameini(int i){
            return _players[i]->getName();
        }
        // Returns the name of the current players
        Player* getPlayerByindex(int i);
        //add a player to the game
        void add_player(Player* player);
        //remove a player from the game
        void remove_player(Player& player,bool using_gui=false);
        //next turn
        void next_turn() {
    // פתח את החסימה של השחקן האחרון ששיחק (אם יש כזה)
    if (!last_played.empty()) {
        Player* last = last_played.back();
        if (last != nullptr) {
            last->set_sanctioned(false); // ודא שיש set_sanctioned(bool) במחלקת Player
            last->set_one_turn_is_over();
        }
    }

    do {
        index++;
        Player* currentPlayer = _players[index % _players.size()];

        // דלג על שחקנים שאינם פעילים
        if (!currentPlayer->is_active()) {
            continue; // דלג לשחקן הבא
        }

        // בדוק אם השחקן "תקוע"
        if (currentPlayer->is_sanctioned() && currentPlayer->get_Blocked() == true && currentPlayer->coins() == 0) {
            std::cout << currentPlayer->getName() << " is stuck! Turn is over automatically." << std::endl;
            continue; // דלג לשחקן הבא
        }

        // אם השחקן לא תקוע ולא מת, עדכן את התור
        _turn = currentPlayer->getName();
        std::cout << "Turn updated to: " << _turn << std::endl; // הודעה למעקב
        break;
    } while (true);
}
        string winner(){
            int count=0;
            for(int i = 0; i < _players.size(); i++) {
                if (_players[i]->is_active() == true) {
                    count++;;
                }
            }
            if(count>1){
                throw runtime_error("Game is not over yet");
            }
            else{
                _game_over = true;
                return _players[index%_players.size()]->getName();
            }
        }
        //void set_game_over(bool game_over);
        void add_last_arrested(const string &name){
            last_arrested.push_back(name);
        }
        string get_last_arrested() const {
            if (!last_arrested.empty()){return last_arrested.back();} 
            return""; 
        }

        friend ostream& operator<<(ostream& os, const Game& game) {
            os << "Game Players:\n";
            for ( int i = 0; i < game._players.size(); ++i) {
                if (game._players[i]->is_active() == false) {
                    continue; // Skip inactive players
                }
                Player* player = game._players[i];
                os << "Name: " << player->getName()
                   << ", Active: " << (player->is_active() ? "Yes" : "No")
                   << ", Role: " << player->role()
                   << ", Coins: " << player->coins() << "\n";
            }
            return os;
        }
        void add_to_players_is_out_of_game(string player_name){
            _players_is_out_of_game.push_back(player_name);
        }
        string get_last_in_players_is_out_of_game() {
            if (!_players_is_out_of_game.empty()) {
                return _players_is_out_of_game.back();
            } else {
                throw runtime_error("No players available for undo coup");
            }
        }
        Game& operator=(const Game& other) ;
        // הוסף במחלקה Game:

        void add_last_played(Player* player) {
        last_played.push_back(player);
        }
        Player * get_last_player(){
            if (!last_played.empty()) {
                return last_played.back();
            } else {
                throw runtime_error("No players available for undo coup");
            }
        }
        // Game.hpp
        bool is_game_over() const {
            return _game_over;
        }
        Player* get_last_couped_player() const { return _last_couped_player; }
        void set_last_couped_player(Player* p) { _last_couped_player = p; }
            ~Game(){}
            // Destructor

    private:
        vector<Player*> _players;
        std::string winnerMsg = "";
        vector<string>last_arrested;
        Player* _last_couped_player;
        string _turn;
        bool _game_over=false;
        int index =0;
        vector<Player*> last_played;
        vector<string> _players_is_out_of_game;
    };
}




#endif // Game_H