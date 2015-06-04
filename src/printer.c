/**
 * @file
 * Functions to print M2/Skin structures.
 * Primary use is debugging.
 */
#include <stdio.h>
#include "printer.h"

/**
 * Print animations of a M2/WotLK model.
 * @param model The M2/WotLK structure.
 * Extract it from a file first with reading functions.
 */
void print_anims(LKM2 model) {
	printf("nAnimations: %d\n", model.header.nAnimations);
	int i;
	for (i = 0; i < model.header.nAnimations; i++) {
		printf("//////\n");
		printf("Animation number %d\n", i);
		printf("animID:%d\n subAnimID:%d\n	length:%d\n moveSpeed:%f\n",
				model.animations[i].animID, model.animations[0].subAnimID,
				model.animations[i].length, model.animations[0].moveSpeed);
		printf("flags:%d\n	d1:%d\n	d2:%d\n playSpeed:%d\n rad:%f\n",
				model.animations[i].flags, model.animations[0].d1,
				model.animations[i].d2, model.animations[0].playSpeed,
				model.animations[i].rad);
		printf("NextAnim: %d\n	Index: %d\n\n",
				model.animations[i].NextAnimation, model.animations[i].Index);
	}
}

void print_skin(Skin skin) {
	printf("ID : %d\n", skin.header.ID);
	printf("Bone influences : %d\n", skin.Submeshes[0].boneInfluences);
	printf("nProperties : %d\n", skin.header.nProperties);
	printf("ofsProperties : %d\n", skin.header.ofsProperties);
	printf("Property : %d\n", skin.Properties[0]);
}

void print_views(BCM2 model) {
	int i;
	for (i = 0; i < model.header.nViews; i++) {
		printf("[View #%d]\n", i);
		printf("nIndices : %d\n", model.views[i].header.nIndices);

		printf("nTriangles %d, so the real number is %d\n",
				model.views[i].header.nTriangles,
				model.views[i].header.nTriangles/3);

		printf("nProperties : %d\n", model.views[i].header.nProperties);

		printf("nSubmeshes : %d\n", model.views[i].header.nSubmeshes);

		printf("nTexUnit : %d\n", model.views[i].header.nTextureUnits);
		printf("\n");
	}
}

/**
 * ATM print Translation timestamps of every bone in a LK model
 * @param model
 */
void print_bonesdata(LKM2 model) {
	int i;
	for (i = 0; i < model.header.nBones; i++) {
		LKModelBoneDef lk_bone = model.bones[i];
		int j;
		printf("LKBone : %d\n", i);
		//Translation
		if (lk_bone.trans.Keys.n > 0) {
			for (j = 0; j < lk_bone.trans.Keys.n; j++) {
				printf("\t LKAnimation : %d\n", j);
				if (model.animofs[i].t_keys[j].n > 0) {
					int k;
					for (k = 0; k < model.animofs[i].t_keys[j].n; k++) {
						printf("\t\tLKValue : (%f,%f,%f)\n",
								model.bonesdata[i].t_keys[j].values[k][0],
								model.bonesdata[i].t_keys[j].values[k][1],
								model.bonesdata[i].t_keys[j].values[k][2]);
					}
				}
			}
		}
	}
}

void print_vertices_lk(LKM2 model) {
	int i;
	for (i = 0; i < model.header.nVertices; i++) {
		printf("%d : (%f,%f,%f)\n", i, model.vertices[i].pos[0],
				model.vertices[i].pos[1], model.vertices[i].pos[2]);
	}
}

void print_vertices_bc(BCM2 model) {
	int i;
	for (i = 0; i < model.header.nVertices; i++) {
		printf("%d : (%f,%f,%f)\n", i, model.vertices[i].pos[0],
				model.vertices[i].pos[1], model.vertices[i].pos[2]);
	}
}
