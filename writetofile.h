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
    void append(string element);
    void write(string element);
    void clear();
    void setLoc(string loc);

private:
    bool checkExistingElement(string element);

private:
    string loc;
};

#endif // WRITETOFILE_H
