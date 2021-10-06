#include "Action.h"
#include<iostream>

Action::Action()
  : _i(0), _j(0), _P(EMPTY), _d(NONE)
{}

Action::Action(int i, int j, PLAYER P)
  : _i(i), _j(j), _P(P), _d(NONE) 
{}

Action::Action(int i, int j, PLAYER P, PUSH_DIRECTION d)
: _i(i), _j(j), _P(P), _d(d) 
{}

bool Action::operator<(const Action& r) const
{
  if(_i<r._i)
    return true;
  if(_i>r._i)
    return false;
  if(_j<r._j)
    return true;
  if(_j>r._j)
    return false;
  if(_d<r._d)
    return true;
  
  return false;
}

void Action::dump() const
{
  std::cout<<_i<<","<<_j<<"-"<<_P<<":"<<_d<<std::endl;
}
