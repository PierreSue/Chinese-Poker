/****************************************************************************
  FileName   [ CprHandMaster.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define a master familiar to any card operation ]
****************************************************************************/

#pragma once
#include "CprHandType.h"
#include "CprDef.h"
class CprHandMaster
{
public:
	CprHandMaster();
	~CprHandMaster();
	static bool Compare(const CprHand&, const CprHand&);
	static void DetermineType(CprHand&);
	static CprHand GetBestHand(const CprCollection&);
	static CprHand GetBestHandUnder(const CprCollection&, const CprHand&);
	static CprHandMaster* CreateMaster(HandType);
	static string TranslateType(HandType);

private:
	virtual bool compareDeeply(const CprHand&, const CprHand&) { return false; }
	virtual bool determineMe(CprHand&) { return false; }
	virtual bool containsMe(const CprCollection&, CprHand&) { return false; }
	virtual bool containsMeUnder(CprHand&, const CprHand& ) { return false; }
};

