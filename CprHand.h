/****************************************************************************
  FileName   [ CprHand.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define a 3-card or 5-card Hand ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCard.h"
#include "CprHandType.h"
#include "CprHandMaster.h"
class CprHand
{
	FRIEND_ALL_MASTER;
	friend class CprStage;
public:
	CprHand();
	CprHand(const CardList&);
	CprHand(const CardList&, HandType);
	~CprHand();
	bool operator <= (const CprHand& hand) const;
	bool operator >= (const CprHand& hand) const;
	
	void print() const;
	HandType getType() const;

	/* convenient methods */
	int size() const;
	bool empty() const;
	CprCard getCard(int idx) const;
	const CardList& getCards() const;
	const CardList* getACR() const;
private:
	CardList _cards;
	HandType _type;
	CardList _ACR[15];
	void computeACR();
};

