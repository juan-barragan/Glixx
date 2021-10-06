#include "GlixxBoard.h"

GlixxBoard::GlixxBoard()
  : _board(Board<PLAYER>(6,6)), whiteTokens(10), blackTokens(10)
{
  for(int i=0; i<_board.height(); ++i)
    for(int j=0; j<_board.width(); ++j)
      _board(i,j) = EMPTY;
}
void GlixxBoard::dump() const
{
  _board.dump();
}
double GlixxBoard::payoff() const
{
  if(win(WHITE))
    return 0.5;
  if(win(BLACK)>0)
    return -0.5;
  return 0;
}

bool GlixxBoard::connected(int i, int j) const
{
  if (i==0) {
    if (j==_board.width()-1)
      return _board(i,j-1) != EMPTY || _board(i+1,j-1) != EMPTY || _board(i+1,j) != EMPTY;
    if (j==0)
      return _board(i+1,j) != EMPTY || _board(i+1,j+1) != EMPTY || _board(i,j+1) != EMPTY;
    
    return _board(i,j-1) != EMPTY || _board(i+1,j-1) != EMPTY || _board(i+1,j) != EMPTY 
      || _board(i+1,j+1) != EMPTY || _board(i,j+1) != EMPTY;
  }

  if (i==_board.height()-1) {
    if (j==_board.width()-1)
      return _board(i-1,j) != EMPTY || _board(i-1,j-1) != EMPTY || _board(i,j-1) != EMPTY;
    if (j==0)
      return _board(i-1,j) != EMPTY || _board(i-1,j+1) != EMPTY || _board(i,j+1) != EMPTY;
    return _board(i,j-1) != EMPTY || _board(i-1,j-1) != EMPTY || _board(i-1,j) != EMPTY 
      || _board(i-1,j+1) != EMPTY || _board(i,j+1) != EMPTY;
  }

  if (j==0) {
    return _board(i-1,j) != EMPTY || _board(i-1,j+1) != EMPTY || _board(i,j+1) != EMPTY 
      || _board(i+1,j+1) != EMPTY || _board(i+1,j) != EMPTY;
  }
  if(j==_board.width()-1) {
    return _board(i-1,j) != EMPTY || _board(i-1,j-1) != EMPTY || _board(i,j-1) != EMPTY 
      || _board(i+1,j-1) != EMPTY || _board(i+1,j) != EMPTY;
  }
  return _board(i-1,j) != EMPTY || _board(i-1,j+1) != EMPTY ||
    _board(i,j+1) != EMPTY || _board(i+1,j+1) != EMPTY ||
    _board(i+1,j) != EMPTY || _board(i+1,j-1) != EMPTY ||
    _board(i,j-1) != EMPTY || _board(i-1,j-1) != EMPTY;
}

bool GlixxBoard::win(PLAYER x) const
{
  for(int i=0; i<3; ++i)
    for(int j=0; j<3; ++j) 
      if (_board(i,j) == x) {
	//if (i==1 && j==1) {
	//std::cout<<"cycle"<<std::endl<<std::flush(std::cout);
	// std::cout<<_board(i,j)<<std::endl;
	// std::cout<<_board(i,j+1)<<std::endl;
	//std::cout<<_board(i,j+2)<<std::endl;
	//std::cout<<_board(i,j+3)<<std::endl<<std::flush(std::cout);
	//}
	if (_board(i,j+1) == x &&
	    _board(i,j+2) == x &&
	    _board(i,j+3) == x )
	  return true;
	if (_board(i+1,j+1) == x &&
	    _board(i+2,j+2) == x &&
	    _board(i+3,j+3) == x )
	  return true;
	if (_board(i+1,j) == x &&
	    _board(i+2,j) == x &&
	    _board(i+3,j) == x )
	  return true;
      }

  for(int i=0; i<3; ++i)
    for(int j=3; j<6; ++j)
      if (_board(i,j) == x) {
	if (_board(i+1,j) == x &&
	    _board(i+2,j) == x &&
	    _board(i+3,j) == x )
	  return true;
	if (_board(i+1,j-1) == x &&
	    _board(i+2,j-2) == x &&
	    _board(i+3,j-3) == x )
	  return true;
      }

  for(int i=3; i<6; ++i)
    for(int j=0; j<3; ++j)
      if (_board(i,j) == x) {
	if (_board(i,j+1) == x &&
	    _board(i,j+2) == x &&
	    _board(i,j+3) == x )
	  return true;
	if (_board(i-1,j+1) == x &&
	    _board(i-2,j+2) == x &&
	    _board(i-3,j+3) == x )
	  return true;
      }
  return false;
}
PLAYER& GlixxBoard::operator()(int i, int j)
{
  return _board(i,j);
}
PLAYER GlixxBoard::operator()(int i, int j) const
{
  return _board(i,j);
}

int GlixxBoard::width() const
{
  return _board.width();
}
int GlixxBoard::height() const
{
  return _board.height();
}
bool GlixxBoard::full() const 
{
  if ( blackTokens == 0 && whiteTokens == 0)
    return true;
  if ( win(BLACK) || win(WHITE) )
    return true;
  return false;
}
