/****************************************************************************
  FileName   [ CprCard.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define a single card ]
****************************************************************************/

#pragma once   // a substitute for:  #ifndef CPR_CARD_H  #define CPR_CARD_H  #endif
#include <iostream>
using namespace std;

class CprCard
{
   friend ostream& operator << (ostream&, const CprCard&);
   friend istream& operator >> (istream&, CprCard&);
public:
   CprCard();
   CprCard(int id);
   int suit() const;
   int rank() const;
   int rankA() const;
   bool operator <= (const CprCard&) const;
   bool operator <  (const CprCard&) const;
   bool operator == (const CprCard&) const;
   bool operator != (const CprCard&) const;
private:
   static int SuitFromChar(const char);
   static int RankFromChar(const char);
   void setting(int suit, int rank);
   short int _cardId;
      /* card index from 1 to 52:
         1  - 13: Ac - Kc
         14 - 26: Ad - Kd
         27 - 39: Ah - Kh
         40 - 52: As - Ks 
      */
};
