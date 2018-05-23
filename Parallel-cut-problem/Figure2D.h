#pragma once
#include <vector>
#include "Point.cpp"
#include "MpiFriendly.h"

class Figure2D : MpiFriendly {
private:

	std::vector<Point> vertexes;
	Point minimum = Point(0, 0);
	Point maximum = Point(0, 0);

	void CalculateMinimumAndMaximum() {
		minimum = vertexes[0];
		maximum = vertexes[0];
		for (int i = 0; i < vertexes.size(); i++) {
			if (vertexes[i].x < minimum.x) {
				minimum.x = vertexes[i].x;
			}
			if (vertexes[i].y < minimum.y) {
				minimum.y = vertexes[i].y;
			}
			if (vertexes[i].x > maximum.x) {
				maximum.x = vertexes[i].x;
			}
			if (vertexes[i].y > maximum.y) {
				maximum.y = vertexes[i].y;
			}
		}
	}

public:

	Figure2D() {
		vertexes = std::vector<Point>();
		vertexes.push_back(Point(1, 1));
		vertexes.push_back(Point(0, 1));
		vertexes.push_back(Point(0, 0));
		vertexes.push_back(Point(1, 0));
		CalculateMinimumAndMaximum();
	};

	Figure2D(std::vector<Point> verticies) {
		this->vertexes = verticies;
		CalculateMinimumAndMaximum();
	}

	~Figure2D() {
		vertexes.clear();
	}

	Figure2D & operator=(const Figure2D& other) {
		this->vertexes = other.vertexes;
		this->maximum = other.maximum;
		this->minimum = other.minimum;
		return *this;
	}

	Figure2D Copy() {
		Figure2D copyFigure = Figure2D(this->vertexes);
		return copyFigure;
	}

	bool FitLine(float lineWidth, float x) {
		if (maximum.x + x < lineWidth && minimum.x + x > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	Point GetFigureMinimum() {
		return minimum;
	}

	Point GetFigureMaximum() {
		return maximum;
	}

	static bool IsFiguresIntersecting(Figure2D first, Point firstPosition, Figure2D second, Point secondPosition) {
		bool intersects = false;
		for (int i = 0; i < first.vertexes.size() + 1; i++) {
			for (int j = 0; j < second.vertexes.size() + 1; j++)
			{
				Point startPointFirstLine, endPointFirstLine, startPointSecondLine, endPointSecondLine;

				int startVertexNumber1 = i % first.vertexes.size();
				int endVertexNumber1 = (i + 1) % first.vertexes.size();
				int startVertexNumber2 = j % second.vertexes.size();
				int endVertexNumber2 = (j + 1) % second.vertexes.size();

				startPointFirstLine = Point(first.vertexes[startVertexNumber1]);
				startPointFirstLine.Add(firstPosition);
				endPointFirstLine = Point(first.vertexes[endVertexNumber1]);
				endPointFirstLine.Add(firstPosition);
				startPointSecondLine = Point(second.vertexes[startVertexNumber2]);
				startPointSecondLine.Add(secondPosition);
				endPointSecondLine = Point(second.vertexes[endVertexNumber2]);
				endPointSecondLine.Add(secondPosition);

				float check = (firstPosition.x - secondPosition.x) * (firstPosition.x - secondPosition.x) +
					(firstPosition.y - secondPosition.y) * (firstPosition.y - secondPosition.y);

				if (Point::LineIntersection(startPointFirstLine, endPointFirstLine, startPointSecondLine, endPointSecondLine)) {
					intersects = true;
				}
			}
		}
		return intersects;
	}

	void RotateFigure(float angleDegree) {
		for (int i = 0; i < vertexes.size(); i++)
		{
			vertexes[i].Rotate(angleDegree);
		}
		CalculateMinimumAndMaximum();
	}

	void MpiSend(int destination, MPI_Comm communicator) {
		float * pointXBuffer = new float[vertexes.size()];
		float * pointYBuffer = new float[vertexes.size()];
		for (int i = 0; i < vertexes.size(); i++) {
			pointXBuffer[i] = vertexes[i].x;
			pointYBuffer[i] = vertexes[i].y;
		}
		int vertexesCount = vertexes.size();
		MPI_Send(&vertexesCount, 1, MPI_INT, destination, 0, communicator);
		MPI_Send(pointXBuffer, vertexes.size(), MPI_FLOAT, destination, 1, communicator);
		MPI_Send(pointYBuffer, vertexes.size(), MPI_FLOAT, destination, 2, communicator);
		delete[] pointXBuffer;
		delete[] pointYBuffer;
	}

	void MpiReceive(int source, MPI_Comm communicator) {
		MPI_Status * status;
		int vertexesCount = 0;
		MPI_Recv(&vertexesCount, 1, MPI_INT, source, 0, communicator, status);
		vertexes = std::vector<Point>(vertexesCount);
		float * pointXBuffer = new float[vertexes.size()];
		float * pointYBuffer = new float[vertexes.size()];
		MPI_Recv(pointXBuffer, vertexesCount, MPI_FLOAT, source, 1, communicator, status);
		MPI_Recv(pointYBuffer, vertexesCount, MPI_FLOAT, source, 2, communicator, status);
		for (int i = 0; i < vertexes.size(); i++) {
			vertexes[i].x = pointXBuffer[i];
			vertexes[i].y = pointYBuffer[i];
		}
		delete[] pointXBuffer;
		delete[] pointYBuffer;
		CalculateMinimumAndMaximum();
	}
};