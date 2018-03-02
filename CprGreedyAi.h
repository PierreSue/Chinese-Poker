#pragma once
#include "CprAiPlayer.h"
class CprGreedyAi :
	public CprAiPlayer 
{
public:
	CprGreedyAi();
	~CprGreedyAi();
private:
	virtual void playerStrategy();
};

