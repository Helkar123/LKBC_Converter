/**
 * @file
 * Functions to print M2/Skin structures.
 * Primary use is debugging.
 */
#include <stdio.h>
#include "printer.h"

/**
 * Print animations of a M2/WotLK model.
 * @param lk_model The M2/WotLK structure.
 * Extract it from a file first with reading functions.
 */
void print_anims(LKM2 lk_model) {
	printf("nAnimations: %d\n", lk_model.header.nAnimations);
	int i;
	for (i = 0; i < lk_model.header.nAnimations; i++) {
		printf("//////\n");
		printf("Animation number %d\n", i);
		printf(
				"animID:%d\n subAnimID:%d\n	length:%d\n moveSpeed:%f\n loopType:%d\n",
				lk_model.animations[i].animID, lk_model.animations[0].subAnimID,
				lk_model.animations[i].length, lk_model.animations[0].moveSpeed,
				lk_model.animations[i].loopType);
		printf("flags:%d\n	d1:%d\n	d2:%d\n playSpeed:%d\n rad:%f\n",
				lk_model.animations[i].flags, lk_model.animations[0].d1,
				lk_model.animations[i].d2, lk_model.animations[0].playSpeed,
				lk_model.animations[i].rad);
		printf("NextAnim: %d\n	Index: %d\n\n",
				lk_model.animations[i].NextAnimation,
				lk_model.animations[i].Index);
	}
}
