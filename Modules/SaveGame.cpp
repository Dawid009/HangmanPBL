#include "SaveGame.h"

#include <fstream>
#include <iostream>
#include <ctime>

SaveGameBase::SaveGameBase()
{

}

void SaveGame::saveToFile(const std::string& path) const
{
    std::ofstream ofs(path,std::ios::out);

    if (ofs.is_open())
    {
        ofs << this->save_name<<std::endl;
        ofs << std::to_string(this->total_points)<<std::endl;
        ofs << std::to_string(this->date.day)<<std::endl;
        ofs << std::to_string(this->date.month)<<std::endl;
        ofs << std::to_string(this->date.year)<<std::endl;
        ofs << std::to_string(this->date.minute)<<std::endl;
        ofs << std::to_string(this->date.hour)<<std::endl;
        ofs << std::to_string(this->current_password_id)<<std::endl;
        ofs << std::to_string(this->misses)<<std::endl;
        ofs << std::to_string(this->win_games)<<std::endl;
        ofs << std::to_string(this->loss_games)<<std::endl;
        ofs << std::to_string(this->playtime)<<std::endl;
        ofs << std::to_string(this->total_miss_hits)<<std::endl;
        ofs << std::to_string(this->total_good_hits)<<std::endl;

        for(int i=0;i<this->win_games_id.size();i++){
            ofs <<win_games_id[i];
            if(i>=this->win_games_id.size()-1) continue;
            ofs << ",";
        }

        if(this->picked_letters.size()>0) ofs<<std::endl;

        for(int i=0;i<this->picked_letters.size();i++){

            ofs <<picked_letters[i];
            if(i>=this->picked_letters.size()-1) continue;
            ofs << ",";
        }

    }

    ofs.close();
}

void SaveGameBase::loadSimpleFromFile(const std::string& path)
{
    std::ifstream ifs(path);

    if (ifs.is_open())
    {
        std::getline(ifs, this->save_name);
        ifs >> this->total_points;
        ifs >> this->date.day;
        ifs >> this->date.month;
        ifs >> this->date.year;
        ifs >> this->date.minute;
        ifs >> this->date.hour;
    }
    ifs.close();
}

void SaveGame::loadAllFromFile(const std::string& path)
{
    std::ifstream ifs(path);

    if (ifs.is_open())
    {
        std::getline(ifs, this->save_name);//game1
        ifs >> this->total_points;//1260

        ifs >> this->date.day;
        ifs >> this->date.month;
        ifs >> this->date.year;
        ifs >> this->date.minute;
        ifs >> this->date.hour;
        ifs >> this->current_password_id; //4
        ifs >> this->misses;//3
        ifs >> this->win_games;//10
        ifs >> this->loss_games;//15
        ifs >> this->playtime;//160
        ifs >> this->total_miss_hits;
        ifs >> this->total_good_hits;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string::size_type start = 0, end;
        std::string line;
        std::getline(ifs,line);
        while ((end = line.find(',', start)) != std::string::npos) {
            win_games_id.push_back(std::stoi(line.substr(start, end - start)));
            start = end + 1;
        }
        win_games_id.push_back(std::stoi(line.substr(start)));

        if(!ifs.eof()){
            start = 0, end = 0;
            std::getline(ifs,line);
            while ((end = line.find(',', start)) != std::string::npos) {
                picked_letters.push_back(std::stoi(line.substr(start, end - start)));
                start = end + 1;
            }
            picked_letters.push_back(std::stoi(line.substr(start)));
        }
    }

    ifs.close();
}

SaveGame::SaveGame(): win_games(0), loss_games(0), current_password_id(0), misses(0), playtime(0),total_good_hits(0),total_miss_hits(0) {
    srand(time(NULL)); // Seed the time
    int finalNum = rand()%(201)+1;
    this->save_name = "Gra"+std::to_string(finalNum);
    this->path = path;
    this->total_points = 0;
    this->date = Date();
    this->win_games_id.push_back(0);

}

SaveGame::SaveGame(const std::string& path): win_games(0), loss_games(0), current_password_id(0), misses(0), playtime(0),total_good_hits(0),total_miss_hits(0) {
    srand(time(NULL)); // Seed the time
    int finalNum = rand() % (100) + 1;
    this->save_name = "Gra" + std::to_string(finalNum);
    this->path = path + this->save_name+".ini";
    this->total_points = 0;
    this->date = Date();
    this->win_games_id.push_back(0);
}
