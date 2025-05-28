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
        // Constructor
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
        vector<Player*> get_players(){
            return _players;
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
        
        // This function updates the turn to the next active player.
        // It skips inactive players and handles cases where the current player is sanctioned or blocked.
        // If the last played player is not active, it will set the next active player as the current turn.
        // If no active players are found, it will continue to loop until a valid player is found.
        // It also resets the last played player's sanctioned status and marks their turn as over.
        // If the last played player is sanctioned and blocked and dont have enough money *or* not blocked but cant 
        //do arrest because the player that left with him is the one that got arrested last time
        //(edge case), it will automatically end their turn.
        /**
         * @brief Advances the game to the next player's turn.
         */
        void next_turn() {
        //
        if (!last_played.empty()) {
            Player* last = last_played.back();
            if (last != nullptr) {
                last->set_sanctioned(false); 
                last->set_one_turn_is_over();
            }
        }

        do {
            index++;
            Player* currentPlayer = _players[index % _players.size()];

            if (!currentPlayer->is_active()) {
                continue; 
            }
            // Check if the current player is sanctioned and blocked, and has less than 3 coins
            // or if they are sanctioned and cannot do an arrest
            // (edge case where the last arrested player is the same as the current player)
            if ((currentPlayer->is_sanctioned() && currentPlayer->get_Blocked() == true && currentPlayer->coins() <3 )||(currentPlayer->is_sanctioned() 
            && get_can_do_arrest(_players,currentPlayer)==false&&currentPlayer->coins() <3))
            {
                std::cout << currentPlayer->getName() << " is stuck! Turn is over automatically." << std::endl;
                continue; 
            }
            _turn = currentPlayer->getName();
            std::cout << "Turn updated to: " << _turn << std::endl;
            break;
        } while (true);
    }
    /**
     * @brief Returns the name of the current player.
     * @return The name of the current player.
     * @throws if the game is no over yet.
     */
    //winner function
    // Returns the name of the winner if the game is over, otherwise throws an error
    // This function checks if there is only one active player left in the game.
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
        //operator overload for printing the game state
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
        /// @brief Adds a player to the game.
        /// @param player Pointer to the player to be added.
        /// @param player_name 
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
        Game& operator=(const Game& other);
        /**
         * @brief Adds a player to the last played list.
         * @param player Pointer to the player to be added.
         */
        void add_last_played(Player* player) {
        last_played.push_back(player);
        }
        /**
         * @brief Returns the last player who played.
         * @return Pointer to the last player who played.
         * @throws if there are no players available for undo coup.
         */
        Player * get_last_player(){
            if (!last_played.empty()) {
                return last_played.back();
            } else {
                throw runtime_error("No players available for undo coup");
            }
        }
        /**
         * @brief Checks if the game is over.
         * @return True if the game is over, false otherwise.
         */
        bool is_game_over() const {
            return _game_over;
        }
        Player* get_last_couped_player() const { return _last_couped_player; }
        void set_last_couped_player(Player* p) { _last_couped_player = p; }
        void set_can_do_arrest(bool _can_do_arrest){
            _can_do_arrest=_can_do_arrest;
        }
        /**
         * @brief Checks if a player can do an arrest.
         * @param players Vector of players in the game.
         * @param currentPlayer Pointer to the current player.
         * @return True if the player can do an arrest, false otherwise.
         */
        bool get_can_do_arrest(vector<Player*> players,Player *currentPlayer){
            for(int i=0;i<players.size();i++){
                if(_players[i]->is_active() == true&&_players[i]!=currentPlayer&&get_last_arrested()!=_players[i]->getName()){
                    return true;
                }
            }
            return false;
        }
        ~Game(){}
        // Destructor

    private:
        bool _can_do_arrest=true;
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