#ifndef GLIXX_BOARD_H
#define GLIXX_BOARD_H

#include "Action.h"
#include "Board.h"

class GlixxBoard
{
 public:
  GlixxBoard();
  void dump() const;
  double payoff() const;
  bool win(PLAYER x) const;
  // THis really means no longuer a move is possible, mostly cause someone win either the 20 tokens
  // are finished
  bool full() const;
  PLAYER& operator()(int i, int j);
  PLAYER operator()(int i, int j) const;
  int width() const;
  int height() const; 
  bool connected(int i, int j) const;
 private:
  Board<PLAYER> _board;
  int blackTokens;
  int whiteTokens;
};

#endif // GLIXX_BOARD_H
