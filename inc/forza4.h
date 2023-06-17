#ifndef FORZA4_H_
#define FORZA4_H_

extern int8_t *gameFieldArr;
extern u_int16_t field_hight;
extern u_int16_t field_width;
extern char symbols[2];


/// @brief Pass all variable
void passVariableToF4Lib(int8_t *arr, u_int16_t _hight, u_int16_t _width, char symbol_0, char symbol_1);

/// @brief Generate a game filed
void generateGameField();

/// @brief Print game filed row
void printGameFieldRaw();

/// @brief Print game filed formatted with symbols 
void printGameFieldFormatted();

/// @brief Add coin to colum
/// @param player id player
/// @param colum nr. colum
/// @return -1: Column full, -2, invalid column, in case of success return the line of coin
int addCoin(int player, int8_t colum);

/// @brief Check win from the last coin added
/// @param line position line
/// @param column position column
/// @return 1 win, 0 not win, -1 draw	
int checkWin(int line, int column);

/// @brief 
/// @param line_coin 
/// @param col_coin 
/// @param up 
/// @param right 
/// @param down 
/// @param left 
/// @return 
int sumSequenceDir(int line_coin, int col_coin, int up, int right, int down, int left);


#endif