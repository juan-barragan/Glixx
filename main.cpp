#include "GlixxBoard.h"
#include "State.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>

static PLAYER player_map[3] = { EMPTY, WHITE, BLACK };

GlixxBoard giveBoard(const int* values)
{
    GlixxBoard b;
    for(int i=0; i<6; ++i)
      for(int j=0; j<6; ++j)
	b(i,j) = player_map[values[6*i+j]];

    return b;
}

std::vector<std::string> split(const std::string& s, char delim)
{
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

static std::map<std::string, PUSH_DIRECTION> initalize()
{
  std::map<std::string, PUSH_DIRECTION> ans;
  ans["O"] = NONE;
  ans["N"] = N;  
  ans["NE"] = NE;
  ans["E"] = E;
  ans["SE"] = SE;
  ans["S"] = S;
  ans["SW"] = SW;
  ans["W"] = W;
  ans["NW"] = NW;

  return ans;
}

static std::map<std::string, PUSH_DIRECTION> DMAP =  initalize();

int main()
{    
  int tBoard[36] = 
    {// 0, 1, 2, 3, 4, 5
        0, 0, 0, 0, 0, 0, // 0 
        0, 0, 0, 0, 0, 0, // 1
	0, 0, 1, 0, 0, 0, // 2
	0, 0, 0, 0, 0, 0, // 3
	0, 0, 0, 0, 0, 0, // 4
	0, 0, 0, 0, 0, 0  // 5
    };
 
  GlixxBoard b = giveBoard(tBoard);
  State s(b);
  bool finished = false;
  bool cerezaWins = false;
  do {
    s.dump();
    // Check what cereza has done
    cerezaWins = s.win(WHITE);
    if (!cerezaWins) {
      // wait for the coup
      std::cout<<"your move ==> ";
      std::string inputString;
      std::cin>>inputString;
      std::vector<std::string> elements = split(inputString, '.');
      int i = atoi(elements[0].c_str()); 
      int j = atoi(elements[1].c_str()); 
      Action a(i,j, BLACK, DMAP[elements[2]]);
      s = s.result(a);
      s.dump();
      finished = s.win(BLACK); 
    }
    std::cout<<"Thinking ..."<<std::endl;
    Action a = s.minimax_decision();
    a.dump();
    s = s.result(a);
    finished = s.win(WHITE);
  } while (!finished);
  if (cerezaWins) {
    std::cout<<"you loose"<<std::endl;
  }


  //b.dump(); std::flush(std::cout);
  //State s(b);
  //s.dump();
  //std::cout<<std::endl;
  //Action a = s.minimax_decision();
  //a.dump();
  //Action a(3,2, WHITE, SW);
  //a.dump();
  //std::cout<<s.legal(3,3,NW)<<std::endl;
  //State r = s.result(a);
  //r.dump();
  //std::cout<<r.terminal()<<std::endl;
  //r.dump();
  //std::cout<<a._i<<","<<a._j<<":"<<a._d<<std::endl;
  //std::cout<<b.win(WHITE)<<std::endl;
  return 0;
}
