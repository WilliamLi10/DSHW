#include"Board.h"
Board::Board(const std::string& PT1, const std::string& PT2, const std::string& TBlank)
: P1(PT1), P2(PT2), Blank(TBlank)
{
	m_data = new int*[4];
	elements = new int[4];
	elements[0] = 0;
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;
 }
std::ostream& operator << (std::ostream& ostr, const Board& b)
{
	for(int i = b.numRows() - 1; i >=0; ++i)
	{
		for(int j = 0; j != b.numColumns() - 2; ++j)
		{
			if  (i> b.numTokensInColumn(j))
			{
				ostr << b.GetBlank() << ' ';
			}
			else
			{
				ostr << b.GetM_Data()[j][i] << ' ';
			}
		}
		if(i > b.numTokensInColumn(b.numColumns() - 1)
		{
			ostr << b.GetBlank() << '\n';
		}
		else
		{
			ostr << b.GetM_Data()[b.numColumns() - 1][i] << '\n';
		}
	}
}