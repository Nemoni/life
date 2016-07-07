INC_DIR=-I ./inc
OBJ_DIR=./obj
SRC_DIR=.
TARGET_DIR=./bin
TARGET=life

CC=gcc
CGLAG=${INC_DIR} -Wall -O0 -g 

DIR_SRC:=${wildcard $(SRC_DIR)/*.c}
SRC:=${notdir $(DIR_SRC)}
OBJ:=${patsubst %.c, %.o, $(SRC)}
DES_DIR_OBJ:=${addprefix $(OBJ_DIR)/, $(OBJ)}

ALL_OBJ=${shell find . -name *.o}

.PHONY:all
all:args ${DES_DIR_OBJ} ${TARGET}

#print the args to debug
.PHONY:args
args:
	@echo "debug: DIR_SRC:${DIR_SRC}" 
	@echo "           SRC:${SRC} "
	@echo "           OBJ:${OBJ} "
	@echo "   DES_DIR_OBJ:${DES_DIR_OBJ}"
	@echo "       ALL_OBJ:${ALL_OBJ}"
	@echo " "

${DES_DIR_OBJ}:${OBJ_DIR}/%.o:${SRC_DIR}/%.c
	mkdir -p ${OBJ_DIR}
	${CC} -c ${CGLAG} $< -o $@


${TARGET}:${ALL_OBJ}
	mkdir -p ${TARGET_DIR}
	${CC} ${CGLAG} ${ALL_OBJ} -o ${TARGET}

.PHONY:clean
clean:
	rm -rf ${OBJ_DIR}
	rm -rf ${TARGET_DIR}
	rm ${TARGET}
