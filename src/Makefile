CXX = gcc

CXXFLAGS = -Wall -MMD -Werror=vla -g

EXEC = waterloop

OBJECTS = SomeFile.o

network/%.o: network/%.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 
-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
