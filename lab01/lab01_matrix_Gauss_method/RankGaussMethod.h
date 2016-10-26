#pragma once
#include "Matrix.h"
#include "stdafx.h"

const double EPS = 1E-9;

class CRankGaussMethod
{
public:
	CRankGaussMethod();
	~CRankGaussMethod();
	
	virtual int GetRank(Matrix matr) = 0;

protected: 
	int m_rank = 0;
};

