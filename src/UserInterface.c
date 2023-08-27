/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* UserInterface.c: source file for user interface functions	     */
/*********************************************************************/
// Author: Christopher Dao
//
// Modifications:
// 4/30/2023 CD  Defined RunHumanHumanMode(), RunHumanComputerMode(),
// 		 RunComputerComputerMode()
//
// 4/26/2023 CD  Defined DrawPlayerMenu(), DrawGamemodeMenu(), 
// 		 PlayerChoice(), HandleChoosePlayer(), 
// 		 HandleChooseGamemode(), functions 
//
// 4/25/2023 CD  Defined GetPosition() function
//
// 4/23/2023 CD  Defined DrawPieces() function, fixed DrawBoard()
// 		 function from having segmentation faults
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

void DrawBoard(t_Board board, SDL_Surface *screen)
{
	// Draw Board
	Uint32 light = SDL_MapRGB(screen->format, 188, 158, 130); 	// Color for light space on chessboard
	Uint32 dark = SDL_MapRGB(screen->format, 111, 78, 55);		// Color for dark space on chessboard
	
	SDL_Rect board_space;	// Rectangle will describe chessboard spaces

		
	int space = 50;		// Width and height of board spaces
	int alternate = 0;	// Controls when the color alternates
	
	/* Set rect to have proper width and height */
	board_space.w = space;
	board_space.h = space;

	/* Draw board */
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			board_space.x = y * space;
			board_space.y = x * space;

			/* light space */
			if (!alternate && x % 2 == 0)
			{
				SDL_FillRect(screen, &board_space, light);
				alternate = 1;
			}

			/* dark space */
			else if (alternate && x % 2 == 0)
			{
				SDL_FillRect(screen, &board_space, dark);
				alternate = 0;
			}

			/* light space */
			if (!alternate && x % 2 == 1)
			{
				SDL_FillRect(screen, &board_space, dark);
				alternate = 1;
			}

			/* dark space */
			else if (alternate && x % 2 == 1)
			{
				SDL_FillRect(screen, &board_space, light);
				alternate = 0;
			}
		}
	}
	
	/* Update screen to see board */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/* Draw all the pieces on the board */
void DrawPieces(t_Board board, SDL_Surface *screen, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b)
{
	SDL_Rect dest;	// Rectangle for where piece will be drawn
	
	int space = 50;	// Width and height of rect
	
	/* Set width and height appropriately */
	dest.w = space;
	dest.h = space;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			
			/* Set position of where pieces will be drawn */
			dest.x = y * space + 5;
			dest.y = x * space + 5;
		
			/* Draw white pieces */
			if (board[x][y] != NULL && board[x][y]->Color == White)
			{
				switch(board[x][y]->Type)
				{
					case Pawn:
						SDL_BlitSurface(pawn_w, NULL, screen, &dest);
						break;
					
					case King:
						SDL_BlitSurface(king_w, NULL, screen, &dest);
						break;
					
					case Queen:
						SDL_BlitSurface(queen_w, NULL, screen, &dest);
						break;
					
					case Rook:
						SDL_BlitSurface(rook_w, NULL, screen, &dest);
						break;
					
					case Bishop:
						SDL_BlitSurface(bishop_w, NULL, screen, &dest);
						break;
					
					case Knight:
						SDL_BlitSurface(knight_w, NULL, screen, &dest);
						break;
					case None:
						break;		
				}
			}
			
			/* Draw black pieces */
			else if (board[x][y] != NULL && board[x][y]->Color == Black)
			{
				switch(board[x][y]->Type)
				{
					case Pawn:
						SDL_BlitSurface(pawn_b, NULL, screen, &dest);
						break;
					
					case King:
						SDL_BlitSurface(king_b, NULL, screen, &dest);
						break;
					
					case Queen:
						SDL_BlitSurface(queen_b, NULL, screen, &dest);
						break;
					
					case Rook:
						SDL_BlitSurface(rook_b, NULL, screen, &dest);
						break;
					
					case Bishop:
						SDL_BlitSurface(bishop_b, NULL, screen, &dest);
						break;
					
					case Knight:
						SDL_BlitSurface(knight_b, NULL, screen, &dest);
						break;
					case None:
						break;
				}
			}
		}
	}

	/* Update screen to see pieces */
	SDL_UpdateRect(screen, 0, 0, 0, 0);

}

