

# Coup Game Implementation

## Overview
Coup is a strategy-based board game for 2–6 players, where each player competes to be the last one standing. In this assignment, we implement part of the game’s mechanics and rules in C++.

## game rule

At the beginning of the game, each player is assigned a secret role by drawing a card from the deck. Each role grants unique abilities. There is a shared pool of coins at the center. On their turn, players perform actions based on their role (details below) and can collect or spend coins accordingly. The goal of the game is to perform "coups" and eliminate other players. The last player remaining wins.

Each player has:
A name
A role
A number of coins

Roles and Abilities
Governor
Gains 3 coins (instead of 2) when using tax().

Can block other players' tax() actions.

Spy
Can view another player’s coin count and prevent them from using arrest() on their next turn.

This ability is free and does not consume the Spy’s turn.

Baron
Can invest 3 coins to receive 6 coins in return.

If targeted by sanction(), receives 1 coin as compensation (max loss is 1 coin).

General
Can pay 5 coins to block a coup() against any player (including themselves).
The attacker loses the 7 coins used for the coup.

If arrested, the General recovers the 1 coin taken.

Judge
Can cancel another player’s bribe(), causing them to lose the 4 coins spent.

If sanctioned, the attacker must pay an extra coin to the treasury.

Merchant
If the turn begins with 3 or more coins, the Merchant gains 1 free coin.

If arrested, the Merchant pays 2 coins to the treasury instead of losing 1 to another player.



## Classes and Roles
- `Game` – Manages the game flow and tracks players.
- `Player` – Abstract base class for all roles.
- `Governor` – Special role that gains 3 coins from `tax()` and can block other players’ `tax()` actions.
- `Spy` – Can inspect another player’s coins and prevent them from using `arrest()` on their next turn.
- `Baron` – Can invest 3 coins to receive 6, and gains compensation if targeted by `sanction()`.
- `General` – Can block a `coup()` by paying 5 coins and recovers coins if arrested.
- `Judge` – Can cancel a `bribe()` action and penalize attackers who use `sanction()` on them.
- `Merchant` – Gains a bonus coin when starting a turn with 3 or more, and redirects arrest cost to the treasury.

## Build and Run
- The project includes a `Makefile` for easy compilation.
- A graphical interface is available via the `GameGUI` class (optional for visualizing the game).

To build the project:
```bash
make
```
* **Project stracture:**
with run "tree" in terminal

```bash
.
├── CPP
│   ├── Baron.cpp
│   ├── Game.cpp
│   ├── General.cpp
│   ├── Governor.cpp
│   ├── Judge.cpp
│   ├── Merchant.cpp
│   ├── Player.cpp
│   └── Spy.cpp
├── Demo.cpp
├── GameGUI.cpp
├── GameGUI.hpp
├── HPP
│   ├── Baron.hpp
│   ├── Game.hpp
│   ├── General.hpp
│   ├── Governor.hpp
│   ├── Judge.hpp
│   ├── Merchant.hpp
│   ├── Player.hpp
│   └── Spy.hpp
├── OBJ
│   ├── Baron.o
│   ├── Game.o
│   ├── General.o
│   ├── Governor.o
│   ├── Judge.o
│   ├── Merchant.o
│   ├── Player.o
│   ├── Spy.o
│   └── test.o
├── README.md
├── Tests
├── doctest.h
├── makefile
├── test.cpp
└── tests
```
## Unit Tests
Unit tests are written using the Catch2 framework.  
Each tes1. Test Game and Player functionality
Verifies that players are added correctly, turns proceed in order, and the gather() action correctly increases each player's coin count.

2. Test Governor functionality
Tests that the Governor gains 3 coins from tax() and can cancel another player's tax() action using undo().

3. Test Spy functionality
Checks that the Spy can block another player from using arrest() and that doing so throws an exception if the player is blocked.

4. Test Baron functionality
Verifies that the Baron can invest 3 coins to gain 6, and that he receives a compensation coin when targeted by sanction().

5. Test General functionality
Confirms that the General can cancel a coup() using undo_coup(), and regains coins lost via arrest().

6. Test Judge functionality – Bribe
Checks that the Judge can cancel a bribe() and cause the briber to lose 4 coins. Also ensures a player must pay 4 coins to sanction a Judge.

7. Test Judge functionality – Sanction Cost
Verifies that sanctioning a Judge reduces the attacker's coins correctly (by 4).

8. Test Merchant functionality
Confirms the Merchant gets a bonus coin if they start a turn with ≥3 coins, and pays 2 coins to the treasury when arrested.

