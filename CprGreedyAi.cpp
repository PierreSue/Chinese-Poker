#include "CprGreedyAi.h"

CprGreedyAi::CprGreedyAi() {
}

CprGreedyAi::~CprGreedyAi() {
}

void CprGreedyAi::playerStrategy() {
	// Note: It's just an example showing you how to create Cpr*Ai 
	// by implementing Cpr*Ai::playerStrategy
	CprHand hand = CprHandMaster::GetBestHand(_collection);
	_collection.settingHand(2, hand.getCards());
	CprHand hand2 = CprHandMaster::GetBestHand(_collection);
	_collection.settingHand(1, hand2.getCards());
}
