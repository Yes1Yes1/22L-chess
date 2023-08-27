/****************************************************************************************/
/* Project: ChessCooker, for EECS22L, Spring 2023                                       */
/* BoardInteract.c: File for chess board interactions                                   */
/****************************************************************************************/
// Author: Ryan Lockie
//
// Modifications:
//
// 4/26/2023 RL Added IsLegalMove() function
//
// 4/25/2023 CD Added definitions for IntToRank() and IntToFile(), Changed IntToRank()
// 		and RankToInt() to properly convert
//
// 4/25/2023 RL Added DeleteBoard and CopyBoard
//
// 4/17/2023 RL Added FileToInt, RankToInt, and modified Rank and File calls
//
// 4/16/2023 RL Initial version
//
//

#include "BoardInteract.h"
#include "ChessObjects.h"
#include "ChessRules.h"
#include "LogFile.h"
#include <stdlib.h>
#include <stdio.h> /* FIXME */

t_Piece *LookupPiece(t_Board board, t_Position position)
{
	t_Piece *returnable = NULL; //Sets return to NULL incase nothing is found
	returnable = board[RankToInt(position)][FileToInt(position)]; //This usage of board is assuming that Rank is stored first, and that the File can be directly converted from char to int. This assumption is made for this whole file
	return returnable;
}

void PlacePiece(t_Board board, t_Piece *piece, t_Position position)
{
	board[RankToInt(position)][FileToInt(position)] = piece; //Sets Location in board array to Piece
	return;
}

void MovePiece(t_Board board, t_Move *move, int moveMode, t_Player color, t_PieceList pieces)
{
	t_Position from = move -> From;
	t_Position to = move -> To;
	t_Piece *tempPiece = NULL;
	if (move -> Castling == 1)
	{
		tempPiece = board[RankToInt(from)][FileToInt(from)]; //Sets origin as first temp piece
		t_Piece *alternatePiece = board[RankToInt(to)][FileToInt(to)]; //Sets final location as alternate temp piece for sw
		board[RankToInt(from)][FileToInt(from)] = NULL;
		board[RankToInt(to)][FileToInt(to)] = NULL;
		
		if (to.File == 'a')
		{
			from.File = 'd';
			to.File = 'c';
		}
		else
		{
			from.File = 'f';
			to.File = 'g';
		}
		board[RankToInt(from)][FileToInt(from)] = alternatePiece; //Sets alternate to original position
		board[RankToInt(to)][FileToInt(to)] = tempPiece; //Sets origin piece to destination
	}
	else if (move -> EnPassant == 1)
	{
		tempPiece = board[RankToInt(from)][FileToInt(from)]; //Clears original position
		board[RankToInt(to)][FileToInt(to)] = tempPiece; //Sets pawn to ending position
		board[RankToInt(from)][FileToInt(to)] = NULL; //Sets captured position to NULL
		board[RankToInt(from)][FileToInt(from)] = NULL; //Sets captured position to NULL
		
	}
	else if (move -> Promotion != None)
	{
		for (int i = 0; i < 32; i++)
		{
			if (pieces[i] -> Type == move -> Promotion && pieces[i] -> Color == color)
			{
				tempPiece = pieces[i]; //Finds the piece of desired type and color
				i = 33; //Ends for loop
			}
		}
		board[RankToInt(from)][FileToInt(from)] = NULL; //Sets origin to NULL
		board[RankToInt(to)][FileToInt(to)] = tempPiece; //Sets to to promotion piece type
	}
	else
	{
		tempPiece = NULL; //Creates a temp Piece reference for moving purposes
		tempPiece = board[RankToInt(from)][FileToInt(from)]; //Records the original piece at from
		board[RankToInt(from)][FileToInt(from)] = NULL; //Sets piece at from to NULL
		board[RankToInt(to)][FileToInt(to)] = tempPiece; //Sets Piece at destination to tempPiece
	}
	if(moveMode){ // if moveMode == 1, then the move was done on the actual board, if 0, then it was done on a virtual board
		board[RankToInt(to)][FileToInt(to)]->HasMoved++; //makes it so that the piece has been recorded as being moved another time
		if (move -> Castling == 1)
		{
			board[RankToInt(from)][FileToInt(from)] -> HasMoved++;
		}
		RecordMove(board[RankToInt(to)][FileToInt(to)], from, to);
	}
	return;
}

int FileToInt(t_Position position) //Returns integer version of File
{
	int returnable = (int) position.File;
	returnable = returnable - (int) 'a';
	return returnable;
}

int RankToInt(t_Position position) //Returns integer version of Rank
{
	int returnable = position.Rank;
	returnable = 8 - returnable; //Assumes ranks are 1 to 8, and converts them to 0 to 7
	return returnable;
}

char IntToFile(int file) // Returns file as seen on chessboard
{
	char returnable = file + (int) 'a';
	return returnable;
}