/* Draw the Promotion Menu */
void DrawPromotionMenu(SDL_Surface *screen, t_Player Color, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b)
{
	SDL_Rect dest1, dest2, dest3, dest4;	// Rectangle for where piece will be drawn
	Uint32 light = SDL_MapRGB(screen->format, 255, 255, 255); 	// Color for light space on chessboard
	
	int space = 50;				// Width and height of rect
	
	// Set width and height appropriately
	dest1.w = space;
	dest1.h = space;
	dest2.w = space;
	dest2.h = space;
	dest3.w = space;
	dest3.h = space;
	dest4.w = space;
	dest4.h = space;

	dest1.y = 0;
	dest2.y = 0;
	dest3.y = 0;
	dest4.y = 0;

	dest1.x = 0 * space;
	dest2.x = 1 * space;
	dest3.x = 2 * space;
	dest4.x = 3 * space;

	SDL_FillRect(screen, &dest1, light);
	SDL_FillRect(screen, &dest2, light);
	SDL_FillRect(screen, &dest3, light);
	SDL_FillRect(screen, &dest4, light);
	
	if (Color == White)
	{
			
		SDL_BlitSurface(queen_w, NULL, screen, &dest1);				
		SDL_BlitSurface(rook_w, NULL, screen, &dest2);
		SDL_BlitSurface(bishop_w, NULL, screen, &dest3);
		SDL_BlitSurface(knight_w, NULL, screen, &dest4);
		
	}
	
	else
	{
		SDL_BlitSurface(queen_b, NULL, screen, &dest1);				
		SDL_BlitSurface(rook_b, NULL, screen, &dest2);
		SDL_BlitSurface(bishop_b, NULL, screen, &dest3);
		SDL_BlitSurface(knight_b, NULL, screen, &dest4);

	}
					

	/* Update screen to see pieces */
	SDL_UpdateRect(screen, 0, 0, 0, 0);

}

/* Returns 1 if a valid position was clicked for promotion */
int ValidPositionClickedPromotion(int x, int y, int space)
{
	if ((x > (space * 4)) || (y > (space * 1)))
	{
		return 0;
	}
	return 1;
}

/* Returns the piece type of the desired promotion */
t_PieceType PromotionType(int x, int y, int space)
{
	if (x >= space * 0 && x <= space * 1)
	{
		return Queen;
	}
	else if (x >= space * 1 && x <= space * 2)
	{
		return Rook;
	}
	else if (x >= space * 2 && x <= space * 3)
	{
		return Bishop;
	}
	else
	{
		return Knight;
	}
}


/* Load the piece image BMP */
SDL_Surface *LoadPieceBMP(const char *name)
{
	SDL_Surface* piece = NULL;
	
	// Load BMP image
	piece = SDL_LoadBMP(name);
	if (name == NULL)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return NULL;
	}

	// Convert the surface to the appropriate display format
	piece = SDL_DisplayFormat(piece);

	// Apply transparency 
	Uint32 colorkey = SDL_MapRGB(piece->format, 0, 0, 0);
	SDL_SetColorKey(piece, SDL_SRCCOLORKEY, colorkey);

	return piece;
}

/* Returns the position of where the user clicked */
t_Position GetPosition(int x, int y, int space)
{
	t_Position position; 	/* position to be returned */
	int rank, file;		/* to store integer values of rank and file from board */

	for (int i = 0; i < 8; i++)
	{
		if (x >= i * space && x <= (i + 1) * space)
		{
			file = i;
		}
		
		if (y >= i * space && y <= (i + 1) * space)
		{
			rank = i;
		}

	}
	
	
	position.Rank = IntToRank(rank);
	position.File = IntToFile(file);
	return position;
}

/* Returns 1 if the position is valid */
int ValidPositionClicked(int x, int y, int space)
{
	if ((x > (space * 8)) || (y > (space * 8)))
	{
		return 0;
	}
	return 1;
}

