/****************************************************************************
Author     [ Iced ]
****************************************************************************/
#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
void CprFlushMaster::f(int a, const CardList &avail, CardList &tmp, HandList &res){
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
static bool card_greater(const CprCard& c1, const CprCard& c2) {
		return c1.rankA() > c2.rankA();
}
static bool compare(const CprHand& x1, const CprHand& x2) {
    CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	for(int x = 0; x < 5; x++){
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() == h2.at(x).rankA())
	        continue;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        return true;
	}
	if(h1.at(0).suit() < h2.at(0).suit())
		return false;
	return true;
}

bool CprFlushMaster::compareDeeply(const CprHand& x1, const CprHand& x2) {
	CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	for(int x = 0; x < 5; x++){
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() == h2.at(x).rankA())
	        continue;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        return true;
	}
	return true;
}
bool CprFlushMaster::determineMe(CprHand& hand) {
    if(hand._cards.size() != 5) return false;
	int fsuit = hand._cards.at(0).suit();
	for(int x = 1; x < 5; x++)
	    if(hand._cards.at(x).suit() != fsuit)
	        return false;
	bool check = true;
	hand.computeACR();
	for(int x = 1; x < 11; x++){
		if(hand._ACR[x].size() == 1){
		    check = true;
		    for(int y = x; y < x + 5; y++){
			    if(hand._ACR[y].size() != 1)
			        check = false;
		    }
		    if(check){
		    	return false;
		    }
	    }
	}
	std::sort(hand._cards.begin(), hand._cards.end(), card_greater);
	return true;
}
void CprFlushMaster::computetmp(const CprCollection& col){
	CardList tmp;
	tmpres.clear();
	f(0, col._availCards, tmp, tmpres);
	std::sort(tmpres.begin(), tmpres.end(), compare);
	return;
}
bool CprFlushMaster::containsMe(const CprCollection& col, CprHand& res) {
    computetmp(col);
    if(tmpres.empty()) return false;
    flag = tmpres.size() - 1;
    res = tmpres.at(flag);
    flag--;
    return true;
}

bool CprFlushMaster::containsMeUnder(CprHand& res, const CprHand& upperHand) {
   for(int x = tmpres.size() - 2; x > 0; x--)
       if(compare(upperHand, tmpres.at(x)))
           if(compare(tmpres.at(x), upperHand)){
               res = tmpres.at(x);
               return true;
           }
   return false;
}
