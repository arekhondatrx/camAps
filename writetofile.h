#ifndef WRITETOFILE_H
#define WRITETOFILE_H


#include <iostream>

using namespace std;

class WriteToFile
{
public:
    WriteToFile();
    WriteToFile(string loc);
    ~WriteToFile();

public:
    void append(string element); // dopisuje tekst do pliku
    void write(string element); // wpisuje tekst do pliku
    void clear(); // czysci plik
    void setLoc(string loc); // pobiera lokalizacje pliku

private:
    bool checkExistingElement(string element);

private:
    string loc;
};

#endif // WRITETOFILE_H
