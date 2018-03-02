/****************************************************************************
  FileName   [ CprHand.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprHand member functions ]
****************************************************************************/

#include "CprHand.h"
#include "CprHandMaster.h"
static bool bysuit(CprCard a, CprCard b){
	return a.suit() < b.suit();
}
CprHand::CprHand()
	: _type(HTUndefined) {}

CprHand::CprHand(const CardList & cards)
	: _cards(cards), _type(HTUndefined) {}

CprHand::CprHand(const CardList & cards, HandType type) 
	: _cards(cards), _type(type) {
}

CprHand::~CprHand() {
}

bool CprHand::operator<=(const CprHand & hand) const {
	return CprHandMaster::Compare(*this, hand);
}

bool CprHand::operator>=(const CprHand & hand) const {
	return CprHandMaster::Compare(hand, *this);
}

void CprHand::print() const {
	for (const CprCard& c : _cards) {
		cout << c << " ";
	}
}
HandType CprHand::getType() const {
	return _type;
}

int CprHand::size() const {
	return _cards.size();
}
bool CprHand::empty() const {
	return _cards.size() == 0;
}
CprCard CprHand::getCard(int idx) const {
	return _cards.at(idx);
}
const CardList& CprHand::getCards() const {
	return _cards;
}

const CardList* CprHand::getACR() const{
return _ACR;
}

void CprHand::computeACR(){
	for(int x = 0; x < 15; x++)
	    _ACR[x].clear();
	for(int x = 0; x < _cards.size(); x++)
		_ACR[_cards.at(x).rank()].push_back(_cards.at(x));
	for(int x = 0; x < 15; x++)
	    sort(_ACR[x].begin() , _ACR[x].end() , bysuit);
	_ACR[14] = _ACR[1];
}
