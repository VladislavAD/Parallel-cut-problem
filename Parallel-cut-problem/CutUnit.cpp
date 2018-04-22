#pragma once
#include "CutUnit.h"

CutUnit::CutUnit() {}

CutUnit::~CutUnit() {
	delete[] genes;
	genes = NULL;
}

CutUnit::CutUnit(const CutUnit& other) {
	if (this != &other) {
		delete[] genes;
		genes = NULL;
		genes = new CutGene[this->figures.size()];
		memcpy(genes, other.genes, sizeof(CutGene) * figures.size());
		this->evaluation = other.evaluation;
	}
}

CutUnit & CutUnit::operator=(const CutUnit& other) {
	if (this != &other) {
		delete[] genes;
		genes = NULL;
		genes = new CutGene[this->figures.size()];
		memcpy(this->genes, other.genes, sizeof(CutGene) * figures.size());
		this->evaluation = other.evaluation;
	}
	return *this;
}

///<summary>
/// �������� ������� � �������
///</summary>
void CutUnit::AddFigure(Figure2D newFigure) {
	figures.push_back(newFigure);
}

///<summary>
/// ������ ������ ������ �������
///</summary>
void CutUnit::SetLineWidth(float newLineWidth) {
	lineWidth = newLineWidth;
}

///<summary>
/// ������������� �����
///</summary>
void CutUnit::InitializeGenes() {
	if (figures.size() == 0) {
		return;
	}
	genes = new CutGene[figures.size()];

	// �������� ������ � �������� � �������� �������� ���
	std::vector<int> randomOrderNumbers = std::vector<int>();
	for (int i = 0; i < figures.size(); i++) {
		randomOrderNumbers.push_back(i);
	}
	std::random_shuffle(randomOrderNumbers.begin(), randomOrderNumbers.end());

	for (int i = 0; i < figures.size(); i++) {
		bool newGeneFitLine = false;
		while (!newGeneFitLine) {
			float positionX = (rand() % ((int)lineWidth * 1000)) / 1000.0f;
			float rotation = (rand() % (360 * 100)) / 100.0f;
			int order = randomOrderNumbers.back();
			genes[i] = CutGene(positionX, rotation, order);
			Figure2D testFigure = figures[i];
			testFigure.RotateFigure(rotation);
			newGeneFitLine = testFigure.FitLine(lineWidth, positionX);
		}
		randomOrderNumbers.pop_back();
	}
	randomOrderNumbers.clear();
}

int CutUnit::GetGenesCount() {
	return figures.size();
}

void CutUnit::MutateGene(int number) {
	int randomMutationType = rand() % 3;
	switch (randomMutationType)
	{
		// ������ ��� ������� - ����� �� �����������
	case 0: {
		genes[number].positionX += -horizontalMutation / 2.0f + (rand() % (int)(horizontalMutation * 1000)) / 1000.0f;
		break;
	}
			// ������ ��� ������� - �������
	case 1: {
		genes[number].rotation += rand() % 360000 / 1000.0f;
		break;
	}
			// ������ ��� ������� - ��������� �������, ��� �������� �������� � ������ �����
	case 2: {
		int order = genes[number].order;
		int swapWith = rand() % figures.size();
		genes[number].order = genes[swapWith].order;
		genes[swapWith].order = order;
		break;
	}

	default:
		break;
	}
}

void CutUnit::MutateGene() {
	int number = rand() % figures.size();
	int randomMutationType = rand() % 3;
	switch (randomMutationType)
	{
		// ������ ��� ������� - ����� �� �����������
	case 0: {
		genes[number].positionX += -horizontalMutation / 2.0f + (rand() % (int)(horizontalMutation * 1000)) / 1000.0f;
		break;
	}
			// ������ ��� ������� - �������
	case 1: {
		genes[number].rotation += rand() % 360000 / 1000.0f;
		break;
	}
			// ������ ��� ������� - ��������� �������, ��� �������� �������� � ������ �����
	case 2: {
		int order = genes[number].order;
		int swapWith = rand() % figures.size();
		genes[number].order = genes[swapWith].order;
		genes[swapWith].order = order;
		break;
	}

	default:
		break;
	}
}

void * CutUnit::ExtractGene(int geneNumber) {
	if (geneNumber >= 0 && geneNumber < figures.size()) {
		return &genes[geneNumber];
	}
	return NULL;
}

//IUnit CrossingoverWithUnit(IUnit unit) {
//	CutUnit newUnit = CutUnit();
//	int exchangeGeneNumber = rand() % figures.size;
//	CutGene exchangeGene = static_cast<CutGene>(unit.ExtractGene(exchangeGeneNumber));
//}

/// <summary>
/// ���������������, ����� ��� �� ����� � ��������� � ������ ����� ��� ���� � ����� ������ �����
/// </summary>
CutUnit CutUnit::DummyCrossingover(CutUnit unit) {
	int exchangeGeneNumber = rand() % figures.size();
	CutUnit newCutUnit = *this;
	int oldOrder = this->genes[exchangeGeneNumber].order;
	int newOrder = unit.genes[exchangeGeneNumber].order;

	// ������ ������� � ���� � ����� �� ��������, ����� ����� �����
	for (int i = 0; i < figures.size(); i++) {
		if (this->genes[i].order == newOrder) {
			newCutUnit.genes[i].order = oldOrder;
			break;
		}
	}

	newCutUnit.genes[exchangeGeneNumber] = unit.genes[exchangeGeneNumber];

	return newCutUnit;
}

float CutUnit::GetEvaluation() {
	return evaluation;
}

void CutUnit::Evaluate() {
	CutStrip cutStrip = CutStrip(figures, genes, lineWidth);
	evaluation = cutStrip.UnitEvaluation();
	//delete &cutStrip;
}

bool CutUnit::sortFunction(CutUnit left, CutUnit right) {
	if (left.evaluation > right.evaluation) {
		return true;
	}
	else {
		return false;
	}
}

/*static void fillFigures(std::list<Figure2D> newFigures) {
while (newFigures.front) {

}
}*/

std::vector<Figure2D> CutUnit::figures;
float CutUnit::lineWidth;
