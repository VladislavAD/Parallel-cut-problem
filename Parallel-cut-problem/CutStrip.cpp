#pragma once
#include "CutStrip.h"

CutStrip::CutStrip() {
	figures = std::vector<Figure2D>();
	genes = NULL;
	width = -1;
}

CutStrip::CutStrip(std::vector<Figure2D> figures, CutGene genes[], float width) {
	this->figures = figures;
	this->genes = genes;
	this->width = width;
	// Копированные фигуры повернём
	for (int i = 0; i < figures.size(); i++) {
		this->figures[i].RotateFigure(genes[i].rotation);
	}
}

CutStrip & CutStrip::operator=(const CutStrip& other) {
	if (this != &other) {
		delete[] this->positionsOfFigures;
		memcpy(this->positionsOfFigures, other.positionsOfFigures, sizeof(Position) * figures.size());
		this->figures = other.figures;
		this->genes = other.genes;
		this->width = other.width;
	}
	return *this;
}

CutStrip::~CutStrip() {
	figures.clear();
	delete[] positionsOfFigures;
}

float CutStrip::UnitEvaluation() {
	this->width = width;

	int * sortedOrder = SortOrderOfGenes(genes, figures.size());

	positionsOfFigures = new Position[figures.size()];
	for (int i = 0; i < figures.size(); i++)
	{
		positionsOfFigures[i] = Position(0.0f, 0.0f, 0.0f);
	}

	// Роняем фигуры в установленном порядке
	currentHeight = 0;
	float evaluation = 0;
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
			if (figures[currentFigure].GetFigureMinimum().y + tmpPosition.y < 0) {
				intersects = true;
			}
			for (int j = 0; j < i; j++) {
				int checkFigure = sortedOrder[j];
				if (Figure2D::IsFiguresIntersecting(figures[currentFigure], tmpPosition, figures[checkFigure], positionsOfFigures[checkFigure])) {
					intersects = true;
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
		evaluation += positionsOfFigures[currentFigure].y + abs(figures[currentFigure].GetFigureMaximum().y);
	}
	delete [] sortedOrder;
	return evaluation;
}

/// <summary>
/// Заполнить массив sortedOrder порядком бросания фигур
/// </summary>
int * CutStrip::SortOrderOfGenes(CutGene genes[], int size) {
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
	delete[] order;
	return bufSortedOrder;
}

Point * CutStrip::GetResultPositions()
{
	return positionsOfFigures;
}
