/**
 * @file SaveGame.h
 * @brief SaveGame and SaveGameBase classes
 */

#ifndef HANGMAN_SAVEGAME_H
#define HANGMAN_SAVEGAME_H
#include <string>
#include "SFML/Graphics.hpp"

/**
 * @struct Date
 * @brief Struct representing date
 */
struct Date{
    int day;
    int month;
    int year;
    int hour;
    int minute;

    Date(){
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        this->day = now->tm_mday;
        this->month = now->tm_mon+1;
        this->year = now->tm_year+1900;
        this->hour=now->tm_hour;
        this->minute=now->tm_min;
    }

     std::wstring getDate() const {
        std::wstring date_temp;
        date_temp+=(this->day<10?L"0":L"")+std::to_wstring(this->day)+L".";
        date_temp+=(this->month<10?L"0":L"")+std::to_wstring(this->month)+L".";
        date_temp+=std::to_wstring(year)+L"  ";
        date_temp+=(this->hour<10?L"0":L"")+std::to_wstring(this->hour)+L":";
        date_temp+=(this->minute<10?L"0":L"")+std::to_wstring(this->minute);
        return date_temp;
    }
};



/**
 * @class SaveGameBase
 * @brief Base class for savegame
 */
class SaveGameBase {

protected:
    std::string save_name;///<Savegame name
    int total_points;///<Total savegame points


public:
    Date date;///<Date object
    std::string path;///<Path to the file
    /**
    * @brief Class constructor
    */
    SaveGameBase();

    /**
    * @brief Reading savegame simple info from file
    * @param path path to the location of savegame
    */
    void loadSimpleFromFile(const std::string& path);

    /**
    * @brief Getter for savegame name
    * @return Returns name
    */
    const std::string& getSaveName() { return this->save_name;}
    /**
    * @brief Getter for savegame Date
    * @return Returns  date
    */
    std::wstring getDate() const { return this->date.getDate();}

    /**
    * @brief Getter for savegame Points
    * @return Returns points
    */
    int getPoints() {return this->total_points;}

    /**
    * @brief Function adding points to the savegame
    * @param points Points amount
    */
    void addPoints(int points) {this->total_points+=points;}

};


/**
 * @class SaveGame
 * @brief Extended savegame object info
 */
class SaveGame : public SaveGameBase{
public:
    int current_password_id;///<Id of the pass
    int misses;///<Misses count in session
    std::vector<int> picked_letters;///<Picked letters in session
    std::vector<int> win_games_id;///<Win games id's
    int win_games; ///<Win games count
    int loss_games;///<Loss games count
    int playtime;///<Total playtime
    int total_good_hits;///<Good hits
    int total_miss_hits;///<Bad hits

    /**
    * @brief Class constructor
    */
    SaveGame();
    /**
    * @brief Class constructor
    * @param path path to the location of savegame
    */
    SaveGame(const std::string& path);

    /**
    * @brief Function saving savegame to file
    * @param path path to the location of savegame
    */
    void saveToFile(const std::string& path) const;

    /**
    * @brief Function loading all info from file
    * @param path path to the location of savegame
    */
    void loadAllFromFile(const std::string& path);
};


#endif