/* Displays the menu for choosing Black or White Player */
void DrawPlayerMenu(SDL_Surface *screen)
{
	SDL_Rect white, black; /* rect to draw menu */

	Uint32 light = SDL_MapRGB(screen->format, 255, 255, 255); 	// Color for white option
	Uint32 dark = SDL_MapRGB(screen->format, 0, 0, 0);		// Color for black option
	
	/* divide the screen in half where left side is White and right side is Black */
	white.x = 0;
	white.y = 0;
	white.w = screen->w / 2;
	white.h = screen->h;

	black.x = screen->w / 2;
	black.y = 0;
	black.w = screen->w / 2;
	black.h = screen->h;

	/* handle case when screen width is not evenly divisble by 2 */
	if (screen->w % 2 == 1)
	{
		black.w += 1;
	}

	/* Color the screen */
	SDL_FillRect(screen, &white, light);
	SDL_FillRect(screen, &black, dark);

	/* Update screen to see pieces */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/* Returns whether the user chooses to be Black or White player based on where they clicked */
int PlayerChoice(SDL_Surface *screen, int x)
{
	if (x < screen->w / 2)
	{
		return White;
	}
	else
	{
		return Black;
	}
}

/* Handles the events that result in the user choosing a player */
int HandleChoosePlayer(SDL_Surface *screen)
{
	//  Draw Player Menu
	DrawPlayerMenu(screen);

	SDL_Event event; 	// Event structure
	
	// Process events
	while (SDL_WaitEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				return PlayerChoice(screen, event.button.x);
				break;
			}

			case SDL_QUIT:
			{
				return -1;
				break;
			}

			default:
				break;
		}	
	}

	return -1;
}

