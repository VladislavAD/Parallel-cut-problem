#pragma once
#include "BaseUnit.h"
#include "CutGene.h"
#include "CutStrip.h"
#include "Figure2D.h"
#include "MpiFriendly.h"
#include <list>
#include <algorithm>
#include <vector>
#include <string>

class CutUnit : public BaseUnit {
private:
	float evaluation = 0;
	static std::vector<Figure2D*> figures;
	static float lineWidth;
	const float horizontalMutation = 1.0f;

	CutGene * genes = NULL;
	std::string outputPositions;

public:
	CutUnit();
	~CutUnit();

	///<summary>
	/// �������� ������� � �������
	///</summary>
	static void AddFigure(Figure2D * newFigure);

	///<summary>
	/// ������ ������ ������ �������
	///</summary>
	static void SetLineWidth(float newLineWidth);

	static void Initialize(Figure2D * figures, int figuresCount, float lineWidth);

	///<summary>
	/// ������������� �����
	///</summary>
	void InitializeGenes();

	int GetGenesCount();
	void MutateGene(int number);
	void MutateGene();
	float GetEvaluation();
	BaseUnit * CrossingoverWithUnit(BaseUnit * unit);
	void * ExtractGene(int geneNumber);
	void Evaluate();
	void Delete();
	BaseUnit * Copy();
	void MpiSend(int destination, MPI_Comm communicator);
	void MpiReceive(int source, MPI_Comm communicator);

	/// <summary>
	/// ���������������, ����� ��� �� ����� � ��������� � ������ ����� ��� ���� � ����� ������ �����
	/// </summary>
	CutUnit DummyCrossingover(CutUnit unit);


	static std::string PrintFigures();

	std::string GetPositions();

	/*static void fillFigures(std::list<Figure2D> newFigures) {
		while (newFigures.front) {

		}
	}*/
};