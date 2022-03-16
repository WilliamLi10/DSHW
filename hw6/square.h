#ifndef __SQUARE_H__
#define __SQUARE_H__
#include"Zone.h"
class Square{
public:
	Square()
		: Val('.') {}
	void SetZone(char CurZone) {MyZone = CurZone;}
	char getZone() const { return MyZone;}
	void SetVal(char CurVal){Val = CurVal;}
	char getVal() const{return Val;}
	~Square();
private:
	char Val;
	char MyZone;


};


#endif