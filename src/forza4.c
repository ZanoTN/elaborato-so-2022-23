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