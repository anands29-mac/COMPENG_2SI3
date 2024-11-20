CC=g++
CFLAGS=-I. -lm -g -std=c++11
DEPS = *.h
OBJTBC = objPos.o objPosQuadHashing.o objPosDoubleHashing.o Test.o  
OBJ = objPos.o objPosQuadHashing.o objPosDoubleHashing.o objPosQuadHashingModel.o objPosDoubleHashingModel.o Test.o  

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Lab5: $(OBJ)
	$(CC) -o $@ ${OBJ} $(CFLAGS)

test:	testLab5
testLab5:
	./run.sh

.PHONY: clean

clean:
	$(RM) ${OBJTBC} *.exe *.xml Lab5
