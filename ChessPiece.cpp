#include <vector>
#include <array>
#include "BoardConfig.h"
#include "Enums.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece()
    : m_type(EMPTY),
      m_color(NONE),
      m_xCoordinates(-1),
      m_yCoordinates(-1)
{}

ChessPiece::ChessPiece(PieceTypes type, Color color, int xCoordinates, int yCoordinates)
    : m_type(type), 
      m_color(color), 
      m_xCoordinates(xCoordinates), 
      m_yCoordinates(yCoordinates) 
{}

std::vector<std::pair<int, int>> ChessPiece::AllPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates) {
    switch(m_type) {
        case PAWN:
            return PawnPossibleMoves(chessBoard, m_xCoordinates, m_yCoordinates);
        case ROOK:
            return RookPossibleMoves(chessBoard, m_xCoordinates, m_yCoordinates);
        case BISHOP:
            return BishopPossibleMoves(chessBoard, m_xCoordinates, m_yCoordinates);
        case KNIGHT:
            return KnightPossibleMoves(chessBoard, m_xCoordinates, m_yCoordinates);
        case QUEEN:
            return QueenPossibleMoves(chessBoard, m_xCoordinates, m_yCoordinates);
        case KING:
            return KingPossibleMoves(chessBoard, m_xCoordinates, m_yCoordinates);
        default:
            return std::vector<std::pair<int, int>>();
    }
}

std::vector<std::pair<int, int>> ChessPiece::PawnPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates) {
    std::vector<std::pair<int, int>> moveSet;
    int DOUBLE_MOVE_DISTANCE = 2;
    int SINGLE_MOVE_DISTANCE = 1;
    int diagonalLeft = -1;
    int diagonalRight = 1;
    int startPosition = m_color == WHITE? 6 : 1;
    int advanceDirection = m_color == WHITE ? -1 : 1;
    int endPosition = m_color == WHITE ? 0 : 7;
    if (yCoordinates != endPosition) {
        if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates).m_type == EMPTY) {
            moveSet.push_back(std::make_pair(xCoordinates, yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)));
            if (yCoordinates == startPosition && chessBoard.at(yCoordinates + (DOUBLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates).m_type == false) {
                moveSet.push_back(std::make_pair(xCoordinates, yCoordinates + (DOUBLE_MOVE_DISTANCE * advanceDirection)));
            }
        }
        
        if (xCoordinates == BoardConfig::CORNER_ONE) {
            if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalRight).m_type != EMPTY) {
                if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalRight).m_color != m_color) {
                    moveSet.push_back(std::make_pair(xCoordinates + diagonalRight, yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)));
                }
            }
        }

        else if (xCoordinates == BoardConfig::CORNER_TWO) {
            if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalLeft).m_type != EMPTY) {
                if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalLeft).m_color != m_color) {
                    moveSet.push_back(std::make_pair(xCoordinates + diagonalLeft, yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)));
                }
            }
        }

        else {
            if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalRight).m_type != EMPTY) {
                if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalRight).m_color != m_color) {
                    moveSet.push_back(std::make_pair(xCoordinates + diagonalRight, yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)));
                }
            }
            
            if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalLeft).m_type != EMPTY) {
                if (chessBoard.at(yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)).at(xCoordinates + diagonalLeft).m_color != m_color) {
                    moveSet.push_back(std::make_pair(xCoordinates + diagonalLeft, yCoordinates + (SINGLE_MOVE_DISTANCE * advanceDirection)));
                }
            }
        }
    }
    return moveSet;
}

std::vector<std::pair<int, int>> ChessPiece::RookPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates) {
    std::vector<std::pair<int, int>> moveSet;
    int ROOK_ADVANCE_FORWARD = 1;
    int ROOK_ADVANCE_BACKWARDS = -1;
    int ROOK_REMAIN = 0;
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, ROOK_ADVANCE_FORWARD, ROOK_REMAIN, m_color, moveSet);
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, ROOK_ADVANCE_BACKWARDS, ROOK_REMAIN, m_color, moveSet);  
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, ROOK_REMAIN, ROOK_ADVANCE_FORWARD, m_color, moveSet);  
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, ROOK_REMAIN, ROOK_ADVANCE_BACKWARDS, m_color, moveSet);
    
    return moveSet;
}

std::vector<std::pair<int, int>> ChessPiece::BishopPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates) {
    std::vector<std::pair<int, int>> moveSet;
    int BISHOP_ADVANCE_FORWARD = 1;
    int BISHOP_ADVANCE_BACKWARDS = -1;
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, BISHOP_ADVANCE_FORWARD, BISHOP_ADVANCE_FORWARD, m_color, moveSet);   // Top-right
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, BISHOP_ADVANCE_FORWARD, BISHOP_ADVANCE_BACKWARDS, m_color, moveSet);  // Bottom-right
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, BISHOP_ADVANCE_BACKWARDS, BISHOP_ADVANCE_FORWARD, m_color, moveSet);  // Top-left
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, BISHOP_ADVANCE_BACKWARDS, BISHOP_ADVANCE_BACKWARDS, m_color, moveSet); // Bottom-left
    return moveSet;
}

