#include "fen.h"
#include "movegen.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {

inline void makeMove(Move Move, Position Position, class Position &ReturnPos) {
  ReturnPos.copyPosition(Position);
  // Make move on piece array
  ReturnPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
  ReturnPos.piece[Move.startSquare] = EMPTY;
  // And on color array
  ReturnPos.color[Move.targetSquare] = Position.color[Move.startSquare];
  ReturnPos.color[Move.startSquare] = EMPTY;
}
inline void search(int depth, int currentDepth, Node Node) {
  if (currentDepth > depth) {
    return;
  }
  int side = (Node.position.enemySide == WHITE) ? BLACK : WHITE;
  MoveGen::initializePosition(Node.position);
  MoveGen::updateAttackedSquares(Node.position.enemySide);
  MoveGen::generate(side);
  for (int i = 0; i < Node.position.moves.size();) {
    Node.children.push_back({});
    makeMove(Node.position.moves[i], Node.position,
             Node.children[Node.children.size() - 1].position);
    search(depth, currentDepth + 1, Node.children[Node.children.size() - 1]);
    i++;
  }
}
} // namespace MoveSearch
} // namespace Aurora
