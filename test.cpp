//noamglikman1@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

//#include <doctest/doctest.h>
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

// Make sure Merchant is declared in the coup namespace and included via "Merchant.hpp"

TEST_CASE("בדיקה לדוגמה") {
    CHECK(1 + 1 == 2);
}
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
////////////////////פעולות על שחקנים 
//הטסט הזה בודק אם המושל יכול לעשות tax
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
//הטסט הזה בודק אם ספאי יכול לחסום את הברון
TEST_CASE("Test Spy functionality") {
    coup::Game game;
    Spy spy(game, "Taliya");
    Governor governor(game, "Noam");
    spy.block(governor);
    cout<<governor.get_Blocked()<<endl; // Should print true
    CHECK_THROWS_AS(governor.arrest(spy), std::runtime_error); // You are blocked and cannot arrest others
}
//הטסט הזה בודק אם ברון יכול להשקיע את המטבעות שלו
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
//בודק אם מישהו חזר לחיים אחרי coup
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
    cout<<game.turn()<<"ggggggggggggggggggggggggggggggggggggg"<<endl;
    general.gather();
    baron.gather();
    cout<<game.turn()<<endl;
     spy.gather();
    general.gather();
    baron.arrest(general); // Baron tries to arrest General and we will see that nothing happens
    CHECK(general.coins() == 5); // General should still have 8 coins
}
//הטסט הזה בודק שכשאר עושים bribe ומישהו עושה undo_bribe אז התור עובר לבא
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
//כאשר עוצרים שופט זה עולה 4 מטבעות
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

//האם באמת merchant מקבל על כל שלוש מטבעות בתחילת תורו עוד מטבע רואים כאן שכאשר עושים arrest אז זה הולך לקוםפה ולא לשחקן עצמו
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
//בדיקה אם מישהו ניצח
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
//מקרי קצה
//כאשר שחקן מסויים עשו עליו sanctuon וגם spy חסם אותו וגם אין לו כסף
TEST_CASE("Test automatic turn transition") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    // הוסף שחקנים למשחק
    for (int i = 0; i < 4; ++i) {
        governor.gather();
        spy.gather();
    }

    // הגדר מצב שבו Noam "תקוע"
    governor.tax();
    governor.set_coins(0); // Set governor's coins to 0
    spy.sanction(governor); // Spy blocks Governor
    spy.block(governor); // Spy blocks Governor
    // בדוק שהתור עובר ל-Taliya
    CHECK(game.turn() == "Taliya");
}
TEST_CASE("Test automatic turn transition") {
    coup::Game game;
    Governor governor(game, "Noam");
    Spy spy(game, "Taliya");

    // הוסף שחקנים למשחק
    for (int i = 0; i < 4; ++i) {
        governor.gather();
        spy.gather();
    }

    // הגדר מצב שבו Noam "תקוע"
    governor.tax();
    governor.set_coins(0); // Set governor's coins to 0
    spy.block(governor); // Spy blocks Governor
    spy.sanction(governor); // Spy sanctions Governor
    // בדוק שהתור עובר ל-Taliya
    CHECK(game.turn() == "Taliya");
}
//assertion failure
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
//bribe twice
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
}
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