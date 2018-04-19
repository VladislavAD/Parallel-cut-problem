#pragma once

class IUnit {
public:
	IUnit() {};
	~IUnit() {};
	virtual int GetGenesCount() = 0;
	virtual void MutateGene(int number) = 0;
	virtual float GetEvaluation() = 0;
	virtual IUnit * CrossingoverWithUnit(IUnit * unit) = 0;
	virtual void * ExtractGene(int geneNumber) = 0;
};