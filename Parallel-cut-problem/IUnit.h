#pragma once

class IUnit {
public:
	virtual int GetGenesCount();
	virtual void MutateGene(int number);
	virtual float GetEvaluation();
	virtual IUnit CrossingoverWithUnit(IUnit unit);
};