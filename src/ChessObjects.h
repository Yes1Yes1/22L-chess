/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* ChessObjects.h: header file for chess data structures	     */
/*********************************************************************/
// Author: Christopher Dao
//
// Modifications:
//
// 4/26/2023 RL  Added HasMoved flag to Piece
//
// 4/22/2023 CD  Added declaration for CreatePiece(), DeletePiece(),
// 		 Added missing semicolons
//
// 4/21/2023 CD  Fixed typedef for t_PieceType, changed Type to
// 		 PieceType
//
// 4/16/2023 CD  Added comments, changed typedef names to include
// 		 "t_" at the start to indicate that its a type
//
// 4/15/2023 CD  Initial version
//

#ifndef CHESSOBJECTS_H
#define CHESSOBJECTS_H

/*** typedef ***/

typedef enum Player t_Player;
typedef enum PieceType t_PieceType;
typedef struct Position t_Position;
typedef struct Piece t_Piece;
typedef t_Piece *t_Board[8][8];
typedef struct Move t_Move;
typedef struct MoveList t_MoveList;
typedef t_Piece *t_PieceList[32];

/*** chess data structures ***/

enum Player
{
	White, 			/* For when player is White */
	Black			/* For when player is Black */
};

enum PieceType
{
	King,			/* Represents the chess piece King */
	Queen,			/* Represents the chess piece Queen */
	Rook,			/* Represents the chess piece Rook */
	Bishop,			/* Represents the chess piece Bishop */
	Knight,			/* Represents the chess piece Knight */
	Pawn,			/* Represents the chess piece Pawn */
	None			/* Represents no piece */
};

struct Position
{
	int Rank;		/* Horizontal row  */
	char File;		/* Vertical column */
};

struct Piece
{
	t_Player Color;		/* Color of piece */
	t_PieceType Type;	/* One of the six types in chess */
	int HasMoved;		/* Whether Piece has Moved */
};

struct Move
{
	t_MoveList *List;	/* Pointer to the list which this move belongs to */
	t_Move *Next;		/* Pointer to the next move, or NULL */
	t_Move *Prev;		/* Pointer to the previous move, or NULL */
	t_Position From;	/* Position that the piece moves from */
	t_Position To;		/* Position that the piece moves to */
	int Points; 		/* Value for point score of specific move */
	t_Piece *Capture;	/* Pointer to captured piece */
	int EnPassant;		/* Value to determine whether there is an En Passant */
	int Castling; 		/* Value to determine whether there is castling */
	t_PieceType Promotion;  /* Value to determine what type of piece it is promoting to (NULL if no promotion) */
};

struct MoveList
{
	unsigned int Length;	/* Length of the list */
	t_Move *First;		/* Pointer to the first move, or NULL */
	t_Move *Last;		/* Pointer to the last move, or NULL */
};

/*** function declarations ***/

t_Piece *CreatePiece(t_Player color, t_PieceType type);
void DeletePiece(t_Piece *piece);
t_Move *CreateMove(t_Position from, t_Position to);
void DeleteMove(t_Move *move);
t_MoveList *CreateMoveList();
void DeleteMoveList(t_MoveList *list);
void AppendMove(t_MoveList *list, t_Move *move);
t_Player OppositePlayer(t_Player color);

#endif

