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
	/// Забирает элемент с памятью
	///</summary>
	static void AddFigure(Figure2D * newFigure);

	///<summary>
	/// Задать ширину полосы раскроя
	///</summary>
	static void SetLineWidth(float newLineWidth);

	static void Initialize(Figure2D * figures, int figuresCount, float lineWidth);

	///<summary>
	/// Инициализация генов
	///</summary>
	void InitializeGenes();

	virtual int GetGenesCount();
	virtual void MutateGene(int number);
	virtual void MutateGene();
	virtual void * ExtractGene(int geneNumber);
	BaseUnit * CrossingoverWithUnit(BaseUnit * unit);
	void MpiSend(int destination, MPI_Comm communicator);
	void MpiReceive(int source, MPI_Comm communicator);

	/// <summary>
	/// Костыльсинговер, берем ген из особи в параметре и создаём новый ген себя с геном второй особи
	/// </summary>
	CutUnit DummyCrossingover(CutUnit unit);

	virtual float GetEvaluation();
	void Evaluate();

	static std::string PrintFigures();

	virtual std::string GetPositions();

	/*static void fillFigures(std::list<Figure2D> newFigures) {
		while (newFigures.front) {

		}
	}*/
	void Delete();
	virtual BaseUnit * Copy();
};