9. Test: More than 10 coins
Ensures a player with more than 10 coins must perform a coup(). Any other action (like tax) throws an exception.

10. Test Game Victory
Simulates full game flow: one player performs coup() and wins. Ensures winner is declared and no further actions are allowed.

11. Test Automatic Turn Transition
Validates that a blocked, sanctioned, and broke player cannot move — turn is automatically passed.

12. Test: Arresting the Same Player Twice
Checks that a player cannot arrest the same target twice in a row. Throws an exception if attempted.

13. Test: Bribe Twice
Confirms that a player can bribe multiple times (if coins allow), and actions work correctly between bribes.

14. Test: Not Spy's Turn
Verifies that a player cannot act outside of their turn — all actions (gather, tax, etc.) must throw if called when it's not the player’s turn.

15. Test: Undo for Wrong Action (Governor)
Ensures the Governor can only undo valid tax actions, and not perform undo on unrelated or invalid actions.

16. Test: Undo for Wrong Action (Cross-role)
Checks that roles cannot perform undo actions that are outside their responsibility — e.g., General can’t undo tax or unrelated actions.

17. Test: General Without Enough Coins
Verifies that a General cannot cancel a coup() unless they have at least 5 coins.

18. Test: Action on Self
Ensures that players cannot perform actions on themselves, such as blocking their own actions.

19. Test: Action on Dead Player
Validates that no action (gather, tax, bribe, etc.) can be performed on a player who has been eliminated from the game.

20. Test: Gather
Tests that all roles can successfully gather coins and that the last move is recorded correctly as gather.

21. Test: Tax
Ensures each role gains the correct number of coins from tax() (e.g., Governor gets 3, others get 2).

22. Test: Sanction
Verifies that a sanctioned player cannot perform gather() or tax() during their turn.

23. Test: Undo When Target Has No Coins
Checks that Governor cannot undo tax if the target has already spent the coins.

24. Test: Stuck Player – No Action Possible
Simulates a case where a player is completely blocked and must auto-skip their turn due to no available actions.

25. Test: Stuck Player With Bribe
Same as #24, but the player has just enough coins to perform bribe() as a fallback — tests if it works.

