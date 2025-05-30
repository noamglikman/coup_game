//noamglikman1@gmail.com
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Player.hpp"
#include "General.hpp"



using namespace std;

namespace coup{
    /**
 * @brief Allows the General to undo the last coup action made by any player, by paying 5 coins.
 *
 * This method verifies the validity of the undo operation by checking that the General has enough coins,
 * the game is not over, and the last move of the target player was a coup.
 * If successful, the last couped player is reactivated, and the move is registered as "undo_coup".
 *
 * @param player Reference to the player whose last move will be undone (must be a coup).
 *
 * @throws std::runtime_error If the game is over.
 * @throws std::runtime_error If the General is not active.
 * @throws std::runtime_error If the General does not have at least 5 coins.
 * @throws std::runtime_error If the player's last move was not a coup.
 * @throws std::runtime_error If there is no valid last couped player to restore.
 *
 * @return void
 */
    void General::undo_coup(Player &player) {
        if(_game.is_game_over()) {
            throw runtime_error("Game is over, you can't gather");
        }
        cout << "General is trying to undo a coup" << endl;
        if (!_is_active) {
            throw runtime_error("Player is not active");
        }
        if (coins() < 5) {
            throw runtime_error("You need 5 coins to undo a coup");
        }
        if (player.LastMove_of_each_player() != "coup") {
            throw runtime_error("General can undo only coup");
        }
        if(_game.get_last_couped_player()->is_active()){
            cout << "Player is already active" << endl;
        }
        if (_game.get_last_couped_player() == nullptr || _game.get_last_couped_player()->is_active()) {
            throw runtime_error("No player to undo coup for!");
        }
        // Check if the last couped player is valid
        _game.get_last_couped_player()->set_active(true); 
        //update the last couped player
        add_move("undo_coup");
        _coinNum -= 5; 
        cout << _game.get_last_couped_player()->getName() << " undoed coup" << endl;
        // Reactivate the last couped player
        _game.set_last_couped_player(nullptr);
    }

    /**
 * @brief Displays a GUI dialog using SFML to ask the player whether they wish to pay 5 coins to stay alive.
 *
 * The dialog provides YES and NO buttons. If YES is clicked, the function returns true;
 * otherwise, or if the window is closed, it returns false.
 *
 * @return true if the user clicks "YES" to pay and stay alive.
 * @return false if the user clicks "NO" or closes the window.
 */
    bool General::askToStayAlive() {
        // Create a simple SFML window with a question and two buttons
        sf::RenderWindow window(sf::VideoMode(400, 200), "Stay Alive?");
        sf::Font font;
        // Load a font from a file (make sure the path is correct for your system)
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "Failed to load font\n";
            return false;
        }
        // Create the question text
        sf::Text questionText("Do you want to pay 5 coins to stay alive?", font, 18); // Create the question text
        questionText.setFillColor(sf::Color::Black);
        questionText.setPosition(20, 50);
        // Create YES and NO buttons
        sf::RectangleShape yesButton(sf::Vector2f(100, 50));
        yesButton.setFillColor(sf::Color(100, 200, 100));
        yesButton.setPosition(50, 120);
        // Create YES text
        sf::Text yesText("YES", font, 20);
        yesText.setFillColor(sf::Color::White);
        yesText.setPosition(75, 130);
        // Create NO button
        sf::RectangleShape noButton(sf::Vector2f(100, 50));
        noButton.setFillColor(sf::Color(200, 100, 100));
        noButton.setPosition(250, 120);
        // Create NO text
        sf::Text noText("NO", font, 20);
        noText.setFillColor(sf::Color::White);
        noText.setPosition(275, 130);
        // Main loop to keep the window open
        while (window.isOpen()) {
            sf::Event event;
            // Process events
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return false; 
                }
                // Check for mouse button presses
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    // Check if the mouse is over the YES or NO button
                    if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) { //getting the mouse position on yes button
                        window.close();
                        return true; 
                    }
                    // Check if the mouse is over the NO button
                    if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) { //getting the mouse position on no button
                        window.close();
                        return false; 
                    }
                }
            }
            // Clear the window and draw the question and buttons
            window.clear(sf::Color(240, 240, 240));
            window.draw(questionText);
            window.draw(yesButton);
            window.draw(yesText);
            window.draw(noButton);
            window.draw(noText);
            window.display();
        }

        return false; 
    }

}
    
