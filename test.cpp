//noamglikman1@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

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
#include "doctest.h"
using namespace std;
using namespace coup;

//The test checks general functionality of adding a player and the gather operation.
TEST_CASE("Test Game and Player functionality") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    CHECK(game.players().size() == 2);
    CHECK(game.turn() == "Noam");

    governor.gather();
    CHECK(governor.coins() == 1);

    spy.gather();
    CHECK(spy.coins() == 1);

    game.next_turn();
    CHECK(game.turn() == "Taliya");

    spy.gather();
    CHECK(spy.coins() == 2);
}

TEST_CASE("error same name"){
    coup::Game game;
    Governor governor(game, "Noam");
    CHECK_THROWS_AS(Spy spy(game, "Noam"),std::runtime_error);
}
//Governor - Takes 3 coins from the treasury instead of 2 when
// using a tax action. In addition, he can cancel other players' tax actions.
TEST_CASE("Test Governor functionality") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    governor.gather();
    CHECK(governor.coins() == 1);
    spy.gather();
    governor.tax();
    CHECK(governor.coins() == 4); // Governor should have 3 coins from tax

    spy.tax();
    CHECK(spy.coins() == 3);

    governor.undo(spy);
    cout<< "Spy coins after undo: " << spy.coins() << endl;
    CHECK(spy.coins() == 1); // Spy should have 0 coins after undo
}


//Spy - can see another player's coin count and prevent them from using the arrest action on their next turn.
// This action does not cost coins and does not count as a turn.
TEST_CASE("Test Spy functionality") {
    coup::Game game;
    Spy spy(game, "Taliya");
    Governor governor(game, "Noam");
    spy.block(governor);
    cout<<governor.get_Blocked()<<endl; // Should print true
    CHECK_THROWS_AS(governor.arrest(spy), std::runtime_error); // You are blocked and cannot arrest others
}


//Baron - can "invest" 3 coins and receive 6 coins in return. Additionally, if he is attacked by a sanction, he receives 1 coin as compensation 
//(i.e., from the entire process he can lose at most 1 coin if he used a tax).
TEST_CASE("Test Baron functionality") {
    coup::Game game;
    Baron baron(game, "Noam");
    General general(game, "Taliya");

    baron.gather();
    CHECK(baron.coins() == 1);
    general.gather();
    baron.tax();
    general.tax();//nees 3 to sanction
    baron.invest();
    CHECK(baron.coins() == 6); // Baron should have 6 coins after investing
    general.sanction(baron);
    baron.tax();//צריך לקבל מטבע אחד מקסימום כאשר הוא sanctioned
    CHECK(baron.coins() == 7); // Baron should have 7 coins after tax while sanctioned
}


//General - can pay 5 coins to prevent a coup against another player (or against himself).
// Note that in this case the player who carried out the coup loses the coins he paid.
// Additionally, if he is hit by an arrest, he gets back the coin that was taken from him.
TEST_CASE("Test General functionality") {
    coup::Game game;
    General general(game, "Noam");
    Baron baron(game, "Taliya");
    Spy spy(game, "Rei");
    for(int i = 0; i < 7; ++i) {
        general.gather();
        baron.gather();
        spy.gather();
    }
    general.gather();
    baron.coup(spy);
    general.undo_coup(baron);
    cout<<baron.coins()<<endl; // Should print 0, because spy was coup and then revived
    CHECK(baron.coins() == 0);
    CHECK(spy.is_active() == true); // Baron should be inactive after coup 
    
    general.gather();
    baron.gather();
    cout<<game.turn()<<endl;
     spy.gather();
    general.gather();
    baron.arrest(general); // Baron tries to arrest General and we will see that nothing happens
    CHECK(general.coins() == 5); // General should still have 8 coins
}


