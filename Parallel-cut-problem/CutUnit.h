#pragma once
#include "BaseUnit.h"
#include "CutGene.h"
#include "CutStrip.h"
#include "Figure2D.h"
#include <list>
#include <algorithm>
#include <vector>

class CutUnit : public BaseUnit {
private:
	float evaluation = 0;
	static std::vector<Figure2D*> figures;
	static float lineWidth;
	const float horizontalMutation = 1.0f;

	CutGene * genes = NULL;

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
	BaseUnit CrossingoverWithUnit(BaseUnit unit);

	/// <summary>
	/// Костыльсинговер, берем ген из особи в параметре и создаём новый ген себя с геном второй особи
	/// </summary>
	CutUnit DummyCrossingover(CutUnit unit);

	virtual float GetEvaluation();
	void Evaluate();
	void Delete();
	virtual BaseUnit * Copy();
};