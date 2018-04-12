#include "IUnit.h"
#include "CutGene.h"
#include "Figure2D.h"
#include <list>
#include <algorithm>
#include <vector>

class CutUnit : public IUnit {
private:
	static std::vector<Figure2D> figures;
	static float lineWidth;

	CutGene * genes;
	int genesCount;
	float evaluation;

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
		if (figures.size == 0) {
			return;
		}
		genes = new CutGene[figures.size];

		// Создадим вектор с порядком и случайно замешаем его
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