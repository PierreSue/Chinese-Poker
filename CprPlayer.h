/****************************************************************************
  FileName   [ CprPlayer.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define CprPlayer class ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCollection.h"

class CprPlayer
{
	friend CprDealer;
	friend class CprStage;
public:
	CprPlayer();
	~CprPlayer();
	void strategy();
	void setId(string);
	string getId() const;
protected:
	CprCollection _collection;
	CprCollection& collection();
	const CprCollection& collection() const;
	
private:
	string _id;
	virtual void playerStrategy() = 0;
};

