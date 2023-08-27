/****************************************************************************************/
/* Project: ChessCooker, for EECS22L, Spring 2023                                       */
/* ChessRules.h: header file for chess rules and regulations                            */
/****************************************************************************************/
// Author: Brandon Dinh
// //
// // Modifications:
//    4/29/23 BD: Added Stalemate declaration
//
//    4/26/23 BD: Removed ReachablePositions declaration	
//
//    4/20/2023 BD: Declared PieceLegalMoves, LegalMoves, InCheck, Checkmate, ReachablePositions
//
// // 4/18/2023 BD Initial version
// //
#include "ChessObjects.h"

#ifndef CHESSRULES_H
#define CHESSRULES_H

t_MoveList *PieceLegalMoves(t_Board board, t_Position position, t_Move *PrevMove);
t_MoveList *LegalMoves(t_Board board, t_Player color, t_Move *PrevMove, t_PieceList pieces);
int InCheck(t_Board board, t_Player color);
int Checkmate(t_Board board, t_Player color, t_PieceList pieces);
int Stalemate(t_Board board, t_Player color, t_PieceList pieces);
t_MoveList *CastlingMove(t_Board board, t_Position position, t_PieceList pieces);

#endif

