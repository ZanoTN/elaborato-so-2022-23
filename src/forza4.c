#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#include<sys/types.h>

#include"../inc/forza4.h"

int8_t *gameFieldArr;
u_int16_t field_hight = 0;
u_int16_t field_width = 0;
char symbols[2];

void passVariableToF4Lib(int8_t *arr, u_int16_t _hight, u_int16_t _width, char symbol_0, char symbol_1) {
	gameFieldArr = arr;
	field_hight = _hight;
	field_width = _width;

	symbols[0] = symbol_0;
	symbols[1] = symbol_1;
}

void generateGameField() {
	int (*mat)[field_width] = (void*) gameFieldArr;

	for(int i=0; i<field_hight; i++) {
		for(int j=0; j<field_width; j++) {
			mat[i][j] = -1;
		}
	}
}

void printGameFieldRaw() {
	int8_t (*mat)[field_width] = (void*) gameFieldArr;

	for(int i=0; i<field_hight; i++) {
		printf("|");
		for(int j=0; j<field_width; j++) {
			printf(" %2d|",mat[i][j]);
		}
		puts("");
	}

	printf("•");
	for(int i=0;i<field_width;i++) {
		printf(" %d •", i);
	}
	puts("");
}

void printGameFieldFormatted() {
	int8_t (*mat)[field_width] = (void*) gameFieldArr;

	for(int i=0; i<field_hight; i++) {
		printf("|");
		for(int j=0; j<field_width; j++) {
			printf(" %c |", (mat[i][j] == -1) ? ' ' : symbols[mat[i][j]]);
		}
		puts("");
	}

	printf("•");
	for(int i=0;i<field_width;i++) {
		printf(" %d •", i);
	}
	puts("");
}

int addCoin(int player, int8_t colum) {
	int8_t (*mat)[field_width] = (void*) gameFieldArr;
	int line_tmp = field_hight - 1;


	if(colum < 0 || colum >= field_width) {
		return -2;
	}

	while(line_tmp >= 0) {
		if(mat[line_tmp][colum] == -1) {
			mat[line_tmp][colum] = player;
			return line_tmp;
		}
		line_tmp--;
	}

	return -1;
}

int checkWin(int line, int column) {
	int8_t (*mat)[field_width] = (void*) gameFieldArr;


	// TODO: check win

	// Orizzontale
	if((1 + sumSequenceDir(line, column, 0, 1, 0, 0) + sumSequenceDir(line, column, 0, 0, 0, 1)) >= 4) {
		return 1;
	}
	// Vertivale
	if((1 + sumSequenceDir(line, column, 1, 0, 0, 0) + sumSequenceDir(line, column, 0, 0, 1, 0)) >= 4) {
		return 1;
	}
	// Obliquo
	if((1 + sumSequenceDir(line, column, 1, 1, 0, 0) + sumSequenceDir(line, column, 0, 0, 1, 1)) >= 4) {
		return 1;
	}
	if((1 + sumSequenceDir(line, column, 1, 0, 0, 1) + sumSequenceDir(line, column, 0, 1, 1, 0)) >= 4) {
		return 1;
	}

	// Check draw
	for(int i=0;i<field_width;i++) {
		if(mat[0][i] == -1) {
			return 0;
		}
	}
	return -1;
}

int sumSequenceDir(int line_coin, int col_coin, int up, int right, int down, int left) {
	int8_t (*mat)[field_width] = (void*) gameFieldArr;

	int end_loop = 0;
	int tmp_line = line_coin;
	int tmp_col = col_coin;
	int counter = 0;
	int8_t idReferenceCoin = mat[line_coin][col_coin];

	while(!end_loop) {
		tmp_line = tmp_line + up - down;
		tmp_col = tmp_col + right - left;

		if(tmp_line < 0 || tmp_line >= field_hight)
			return counter;

		if(tmp_col < 0 || tmp_col >= field_width)
			return counter;

		if(mat[tmp_line][tmp_col] == idReferenceCoin) {
			counter++;
		} else {
			return counter;
		}
	}

	return 0;
}
