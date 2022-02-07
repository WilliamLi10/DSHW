
#ifndef __BOARD_H__
#define __BOARD_H__

class Board{
#include<string>
#include<fstream>
public:

int numTokensInRow(int Row) const;
int numTokensInColumn(int Column) const;
int numRows() const {return row;} 
int numColumns() const {return column;} 
std::string GetP1() const {return P1;} 
std::string GetP2() const {return P2;} 
std::string GetBlank() const{return Blank;}
int** GetM_Data() const{retun m_data;}
Board(const std::string& PT1, const std::string& PT2, const std::string& TBlank);
Board(const Board& B);

private:
    std::string P1;
    std::string P2;
    std::string Blank;
    std::string **m_data;
    int column = 4;
    int row = 5;

    //int* elements;






};


std::ostream& operator << (std::ostream& ostr, const Board& b);

#endif