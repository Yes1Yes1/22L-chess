/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* LogFile.h: header file for editing a log of moves		     */
/*********************************************************************/
// Author: Christopher Dao
//
// Modifications:
// 4/21/2023 CD  Initial version
//

#ifndef LOGFILE_H
#define LOGFILE_H

#include "ChessObjects.h"

int RecordMove(t_Piece *piece, t_Position from, t_Position to);

int DeleteLog(const char *fileName);

#endif
/* EOF LogFile.h */