//Judge - can cancel another player's bribe, causing them to lose the 4 coins they paid. 
//Additionally, if they are attacked with a sanction,
// the player who imposed the sanction must pay an additional coin to the cashier.
TEST_CASE("Test Judge functionality") {
    coup::Game game;
    Judge judge(game, "Noam");
    General general(game, "Taliya");
    for(int i = 0; i < 3; ++i) {
        judge.tax();
        general.tax();
    }
    judge.tax();
    cout<<game.turn()<<endl; // Should print "Taliya"
    //Bribe is working
    general.bribe();
    cout<<game.turn()<<endl; // Should print "Taliya"
    general.tax();
    cout<<game.turn()<<endl; // Should print "Taliya"
    general.tax();
    judge.gather();
    general.bribe();
    cout<<general.LastMove_of_each_player()<<endl; // Should print "bribe"
    CHECK(game.turn() == "Taliya");
    judge.undo_bribe(general);
    CHECK(game.turn() == "Noam");
    judge.gather();
    CHECK_THROWS_AS(general.sanction(judge),std::runtime_error); // need 4 coins to sanction a judge
}


//When you arrest a judge it costs 4 coins.
TEST_CASE("Test Judge functionality") {
    coup::Game game;
    Judge judge(game, "Noam");
    General general(game, "Taliya");
    for(int i = 0; i < 3; ++i) {
        judge.tax();
        general.tax();
    } 
    judge.tax();
    general.sanction(judge);
    CHECK(general.coins() == 2);//if you arrest judge it cost 4 coins
}


//Merchant - If he starts a turn with at least 3 coins, he gets an extra coin for free. Additionally, 
//if he is attacked with an arrest, he pays two coins to the cashier instead of losing one to another player.
TEST_CASE("Test Merchant functionality") {
    coup::Game game;
    merchant merchant(game,"rei");
    General general(game, "Taliya");

    merchant.gather();
    CHECK(merchant.coins() == 1);
    general.gather();
    merchant.tax();
    general.gather();
    merchant.tax();
    CHECK(merchant.coins() == 6); 
    
    general.arrest(merchant); 
    CHECK(merchant.coins() == 4); 
    CHECK(general.coins() == 2); 
    cout<<general.coins()<<endl; 
}


//more then 10 coins test
TEST_CASE("Test more than 10 coins functionality") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i <= 9; ++i) {
        governor.gather();
        spy.gather();
    }
    cout<< "Governor coins: " << governor.coins() << endl; // Should print 10
    cout<< "Spy coins: " << spy.coins() << endl; // Should print 10
    CHECK(governor.coins() == 10);
    CHECK(spy.coins() == 10);

    // you must coup someone because you have more then 10 coins,
    //choose player to coup
    CHECK_THROWS_AS(governor.tax(), std::runtime_error);
}


//This test verifies the game’s victory condition. Two players (Governor and Spy) gather coins
// until the Governor can perform a coup, eliminating the Spy. The test checks that the Spy becomes inactive, 
//the Governor is declared the winner, and no further actions can be taken once the game ends.
TEST_CASE("Test game victory") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i <= 9; ++i) {
        governor.gather();
        spy.gather();
    }
    governor.coup(spy);
    CHECK(spy.is_active() == false); // Spy should be inactive after coup
    // Governor should be forced to coup someone
    CHECK(game.winner() == "Noam"); // Spy is the only player left
    CHECK_THROWS_AS(spy.gather(), std::runtime_error);//spy is not active anymore
    CHECK_THROWS_AS(governor.gather(), std::runtime_error);
}


//importanat Edge cases
//Spy blocked a player and in addition he is sanctioned and he also doesn't 
//have enough money so the player is blocked and has nothing to do at all, 
//so in an automatic step I wrote the turn passes and this is the test.
TEST_CASE("Test automatic turn transition") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for (int i = 0; i < 4; ++i) {
        governor.gather();
        spy.gather();
    }
    //Put Noam in a "stuck" situation
    governor.tax();
    governor.set_coins(0); // Set governor's coins to 0
    spy.block(governor); // Spy blocks Governor
    spy.sanction(governor); // Spy blocks Governor
    cout<<governor.coins()<<endl;
    cout<<spy.coins()<<endl;
    //Check that the line goes to Taliya.
    CHECK(game.turn() == "Taliya");
}


