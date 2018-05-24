#pragma once
#include "DefaultPopulation.h"
#include "CutSettingsHolder.h"
#include "mpi.h"

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//std::cout << "The number of processes: " << size << " my number is " << rank << std::endl;
	if (rank == 0) {
		Figure2D testFigure = Figure2D(std::vector<Point>({ Point(2,2), Point(2,-2), Point(-2,2) }));
		CutSettingsHolder testCutSettingsHolder = CutSettingsHolder();
		testCutSettingsHolder.figures.push_back(new Figure2D(testFigure));
		testCutSettingsHolder.figures.push_back(new Figure2D(testFigure));
		testCutSettingsHolder.lineWidth = 2;
		for (int i = 1; i < size; i++)
		{
			testCutSettingsHolder.MpiSend(i, MPI_COMM_WORLD);
		}
	}
	else {
		CutSettingsHolder testCutSettingsHolder = CutSettingsHolder();
		testCutSettingsHolder.MpiReceive(0, MPI_COMM_WORLD);
		std::cout << "My number is " << rank << std::endl << "figure test" << std::endl << testCutSettingsHolder.figures[0]->PrintFigure();
	}
	MPI_Finalize();
	//std::cin >> rank;
	return 0;
}