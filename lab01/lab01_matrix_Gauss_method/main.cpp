// lab0_matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "MultiThreadRank.h"

using namespace std;

int GetRang(std::vector<vector<float>> &matrix)
{
	int rank = 4;
	vector<bool> line_used(4);
	for (int i = 0; i < 4; ++i)
	{
		int j;
		for (j = 0; j < 4; ++j)
			if (!line_used[j] && abs(matrix[j][i]) > EPS)
				break;
		if (j == 4)
			--rank;
		else
		{
			line_used[j] = true;
			for (int p = i + 1; p< 4; ++p)
				matrix[j][p] /= matrix[j][i];
			for (int k = 0; k< 4; ++k)
				if (k != j && abs(matrix[k][i]) > EPS)
					for (int p = i + 1; p< 4; ++p)
						matrix[k][p] -= matrix[j][p] * matrix[k][i];
		}
	}
	return rank;
}


int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		size_t time = clock();
		CMultiThreadRank asad(std::atoi(argv[1]), std::atoi(argv[2]));
		size_t finishTime = clock();
		double processTime = (finishTime - time) / 1000.0;
		std::cout << "Time: " << processTime << std::endl;

	}
	else
	{
		size_t time = clock();
		CMultiThreadRank asad(10, 3);
		size_t finishTime = clock();
		double processTime = (finishTime - time) / 1000.0;
		std::cout << "Time: " << processTime << std::endl;

	}

    return 0;
}

