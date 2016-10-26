#pragma once
#include "RankGaussMethod.h"
#include "stdafx.h"

class COneThreadRank : public CRankGaussMethod
{
public:
	COneThreadRank();
	~COneThreadRank();
	int GetRank(Matrix matr) override;
private:
	//std::vector<bool> m_line_used;

};