/* Displays the menu for choosing Gamemode */
void DrawGamemodeMenu(SDL_Surface *screen)
{
	SDL_Rect HH, HC, CC; /* Rect representing HumanHuman, HumanComputer, and ComputerComputer */

	Uint32 hh_color = SDL_MapRGB(screen->format, 255, 255, 255); 	// Color for white option
	Uint32 hc_color = SDL_MapRGB(screen->format, 196, 164, 132);	// Color for black option
	Uint32 cc_color = SDL_MapRGB(screen->format, 255, 255, 255);	// Color for black option
	
	HH.x = 0;
	HH.y = 0;
	HH.w = screen -> w / 3;
	HH.h = screen -> h;

	HC.x = screen -> w / 3;
	HC.y = 0;
	HC.w = screen -> w / 3;
	HC.h = screen -> h;

	CC.x = screen -> w / 3 * 2;
	CC.y = 0;
	CC.w = screen -> w / 3;
	CC.h = screen -> h;
	
	/* handle case when screen width is not evenly divisible by 3 */
	if (screen -> w % 3 == 1)
		CC.w += 1;
	else if (screen -> w % 3 == 2)
		CC.w += 2;
	
	/* Color the screen */
	SDL_FillRect(screen, &HH, hh_color);
	SDL_FillRect(screen, &HC, hc_color);
	SDL_FillRect(screen, &CC, cc_color);

	/* Update screen to see pieces */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/* Handles the events that result in the user choosing a gamemode */
int HandleChooseGamemode(SDL_Surface *screen)
{
	//  Draw Player Menu
	DrawGamemodeMenu(screen);

	SDL_Event event; 	// Event structure
	
	// Process events
	while (SDL_WaitEvent(&event))
	{
		switch (event.type)
		{
			case (SDL_MOUSEBUTTONDOWN):
			{
				if (event.button.x < screen->w / 3)
				{
					return 0; // represents Human Human mode
				}
			
				else if (event.button.x >= screen-> w / 3 && event.button.x <= screen->w / 3 * 2)
				{
					return 1; // represents Human Computer mode
				}

				else
				{
					return 2; // represents Computer Computer mode
				}
			}

			case (SDL_QUIT):
			{	
				return -1;
				break;
			}

			default:
				break;
		}
	}

	return -1;
}

void RunHumanHumanMode(t_Board board, SDL_Surface *screen, t_PieceList pieces, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b)
{
	int CurrPlayer = White;		// The CurrPlayer begins as White
	int FirstPositionChosen = 0;	// Keeps track of whether it's the first or second click of the User
	int x, y; 			// Stores the x and y coordinates of a button click
	int space = 50;			// Width of a space on the board
	int Running = 1;		// Game loop
	t_Player color;			// color of piece at from position
	t_Position from, to;		// First and second click of User
	t_Move *PrevMove = NULL;	// Record PrevMove for En Passant
	t_Move *CurrMove = NULL;	// keeps track of the player's current move	

	SDL_Event event;		// SDL EventStructure

	/* Draw Board */
	DrawBoard(board, screen);
	
	/* Draw Pieces */	
	DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);

	// Process events Human
	while (Running && SDL_WaitEvent(&event))
	{
		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				x = event.button.x;
				y = event.button.y;
				
				if (!FirstPositionChosen)
				{
					if (ValidPositionClicked(x, y, space) && LookupPiece(board, GetPosition(x, y, space)) != NULL && LookupPiece(board, GetPosition(x, y, space)) -> Color == CurrPlayer)
					{
						from = GetPosition(x, y, space);
						FirstPositionChosen = 1;
					}
				}
				else if (FirstPositionChosen)
				{
					if (ValidPositionClicked(x, y, space))
					{
						to = GetPosition(x, y, space);
						CurrMove = CreateMove(from, to);
						if (IsLegalMove(CurrMove, board, PrevMove, pieces))
						{
							color = LookupPiece(board, CurrMove->From)->Color;

							if (PrevMove != NULL)
							{
								DeleteMove(PrevMove);
							}

							PrevMove = CreateMove(from, to);

							// Handle Promotion
							if (CurrMove->Promotion == Queen)
							{
								DrawPromotionMenu(screen, color, queen_w, rook_w, bishop_w, knight_w, queen_b, rook_b, bishop_b, knight_b);
								SDL_Event event2;
								int Running1 = 1;
								while (Running1 && SDL_WaitEvent(&event2))
								{
									switch(event2.type)
									{
										case SDL_MOUSEBUTTONDOWN:
										{
											x = event2.button.x;
											y = event2.button.y;
											if (ValidPositionClickedPromotion(x, y, space))
											{
												CurrMove->Promotion = PromotionType(x, y, space);
												Running1 = 0;
											}

											break;	
										}

										case SDL_QUIT:
										{
											Running1 = 0;
											break;
										}
										
										default:
										{
											// ignore other events
											break;
										}
									}
								}
							}
	
							MovePiece(board, CurrMove, 1, color, pieces);
							DrawBoard(board, screen);
							DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
							CurrPlayer = OppositePlayer(CurrPlayer);
							FirstPositionChosen = 0;
							
							/* Check for Checkmate after move is conducted */
							if (Checkmate(board, CurrPlayer, pieces))
							{
								Running = 0;
								if (OppositePlayer(CurrPlayer) == White)
								{
									printf("WHITE WINS!\n");
								}
								else
								{
									printf("BLACK WINS!\n");
								}
							}
						}
						else
						{
							FirstPositionChosen = 0;
						}

					}
						
					if (CurrMove != NULL)
					{
						DeleteMove(CurrMove);
					}
				}
				break;
			}

			case SDL_QUIT:
			{
				Running = 0;
				break;
			}
			
			default: // Ignore other events
			{
				break;
			}
		}
	}	
}

