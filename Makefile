########################################################################
# Makefile: Makefile for ChessCooker
# 4/28/23 BD: Changed names of tarballs for final release, added make test for debugging
#
# 04/25/2023 CD  Added dependency to UserInterface.o
#
# 04/23/23 Brandon Dinh: Allowed for source code to be in the /src directory,
# 			 added tarball support, allowed for executable to be
# 			 moved to /bin directory
#
# 04/23/2023 CD  Added target for ChessObjects.o, updated rule for
# 		 ChessCooker to link SDL library, updated dependencies 
# 		 for UserInterface.o
# 		 
#
# 04/20/2023 Brandon Dinh: Initial targets/variables for compiling
#
########################################################################

#libs
CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -Wall -std=c11
LFLAGS = -Wall -lm
AR     = ar rc
RANLIB = ranlib
SRC = ./src/

all: ChessCooker mv_bin

test: clean ChessCookerTest mv_bin_test

mv_bin: 
	mv ChessCooker ./bin
	cp ./images/*.bmp ./bin

mv_bin_test:
	mv ChessCookerTest ./bin
	cp ./images/*.bmp ./bin

tar: Chess_V1.0_src.tar.gz ChessCooker mv_bin Chess_V1.0.tar.gz

############ generate object files ######################

#target to generate ChessObjects.o
ChessObjects.o: $(SRC)ChessObjects.c $(SRC)ChessObjects.h
	$(CC) $(CFLAGS) -c $(SRC)ChessObjects.c -o $(SRC)ChessObjects.o

#target to generate ChessRules.o
ChessRules.o: $(SRC)ChessRules.c $(SRC)ChessRules.h $(SRC)ChessObjects.h $(SRC)BoardInteract.h
	$(CC) $(CFLAGS) -c $(SRC)ChessRules.c -o $(SRC)ChessRules.o

#target to generate BoardInteract.o
BoardInteract.o: $(SRC)BoardInteract.c $(SRC)BoardInteract.h $(SRC)ChessObjects.h $(SRC)ChessRules.h
	$(CC) $(CFLAGS) -c $(SRC)BoardInteract.c -o $(SRC)BoardInteract.o

#target to generate LogFile.o (not written yet, modify as needed)
LogFile.o: $(SRC)LogFile.c $(SRC)LogFile.h $(SRC)ChessObjects.h
	$(CC) $(CFLAGS) -c $(SRC)LogFile.c -o $(SRC)LogFile.o

#target to generate UserInterface.o (not written yet, modify as needed)
UserInterface.o: $(SRC)UserInterface.c $(SRC)UserInterface.h $(SRC)ChessObjects.h $(SRC)BoardInteract.h $(SRC)Strategy.h
	$(CC) $(CFLAGS) -c UserInterface.c -o UserInterface.o

#target to generate Strategy.o (not written yet, modify as needed)
Strategy.o: $(SRC)Strategy.c $(SRC)Strategy.h $(SRC)ChessObjects.h $(SRC)ChessRules.h $(SRC)BoardInteract.h
	$(CC) $(CFLAGS) -c $(SRC)Strategy.c -o $(SRC)Strategy.o

#target to generate ChessCooker.o (not all of these dependencies exist yet, modify as needed) 
ChessCooker.o: $(SRC)ChessCooker.c $(SRC)ChessRules.h $(SRC)ChessObjects.h $(SRC)UserInterface.h $(SRC)Strategy.h $(SRC)LogFile.h $(SRC)BoardInteract.h
	$(CC) $(CFLAGS) -c $(SRC)ChessCooker.c -o $(SRC)ChessCooker.o

############## generate executable ###################

#target to generate ChessCooker (program structure might change, modify as needed)
ChessCooker: $(SRC)ChessCooker.o $(SRC)ChessRules.o $(SRC)BoardInteract.o $(SRC)LogFile.o $(SRC)UserInterface.o $(SRC)Strategy.o $(SRC)ChessObjects.o
	$(CC) $(CFLAGS) $(SRC)ChessObjects.o $(SRC)ChessRules.o $(SRC)BoardInteract.o $(SRC)LogFile.o $(SRC)UserInterface.o $(SRC)Strategy.o $(SRC)ChessCooker.o -o ChessCooker -lSDL

ChessCookerTest: $(SRC)ChessCooker.o $(SRC)ChessRules.o $(SRC)BoardInteract.o $(SRC)LogFile.o $(SRC)UserInterface.o $(SRC)Strategy.o $(SRC)ChessObjects.o
	$(CC) $(CFLAGS) -g $(SRC)ChessObjects.o $(SRC)ChessRules.o $(SRC)BoardInteract.o $(SRC)LogFile.o $(SRC)UserInterface.o $(SRC)Strategy.o $(SRC)ChessCooker.o -o ChessCookerTest -lSDL

################ generate tarballs ###################
Chess_V1.0.tar.gz:
	mv ./doc/Chess_SoftwareSpec.pdf .
	gtar cvzf Chess_V1.0.tar.gz README COPYRIGHT INSTALL bin doc images
	mv Chess_SoftwareSpec.pdf ./doc

Chess_V1.0_src.tar.gz:
	gtar cvzf Chess_V1.0_src.tar.gz README COPYRIGHT INSTALL Makefile bin doc src images

#target to clean the directory
clean:
	rm -f $(SRC)*.o ./bin/ChessCooker ./bin/ChessCookerTest Chess_V1.0.tar.gz Chess_V1.0_src.tar.gz ./bin/*.bmp



