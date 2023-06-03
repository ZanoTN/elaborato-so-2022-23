#ifndef PRINTLOG_H_ 
#define PRINTLOG_H_
#define LOG_ENABLE 1
#define LOG_SERVER 100
#define LOG_CLIENT 101

/// @brief Print log only if the varaible is enable (=1)
/// @param type Select if is SERVER or CLIENT
/// @param format Sring to print
void plog(int type, char* format, ...);

/// @brief Convert integer number into octal, hex, etc 
char *convert(unsigned int, int);

#endif