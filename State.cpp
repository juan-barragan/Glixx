#include "State.h"
#include <map>

static PUSH_DIRECTION direction_map[9] = { NONE, N, NE, E, SE, S, SW, W, NW }; 

State::State(GlixxBoard b)
  : _board(b), _tokens(3)
{
 int numBLACK = 0;
  int numWHITE = 0;
  for(int i=0; i<_board.height(); ++i)
    for(int j=0; j<_board.width(); ++j)
      if( _board(i,j) == BLACK )
	++numBLACK;
      else if (_board(i,j) == WHITE)
	++numWHITE;
  if (numWHITE == numBLACK)
    playerinTurn = WHITE;
  else
    playerinTurn = BLACK;
}

PLAYER State::turn() const
{
  int numBLACK = 0;
  int numWHITE = 0;
  for(int i=0; i<_board.height(); ++i)
    for(int j=0; j<_board.width(); ++j)
      if( _board(i,j) == BLACK )
	++numBLACK;
      else if (_board(i,j) == WHITE)
	++numWHITE;
  if (numWHITE == numBLACK)
    return WHITE;
  return BLACK;
}

State State::result(const Action& a) const
{
  State ans(*this);
  // Each move takes one token
  --ans._tokens;
  if (playerinTurn == WHITE)
    ans.playerinTurn = BLACK;
  else
    ans.playerinTurn = WHITE;
  ans._board(a._i, a._j) = a._P;
  // initial position
  int i = a._i;
  int j = a._j;
  switch(a._d) {
  case N: // test OK
    while(i>=0 && ans._board(i,j) != EMPTY)
      --i;
    if (i>=0) {
      for(int k=i; k<a._i; ++k) 
	ans._board(k, j) = ans._board(k+1, j);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case NE: // test OK
    while(i>=0 && j<ans._board.width() && ans._board(i,j) != EMPTY) {
      --i; ++j;
    }
    if(i>=0 && j<_board.width()) {
      for(int k=0; k<j-a._j; ++k)
	ans._board(i+k,j-k) = ans._board(i+k+1, j-k-1);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case E: // test OK
    while(j<ans._board.width() && ans._board(i,j) != EMPTY)
      ++j;
    if(j<ans._board.width()) {
      for(int k=j; k>a._j; --k)
	ans._board(i, k) = ans._board(i, k-1);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case SE:
    while(i<ans._board.height() && j<ans._board.width() && ans._board(i,j) != EMPTY) {
      ++i; ++j;
    }
    if(i<ans._board.height() && j<ans._board.width()) {
      for(int k=0; k<j-a._j; ++k)
        ans._board(i-k, j-k) = ans._board(i-k-1,j-k-1);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case S: // test OK
    while(i<ans._board.height() && ans._board(i,j) != EMPTY)
      ++i;
    if (i<ans._board.height()) {
      for(int k=i; k>a._i; --k)
	ans._board(k,j) = ans._board(k-1,j);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case SW: //Text OK 
    while(i<ans._board.height() && j>=0 && ans._board(i,j) != EMPTY) {
      ++i; --j;
    }
    if(i<ans._board.height() && j>=0) {
      for(int k=0; k<i-a._i; ++k)
	ans._board(i-k,j+k) = ans._board(i-k-1, j+k+1);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case W: // Test OK
    while(j>=0 && ans._board(i,j) != EMPTY)
      --j;
    if(j>=0) {
      for(int k=0; k<a._j-j; ++k)
	ans._board(i, j+k) = ans._board(i, j+k+1);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case NW:  
    while(i>=0 && j>=0 && ans._board(i,j) != EMPTY) {
      --i; --j;
    } 
    if(i>=0 && j>=0) {
      for(int k=0; k<a._i-i; ++k)
	ans._board(i+k, j+k) = ans._board(i+k+1, j+k+1);
      ans._board(a._i, a._j) = EMPTY;
    }
    break;
  case NONE:
  default:
    break;
  }
  //dump();
  //std::cout<<_tokens<<"->";
  //a.dump(); 
  //ans.dump();
  return ans;
}

bool State::legal(const Action& a) const
{
  return legal(a._i, a._j, a._d);
}

bool State::win(PLAYER p) const
{
  return _board.win(p);
}

bool State::legal(int i, int j, PUSH_DIRECTION d) const
{
  if(_board(i, j) != EMPTY)
    return false;
  //std::cout<<i<<","<<j<<":"<<d<<std::endl; std::flush(std::cout);
  switch(d) {
  case N: 
    if (i==0 || _board(i-1,j) == EMPTY)
      return false;
    --i;
    while(i>=0 && _board(i,j) != EMPTY)
      --i;
    if (i>=0) return true;
    break;
  case NE:
    if (i == 0 || j == _board.width()-1 || _board(i-1,j+1) == EMPTY)
      return false;
    --i; ++j;
    while(i>=0 && j<_board.width() && _board(i,j) != EMPTY) {
      --i; ++j;
    }
    if(i>=0 && j<_board.width()) return true;
    break;
  case E:
    if (j==_board.width()-1 || _board(i,j+1) == EMPTY)
      return false;
    ++j;
    while(j<_board.width() && _board(i,j) != EMPTY)
      ++j;
    if(j<_board.width()) return true;
    break;
  case SE:
    if (i == _board.height()-1 || j == _board.width()-1 || _board(i+1,j+1) == EMPTY)
      return false;
    ++i; ++j;
    while(i<_board.height() && j<_board.width() && _board(i,j) != EMPTY) {
      ++i; ++j;
    }
    if(i<_board.height() && j<_board.width()) return true;
    break;
  case S:
    if (i == _board.height()-1 || _board(i+1,j) == EMPTY)
      return false;
    ++i;
    while(i<_board.height() && _board(i,j) != EMPTY)
      ++i;
    if (i<_board.height()) return true;
    break;
  case SW:
    if(i == _board.height()-1 || j==0 || _board(i+1, j-1) == EMPTY)
      return false;
    ++i; --j;
    while(i<_board.height() && j>=0 && _board(i,j) != EMPTY) {
      ++i; --j;
    }
    if(i<_board.height() && j>=0) return true;
    break;
  case W:
    if (j==0 || _board(i, j-1) == EMPTY)
      return false;
    --j;
    while(j>=0 && _board(i,j) != EMPTY)
      --j;
    if(j>=0) return true;
    break;
  case NW:
    if (i==0 || j == 0 || _board(i-1, j-1) == EMPTY)
      return false;
    --i; --j;
    while(i>=0 && j>=0 && _board(i,j) != EMPTY) {
      --i; --j;
    } 
    if(i>=0 && j>=0) return true;
    break;
  case NONE:
    return _board(i, j) == EMPTY;
  }

  return false;
}
void State::dump() const
{
  _board.dump();
}

std::set<Action> State::actions() const
{
  // for each legal action there are perhaps two: the normal 
  // and the pushed one
  std::set<Action> ans;
  for(int i=0; i<6; ++i)
    for(int j=0; j<6; ++j) {
      for(int k=0; k<9; ++k)
	if (legal(i,j, direction_map[k]) && _board.connected(i,j)) {
	  Action a(i,j,playerinTurn,direction_map[k]);
	  ans.insert(a);
	}
    }
  //std::cout<<static_counter++<<std::endl;
  //_board.dump();
  //for(std::set<Action>::const_iterator i=ans.begin(); i!=ans.end(); ++i)
  //i->dump();

  
  return ans;
}

bool State::terminal() const
{
  if (_board.win(BLACK) || _board.win(WHITE) || _tokens == 0)
    return true;
  return false;
}

double State::utility() const
{
  if (_board.win(WHITE)) {
    //std::cout<<"WHITE WINS"<<std::endl;
    //std::cout<<_tokens<<std::endl;
    //_board.dump();
    return _tokens*1.0;
  }
  if (_board.win(BLACK)) {
    //std::cout<<"BLACK WINS"<<std::endl;
    //std::cout<<_tokens<<std::endl;
    //_board.dump();
    return -_tokens*1.0;
  }
  return 0;
}

double State::max_value() const
{
  if (terminal()) {
    return utility();
  }
  double ans = -100.0;
  std::set<Action> moves = actions();
  for(std::set<Action>::const_iterator i=moves.begin(); i!=moves.end(); ++i) {
    ans = std::max(ans, result(*i).min_value());
  }

  return ans;
}

double State::min_value() const
{
  if (terminal()) {
    return utility();
  }
  double ans = 100.0;
  std::set<Action> moves = actions();
  for(std::set<Action>::const_iterator i=moves.begin(); i!=moves.end(); ++i) {
    ans = std::min(ans, result(*i).max_value());
  }

  return ans;
}

Action State::minimax_decision() const
{
  std::set<Action> moves = actions();
  //std::cout<<"Moves Size: "<<moves.size()<<std::endl;
  std::map<double, Action, std::greater<double> > minimalSeeker;
  //std::map<Action, double> minimalSeeker;
  for(std::set<Action>::const_iterator i=moves.begin(); i!=moves.end(); ++i) {
    //State s = result(*i);
    //if(s.terminal())
    //return *i;
    //s._board.dump();
    //double m = s.min_value();
    //std::cout<<m<<std::endl;
    minimalSeeker[result(*i).min_value()] = *i;
    //minimalSeeker[*i] = result(*i).min_value();
  }
  //for(std::map<double, Action, std::greater<double> >::const_iterator i = minimalSeeker.begin(); i!=minimalSeeker.end(); ++i) {
  //(i->second).dump(); std::cout<<i->first<<std::endl;
  //}
  //for(std::map<Action, double >::const_iterator i = minimalSeeker.begin(); i!=minimalSeeker.end(); ++i) {
  //  (i->first).dump(); std::cout<<i->second<<std::endl;
  //}
  return ((minimalSeeker.begin()))->second;
  
}
