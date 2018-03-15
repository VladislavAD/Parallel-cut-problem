

class Point {
public:
	float x;
	float y;

	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Point Add(Point second) {
		this->x += second.x;
		this->y += second.y;
	}
};