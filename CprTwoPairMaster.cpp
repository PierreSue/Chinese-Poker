/****************************************************************************
Author     [ Iced ]
****************************************************************************/
#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
void CprTwoPairMaster::f(int a, const CardList &avail, CardList &tmp, HandList &res){
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
		if(h1.at(x).rank() == h2.at(x).rank()) continue;
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        return true;
	}
	for(int x = 0; x < 5; x++){
		if(h1.at(x).suit() < h2.at(x).suit())
		    return false;
	}
	return true;
}

bool CprTwoPairMaster::compareDeeply(const CprHand& x1, const CprHand& x2) {
	CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	for(int x = 0; x < 5; x++){
		if(h1.at(x).rank() == h2.at(x).rank()) continue;
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        break;
	}
	return true;
}
bool CprTwoPairMaster::determineMe(CprHand& hand) {
	if(hand._cards.size() != 5) return false;
	hand.computeACR();
	CardList temp;
	for(int x = 14; x > 1; x--){
	    if(hand._ACR[x].size() == 2){
	        for(int y = 0; y < 2; y++)
	            temp.push_back(hand._ACR[x].at(y));
	    } 
	}
	if(temp.size() != 4) return false;
	for(int y = 14; y > 1; y--){
	    if(hand._ACR[y].size() == 1){
	        temp.push_back(hand._ACR[y].at(0));
	        break;
		}
	}
	hand._cards = temp;
	return true;
}
void CprTwoPairMaster::computetmp(const CprCollection& col){
	CardList tmp;
	tmpres.clear();
	f(0, col._availCards, tmp, tmpres);
	std::sort(tmpres.begin(), tmpres.end(), compare);
	return;
}
bool CprTwoPairMaster::containsMe(const CprCollection& col, CprHand& res) {
    computetmp(col);
    if(tmpres.empty()) return false;
    flag = tmpres.size() - 1;
    res = tmpres.at(flag);
    flag--;
    return true;
}

bool CprTwoPairMaster::containsMeUnder(CprHand& res, const CprHand& upperHand) {
   for(int x = tmpres.size() - 2; x > 0; x--)
       if(compare(upperHand, tmpres.at(x)))
           if(compare(tmpres.at(x), upperHand)){
               res = tmpres.at(x);
               return true;
           }
   return false;
}
