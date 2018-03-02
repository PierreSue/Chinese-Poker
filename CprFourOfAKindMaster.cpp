/****************************************************************************
Author     [ Iced ]
****************************************************************************/
#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
void CprFourOfAKindMaster::f(int a, const CardList &avail, CardList &tmp, HandList &res){
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
	if(h1.at(0).rankA() > h2.at(0).rankA())
	  return false;
	if(h1.at(0).rankA() == h2.at(0).rankA() && h1.at(4).rankA() > h2.at(4).rankA())
	  return false;
	if(h1.at(0).rankA() == h2.at(0).rankA() && h1.at(4).rankA() == h2.at(4).rankA())
	    if(h1.at(4).suit() < h2.at(4).suit())
		    return false;
	    
	return true;
}

bool CprFourOfAKindMaster::compareDeeply(const CprHand& x1, const CprHand& x2) {
	CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	if(h1.at(0).rankA() > h2.at(0).rankA())
	  return false;
	if(h1.at(0).rankA() == h2.at(0).rankA() && h1.at(4).rankA() > h2.at(4).rankA())
	  return false;
	return true;
}
bool CprFourOfAKindMaster::determineMe(CprHand& hand) {
    CardList tmp;
	if(hand._cards.size() != 5) return false;
	hand.computeACR();
	for(int x = 2; x < 15; x++)
	    if(hand._ACR[x].size() == 4){
	    	for(int y = 0; y < 4; y++)
	    	    tmp.push_back(hand._ACR[x].at(y));
	    	break;
	    }
	if(tmp.empty()) return false;
	for(int x = 2; x < 15; x++)
	    if(hand._ACR[x].size() == 1){
	    	tmp.push_back(hand._ACR[x].at(0));
	    	hand._cards = tmp;
	    	return true;
	    }
}
void CprFourOfAKindMaster::computetmp(const CprCollection& col){
	CardList tmp;
	tmpres.clear();
	f(0, col._availCards, tmp, tmpres);
	std::sort(tmpres.begin(), tmpres.end(), compare);
	return;
}
bool CprFourOfAKindMaster::containsMe(const CprCollection& col, CprHand& res) {
    computetmp(col);
    if(tmpres.empty()) return false;
    flag = tmpres.size() - 1;
    res = tmpres.at(flag);
    flag--;
    return true;
}

bool CprFourOfAKindMaster::containsMeUnder(CprHand& res, const CprHand& upperHand) {
   for(int x = tmpres.size() - 2; x > 0; x--)
       if(compare(upperHand, tmpres.at(x)))
           if(compare(tmpres.at(x), upperHand)){
               res = tmpres.at(x);
               return true;
           }
   return false;
}
