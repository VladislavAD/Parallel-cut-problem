#pragma once
#include "DummyPopulation.h"

int main() {
	DummyPopulation population = DummyPopulation();
	while (population.Step()) {}
	return 0;
}