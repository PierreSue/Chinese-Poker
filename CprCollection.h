/****************************************************************************
  FileName   [ CprCollection.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define cards held by players ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprHand.h"
class CprCollection
{
	FRIEND_ALL_MASTER;
	friend class CprDealer;
	friend class CprStage;
	friend class CprCustomAi;
public:
	CprCollection();
	~CprCollection();

	/* setting methods */
	bool settingHand(int, const CardList&);
	void resetAllHands();

	/* other methods */
	void printByRank() const;
	void printBySuit() const;
	void showCollection() const;
	bool isValidSet() const;
    const CardList* getACR() const;
    CardList getAvailableCards() const;
    void finishSetting();
private:
	CardList _cards;
		// The given 13 cards
	CardList _availCards;
		// A subset of _cards, 
		// recording those which haven't been set to any hand
	HandList _hands;
		// A CprHand vector with size 3
		// _hands[0]: 1st hand, _hands[1]: 2nd hand, _hands[2]: 3rd hand
	bool isCardAvailable(const CprCard&) const;
	CardList _ACR[15];
	void computeACR();
};

