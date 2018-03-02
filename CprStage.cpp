/****************************************************************************
  FileName   [ CprStage.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement each phase in a single stage ]
****************************************************************************/

#include "CprStage.h"
#include "CprPlayer.h"
#include "CprHand.h"
#include "CprDealer.h"
short int CprStage::_playerscore[4] = {0};
CprStage::CprStage(vector<CprPlayer *>& players, int id)
	: _players(players), _stageId(id) {
}

CprStage::~CprStage() {
}

void CprStage::start() {
	cout << "== Stage " << _stageId << " start!" << endl;
	dealingPhase();
	strategyPhase();
	checkXianggongPhase();
	comparisonPhase();
	shootingPhase();
	printScores();
	cout << "== Stage " << _stageId << " end" << endl << endl;
	cout << endl;
}

void CprStage::dealingPhase() {
	// TODO: call CprDealer to distribute cards to players
    CprDealer dealer;
	dealer.deal(_players);
}

void CprStage::strategyPhase() {
	// DONE
	for (unsigned i = 0; i < _players.size(); ++i) {
		CprPlayer *py = _players.at(i);
		py->_collection.resetAllHands();
		py->strategy();
	}
}

void CprStage::checkXianggongPhase() {
  for (unsigned i = 0; i < _players.size(); ++i) {
	if(_players.at(i)->collection()._hands[0] <= _players.at(i)->collection()._hands[1]){
		if(_players.at(i)->collection()._hands[1] <= _players.at(i)->collection()._hands[2]){
			continue;
		}
	}
	_players.at(i)->collection()._hands[0]._type = HTXianggong;
	_players.at(i)->collection()._hands[1]._type = HTXianggong;
	_players.at(i)->collection()._hands[2]._type = HTXianggong;
  }
	// TODO: if a player's collection is detected as Xianggong,
	// set all his/her hands' type as HTXianggong
}

void CprStage::comparisonPhase() {
	// TODO: compare players' hands and print them with tricks num
	int tempscore[4]={0};
	for (int ridx = 1; ridx <= 3; ++ridx) {
		cout << "= Round " << ridx << ".." << endl;
		for(int x = 0; x < 4; x++){
			for(int y = 0; y < 4; y++){
				if(y == x) continue;
				if(_players.at(x)->collection()._hands[ridx - 1] <= _players.at(y)->collection()._hands[ridx - 1]){
					if(_players.at(x)->collection()._hands[ridx - 1] >= _players.at(y)->collection()._hands[ridx - 1])
					    continue;
					else tempscore[x]--;
				}
				else tempscore[x]++;
			}
		}
		for(int x = 0; x < 4; x++){
		    cout << _players.at(x)->getId() << "   : ";
			_players.at(x)->collection()._hands[ridx - 1].print();
			cout << "  <" << CprHandMaster::TranslateType(_players.at(x)->collection()._hands[ridx - 1].getType());
			cout << "> : " ;
			if(tempscore[x] > 0) cout<<'+';
			cout << tempscore[x] <<endl;
	    }
	    for(int x = 0; x < 4; x++){
	    	_playerscore[x] += tempscore[x];
	    	tempscore[x] = 0;
	    }
	}
}

void CprStage::shootingPhase() {
	// TODO: check if someone shoots another
	cout << "= Check shooting.." << endl;
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			if(y == x) continue;
			if(!(_players.at(x)->collection()._hands[0] <= _players.at(y)->collection()._hands[0]))
			    if(!(_players.at(x)->collection()._hands[1] <= _players.at(y)->collection()._hands[1]))
			        if(!(_players.at(x)->collection()._hands[2] <= _players.at(y)->collection()._hands[2])){
			        	_playerscore[x] += 3;
			        	_playerscore[y] -= 3;
			        	cout << _players.at(x)->getId();
			        	cout << " <+3> shoots ";
			        	cout << _players.at(y)->getId();
			        	cout << " <-3>\n";
			        }
			            
			    
	    }
	}
}


void CprStage::printScores() const {
	// TODO: print all players' scores
	cout << "== Stage " << _stageId << " scores.." << endl;
	int rank[4]={0};
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			if(y == x) continue;
			if(_playerscore[x] < _playerscore[y])
			    rank[x]++;
	    }
	}
	for(int x = 0; x < 4; x++){
	    cout << _players.at(x)->getId() << "   :";
	    cout << setw(5) << _playerscore[x];
	    if(rank[x] == 0) cout<< " <1st>\n";
	    else if(rank[x] == 1) cout<< " <2nd>\n";
	    else if(rank[x] == 2) cout<< " <3rd>\n";
	    else cout<< " <4th>\n";
	}
	
	
}

