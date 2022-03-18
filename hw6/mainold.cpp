#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include "square.h"
#include "Zone.h"
#include"point.h"
typedef std::vector<std::vector<Square>> Grid;
int MaxStars = 0;
int NumStarsInZone(const Grid& CurGrid, char ZoneLetter)
{
	int StarCount = 0;
	for(int i = 0; i != CurGrid.size(); ++i)
	{
		for(int j = 0; j != CurGrid[0].size(); ++j)
		{
			if(CurGrid[i][j].getZone() == ZoneLetter && CurGrid[i][j].getVal() == '@')
			{
				++StarCount;
			}
		}
	}
	return StarCount;
}
int NumStarsInRow(const Grid& CurGrid, int row)
{
	int StarCount = 0;
	for(int i = 0; i != CurGrid[row].size(); ++i)
	{
		if(CurGrid[row][i].getVal() == '@')
		{
			++StarCount;
		}
	}
	return StarCount;
}
int NumStarsInColumn(const Grid& CurGrid, int column)
{
	int StarCount = 0;
	for(int i = 0; i != CurGrid.size(); ++i)
	{
		if(CurGrid[i][column].getVal() == '@')
		{
			++StarCount;
		}
	}
	return StarCount;
}
bool CanPut(const Grid& CurGrid, int row, int column)
{
	if(NumStarsInZone(CurGrid,CurGrid[row][column].getZone()) >= MaxStars)
	{
		return false;
	}
	 if(NumStarsInRow(CurGrid,row) >= MaxStars)
	{
		return false;
	}
 if(NumStarsInColumn(CurGrid,column) >= MaxStars)
	{
		return false;
	}
	 if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))][column].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[std::max(0,row-1)][column].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[row][std::min(column+1,int(CurGrid[row].size()))].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[row][std::max(0,column-1)].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))][std::min(column+1,int(CurGrid[row].size() - 1))].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))][std::max(0,column-1)].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[std::max(0,row-1)][std::min(column+1,int(CurGrid[row].size()))].getVal() == '@')
	{
		return false;
	}
	 if( CurGrid[std::max(0,row-1)][std::max(0,column-1)].getVal() == '@')
	{
		return false;
	}
	return true;
}
bool GridSolved(const Grid& CurGrid,const std::vector<char>& Zones)
{
	for(int i = 0; i != Zones.size(); ++i)
	{
		if(NumStarsInZone(CurGrid,Zones[i])  != MaxStars)
		{
			return false;
		}
	}
	return true;
}

Grid CreateGrid(char* FileName,std::vector<Zone>& Zones)
{
	std::ifstream inFile;
	inFile.open(FileName);
	int rownum, columnnum;
	inFile >> rownum >> columnnum;
	Grid retGrid(rownum,std::vector<Square>(columnnum,Square()));
	char newZone;
	int square_count;
	while(inFile >> newZone >> square_count)
	{
		Zones.push_back(Zone(newZone,square_count,inFile));
		//std::cout << [i][j].getZone() <<' ';
	}
	return retGrid;
}

int main(int argc, char* argv[])
{
	std::ifstream inFile;
	std::ofstream outFile;
	inFile.open(argv[1]);
	MaxStars = *argv[3] - '0';
	std::vector<Zone> Zones;
	std::vector<Point> Stars;
	Grid CurGrid = CreateGrid(argv[1],Zones);
	bool SolutionFound = false;
	std::vector<Grid> SolvedGrids;
	if(std::string(argv[5]) == "all_solutions")
		Solve(CurGrid,SolvedGrids,Zones,0,0,true,SolutionFound);
	else
		Solve(CurGrid,SolvedGrids,Zones,0,0,false,SolutionFound);
	outFile.open(argv[2]);
	outFile << "Number of solutions: " << SolvedGrids.size() << std::endl;
	if(std::string(argv[4]) == "print")
	{
	}
}