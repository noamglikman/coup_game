
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Game.hpp"
#include "GameGUI.hpp"


#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace coup;

int main() {
    

    Game game_1{};

    Governor governor(game_1, "Dotan");
    Spy spy(game_1, "Taliya");
    Baron baron(game_1, "Noam");
    General general(game_1, "Itamar");
    Judge judge(game_1, "Rei");
    merchant merchant(game_1, "Moshe");
    vector<string> players = game_1.players();
    
    // Expected output:
    // Moshe
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for(string name : players){
        cout << name << endl;
    }

    // Expected output: Moshe
    cout << game_1.turn() << endl;
    cout<<"here"<<endl;
    governor.gather();
    
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();
    merchant.gather();
    // Expected exception - Not spy's turn
    try{
        spy.gather();
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    governor.gather();
    spy.tax();

    // Expected exception - Judge can undo only bribe
    try{
        judge.undo(governor);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    cout << governor.coins() << endl; // Expected: 2
    cout << spy.coins() << endl; // Expected: 3

    governor.undo(spy); // Governor undo tax
    cout << spy.coins() << endl; // Expected: 1

    baron.tax();
    general.gather();
    judge.gather(); 
    merchant.gather();
    governor.tax(); 
    spy.gather();
    baron.invest(); // Baron traded its 3 coins and got 6 
    general.gather();
    judge.gather();
    merchant.gather();
    cout << baron.coins() << endl; // Expected: 6

    governor.tax();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();
    merchant.gather();
    governor.tax();
    spy.gather();
    cout << baron.coins() << endl; // Expected: 7
    //baron.coup(governor); // Coup against governor
    baron.gather();
    cout << baron.coins() << endl; // Expected: 7
    general.gather();
    judge.gather();
    merchant.gather();
    players = game_1.players();
    // Since no one blocked the Baron, the expected output is:
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for (string name : players) {
         cout << name << endl;
     }
    governor.coup(spy); // Coup against spy

    cout<<governor.coins()<<endl; // Expected: 4
    cout<<baron.coins()<<endl; // Expected: 5
    cout<<general.coins()<<endl; // Expected: 5
    cout<<judge.coins()<<endl; // Expected: 7
    cout<<merchant.coins()<<endl; // Expected: 8
    
    cout<<game_1.turn()<<endl;
    cout<<spy.is_active()<<endl;


    cout<< game_1<<endl;




    baron.gather();
    general.sanction(baron);
    judge.gather();
    merchant.gather();
    governor.gather();
    
    try{
        baron.tax();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n'; // Expected: You can't tax after you have been sanctioned
        baron.arrest(governor);
    }
    cout<< baron.coins() << endl; // Expected: 8
    
    //cout<< game_1<<endl;
    try{
        general.bribe();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    general.gather();
    try{
        judge.undo(general);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    
    cout<< merchant.coins() << endl; // Expected:11 
    judge.gather();
    merchant.gather();
    governor.gather();
    cout<<game_1.turn()<<endl; 
    //general.undo_coup(merchant);
    cout<< game_1<<endl;
    baron.coup(general);
    judge.gather();
    merchant.coup(baron);
    governor.bribe();
    cout<<game_1.turn()<<endl;
    judge.undo(governor);
    
    cout<<game_1.turn()<<endl;
    
   
    
    cout<< game_1<<endl;
    // baron.arrest(general);
    // general.gather();
    // merchant.coup(baron);//nothing happened
    
    //stay the same after i did arresrt to general
    //////להמשיך לממש את הברייב ,אם הפעולה החארונה היא ברייב לא לקדם את התור אחרת כן לקדם
    //cout<<game_1.winner()<<endl; // Expected: the winner is: merchant
    
}
