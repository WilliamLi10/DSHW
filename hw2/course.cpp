#include "course.h"
#include<string>
#include<iomanip>
#include<fstream>
#include<iostream>
bool RoomSort(const Course& C1, const Course&C2)
{
    if(C1.Room < C2.Room)
    {
        return true;
    }
    else if (C1.Room == C2.Room)
    {
        if (C1.Day < C2.Day)
        {
            return true;
        }
        else if (C1.Day == C2.Day)
        {
            if (C1.StartHour < C2.StartHour)
            {
                return true;
            }
            else if (C1.StartHour == C2.StartHour)
            {
                
                if(C1.Code < C2.Code)
                {
                    return true;
                }
                else if (C2.Code == C2.Code)
                {
                    if(C2.Dept < C2.Dept)
                    {
                        return true;
                    }
                }
            }
        }
    }

     return false;
    

}
bool DeptSort(const Course& C1, const Course&C2)
{
    if(C1.Code < C2.Code)
    {
        return true;
    }
    else if (C1.Code == C2.Code)
    {
        if(C1.Day < C2.Day)
        {
            return true;
        }
        else if (C1.Day == C2.Day)
        {
            if (C1.StartHour > C2.StartHour)
            {
                return true;
            }
        }

    }
    return false;
}
bool DaySort(const Course& C1, const Course&C2)
{
    if(C1.Day < C2.Day)
    {
        return true;
    }
    else if (C1.Day == C2.Day)
    {
        if(C1.Code < C2.Code)
        {
            return true;
        }
        else if (C1.Code == C2.Code)
        {
            if (C1.StartHour < C2.StartHour)
            {
                return true;
            }
        }

    }
    return false;
}
Course::Course()
    : ID(0), Dept(""), Code(""),Title(""), STime(""), ETime(""), Room(""), Day(0),StartHour(0)
{
}

Course::Course(int tID, std::string tDept, std::string tCode, std::string tTitle, char tDay, std::string tSTime, std::string tETime, std::string tRoom)
    : ID(tID), Dept(tDept), Code(tCode),Title(tTitle), STime(tSTime),ETime(tETime), Room(tRoom)
    {
                if(tDay == 'M')
                {
                    Day = 1;
                }
                else if (tDay == 'T')
                {
                    Day = 2;
                }
                else if (tDay == 'W')
                {
                    Day = 3;
                }   
                else if (tDay == 'R')
                {
                    Day = 4;
                }
                else if (tDay == 'F')
                {
                    Day = 5;
                }

            
            if(STime.substr(5) == "AM" || STime.substr(0,2) == "12")
            {
                StartHour = (std::stoi(STime.substr(0,2))*60) +std::stoi(STime.substr(3,2)); 
            }
            else
            {
                StartHour = ((std::stoi(STime.substr(0,2))+12)*60) +std::stoi(STime.substr(3,2)); 
            }
        

    }
std::string Course::GetRoom() const
{
    return Room;
}
std::string Course::GetDay() const
{
    if(Day == 1)
    {
        return "Monday";
    }
    else if (Day == 2)
    {
        return "Tuesday";
    }
    else if (Day == 3)
    {
        return "Wednesday";
    }   
    else if (Day == 4)
    {
        return "Thursday";
    }
    else if (Day == 5)
    {
        return "Friday";
    }
    else
    {
        return "Day Not Found";
    }

}
std::string Course::GetTitle() const
{
    return Title;
}
std::string Course::GetDept() const
{
    return Dept;
}
std::string Course::GetSTime() const
{
    return STime;
}
std::string Course::GetETime() const
{
    return ETime;
}
std::string Course::GetCode() const
{
    return Code;
}
int FindMaxDayLen( std::vector<Course>& CL)
{
    int retval = 0;
    for (int i = 0; i != CL.size(); ++i)
    {
        if(CL[i].GetDay().size() > retval)
        {
            retval = CL[i].GetDay().size();
        }
    }
    return retval;

}
int FindMaxRoomLen( std::vector<Course>& CL)
{
    int retval = 0;
    for (int i = 0; i != CL.size(); ++i)
    {
        if(CL[i].GetRoom().size() > retval)
        {
            retval = CL[i].GetRoom().size();
        }
    }
    return retval;

}
int FindMaxCTLen( std::vector<Course>& CL)
{
    int retval = 0;
    for (int i = 0; i != CL.size(); ++i)
    {
        if(CL[i].GetTitle().size() > retval)
        {
            retval = CL[i].GetTitle().size();
        }
    }
    return retval;

}
void PrintHeader(std::ofstream& ostr, int CNameLen, int DNameLen)
{
    ostr << "Dept  Coursenum  Class Title" << std::setw(CNameLen-9) << "  " << "Day" << std::setw(DNameLen -1) << "  " << "Start Time  End Time" << std::endl;
    ostr << "----  ---------  " << std::setfill('-') << std::setw(CNameLen + 2) << "  " << std::setw(DNameLen +2) << "  " << "----------  --------" << std::endl;
}

