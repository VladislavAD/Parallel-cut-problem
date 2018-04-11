#include "IUnit.h"
#include "CutGene.h"
#include "Figure2D.h"
#include <list>
#include <algorithm>
#include <vector>

class CutUnit : public IUnit {
private:
	static std::list<Figure2D> figures;
	static float lineWidth;

	CutGene * genes;
	int genesCount;
	float evaluation;

	/// <summary>
	/// Проверка двух линий на пересечение
	/// </summary>
	bool LineIntersection(Point fbegin, Point fend, Point sbegin, Point send) {
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


	/// <summary>
	/// Проверка на пересечение генов
	/// </summary>
	bool UnitsIntersection(CutGene first, CutGene second) {
		bool ka = false;
		//for (int i = 0; i < first.size_ + 1; i++) {
		//	for (int j = 0; j < second.size_ + 1; j++)
		//	{
		//		//if (i != j){
		//		Point f1, e1, f2, e2;
		//		f1 = Point(first.vertices_[i%first.size_].x + first.getPosition().x, first.vertices_[i%first.size_].y + first.getPosition().y);
		//		e1 = Point(first.vertices_[(i + 1) % first.size_].x + first.getPosition().x, first.vertices_[(i + 1) % first.size_].y + first.getPosition().y);
		//		f2 = Point(second.vertices_[j%second.size_].x + second.getPosition().x, second.vertices_[j%second.size_].y + second.getPosition().y);
		//		e2 = Point(second.vertices_[(j + 1) % second.size_].x + second.getPosition().x, second.vertices_[(j + 1) % second.size_].y + second.getPosition().y);

		//		float check = (first.getPosition().x - second.getPosition().x)*(first.getPosition().x - second.getPosition().x) + (first.getPosition().y - second.getPosition().y)*(first.getPosition().y - second.getPosition().y);

		//		if (LineIntersection(f1, e1, f2, e2))
		//			ka = true;
		//		//}
		//	}
		//}
		return ka;
	}

public:

	///<summary>
	/// Забирает элемент с памятью
	///</summary>
	static void addFigure(Figure2D newFigure) {
		figures.push_back(newFigure);
	}

	///<summary>
	/// Задать ширину полосы раскроя
	///</summary>
	static void setLineWidth(float newLineWidth) {
		lineWidth = newLineWidth;
	}

	///<summary>
	/// Инициализация генов
	///</summary>
	void InitializeGenes() {
		if (figures.size < 0) {
			return;
		}
		genes = new CutGene[figures.size];

		std::vector<int> randomOrderNumbers = std::vector<int>();
		for (int i = 0; i < figures.size; i++) {
			randomOrderNumbers.push_back(i);
		}
		std::random_shuffle(randomOrderNumbers.begin, randomOrderNumbers.end);

		for (int i = 0; i < figures.size; i++) {
			float positionX = (rand() % ((int)lineWidth * 1000)) / 1000.0f;
			float rotation = (rand() % (360 * 100)) / 100.0f;
			int order = randomOrderNumbers.back;
			genes[i] = CutGene(positionX, rotation, order);
			randomOrderNumbers.pop_back();
		}
	}

	int getGenesCount() {
		return genesCount;
	}

	void mutateGene(int number) {

	}

	/*static void fillFigures(std::list<Figure2D> newFigures) {
		while (newFigures.front) {

		}
	}*/
};