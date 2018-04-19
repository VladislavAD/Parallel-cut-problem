#pragma once
#include "CutGene.h"
#include <vector>
#include "Figure2D.h"

class CutStrip {
private:
	float width;
	float currentHeight = 0;
	const float eps = 0.0001f;
	std::vector<Figure2D> figures;
	CutGene * genes;
public:
	Point * positionsOfFigures;

	CutStrip(std::vector<Figure2D> figures, CutGene genes[], float width) {
		this->figures = figures;
		this->genes = genes;
		this->width = width;
		// Копированные фигуры повернём
		for (int i = 0; i < figures.size(); i++) {
			figures[i].RotateFigure(genes[i].rotation);
		}
	}

	float UnitEvaluation() {
		this->width = width;

		int * sortedOrder = new int[figures.size()];
		SortOrderOfGenes(genes, *sortedOrder, figures.size());

		positionsOfFigures = new Position[figures.size()];
		for (int i = 0; i < figures.size(); i++)
		{
			positionsOfFigures[i] = Position(0.0f, 0.0f, 0.0f);
		}

		// Роняем фигуры в установленном порядке
		currentHeight = 0;
		for (int i = 0; i < figures.size(); i++)
		{
			// Определяем начальную позицию
			int currentFigure = sortedOrder[i];
			float initialOffset = currentHeight + abs(figures[currentFigure].GetFigureMinimum().y);
			positionsOfFigures[currentFigure].y = initialOffset;
			positionsOfFigures[currentFigure].x = genes[currentFigure].positionX;
			float stepValue = 1.0f;
			while (stepValue > eps) {
				bool intersects = false;
				Point tmpPosition = Point(positionsOfFigures[currentFigure]).Add(Point(0, -stepValue));
				for (int j = 0; j < i; j++) {
					int checkFigure = sortedOrder[j];
					if (Figure2D::IsFiguresIntersecting(figures[currentFigure], tmpPosition, figures[checkFigure], positionsOfFigures[checkFigure])) {
						intersects = false;
						break;
					}
				}
				if (intersects) {
					stepValue /= 2.0f;
				}
				else {
					positionsOfFigures[currentFigure].Add(Point(0, -stepValue));
				}
			}
			if (positionsOfFigures[currentFigure].y + abs(figures[currentFigure].GetFigureMaximum().y) > currentHeight) {
				currentHeight = positionsOfFigures[currentFigure].y + abs(figures[currentFigure].GetFigureMaximum().y);
			}
		}
		return currentHeight;
	}

	/// <summary>
	/// Заполнить массив sortedOrder порядком бросания фигур
	/// </summary>
	void SortOrderOfGenes(CutGene genes[], int & sortedOrder, int size) {
		int * order = new int[size];
		for (int i = 0; i < size; i++) {
			order[i] = genes[i].order;
		}
		int * bufSortedOrder = new int[size];
		// Создаём отсортированный порядок генов. 
		// Порядок однозначен, числа от нуля до сайз, поэтому просто ищем последовательно числа и пишем в массив
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (order[j] == i) {
					bufSortedOrder[i] = j;
					break;
				}
			}
		}
		sortedOrder = *bufSortedOrder;
	}

	Point * GetResultPositions()
	{
		return positionsOfFigures;
	}

	~CutStrip() {
		figures.clear();
		delete[] positionsOfFigures;
	}
};