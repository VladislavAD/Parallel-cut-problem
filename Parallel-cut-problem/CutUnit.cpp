#pragma once
#include "CutUnit.h"

CutUnit::CutUnit() {
	genes = NULL;
	evaluation = -1;
	InitializeGenes();
}

CutUnit::~CutUnit() {
	delete[] genes;
	genes = NULL;
}

///<summary>
/// «абирает элемент с пам€тью
///</summary>
void CutUnit::AddFigure(Figure2D * newFigure) {
	figures.push_back(newFigure);
}

///<summary>
/// «адать ширину полосы раскро€
///</summary>
void CutUnit::SetLineWidth(float newLineWidth) {
	lineWidth = newLineWidth;
}

void CutUnit::Initialize(Figure2D * figures, int figuresCount, float lineWidth)
{
	for (int i = 0; i < figuresCount; i++) {
		AddFigure(&figures[i]);
	}
	SetLineWidth(lineWidth);
}

///<summary>
/// »нициализаци€ генов
///</summary>
void CutUnit::InitializeGenes() {
	if (figures.size() == 0) {
		return;
	}
	genes = new CutGene[figures.size()];

	// —оздадим вектор с пор€дком и случайно замешаем его
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
			Figure2D testFigure = figures[i]->Copy();
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
		// ѕервый тип мутации - сдвиг по горизонтали
	case 0: {
		genes[number].positionX += -horizontalMutation / 2.0f + (rand() % (int)(horizontalMutation * 1000)) / 1000.0f;
		break;
	}
			// ¬торой тип мутации - поворот
	case 1: {
		genes[number].rotation += rand() % 360000 / 1000.0f;
		break;
	}
			// “ретий тип мутации - изменение пор€дка, ген мен€етс€ пор€дком с другим геном
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
		// ѕервый тип мутации - сдвиг по горизонтали
	case 0: {
		genes[number].positionX += -horizontalMutation / 2.0f + (rand() % (int)(horizontalMutation * 1000)) / 1000.0f;
		break;
	}
			// ¬торой тип мутации - поворот
	case 1: {
		genes[number].rotation += rand() % 360000 / 1000.0f;
		break;
	}
			// “ретий тип мутации - изменение пор€дка, ген мен€етс€ пор€дком с другим геном
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

BaseUnit CutUnit::CrossingoverWithUnit(BaseUnit unit) {
	CutUnit * castUnit = dynamic_cast<CutUnit*>(&unit);
	int exchangeGeneNumber = rand() % figures.size();
	CutUnit newCutUnit = *this;
	int oldOrder = this->genes[exchangeGeneNumber].order;
	int newOrder = castUnit->genes[exchangeGeneNumber].order;

	// ћен€ем пор€док у гена с таким же пор€дком, какой будет новый
	for (int i = 0; i < figures.size(); i++) {
		if (this->genes[i].order == newOrder) {
			newCutUnit.genes[i].order = oldOrder;
			break;
		}
	}

	newCutUnit.genes[exchangeGeneNumber] = castUnit->genes[exchangeGeneNumber];

	return newCutUnit;
}

/// <summary>
///  остыльсинговер, берем ген из особи в параметре и создаЄм новый ген себ€ с геном второй особи
/// </summary>
CutUnit CutUnit::DummyCrossingover(CutUnit unit) {
	int exchangeGeneNumber = rand() % figures.size();
	CutUnit newCutUnit = *this;
	int oldOrder = this->genes[exchangeGeneNumber].order;
	int newOrder = unit.genes[exchangeGeneNumber].order;

	// ћен€ем пор€док у гена с таким же пор€дком, какой будет новый
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
	std::vector<Figure2D> bufferFigures = std::vector<Figure2D>(0);
	for (int i = 0; i < figures.size(); i++)
	{
		bufferFigures.push_back(figures[i]->Copy());
	}
	CutStrip * cutStrip = new CutStrip(bufferFigures, genes, lineWidth);
	evaluation = cutStrip->UnitEvaluation();
	for (int i = 0; i < figures.size(); i++)
	{
		Figure2D * figureToDelete = &bufferFigures.back();
		//delete figureToDelete;
		figureToDelete->~Figure2D();
	}
	bufferFigures.clear();
	delete cutStrip;
}

void CutUnit::Delete() {
	this->~CutUnit();
}

BaseUnit * CutUnit::Copy()
{
	CutUnit * copyUnit = new CutUnit();
	for (int i = 0; i < figures.size(); i++)
	{
		copyUnit->genes[i].order = this->genes[i].order;
		copyUnit->genes[i].positionX = this->genes[i].positionX;
		copyUnit->genes[i].rotation = this->genes[i].rotation;
	}
	return copyUnit;
}

/*static void fillFigures(std::list<Figure2D> newFigures) {
while (newFigures.front) {

}
}*/

std::vector<Figure2D*> CutUnit::figures;
float CutUnit::lineWidth;
