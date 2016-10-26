#include "Matrix.h"


CMatrix::CMatrix()
{
}


CMatrix::~CMatrix()
{
}

void CMatrix::CreateMatrix(unsigned sizeMatrix)
{
	m_matrix.resize(sizeMatrix);

	for (unsigned i = 0; i < sizeMatrix; ++i)
	{
		m_matrix[i].resize(sizeMatrix);
		for (unsigned j = 0; j < sizeMatrix; ++j)
		{
			m_matrix[i][j] = float(rand() % 10);
		}
	}
}

void CMatrix::PrintMatrix()
{
	for (size_t i = 0; i < m_matrix.size(); ++i)
	{
		for (size_t j = 0; j < m_matrix[i].size(); ++j)
		{
			std::cout << m_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix CMatrix::GetMatrix() const
{
	return m_matrix;
}
