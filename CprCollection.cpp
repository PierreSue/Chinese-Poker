/****************************************************************************
  FileName   [ CprCollection.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprCollection member functions ]
****************************************************************************/

#include "CprCollection.h"
#include "CprHand.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool byrank(CprCard a, CprCard b){
	return a.rank() < b.rank();
}

bool bysuit(CprCard a, CprCard b){
	return a.suit() < b.suit();
}

CprCollection::CprCollection() 
	:_cards(), _hands(3) {
	// DONE: now _hands.size() is 3
}

CprCollection::~CprCollection() {
}

bool CprCollection::settingHand(int hidx, const CardList& cs) {
	bool b=true;
	if(!_hands[hidx].empty()) return false;
	for( int x = 0; x < cs.size(); x++ ){
		b = true;
		for(int y = 0; y < _availCards.size() && b; y++){
		    if(cs.at(x) == _availCards.at(y)){
		        _availCards.at(y) = _availCards.at(_availCards.size() - 1);
			    _availCards.pop_back();
			    b = false;
			}
		}
		if(b) {
		    for(int z = 0; z < x; z++)
		        _availCards.push_back(cs.at(z));
		    return false;
		}
	}
	_hands[hidx] = cs;
	short int count = 0;
	for(int x = 0; x < 3; x++)
	    if(_hands[x].empty()) count++;
	if(count == 1){
		sort(_availCards.begin() , _availCards.end() , bysuit);
	    sort(_availCards.begin() , _availCards.end() , byrank);
		for(int x = 0; x < 3; x++)
	        if(_hands[x].empty()){
	        	_hands[x] = _availCards;
	        	_availCards.clear();
	        }
	}
	computeACR();
	return true;
}

void CprCollection::resetAllHands() {
	_hands.clear();
	_hands.resize(3);
	_availCards = _cards;
	computeACR();
}

void CprCollection::printByRank() const {
	CardList a = _availCards;
	sort(a.begin() , a.end() , bysuit);
	sort(a.begin() , a.end() , byrank);
	for(int x = 0; x < a.size(); x++)
	cout << a.at(x) << " ";
	cout<<endl;
}

void CprCollection::printBySuit() const {
	CardList a=_availCards;
	sort(a.begin() , a.end() , byrank);
	sort(a.begin() , a.end() , bysuit);
	for(int x = 0; x < a.size(); x++)
	cout << a.at(x) << " ";
	cout<<endl;
}

void CprCollection::showCollection() const {
	// DONE: do not modify me
	if (!_availCards.empty()) {
		cout << "Available cards: " << endl << "  ";
		printByRank();
	}
	for (unsigned i = 0; i < _hands.size(); ++i) {
		const CprHand& hand = _hands.at(i);
		cout << "hand " << (i + 1) << ": ";
		hand.print();
		cout << endl;
	}
}

bool CprCollection::isValidSet() const {
	if(_hands.at(0).empty() || _hands.at(1).empty() || _hands.at(2).empty())
	return false;
	return true;
}

bool CprCollection::isCardAvailable(const CprCard& c) const {
	for(int x = 0; x < 13; x++)
	    if(_cards.at(x) == c)
	    return true;
	return false;
}

const CardList* CprCollection::getACR() const{
return _ACR;
}

void CprCollection::computeACR(){
	for(int x = 0; x < 15; x++)
	    _ACR[x].clear();
	for(int x = 0; x < _availCards.size(); x++)
		_ACR[_availCards.at(x).rank()].push_back(_availCards.at(x));
	for(int x = 0; x < 15; x++)
	    sort(_ACR[x].begin() , _ACR[x].end() , bysuit);
	_ACR[14] = _ACR[1];
}

CardList CprCollection::getAvailableCards() const{
    return _availCards;
}

void CprCollection::finishSetting(){
	CprHandMaster::DetermineType(_hands.at(0));
	CprHandMaster::DetermineType(_hands[1]);
	CprHandMaster::DetermineType(_hands[2]);
}
