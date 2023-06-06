#ifndef FORZA4_H_
#define FORZA4_H_

extern int8_t *gameFieldArr;
extern u_int16_t hight;
extern u_int16_t width;

/// @brief Pass all variable
void passVariableToF4Lib(int8_t *arr, u_int16_t _hight, u_int16_t _width);

/// @brief Generate a game filed
void generateGameField();

/// @brief Print game filed row
void printGameFieldRaw();

/// @brief Print game filed formatted with symbols 
void printGameFieldFormatted(char symbol_1, char symbol_2);

/// @brief Add coin to colum
/// @param player id player
/// @param colum nr. colum
/// @return -1 coin not added
int addCoin(int player, int8_t colum);

#endif