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

void Logger::save()
{
    std::ofstream scoreFile(_filename);
    for (auto&& t : _datas)
        scoreFile << t.first << ':' << t.second << std::endl;
    scoreFile.flush();
    scoreFile.close();
}

void Logger::readData()
{
    std::ifstream scoreFile(_filename);
    std::string line;

    for (int i = 0; i < 16; ++i)
    {
        std::getline(scoreFile, line, ':');
        int score;
        scoreFile >> score;
        _datas[line] = score;
    }
}