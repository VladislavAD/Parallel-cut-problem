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
	CutUnit &operator=(const CutUnit& other) {
		memcpy(genes, other.genes, sizeof(CutGene) * figures.size());
		evaluation = other.evaluation;
		return *this;
	}

	///<summary>
	/// �������� ������� � �������
	///</summary>
	static void AddFigure(Figure2D newFigure) {
		figures.push_back(newFigure);
	}

	///<summary>
	/// ������ ������ ������ �������
	///</summary>
	static void SetLineWidth(float newLineWidth) {
		lineWidth = newLineWidth;
	}

	///<summary>
	/// ������������� �����
	///</summary>
	void InitializeGenes() {
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
			float positionX = (rand() % ((int)lineWidth * 1000)) / 1000.0f;
			float rotation = (rand() % (360 * 100)) / 100.0f;
			int order = randomOrderNumbers.back();
			genes[i] = CutGene(positionX, rotation, order);
			randomOrderNumbers.pop_back();
		}
	}

	virtual int GetGenesCount() {
		return figures.size();
	}

	virtual void MutateGene(int number) {
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

	virtual void MutateGene() {
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

	virtual void * ExtractGene(int geneNumber) {
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
	CutUnit DummyCrossingover(CutUnit unit) {
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

	virtual float GetEvaluation() {
		return evaluation;
	}

	void Evaluate() {
		CutStrip cutStrip = CutStrip(figures, genes, lineWidth);
		evaluation = cutStrip.UnitEvaluation();
		delete &cutStrip;
	}

	static bool sortFunction(CutUnit left, CutUnit right) {
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
};

std::vector<Figure2D> CutUnit::figures;
