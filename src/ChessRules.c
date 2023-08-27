/****************************************************************************************/
/* Project: ChessCooker, for EECS22L, Spring 2023                                       */
/* ChessRules.c: functions for chess rules and regulations                              */
/****************************************************************************************/
// Author: Brandon Dinh/Miguel Vidal
// // //
// // // Modifications:
// // // 4/26/23 BD: Fixed git merge issues, fixed InCheck and Checkmate to use doubly linked list and virtual board
//
// // // 4/22/2023 BD: Initial implementations of InCheck and Checkmate
//
// // // 4/20/2023 BD: Added another author to the heading and included ChessObjects.h
//
// // // 4/20/2023 BD Initial version
// // //

#include <stdlib.h>
#include "ChessRules.h"
#include "ChessObjects.h"
#include "BoardInteract.h"
#include <stdio.h>

t_MoveList *PieceLegalMoves(t_Board board, t_Position position, t_Move *PrevMove)
{
	t_Piece *piece = NULL;
        t_MoveList *LegalMove = CreateMoveList();
        t_Position from;
        t_Position to;
	t_Move *move;
        piece = LookupPiece(board, position);
        t_Position temp;
	t_Piece *temp_piece = NULL;
        from.Rank = position.Rank;
        from.File = position.File;
        int rank = position.Rank;
        char file = position.File;
        int color = piece->Color;
        int type = piece->Type;
        int x;
        if(type == Pawn){       /* Checks what type of piece it is */
                if(color == White){     /* Checks what color is the piece */
                        if(rank == 2){  /* Checks if the pawn is ats its starting location*/
                                temp.Rank = from.Rank + 2;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){   /* Checks if its legal to move 2 upward */
                                	temp.Rank = from.Rank + 1;
                                	temp.File = from.File;
                                	if(LookupPiece(board, temp) == NULL){   /* Checks if its legal to move 1 upward */
                                        	to.Rank = rank + 2;
                                        	to.File = file;
                                        	move = CreateMove(from, to);
                                        	AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
					}
                                }
                        }

                        if(rank == 5 && PrevMove != NULL){  /* en passant */
				temp_piece = LookupPiece(board, PrevMove->To);
				temp.Rank = rank;
				temp.File = file - 1;
				if (file != 'a' && LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color && LookupPiece(board, temp)->Type == Pawn && temp_piece->HasMoved == 1 && LookupPiece(board, temp) == temp_piece)
				{
                                       	to.Rank = rank + 1;
                                       	to.File = file - 1;
                                       	move = CreateMove(from, to);
					move->EnPassant = 1;
					move->Capture = LookupPiece(board, temp);
                                       	AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
				}
				
				temp.Rank = rank;
				temp.File = file + 1;
				if (file != 'h' && LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color && LookupPiece(board, temp) ->Type == Pawn && temp_piece->HasMoved == 1 && LookupPiece(board, temp) == temp_piece)
				{
                                       	to.Rank = rank + 1;
                                       	to.File = file + 1;
                                       	move = CreateMove(from, to);
					move->EnPassant = 1;
					move->Capture = LookupPiece(board, temp);
                                       	AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
				}
					

			}
			
                        if(rank != 8){  /* check if its at the very top of the board*/
                                temp.Rank = from.Rank + 1;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){   /* Checks if its legal to move 1 upward */
                                        to.Rank = rank + 1;
                                        to.File = file;
                                        move = CreateMove(from, to);
					if (rank == 7)
					{
						move -> Promotion = Queen;
					}
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                                if(file != 'a'){        /* check if its at the very bottom of the board*/
                                        temp.Rank = from.Rank + 1;
                                        temp.File = from.File - 1;
                                        if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){   /* Checks if its legal to move 1 upward and 1 to the left */
                                                to.Rank = rank + 1;
                                                to.File = file - 1;
                                                move = CreateMove(from, to);
						if (rank == 7)
						{
							move -> Promotion = Queen;
						}
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
                                }
                                if(file != 'h'){        /* check if its at the very right of the board*/
                                        temp.Rank = from.Rank + 1;
                                        temp.File = from.File + 1;
                                        if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){   /* Checks if its legal to move 1 upward and 1 to the right*/
                                                to.Rank = rank + 1;
                                                to.File = file + 1;
                                                move = CreateMove(from, to);
						if (rank == 7)
						{
							move -> Promotion = Queen;
						}
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
                               }
                        }
                }
                if(color == Black){     /* Checks what color is the piece */
                        if(rank == 7){  /* Checks if the pawn is ats its starting location*/
                                temp.Rank = from.Rank - 1;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){   /* Checks if its legal to move 2 upward */
                                	temp.Rank = from.Rank - 2;
                                	temp.File = from.File;
                                	if(LookupPiece(board, temp) == NULL){   /* Checks if its legal to move 2 downward */
                                	        to.Rank = rank - 2;
                                	        to.File = file;
                                	        move = CreateMove(from, to);
                                        	AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                	}
				}	
                        }
                        
			if(rank == 4 && PrevMove != NULL){  /* en passant */
				temp_piece = LookupPiece(board, PrevMove->To);
				temp.Rank = rank;
				temp.File = file - 1;
				if (file != 'a' && LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color && LookupPiece(board, temp)->Type == Pawn && temp_piece->HasMoved == 1 && LookupPiece(board, temp) == temp_piece)
				{
                                       	to.Rank = rank - 1;
                                       	to.File = file - 1;
                                       	move = CreateMove(from, to);
					move->EnPassant = 1;
					move->Capture = LookupPiece(board, temp);
                                       	AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
				}
				
				temp.Rank = rank;
				temp.File = file + 1;
				if (file != 'h' && LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color && LookupPiece(board, temp)->Type == Pawn && temp_piece->HasMoved == 1 && LookupPiece(board, temp) == temp_piece)
				{
                                       	to.Rank = rank - 1;
                                       	to.File = file + 1;
                                       	move = CreateMove(from, to);
					move->EnPassant = 1;
					move->Capture = LookupPiece(board, temp);
                                       	AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
				}
					

			}
                        if(rank != 1){  /* check if its at the very bottom of the board*/
                                temp.Rank = from.Rank - 1;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){   /* Checks if its legal to move 1 downpward */
                                        to.Rank = rank - 1;
                                        to.File = file;
                                        move = CreateMove(from, to);
					if (rank == 2)
					{
						move -> Promotion = Queen;
					}
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                                if(file != 'a'){        /* check if its at the very left of the board*/
                                        temp.Rank = from.Rank - 1;
                                        temp.File = from.File - 1;
                                        if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){   /* Checks if its legal to move 1 downward and 1 to the left */
                                                to.Rank = rank - 1;
                                                to.File = file - 1;
                                                move = CreateMove(from, to);
						if (rank == 2)
						{
							move -> Promotion = Queen;
						}
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
                                }
                                if(file != 'h'){        /* check if its at the very right of the board*/
                                        temp.Rank = from.Rank - 1;
                                        temp.File = from.File + 1;
                                        if(LookupPiece(board,temp) != NULL && LookupPiece(board, temp)->Color != color){   /* Checks if its legal to move 1 downward and 1 to the right*/
                                                to.Rank = rank - 1;
                                                to.File = file + 1;
                                                move = CreateMove(from, to);
						if (rank == 2)
						{
							move -> Promotion = Queen;
						}
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
                                }
                        }
                }
	}
        else if(type == Knight){        /* Checks what type of piece it is */
                if(rank != 8){  /* Checks if its at the very top */
                        to.Rank = rank + 1;
                        if(file <= 'f'){        /* Checks if its two from the right */
                                temp.Rank = from.Rank + 1;
                                temp.File = from.File + 2;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.File = file + 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                        if(file >= 'c'){        /* Checks if its two from the left */
                                temp.Rank = from.Rank + 1;
                                temp.File = from.File - 2;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.File = file - 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                }
                if(rank != 1){ /* Checks if its at the very bottom */
                        to.Rank = rank - 1;
                        if(file <= 'f'){        /* Checks if its two from the right */
                                temp.Rank = from.Rank - 1;
                                temp.File = from.File + 2;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.File = file + 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                        if(file >= 'c'){        /* Checks if its two from the left */
                                temp.Rank = from.Rank - 1;
                                temp.File = from.File - 2;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.File = file - 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                }
                if(file != 'a'){        /* Checks if its at the very left */
                        to.File = file - 1;
                        if(rank <= 6){  /* Checks if its two from the top */
                                temp.Rank = from.Rank + 2;
                                temp.File = from.File - 1;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.Rank = rank + 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                        if(rank >= 3){  /* Checks if its two from the bottom */
                                temp.Rank = from.Rank - 2;
                                temp.File = from.File - 1;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.Rank = rank - 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                }
                if(file != 'h'){        /* Checks if its at the very right */
                        to.File = file + 1;
                        if(rank <= 6){  /* Checks if its two from the top */
                                temp.Rank = from.Rank + 2;
                                temp.File = from.File + 1;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.Rank = rank + 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                        if(rank >= 3){  /* Checks if its two from the bottom */
                                temp.Rank = from.Rank - 2;
                                temp.File = from.File + 1;
                                if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                        to.Rank = rank - 2;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                }
                        }
                }
        }
        else if(type == Bishop){         /* Checks what type of piece it is */
              	x = 0;
                while(x != 8){  /* iterates to all the diagnal places up right*/
                        x++;
                        if(rank + x <= 8){	/* Check if it goes out the board */
                                if(file + x <= 'h'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank + x;
                                        temp.File = from.File + x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank + x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank + x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                x = 0;
                while(x != 8){  /* iterates to all the diagnal places up left*/
                        x++;
                        if(rank + x <= 8){	 /* Check if it goes out the board */
                                if(file - x >= 'a'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank + x;
                                        temp.File = from.File - x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank + x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
						AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank + x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                x = 0;
                while(x != 8){  /* iterates to all the diagnal places dowon right*/
                        x++;
                        if(rank - x >= 1){	 /* Check if it goes out the board */
                                if(file + x <= 'h'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank - x;
                                        temp.File = from.File + x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank - x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank - x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                x = 0;
                while(x != 8){  /* iterates to all the diagnal places down left*/
                        x++;
                        if(rank - x >= 1){	 /* Check if it goes out the board */
                                if(file - x >= 'a'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank - x;
                                        temp.File = from.File - x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank - x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank - x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
        }
        else if(type == Rook){  /* Checks what type of piece it is */
                for(x=1; x<=8; x++){    /* iterates to all the pieces to the up*/
                        if(rank + x <= 8){	 /* Check if it goes out the board */
                                temp.Rank = from.Rank + x;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank + x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank +  x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
                for(x=1; x<=8; x++){	 /* Check if it goes out the board */
                        if(rank - x >= 1){      /* iterates to all the pieces to the down*/
                                temp.Rank = from.Rank - x;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank - x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank - x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
                for(x=1; x<=8; x++){	 /* Check if it goes out the board */
                        if(file + x <= 'h'){    /* iterates to all the pieces to the right*/
                                temp.Rank = from.Rank;
                                temp.File = from.File + x;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank;
                                        to.File = file + x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank;
                                        to.File = file + x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
                for(x=1; x<=8; x++){    /* iterates to all the pieces to the left*/
                        if(file - x >= 'a'){	 /* Check if it goes out the board */
                                temp.Rank = from.Rank;
                                temp.File = from.File - x;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank;
                                        to.File = file - x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank;
                                        to.File = file - x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
        }
        else if(type == Queen){ /* Checks what type of piece it is */
              	x = 0;
                while(x != 8){  /* iterates to all the diagnal places up right*/
                        x++;
                        if(rank + x <= 8){	/* Check if it goes out the board */
                                if(file + x <= 'h'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank + x;
                                        temp.File = from.File + x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank + x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank + x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                x = 0;
                while(x != 8){  /* iterates to all the diagnal places up left*/
                        x++;
                        if(rank + x <= 8){	 /* Check if it goes out the board */
                                if(file - x >= 'a'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank + x;
                                        temp.File = from.File - x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank + x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
						AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank + x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                x = 0;
                while(x != 8){  /* iterates to all the diagnal places dowon right*/
                        x++;
                        if(rank - x >= 1){	 /* Check if it goes out the board */
                                if(file + x <= 'h'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank - x;
                                        temp.File = from.File + x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank - x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank - x;
                                                to.File = file + x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                x = 0;
                while(x != 8){  /* iterates to all the diagnal places down left*/
                        x++;
                        if(rank - x >= 1){	 /* Check if it goes out the board */
                                if(file - x >= 'a'){	 /* Check if it goes out the board */
                                        temp.Rank = from.Rank - x;
                                        temp.File = from.File - x;
                                        if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                                to.Rank = rank - x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        }
					else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                                to.Rank = rank - x;
                                                to.File = file - x;
                                                move = CreateMove(from, to);
                                                AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                                x = 8;  /* break */
					}
                                        else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                                x = 8;  /* break */
                                        }
                                }
                        }
                }
                
		for(x=1; x<=8; x++){    /* iterates to all the pieces to the up*/
                        if(rank + x <= 8){	 /* Check if it goes out the board */
                                temp.Rank = from.Rank + x;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank + x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank +  x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
                for(x=1; x<=8; x++){	 /* Check if it goes out the board */
                        if(rank - x >= 1){      /* iterates to all the pieces to the down*/
                                temp.Rank = from.Rank - x;
                                temp.File = from.File;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank - x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank - x;
                                        to.File = file;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
                for(x=1; x<=8; x++){	 /* Check if it goes out the board */
                        if(file + x <= 'h'){    /* iterates to all the pieces to the right*/
                                temp.Rank = from.Rank;
                                temp.File = from.File + x;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank;
                                        to.File = file + x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank;
                                        to.File = file + x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
                for(x=1; x<=8; x++){    /* iterates to all the pieces to the left*/
                        if(file - x >= 'a'){	 /* Check if it goes out the board */
                                temp.Rank = from.Rank;
                                temp.File = from.File - x;
                                if(LookupPiece(board, temp) == NULL){         /* Checks if its legal to move */
                                        to.Rank = rank;
                                        to.File = file - x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);       /* record that this is a possible and legal move*/
                                }
				else if(LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color){
                                        to.Rank = rank;
                                        to.File = file - x;
                                        move = CreateMove(from, to);
                                        AppendMove(LegalMove, move);    /* record that this is a possible and legal move*/
                                        break;  /* break */
				}
                                else if (LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color == color){
                                        break;
                                }
                        }
                }
	
	}
        else if(type == King){  /* Checks what type of piece it is */
                if(rank != 1 && file != 'a' ){
                        temp.Rank = from.Rank - 1;
                        temp.File = from.File - 1;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank - 1;
                                to.File = file - 1;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(rank != 1 && file != 'h'){
                        temp.Rank = from.Rank - 1;
                        temp.File = from.File + 1;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank - 1;
                                to.File = file + 1;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(rank != 8 && file != 'a'){
                        temp.Rank = from.Rank + 1;
                        temp.File = from.File - 1;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank + 1;
                                to.File = file - 1;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(rank != 8 && file != 'h'){
                        temp.Rank = from.Rank + 1;
                        temp.File = from.File + 1;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank + 1;
                                to.File = file + 1;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(file != 'a'){
                        temp.Rank = from.Rank;
                        temp.File = from.File - 1;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank;
                                to.File = file - 1;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(file != 'h'){
                        temp.Rank = from.Rank;
                        temp.File = from.File + 1;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank;
                                to.File = file + 1;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(rank != 1){
                        temp.Rank = from.Rank - 1;
                        temp.File = from.File;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank - 1;
                                to.File = file;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
                if(rank != 8){
                        temp.Rank = from.Rank + 1;
                        temp.File = from.File;
                        if((LookupPiece(board, temp) != NULL && LookupPiece(board, temp)->Color != color) || LookupPiece(board, temp) == NULL){ /* Checks if its legal to move 1 upward and 2 to the right*/
                                to.Rank = rank + 1;
                                to.File = file;
                                move = CreateMove(from, to);
                                AppendMove(LegalMove, move);
                        }
                }
        }

	/* Iterates through LegalMoves and sets the piece to capture */
	if (LegalMove != NULL && LegalMove -> Length != 0)
	{
		move = LegalMove->First;
		while (move)
		{	if (move->EnPassant == 1)
			{
				// do nothing
			}
			else
			{
				move->Capture = LookupPiece(board, move->To);
			}
			move = move->Next;
		}	
	}
        return LegalMove;
}

t_MoveList *LegalMoves(t_Board board, t_Player color, t_Move *PrevMove, t_PieceList pieces)
{
	t_Position iterator;
        t_MoveList *returnable = NULL;
	returnable = CreateMoveList();
        for (int i = 0; i <= 7; i++)
        {
                for (int j = 0; j <= 7; j++)
                {
                        iterator.Rank = IntToRank(i);
                        iterator.File = IntToFile(j);
                        if (LookupPiece(board, iterator) != NULL && LookupPiece(board, iterator) -> Color == color) //Checks color validity
                        {
                                t_MoveList *tempList;
                                tempList = PieceLegalMoves(board, iterator, PrevMove); //Generates temp list for each valid position
				if (returnable != NULL && tempList != NULL && returnable->Length == 0)
				{
					returnable->First = tempList -> First;
					returnable-> Last = tempList -> Last;
					returnable->Length += tempList->Length;
				}
				else if (returnable != NULL && tempList != NULL && returnable -> Length > 0 && tempList -> Length > 0)
				{
					returnable->Last->Next = tempList->First;
					tempList->First->Prev = returnable->Last;
					returnable->Last = tempList->Last;
					returnable->Length += tempList->Length;
				}
				
				// account for castling
				/*if (LookupPiece(board, iterator)->Type == King)
				{
					t_MoveList *Castling = NULL;
					Castling = CastlingMove(board, iterator, pieces);
					if (returnable != NULL && Castling != NULL && returnable->Length == 0 && Castling->Length != 0)
					{
						returnable -> First = Castling -> First;
						returnable -> Last = Castling -> Last;
						returnable -> Length += Castling -> Length;
					}
		
					else if (returnable != NULL && Castling != NULL && returnable -> Length > 0 && Castling->Length > 0)
					{
						returnable -> Last -> Next = Castling -> First;
						Castling -> First -> Prev  = returnable -> Last;
						returnable -> Last = Castling -> Last;
						returnable -> Length += Castling -> Length;
					}
					t_Move *analyzeList1;
					if (Castling != NULL)
					{
						analyzeList1 = Castling -> First;
						for (int i = 1; i <= Castling -> Length; i++)
						{
							analyzeList1 -> List = returnable;
						}
					}

					free(Castling);
				}*/
				free(tempList);
			}
                }
        }
	
        t_Move *analyzeList;
	if (returnable != NULL)
        {
		analyzeList = returnable -> First;
       		 for (int i = 1; i <= returnable -> Length; i++) //Iterates through the entire list and assigns the list attribute for each of the moves to the returnable list
        	{
               		 analyzeList -> List = returnable;
        	}	
	}
	//printf("Length: %d\n", returnable->Length);	
        return returnable;
}

int InCheck(t_Board board, t_Player color) // returns 0 if not in check, 1 if in check
{
	t_Position iterator; // meant for iterating through the board and finding all the moves
				// that a piece can make at position indicated by iterator
	t_Piece *king = CreatePiece(color, King); // variable for storing the relevant values of the current player's king
	t_Position posOfKing; // meant to store the location of the king as a Position struct
	
	t_MoveList *toCompare = NULL;
	t_Move *toCompareMove = NULL;

	posOfKing.Rank = -1; // used to keep iterating until king is found

	for (int i = 0; i<8; i++){ // go through the board and find the king
		for (int j = 0; j<8; j++){
			if (board[i][j] != NULL){
				if (board[i][j]->Color == color && board[i][j]->Type == 0){
					//king = board[i][j]; // store the king in the variable king
					
					// converting [i][j] into a Position struct (Position struct uses 1-8 and a-h
					posOfKing.Rank = IntToRank(i);
					posOfKing.File = IntToFile(j);

					break;
				}
			} 
		}
		// if posOfKing is found then no need to search anymore
		if (posOfKing.Rank != -1){
	                break;
               	}
	}
	
	
	// goal here is to compare all the reachable positions of the opposing player's pieces
	// to the position of the king
	for (int i = 0; i<=7; i++){ // iterate through the board's spaces
		for (int j = 0; j<=7; j++){
			iterator.Rank = IntToRank(i); // this is used to traverse the board in a way that allows for the use of the other functions in ChessRules.c
			iterator.File = IntToFile(j);
			if (LookupPiece(board, iterator) != NULL && LookupPiece(board, iterator)->Color == OppositePlayer(king->Color))
				toCompare = PieceLegalMoves(board, iterator, NULL); // assuming ReachablePositions can handle capture moves that are not the same as how the piece moves when not capturing
			if (toCompare != NULL && toCompare->Length != 0) 
			{
				toCompareMove = toCompare->First; // toCompareMove is used to compare
								// each possible move's destination
								// to the current position of the king
				do { // if a piece can reach the king's current position, then the king is in check (assuming ReachablePositions accounts for pieces of the same color not being able to be on the same position)
					if (toCompareMove->To.Rank == posOfKing.Rank && toCompareMove->To.File == posOfKing.File) { // return 1 if the king can be reached by the piece at [i][j]
						// free memory reserved for the struct pointers that were created
						DeletePiece(king);
						DeleteMoveList(toCompare);
						return 1;
					}
					else { // if not this move check the next available move for the piece
						toCompareMove = toCompareMove->Next;
					}	
				} while (toCompareMove); // go until we check all reachable positions of piece
			}
		}	
	}
	
	// free memory reserved for the struct pointers that were created
	if (toCompare != NULL)
		DeleteMoveList(toCompare);
	if (king != NULL)
		DeletePiece(king);
	return 0; // if no matches are found then return 0, king isn't in check	
}

int Checkmate(t_Board board, t_Player color, t_PieceList pieces) // returns 1 if checkmate, 0 if not
{
	if (!InCheck(board, color)) { // if not in check then also not in checkmate
		return 0;		
	}
	else { // if in check then could be in checkmate
		t_Position iterator; // meant for iterating through the board and finding all the moves
                                // that a piece can make at position indicated by iterator
		t_Piece *king = CreatePiece(color, King); // variable for storing the relevant values of the current player's king
		t_Position posOfKing; //meant to store the location of the king as a Position struct

		posOfKing.Rank = -1;

		for (int i = 0; i<8; i++){ // go through the board and find the king
			for (int j = 0; j<8; j++){
				if (board[i][j] != NULL){
					if (board[i][j]->Color == color && board[i][j]->Type == 0){
						//king = board[i][j]; // store the king in the variable king
						// Converting i and j to rank and file notation
						posOfKing.Rank = IntToRank(i);
                                        	posOfKing.File = IntToFile(j);
						break;		
					}
				}
			}
			// if posOfKing is already found then no need to keep searching
			if (posOfKing.Rank != -1) {
				break;
			}		
		}

		t_MoveList *kingReachable = PieceLegalMoves(board, posOfKing, NULL); // for finding out where the king can go without considering the legality of the move
                t_Move *kingReachableMove = kingReachable->First; // for comparing king's possible destinations with the possible destinations of other units

		int checkCntr = 0; // counts how many possible moves will result in another check, if this equals the length of kingReachable, the king is in checkmate

		while(kingReachableMove){ // go through all of the possible moves of the king
			t_Board virtBoard; // for the purposes of moving the king around to check for check in each of his next possible moves
			CopyBoard(board, virtBoard); // copy the board in the parameters to the virtBoard
			MovePiece(virtBoard, kingReachableMove, 0, color, pieces); // virtually perform one of the king's possible moves
			if (InCheck(virtBoard, color)){ // if the king is in check at this position then increment checkCntr
				checkCntr++;
			}
			kingReachableMove = kingReachableMove->Next; // move on to next move of the king
		}
			
		if (kingReachable->Length != checkCntr){ // if the king can move somewhere without being in check anymore, he is not in checkmate
			if (kingReachable != NULL)
				DeleteMoveList(kingReachable);
			if (king != NULL)
				DeletePiece(king);
			return 0;
		}
			
		for (int i = 0; i<=7; i++){ // go through the board 
			for (int j = 0; j<=7; j++){
				iterator.Rank = IntToRank(i); //converting array notation to rank and file
				iterator.File = IntToFile(j);
				if (LookupPiece(board, iterator) != NULL && LookupPiece(board, iterator)->Color == color && LookupPiece(board, iterator)->Type != 0){ // if there is a piece other than king at [i][j]
					t_MoveList *blockerMoves = PieceLegalMoves(board, iterator, NULL); // find the legal moves of the piece at [i][j]
					if (blockerMoves != NULL && blockerMoves->Length !=0){ // if the piece at [i][j] can move anywhere
						t_Move *blockerMove = blockerMoves->First;
						while(blockerMove){ // iterate through the possible moves of the piece at [i][j]
							t_Board virtBoard1;
							CopyBoard(board, virtBoard1);
							MovePiece(virtBoard1, blockerMove, 0, color, pieces); // virtually perform the piece's move 
							if(!InCheck(virtBoard1, color)){ // if the king is no longer in check as a result of the piece's move then not in checkmate
								DeleteMoveList(blockerMoves);
								return 0;	
							}
							blockerMove = blockerMove->Next;
						}
					}
					if (blockerMoves != NULL){ 
					DeleteMoveList(blockerMoves); // free up the memory for blockerMoves (idk if this is where you do it or if you need to)
					}					
				}
			}	
		}
		if (kingReachable != NULL){
			DeleteMoveList(kingReachable);
		}
		if (king != NULL){
			DeletePiece(king);	
		}
		return 1; // if no moves can be done by pieces other than the king to prevent checkmate, then the king is in checkmate
	}
}

int Stalemate(t_Board board, t_Player color, t_PieceList pieces) // returns 1 if stalemate, 0 if not
{
	if (InCheck(board, color)) { // if in check then not in stalemate
		return 0;
	}
	else{
		// t_Piece *king = CreatePiece(color, King);
		t_Position posOfKing; // stores position of king of the color in the parameter
		
		posOfKing.Rank = -1; // this is initialized to -1 so we can more easily break out of for loops

		for (int i = 0; i<8; i++){ // go through board
			for (int j = 0; j<8; j++){
				if (board[i][j] != NULL){
					if (board[i][j]->Color == color && board[i][j]->Type == 0){ // if there is a king that is of same color as parameter 
						posOfKing.Rank = IntToRank(i); // store position of king in posOfKing
						posOfKing.File = IntToFile(j);
						break;
					}
				}
			}
			if (posOfKing.Rank != -1){ // if king has been found then no need to search anymore
				break;
			}
		}
		
		t_MoveList *kingReachable = PieceLegalMoves(board, posOfKing, NULL); // reachable positions of king
		t_Move *kingReachableMove = kingReachable->First; // move that we are going to check
		int checkCntr = 0; // incremented once one of the king's moves results in it going into check
		if (kingReachableMove){ // if the king has places to go
			while(kingReachableMove){ // go through the entire list of moves of the king
				t_Board virtBoard; // virtual board for virtually moving the king
				CopyBoard(board, virtBoard); // copy the current board to virtBoard
				MovePiece(virtBoard, kingReachableMove, 0, color, pieces);// virtually perform the king's move
				if (InCheck(virtBoard, color)){ // if the king is in check at this position then increment checkCntr
					checkCntr++;
				}
				kingReachableMove = kingReachableMove->Next; // once finished checking this move move on to the next one		
			}
		}

		if (kingReachable->Length == checkCntr){ // if all the king's moves result in check
			if(kingReachable != NULL){ // if kingReachable exists
				DeleteMoveList(kingReachable);
			}
			return 1; // the king is in stalemate
		}		
	}
	return 0; // if the stalemate checking doesn't return 1 then the king isn't in stalemate
}

t_MoveList *CastlingMove(t_Board board, t_Position position, t_PieceList pieces){
	t_Piece *piece = NULL;
        piece = LookupPiece(board, position);
        t_MoveList *Castling = CreateMoveList();
        t_Position from;
        t_Position to;
	t_Move *move;
        t_Position temp;
        t_Position temp1;
	t_Board virtBoard; // virtual board for virtually moving the king
        int rank = position.Rank;
        char file = position.File;
        int color = piece->Color;
        int type = piece->Type;
	
	int Lrook = 0;
	int Rrook = 0;
	if(type == King){
		if(color == White){
			temp.Rank = 1; 
			temp.File = 'a';
			temp1.Rank = 1; 
			temp1.File = 'e';
			if (LookupPiece(board,temp) != NULL && LookupPiece(board,temp1) != NULL && LookupPiece(board,temp)->Color == color && LookupPiece(board,temp)->HasMoved == 0 && LookupPiece(board,temp1)->HasMoved == 0){	/* check if any of the pieces have moved */
				for(int x=1; x<=3; x++){
					temp.Rank = rank;
					temp.File = file - x;
					if(LookupPiece(board,temp) == NULL){
						Lrook++;
					}	
				}
				CopyBoard(board, virtBoard); // copy the current board to virtBoard
				from.Rank = 1;
				from.File = 'e';
				to.Rank = 1;
				to.File = 'c';
				move = CreateMove(from, to); 
				MovePiece(virtBoard, move, 0, color, pieces);// virtually perform the king's move
				DeleteMove(move);
				if(Lrook == 3 && !InCheck(board, color) && !InCheck(virtBoard, color)){		/* check if all the spaces in betwwen are empty */
					to.Rank = rank;
					to.File = file - 4;	/* castling */
					move = CreateMove(from, to);
					AppendMove(Castling, move);
					move->Castling = 1;
				}
			}
			temp.Rank = 1; 
			temp.File = 'h';
			if (LookupPiece(board,temp) != NULL && LookupPiece(board,temp1) != NULL && LookupPiece(board,temp)->Color == color && LookupPiece(board,temp)->HasMoved == 0 && LookupPiece(board,temp1)->HasMoved == 0){	/* check if any of the pieces have moved */
				for(int x=1; x<=2; x++){
					temp.Rank = rank;
					temp.File = file + x;
					if(LookupPiece(board,temp) == NULL){
						Rrook++;
					}	
				}
				CopyBoard(board, virtBoard); // copy the current board to virtBoard
				from.Rank = 1;
				from.File = 'e';
				to.Rank = 1;
				to.File = 'g';
				move = CreateMove(from, to); 
				MovePiece(virtBoard, move, 0, color, pieces);// virtually perform the king's move
				DeleteMove(move);
				if(Rrook == 2 && !InCheck(board, color) && !InCheck(virtBoard, color)){		/* check if all the spaces in betwwen are empty */
					to.Rank = rank;
					to.File = file + 3;	/* castling */
					move = CreateMove(from, to);
					AppendMove(Castling, move);
					move->Castling = 1;
				}
			}
		}
		if(color == Black){
			temp.Rank = 8; 
			temp.File = 'a';
			temp1.Rank = 8; 
			temp1.File = 'e';
			if (LookupPiece(board,temp) != NULL && LookupPiece(board,temp1) != NULL && LookupPiece(board,temp)->Color == color && LookupPiece(board,temp)->HasMoved == 0 && LookupPiece(board,temp1)->HasMoved == 0){	/* check if any of the pieces have moved */
				for(int x=1; x<=3; x++){
					temp.Rank = rank;
					temp.File = file - x;
					if(LookupPiece(board,temp) == NULL){
						Lrook++;
					}	
				}
				CopyBoard(board, virtBoard); // copy the current board to virtBoard
				from.Rank = 8;
				from.File = 'e';
				to.Rank = 8;
				to.File = 'c';
				move = CreateMove(from, to); 
				MovePiece(virtBoard, move, 0, color, pieces);// virtually perform the king's move
				DeleteMove(move);
				if(Lrook == 3 && !InCheck(board, color) && !InCheck(virtBoard, color)){		/* check if all the spaces in betwwen are empty */
					to.Rank = rank;
					to.File = file - 4;	/* castling */
					move = CreateMove(from, to);
					AppendMove(Castling, move);
					move->Castling = 1;
				}
			}
			temp.Rank = 8; 
			temp.File = 'h';
			if (LookupPiece(board,temp) != NULL && LookupPiece(board,temp1) != NULL && LookupPiece(board,temp)->Color == color && LookupPiece(board,temp)->HasMoved == 0 && LookupPiece(board,temp1)->HasMoved == 0){	/* check if any of the pieces have moved */
				for(int x=1; x<=2; x++){
					temp.Rank = rank;
					temp.File = file + x;
					if(LookupPiece(board,temp) == NULL){
						Rrook++;
					}	
				}
				CopyBoard(board, virtBoard); // copy the current board to virtBoard
				from.Rank = 8;
				from.File = 'e';
				to.Rank = 8;
				to.File = 'g';
				move = CreateMove(from, to); 
				MovePiece(virtBoard, move, 0, color, pieces);// virtually perform the king's move
				DeleteMove(move);
				if(Rrook == 2 && !InCheck(board, color) && !InCheck(virtBoard, color)){		/* check if all the spaces in betwwen are empty */
					to.Rank = rank;
					to.File = file + 3;	/* castling */
					move = CreateMove(from, to);
					AppendMove(Castling, move);
					move->Castling = 1;
				}
			}
		}
	}
	return Castling;
}	

	








			

			
		
