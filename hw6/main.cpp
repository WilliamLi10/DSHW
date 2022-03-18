#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<algorithm>
#include "square.h"
#include "Zone.h"
#include"point.h"
typedef std::vector<std::vector<Square>> Grid;
int MaxStars = 0;
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

	if(NumStarsInRow(CurGrid,row) >= MaxStars)
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
	else if( CurGrid[std::min(row+1,int(CurGrid.size() - 1))][std::min(column+1,int(CurGrid[row].size() - 1))].getVal() == '@')
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
bool GridSolved(const std::vector<Zone> Zones)
{
	for(int i = 0; i != Zones.size(); ++i)
	{
		if(Zones[i].StarCount != MaxStars)
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
		Zones.push_back(Zone(newZone, square_count));
		for (int i = 0; i != square_count; ++i)
		{
			int x, y;
			inFile >> x >> y;
			Zones.back().Points.push_back(Point(x, y));
			retGrid[y][x].SetZone(newZone);
		}
		//std::cout << [i][j].getZone() <<' ';
	}
	return retGrid;
}
void Solve(const std::vector<Zone>& Zones, Grid& CurGrid,Grid& SolvedGrids, int CurPoint)
{
	for (int i = CurPoint; i != Zones.size(); ++i)
	{
		if (GridSolved(Zones))
		{
			SolvedGrids.push_back(Grid(CurGrid));
			return;
		}
		else
		{
			for (int j = 0; j != Zones[i].Points.size(); ++j)
			{
				if (CanPut(CurGrid, Zones[i].Points[j].y, Zones[i].Points[j].x))
				{
					CurGrid[Zones[i].Points[j].y][Zones[i].Points[j].x].SetVal('@');
					++Zones[i].StarCount;
					Solve(Zones, CurGrid, SolvedGrids, j + 1);
					CurGrid[Zones[i].Points[j].y][Zones[i].Points[j].x].SetVal('.');
				}
			}
			if (Zones[i].StarCount != MaxStars)
			{
				return;
			}
		}
	}
}
int main(int argc, char* argv[])
{
	std::ifstream inFile;
	std::ofstream outFile;
	inFile.open(argv[1]);
	MaxStars = *argv[3] - '0';
	std::vector<Zone> Zones;
	std::vector<Point> Stars;
	Grid CurGrid = CreateGrid(argv[1], Zones);
	std::sort(Zones.begin(), Zones.end());
	for (int i = 0; i  != Zones.size(); ++i)
	{
		std::cout << Zones[i].size << std::endl;
	}
	for (int i = 0; i != CurGrid.size(); ++i)
	{
		for (int j = 0; j != CurGrid[i].size(); ++j)
		{
			std::cout << CurGrid[i][j].getZone();
		}
		std::cout << std::endl;
	}
}