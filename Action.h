#ifndef ACTION_H
#define ACTION_H

enum PLAYER { EMPTY=0, WHITE, BLACK };
enum PUSH_DIRECTION { NONE=0, N, NE, E, SE, S, SW, W, NW };

class Action
{
 public:
  Action();
  Action(int, int, PLAYER); 
  Action(int, int, PLAYER, PUSH_DIRECTION d);
  bool operator<(const Action&) const;
  void dump() const;
  int _i;
  int _j;
  PLAYER _P;
  PUSH_DIRECTION _d;
};

struct pair
{
  pair() { value=0; depth=1; }
  pair(double v, int d) { value = v; depth = d; }
  double value;
  int depth;
  bool operator<(const pair& r) const {
    if (value<r.value)
      return true;
    if (value>r.value)
      return false;
    return depth<r.depth;
  }
};

#endif // ACTION_H
