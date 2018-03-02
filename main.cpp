/****************************************************************************
  FileName   [ main.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ main of Chinese Poker Game ]
****************************************************************************/

#include "CprDef.h"
#include "CprGame.h"
using namespace std;

int main() {
	const int GroupID = 18;
	cout << "This is group " << GroupID << "'s program." << endl;

	int seed = (unsigned)time(0);
	cout << "Using seed " << seed << ".." << endl;
 	srand(seed);
 	
	CprGame game;
	game.setting();
	game.start();
	return 0;
}
