/****************************************************************************
  FileName   [ CprStage.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define each phase in a single stage ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCollection.h"

class CprStage
{
public:
	CprStage(vector<CprPlayer*>&, int id);
	~CprStage();
	void start();
    static short int _playerscore[4];
private:
	void dealingPhase();
	void strategyPhase();
	void checkXianggongPhase();
	void comparisonPhase();
	void shootingPhase();
	void printScores() const;

	vector<CprPlayer*>& _players;
	int _stageId;
	
};

