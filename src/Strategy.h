/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* Strategy.h: header file for chess strategy			     */
/*********************************************************************/
// Author: Christopher Dao / Ryan Lockie
//
// Modifications:
//
// 4/25/2023 RL  Added AnalyzeCapture and Board Interact Dependency
//
// 4/23/2023 CD  Initial version
//

#ifndef STRATEGY_H
#define STRATEGY_H

#include "ChessObjects.h"
#include "BoardInteract.h"
#include "ChessRules.h"

t_Move *ChooseBestMove(t_MoveList *moves, t_Player color, t_Board board, int loops, t_PieceList pieces);

void AnalyzeCapture(t_Move *move);

void AnalyzeFuture(t_Move *move, t_Board board, int loops, t_Player color, t_PieceList pieces); 

#endif
