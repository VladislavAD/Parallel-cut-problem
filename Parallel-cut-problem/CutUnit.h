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
	const float horizontalMutation = 1.0f;

	CutGene * genes;
	int genesCount;
	float evaluation;

public:

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
		if (figures.size == 0) {
			return;
		}
		genes = new CutGene[figures.size];

		// �������� ������ � �������� � �������� �������� ���
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

	int GetGenesCount() {
		return figures.size;
	}

	void MutateGene(int number) {
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
			int swapWith = rand() % figures.size;
			genes[number].order = genes[swapWith].order;
			genes[swapWith].order = order;
			break;
		}

		default:
			break;
		}
	}

	IUnit CrossingoverWithUnit(IUnit unit) {
	}

	/*static void fillFigures(std::list<Figure2D> newFigures) {
		while (newFigures.front) {

		}
	}*/
};