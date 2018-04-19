#pragma once
#include "IUnit.h"
#include "CutGene.h"
#include "CutStrip.h"
#include "Figure2D.h"
#include <list>
#include <algorithm>
#include <vector>

class CutUnit {
private:
	static std::vector<Figure2D> figures;
	static float lineWidth;
	const float horizontalMutation = 1.0f;

	CutGene * genes;
	float evaluation;

public:
	CutUnit & operator=(const CutUnit& other);

	///<summary>
	/// Забирает элемент с памятью
	///</summary>
	static void AddFigure(Figure2D newFigure);

	///<summary>
	/// Задать ширину полосы раскроя
	///</summary>
	static void SetLineWidth(float newLineWidth);

	///<summary>
	/// Инициализация генов
	///</summary>
	void InitializeGenes();

	virtual int GetGenesCount();

	virtual void MutateGene(int number);

	virtual void MutateGene();

	virtual void * ExtractGene(int geneNumber);

	//IUnit CrossingoverWithUnit(IUnit unit) {
	//	CutUnit newUnit = CutUnit();
	//	int exchangeGeneNumber = rand() % figures.size;
	//	CutGene exchangeGene = static_cast<CutGene>(unit.ExtractGene(exchangeGeneNumber));
	//}

	/// <summary>
	/// Костыльсинговер, берем ген из особи в параметре и создаём новый ген себя с геном второй особи
	/// </summary>
	CutUnit DummyCrossingover(CutUnit unit);

	virtual float GetEvaluation();

	void Evaluate();

	static bool sortFunction(CutUnit left, CutUnit right);

	/*static void fillFigures(std::list<Figure2D> newFigures) {
		while (newFigures.front) {

		}
	}*/
};