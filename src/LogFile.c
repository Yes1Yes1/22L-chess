/*********************************************************************/
/* Project: ChessCooker, for EECS 22L, Spring 2023		     */
/* LogFile.c: source file for editing a log of moves		     */
/*********************************************************************/
// Author: Christopher Dao
//
// Modifications:
// 4/21/2023 CD  Initial version
//

/*** preprocessor directives ***/

#include <stdio.h>
#include <stdlib.h>
#include "LogFile.h"
#include "ChessObjects.h"

/*** function defintions ***/

/* Records a move in the log file */
int RecordMove(t_Piece *piece, t_Position from, t_Position to)
{
	char *OutFileName = "log.txt";
	FILE *OutFile = NULL;
	char type;

	switch (piece->Type)
	{
		case King:
			type = 'K';
			break;

		case Queen:
			type = 'Q';
			break;

		case Rook:
			type = 'R';
			break;

		case Bishop:
			type = 'B';
			break;

		case Knight:
			type = 'N';
			break;

		case Pawn:
			type = ' ';
			break;
		case None:
			break;
	}
	

	if (OutFileName)
	{
		OutFile = fopen(OutFileName, "a");
		if (!OutFile)
		{
			fprintf(stderr, "Can't open file \"%s\" to write!\n", OutFileName);
			perror("Error: ");
			exit(10);
		}
		
		if (piece->Color==White)
		{
			if (piece->Type == Pawn)
				fprintf(OutFile, "%c%d%c%d ", from.File, from.Rank, to.File, to.Rank);
			else
				fprintf(OutFile, "%c%c%d%c%d ", type, from.File, from.Rank, to.File, to.Rank);
		}

		else
		{
			if (piece->Type == Pawn)
				fprintf(OutFile, "%c%d%c%d\n", from.File, from.Rank, to.File, to.Rank);
			else
				fprintf(OutFile, "%c%c%d%c%d\n", type, from.File, from.Rank, to.File, to.Rank);
		}
		
		if (ferror(OutFile))
		{
			printf("\nError while writing to file!\n");
			return 2;
		}

		fclose(OutFile);
	}

	return 0;
}

/* Deletes the log file */
int DeleteLog(const char *fileName)
{
	FILE* file;
	int success = 0;

	file = fopen(fileName, "r");
	if (file)
	{
		success = remove(fileName);
	}

	if (!(success))
	{
		return 1;
	}

	return 0;
}

/* EOF LogFile.c */
