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

	FILE *lk_m2_file = fopen(argv[1], "r+b");
	if (lk_m2_file == NULL) {
		fprintf(stderr, "M2 opening error \n");
	}

	struct LKM2File lk_model;

	read_model(lk_m2_file, &lk_model);

	/*FIXME
	 FILE *skin_file = fopen(, "r+b");
	 if (skin_file == NULL) {
	 fprintf(stderr, "SKIN/LK opening error \r\n");
	 }

	 fclose(skin_file);
	 */
	fclose(lk_m2_file);
	return 0;
}
