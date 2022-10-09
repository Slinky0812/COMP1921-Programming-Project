C=gcc #compiler
CFLAGS=-g -std=c99 -fmax-errors=1 -Wall -Werror #compiler flags used when compiling
MODULES=fileOperations.o errorCheck.o pgmOperations.o #object files used in all main files
MAINS=pgmEcho.o pgmComp.o pgma2b.o pgmb2a.o pgmReduce.o pgmTile.o pgmAssemble.o #all main object files
TARGETS=pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble #names to run main files when compiled successfully

#enables make all
all:	${TARGETS}

#removes all object files created
clean:
	rm ${TARGETS} ${MAINS} ${MODULES}

#compiles pgmEcho
pgmEcho:	pgmEcho.o ${MODULES}
	${CC}	${CCFLAGS}	-o pgmEcho	pgmEcho.o ${MODULES}

#compiles pgmComp
pgmComp:	pgmComp.o ${MODULES}
	${CC}	${CCFLAGS} -o pgmComp	pgmComp.o ${MODULES}

#compiles pgma2b
pgma2b:		pgma2b.o ${MODULES}
	${CC}	${CCFLAGS} -o pgma2b	pgma2b.o ${MODULES}

#compiles pgmb2a
pgmb2a:		pgmb2a.o ${MODULES}
	${CC}	${CCFLAGS} -o pgmb2a	pgmb2a.o ${MODULES}

#compiles pgmReduce
pgmReduce:		pgmReduce.o ${MODULES}
	${CC}	${CCFLAGS} -o pgmReduce	pgmReduce.o ${MODULES}

#compiles pgmTile
pgmTile:	pgmTile.o ${MODULES}
	${CC}	${CCFLAGS} -o pgmTile	pgmTile.o ${MODULES}

#compiles pgmAssemble
pgmAssemble:	pgmAssemble.o ${MODULES}
	${CC}	${CCFLAGS} -o pgmAssemble	pgmAssemble.o ${MODULES}