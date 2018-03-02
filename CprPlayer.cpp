/****************************************************************************
  FileName   [ CprPlayer.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprPlayer member functions ]
****************************************************************************/

#include "CprPlayer.h"
#include "CprHandMaster.h"
#include "CprHand.h"

CprPlayer::CprPlayer() {
}

CprPlayer::~CprPlayer() {
}

void CprPlayer::strategy() {
	// Note: please define CprCollection::finishSetting such that
	// all hands' type are determined, by calling CprHandMaster::DetermineType
	playerStrategy();
	
	collection().finishSetting();
}

void CprPlayer::setId(string str) {
	_id = str;
}

CprCollection & CprPlayer::collection() {
	return _collection;
}

const CprCollection & CprPlayer::collection() const {
	return _collection;
}

string CprPlayer::getId() const{
    return _id;
}
