//
// Created by Dawid Knura on 19/06/2024.
//

#ifndef HANGMAN_SAVEGAME_H
#define HANGMAN_SAVEGAME_H
#include <string>
#include "SFML/Graphics.hpp"

class SaveGameBase {

protected:
    std::string save_name;
    int total_points;
    std::string date;

public:

    std::string path;
    /**
    * @brief Class constructor
    */
    SaveGameBase();
    /**
    * @brief Saving settings to file
    * @param path Path to graphics.ini file
    */

    /**
    * @brief Reading settings from file
    * @param path Path to graphics.ini file
    */
    void loadSimpleFromFile(const std::string& path);
    const std::string& getSaveName() { return this->save_name;}
    const std::string& getDate() { return this->date;}
    int getPoints() {return this->total_points;}

};



class SaveGame : public SaveGameBase{
    //current game
public:
    SaveGame();
    void saveToFile(const std::string& path) const;

    int current_password_id;
    int misses;
    std::vector<int> picked_letters;
    std::vector<int> win_games_id;
    int win_games;
    int loss_games;
    int playtime;
    void loadAllFromFile(const std::string& path);
};


#endif //HANGMAN_SAVEGAME_H
