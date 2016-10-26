// Lab1version2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <ctime>
#include "Matrix.h"
#include "Difinition.h"

using namespace std;

int GetRang(vector<vector<float>> &matrix)
{
	int rank = MATRIX_SIZE;
	vector<bool> line_used(MATRIX_SIZE);
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		int j;
		for (j = 0; j < MATRIX_SIZE; ++j)
			if (!line_used[j] && abs(matrix[j][i]) > EPS)
				break;
		if (j == MATRIX_SIZE)
			--rank;
		else 
		{
			line_used[j] = true;
			for (int p = i + 1; p< MATRIX_SIZE; ++p)// ���������� �� �����
				matrix[j][p] /= matrix[j][i];
			for (int k = 0; k< MATRIX_SIZE; ++k)
				if (k != j && abs(matrix[k][i]) > EPS)//� ������ 1
					for (int p = i + 1; p< MATRIX_SIZE; ++p)
						matrix[k][p] -= matrix[j][p] * matrix[k][i];
		}
	}
	return rank;
}

vector<vector<float>> GenerateMatrix()
{
	vector<vector<float>> matrix(MATRIX_SIZE);

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j< MATRIX_SIZE; j++)
		{
			int a;
			std::cin >> a;
			matrix[i].push_back(a);
		}
	}
	return matrix;
}

void StartProgrammWithoutMultithreading() 
{
	cout << "======================================" << endl;
	cout << "======= Without Multithreading =======" << endl;
	unsigned int start_time = clock();

	cout << "rang: " << GetRang(GenerateMatrix()) << endl;
	/////////////////////////////////////////////////
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	cout << "time proccess: " << float(search_time) / 1000 << endl << endl << endl;

	cout << "======================================" << endl;
	cout << "======== With Multithreading =========" << endl;
}
void StartProgrammWithMultithreading(const int quantityStream)
{
	unsigned int  start_time = clock();
	Matrix matrix(quantityStream);
	matrix.GetRank();
	unsigned int end_time = clock();
	unsigned int  search_time = end_time - start_time;
	cout << "time proccess: " << float(search_time) / 1000 << endl;
}

//���������� �������, ����������� ����� ��������� ���������� �������� ������������� ����� �������� ( 2 �� ).
//������ ����� ����� ���� ���� ( VC �� ��������� ������ ��� ������ 1�� ). 
//����������, ��� ������� ������ ������� �������� 2000 ������� �� ������ � 1��. ����� ��������� �������� ����� ( ����� ������� ). 
/*int main()
{
	////////////��� ���������������//////////
	StartProgrammWithoutMultithreading();
	////////////C ����������������///////////
	const int quantityStream = 1;
	//StartProgrammWithMultithreading(quantityStream);
	return 0;
}
  */