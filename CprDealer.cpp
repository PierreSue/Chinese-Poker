#include "CprStage.h"
#include "CprPlayer.h"
#include "CprHand.h"
#include "CprDealer.h"
#include <string.h>
	void CprDealer::deal(vector<CprPlayer*>& player){
		CardList cards[4];
		int x = 0;
		memset( b , false , 52 );
		while(x < 52){
		    a = rand() % 52;
		    if(!b[a]){
		      cards[x / 13].push_back(CprCard(a + 1));
		      b[a]=true;
		      x++;
		    }
	    }

	    for(int z = 0; z < 4; z++){
	    	player.at(z)->_collection._cards.clear();
	        player.at(z)->_collection._availCards.clear();
		    player.at(z)->_collection._cards = cards[z];
	        player.at(z)->_collection._availCards = cards[z];
	    }
		
	}