26. Duplicate: Judge Sanction
(Repeat of test #7 — can be merged.)

27. Duplicate: Spy Block
(Covered in test #3.)

28. Duplicate: Merchant Arrest Handling
(Already covered in test #8.)

29. Duplicate: Governor Undo
(Already covered in test #2.)

30. Duplicate: Baron Invest
(Already covered in test #4.)

31. Duplicate: General Undo Coup
(Already covered in test #5.)

32. Duplicate: Game and Player Basics
(Already covered in test #1.)t checks key game behaviors and edge cases.



## Details about the given classes ##
A brief explanation before:
We have the game and player classes, which are the main ones. For each role in the game, there is a separate class that inherits from player by implementing virtual functions.
## Game.cpp ##
This code snippet defines several core functions of the Game class within the coup namespace, which manages the state and flow of the game. The add_player function adds a new player to the game’s player list and sets the current turn to that player’s name. The remove_player function marks a player as inactive and announces their removal from the game, supporting an optional graphical interface flag (using_gui). The method getPlayerByindex safely retrieves a player pointer by their index in the players list, throwing an exception if the index is invalid. Finally, the assignment operator (operator=) allows for copying the state from one Game instance to another, including the turn information, game-over status, player list, and other related attributes. Together, these functions enable managing players' participation and game progression within the game engine.
## Player ##
This code defines the implementation of the Player class inside the coup namespace.
The Player class interacts closely with the Game class and manages a single player's state, actions, and game rules enforcement.
Constructor (Player::Player): When a new player is created, the constructor initializes the player's name, role, status (active/inactive), and coin count. It performs validation checks, ensuring the name is not empty and the game isn't already full (max 6 players). It then registers the player into the game by calling _game.add_player(this).
Actions (gather, tax, coup, bribe, arrest, sanction): These functions implement the core gameplay moves a player can perform, each carefully validating conditions such as:
The game not being over,
The player being active,
It being the player's turn,
Players having the required coins for certain actions,
Special role-related rules (e.g., Governor role gets more coins on tax),
Restrictions if the player is "sanctioned" or blocked,
Enforcing the rule that players must coup if they have 10 or more coins.
Gather increases the player's coins by 1 unless certain sanctions apply, and manages turn progression.
Tax allows a player to collect more coins (2 or 3 depending on their role) with similar checks and turn management.
Coup costs 7 coins and forces another player to be removed from the game, disallowing self-targeting and managing game state changes accordingly.
Bribe lets the player pay 4 coins, with restrictions if sanctioned, and includes some automatic turn progression if the player is stuck.
Arrest is an action targeting another player, with exceptions based on roles (like General or Merchant) and rules preventing repeated arrests on the same player in consecutive turns.
Sanction applies a penalty to another player, with different costs and effects depending on whether the target is a Judge or another role.
Throughout the methods, there are checks on the game state (_game.is_game_over()), active status (_is_active), and turn order (_game.turn() == _name), ensuring strict adherence to game rules.
The code also tracks the last moves and applies various flags to control blocking, sanctioning, and turn endings.
Error handling is done through exceptions like runtime_error and invalid_argument to enforce correct usage.
In summary, this code provides the logic for player actions within a turn-based game environment, enforcing game rules, managing coin balances, player status, and integrating with the overall game state to maintain consistent play flow.
## GameGUI ##
GameGUI Overview
The GameGUI.cpp file is responsible for the graphical user interface (GUI) of a Coup-style game, implemented using the SFML graphics library.
It handles all visual elements, player interaction, and graphical game logic.
1. Main Menu
Displays a window with a “Start” button.
Once clicked, it proceeds to a screen where:
The user enters the number of players (2–6).
Then enters a name for each player.
2. Player Creation
The creat_player function assigns each player a random role from the available classes:
General, Spy, Baron, Governor, Judge, or Merchant.
3. In-Game Board (Player Dashboard)
Displays a visual "card" for each player, including:
Player name, role, number of coins, status (alive/dead), sanction/block indicators.
Shows action buttons based on the player’s role:
e.g., gather, tax, coup, bribe, block arrest, etc.
Special “Undo” buttons appear for roles like:
Governor, General, and Judge.
Highlights the current player’s turn with a green ✓ symbol.
Handles game flow (turn passing, victory display, etc.).
4. Special Functions
askGeneralSave: Pops up a prompt asking if the General wants to save themselves (e.g., from a coup).
Additional logic includes:
Undo actions, block handling, action targeting, and role-based abilities.
5. Main Function
Drives the overall game:
Displays the main menu.
Creates players with randomized roles.
Launches the player board interface.
Cleans up memory at the end.
Key Features & Technologies
Graphics/UI: SFML library (sf::RenderWindow, sf::Text, sf::RectangleShape, etc.).
Game logic integration: Uses Game, Player, and role-specific class headers.
Turn-based system with visual feedback and interactive decision-making.
## Baron.cpp ##
These are actions that the Baron player can perform during their turn.
They include checks for game state, turn order, and player's coin count.
The invest action tries to trade coins for a bigger payoff.
The tax action gains coins, possibly reduced if the player is sanctioned.
Moves are recorded, and the game advances turns accordingly.
## General.cpp ##
The General class is a special player role in the game with the unique ability to undo a coup performed on another player by spending 5 coins. It enforces game rules such as player activity, sufficient coins, and validates that the last move to undo was indeed a coup. The class also includes a graphical prompt (using SFML) that asks the player if they want to pay coins to stay alive, providing an interactive yes/no window for player input.
## Governor.cpp ##
The Governor class is a player role with the ability to undo another player’s last tax action by removing 2 coins from that player. It enforces game rules such as checking if the game is over, player activity, that the target’s last move was a tax, and prevents undoing on oneself. Additionally, it requires the Governor to have fewer than 10 coins (to avoid mandatory coups). The class updates the move history accordingly.
## Judge.cpp ##
The Judge class is a player role with the unique ability to undo a bribe action performed by another player. It enforces game rules such as checking if the game is over, player activity, and that the player has fewer than 10 coins (to avoid mandatory coups). The Judge cannot undo their own bribe and can only undo if the targeted player’s last move was a bribe. After undoing, the targeted player is blocked from performing further bribes. The class updates the game state and advances the turn accordingly.
## Marchant.cpp ##
If the turn begins with 3 or more coins, the Merchant gains 1 free coin.oll the rest is the same.
## Spy.cpp ##
The Spy can view any player’s coin count and block another player’s action (except themselves). When blocking, the Spy marks the target as blocked and updates game state.
## Demo ##
A new game is created with players having roles like Governor, Spy, Baron, General, Judge, and Merchant. Each player performs actions such as gather, tax, coup, undo, etc., following the game rules (e.g., you can’t act if it’s not your turn or if you’re sanctioned). The code also handles runtime exceptions for invalid moves and tests various game scenarios. In the end, it shows different game states like rounds played, each player’s coins, and whose turn is next.




# noam_coup
