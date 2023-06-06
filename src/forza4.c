#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#include<sys/types.h>

#include"../inc/forza4.h"

int8_t *gameFieldArr;
u_int16_t hight = 0;
u_int16_t width = 0;

void passVariableToF4Lib(int8_t *arr, u_int16_t _hight, u_int16_t _width) {
	gameFieldArr = arr;
	hight = _hight;
	width = _width;
}

void generateGameField() {
	int (*mat)[width] = (void*) gameFieldArr;

	for(int i=0; i<hight; i++) {
		for(int j=0; j<width; j++) {
			mat[i][j] = -1;
		}
	}
}

void printGameFieldRaw() {
	int8_t (*mat)[width] = (void*) gameFieldArr;

	for(int i=0; i<hight; i++) {
		printf("|");
		for(int j=0; j<width; j++) {
			printf(" %2d|",mat[i][j]);
		}
		puts("");
	}

	printf("•");
	for(int i=0;i<width;i++) {
		printf(" %d •", i);
	}
	puts("");
}

void printGameFieldFormatted(char symbol_1, char symbol_2) {
	int8_t (*mat)[width] = (void*) gameFieldArr;

	char symbols[] = {symbol_1, symbol_2};

	for(int i=0; i<hight; i++) {
		printf("|");
		for(int j=0; j<width; j++) {
			printf(" %c |", (mat[i][j] == -1) ? ' ' : symbols[mat[i][j]]);
		}
		puts("");
	}

	printf("•");
	for(int i=0;i<width;i++) {
		printf(" %d •", i);
	}
	puts("");
}

int addCoin(int player, int8_t colum) {
	int8_t (*mat)[width] = (void*) gameFieldArr;
	int line_tmp = hight - 1;

	// TODO: Verificare se la colonna esiste

	while(line_tmp >= 0) {
		if(mat[line_tmp][colum] == -1) {
			mat[line_tmp][colum] = player;
			return 0;
		}
		line_tmp--;
	}

	return -1;
}