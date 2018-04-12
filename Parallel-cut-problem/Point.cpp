#include <math.h>

class Point {
private:
public:
	float x;
	float y;

	Point() {}

	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Point Add(Point second) {
		this->x += second.x;
		this->y += second.y;
	}

	void Rotate(float degreeAngle) {
		float PI = 3.1415927;
		float cosinus = cos(degreeAngle * PI / 180.0);
		float sinus = sin(degreeAngle * PI / 180.0);
		float tmpX = this->x * cosinus - this->y * sinus;
		float tmpY = this->x * sinus + this->y * cosinus;
		this->x = tmpX;
		this->y = tmpY;
	}

	/// <summary>
	/// Проверка двух линий на пересечение
	/// </summary>
	static bool LineIntersection(Point fbegin, Point fend, Point sbegin, Point send) {
		// обработка пересечения параллельных осям линий
		// TODO: порефакторить бы этот бедлам
		bool firstparallelX = false;
		bool firstparallelY = false;
		bool secondparallelX = false;
		bool secondparallelY = false;
		if (abs(fend.y - fbegin.y) < 0.001) firstparallelX = true;
		if (abs(fend.x - fbegin.x) < 0.001) firstparallelY = true;
		if (abs(send.y - sbegin.y) < 0.001) secondparallelX = true;
		if (abs(send.x - sbegin.x) < 0.001) secondparallelY = true;
		if (firstparallelX || firstparallelY || secondparallelX || secondparallelY) {
			if (firstparallelX) {
				bool yfit = send.y < fend.y && sbegin.y > fend.y || send.y > fend.y && sbegin.y < fend.y;
				double x = ((sbegin.x - send.x) * fend.y + (send.x * sbegin.y - sbegin.x * send.y)) / (sbegin.y - send.y);
				bool xfit = fend.x < x && fbegin.x > x || fend.x > x && fbegin.x < x;
				if (yfit && xfit) return true;
			}
			if (firstparallelY) {
				bool xfit = send.x < fend.x && sbegin.x > fend.x || send.x > fend.x && sbegin.x < fend.x;
				double y = ((sbegin.y - send.y) * fend.x + (send.y * sbegin.x - sbegin.y * send.x)) / (sbegin.x - send.x);
				bool yfit = fend.y < y && fbegin.y > y || fend.y > y && fbegin.y < y;
				if (yfit && xfit) return true;
			}
			if (secondparallelX) {
				bool yfit = fend.y < send.y && fbegin.y > send.y || fend.y > send.y && fbegin.y < send.y;
				double x = ((fbegin.x - fend.x) * send.y + (fend.x * fbegin.y - fbegin.x * fend.y)) / (fbegin.y - fend.y);
				bool xfit = send.x < x && sbegin.x > x || send.x > x && sbegin.x < x;
				if (yfit && xfit) return true;
			}
			if (secondparallelY) {
				bool xfit = fend.x < send.x && fbegin.x > send.x || fend.x > send.x && fbegin.x < send.x;
				double y = ((fbegin.y - fend.y) * send.x + (fend.y * fbegin.x - fbegin.y * fend.x)) / (fbegin.x - fend.x);
				bool yfit = send.y < y && sbegin.y > y || send.y > y && sbegin.y < y;
				if (yfit && xfit) return true;
			}
		}
		double a1, b1, a2, b2;
		bool pox = false;
		a1 = (fend.y - fbegin.y) / (fend.x - fbegin.x);
		a2 = (send.y - sbegin.y) / (send.x - sbegin.x);
		b1 = (fend.x * fbegin.y - fbegin.x * fend.y) / (fend.x - fbegin.x);
		b2 = (send.x * sbegin.y - sbegin.x * send.y) / (send.x - sbegin.x);
		double b = b2 - b1;
		double a = a1 - a2;
		if (abs(a) < 0.0001) return false;
		else {
			double x = b / a;
			bool cross1 = fbegin.x - fend.x > 0.001 && x - fbegin.x<0.001 && x - fend.x>0.001 || fbegin.x - fend.x < 0 && x - fbegin.x>0 && x - fend.x < 0;
			bool cross2 = sbegin.x - send.x > 0.001 && x - sbegin.x<0.001 && x - send.x>0.001 || sbegin.x - send.x < 0 && x - sbegin.x>0 && x - send.x < 0;
			if (cross1 && cross2)
				pox = true;
		}

		a1 = (fend.x - fbegin.x) / (fend.y - fbegin.y);
		a2 = (send.x - sbegin.x) / (send.y - sbegin.y);
		b1 = (fend.y * fbegin.x - fbegin.y * fend.x) / (fend.y - fbegin.y);
		b2 = (send.y * sbegin.x - sbegin.y * send.x) / (send.y - sbegin.y);
		b = b2 - b1;
		a = a1 - a2;
		if (abs(a) < 0.0001) return false;
		else {
			double y = b / a;
			bool cross1 = fbegin.y - fend.y > 0.001 && y - fbegin.y < 0.001 && y - fend.y > 0.001 || fbegin.y - fend.y < 0 && y - fbegin.y>0 && y - fend.y < 0;
			bool cross2 = sbegin.y - send.y > 0.001 && y - sbegin.y < 0.001 && y - send.y > 0.001 || sbegin.y - send.y < 0 && y - sbegin.y>0 && y - send.y < 0;
			if (cross1 && cross2 && pox)
				return true;
		}
		return false;
	}
};