//It is not possible to arrest the same player twice, so in the code I checked before each arrest whether
// the player you want to arrest is the last one arrested or not.
TEST_CASE("areest twice"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i < 3; ++i) {
        governor.gather();
        spy.gather();
    }
    governor.gather();
    spy.arrest(governor);
    CHECK(governor.coins() == 3); // Governor should have 0 coins after arrest
    CHECK_THROWS_AS(spy.arrest(governor), std::runtime_error);
}


//bribe twice:
//You can bribe twice. It doesn't give any advantage, 
//but it's possible and it's a test that the turns are going correctly.
TEST_CASE("bribe twice") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i < 3; ++i) {
        governor.tax();
        spy.tax();
    }
    governor.gather();
    spy.bribe();
    spy.gather();
    spy.gather();
    CHECK_THROWS_AS(spy.bribe(), std::runtime_error); // Spy cannot bribe again with his coins now
}

//Check if it is really blocked
TEST_CASE("NOT Spy's turn") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i < 3; ++i) {
        governor.gather();
        spy.gather();
    }
    CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Spy cannot gather on not his turn
    CHECK_THROWS_AS(spy.tax(), std::runtime_error); // Spy cannot tax on not his turn
    CHECK_THROWS_AS(spy.bribe(), std::runtime_error); // Spy cannot bribe on not his turn
    CHECK_THROWS_AS(spy.arrest(governor), std::runtime_error); 
    CHECK_THROWS_AS(spy.coup(governor), std::runtime_error); 
}


//Check that a player with an undo button can only perform the undo he is allowed to do.
//There are previous tests for each player whose undo works but we'll add it just to be sure.
TEST_CASE("undo for wrong action") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i < 3; ++i) {
        governor.gather();
        spy.tax();
    }
    governor.undo(spy); // Governor undoes Spy's tax action
    governor.gather();
    spy.gather();
    CHECK_THROWS_AS(governor.undo(spy), std::runtime_error); // Governor can only undo tax
}


//Strict check whether a player can activate an undo that is not theirs
TEST_CASE("undo for wrong action") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    Judge Judge(game,"asaf");
    General general(game,"shachar");
    for(int i = 0; i < 3; ++i) {
        governor.gather();
        spy.tax();
        Judge.gather();
        general.gather();
    }
    governor.undo(spy); // Governor undoes Spy's tax action
    governor.gather();
    spy.bribe();
    CHECK_THROWS_AS(governor.undo(spy), std::runtime_error); // Governor can only undo tax
    CHECK_THROWS_AS(governor.undo(spy), std::runtime_error);
    CHECK_THROWS_AS(general.undo_coup(spy), std::runtime_error);
}


//A general cannot cancel a coup without 5 coins.
TEST_CASE("general do not have 5 coins"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    General general(game,"rei");
    for(int i = 0; i < 4; ++i) {
        governor.tax();
        spy.tax();
        general.gather();
    }
    governor.coup(spy);
    CHECK_THROWS_AS(general.undo_coup(governor),std::runtime_error);
}

//A player cannot perform actions on himself.
TEST_CASE("action of yourself"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    General general(game,"rei");
    for(int i = 0; i < 4; ++i) {
        governor.tax();
        spy.tax();
        general.gather();
    }
    CHECK_THROWS_AS(spy.block(spy),std::runtime_error);
}

//Actions cannot be performed on a player who has died, 
//meaning that they have been defeated and are no longer in the game.
TEST_CASE("action on dead player"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    for(int i = 0; i <= 9; ++i) {
        governor.gather();
        spy.gather();
    }
    governor.coup(spy);
    CHECK(spy.is_active() == false);
    CHECK_THROWS_AS(spy.gather(),std::runtime_error);
    CHECK_THROWS_AS(spy.tax(),std::runtime_error);
    CHECK_THROWS_AS(spy.coup(governor),std::runtime_error);
    CHECK_THROWS_AS(spy.sanction(governor),std::runtime_error);
    CHECK_THROWS_AS(spy.arrest(governor),std::runtime_error);
    CHECK_THROWS_AS(spy.bribe(),std::runtime_error);
}

