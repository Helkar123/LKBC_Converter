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
void print_anims_lk(LKM2 model) {
	printf("nAnimations: %d\n", model.header.nAnimations);
	int i;
	for (i = 0; i < model.header.nAnimations; i++) {
		printf("[Animation #%d]\n", i);
		printf("AnimID: %d\n", model.animations[i].animID);
		printf("SubAnimID: %d\n", model.animations[i].subAnimID);
		printf("Length: %d\n", model.animations[i].length);
		printf("MoveSpeed: %f\n", model.animations[i].moveSpeed);
		printf("Flags: %d\n", model.animations[i].flags);
		printf("Probability: %d\n", model.animations[i].probability);
		printf("Unused: %d\n", model.animations[i].unused);
		printf("Unknown 1: %d\n", model.animations[i].d1);
		printf("Unknown 2: %d\n", model.animations[i].d2);
		printf("playSpeed: %d\n", model.animations[i].playSpeed);
		printf("MinimumExtent: (%f,%f,%f)\n", model.animations[i].boxA[0],
				model.animations[i].boxA[1], model.animations[i].boxA[2]);
		printf("MaximumExtent: (%f,%f,%f)\n", model.animations[i].boxB[0],
				model.animations[i].boxB[1], model.animations[i].boxB[2]);
		printf("Radius: %f\n", model.animations[i].rad);
		printf("NextAnimation: %d\n", model.animations[i].NextAnimation);
		printf("Index: %d\n", model.animations[i].Index);
		printf("\n");
	}
}

/**
 * Print animations of a M2/BC model.
 * @param model The M2/BC structure.
 */
void print_anims_bc(BCM2 model) {
	printf("nAnimations: %d\n", model.header.nAnimations);
	int i;
	for (i = 0; i < model.header.nAnimations; i++) {
		printf("[Animation #%d]\n", i);
		printf("AnimID: %d\n", model.animations[i].animID);
		printf("SubAnimID: %d\n", model.animations[i].subAnimID);
		printf("timeStart: %d\n", model.animations[i].timeStart);
		printf("timeEnd: %d\n", model.animations[i].timeEnd);
		printf("MoveSpeed: %f\n", model.animations[i].moveSpeed);
		printf("Flags: %d\n", model.animations[i].flags);
		printf("Probability: %d\n", model.animations[i].probability);
		printf("Unused: %d\n", model.animations[i].unused);
		printf("Unknown 1: %d\n", model.animations[i].d1);
		printf("Unknown 2: %d\n", model.animations[i].d2);
		printf("playSpeed: %d\n", model.animations[i].playSpeed);
		printf("MinimumExtent: (%f,%f,%f)\n", model.animations[i].boxA[0],
				model.animations[i].boxA[1], model.animations[i].boxA[2]);
		printf("MaximumExtent: (%f,%f,%f)\n", model.animations[i].boxB[0],
				model.animations[i].boxB[1], model.animations[i].boxB[2]);
		printf("Radius: %f\n", model.animations[i].rad);
		printf("NextAnimation: %d\n", model.animations[i].NextAnimation);
		printf("Index: %d\n", model.animations[i].Index);
		printf("\n");
	}
}

void print_skin(Skin skin) {
	printf("[Skin #%d]\n", skin.header.ID);
	printf("nIndices : %d\n", skin.header.nIndices);
	printf("nTriangles : %d\n", skin.header.nTriangles);
	printf("nProperties : %d\n", skin.header.nProperties);
	printf("nSubmeshes : %d\n", skin.header.nSubmeshes);
	printf("nTextureUnits : %d\n", skin.header.nTextureUnits);
	printf("\n");
}

void print_views(BCM2 model) {
	int i;
	for (i = 0; i < model.header.nViews; i++) {
		int j;
		printf("[View #%d]\n", i);
		printf("nIndices : %d\n", model.views[i].header.nIndices);
		/*
		 for (j=0;j<model.views[i].header.nIndices;j++){
		 printf("[%d]%d\n ",j,model.views[i].Indices[j]);
		 }
		 */

		printf("nTriangles %d, so the real number is %d\n",
				model.views[i].header.nTriangles,
				model.views[i].header.nTriangles / 3);

		printf("nProperties : %d\n", model.views[i].header.nProperties);

		printf("nSubmeshes : %d\n", model.views[i].header.nSubmeshes);
		for (j = 0; j < model.views[i].header.nSubmeshes; j++) {
			printf("\t[Submesh #%d]\n", j);
			printf("\tID : %d\n", model.views[i].Submeshes[j].ID);
			printf("\tStartVertex : %d\n",
					model.views[i].Submeshes[j].StartVertex);
			printf("\tnVertices : %d\n", model.views[i].Submeshes[j].nVertices);
			printf("\tnTriangles : %d\n",
					model.views[i].Submeshes[j].nTriangles);
			printf("\tnBones : %d\n", model.views[i].Submeshes[j].nBones);
			printf("\tStartBones : %d\n",
					model.views[i].Submeshes[j].StartBones);
			printf("\tRootBone : %d\n", model.views[i].Submeshes[j].RootBone);
			printf("\n");
		}

		printf("nTexUnit : %d\n", model.views[i].header.nTextureUnits);
		printf("\n");
	}
}

/**
 * Print the Bones from a BC model
 * @param model
 */
void print_bones(BCM2 model) {
	int i;
	for (i = 0; i < model.header.nBones; i++) {
		printf("[Bone #%d]\n", i);
		int j;
		/*
		printf("Translation:\n");
		printf("\tNumber of Ranges: %d\n", model.bones[i].trans.Ranges.n);
		for (j = 0; j < model.bones[i].trans.Ranges.n; j++) {
			printf("\t\t(%d, %d)\n", model.bonesdata[i].t_ranges.values[j][0],
					model.bonesdata[i].t_ranges.values[j][1]);
		}
		printf("\tNumber of Timestamps: %d", model.bones[i].trans.Times.n);
		printf("\t Number of Keys: %d\n", model.bones[i].trans.Keys.n);
		for (j = 0; j < model.bones[i].trans.Times.n; j++) {
			printf("\t\t%d: (%f, %f, %f)\n", model.bonesdata[i].t_times.values[j],
					model.bonesdata[i].t_keys.values[j][0],
					model.bonesdata[i].t_keys.values[j][1],
					model.bonesdata[i].t_keys.values[j][2]);
		}
		*/

		printf("Rotation:\n");
		printf("\tNumber of Ranges: %d\n", model.bones[i].rot.Ranges.n);
		for (j = 0; j < model.bones[i].rot.Ranges.n; j++) {
			printf("\t\t(%d,%d)\n", model.bonesdata[i].r_ranges.values[j][0],
					model.bonesdata[i].r_ranges.values[j][1]);
		}
		printf("\tNumber of Timestamps: %d", model.bones[i].rot.Times.n);
		printf("\t Number of Keys: %d\n", model.bones[i].rot.Keys.n);
		for (j = 0; j < model.bones[i].rot.Times.n; j++) {
			printf("\t\t%d: (%d, %d, %d, %d)\n",
					model.bonesdata[i].r_times.values[j],
					model.bonesdata[i].r_keys.values[j][0],
					model.bonesdata[i].r_keys.values[j][1],
					model.bonesdata[i].r_keys.values[j][2],
					model.bonesdata[i].r_keys.values[j][3]);
		}
		//printf("Scaling:\n");//TODO
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
