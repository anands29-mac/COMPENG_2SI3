CC=g++
CFLAGS=-I. -lm -g -std=c++11
DEPS = *.h
OBJTBC = objPos.o objPosStack.o DLinkedList.o cmdQueue.o Test.o  
OBJ = objPos.o objPosDLinkedList.o objPosStack.o objPosStackModel.o DLinkedList.o cmdQueue.o cmdQueueModel.o Test.o  

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Lab3: $(OBJ)
	$(CC) -o $@ ${OBJ} $(CFLAGS)

test:	testLab3
testLab3:
	./run.sh

.PHONY: clean

clean:
	$(RM) ${OBJTBC} *.exe *.xml Lab3
