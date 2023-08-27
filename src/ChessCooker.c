/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* ChessCooker.c: source file for chess program			     */
/*********************************************************************/
// Author: Christopher Dao
//
// Modifications:
// 4/25/2023 CD  Made it so pieces can move
//
// 4/23/2023 CD  Initial chess board is properly shown
//
// 4/22/2023 CD  Initial version
//

#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "UserInterface.h"
#include "ChessObjects.h"
#include "BoardInteract.h"
#include "Strategy.h"
#include "ChessRules.h"
#include "LogFile.h"

int main()
{
	/* Surface for video dispaly */
	SDL_Surface *screen;

	/*** piece images ***/
	SDL_Surface *pawn_w; 	// Pointer to bitmap white pawn
	SDL_Surface *king_w; 	// Pointer to bitmap white king
	SDL_Surface *queen_w;	// Pointer to bitmap white queen
	SDL_Surface *rook_w;	// Pointer to bitmap white rook
	SDL_Surface *bishop_w;	// Pointer to bitmap white bishop
	SDL_Surface *knight_w;	// Pointer to bitmap white knight
	SDL_Surface *pawn_b; 	// Pointer to bitmap black pawn
	SDL_Surface *king_b; 	// Pointer to bitmap black king
	SDL_Surface *queen_b;	// Pointer to bitmap black queen
	SDL_Surface *rook_b;	// Pointer to bitmap black rook
	SDL_Surface *bishop_b;	// Pointer to bitmap black bishop
	SDL_Surface *knight_b;	// Pointer to bitmap black knight
	
	/* board */
	t_Board board;

	/* Allocate memory for Pieces */
	t_Piece *pawn_w1 = CreatePiece(White, Pawn);
	t_Piece *pawn_w2 = CreatePiece(White, Pawn);
	t_Piece *pawn_w3 = CreatePiece(White, Pawn);
	t_Piece *pawn_w4 = CreatePiece(White, Pawn);
	t_Piece *pawn_w5 = CreatePiece(White, Pawn);
	t_Piece *pawn_w6 = CreatePiece(White, Pawn);
	t_Piece *pawn_w7 = CreatePiece(White, Pawn);
	t_Piece *pawn_w8 = CreatePiece(White, Pawn);

	t_Piece *rook_w1 = CreatePiece(White, Rook);
	t_Piece *rook_w2 = CreatePiece(White, Rook);
	t_Piece *knight_w1 = CreatePiece(White, Knight);
	t_Piece *knight_w2 = CreatePiece(White, Knight);
	t_Piece *bishop_w1 = CreatePiece(White, Bishop);
	t_Piece *bishop_w2 = CreatePiece(White, Bishop);
	t_Piece *king_w1 = CreatePiece(White, King);
	t_Piece *queen_w1 = CreatePiece(White, Queen);

	t_Piece *pawn_b1 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b2 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b3 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b4 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b5 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b6 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b7 = CreatePiece(Black, Pawn);
	t_Piece *pawn_b8 = CreatePiece(Black, Pawn);
	
	t_Piece *rook_b1 = CreatePiece(Black, Rook);
	t_Piece *rook_b2 = CreatePiece(Black, Rook);
	t_Piece *knight_b1 = CreatePiece(Black, Knight);
	t_Piece *knight_b2 = CreatePiece(Black, Knight);
	t_Piece *bishop_b1 = CreatePiece(Black, Bishop);
	t_Piece *bishop_b2 = CreatePiece(Black, Bishop);
	t_Piece *king_b1 = CreatePiece(Black, King);
	t_Piece *queen_b1 = CreatePiece(Black, Queen);
	
	/* set all elements on board  to null */
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = NULL;
		}
	}


	/* Populate board */
	board[0][0] = rook_b1;
	board[0][1] = knight_b1;
	board[0][2] = bishop_b1;
	board[0][3] = queen_b1;
	board[0][4] = king_b1;
	board[0][5] = bishop_b2;
	board[0][6] = knight_b2;
	board[0][7] = rook_b2;
	
	board[1][0] = pawn_b1;
	board[1][1] = pawn_b2;
	board[1][2] = pawn_b3;
	board[1][3] = pawn_b4;
	board[1][4] = pawn_b5;
	board[1][5] = pawn_b6;
	board[1][6] = pawn_b7;
	board[1][7] = pawn_b8;

	board[7][0] = rook_w1;
	board[7][1] = knight_w1;
	board[7][2] = bishop_w1;
	board[7][3] = queen_w1;
	board[7][4] = king_w1;
	board[7][5] = bishop_w2;
	board[7][6] = knight_w2;
	board[7][7] = rook_w2;
	
	board[6][0] = pawn_w1;
	board[6][1] = pawn_w2;
	board[6][2] = pawn_w3;
	board[6][3] = pawn_w4;
	board[6][4] = pawn_w5;
	board[6][5] = pawn_w6;
	board[6][6] = pawn_w7;
	board[6][7] = pawn_w8;

	/* populate piece list */
	t_PieceList pieces = {rook_w1, knight_w1, bishop_w1, queen_w1, rook_b1, knight_b1, bishop_b1, queen_b1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	// Initilize SDL video component, and check it is successfull
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
	}

	// When program exits, SDL_Quit is called
	atexit(SDL_Quit);

	// Set video mode to window of size 640 by 480 pixels with 32 bits per pixel
	screen = SDL_SetVideoMode(640, 480, 32, SDL_ANYFORMAT);
	if (screen == NULL)
	{
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	/*** Load pieces ***/
	
	pawn_w = LoadPieceBMP("white_pawn.bmp");
	king_w = LoadPieceBMP("white_king.bmp");
	queen_w = LoadPieceBMP("white_queen.bmp");
	rook_w = LoadPieceBMP("white_rook.bmp");
	bishop_w = LoadPieceBMP("white_bishop.bmp");
	knight_w = LoadPieceBMP("white_knight.bmp");
	pawn_b = LoadPieceBMP("black_pawn.bmp");
	king_b = LoadPieceBMP("black_king.bmp");
	queen_b = LoadPieceBMP("black_queen.bmp");
	rook_b = LoadPieceBMP("black_rook.bmp");
	bishop_b = LoadPieceBMP("black_bishop.bmp");
	knight_b = LoadPieceBMP("black_knight.bmp");
	
	int gamemode;
	int PlayerOne;
	gamemode = HandleChooseGamemode(screen);
	DeleteLog("log.txt");
	if (gamemode == 0) // Human Human case
	{
			
		RunHumanHumanMode(board, screen, pieces, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
	}
	
	else if (gamemode == 1) // Human Computer case
	{
		PlayerOne = HandleChoosePlayer(screen);
		if (PlayerOne != -1)
		{
	
			RunHumanComputerMode(board, screen, PlayerOne, pieces, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
		}
	}

	else if (gamemode == 2) // Computer Computer case
	{
	
		RunComputerComputerMode(board, screen, pieces, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
	}

	/* Deallocate piece image spaces */	
	SDL_FreeSurface(pawn_w);
	SDL_FreeSurface(king_w);
	SDL_FreeSurface(queen_w);
	SDL_FreeSurface(rook_w);
	SDL_FreeSurface(bishop_w);
	SDL_FreeSurface(knight_w);
	SDL_FreeSurface(pawn_b);
	SDL_FreeSurface(king_b);
	SDL_FreeSurface(queen_b);
	SDL_FreeSurface(rook_b);
	SDL_FreeSurface(bishop_b);
	SDL_FreeSurface(knight_b);
	
	/* Deallocate memory for pieces */
	DeletePiece(pawn_w1);
	DeletePiece(pawn_w2);
	DeletePiece(pawn_w3);
	DeletePiece(pawn_w4);
	DeletePiece(pawn_w5);
	DeletePiece(pawn_w6);
	DeletePiece(pawn_w7);
	DeletePiece(pawn_w8);

	DeletePiece(rook_w1);
	DeletePiece(rook_w2);
	DeletePiece(knight_w1);
	DeletePiece(knight_w2);
	DeletePiece(bishop_w1);
	DeletePiece(bishop_w2);
	DeletePiece(king_w1);
	DeletePiece(queen_w1);

	DeletePiece(pawn_b1);
	DeletePiece(pawn_b2);
	DeletePiece(pawn_b3);
	DeletePiece(pawn_b4);
	DeletePiece(pawn_b5);
	DeletePiece(pawn_b6);
	DeletePiece(pawn_b7);
	DeletePiece(pawn_b8);
	
	DeletePiece(rook_b1);
	DeletePiece(rook_b2);
	DeletePiece(knight_b1);
	DeletePiece(knight_b2);
	DeletePiece(bishop_b1);
	DeletePiece(bishop_b2);
	DeletePiece(king_b1);
	DeletePiece(queen_b1);
	
	
	return 0;
}
