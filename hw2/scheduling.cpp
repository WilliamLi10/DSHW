#include"course.h"
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include<iomanip>

int main(int argc, char* argv[])
{
    //creates variables that will be used when the file is being read, also makes vector to hold all the courses
    std::vector<Course> CourseList;
    int ID;
    std::string Dept;
    std::string Code;
    std::string Title;
    std::string Days;
    std::string STime;
    std::string ETime;
    std::string Room;
    //opens files specified in command line arguments
    std::ifstream infile;
    infile.open(argv[1]);
    std::ofstream outfile;
    outfile.open(argv[2]);
    //checks to see which data should be printed
    if(std::string(argv[3]) == "room")
    {
        //reads the infiles based on the arguments
        if(argc == 5)
        {
            while( infile >> ID >> Dept >> Code >> Title >>  Days >> STime >> ETime >> Room)
            {
                for (int i = 0; i != Days.size(); ++i)
                {                      
                    if(Room == std::string(argv[4]))
                    {
                        CourseList.push_back(Course(ID,Dept,Code,Title,Days[i],STime,ETime,Room));
                    }
                }
            }
        }
        else
        {
            while( infile >> ID >> Dept >> Code >> Title >>  Days >> STime >> ETime >> Room)
            {
                for (int i = 0; i != Days.size(); ++i)
                {                      
                    CourseList.push_back(Course(ID,Dept,Code,Title,Days[i],STime,ETime,Room));
                    
                }
            }
        }

        //if no data available state so and exit program
        if(CourseList.size() == 0)
            {
                outfile << "No data available." << std::endl;
                return 1;
            }
        /*sorts the entire course list. It will then scan the vector starting from the beginning until it reaches the first course with a different room than the first one.
        from that point, it will copy that segment into another vector and proceed to print out all the courses inside that subvector*/    
        std::sort(CourseList.begin(),CourseList.end(),RoomSort);
        std::vector<Course>::iterator i = CourseList.begin();
        std::vector<Course>::iterator j = i + 1;
        while(i != CourseList.end())
        {
            while((j != CourseList.end()) && (j->GetRoom() == i->GetRoom()) )
            {
                ++j;
            }
            std::vector<Course> SubCourseList(std::distance(i,j));
            std::copy(i,j,SubCourseList.begin());
            i = j;
            //used to find the max length for the day section and the title section
            int MaxCTLen = std::max(11,FindMaxCTLen(SubCourseList));
            int MaxDayLen = FindMaxDayLen(SubCourseList);
            //prints out the header
            outfile << "Room " << SubCourseList[0].GetRoom() <<std::endl;
            PrintHeader( outfile, MaxCTLen,MaxDayLen);
            //iterates through sub vector and prints out the information for the courses. It will separate each piece of data with an appropriate number of spaces based on the lenghth of that piece of data
            for( int i = 0; i != SubCourseList.size(); ++i)
            {
            outfile << std::setfill(' ') <<SubCourseList[i].GetDept() << "  " <<  SubCourseList[i].GetCode() << std::setw(9 - SubCourseList[i].GetCode().size() + 2 )<< "  " << SubCourseList[i].GetTitle() << 
            std::setw(MaxCTLen - SubCourseList[i].GetTitle().size() + 2) << "  " << SubCourseList[i].GetDay() << std::setw(MaxDayLen - SubCourseList[i].GetDay().size() + 2 ) << "  " << SubCourseList[i].GetSTime() << "     " << SubCourseList[i].GetETime() << ' ' << std::endl;
            }
            outfile << SubCourseList.size() << " entries" << std::endl << std::endl;        
        }

    }


    //checks if input is department
    else if (std::string(argv[3]) == "dept")
    {
        //if there is no given department, shoot an error out
        if (argc != 5)
        {
            std::cerr << "Missing Department" << std::endl;
            return 1;
        }
        //reads the file and only adds courses with the correct department
        while( infile >> ID >> Dept >> Code >> Title >>  Days >> STime >> ETime >> Room)
        {
            for (int i = 0; i != Days.size(); ++i)
            {
                if(Dept == std::string(argv[4]))
                {
                    CourseList.push_back(Course(ID,Dept,Code,Title,Days[i],STime,ETime,Room));
                }
            }
        }
        //if there is no data, it will shoot an error
        if(CourseList.size() == 0)
            {
                outfile << "No data available." << std::endl;
                return 1;
            }
        //sorts the vector and then prints everything out in a similar way to the way described in the room section above
        std::sort(CourseList.begin(),CourseList.end(),DeptSort);
        outfile << "Dept " << argv[4] << std::endl;
        int MaxCTLen = std::max(11,FindMaxCTLen(CourseList));
        int MaxDayLen = FindMaxDayLen(CourseList);
        outfile << "Coursenum  Class Title" << std::setw(MaxCTLen-9) << "  " << "Day" << std::setw(MaxDayLen -1) << "  " << "Start Time  End Time" << std::endl;
        outfile << "---------  " << std::setfill('-') << std::setw(MaxCTLen + 2) << "  " << std::setw(MaxDayLen +2) << "  " << "----------  --------" << std::endl;
        for (int i = 0; i!= CourseList.size(); ++i) 
        {
            outfile << std::setfill(' ') << CourseList[i].GetCode() << std::setw(9 - CourseList[i].GetCode().size() + 2 ) << "  " << CourseList[i].GetTitle() << 
            std::setw(MaxCTLen - CourseList[i].GetTitle().size() + 2) << "  " << CourseList[i].GetDay() << std::setw(MaxDayLen - CourseList[i].GetDay().size() + 2 ) << "  " << CourseList[i].GetSTime() << "     " << CourseList[i].GetETime() << ' ' << std::endl;
        }
        outfile << CourseList.size() << " entries" << std::endl << std::endl;
    }
    //custom section will print out all courses that take place on a friday.
    else if (std::string(argv[3]) == "custom")
    {
        //reads the file in a way similar to department, except it checsk the day for friday
        while( infile >> ID >> Dept >> Code >> Title >>  Days >> STime >> ETime >> Room)
        {
            for (int i = 0; i != Days.size(); ++i)
            {                      
                if(Days[i] == 'F')
                CourseList.push_back(Course(ID,Dept,Code,Title,Days[i],STime,ETime,Room));
                    
            }
        }
        //sorts the vector and then prints it out similar to the department section of the code
        std::sort(CourseList.begin(),CourseList.end(),DaySort);
        outfile << "Courses on Friday"  << std::endl;
        int MaxCTLen = std::max(11,FindMaxCTLen(CourseList));
        int MaxRoomLen = FindMaxRoomLen(CourseList);
        outfile << "Coursenum  Class Title" << std::setw(MaxCTLen-9) << "  " << "Room" << std::setw(MaxRoomLen-2) << "  " << "Start Time  End Time" << std::endl;
        outfile << "---------  " << std::setfill('-') << std::setw(MaxCTLen + 2) << "  " << std::setw(MaxRoomLen +2) << "  " << "----------  --------" << std::endl;
        for (int i = 0; i!= CourseList.size(); ++i) 
        {
            outfile << std::setfill(' ') << CourseList[i].GetCode() <<  std::setw(9 - CourseList[i].GetCode().size() + 2 ) << "  " << CourseList[i].GetTitle() << 
            std::setw(MaxCTLen - CourseList[i].GetTitle().size() + 2) << "  " << CourseList[i].GetRoom() << std::setw(MaxRoomLen - CourseList[i].GetRoom().size() + 2 ) << "  " << CourseList[i].GetSTime() << "     " << CourseList[i].GetETime() << ' ' << std::endl;
        }
        outfile << CourseList.size() << " entries" << std::endl << std::endl;
            
    }
    //if none of the if statements are true, the input is invalid and shoots an error
    else{
        std::cerr << "invalid input" << std::endl;
        return 1;
    }
    return 0;
    
}