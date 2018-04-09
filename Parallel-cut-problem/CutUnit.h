#include "IUnit.h"
#include "CutGene.h"
#include "Figure2D.h"
#include <list>

class CutUnit : public IUnit {
private:
	static std::list<Figure2D> figures;

	std::list<CutGene> genesList;
	float evaluation;

public:
	
	///<summary>
	/// Забирает элемент с памятью
	///</summary>
	static void addFigure(Figure2D newFigure) {
		figures.push_back(newFigure);
	}

	static void fillFigures(std::list<Figure2D> newFigures) {
		//while ()
	}
};