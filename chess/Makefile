CXX=g++
CXXFLAGS=-std=c++14 -Wall -Werror -g -MMD -Werror=vla
EXEC=chess
OBJECTS= bishop.o board.o boarddisplay.o computer.o empty.o king.o knight.o main.o pawn.o piece.o player.o queen.o rook.o
DEPENDS=${OBJECTS:.o=.d}
	
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
