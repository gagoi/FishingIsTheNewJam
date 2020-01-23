#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>

class Logger
{
private:
    std::string _filename;
    std::map<std::string, int> _datas;
    void readData();
public:
    Logger();
    void save();
    int& operator[](std::string const &);
    friend void operator<<(Logger const &, std::string);
};

void operator<<(Logger const &, std::string);