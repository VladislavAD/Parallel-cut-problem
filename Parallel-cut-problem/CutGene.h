#include <list>
#include "Point.cpp"
#include "Position.cpp"

class CutGene {
public:
	float positionX;
	int order;
	std::list<Point> points;

	CutGene(std::list<Point> points) {
		this->points = points;
		this->positionX = 0;
		this->order = 0;
	}
};