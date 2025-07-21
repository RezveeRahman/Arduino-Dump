#
# @Author: Rezvee Rahman
# @Date:   07-18-2025
#
# @details: This make file is responsible for flashing
#           binaries to the arduino.
#
#           Targets may vary, I'm using arduino R3.
#           Partly because Renessas compilers are
#           not free and originally wanted to target
#           R4 boards but can't due to this.
#
SHELL=/bin/bash

CC=avr-gcc
CC2=avr-objcopy
FLASH=avrdude
CPU_SPEED=-DF_CPU=1600000UL # 16MHz
ARCH=ATMEGA328P
FLASH_FLAGS=-F -V -c
TARGET_ARCH=-mmcu=atmega328p
C_FLAGS=-Os ${CPU_SPEED} ${TARGET_ARCH}

# INPUTS
DEV= # - device connection (e.g. /dev/ttyACM0)
BAUD= # - Baud rate (e.g. 115200)




# ENV VARS
SRC:=./src
OBJ:=${SRC}/.obj
VAR:=./bin

SRC_FILES:=main.c
OBJ_FILES:=$(patsubst %.c,%.o, ${SRC_FILES})
BIN_DIR:=./bin
BIN_FILE:=${BIN_DIR}/main.bin
HEX_FILE:=${BIN_DIR}/main.hex

# Recipes
.PHONY: build clean info obj flash
flash : build # make sure to specify DEV and BAUD
	@printf "\033[38;5;2mFlashing to the arduino target:\033[0m\n";
	@printf "You'll need sudo permissions to flash -"
	@sudo ${FLASH} ${FLASH_FLAGS} arduino -p ${ARCH} -P ${DEV} -b ${BAUD} \
			-U flash:w:${HEX_FILE}


build : $(OBJ_FILES)
	@printf "\033[38;5;2mCreating binary objects:\033[0m\n"
	@${CC} -o ${BIN_FILE} ${OBJ}/${OBJ_FILES}
	@${CC2} -O ihex -R .eeprom ${BIN_FILE} ${HEX_FILE}


$(OBJ_FILES) : %.o : ${SRC}/%.c
	@printf "\033[38;5;2mCreating object output\033[0m";
	@printf "\033[38;5;2mCreating object directory: ${OBJ} \033[0m\n";
	@mkdir -p ${OBJ};
	@${CC} ${C_FLAGS} -c $< -o ${OBJ}/$@

clean :
	@printf "\033[38;5;1mCleaning up ${OBJ}\033[0m\n";
	@rm -rf ${OBJ};
	@printf "\033[38;5;1mCleaning up ${VAR}\033[0m\n";
	@rm -rf ${VAR}/*;

info :
	@printf "\033[38;5;4mUsing the Following setup:\033[0m\n";
	@printf "\033[38;5;3m\tUsing Compiler: ${CC}\033[0m\n";
	@printf "\033[38;5;3m\tWith flags:     ${C_FLAGS} \033[0m\n";
	@printf "\033[38;5;3m\tSource Files:   ${SRC_FILES}\033[0m\n"
	@printf "\033[38;5;3m\tObject Files:   ${OBJ_FILES}\033[0m\n"

input :
	@printf "\033[38;5;2mHere Checking inputs:\033[0m\n";
	@printf "\033[38;5;2m\tBAUD=${BAUD}\033[0m\n";
	@printf "\033[38;5;2m\tDEV=${DEV}\033[0m\n";
	@printf "\033[38;5;2m\t=\033[0m\n";
	@printf "\033[38;5;2m\t=\033[0m\n";