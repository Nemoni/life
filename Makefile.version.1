INC_DIR=-I ./inc \
		-I person/inc \
		-I log/inc
OBJ_DIR=./obj
SRC_DIR=.
TARGET_DIR=./bin
TARGET=life
SUBDIRS=person rbtree timer log
LIBS=-lpthread -lreadline -ltermcap

CC=gcc
CGLAG=${INC_DIR} -Wall -O0 -g ${LIBS} 

DIR_SRC:=${wildcard $(SRC_DIR)/*.c}
SRC:=${notdir $(DIR_SRC)}
OBJ:=${patsubst %.c, %.o, $(SRC)}
DES_DIR_OBJ:=${addprefix $(OBJ_DIR)/, $(OBJ)}

ALL_OBJ=${shell find . -name *.o}

.PHONY:all
all:args ${DES_DIR_OBJ} sub_make ${TARGET}

#print the args to debug
.PHONY:args
args:
	@echo " "
	@echo "debug: DIR_SRC:${DIR_SRC}" 
	@echo "           SRC:${SRC} "
	@echo "           OBJ:${OBJ} "
	@echo "   DES_DIR_OBJ:${DES_DIR_OBJ}"
	@echo "       ALL_OBJ:${ALL_OBJ}"

${DES_DIR_OBJ}:${OBJ_DIR}/%.o:${SRC_DIR}/%.c
	mkdir -p ${OBJ_DIR}
	${CC} -c ${CGLAG} $< -o $@

sub_make:
	$(call make_subdir,all)

sub_clean:
	$(call make_subdir,clean)

${TARGET}:${ALL_OBJ}
	mkdir -p ${TARGET_DIR}
	${CC} ${CGLAG} ${ALL_OBJ} -o ${TARGET_DIR}/${TARGET}

.PHONY:clean
clean:sub_clean
	rm -rf ${OBJ_DIR}
	rm -rf ${TARGET_DIR}

define make_subdir
@for subdir in ${SUBDIRS};do \
(cd $$subdir && make $1) \
done;
endef

