CC = g++
CFLAGS = -I. -I../inc -g -std=c++11
OBJTBC = objPos.o DLinkedList.o objPosDoubleHashing.o objPosQuadHashing.o GameMechs.o MacUILib.o Player.o ItemBin.o ScreenDrawer.o MainGame.o 
OBJ = objPos.o DLinkedList.o ../obj/objPosDLinkedList.o ../obj/objPosStack.o ../obj/cmdQueue.o ../obj/objPosBST.o objPosDoubleHashing.o objPosQuadHashing.o GameMechs.o MacUILib.o Player.o ItemBin.o ScreenDrawer.o MainGame.o  
DEPS = *.h

ifeq (${OS}, Windows_NT)
	OSSETTING = -DWINDOWS
else
	OSSETTING = -DPOSIX
	POSTLINKER = -lncurses   ## uncomment this if on Linux
endif

EXEC = ../bin/Project

%.o: %.cpp $(DEPENDS)
	$(CC) ${OSSETTING} -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC)  ${OSSETTING} -o $@ ${OBJ} $(CFLAGS) ${POSTLINKER}

clean :
	rm -rf ${OBJTBC} ${EXEC} ${EXEC}.exe