//gather
TEST_CASE("gather"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    merchant merchant(game,"rei");
    Baron baron(game,"naama");
    Judge Judge(game,"or");
    governor.gather();
    spy.gather();
    merchant.gather();
    baron.gather();
    Judge.gather();
    CHECK(Judge.coins()==1);
    CHECK(baron.coins()==1);
    CHECK(merchant.coins()==1);
    CHECK(spy.coins()==1);
    CHECK(governor.coins()==1);
    CHECK(governor.LastMove_of_each_player()=="gather");
}

//tax
TEST_CASE("tax"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    merchant merchant(game,"rei");
    Baron baron(game,"naama");
    Judge Judge(game,"or");
    governor.tax();
    spy.tax();
    merchant.tax();
    baron.tax();
    Judge.tax();
    CHECK(Judge.coins()==2);
    CHECK(baron.coins()==2);
    CHECK(merchant.coins()==2);
    CHECK(spy.coins()==2);
    CHECK(governor.coins()==3);
    CHECK(governor.LastMove_of_each_player()=="tax");
}


//When a player is sanctioned, he cannot *on his turn* gather, tax
TEST_CASE("sanction"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    merchant merchant(game,"rei");
    for(int i = 0; i <= 3; ++i) {
        governor.gather();
        spy.gather();
        merchant.tax();
    }
    governor.sanction(spy);
    CHECK_THROWS_AS(spy.gather(),std::runtime_error);
    CHECK_THROWS_AS(spy.tax(),std::runtime_error);
}

TEST_CASE("arrest"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    merchant merchant(game,"rei");
    for(int i = 0; i <3; ++i) {
        governor.gather();
        spy.gather();
        merchant.tax();
    }
    governor.sanction(spy);
    CHECK_THROWS_AS(spy.arrest(governor),std::runtime_error);
}


//When a spy tries to perform an undo for tax as per his role,
// but the player has already used his money and now there is no money he can return.
TEST_CASE("governor undo but the player have no 2 coins or the last move is not tax"){
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");
    merchant merchant(game,"rei");
    governor.gather();
    spy.tax();
    merchant.arrest(spy);
    CHECK_THROWS_AS(governor.undo(spy),std::runtime_error);
   // cout<<spy.coins()<<"ggggg"<<endl;
}


//An *very important* edge case where two players remain in the game and one player is blocked by a
// sanction, meaning he cannot perform a tax gather and cannot perform an arrest because the player 
//he remains with has already been arrested, so we get a blow and the turn will automatically
// go through the loop in nextturn because *he also doesn't have the money to do anything else*
TEST_CASE(" is stuck! Turn is over automatically "){
    coup::Game game;
    General general(game, "Noam");
    Baron baron(game, "Taliya");
    Spy spy(game, "Rei");
    for(int i = 0; i < 7; ++i) {
        general.gather();
        baron.gather();
        spy.gather();
    }
    general.gather();
    baron.coup(spy);
    general.gather();
    baron.arrest(general);
    general.sanction(baron);
    cout<<baron.coins()<<endl;
    CHECK(game.turn()=="Noam");
}


