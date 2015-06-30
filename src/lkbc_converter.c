/**
 * @file
 * Main file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printer.h"
#include "reading.h"
#include "conversion.h"
#include "writing.h"

/** Skin file extension */
#define SKIN_SUFF ".skin"
/** M2 file extension */
#define M2_EXT ".m2"

/**
 * @return The name of a skin file
 * Example : skin_name("Test.m2", 2) returns "Test02.skin"
 * @param m2_name A string usually given as an argument to the program. Example : "Test.m2"
 * @param number The skin file number.
 * @author ghuysmans
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

/**
 * Main function
 */
int main(int argc, char *argv[]) {
	printf("============================\n");
	printf("= LKBC_Converter by Koward =\n");
	printf("============================\n");
	printf("\tNote : models with .anim files are unsupported.\n");
	printf("\tThe converter will crash or produce a flawed m2 if you try them.\n");
	printf("\n");
	if (argc < 2) {
		fprintf(stderr, "No M2 file specified.\n");
		return -1;
	}

	//Reading files
	printf("Opening M2/WotLK file : \t%s\n", argv[1]);
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
		printf("Opening Skin file : \t\t%s\n", skin_name(argv[1], i));
		skin_files[i] = fopen(skin_name(argv[1], i), "r+b");
		if (skin_files[i] == NULL) {
			fprintf(stderr, "SKIN/LK number %d opening error \r\n", i);
			return -1;
		}
	}

	Skin *skins;
	read_skins(skin_files, &skins, lk_model.header.nViews);
	printf("Model successfully read.\n\n");

	//Converting
	BCM2 bc_model;
	lk_to_bc(lk_model, skins, &bc_model);
	printf("Conversion complete.\n\n");

	//FIXME Debug. Reads the genuine TBC file. Useful to compare the models.
	/*
	FILE *genuine_m2_file = fopen("FrogGenuine.m2", "r+b");
	if (genuine_m2_file == NULL) {
		fprintf(stderr, "Debug file opening error.\nIf you have this error using a release version, please report issue on Github.\n");
		return -1;
	}
	BCM2 genuine_model;
	read_model_bc(genuine_m2_file, &genuine_model);
	print_events_bc(genuine_model);
	*/
	//print_events_lk(lk_model);
	print_cameras_bc(bc_model);

	//Writing
	char new_name[64] = "BC_";
	strcat(new_name, argv[1]);
	printf("Output name : %s\n", new_name);
	FILE *bc_m2_file = fopen(new_name, "w+b");
	write_model(bc_m2_file, &bc_model);
	printf("Model successfully written.\n");

	//Closing files
	printf("\n");
	printf("Closing streams...\n");
	for (i = 0; i < lk_model.header.nViews; i++) {
		fclose(skin_files[i]);
	}
	fclose(lk_m2_file);
	fclose(bc_m2_file);
	return 0;
}
