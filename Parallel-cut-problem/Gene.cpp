#include <list>
#include "Point.cpp"
#include "Position.cpp"

class Gene {
public:
	Position position;
	std::list<Point> points;

	Gene(std::list<Point> points) {
		this->points = points;
	}
};