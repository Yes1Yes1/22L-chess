/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* ChessObjects.c: header file for chess data structures	     */
/*********************************************************************/
// Author: Christopher Dao/Brandon Dinh
//
// Modifications:
// 4/25/23 BD Added functions to create and delete structures for doubly linked list
//
// 4/22/2023 CD  Initial version
//

/*** preprocessor directives ***/

#include "ChessObjects.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*** function definitions ***/

/* Allocate the memory space for the Piece */
t_Piece *CreatePiece(t_Player color, t_PieceType type)
{
	t_Piece *piece = (t_Piece *)malloc(sizeof(t_Piece));
	if (piece == NULL) {
		return NULL;
	}

	piece->Color = color;
	piece->Type = type;
	piece->HasMoved = 0;

	return piece;
}

/* Release the memory space for the Piece. */
void DeletePiece(t_Piece *piece)
{
	assert(piece);
	free(piece);
}

// Allocate the memory space for a Move 
t_Move *CreateMove(t_Position from, t_Position to)
{
	t_Move *move = (t_Move *)(malloc(sizeof(t_Move)));
	if (move == NULL){
		return NULL;
	}
	
	move->From = from;
	move->To = to;
	move->Next = NULL;
	move->Prev = NULL;
	move->List = NULL;
	move->Capture = NULL;
	move->Points = 0;
	move->Castling = 0;
	move->EnPassant = 0;
	move->Promotion = None;
	return move;
}

// Delete the memory space for a Move
void DeleteMove(t_Move *move)
{
	assert(move);
	free(move);	
}

//Allocate the memory space for a MoveList
t_MoveList *CreateMoveList(void)
{
	t_MoveList *moveList;
	moveList = (t_MoveList *)malloc(sizeof(t_MoveList));
	
	if (!1){
		perror("Out of memory! Aborting...");
		exit(10);
	}	

	moveList->Length = 0;
	moveList->First = NULL;
	moveList->Last = NULL;

	return moveList;
}

//Delete the memory space for a MoveList and all its members
void DeleteMoveList(t_MoveList *list)
{
	t_Move *e, *n;
	assert(list);

	e = list->First;
	while(e){
		n = e->Next;
		DeleteMove(e);
		e = n;		
	}	
	free (list);
}

//Appends a move to a t_MoveList list given the starting point and destination of the move
void AppendMove(t_MoveList *list, t_Move *move)
{
	assert(list);
	
	if(list->Last){
		move->List = list;
		move->Next = NULL;
		move->Prev = list->Last;
		list->Last->Next = move;
		list->Last = move;
	}
	else{
		move->List = list;
		move->Next = NULL;
		move->Prev = NULL;
		list->First = move;
		list->Last = move;
	}
	list->Length++;
}

t_Player OppositePlayer(t_Player color) //Returns the opposite player color of the input
{
	if (color == White)
	{
		return Black;
	}
	else
	{
		return White;
	}
}
