#ifndef __Zone_H__
#define __Zone_H__

#include "point.h"
#include <vector>
#include <fstream>
class Zone{
public:
	Zone(char L, int ZoneSize);
	Zone() {}
	bool operator<(const Zone& other) { return this->size < other.size;}
	char letter;
	int size;
	int StarCount;
	std::vector<Point> Points;



};


#endif