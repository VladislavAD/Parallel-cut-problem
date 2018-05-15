#pragma once

class IUnit {
public:
	IUnit() {};
	~IUnit() {};
	virtual int GetGenesCount() { return 0; }
	virtual void MutateGene(int number) {}
	virtual float GetEvaluation() { return 0; }
	virtual IUnit * CrossingoverWithUnit(IUnit * unit) { return unit; }
	virtual void * ExtractGene(int geneNumber) { return; }
};