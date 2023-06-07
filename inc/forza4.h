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
/// @return -1 coin not added
int addCoin(int player, int8_t colum);

#endif