#include "Logger.hpp"

Logger::Logger()
{
    _filename = std::string(getenv("HOME")) + "/.fishIsTheNewGame.txt";
    std::cout << "Fichier de save : " << _filename << std::endl;
    readData();
}

int& Logger::operator[](std::string const & key)
{
    return _datas[key];
}

int Logger::operator[](std::string const & key) const
{
    return _datas.count(key) > 0 ? _datas.find(key)->second : 0;
}

void Logger::save()
{
    std::ofstream scoreFile(_filename, std::ios::trunc);
    for (auto&& t : _datas)
        scoreFile << t.first << ':' << t.second << std::endl;
    scoreFile.flush();
    scoreFile.close();
}

void Logger::readData()
{
    std::ifstream scoreFile(_filename);
    std::string line;
    std::cout << "Read : " << scoreFile.eof() << std::endl;
    while (!scoreFile.eof())
    {
        std::getline(scoreFile, line, ':');
        int score;
        scoreFile >> score;
        if (line != "") 
        {
            _datas[line] = score;
            std::cout << line << " -> " << score << std::endl;
        }
        getline(scoreFile, line);
    }

    scoreFile.close();
}