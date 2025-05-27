#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "GameGUI.hpp"


using namespace std;
using namespace coup;
 //Player* createPlayers(Game& game, std::string playerName, int numPlayers);
void runGameSetup(std::vector<std::string>& playerNames) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Setup");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Failed to load font\n";
        return;
    }

    enum class State { AskNumber, AskNames, Done };
    State state = State::AskNumber;

    int numPlayers = 0;
    int currentPlayer = 1;
    std::string inputText;

    sf::Text prompt;
    prompt.setFont(font);
    prompt.setCharacterSize(24);
    prompt.setFillColor(sf::Color(255, 0, 255));
    prompt.setPosition(50, 50);

    sf::Text inputDisplay;
    inputDisplay.setFont(font);
    inputDisplay.setCharacterSize(30);
    inputDisplay.setFillColor(sf::Color::Black);
    inputDisplay.setPosition(50, 150);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {
                    if (!inputText.empty())
                        inputText.pop_back();
                } else if (event.text.unicode == 13) {
                    if (!inputText.empty()) {
                        if (state == State::AskNumber) {
                            try {
                                int n = std::stoi(inputText);
                                if (n >= 2 && n <= 6) {
                                    numPlayers = n;
                                    playerNames.reserve(numPlayers);
                                    inputText.clear();
                                    currentPlayer = 1;
                                    state = State::AskNames;
                                } else {
                                    inputText.clear();
                                }
                            } catch (...) {
                                inputText.clear();
                            }
                        } else if (state == State::AskNames) {
                            playerNames.push_back(inputText);
                            inputText.clear();
                            currentPlayer++;
                            if (currentPlayer > numPlayers) {
                                state = State::Done;
                                window.close();
                            }
                        }
                    }
                } else if (event.text.unicode < 128) {
                    inputText += static_cast<char>(event.text.unicode);
                }
            }
        }

        if (state == State::AskNumber) {
            prompt.setString("Enter number of players (2-6):");
        } else if (state == State::AskNames) {
            prompt.setString("Enter name for player " + std::to_string(currentPlayer) + ":");
        }

        inputDisplay.setString(inputText);

        window.clear(sf::Color(230, 230, 255));
        window.draw(prompt);
        window.draw(inputDisplay);
        window.display();
    }
}

void showMainMenu(std::vector<std::string>& playerNames) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Coup");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Failed to load font\n";
        return;
    }

    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(250, 0, 250));
    startButton.setPosition(300, 275);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Start");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(360, 285);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        window.close();
                        runGameSetup(playerNames);
                    }
                }
            }
        }

        window.clear(sf::Color(230, 230, 255));
        window.draw(startButton);
        window.draw(buttonText);
        window.display();
    }
}

