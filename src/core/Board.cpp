// Board.cpp
#include <iostream>
#include "Board.hpp"

// Board representation using 4 uint64_t (64 squares, 4 bits per square)
// Each square can hold a piece type (0-12) or be empty (0)
// The board is represented as follows:

// 8 | 56 57 58 59 60 61 62 63
// 7 | 48 49 50 51 52 53 54 55
// 6 | 40 41 42 43 44 45 46 47
// 5 | 32 33 34 35 36 37 38 39
// 4 | 24 25 26 27 28 29 30 31
// 3 | 16 17 18 19 20 21 22 23
// 2 |  8  9 10 11 12 13 14 15
// 1 |  0  1  2  3  4  5  6  7
//      a  b  c  d  e  f  g  h

Board::Board()
{
  for (int i = 0; i < 4; ++i)
    board[i] = 0ULL;
}

void Board::initialize()
{
  // Example: Place white pawns on the second rank (squares 8 to 15)
  for (int i = 8; i <= 15; ++i)
  {
    setPieceAt(i, Piece::WHITE_PAWN);
  }

  // Example: Place black pawns on the seventh rank (squares 48 to 55)
  for (int i = 48; i <= 55; ++i)
  {
    setPieceAt(i, Piece::BLACK_PAWN);
  }

  // Example: Place white rooks on a1 and h1 (squares 0 and 7)
  setPieceAt(0, Piece::WHITE_ROOK);
  setPieceAt(7, Piece::WHITE_ROOK);
  // Example: Place black rooks on a8 and h8 (squares 56 and 63)
  setPieceAt(56, Piece::BLACK_ROOK);
  setPieceAt(63, Piece::BLACK_ROOK);

  // Example: Place white knights on b1 and g1 (squares 1 and 6)
  setPieceAt(1, Piece::WHITE_KNIGHT);
  setPieceAt(6, Piece::WHITE_KNIGHT);
  // Example: Place black knights on b8 and g8 (squares 57 and 62)
  setPieceAt(57, Piece::BLACK_KNIGHT);
  setPieceAt(62, Piece::BLACK_KNIGHT);

  // Example: Place white bishops on c1 and f1 (squares 2 and 5)
  setPieceAt(2, Piece::WHITE_BISHOP);
  setPieceAt(5, Piece::WHITE_BISHOP);
  // Example: Place black bishops on c8 and f8 (squares 58 and 61)
  setPieceAt(58, Piece::BLACK_BISHOP);
  setPieceAt(61, Piece::BLACK_BISHOP);
  // Example: Place white queen on d1 (square 3)
  setPieceAt(3, Piece::WHITE_QUEEN);
  // Example: Place black queen on d8 (square 59)
  setPieceAt(59, Piece::BLACK_QUEEN);

  setPieceAt(4, Piece::WHITE_KING);
  setPieceAt(60, Piece::BLACK_KING);
}

Board::Piece Board::getPieceAt(int square) const
{
  int block = square / 16;
  int offset = (square % 16) * 4;
  return static_cast<Piece>((board[block] >> offset) & 0xF);
}

void Board::setPieceAt(int square, Piece piece)
{
  int block = square / 16;
  int offset = (square % 16) * 4;
  board[block] &= ~(0xFULL << offset);                      // clear the 4 bits
  board[block] |= (static_cast<uint64_t>(piece) << offset); // set the new piece
  // Note: The piece is cast to uint64_t to ensure it fits in the 4 bits
  // and is shifted to the correct position in the block.
  // The 0xFULL mask is used to clear the bits before setting the new piece.
  // This ensures that the piece is stored correctly in the board representation.
}

void Board::printBoard() const
{
  for (int rank = 7; rank >= 0; --rank)
  {
    for (int file = 0; file < 8; ++file)
    {
      int square = rank * 8 + file;
      Piece p = getPieceAt(square);
      std::cout << BoardHelper::pieceToString(p) << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}

// Helper functions to convert between square numbers and algebraic notation
namespace BoardHelper
{

  std::string squareToString(int square)
  {
    // Convert square number to algebraic notation (e.g., 0 -> a1, 63 -> h8)
    char file = 'a' + (square % 8);
    char rank = '1' + (square / 8);
    return std::string(1, file) + std::string(1, rank);
  }

  int stringToSquare(const std::string &squareStr)
  {
    // Convert algebraic notation (e.g., a1, h8) to square number
    if (squareStr.length() != 2)
      return -1; // Invalid input

    char file = squareStr[0];
    char rank = squareStr[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
      return -1; // Invalid input

    int fileIndex = file - 'a';
    int rankIndex = rank - '1';

    return rankIndex + fileIndex;
  }

  std::string pieceToString(Board::Piece piece)
  {
    switch (piece)
    {
    case Board::Piece::WHITE_PAWN:
      return "P";
    case Board::Piece::BLACK_PAWN:
      return "p";
    case Board::Piece::WHITE_KNIGHT:
      return "N";
    case Board::Piece::BLACK_KNIGHT:
      return "n";
    case Board::Piece::WHITE_BISHOP:
      return "B";
    case Board::Piece::BLACK_BISHOP:
      return "b";
    case Board::Piece::WHITE_ROOK:
      return "R";
    case Board::Piece::BLACK_ROOK:
      return "r";
    case Board::Piece::WHITE_QUEEN:
      return "Q";
    case Board::Piece::BLACK_QUEEN:
      return "q";
    case Board::Piece::WHITE_KING:
      return "K";
    case Board::Piece::BLACK_KING:
      return "k";
    default:
      return "."; // Empty square
    }
  }

}
