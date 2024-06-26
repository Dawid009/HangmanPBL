#include "Points.h"
#include <algorithm>

Points::Points(size_t length) : correctStreak(0), PointsAmount(0){
    this->wordLength = length;
}


void Points::addPoints(const uint8_t letterId, int amount){
    constexpr float single_scale{10.f};
    constexpr float multi_scale{15.f};
    constexpr float polish_scale{20.f};
    constexpr int single[] = {0, 6, 11, 19, 27, 30};
    constexpr int multi[] = {1, 4, 7, 15, 18, 20, 25, 32, 33};

    if(amount>0){
        correctStreak++;
        float points;
        if (std::find(std::begin(single), std::end(single), letterId) != std::end(single))
        {
            points = static_cast<float>(amount)*single_scale;
        }
        else if(std::find(std::begin(multi), std::end(multi), letterId) != std::end(multi))
        {
            points = static_cast<float>(amount) * polish_scale;
        }
        else
        {
            points = static_cast<float>(amount) * multi_scale;
        }
        PointsAmount+=points*(correctStreak/(static_cast<float>(wordLength)/3));
        missStreak=0;
    }else{
        if(PointsAmount>7){
            missStreak++;
            float points;
            if (std::find(std::begin(single), std::end(single), letterId) != std::end(single))
            {
                points = 100/single_scale;
            }
            else if(std::find(std::begin(multi), std::end(multi), letterId) != std::end(multi))
            {
                points = 100/polish_scale;
            }
            else
            {
                points = 100/multi_scale;
            }

            PointsAmount-=points*((missStreak/2.f) /(static_cast<float>(wordLength)/4));
            if(PointsAmount<0) PointsAmount=0;
        }
        correctStreak=0;
    }
}
