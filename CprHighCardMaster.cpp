/****************************************************************************
Author     [ Iced ]
****************************************************************************/
#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
void CprHighCardMaster::f(int a, const CardList &avail, CardList &tmp, HandList &res){
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
		if(h1.size() == x || h2.size() == x) return true;
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

bool CprHighCardMaster::compareDeeply(const CprHand& x1, const CprHand& x2) {
	CardList h1 = x1.getCards();
	CardList h2 = x2.getCards();
	for(int x = 0; x < 5; x++){
	    if(h1.size() == x || h2.size() == x) break;
		if(h1.at(x).rank() == h2.at(x).rank()) continue;
		if(h1.at(x).rankA() > h2.at(x).rankA())
	        return false;
	    if(h1.at(x).rankA() < h2.at(x).rankA())
	        break;
	}
	return true;
}
bool CprHighCardMaster::determineMe(CprHand& hand) {
	CardList tmp;
	hand.computeACR();
	if(hand._cards.size() == 3){
	    for(int x = 14; x > 1; x--){
	    	if(hand._ACR[x].size() > 1) return false;
	        if(hand._ACR[x].size() == 1){
	            tmp.push_back(hand._ACR[x].at(0));
			}
	    }
	    hand._cards = tmp;
	    return true;
    }
	for(int x = 2; x < 15; x++)
	    if(hand._ACR[x].size() > 1)
	        return false;
	bool check = true;
	int fsuit = hand._cards.at(0).suit();
	for(int x = 1; x < 5; x++){
	    if(hand._cards.at(x).suit() != fsuit)
	        check = false;
	}
	if(check) return false;//check not flush
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
	}//check not straight
	for(int x = 14; x > 1; x--)
	    if(hand._ACR[x].size() == 1)
	    	tmp.push_back(hand._ACR[x].at(0));
	hand._cards = tmp;
	return true;
}
void CprHighCardMaster::computetmp(const CprCollection& col){
	CardList tmp;
	tmpres.clear();
	f(0, col._availCards, tmp, tmpres);
	std::sort(tmpres.begin(), tmpres.end(), compare);
	return;
}
bool CprHighCardMaster::containsMe(const CprCollection& col, CprHand& res) {
    computetmp(col);
    if(tmpres.empty()) return false;
    flag = tmpres.size() - 1;
    res = tmpres.at(flag);
    flag--;
    return true;
}

bool CprHighCardMaster::containsMeUnder(CprHand& res, const CprHand& upperHand) {
   for(int x = tmpres.size() - 2; x > 0; x--)
       if(compare(upperHand, tmpres.at(x)))
           if(compare(tmpres.at(x), upperHand)){
               res = tmpres.at(x);
               return true;
           }
   return false;
}
