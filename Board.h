#ifndef BOARD_H
#define BOARD_H

#include<iostream>

template <class T> 
class Board
{
 public:
 Board() : _height(0), _width(0), _board(0) { }

 Board(int h, int w) : _height(h), _width(w)
  {
    _board = new T*[_width];
    for(int i=0; i<_width; ++i)
      _board[i] = new T[_height];
  }
  ~Board() {
    clean();
  }
 
  T& operator()(int i, int j) {
    return *(*(_board+j)+i);
  }

  T operator()(int i, int j) const {
    return *(*(_board+j)+i);
  }  

 Board(const Board& right) : _height(right._height), _width(right._width) {
    copyFrom(right);
  }

  Board& operator=(const Board& right) {
    if(this != &right) {
      clean();
      _height = right._height; 
      _width = right._width;
      copyFrom(right);
    }
    return *this;
  }

  void dump() const {
    for(int i=0; i<_height; ++i) {
      for(int j=0; j<_width; ++j)
	std::cout<<this->operator()(i,j);
      std::cout<<std::endl;
    }
  }

  int width() const { return _width; }
  int height() const { return _height; }

 private:
  void clean() {
    for(int i=0; i<_width; ++i) {
      delete[] _board[i]; 
    }
    delete[] _board;
  }
  void copyFrom(const Board& right) {
    _board = new T*[_width];
    for(int i=0; i<_width; ++i)
      _board[i] = new T[_height];
    for(int i=0; i<_height; ++i)
      for(int j=0; j<_width; ++j)
	_board[j][i] = right._board[j][i];
  }

  T** _board;
  int _width;
  int _height;
};

#endif // BOARD_H