int IntToRank(int rank) // Returns rank as seen on chessboard
{
	char returnable = 8 - rank;
	return returnable;
}

void DeleteBoard(t_Board board) //Deletes given board
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			DeletePiece(board[i][j]);
		}
	}
}

void CopyBoard(t_Board source, t_Board destination) //Copies given board
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j <8; j++)
		{
			destination[i][j] = source[i][j];
		}
	}
}

int IsLegalMove(t_Move *move, t_Board board, t_Move *PrevMove, t_PieceList pieces) //Determines whether a piece is legal. Returns 1 if so, 0 if not
{
	t_Position start = move -> From;
	t_Position finish = move -> To;
	t_MoveList *PossibleMoves = PieceLegalMoves(board, start, PrevMove); //Finds possible moves from given position
	t_MoveList *Castling = NULL; //Finds possible moves from given position
	
	// account for castling
	if (LookupPiece(board, move->From)->Type == King)
	{
		Castling = CastlingMove(board, start, pieces);
		if (PossibleMoves != NULL && Castling != NULL && PossibleMoves->Length == 0)
		{
			PossibleMoves -> First = Castling -> First;
			PossibleMoves -> Last = Castling -> Last;
			PossibleMoves -> Length += Castling -> Length;
		}
		
		else if (PossibleMoves != NULL && Castling != NULL && PossibleMoves -> Length > 0 && Castling->Length > 0)
		{
			PossibleMoves -> Last -> Next = Castling -> First;
			Castling -> First -> Prev  = PossibleMoves -> Last;
			PossibleMoves -> Last = Castling -> Last;
			PossibleMoves -> Length += Castling -> Length;
		}
		t_Move *analyzeList;
		if (Castling != NULL)
		{
			analyzeList = Castling -> First;
			for (int i = 1; i <= Castling -> Length; i++)
			{
				analyzeList -> List = PossibleMoves;
			}
		}

		free(Castling);
	}
	
	// remove moves that put king in check
	/*if (PossibleMoves != NULL && PossibleMoves -> Length > 0)
	{	
		t_Move *potentialDelete, *next; 
		t_Board virtBoard;
		potentialDelete = PossibleMoves->First;
		while (potentialDelete)
		{
			CopyBoard(board, virtBoard);
			next = potentialDelete->Next;
			MovePiece(virtBoard, potentialDelete, 0, LookupPiece(board, potentialDelete->From)->Color, pieces);
			if (InCheck(virtBoard, LookupPiece(board, potentialDelete->From)->Color))
			{
				if (PossibleMoves->Length == 1)
				{
					potentialDelete->Prev->Next = next;
					next->Prev = potentialDelete->Prev;
					PossibleMoves->First=NULL;
					PossibleMoves->Last = NULL;
					DeleteMove(potentialDelete);
					PossibleMoves--;
				}

				else if (PossibleMoves->First == potentialDelete && PossibleMoves->Length > 1)
				{
					PossibleMoves->First = next;
					potentialDelete->Prev->Next = next;
					next->Prev = potentialDelete->Prev;
					DeleteMove(potentialDelete);
					PossibleMoves--;
				}
				
				else if (PossibleMoves->Last == potentialDelete && PossibleMoves->Length > 1)
				{
					PossibleMoves->Last = potentialDelete->Prev;
					potentialDelete->Prev->Next = next;
					next->Prev = potentialDelete->Prev;
					DeleteMove(potentialDelete);
					PossibleMoves--;
				}

				else
				{
					potentialDelete->Prev->Next = next;
					next->Prev = potentialDelete->Prev;
					DeleteMove(potentialDelete);
					PossibleMoves--;
					
				}
			}
			
			potentialDelete = next;
		}
	}*/

	t_Move *currentMove = NULL;
	int temp = 1; //Turns to one when while loop is complete
	if (PossibleMoves != NULL && PossibleMoves -> Length != 0)
	{
		currentMove = PossibleMoves -> First; //Sets first move
		temp = 0;
	}
	int result = 0; //Sets integer for result of whether move is legal
	
	while (temp == 0)
	{
		if (currentMove->To.Rank == finish.Rank && currentMove->To.File == finish.File) //Ends loop and confirms if move is found to be valid
		{
			result = 1;
			temp = 1;
			move -> Castling = currentMove -> Castling;
			move -> EnPassant = currentMove -> EnPassant;
			move -> Promotion = currentMove -> Promotion;
		}
		if (currentMove -> Next == NULL)
		{
			temp = 1; //Ends loop if nothing is ever found
		}
		else
		{
			currentMove = currentMove -> Next; //Continues with next entry in PossibleMoves Doubly Linked List
		}
	}

	if (PossibleMoves != NULL && PossibleMoves -> Length != 0)
	{
		DeleteMoveList(PossibleMoves);
	}



	return result; //Returns 0 or 1 depending on if the move was valid
}
