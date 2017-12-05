#include "picframe.h"
#include <QDebug>
#include <QString>

using namespace std;

PicFrame::PicFrame()
{

}

PicFrame::~PicFrame()
{

}
std::string PicFrame::getCurrent_time() const
{
    return current_time;
}

void PicFrame::setCurrent_time(const std::string &value)
{
    current_time = value;
}


void PicFrame::GetTime()
{
    SYSTEMTIME st;
    GetSystemTime(&st);

    current_time = to_string(st.wYear) + "-" + to_string(st.wMonth) + "-" + to_string(st.wDay) + ", " +
    to_string(st.wHour + 1) + "h" + to_string(st.wMinute) + "m" + to_string(st.wSecond) + "s" + to_string(st.wMilliseconds) + "ms";
}

