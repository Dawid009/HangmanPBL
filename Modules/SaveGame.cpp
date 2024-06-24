#include "SaveGame.h"

#include <fstream>
#include <iostream>
#include <ctime>

SaveGameBase::SaveGameBase()
{

}

void SaveGame::saveToFile(const std::string& path) const
{
    std::ofstream ofs(path);

    if (ofs.is_open())
    {
        ofs << this->save_name<<std::endl;
        ofs << this->total_points<<std::endl;
        ofs << this->current_password_id<<std::endl;
        ofs << this->misses<<std::endl;
        ofs << this->win_games<<std::endl;
        ofs << this->loss_games<<std::endl;
        ofs << this->playtime<<std::endl;

        for(int i=0;i<this->win_games_id.size();i++){
            ofs <<win_games_id[i];
            if(i<this->win_games_id.size()-1) continue;
            ofs << ",";
        }

        for(int i=0;i<this->picked_letters.size();i++){
            ofs <<picked_letters[i];
            if(i<this->picked_letters.size()-1) continue;
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
        std::string date_temp;
        int temp;
        ifs >> temp;
        date_temp+=(temp<10?"0":"")+std::to_string(temp)+".";
        ifs >> temp;
        date_temp+=(temp<10?"0":"")+std::to_string(temp)+".";
        ifs >> temp;
        date_temp+=std::to_string(temp)+"  ";
        ifs >> temp;
        date_temp+=(temp<10?"0":"")+std::to_string(temp)+":";
        ifs >> temp;
        date_temp+=(temp<10?"0":"")+std::to_string(temp);

        date = date_temp;
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

        std::string date_temp;
        int temp;
        ifs >> temp;
        date_temp+=std::to_string(temp)+".";
        ifs >> temp;
        date_temp+=std::to_string(temp)+".";
        ifs >> temp;
        date_temp+=std::to_string(temp)+"  ";
        ifs >> temp;
        date_temp+=std::to_string(temp)+":";
        ifs >> temp;
        date_temp+=std::to_string(temp);

        date = date_temp;
        ifs >> this->current_password_id; //4
        ifs >> this->misses;//3
        ifs >> this->win_games;//10
        ifs >> this->loss_games;//15
        ifs >> this->playtime;//160
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string::size_type start = 0, end;
        std::string line;
        std::getline(ifs,line);
        while ((end = line.find(',', start)) != std::string::npos) {
            win_games_id.push_back(std::stoi(line.substr(start, end - start)));
            start = end + 1;
        }
        win_games_id.push_back(std::stoi(line.substr(start)));


        start = 0, end = 0;
        std::getline(ifs,line);
        while ((end = line.find(',', start)) != std::string::npos) {
           picked_letters.push_back(std::stoi(line.substr(start, end - start)));
            start = end + 1;
        }
        picked_letters.push_back(std::stoi(line.substr(start)));
    }

    ifs.close();
}

SaveGame::SaveGame(): win_games(0), loss_games(0), current_password_id(0), misses(0), playtime(0) {
    srand(time(NULL)); // Seed the time
    int finalNum = rand()%(201)+1;
    this->save_name = "Newgame"+std::to_string(finalNum);
    this->total_points = 0;
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    this->date = std::to_string(now->tm_mday)+"."+std::to_string(now->tm_mon)+"."+std::to_string(now->tm_year);

}
