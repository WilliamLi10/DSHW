#ifndef __BOARD_H__
#define __BOARD_H__

class Board{
#include<string>
#include<fstream>
public:

int numTokensInRow(int Row) const;
int numTokensInColumn(int Column) const;
int numRows() const;
int numColumns() const;

private:
    std::string P1;
    std::string P2;
    std::string Blank;
    std::string **m_data;






};


std::ostream& operator << (std::ostream& ostr, const Board& b);

#endif