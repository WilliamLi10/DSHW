#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include "square.h"
#include "Zone.h"
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
	else if(NumStarsInRow(CurGrid,row) >= MaxStars)
	{
		return false;
	}
	else if(NumStarsInColumn(CurGrid,column) >= MaxStars)
	{
		return false;
	}
	else if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))][column].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[std::max(0,row-1)][column].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[row][std::min(column+1,int(CurGrid[row].size()))].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[row][std::max(0,column-1)].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))]
		[std::min(column+1,int(CurGrid[column].size()))].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))][std::max(0,column-1)].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[std::max(0,row-1)][std::min(column+1,int(CurGrid[row].size()))].getVal() == '@')
	{
		return false;
	}
	else if( CurGrid[std::max(0,row-1)][std::max(0,column-1)].getVal() == '@')
	{
		return false;
	}
	return true;
}


Grid CreateGrid(char* FileName)
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
		int x, y;
		for(int i = 0; i != square_count; ++i)
		{
			inFile >> x >> y;
			retGrid[y][x].SetZone(newZone);
		}
		//std::cout << [i][j].getZone() <<' ';
	}
	return retGrid;
}
void Solve(Grid& CurGrid, std::vector<Grid>& FailedGrids, std::vector<Grid>& SolvedGrids)
{
	
}
int main(int argc, char* argv[])
{
	std::ifstream inFile;
	inFile.open(argv[1]);
	MaxStars = *argv[3] - '0';
	std::vector<Square> ZoneStartPts;
	Grid CurGrid = CreateGrid(argv[1]);
	CurGrid[0][0].SetVal('@');
	for(int i = 0; i != CurGrid.size(); ++i)
	{
		for(int j = 0; j != CurGrid[i].size(); ++j)
		{
			std::cout << CurGrid[i][j].getVal() <<' ';
		}
		std::cout << std::endl;
	}
	if(CanPut(CurGrid,0,2))
	{
		std::cout << "True" << std::endl;
	}
	else
	{
		std::cout <<"False" << std::endl;
	}
	//DeleteZones(ZoneStartPts);
}