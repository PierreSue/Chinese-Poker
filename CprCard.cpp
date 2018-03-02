#include "CprCard.h"
#include <sstream>

CprCard::CprCard() 
	: _cardId(-1) {
}

CprCard::CprCard(int id)
	: _cardId(id) {
}

int CprCard::suit() const {
	return (_cardId - 1) / 13 + 1;
}
int CprCard::rank() const {
	return (_cardId - 1) % 13 + 1;
}

int CprCard::rankA() const {
	return (rank() == 1)? 14: rank();
}

bool CprCard::operator<=(const CprCard &c) const {
	if(rankA() <= c.rankA())
	   return true;
	return false;
}
bool CprCard::operator < (const CprCard& card) const {
	return _cardId < card._cardId;
}
bool CprCard::operator == (const CprCard& card) const {
	if(_cardId == card._cardId)
	   return true;
	return false;
}
bool CprCard::operator != (const CprCard& card) const {
	if(_cardId != card._cardId)
	   return true;
	return false;
}

int CprCard::SuitFromChar(const char c) {
	if(c == 'h' || c == 'H')      return 3;
	else if(c == 'c' || c == 'C') return 1;
	else if(c == 'd' || c == 'D') return 2;
	else if(c == 's' || c == 'S') return 4;
	else return -1;
}

int CprCard::RankFromChar(const char c) {
	if(c == 'A' || c == 'a')      return 1;
	else if(c == 'j' || c == 'J') return 11;
	else if(c == 'q' || c == 'Q') return 12;
	else if(c == 'k' || c == 'K') return 13;
	else return -1;
}

void CprCard::setting(int suit, int rank) {
	_cardId = (suit - 1) * 13 + rank;
}

ostream& operator << (ostream& os, const CprCard& c) {
	if(c.rank() == 1)       os << "A";
	else if(c.rank() == 11) os << "J";
	else if(c.rank() == 12) os << "Q";
	else if(c.rank() == 13) os << "K";
	else os << c.rank();
	
	if(c.suit() == 1)      os << "c";
	else if(c.suit() == 2) os << "d";
	else if(c.suit() == 3) os << "h";
	else if(c.suit() == 4) os << "s";
	return os;
}

istream& operator >> (istream& is, CprCard& c) {
	string str;
	is >> str;
	if (str.empty()) {
		is.clear(ios::failbit);
		return is;
	}

	// 1. parse suit
	int suit = CprCard::SuitFromChar(str.back());
	if (suit == -1) {
		is.clear(ios::failbit);
		return is;
	}
	str.pop_back();

	// 2. parse rank
	istringstream in(str);
	int rank;
	if (in >> rank) {
	} else if (str.size() == 1) {
		rank = CprCard::RankFromChar(str.back());
	} else {
		rank = -1;
	}
	if (rank > 0 && rank <= 13) {
		c.setting(suit, rank);
	} else {
		is.clear(ios::failbit);
	}
	return is;
}
