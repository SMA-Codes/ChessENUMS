#include <iostream>
#include <array>
#include "BoardConfig.h"
#include "ChessPiece.h"
#include "Enums.h"

void SetUpPawnPieces(std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard);
void SetUpMainPieces(std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard);
void PrintChessBoard(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard);

int main() {
    std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> chessBoard;
    SetUpPawnPieces(chessBoard);
    SetUpMainPieces(chessBoard);
    PrintChessBoard(chessBoard);

    return 0;
}

void SetUpPawnPieces(std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard) {
    for (int i = 0; i < BoardConfig::COLUMN_SIZE; i++) {
        chessBoard[1][i] = ChessPiece(PAWN, BLACK, i, 1);
        chessBoard[6][i] = ChessPiece(PAWN, WHITE, i, 6);
    }
}

void SetUpMainPieces(std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard) {
    for (int i = 0; i < BoardConfig::COLUMN_SIZE; i++) {
        switch (i) {
            case 0:
                chessBoard[0][i] = ChessPiece(ROOK, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(ROOK, WHITE, i, 0);
                break;
            case 1:
                chessBoard[0][i] = ChessPiece(KNIGHT, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(KNIGHT, WHITE, i, 0);
                break;
            case 2:
                chessBoard[0][i] = ChessPiece(BISHOP, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(BISHOP, WHITE, i, 0);
                break;
            case 3:
                chessBoard[0][i] = ChessPiece(QUEEN, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(QUEEN, WHITE, i, 0);
                break;
            case 4:
                chessBoard[0][i] = ChessPiece(KING, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(KING, WHITE, i, 0);
                break;
            case 5:
                chessBoard[0][i] = ChessPiece(BISHOP, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(BISHOP, WHITE, i, 0);
                break;
            case 6:
                chessBoard[0][i] = ChessPiece(KNIGHT, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(KNIGHT, WHITE, i, 0);
                break;
            case 7:
                chessBoard[0][i] = ChessPiece(ROOK, BLACK, i, 0);
                chessBoard[7][i] = ChessPiece(ROOK, WHITE, i, 0);
                break;
        }
    }
}

void PrintChessBoard(const std::array<std::array<ChessPiece, BoardConfig::COLUMN_SIZE>, BoardConfig::ROW_SIZE> &chessBoard) {
    for (int row = 0; row < BoardConfig::ROW_SIZE; row++) {
        for (int col = 0; col < BoardConfig::COLUMN_SIZE; col++) {
            if (chessBoard[row][col].m_type == EMPTY) {
                std::cout << ".  "; // Empty square
            } else {
                switch (chessBoard[row][col].m_type) {
                    case PAWN:
                        if (chessBoard[row][col].m_color == WHITE)   
                            std::cout << "WP" << " ";
                        else 
                            std::cout << "BP" << " ";
                        break;
                    case ROOK:   
                        if (chessBoard[row][col].m_color == WHITE)   
                            std::cout << "WR" << " ";
                        else 
                            std::cout << "BR" << " ";
                        break;
                    case KNIGHT: 
                        if (chessBoard[row][col].m_color == WHITE)   
                            std::cout << "WN" << " ";
                        else 
                            std::cout << "BN" << " ";
                        break;
                    case BISHOP: 
                        if (chessBoard[row][col].m_color == WHITE)   
                            std::cout << "WB" << " ";
                        else 
                            std::cout << "BB" << " ";
                        break;
                    case QUEEN:  
                        if (chessBoard[row][col].m_color == WHITE)   
                            std::cout << "WQ" << " ";
                        else 
                            std::cout << "BQ" << " ";
                        break;
                    case KING:   
                        if (chessBoard[row][col].m_color == WHITE)   
                            std::cout << "WK" << " ";
                        else 
                            std::cout << "BK" << " ";
                        break;
                    default:     
                        std::cout << "?" << " "; break;
                }
            }
        }
        std::cout << std::endl; // New line after each row
    }
}