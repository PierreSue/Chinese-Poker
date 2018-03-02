/****************************************************************************
Author     [ Iced ]
****************************************************************************/
#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
void CprThreeOfAKindMaster::f(int a, const CardList &avail, CardList &tmp, HandList &res){
	if(tmp.size() == 5){
		CprHand x(tmp);
		if(determineMe(x))
	        res.push_back(x);
		return;
	}
	for(int x = a; x < avail.size(); x++){
		tmp.push_back(avail.at(x));
		f(x + 1, avail, tmp, res);
		tmp.pop_back();
	}
	return;
}
static bool compare(const CprHand& x1, const CprHand& x2) {
	CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	for(int x = 0; x < 5; x++){
		if(h1.size() == x || h2.size() == x) break;
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() == h2.at(x).rankA())
	        continue;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        return true;
	}
	for(int x = 0; x < 5; x++){
		if(h1.at(x).suit() < h2.at(x).suit())
		    return false;
	}
	return true;
}

bool CprThreeOfAKindMaster::compareDeeply(const CprHand& x1, const CprHand& x2) {
	CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	for(int x = 0; x < 5; x++){
		if(h1.size() == x || h2.size() == x) break;
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() == h2.at(x).rankA())
	        continue;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        return true;
	}
	return true;
}
bool CprThreeOfAKindMaster::determineMe(CprHand& hand) {
    CardList tmp;
	hand.computeACR();
	if(hand._cards.size() == 3){
	    for(int x = 2; x < 15; x++)
	        if(hand._ACR[x].size() == 3){
	            hand._cards = hand._ACR[x];
                return true;
			}
	    return false;
    }
	for(int x = 2; x < 15; x++)
	    if(hand._ACR[x].size() == 3){
	    	for(int y = 0; y < hand._ACR[x].size(); y++)
	    	    tmp.push_back(hand._ACR[x].at(y));
	    	break;
	    }
	if(tmp.empty()) return false;
	for(int x = 14; x > 1; x--){
	    if(hand._ACR[x].size() == 2)
	        return false;
	    if(hand._ACR[x].size() == 1){
	    	for(int y = 0; y < hand._ACR[x].size(); y++)
	    	    tmp.push_back(hand._ACR[x].at(y));
	    }
    }
	hand._cards = tmp;
	return true;
}
void CprThreeOfAKindMaster::computetmp(const CprCollection& col){
	CardList tmp;
	tmpres.clear();
	f(0, col._availCards, tmp, tmpres);
	std::sort(tmpres.begin(), tmpres.end(), compare);
	return;
}
bool CprThreeOfAKindMaster::containsMe(const CprCollection& col, CprHand& res) {
    computetmp(col);
    if(tmpres.empty()) return false;
    flag = tmpres.size() - 1;
    res = tmpres.at(flag);
    flag--;
    return true;
}

bool CprThreeOfAKindMaster::containsMeUnder(CprHand& res, const CprHand& upperHand) {
   for(int x = tmpres.size() - 2; x > 0; x--)
       if(compare(upperHand, tmpres.at(x)))
           if(compare(tmpres.at(x), upperHand)){
               res = tmpres.at(x);
               return true;
           }
   return false;
}
