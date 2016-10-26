#pragma once
#include "stdafx.h"

typedef std::vector<std::vector<float>> Matrix;


class CMatrix
{
public:
	CMatrix();
	~CMatrix();
	void CreateMatrix(unsigned sizeMatrix);
	void PrintMatrix();
	Matrix GetMatrix() const;
private:
	Matrix m_matrix;
};

