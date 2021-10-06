#ifndef GLIXX_STATE_H
#define GLIXX_STATE_H

#include "GlixxBoard.h"
#include <set>

class State
{
 public:
  State(GlixxBoard b);
  PLAYER turn() const;
  State result(const Action& a) const;
  bool legal(const Action& a) const;
  bool legal(int i, int j) const;
  bool legal(int i, int j, PUSH_DIRECTION d) const;
  std::set<Action> actions() const;
  bool terminal() const;
  double utility() const;
  double max_value() const;
  double min_value() const;
  Action minimax_decision() const;
  void dump() const;
  bool win(PLAYER p) const;

 private:
  GlixxBoard _board;
  int _tokens;
  PLAYER playerinTurn;
};

#endif // GLIXX_STATE_H