void RunHumanComputerMode(t_Board board, SDL_Surface *screen, int PlayerOne, t_PieceList pieces, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b)
{
	int CurrPlayer = White;		// The CurrPlayer begins as White
	int FirstPositionChosen = 0;	// Keeps track of whether it's the first or second click of the User
	int x, y; 			// Stores the x and y coordinates of a button click
	int space = 50;			// Width of a space on the board
	int Running = 1;		// Game loop
	t_Player color;			// color of piece at from position
	t_Position from, to;		// First and second click of User
	t_Move *PrevMove = NULL;	// Record PrevMove for En Passant
	t_Move *BestMove = NULL;	// Records the AI's BestMove
	t_Move *CurrMove = NULL;	// Keeps track of the user's current move

	SDL_Event event;		// SDL EventStructure

	/* Draw Board */
	DrawBoard(board, screen);
	
	/* Draw Pieces */	
	DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);

	if (PlayerOne == Black)
	{
		BestMove = ChooseBestMove(LegalMoves(board, CurrPlayer, PrevMove, pieces), CurrPlayer, board, 3, pieces);
		color = LookupPiece(board, BestMove->From)->Color;
		MovePiece(board, BestMove, 1, color, pieces);
		DrawBoard(board, screen);
                DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
		CurrPlayer = OppositePlayer(CurrPlayer);
							
		if (PrevMove != NULL)
		{
			DeleteMove(PrevMove);
		}

		PrevMove = CreateMove(BestMove->From, BestMove->To);
							
		if (BestMove != NULL)
		{
			DeleteMove(BestMove);
		}
		
	}

	// Process events Human
	while (Running && SDL_WaitEvent(&event))
	{
		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				x = event.button.x;
				y = event.button.y;
				
				if (!FirstPositionChosen)
				{
					if (ValidPositionClicked(x, y, space) && LookupPiece(board, GetPosition(x, y, space)) != NULL && LookupPiece(board, GetPosition(x, y, space)) -> Color == CurrPlayer)
					{
						from = GetPosition(x, y, space);
						FirstPositionChosen = 1;
					}
				}
				else if (FirstPositionChosen)
				{
					if (ValidPositionClicked(x, y, space))
					{
						to = GetPosition(x, y, space);
						CurrMove = CreateMove(from, to);
						if (IsLegalMove(CurrMove, board, PrevMove, pieces))
						{
							color = LookupPiece(board, CurrMove->From)->Color;

							/* prob gonna need if statements to differentiate between en passant and castleling */
							MovePiece(board, CurrMove, 1, color, pieces);
							DrawBoard(board, screen);
							DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
							CurrPlayer = OppositePlayer(CurrPlayer);
							
							if (PrevMove != NULL)
							{
								DeleteMove(PrevMove);
							}

							PrevMove = CreateMove(from, to);
							
							// Handle Promotion
							if (CurrMove->Promotion == Queen)
							{
								DrawPromotionMenu(screen, color, queen_w, rook_w, bishop_w, knight_w, queen_b, rook_b, bishop_b, knight_b);
								SDL_Event event2;
								int Running1 = 1;
								while (Running1 && SDL_WaitEvent(&event2))
								{
									switch(event2.type)
									{
										case SDL_MOUSEBUTTONDOWN:
										{
											x = event2.button.x;
											y = event2.button.y;
											if (ValidPositionClickedPromotion(x, y, space))
											{
												CurrMove->Promotion = PromotionType(x, y, space);
												Running1 = 0;
											}

											break;	
										}

										case SDL_QUIT:
										{
											Running1 = 0;
											break;
										}
										
										default:
										{
											// ignore other events
											break;
										}
									}
								}
							}
							
							
							/* Check for Checkmate after move is conducted */
							if (Checkmate(board, CurrPlayer, pieces))
							{
								if (OppositePlayer(CurrPlayer) == White)
								{
									printf("WHITE WINS!\n");
								}
								else
								{
									printf("BLACK WINS!\n");
								}
								break;
							}

							BestMove = ChooseBestMove(LegalMoves(board, CurrPlayer, PrevMove, pieces), CurrPlayer, board, 3, pieces);
							color = LookupPiece(board, BestMove->From)->Color;
							MovePiece(board, BestMove, 1, color, pieces);
							DrawBoard(board, screen);
                                                        DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
							CurrPlayer = OppositePlayer(CurrPlayer);
							
							if (PrevMove != NULL)
							{
								DeleteMove(PrevMove);
							}

							PrevMove = CreateMove(BestMove->From, BestMove->To);
							
							if (BestMove != NULL)
							{
								DeleteMove(BestMove);
							}

							FirstPositionChosen = 0;
							
							/* Check for Checkmate after move is conducted */
							if (Checkmate(board, CurrPlayer, pieces))
							{
								if (OppositePlayer(CurrPlayer) == White)
								{
									printf("WHITE WINS!\n");
								}
								else
								{
									printf("BLACK WINS!\n");
								}
								break;
							}
						}
						else
						{
							FirstPositionChosen = 0;
						}
					}
					
					if (CurrMove != NULL)
					{
						DeleteMove(CurrMove);
					}
				}
				break;
			}

			case SDL_QUIT:
			{
				Running = 0;
				break;
			}
			
			default: // Ignore other events
			{
				break;
			}
		}
	}	
}

