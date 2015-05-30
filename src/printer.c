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
		printf("animID:%d\n subAnimID:%d\n	length:%d\n moveSpeed:%f\n",
				lk_model.animations[i].animID, lk_model.animations[0].subAnimID,
				lk_model.animations[i].length,
				lk_model.animations[0].moveSpeed);
		printf("flags:%d\n	d1:%d\n	d2:%d\n playSpeed:%d\n rad:%f\n",
				lk_model.animations[i].flags, lk_model.animations[0].d1,
				lk_model.animations[i].d2, lk_model.animations[0].playSpeed,
				lk_model.animations[i].rad);
		printf("NextAnim: %d\n	Index: %d\n\n",
				lk_model.animations[i].NextAnimation,
				lk_model.animations[i].Index);
	}
}

void print_skin(Skin skin) {
	printf("ID : %d\n", skin.header.ID);
	printf("Bone influences : %d\n", skin.Submeshes[0].boneInfluences);
	printf("nProperties : %d\n", skin.header.nProperties);
	printf("ofsProperties : %d\n", skin.header.ofsProperties);
	printf("Property : %d\n", skin.Properties[0]);
}

/**
 * ATM print Translation timestamps of every bone in a LK model
 * @param lk_model
 */
void print_bonesdata(LKM2 lk_model) {
	int i;
	for (i = 0; i < lk_model.header.nBones; i++) {
		LKModelBoneDef lk_bone = lk_model.bones[i];
		int j;
		printf("LKBone : %d\n", i);
		//Translation
		if (lk_bone.trans.Keys.n > 0) {
			for (j = 0; j < lk_bone.trans.Keys.n; j++) {
				printf("\t LKAnimation : %d\n", j);
				if (lk_model.animofs[i].t_keys[j].n > 0) {
					int k;
					for (k = 0; k < lk_model.animofs[i].t_keys[j].n; k++) {
						printf("\t\tLKValue : (%f,%f,%f)\n",
								lk_model.bonesdata[i].t_keys[j].values[k][0],
								lk_model.bonesdata[i].t_keys[j].values[k][1],
								lk_model.bonesdata[i].t_keys[j].values[k][2]);
					}
				}
			}
		}
	}
}
