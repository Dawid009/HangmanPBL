/**
 * @file Points.h
 * @brief Game points module
 */

#ifndef HANGMAN_POINTS_H
#define HANGMAN_POINTS_H
#include <type_traits>

/**
 * @class Points
 * @brief Class reponsible for game points
 */
class Points {

private:
    float PointsAmount; ///<Amount of the points
    size_t wordLength; ///<Password length
    float correctStreak; ///<Streak
    float missStreak;///<Streak
public:
    /**
    * @brief Class constructor
    * @param length Password length
    */
    Points(size_t length);

    /**
    * @brief Add points based on letter type and amount of letter hits
    * @param letterId Id of the letter
    * @param amount Amount of letter hits
     *
    */
    void addPoints(const uint8_t letterId,int amount);
    /**
    * @brief Returns points amount
    * @return Point amount
    */
    int getPoints() {return PointsAmount;};
};


#endif
