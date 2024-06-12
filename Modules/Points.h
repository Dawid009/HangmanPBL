#ifndef HANGMAN_POINTS_H
#define HANGMAN_POINTS_H

#include <type_traits>


class Points {

private:
    float PointsAmount;
    size_t wordLength;
    float correctStreak;
    float missStreak;
public:
    Points(size_t length);
    void addPoints(const uint8_t letterId,int amount);
    int getPoints() {return PointsAmount;};


};


#endif //HANGMAN_POINTS_H
