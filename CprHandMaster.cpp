/****************************************************************************
  FileName   [ CprHandMaster.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprHandMaster member functions ]
****************************************************************************/

#include "CprHandMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
#include "CprEachMaster.h"

CprHandMaster::CprHandMaster() {
}

CprHandMaster::~CprHandMaster() {
}

bool CprHandMaster::Compare(const CprHand& h1, const CprHand& h2) {
	// TODO (unfinished): return true if h1 is not stronger than h2
	assert(h1._type != HTUndefined && h2._type != HTUndefined);
	if (h1.getType() != h2.getType()) {
		return h1._type < h2._type;
	} else if (h1.getType() == HTXianggong) {
		return true;
	} else {
		CprHandMaster* ms;
		HandType type = HandType(h1.getType());
		ms = CreateMaster(type);
		bool com = ms->compareDeeply(h1, h2);
		delete ms;
		return com;
		// TODO: finish the case when h1._type == h2._type
	}
}

void CprHandMaster::DetermineType(CprHand& hand) {
	// DONE
	CprHandMaster* ms;
	for (int i = HTHighestType; i >= HTLowestType; --i) {
		HandType type = HandType(i);
		ms = CreateMaster(type);
		if (ms->determineMe(hand)) {
			hand._type = type;
			delete ms;
			return;
		}
		delete ms;
	}
	assert(false);
}

CprHand CprHandMaster::GetBestHand(const CprCollection& col) {
	// TODO: Find the best possible hand in col
	CprHand hand;
	CprHandMaster* ms;
	if(col.getAvailableCards().size() == 13){
		for (int i = HTHighestType; i >= HTTwoPair; --i) {
		HandType type = HandType(i);
		ms = CreateMaster(type);
		if (ms->containsMe(col, hand)) {
			delete ms;
			return hand;
		}
		delete ms;
	    }
	}
	else
	for (int i = HTHighestType; i >= HTLowestType; --i) {
		HandType type = HandType(i);
		ms = CreateMaster(type);
		if (ms->containsMe(col, hand)) {
			delete ms;
			return hand;
		}
		delete ms;
	}
}

CprHand CprHandMaster::GetBestHandUnder(const CprCollection& col, const CprHand& upperHand) {
	// [Optional] Find the best hand weaker than upperHand in col
	
	//fatal error::pointer
	CprHand hand;
	CprHandMaster* ms;
	HandType type = HandType(upperHand.getType());
	ms = CreateMaster(type);
	ms->containsMe(col, hand);//hand
	if (ms->containsMeUnder(hand, upperHand)) {
			delete ms;
			return hand;
	}
	else delete ms;
	for (int i = upperHand.getType() - 1; i >= HTLowestType; --i) {
		HandType type = HandType(i);
		ms = CreateMaster(type);
		if (ms->containsMe(col, hand)) {
			delete ms;
			return hand;
		}
		delete ms;
	}
	CprHand null;
	return null;
}

CprHandMaster * CprHandMaster::CreateMaster(HandType type) {
	CprHandMaster* ms = 0;
	switch (type) {
	case HTStraightFlush:
		ms = new CprStraightFlushMaster();
		break;
	case HTFourOfAKind:
		ms = new CprFourOfAKindMaster();
		break;
	case HTFullHouse:
		ms = new CprFullHouseMaster();
		break;
	case HTFlush:
		ms = new CprFlushMaster();
		break;
	case HTStraight:
		ms = new CprStraightMaster();
		break;
	case HTThreeOfAKind:
		ms = new CprThreeOfAKindMaster();
		break;
	case HTTwoPair:
		ms = new CprTwoPairMaster();
		break;
	case HTOnePair:
		ms = new CprOnePairMaster();
		break;
	case HTHighCard:
		ms = new CprHighCardMaster();
		break;
	case HTXianggong:
	default:
		assert(false);
		break;
	}
	return ms;
}

string CprHandMaster::TranslateType(HandType type) {
	switch (type) {
	case HTStraightFlush:
		return "StraightFlush";
	case HTFourOfAKind:
		return "FourOfAKind";
	case HTFullHouse:
		return "FullHouse";
	case HTFlush:
		return "Flush";
	case HTStraight:
		return "Straight";
	case HTThreeOfAKind:
		return "ThreeOfAKind";
	case HTTwoPair:
		return "TwoPair";
	case HTOnePair:
		return "OnePair";
	case HTHighCard:
		return "HighCard";
	case HTXianggong:
		return "Xianggong";
	default:
		assert(false);
		return string();
	}
}
