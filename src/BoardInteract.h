/****************************************************************************************/
/* Project: ChessCooker, for EECS22L, Spring 2023                                       */
/* BoardInteract.h: header file for chess board interactions                            */
/****************************************************************************************/
// Author: Ryan Lockie
//
// Modifications:
// 4/26/2023 CD Added include guard
//
// 4/25/2023 CD Added declaration for IntToFile() and IntToRank()
//
// 4/25/2023 RL Added DeleteBoard and CopyBoard
//
// 4/17/2023 RL Added FileToInt and RankToInt
//
// 4/16/2023 RL	Initial version
//

#ifndef BOARDINTERACT_H
#define BOARDINTERACT_H

#include "ChessObjects.h"
#include "ChessRules.h"
#include "LogFile.h"

t_Piece *LookupPiece(t_Board board, t_Position position); //Finds a Piece given a location on the board

void PlacePiece(t_Board board, t_Piece *piece, t_Position position); //Puts a given Piece to a given location on the board

void MovePiece(t_Board board, t_Move *move, int moveMode, t_Player color, t_PieceList pieces); //Moves a position at a given position from one to another on the board

int FileToInt(t_Position position); //Converts File value to an integer between 0 and 7 for array usage

int RankToInt(t_Position position); //Converts Rank value to an integer between 0 and 7 for array usage

char IntToFile(int file); // Converts from an integer value between 0 and 7 to a File for a t_Position

int IntToRank(int rank); // Converts from an integer value between 0 and 7 to a Rank for a t_Position

void DeleteBoard(t_Board board); //Deletes given board

void CopyBoard(t_Board source, t_Board destination); //Copies given board

int IsLegalMove(t_Move *move, t_Board board, t_Move *PrevMove, t_PieceList pieces); //Returns whether or not a move is legal

#endif
