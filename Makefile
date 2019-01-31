CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -g
EXEC = PNG-BMP
OBJECTS = diffBMP.o bitmap_image.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
