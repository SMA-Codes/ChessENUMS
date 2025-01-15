#pragma once

#include <vector>
#include <array>
#include "BoardConfig.h"
#include "Enums.h"

class ChessPiece {
public:
    ChessPiece();
    ChessPiece(PieceTypes type, Color color, int xCoordinates, int yCoordinates);

    std::vector<std::pair<int, int>> AllPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    
    PieceTypes m_type;
    Color m_color;
    int m_xCoordinates;
    int m_yCoordinates;

private:
    std::vector<std::pair<int, int>> PawnPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    std::vector<std::pair<int, int>> RookPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    std::vector<std::pair<int, int>> BishopPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    std::vector<std::pair<int, int>> KnightPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    std::vector<std::pair<int, int>> QueenPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    std::vector<std::pair<int, int>> KingPossibleMoves(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard, int xCoordinates, int yCoordinates);
    void addMovesInDirection(
    const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard,
    int xCoordinates,
    int yCoordinates,
    int xDir,
    int yDir,
    Color m_color,
    std::vector<std::pair<int, int>>& moveSet);
};