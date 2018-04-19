#pragma once
#include "CutGene.h"
#include <vector>
#include "Figure2D.h"
#include "Position.cpp"

class CutStrip {
private:
	float width;
	float currentHeight = 0;
	const float eps = 0.0001f;
	std::vector<Figure2D> figures;
	CutGene * genes;
public:
	Point * positionsOfFigures;

	CutStrip(std::vector<Figure2D> figures, CutGene genes[], float width);

	float UnitEvaluation();

	/// <summary>
	/// ��������� ������ sortedOrder �������� �������� �����
	/// </summary>
	void SortOrderOfGenes(CutGene genes[], int & sortedOrder, int size);

	Point * GetResultPositions();

	~CutStrip();
};