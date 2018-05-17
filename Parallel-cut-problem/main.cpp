#pragma once
#include "DefaultPopulation.h"
#include "CutSettingsHolder.h"
#include "mpi.h"

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::cout << "The number of processes: " << size << " my number is " << rank << std::endl;
	CutSettingsHolder * settingsHolder = new CutSettingsHolder();
	settingsHolder->unitsSize = 30;
	settingsHolder->newMutateUnits = 3;
	settingsHolder->newCrossingoverUnits = 0;
	for (int i = 0; i < 4; i++)
	{
		settingsHolder->figures.push_back(new Figure2D());
	}
	DefaultPopulation population = DefaultPopulation(settingsHolder);
	while (population.Step()) {}
	MPI_Finalize();
	std::cin >> rank;
	return 0;
}