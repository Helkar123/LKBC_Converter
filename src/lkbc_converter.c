/**
 * @file
 * Main file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"
#include "printer.h"

#define SKIN_SUFF ".skin"
#define M2_EXT ".m2"

/**
 * @return The name of a skin file
 * Example : skin_name("Test.m2", 2) returns "Test02.skin"
 * @param m2_name A string usually given as an argument to the program. Example : "Test.m2"
 * @param number The skin file number.
 */
char* skin_name(char *m2_name, int number) {
	size_t m2_name_length = strlen(m2_name);
	char skin_number[2];
	sprintf(skin_number, "%d", number);
	char *s = malloc(
			m2_name_length - strlen(M2_EXT) + 2 + strlen(SKIN_SUFF) + 1);
	char *p = s + m2_name_length - 3;
	strcpy(s, m2_name);
	strcpy(p, "0");
	p++;
	strcpy(p, skin_number);
	p++;
	strcpy(p, SKIN_SUFF);
	return s;
}

int main(int argc, char *argv[]) {
	printf("LKBC_Converter by Koward\n");
	if (argc < 2) {
		fprintf(stderr, "No M2 file specified.\n");
		return -1;
	}

	FILE *lk_m2_file = fopen(argv[1], "r+b");
	if (lk_m2_file == NULL) {
		fprintf(stderr, "M2 opening error \n");
		return -1;
	}

	LKM2 lk_model;

	read_model(lk_m2_file, &lk_model);

	FILE **skin_files;
	skin_files = malloc(lk_model.header.nViews * sizeof(FILE *));
	int i;
	for (i = 0; i < lk_model.header.nViews; i++) {
		printf("Opening Skin file : %s\n", skin_name(argv[1], i));
		skin_files[i] = fopen(skin_name(argv[1], i), "r+b");
		if (skin_files[i] == NULL) {
			fprintf(stderr, "SKIN/LK number %d opening error \r\n", i);
			return -1;
		}
	}
	Skin *skins;
	read_skins(skin_files, &skins, lk_model.header.nViews);

	//Closing files
	for (i = 0; i < lk_model.header.nViews; i++) {
		fclose(skin_files[i]);
	}
	fclose(lk_m2_file);
	return 0;
}
