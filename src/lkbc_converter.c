/**
 * @file
 * Main file
 */

#include <stdio.h>
#include <stdlib.h>
#include "reading.h"

int main(int argc, char *argv[]) {
	printf("LKBC_Converter by Koward\n");
	if (argc < 2) {
		fprintf(stderr, "No M2 file specified.\n");
		return -1;
	}

	FILE *lk_m2 = fopen(argv[1], "r+b");
	if (lk_m2 == NULL) {
		fprintf(stderr, "M2 opening error \n");
	}

	struct LKM2File lk_model;

	read_model(lk_m2, &lk_model);

	fclose(lk_m2);
	return 0;
}
