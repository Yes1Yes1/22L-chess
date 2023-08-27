/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* UserInterface.h: header file for user interface functions	     */
/*********************************************************************/
// Author: Christopher Dao
//
// Modifications:
// 4/26/2023 CD  Added declaration for DrawPlayerMenu(), PlayerChoice(),
// 		 HandleChoosePlayer(), DrawGamemodeMenu(),
// 		 HandleChooseGamemode(), ValidPositionClicked()
//
// 4/25/2023 CD  Added declaration for GetPosition()
//
// 4/23/2023 CD  Added declaration for DrawPieces() function
//
// 4/22/2023 CD  Initial version
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "ChessObjects.h"

/*** function declarations ***/

void DrawBoard(t_Board board, SDL_Surface *screen);

void DrawPieces(t_Board board, SDL_Surface *screen, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b);

void DrawPromotionMenu(SDL_Surface *screen, t_Player Color, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b);

int ValidPositionClickedPromotion(int x, int y, int space);

t_PieceType PromotionType(int x, int y, int space);

SDL_Surface *LoadPieceBMP(const char *name);

t_Position GetPosition(int x, int y, int space);

void DrawPlayerMenu(SDL_Surface *screen);

int PlayerChoice(SDL_Surface* screen, int x);

int HandleChoosePlayer(SDL_Surface *screen);

int HandleChooseGamemode(SDL_Surface *screen);

void DrawGamemodeMenu(SDL_Surface *screen);

int ValidPositionClicked(int x, int y, int space);

void RunHumanHumanMode(t_Board board, SDL_Surface *screen, t_PieceList pieces, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b);

void RunHumanComputerMode(t_Board board, SDL_Surface *screen, int PlayerOne, t_PieceList pieces, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b);

void RunComputerComputerMode(t_Board board, SDL_Surface *screen, t_PieceList pieces, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b);

#endif

