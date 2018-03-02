#pragma once
#include "CprAiPlayer.h"
class CprCustomAi :
	public CprAiPlayer 
{
public:
	CprCustomAi();
	~CprCustomAi();
private:
	virtual void playerStrategy();
};

