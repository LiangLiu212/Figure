INCLUDE_PATH=include
obj_dir=obj/
bin_dir=bin
TARGET=${bin_dir}/xixi
VPATH=src:include:obj
INCLUDE= ${addprefix -I,${INCLUDE_PATH}}
CC := g++
CPPFLAGS := `root-config --cflags` \
            `root-config --libs` \
            -lm \
            -g  \
            -w -lRooFit -lRooFitCore
vpath %.cxx src
cxxfiles=$(wildcard *.cxx src/*cxx)
OBJS=$(addprefix ${obj_dir}, $(notdir $(notdir $(patsubst %.cxx,%.o,$(cxxfiles)))))


#.SUFFIXES: .cxx .o
#.cxx.o:
#       ${CC} $(INCLUDE) ${CPPFLAGS} -c $<  -o $@
#       mv $@ obj/

ALL : ${OBJS} ${TARGET}

${OBJS} : ${obj_dir}%.o : src/%.cxx
	${CC} $(INCLUDE) ${CPPFLAGS} -c $<  -o $@

${TARGET}: ${OBJS}
	${CC}  $^ ${CPPFLAGS} ${INCLUDE} -o $@


.PHONY: clean
clean:
	rm -rf bin/*
	rm -rf obj/*o
