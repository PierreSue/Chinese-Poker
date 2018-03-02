/****************************************************************************
  FileName   [ CprHumanPlayer.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define user interface for human players ]
****************************************************************************/

#pragma once
#include "CprPlayer.h"
class CprHumanPlayer :
	public CprPlayer
{
	friend class CprW13Test;
public:
	CprHumanPlayer();
	~CprHumanPlayer();
private:
	void playerStrategy();
	void showHelps();
	void readCommands();
	bool parseOneCmd();
	void parseHandCmd();
	bool checkValidStrategy();
	string _command;
};