Player *creat_player(Game& game, string playerName,int numPlayers) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, numPlayers); 

    int randomRole = dist(gen);

    switch (randomRole) {
        case 1:
            return new Baron(game, playerName);
        case 2:
            
            return new General(game, playerName);
        case 3:
            
            return new Governor(game, playerName);
        case 4:
            
            return new merchant(game, playerName);
        case 5:
            return new Spy(game, playerName);
        case 6:
            return new Judge(game, playerName);
        default:
            throw std::runtime_error("Invalid role generated");
    }
}
bool askGeneralSave(sf::RenderWindow& window, const std::string& generalName) {
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return false;
    }

    sf::Text question;
    question.setFont(font);
    question.setString(generalName + ", do you want to save yourself?");
    question.setCharacterSize(24);
    question.setFillColor(sf::Color::Black);
    question.setPosition(50, 50);

    sf::RectangleShape yesButton(sf::Vector2f(100, 50));
    yesButton.setFillColor(sf::Color::Green);
    yesButton.setPosition(50, 150);

    sf::RectangleShape noButton(sf::Vector2f(100, 50));
    noButton.setFillColor(sf::Color::Red);
    noButton.setPosition(200, 150);

    sf::Text yesText;
    yesText.setFont(font);
    yesText.setString("Yes");
    yesText.setCharacterSize(20);
    yesText.setFillColor(sf::Color::White);
    yesText.setPosition(70, 160);

    sf::Text noText;
    noText.setFont(font);
    noText.setString("No");
    noText.setCharacterSize(20);
    noText.setFillColor(sf::Color::White);
    noText.setPosition(220, 160);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (yesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    return true; // המשתמש בחר "כן"
                }
                if (noButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    return false; // המשתמש בחר "לא"
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(question);
        window.draw(yesButton);
        window.draw(noButton);
        window.draw(yesText);
        window.draw(noText);
        window.display();
    }

    return false;
}
void showPlayersBoard(std::vector<Player*>& players, Game* game) {
    int cardWidth = 480; // שמירה על גודל הכרטיסים
    int cardHeight = 180;
    int spacing = 40;
    int buttonWidth = 50; // הקטנת רוחב הכפתורים
    int buttonHeight = 20; // הקטנת גובה הכפתורים

    int cardsPerRow = 3;
    int numRows = (players.size() + cardsPerRow - 1) / cardsPerRow;
    int windowWidth = spacing + cardsPerRow * (cardWidth + spacing);
    int windowHeight = spacing + numRows * (cardHeight + spacing);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Players Board");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Failed to load font\n";
        return;
    }
    // bool showSaveQuestion = false;
    // Player* targetPlayer = nullptr;

    std::vector<std::string> actions = {"gather", "tax", "bribe", "arrest", "sanction", "coup"};
    std::vector<std::string> spyActions = {"gather", "tax", "bribe", "arrest", "sanction", "coup", "block arrest", "show coins"};
    std::vector<std::string> baronActions = {"gather", "tax", "bribe", "arrest", "sanction", "coup", "invest"}; 
    bool selectTarget = false;
    int coupPlayerIndex = -1;
    int actionType = -1; // 5=coup, 3=arrest, 4=sanction, 6=block arrest
    std::string errorMsg = "";
    bool gameOver = false;
    std::string winnerMsg = "";

     bool selectGovernorUndo = false;
     int governorIndex = -1;

    while (window.isOpen()) {
        if (!gameOver) {
            try {
                winnerMsg = game->winner();
                gameOver = true;
            } catch (const std::exception&) {}
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (gameOver) continue;
            //    if (showSaveQuestion && targetPlayer != nullptr) {
            //     // Define the question and buttons here
            //     sf::Text question;
            //     question.setFont(font);
            //     question.setString(targetPlayer->getName() + ", do you want to save yourself?");
            //     question.setCharacterSize(24);
            //     question.setFillColor(sf::Color::Black);
            //     question.setPosition(50, 50);

            //     sf::RectangleShape yesButton(sf::Vector2f(100, 50));
            //     yesButton.setFillColor(sf::Color::Green);
            //     yesButton.setPosition(50, 150);

            //     sf::RectangleShape noButton(sf::Vector2f(100, 50));
            //     noButton.setFillColor(sf::Color::Red);
            //     noButton.setPosition(200, 150);

            //     sf::Text yesText;
            //     yesText.setFont(font);
            //     yesText.setString("Yes");
            //     yesText.setCharacterSize(20);
            //     yesText.setFillColor(sf::Color::White);
            //     yesText.setPosition(70, 160);

            //     sf::Text noText;
            //     noText.setFont(font);
            //     noText.setString("No");
            //     noText.setCharacterSize(20);
            //     noText.setFillColor(sf::Color::White);
            //     noText.setPosition(220, 160);

            //     while (showSaveQuestion) {
            //         sf::Event questionEvent;
                  
            //         while (window.pollEvent(questionEvent)) {
            //             if (questionEvent.type == sf::Event::Closed) {
            //                 window.close();
            //                 return;
            //             }

            //             if (questionEvent.type == sf::Event::MouseButtonPressed) {
            //                 sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //                 if (yesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            //                    //targetPlayer->set_active(true,true);
            //                     showSaveQuestion = false; // Exit the loop after handling the response
            //                     cout << targetPlayer->getName() << " saved themselves." << std::endl;
            //                     break;
            //                 }
            //                 if (noButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                                
            //                    // targetPlayer->set_active(false,true);

            //                     showSaveQuestion = false; // Exit the loop after handling the response
            //                     cout << targetPlayer->getName() << " choose not to save themselves." << std::endl;
            //                     break;
            //                 }
            //             }
            //         }
            //         // Draw the question and buttons
            //         window.clear(sf::Color::White);
            //         window.draw(question);
            //         window.draw(yesButton);
            //         window.draw(noButton);
            //         window.draw(yesText);
            //         window.draw(noText);
            //         window.display();
            //     }
            //     continue; // Skip the rest of the main loop
            // }

        //             if (showSaveQuestion && targetPlayer != nullptr) {
        //     // Define the question and buttons here
        //     sf::Text question;
        //     question.setFont(font);
        //     question.setString(targetPlayer->getName() + ", do you want to save yourself?");
        //     question.setCharacterSize(24);
        //     question.setFillColor(sf::Color::Black);
        //     question.setPosition(50, 50);

        //     sf::RectangleShape yesButton(sf::Vector2f(100, 50));
        //     yesButton.setFillColor(sf::Color::Green);
        //     yesButton.setPosition(50, 150);

        //     sf::RectangleShape noButton(sf::Vector2f(100, 50));
        //     noButton.setFillColor(sf::Color::Red);
        //     noButton.setPosition(200, 150);

        //     sf::Text yesText;
        //     yesText.setFont(font);
        //     yesText.setString("Yes");
        //     yesText.setCharacterSize(20);
        //     yesText.setFillColor(sf::Color::White);
        //     yesText.setPosition(70, 160);

        //     sf::Text noText;
        //     noText.setFont(font);
        //     noText.setString("No");
        //     noText.setCharacterSize(20);
        //     noText.setFillColor(sf::Color::White);
        //     noText.setPosition(220, 160);

        //     while (showSaveQuestion) {
        //         sf::Event questionEvent;

        //         // Use the correct event variable here
        //         while (window.pollEvent(questionEvent)) {
        //             if (questionEvent.type == sf::Event::Closed) {
        //                 window.close();
        //                 return;
        //             }

        //             if (questionEvent.type == sf::Event::MouseButtonPressed) {
        //                 sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //                 if (yesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        //                     //targetPlayer->set_active(true, true);
        //                     showSaveQuestion = false; // Exit the loop after handling the response
        //                     std::cout << targetPlayer->getName() << " saved themselves." << std::endl;
        //                     break;
        //                 }
        //                 if (noButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        //                     //targetPlayer->set_active(false, true);
        //                     showSaveQuestion = false; // Exit the loop after handling the response
        //                     std::cout << targetPlayer->getName() << " chose not to save themselves." << std::endl;
        //                     break;
        //                 }
        //             }
        //         }

        //         // Draw the question and buttons
        //         window.clear(sf::Color::White);
        //         window.draw(question);
        //         window.draw(yesButton);
        //         window.draw(noButton);
        //         window.draw(yesText);
        //         window.draw(noText);
        //         window.display();
        //     }
        //     continue; // Skip the rest of the main loop
        // }
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (!selectTarget && !selectGovernorUndo) {
                    for (size_t i = 0; i < players.size(); ++i) {
                        int row = i / cardsPerRow;
                        int col = i % cardsPerRow;
                        int x = spacing + col * (cardWidth + spacing);
                        int y = spacing + row * (cardHeight + spacing);

                        // Governor: עבור למצב בחירת יעד ל-undo
                        if (players[i]->role() == "Governor") {
                            sf::FloatRect undoRect(
                                x + 20 + actions.size() * (buttonWidth + 7),
                                y + cardHeight - buttonHeight - 8,
                                buttonWidth, buttonHeight
                            );
                            if (undoRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                                selectGovernorUndo = true;
                                governorIndex = i;
                                break;
                            }
                        }

                                                    // General undo (coup)
                            if (players[i]->role() == "General") {
                                sf::FloatRect undoRect(
                                    x + 20 + actions.size() * (buttonWidth + 7),
                                    y + cardHeight - buttonHeight - 8,
                                    buttonWidth, buttonHeight
                                );
                                if (undoRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                                    bool found = false;
                                    for (size_t j = 0; j < players.size(); ++j) {
                                        if (players[j]->is_active() && players[j]->LastMove_of_each_player() == "coup") {
                                            try {
                                                General* general = dynamic_cast<General*>(players[i]);
                                                if (general) {
                                                    general->undo_coup(*players[j]);
                                                    errorMsg = "";
                                                    found = true;
                                                    break;
                                                } else {
                                                    errorMsg = "Only General can undo coup!";
                                                }
                                            } catch (const std::exception& ex) {
                                                errorMsg = ex.what();
                                            }
                                        }
                                    }
                                    if (!found) {
                                        errorMsg = "No player to undo coup for!";
                                    }
                                }
                            }

                            // Judge undo (bribe)
                            if (players[i]->role() == "Judge") {
                                sf::FloatRect undoRect(
                                    x + 20 + actions.size() * (buttonWidth + 7),
                                    y + cardHeight - buttonHeight - 8,
                                    buttonWidth, buttonHeight
                                );
                                if (undoRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                                    bool found = false;
                                    for (size_t j = 0; j < players.size(); ++j) {
                                        if (players[j]->LastMove_of_each_player() == "bribe") {
                                            try {
                                                Judge* judge = dynamic_cast<Judge*>(players[i]);
                                                if (judge) {
                                                    judge->undo_bribe(*players[j]);
                                                    errorMsg = "";
                                                    found = true;
                                                    break;
                                                } else {
                                                    errorMsg = "Only Judge can undo bribe!";
                                                }
                                            } catch (const std::exception& ex) {
                                                errorMsg = ex.what();
                                            }
                                        }
                                    }
                                    if (!found) {
                                        errorMsg = "No player to undo bribe for!";
                                    }
                                }
                            }
                        // כפתורי פעולה רגילים + block arrest ל-Spy
                        // ...existing code...
                        const std::vector<std::string>& actionsToCheck =
                            (players[i]->role() == "Spy") ? spyActions :
                            (players[i]->role() == "Baron") ? baronActions :
                            actions;
                        
                        for (size_t j = 0; j < actionsToCheck.size(); ++j) {
                            sf::FloatRect btnRect(
                                x + 20 + j * (buttonWidth + 7),
                                y + cardHeight - buttonHeight - 8,
                                buttonWidth, buttonHeight
                            );
                            if (btnRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                                if (actionsToCheck[j] == "invest" && players[i]->role() == "Baron") {
                                    try {
                                        Baron* baron = dynamic_cast<Baron*>(players[i]);
                                        if (baron) {
                                            baron->invest();
                                            errorMsg = "";
                                        } else {
                                            errorMsg = "Only Baron can invest!";
                                        }
                                    } catch (const std::exception& ex) {
                                        errorMsg = ex.what();
                                    }
                                    break;
                                }
                                if (actionsToCheck[j] == "show coins" && players[i]->role() == "Spy") {
                                    std::string coinsInfo = "Players' coins:\n";
                                    for (Player* p : players) {
                                        coinsInfo += p->getName() + ": " + std::to_string(p->coins()) + "\n";
                                    }
                                    errorMsg = coinsInfo;
                                    break;
                                }
                                if (actionsToCheck[j] == "bribe") {
                                if (game && players[i]->getName() == game->turn()) { // בדוק אם זה תורו של השחקן
                                    try {
                                        players[i]->bribe(); // קריאה לפונקציה bribe
                                        errorMsg = "";
                                    } catch (const std::exception& ex) {
                                        errorMsg = ex.what();
                                    }
                                } else {
                                    errorMsg = "It's not your turn!";
                                }
                                break;
                            }
                                // כפתור block arrest ל-Spy
                                if (actionsToCheck[j] == "block arrest") {
                                    selectTarget = true;
                                    coupPlayerIndex = i;
                                    actionType = 6;
                                    break;
                                }
                                // בדוק אם זה תורו של השחקן לפי game->turn()
                                if (game && players[i]->getName() == game->turn()) {
                                    try {
                                        if (actionsToCheck[j] == "gather") {
                                            players[i]->gather();
                                            errorMsg = "";
                                        } else if (actionsToCheck[j] == "tax") {
                                            players[i]->tax();
                                            errorMsg = "";
                                        } else if (actionsToCheck[j] == "coup" || actionsToCheck[j] == "arrest" || actionsToCheck[j] == "sanction") {
                                            selectTarget = true;
                                            coupPlayerIndex = i;
                                            if (actionsToCheck[j] == "arrest") actionType = 3;
                                            else if (actionsToCheck[j] == "sanction") actionType = 4;
                                            else if (actionsToCheck[j] == "coup") actionType = 5;
                                        }
                                    } catch (const std::exception& ex) {
                                        errorMsg = ex.what();
                                    }
                                } else {
                                    errorMsg = "It's not your turn!";
                                }
                                break;
                            }
                        }
                        if (selectTarget || selectGovernorUndo) break;
                    }
                } else if (selectGovernorUndo) {
                    for (size_t i = 0; i < players.size(); ++i) {
                        if (i == governorIndex) continue;
                        int row = i / cardsPerRow;
                        int col = i % cardsPerRow;
                        int x = spacing + col * (cardWidth + spacing);
                        int y = spacing + row * (cardHeight + spacing);
                        sf::FloatRect cardRect(x, y, cardWidth, cardHeight);
                        if (cardRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                            try {
                                Governor* gov = dynamic_cast<Governor*>(players[governorIndex]);
                                if (gov) {
                                    gov->undo(*players[i]);
                                    errorMsg = "";
                                }
                            } catch (const std::exception& ex) {
                                errorMsg = ex.what();
                            }
                            selectGovernorUndo = false;
                            governorIndex = -1;
                            break;
                        }
                    }
                 }
                 //else if (actionType == 5 && selectTarget) { // אם מדובר ב-coup
                //     for (size_t i = 0; i < players.size(); ++i) {
                //         int row = i / cardsPerRow;
                //         int col = i % cardsPerRow;
                //         int x = spacing + col * (cardWidth + spacing);
                //         int y = spacing + row * (cardHeight + spacing);
                //         sf::FloatRect cardRect(x, y, cardWidth, cardHeight);
                //         if (cardRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                //             targetPlayer = players[i];
                //             if (targetPlayer->role() == "General") {
                //                 showSaveQuestion = true; // הצג את השאלה/////////////////////////////////////////
                //                 selectTarget = false; // סיים את בחירת היעד
                //                 break;
                //             }
                //         }
                //     }
                // }
                else if (selectTarget && actionType == 6) {
                    for (size_t i = 0; i < players.size(); ++i) {
                        if (static_cast<int>(i) == coupPlayerIndex) continue;
                        int row = i / cardsPerRow;
                        int col = i % cardsPerRow;
                        int x = spacing + col * (cardWidth + spacing);
                        int y = spacing + row * (cardHeight + spacing);
                        sf::FloatRect cardRect(x, y, cardWidth, cardHeight);
                        if (cardRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                            try {
                                Spy* spy = dynamic_cast<Spy*>(players[coupPlayerIndex]);
                                if (spy) {
                                    spy->block(*players[i]);
                                    errorMsg = "";
                                } else {
                                    errorMsg = "Only Spy can block arrest!";
                                }
                            } catch (const std::exception& ex) {
                                errorMsg = ex.what();
                            }
                            selectTarget = false;
                            coupPlayerIndex = -1;
                            actionType = -1;
                            break;
                        }
                    }
                } else {
                    for (size_t i = 0; i < players.size(); ++i) {
                        if (static_cast<int>(i) == coupPlayerIndex) continue;
                        int row = i / cardsPerRow;
                        int col = i % cardsPerRow;
                        int x = spacing + col * (cardWidth + spacing);
                        int y = spacing + row * (cardHeight + spacing);
                        sf::FloatRect cardRect(x, y, cardWidth, cardHeight);
                        if (cardRect.contains(static_cast<sf::Vector2f>(mousePos))) {
                            try {
                                if (actionType == 3) {
                                    players[coupPlayerIndex]->arrest(*players[i]);
                                } else if (actionType == 4) {
                                    players[coupPlayerIndex]->sanction(*players[i]);
                                } else if (actionType == 5) {
                                    players[coupPlayerIndex]->coup(*players[i],true);
                                }
                                errorMsg = "";
                            } catch (const std::exception& ex) {
                                errorMsg = ex.what();
                            }
                            selectTarget = false;
                            coupPlayerIndex = -1;
                            actionType = -1;
                            break;
                        }
                    }
                }
                
            }
        }

        window.clear(sf::Color(200, 230, 255));

        int currentTurn = -1;
        if (game) {
            std::string turnName = game->turn();
            for (size_t i = 0; i < players.size(); ++i) {
                if (players[i]->getName() == turnName) {
                    currentTurn = i;
                    break;
                }
            }

            // בדוק אם השחקן הנוכחי חסום
            if (currentTurn != -1) {
                Player* currentPlayer = players[currentTurn];
                if (currentPlayer->is_active() && currentPlayer->is_sanctioned() && currentPlayer->get_Blocked() && currentPlayer->coins() == 0) {
                    errorMsg = currentPlayer->getName() + " is stuck! Turn is over automatically.";
                    game->next_turn(); // העבר את התור לשחקן הבא
                }
            }
        }

        for (size_t i = 0; i < players.size(); ++i) {
            int row = i / cardsPerRow;
            int col = i % cardsPerRow;
            int x = spacing + col * (cardWidth + spacing);
            int y = spacing + row * (cardHeight + spacing);

            sf::RectangleShape card(sf::Vector2f(cardWidth, cardHeight));
            card.setPosition(x, y);
            card.setFillColor(players[i]->is_active() ? sf::Color(220, 240, 255) : sf::Color(255, 200, 220));
            card.setOutlineColor(sf::Color(180, 210, 255));
            card.setOutlineThickness(3);
            window.draw(card);

            // כפתור undo רק ל-Governor, Judge, General
            if (players[i]->role() == "Governor" || players[i]->role() == "Judge" || players[i]->role() == "General") {
                sf::RectangleShape undoButton(sf::Vector2f(buttonWidth, buttonHeight));
                undoButton.setPosition(x + 20 + actions.size() * (buttonWidth + 7), y + cardHeight - buttonHeight - 8);
                undoButton.setFillColor(sf::Color(255, 220, 180));
                undoButton.setOutlineColor(sf::Color(200, 150, 100));
                undoButton.setOutlineThickness(1);
                window.draw(undoButton);

                sf::Text undoText;
                undoText.setFont(font);
                if (players[i]->role() == "General") {
                    undoText.setString("block coup");
                } else if (players[i]->role() == "Judge") {
                    undoText.setString("undo bribe"); // שם חדש לשופט
                } else {
                    undoText.setString("undo");
                }
                undoText.setCharacterSize(12);
                undoText.setFillColor(sf::Color::Black);
                undoText.setPosition(x + 25 + actions.size() * (buttonWidth + 7), y + cardHeight - buttonHeight - 3);
                window.draw(undoText);
            }
            if (players[i]->is_active() && i == currentTurn) {
            sf::CircleShape turnCircle(12);
            turnCircle.setFillColor(sf::Color(0, 220, 0));
            turnCircle.setOutlineColor(sf::Color::Black);
            turnCircle.setOutlineThickness(2);
            turnCircle.setPosition(x + cardWidth - 30, y + 10);
            window.draw(turnCircle);

            sf::Text turnText;
            turnText.setFont(font);
            turnText.setString("✓");
            turnText.setCharacterSize(18);
            turnText.setFillColor(sf::Color::Black);
            turnText.setPosition(x + cardWidth - 26, y + 10);
            window.draw(turnText);
        }

            sf::Text nameText;
            nameText.setFont(font);
            nameText.setString(players[i]->getName());
            nameText.setCharacterSize(22);
            nameText.setFillColor(sf::Color::Black);
            nameText.setPosition(x + 20, y + 10);
            window.draw(nameText);

            sf::Text coinsText;
            coinsText.setFont(font);
            coinsText.setString("Coins: " + std::to_string(players[i]->coins()));
            coinsText.setCharacterSize(16);
            coinsText.setFillColor(sf::Color(0, 120, 180));
            coinsText.setPosition(x + 20, y + 40);
            window.draw(coinsText);

            sf::Text statusText;
            statusText.setFont(font);
            statusText.setString("Status: " + std::string(players[i]->is_active() ? "Alive" : "Dead"));
            statusText.setCharacterSize(16);
            statusText.setFillColor(players[i]->is_active() ? sf::Color(0, 180, 180) : sf::Color(255, 105, 180));
            statusText.setPosition(x + 150, y + 40);
            window.draw(statusText);

            sf::Text roleText;
            roleText.setFont(font);
            roleText.setString("Role: " + players[i]->role());
            roleText.setCharacterSize(16);
            roleText.setFillColor(sf::Color(255, 105, 180));
            roleText.setPosition(x + 20, y + 70);
            window.draw(roleText);

            int circleRadius = 5;
            int circleY = y + 100;
            int circleX = x + 20;

            sf::CircleShape sanctionCircle(circleRadius);
            sanctionCircle.setPosition(circleX, circleY);
            sanctionCircle.setFillColor(players[i]->is_sanctioned() ? sf::Color::Black : sf::Color::Transparent);
            sanctionCircle.setOutlineColor(sf::Color::Black);
            sanctionCircle.setOutlineThickness(2);
            window.draw(sanctionCircle);

            sf::Text sanctionText;
            sanctionText.setFont(font);
            sanctionText.setString("Sanctioned");
            sanctionText.setCharacterSize(12);
            sanctionText.setFillColor(sf::Color::Black);
            sanctionText.setPosition(circleX + 2 * circleRadius + 5, circleY - 2);
            window.draw(sanctionText);

            int blocketCircleX = x + 140;
            int blocketCircleY = y + 100;
            sf::CircleShape blocketCircle(5);
            blocketCircle.setPosition(blocketCircleX, blocketCircleY);
            blocketCircle.setFillColor(players[i]->get_Blocked() ? sf::Color(0, 0, 0) : sf::Color::Transparent);
            blocketCircle.setOutlineColor(sf::Color::Black);
            blocketCircle.setOutlineThickness(2);
            window.draw(blocketCircle);

            sf::Text blocketText;
            blocketText.setFont(font);
            blocketText.setString("blocket");
            blocketText.setCharacterSize(12);
            blocketText.setFillColor(sf::Color::Black);
            blocketText.setPosition(blocketCircleX + 15, blocketCircleY - 2);
            window.draw(blocketText);

            // ...existing code...
            const std::vector<std::string>& actionsToDraw =
                (players[i]->role() == "Spy") ? spyActions :
                (players[i]->role() == "Baron") ? baronActions :
                actions;
            // ...existing code...
            for (size_t j = 0; j < actionsToDraw.size(); ++j) {
                sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
                button.setPosition(x + 20 + j * (buttonWidth + 7), y + cardHeight - buttonHeight - 8);
                button.setFillColor(sf::Color(180, 220, 255));
                button.setOutlineColor(sf::Color(150, 200, 255));
                button.setOutlineThickness(1);
                window.draw(button);

                sf::Text btnText;
                btnText.setFont(font);
                btnText.setString(actionsToDraw[j]);
                btnText.setCharacterSize(12);
                btnText.setFillColor(sf::Color::Black);
                btnText.setPosition(x + 25 + j * (buttonWidth + 7), y + cardHeight - buttonHeight - 3);
                window.draw(btnText);
            }
        }

        if (!errorMsg.empty()) {
            sf::RectangleShape errorBox(sf::Vector2f(windowWidth - 40, 60));
            errorBox.setPosition(20, 20);
            errorBox.setFillColor(sf::Color(255, 200, 200, 230));
            errorBox.setOutlineColor(sf::Color::Red);
            errorBox.setOutlineThickness(2);
            window.draw(errorBox);

            sf::Text errorText;
            errorText.setFont(font);
            errorText.setString(errorMsg);
            errorText.setCharacterSize(22);
            errorText.setFillColor(sf::Color::Red);
            errorText.setPosition(35, 35);
            window.draw(errorText);
        }

        if (gameOver) {
            sf::RectangleShape winBox(sf::Vector2f(windowWidth - 40, 80));
            winBox.setPosition(20, 100);
            winBox.setFillColor(sf::Color(200, 255, 200, 230));
            winBox.setOutlineColor(sf::Color::Green);
            winBox.setOutlineThickness(3);
            window.draw(winBox);

            sf::Text winText;
            winText.setFont(font);
            winText.setString("Winner: " + winnerMsg + "\nClose the window to exit.");
            winText.setCharacterSize(32);
            winText.setFillColor(sf::Color::Green);
            winText.setPosition(40, 120);
            window.draw(winText);
        }

        if (selectTarget && coupPlayerIndex != -1) {
            sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
            overlay.setFillColor(sf::Color(255, 255, 255, 180));
            window.draw(overlay);

            sf::Text msg;
            msg.setFont(font);
            if (actionType == 3)
                msg.setString("Select a player to arrest");
            else if (actionType == 4)
                msg.setString("Select a player to sanction");
            else if (actionType == 6)
                msg.setString("Select a player to block arrest");
            else
                msg.setString("Select a player to coup");
            msg.setCharacterSize(32);
            msg.setFillColor(sf::Color::Black);
            msg.setPosition(80, 40);
            window.draw(msg);
        }

        if (selectGovernorUndo && governorIndex != -1) {
            sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
            overlay.setFillColor(sf::Color(255, 255, 255, 180));
            window.draw(overlay);

            sf::Text msg;
            msg.setFont(font);
            msg.setString("Select a player to undo tax for");
            msg.setCharacterSize(32);
            msg.setFillColor(sf::Color::Black);
            msg.setPosition(80, 40);
            window.draw(msg);
        }

        window.display();
    }
}
int main() {
    std::vector<std::string> playerNames;
    showMainMenu(playerNames);

    Game game{};
     std::vector<Player*> players;
    for (int i = 0; i < playerNames.size(); i++) {
        players.push_back(creat_player(game, playerNames[i], playerNames.size()));
    }
    showPlayersBoard(players, &game);
    //cout<<game;
    for(int i=0; i<players.size(); i++){
        delete players[i];
    }
    players.clear();
    return 0;
}