#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Headers/Dungeon.h"
#include "../Headers/Entity.h"
#include "../Headers/GraphicManager.h"
#include "../Headers/Item.h"

using JSON = nlohmann::json;

// initialize game settings
int Player::health_initializer = std::numeric_limits<int>::min();
int Player::attack_initializer = std::numeric_limits<int>::min();
int Player::defense_initializer = std::numeric_limits<int>::min();
const int &Player::INIT_HEALTH = Player::health_initializer;
const int &Player::INIT_ATTACK = Player::attack_initializer;
const int &Player::INIT_DEFENSE = Player::defense_initializer;

// game menu function, return true if exit
bool runMenu(Dungeon *dungeon) {
    int option = 1;
    std::string name;
    while (option == 1) {
        option = displayMenu();
        switch (option) {
            // start
            case 0:
                name = inputPlayerName();
                break;
            case 1:
                chooseDifficulty();
                break;
            case 2:
                endGraphic();
                return true;
            default:
                break;
        }
    }
    dungeon->createPlayer(name);
    return false;
}

int main() {
    JSON Settings;
    std::ifstream jfile("../assets/Settings.json");
    jfile >> Settings;
    jfile.close();

    Player::health_init(Settings.at("PLAYER_INIT_HEALTH"));
    Player::attack_init(Settings.at("PLAYER_INIT_ATTACK"));
    Player::defense_init(Settings.at("PLAYER_INIT_DEFENSE"));

    initGraphic();
    Dungeon *dungeon = new Dungeon;
    dungeon->initGame();

    // display menu
    // runMenu() has called createPlayer()
    if (runMenu(dungeon) == true) return 0;
    Player *player = dungeon->getPlayer();

    // TODO: intepret story

    ExploringScene exploring;
    exploring.drawMiniMap(dungeon);
    exploring.drawRoom(player);
    /* game loop
    assume scene can be overlapped after clear()
    while(exploring) {
        if (fighting) {}
        else if (trading) {}
    }
    */
    std::array<bool, 3> gameStatus{true, false, false};  // explore, fight, trade
    int input;
    keypad(stdscr, true);
    while (gameStatus[0]) {
        switch ((input = getch())) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                player->playerMove(input, exploring.getRoom());
                break;
            case 27:
            default:
                break;
        }
        exploring.drawMiniMap(dungeon);
        exploring.drawRoom(player);
    }
    return 0;
}