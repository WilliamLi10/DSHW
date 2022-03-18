#include "point.h"
#include"Zone.h"
#include <vector>
Zone::Zone(char L, int ZoneSize)
{
	letter = L;
	size = ZoneSize;
	StarCount = 0;
}