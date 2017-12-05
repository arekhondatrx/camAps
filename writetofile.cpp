#include "writetofile.h"
#include <fstream>
#include <QDebug>

WriteToFile::WriteToFile()
{

}

WriteToFile::WriteToFile(string loc)
{
    setLoc(loc);
}

WriteToFile::~WriteToFile()
{

}

void WriteToFile::append(string element)
{
    if(!checkExistingElement(element))
    {
        fstream file;
        file.open(loc, ios::in | ios::app);
        file << element << endl;
        file.close();
    }
}

void WriteToFile::write(string element)
{
    fstream file;
    file.open(loc, ios::in);
    file << element << endl;
    file.close();
}

void WriteToFile::clear()
{
    fstream file;
    file.open(loc, ios::out | ios::trunc );
    file.close();
}

void WriteToFile::setLoc(string loc)
{
    this->loc = loc;
}

bool WriteToFile::checkExistingElement(string element)
{
    fstream file;
    file.open(loc, ios::in);
    string temp;

    if(file.good())
    {
        while(getline(file, temp))
        {
            if(temp == element)
                return true;
        }
    }
    file.close();
    return false;
}
