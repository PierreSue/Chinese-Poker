#include "CprCustomAi.h"

CprCustomAi::CprCustomAi() {
}

CprCustomAi::~CprCustomAi() {
}

void CprCustomAi::playerStrategy() {
	// Note: It's just an example showing you how to create Cpr*Ai 
	// by implementing Cpr*Ai::playerStrategy
	CprCollection tmpcol, bestcol;
	bestcol = _collection;
	CprHand hand = CprHandMaster::GetBestHand(bestcol);
	bestcol.settingHand(2, hand.getCards());
	CprHand hand2 = CprHandMaster::GetBestHand(bestcol);
	bestcol.settingHand(1, hand2.getCards());
	while(true){
		tmpcol = _collection;
		hand = CprHandMaster::GetBestHandUnder(tmpcol, hand);
		if(hand.getCards().size() == 0) break;
	    tmpcol.settingHand(2, hand.getCards());
	    hand2 = CprHandMaster::GetBestHandUnder(tmpcol, hand2);
	    if(hand2.getCards().size() == 0) break;
	    tmpcol.settingHand(1, hand2.getCards());
	    int tempscore =0;
		for(int ridx = 1; ridx < 4; ridx++){
				if(tmpcol._hands[ridx - 1] <=bestcol._hands[ridx - 1]){
					if(tmpcol._hands[ridx - 1] >= bestcol._hands[ridx - 1])
					    continue;
					else tempscore--;
				}
				else tempscore++;
		}
		if(tempscore > 0)
			bestcol = tmpcol;
	}
	
	
	
	_collection = bestcol;
}