std::vector<std::pair<int, int>> ChessPiece::KnightPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates) {
    int KNIGHT_FORWARD_TWICE = 2;
    int KNIGHT_BACKWARDS_TWICE = -2;
    int KNIGHT_FORWARD_ONCE = 1;
    int KNIGHT_BACKWARDS_ONCE = -1;
    std::vector<std::pair<int, int>> allMoves;
    std::vector<std::pair<int, int>> moveSet;
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_FORWARD_TWICE, yCoordinates + KNIGHT_FORWARD_ONCE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_FORWARD_TWICE, yCoordinates + KNIGHT_BACKWARDS_ONCE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_BACKWARDS_TWICE, yCoordinates + KNIGHT_FORWARD_ONCE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_BACKWARDS_TWICE, yCoordinates + KNIGHT_BACKWARDS_ONCE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_FORWARD_ONCE, yCoordinates + KNIGHT_FORWARD_TWICE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_FORWARD_ONCE, yCoordinates + KNIGHT_BACKWARDS_TWICE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_BACKWARDS_ONCE, yCoordinates + KNIGHT_FORWARD_TWICE));
    allMoves.push_back(std::make_pair(xCoordinates + KNIGHT_BACKWARDS_ONCE, yCoordinates + KNIGHT_BACKWARDS_TWICE));
    
    for (const auto& move : allMoves) {
        if (move.first < BoardConfig::CORNER_ONE || move.first > BoardConfig::CORNER_TWO || move.second < BoardConfig::CORNER_ONE || move.second > BoardConfig::CORNER_TWO) {
            continue;
        }

        else if (chessBoard.at(move.second).at(move.first).m_type != EMPTY){
            if (chessBoard.at(move.second).at(move.first).m_color == m_color) {
                continue;
            }
            else {
                moveSet.push_back(move);
            }
        }
        else {
            moveSet.push_back(move);
        }
    }
    return moveSet;
}


std::vector<std::pair<int, int>> ChessPiece::QueenPossibleMoves(
    const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE>& chessBoard, int xCoordinates, int yCoordinates) {
    std::vector<std::pair<int, int>> moveSet;
    int QUEEN_ADVANCE_FORWARD = 1;
    int QUEEN_ADVANCE_BACKWARDS = -1;
    int QUEEN_REMAIN = 0;
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_ADVANCE_FORWARD, QUEEN_ADVANCE_FORWARD, m_color, moveSet);   
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_ADVANCE_FORWARD, QUEEN_ADVANCE_BACKWARDS, m_color, moveSet);  
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_ADVANCE_BACKWARDS, QUEEN_ADVANCE_FORWARD, m_color, moveSet);  
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_ADVANCE_BACKWARDS, QUEEN_ADVANCE_BACKWARDS, m_color, moveSet); 

    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_ADVANCE_FORWARD, QUEEN_REMAIN, m_color, moveSet);   
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_ADVANCE_BACKWARDS, QUEEN_REMAIN, m_color, moveSet);  
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_REMAIN, QUEEN_ADVANCE_FORWARD, m_color, moveSet);   
    addMovesInDirection(chessBoard, xCoordinates, yCoordinates, QUEEN_REMAIN, QUEEN_ADVANCE_BACKWARDS, m_color, moveSet);  

    return moveSet;
}

std::vector<std::pair<int, int>> ChessPiece::KingPossibleMoves (const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates) {
    int KING_ADVANCE_FORWARD = 1;
    int KING_ADVANCE_BACKWARD = -1;
    std::vector<std::pair<int, int>> allMoves;
    std::vector<std::pair<int, int>> moveSet;
    allMoves.push_back(std::make_pair(xCoordinates + KING_ADVANCE_FORWARD, yCoordinates + KING_ADVANCE_FORWARD));
    allMoves.push_back(std::make_pair(xCoordinates + KING_ADVANCE_FORWARD, yCoordinates + KING_ADVANCE_BACKWARD));
    allMoves.push_back(std::make_pair(xCoordinates + KING_ADVANCE_FORWARD, yCoordinates));
    allMoves.push_back(std::make_pair(xCoordinates + KING_ADVANCE_BACKWARD, yCoordinates + KING_ADVANCE_FORWARD));
    allMoves.push_back(std::make_pair(xCoordinates + KING_ADVANCE_BACKWARD, yCoordinates + KING_ADVANCE_BACKWARD));
    allMoves.push_back(std::make_pair(xCoordinates + KING_ADVANCE_BACKWARD, yCoordinates));
    allMoves.push_back(std::make_pair(xCoordinates, yCoordinates + KING_ADVANCE_FORWARD));
    allMoves.push_back(std::make_pair(xCoordinates, yCoordinates + KING_ADVANCE_BACKWARD));

    for (const auto& move : allMoves) {
        if (move.first < BoardConfig::CORNER_ONE || move.first > BoardConfig::CORNER_TWO || move.second < BoardConfig::CORNER_ONE || move.second > BoardConfig::CORNER_TWO) {
            continue;
        }

        else if (chessBoard.at(move.second).at(move.first).m_type != EMPTY){
            if (chessBoard.at(move.second).at(move.first).m_color == m_color) {
                continue;
            }
            else {
                moveSet.push_back(move);
            }
        }
        else {
            moveSet.push_back(move);
        }
    }
    return moveSet;
}


void ChessPiece::addMovesInDirection(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates, int xDir, int yDir, Color m_color, std::vector<std::pair<int, int>>& moveSet) {
    int x = xCoordinates + xDir;
    int y = yCoordinates + yDir;

    while (x >= BoardConfig::CORNER_ONE && x <= BoardConfig::CORNER_TWO &&
           y >= BoardConfig::CORNER_ONE && y <= BoardConfig::CORNER_TWO) {
        if (chessBoard.at(y).at(x).m_type != EMPTY) {
            if (chessBoard.at(y).at(x).m_color == m_color) {
                break;
            }
            moveSet.emplace_back(x, y);
            break;
        }

        moveSet.emplace_back(x, y);

        x += xDir;
        y += yDir;
    }
}