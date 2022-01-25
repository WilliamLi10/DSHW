#ifndef __COURSE_H__
#define __COURSE_H__
#include<string>
#include<vector>
#include<fstream>
class Course{
    public:
        Course();
        Course(int tID, std::string tDept, std::string tCode, std::string tTitle, char tDay, std::string tSTime, std::string tETime, std::string tRoom);
        std::string GetRoom() const;
        std::string GetDept() const;
        std::string GetTitle() const;
        std::string GetDay() const;
        std::string GetSTime() const;
        std::string GetETime() const;
        std::string GetCode() const;
        //friend void PrintCourses(std::ostream& ostr, const std::vector<Course>& Courses);
        friend bool RoomSort(const Course& C1, const Course&C2);
        friend bool DeptSort(const Course& C1, const Course&C2);
        friend bool DaySort(const Course& C1, const Course&C2);
    private:
        int ID;
        std::string Dept;
        std::string Code;
        std::string Title;
        std::string STime;
        std::string ETime;
        std::string Room;
        int Day;
        int StartHour;

};
bool RoomSort(const Course& C1, const Course&C2);
bool DeptSort(const Course& C1, const Course&C2);
bool DaySort(const Course& C1, const Course&C2);
int FindMaxRoomLen(std::vector<Course>& CL);
int FindMaxDayLen( std::vector<Course>& CL);
int FindMaxCTLen( std::vector<Course>& CL);
void PrintHeader(std::ofstream& ostr, int CNameLen, int DNameLen);
#endif