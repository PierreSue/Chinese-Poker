/****************************************************************************
FileName   [ CprEachMaster.h ]
Author     [ Haowei Luan ]
Synopsis   [ define masters on each card type ]
****************************************************************************/

#pragma once
#include "CprHandMaster.h"

#define CprEachMasterClass(T)												\
class T : public CprHandMaster											\
{																					\
	template <class S> friend class CprEachMasterTest;				\
private:                                                                        \
    void f(int, const CardList &, CardList &, HandList &);		\
    void computetmp(const CprCollection&);                                                \
    HandList tmpres;                                                \
    int flag;                                                       \
	bool compareDeeply(const CprHand&, const CprHand&);			\
	bool determineMe(CprHand&);											\
	bool containsMe(const CprCollection&, CprHand&);				\
	bool containsMeUnder(CprHand&, const CprHand& ); \
}																					\


CprEachMasterClass(CprStraightFlushMaster);
CprEachMasterClass(CprFourOfAKindMaster);
CprEachMasterClass(CprFullHouseMaster);
CprEachMasterClass(CprFlushMaster);
CprEachMasterClass(CprStraightMaster);
CprEachMasterClass(CprThreeOfAKindMaster);
CprEachMasterClass(CprTwoPairMaster);
CprEachMasterClass(CprOnePairMaster);
CprEachMasterClass(CprHighCardMaster);
