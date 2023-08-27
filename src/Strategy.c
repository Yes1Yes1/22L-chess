/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* Strategy.c: source file for chess strategy			     */
/*********************************************************************/
// Author: Christopher Dao / Ryan Lockie
//
// Modifications:
//
// 4/26/2023 RL Completed initial functionality for AI processes
//
// 4/25/2023 RL Added functionality to ChooseBestMove, AnalyzeCapture, and Board Interact Dependency
//
// 4/23/2023 CD  Initial version
//

/*** preprocessor directives ***/

#include "Strategy.h"
#include "ChessObjects.h"
#include "BoardInteract.h"
#include "ChessRules.h"
#include <stdlib.h>
#include <stdio.h>

t_Move *ChooseBestMove(t_MoveList *moves, t_Player color, t_Board board, int loops, t_PieceList pieces)
{
	if (moves != NULL && moves -> First != NULL)
	{
		int loopies = loops - 1;
		t_Move *BestMove = moves -> First; //Initializes BestMove as the first value
		if (BestMove -> Next == NULL)
		{
			return BestMove;
		}
		else
		{
			t_Move *CurrentMove = BestMove -> Next; //Initializes value to check as the second move
	
			if (loops > 0) //Checks if future is to be analyzed any more times
			{
				AnalyzeFuture(BestMove, board, loopies, color, pieces); //Implementation in progress
			}
			AnalyzeCapture(BestMove); //Checks first move
			if (CurrentMove != NULL)
			{
				int Iterated = 0; //Integer to check if moves has been completely searched through
				while (Iterated == 0)
				{
					loopies = loops - 1;
					if (loops > 0)
					{
						AnalyzeFuture(CurrentMove, board, loopies, color, pieces); //Implementation in progress
					}
					AnalyzeCapture(CurrentMove); //Run all point analysis functions here
					if (CurrentMove -> Points > BestMove -> Points)
					{
					BestMove = CurrentMove; //Sets a new Best Move
					}
					if (CurrentMove -> Next == NULL)
					{
						Iterated = 1; //Flags for completion
					}
					else
					{
						CurrentMove = CurrentMove -> Next; //Checks next move in list
					}
				}
			}	
			return BestMove;
		}
	}
	else
	{
		return NULL;
	}
}

void AnalyzeCapture(t_Move *move) //Assigns adds to the point value depending on captured piece type
{	
	if (move != NULL && move -> Capture != NULL) //Iterates when a piece is captured
	{
		switch(move -> Capture -> Type)
		{
			case Pawn :
				move -> Points += 2000;
				break;
		
			case Knight :
				move -> Points += 3000;
				break;

			case Bishop :
				move -> Points += 3000;
				break;
		
			case Rook :
				move -> Points += 5000;
				break;

			case Queen :
				move -> Points += 9000;
				break;
		
			case King :
				move -> Points += 100000;
				break;
		
			default :
				move -> Points += -1000;
				break;
		}
	}
	else if(move != NULL)//Optional place to add feature for when no piece is captured
	{
		move -> Points += -1000;
	}
}

void AnalyzeFuture(t_Move *move, t_Board board, int loops, t_Player color, t_PieceList pieces) //Checks future moves with a simulated board
{
	if (move != NULL && board != NULL && (color == White || color == Black))
	{
		t_Board VirtualBoard;
		CopyBoard(board, VirtualBoard); //Creates a virtual board
		MovePiece(VirtualBoard, move, 0, color, pieces); //Makes the entered move on the simulated board
		t_MoveList *firstTempList = LegalMoves(VirtualBoard, OppositePlayer(color), move, pieces); //Creates temp move list
		t_Move *tempMove = ChooseBestMove(firstTempList, OppositePlayer(color), VirtualBoard, 0, pieces); //Simulated enemy move with zero loop iterations on virtual board
		if (tempMove != NULL)
		{
			MovePiece(VirtualBoard, tempMove, 0, color, pieces); //Simulates move that was just created in the virtual board
			
			for (int i = (2 - loops); i > 0; i--)
			{
				tempMove -> Points /= 10; //Reduces value by a factor of ten based upon the amount of loops remaining
			}
			move -> Points -= tempMove -> Points; //Deducts lost value from points
			
			t_MoveList *secondTempList = LegalMoves(VirtualBoard, color, tempMove, pieces); //Creates second temp list
			t_Move *secondtempMove = ChooseBestMove(secondTempList, color, VirtualBoard, loops, pieces); //Continues recursion, with new loops value being one less (was reduced in the other function)
			if (secondtempMove != NULL)
			{
				for (int i = (3 - loops); i > 0; i--)
				{
					secondtempMove -> Points /= 10; //Reduces value by a factor of ten based upon the amount of loops remaining
				}
				move -> Points += secondtempMove -> Points; //Adds the points value from simulated version into the original move command (The value of 4 is assuming there will be 3 depth iterations, and it must be 1 greater than the value of iterations)
			}
			DeleteMoveList(secondTempList); //Deletes initial simulated Move List
		}
		DeleteMoveList(firstTempList); //Deletes secondary simulated Move List
	}
}