//An *very important* edge case where two players remain in the game and one player is blocked by 
//a sanction, meaning he cannot perform a tax gather and cannot perform an arrest because the player he
// remains with has already been arrested, so we received a blow and the turn will automatically 
//proceed according to the loop in nextturn because he now has money to perform a bribe.
TEST_CASE(" is stuck with bribe! Turn is over automatically "){
    coup::Game game;
    General general(game, "Noam");
    Baron baron(game, "Taliya");
    Spy spy(game, "Rei");
    for(int i = 0; i < 7; ++i) {
        general.gather();
        baron.gather();
        spy.gather();
    }
    general.gather();
    baron.coup(spy);
    baron.set_coins(7);
    general.gather();
    baron.arrest(general);
    general.sanction(baron);
    baron.set_coins(4);
    cout<<game.turn()<<endl;
    baron.bribe();
    CHECK_THROWS_AS(baron.tax(),std::runtime_error);
}
//Basic actions before and after the game ends
//I checked the actions that will be blocked because the
// game is definitely over and not because of another error
// such as the player on whom the action is being performed is dead, etc.
TEST_CASE("oll action on Baron and General"){
    coup::Game game;
    General general(game, "Noam");
    Baron baron(game, "Taliya");
    general.gather();
    baron.gather();
    CHECK(general.coins()==1);
    CHECK(baron.coins()==1);
    general.tax();
    baron.tax();
    CHECK(general.coins()==3);
    CHECK(baron.coins()==3);
    general.arrest(baron);
    CHECK(general.coins()==4);
    CHECK(baron.coins()==2);
    baron.gather();
    for(int i = 0; i < 3; ++i) {
    general.tax();
    baron.gather();
    }
    general.coup(baron);
    
    CHECK_THROWS_AS(baron.gather(),std::runtime_error);
    CHECK_THROWS_AS(general.tax(),std::runtime_error);
    CHECK_THROWS_AS(general.gather(),std::runtime_error);
    CHECK_THROWS_AS(general.bribe(),std::runtime_error);
    //cout<<game.winner()<<endl;
}

//Basic actions before and after the game ends
//I checked the actions that will be blocked because the
// game is definitely over and not because of another error
// such as the player on whom the action is being performed is dead, etc.
TEST_CASE("oll action on merchant and Governor"){
    coup::Game game;
    merchant merchant(game, "Noam");
    Governor governor(game, "Taliya");
    merchant.gather();
    governor.gather();
    CHECK(merchant.coins()==1);
    CHECK(governor.coins()==1);
    merchant.tax();
    governor.tax();
    CHECK(merchant.coins()==3);
    CHECK(governor.coins()==4);
    merchant.arrest(governor);
    CHECK(merchant.coins()==5);
    CHECK(governor.coins()==3);
    governor.gather();
    merchant.tax();
    governor.gather();
    merchant.coup(governor);
    
    CHECK_THROWS_AS(governor.gather(),std::runtime_error);
    CHECK_THROWS_AS(merchant.tax(),std::runtime_error);
    CHECK_THROWS_AS(merchant.gather(),std::runtime_error);
    CHECK_THROWS_AS(merchant.bribe(),std::runtime_error);
    //cout<<game.winner()<<endl;
}

//Basic actions before and after the game ends
//I checked the actions that will be blocked because the
// game is definitely over and not because of another error
// such as the player on whom the action is being performed is dead, etc.
TEST_CASE("oll action on merchant and Governor"){
    coup::Game game;
    Judge Judge(game, "Noam");
    Spy spy(game, "Taliya");
    Judge.gather();
    spy.gather();
    CHECK(Judge.coins()==1);
    CHECK(spy.coins()==1);
    Judge.tax();
    spy.tax();
    CHECK(Judge.coins()==3);
    CHECK(spy.coins()==3);
    Judge.arrest(spy);
    CHECK(Judge.coins()==4);
    CHECK(spy.coins()==2);
    spy.gather();
    for(int i = 0; i < 3; ++i) {
    Judge.tax();
    spy.gather();
    }
    Judge.coup(spy);
    
    CHECK_THROWS_AS(spy.gather(),std::runtime_error);
    CHECK_THROWS_AS(Judge.tax(),std::runtime_error);
    CHECK_THROWS_AS(Judge.gather(),std::runtime_error);
    CHECK_THROWS_AS(Judge.bribe(),std::runtime_error);
    //cout<<game.winner()<<endl;
}