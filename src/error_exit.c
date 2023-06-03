#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/error_exit.h"

void errExit(const char *msg) {
	perror(msg);
	exit(1);
}