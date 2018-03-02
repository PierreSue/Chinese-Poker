/****************************************************************************
Author     [ Iced ]
****************************************************************************/
#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
void CprFullHouseMaster::f(int a, const CardList &avail, CardList &tmp, HandList &res){
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
	if(h1.at(0).rankA() == h2.at(0).rankA() && h1.at(3).rankA() > h2.at(3).rankA())
	  return false;
	if(h1.at(0).rankA() == h2.at(0).rankA() && h1.at(3).rankA() == h2.at(3).rankA())
	    for(int x = 0; x < 5; x++){
		    if(h1.at(x).suit() < h2.at(x).suit())
		        return false;
	    }
	return true;
}
bool CprFullHouseMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	if(h1._cards.at(0).rankA() > h2._cards.at(0).rankA())
	  return false;
	if(h1._cards.at(0).rankA() == h2._cards.at(0).rankA() && h1._cards.at(3).rankA() > h2._cards.at(3).rankA())
	  return false;
	return true;
}
bool CprFullHouseMaster::determineMe(CprHand& hand) {
	if(hand._cards.size() != 5) return false;
	CardList tmp;
	hand.computeACR();
	for(int x = 2; x < 15; x++)
	    if(hand._ACR[x].size() == 3){
	    	for(int y = 0; y < 3; y++)
	    	    tmp.push_back(hand._ACR[x].at(y));
	    	break;
	    }
	if(tmp.empty()) return false;
	for(int x = 2; x < 15; x++)
	    if(hand._ACR[x].size() == 2){
	    	for(int y = 0; y < 2; y++)
	    	    tmp.push_back(hand._ACR[x].at(y));
	    	break;
	    }
	if(tmp.size() != 5) return false;
	hand._cards = tmp;
    return true;
}
void CprFullHouseMaster::computetmp(const CprCollection& col){
	CardList tmp;
	tmpres.clear();
	f(0, col._availCards, tmp, tmpres);
	std::sort(tmpres.begin(), tmpres.end(), compare);
	return;
}
bool CprFullHouseMaster::containsMe(const CprCollection& col, CprHand& res) {
    computetmp(col);
    if(tmpres.empty()) return false;
    flag = tmpres.size() - 1;
    res = tmpres.at(flag);
    flag--;
    return true;
}

bool CprFullHouseMaster::containsMeUnder(CprHand& res, const CprHand& upperHand) {
   for(int x = tmpres.size() - 2; x > 0; x--)
       if(compare(upperHand, tmpres.at(x)))
           if(compare(tmpres.at(x), upperHand)){
               res = tmpres.at(x);
               return true;
           }
   return false;
}