void RunComputerComputerMode(t_Board board, SDL_Surface *screen, t_PieceList pieces, SDL_Surface *pawn_w, SDL_Surface *king_w, SDL_Surface *queen_w, SDL_Surface *rook_w, SDL_Surface *bishop_w, SDL_Surface *knight_w, SDL_Surface *pawn_b, SDL_Surface *king_b, SDL_Surface *queen_b, SDL_Surface *rook_b, SDL_Surface *bishop_b, SDL_Surface *knight_b)
{
	int CurrPlayer = White;		// The CurrPlayer begins as White
	int Running = 1;		// Game loop
	t_Player color;			// color of piece at from position
	t_Position from, to;		// First and second click of User
	t_Move *PrevMove = NULL;	// Record PrevMove for En Passant
	t_Move *BestMove = NULL; 	// Record BestMove

	SDL_Event event;		// SDL EventStructure

	/* Draw Board */
	DrawBoard(board, screen);
	
	/* Draw Pieces */	
	DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);

	PrevMove = CreateMove(from, to);
	
	// Run Computer Computer
	while (Running && SDL_WaitEvent(&event))
	{
							
		/* prob gonna need if statements to differentiate between en passant and castleling */
		switch(event.type)
		{
			case SDL_QUIT:
			{
				Running = 0;
				break;
			}
			default:
			{ 					
				BestMove = ChooseBestMove(LegalMoves(board, CurrPlayer, PrevMove, pieces), CurrPlayer, board, 3, pieces);
				color = LookupPiece(board, BestMove->From)->Color;
				MovePiece(board, BestMove, 1, color, pieces);
				DrawBoard(board, screen);
      		 		DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
				CurrPlayer = OppositePlayer(CurrPlayer);
		
				if (PrevMove != NULL)
				{
					DeleteMove(PrevMove);
				}

				PrevMove = CreateMove(BestMove->From, BestMove->To);
		
				if (BestMove != NULL)
				{
					DeleteMove(BestMove);
				}

				/* Check for Checkmate after move is conducted */
				if (Checkmate(board, CurrPlayer, pieces))
				{
					Running = 0;
					if (OppositePlayer(CurrPlayer) == White)
					{
						printf("WHITE WINS!\n");
					}
					else
					{
						printf("BLACK WINS!\n");
					}
				}
	
				BestMove = ChooseBestMove(LegalMoves(board, CurrPlayer, PrevMove, pieces), CurrPlayer, board, 3, pieces);
				color = LookupPiece(board, BestMove->From)->Color;
				MovePiece(board, BestMove, 1, color, pieces);
				DrawBoard(board, screen);
      				DrawPieces(board, screen, pawn_w, king_w, queen_w, rook_w, bishop_w, knight_w, pawn_b, king_b, queen_b, rook_b, bishop_b, knight_b);
				CurrPlayer = OppositePlayer(CurrPlayer);

				if (PrevMove != NULL)
				{
					DeleteMove(PrevMove);
				}

				PrevMove = CreateMove(BestMove->From, BestMove->To);
		
				if (BestMove != NULL)
				{
					DeleteMove(BestMove);
				}

				/* Check for Checkmate after move is conducted */
				if (Checkmate(board, CurrPlayer, pieces))
				{
					Running = 0;
					if (OppositePlayer(CurrPlayer) == White)
					{
						printf("WHITE WINS!\n");
					}
					else
					{
						printf("BLACK WINS!\n");
					}
				}
				break;
			}
		}
	}
	
}
