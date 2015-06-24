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

/**
 * Print a Skin structure.
 * @param skin
 */
void print_skin(Skin skin) {
	printf("[Skin #%d]\n", skin.header.ID);
	printf("nIndices : %d\n", skin.header.nIndices);
	printf("nTriangles : %d\n", skin.header.nTriangles);
	printf("nProperties : %d\n", skin.header.nProperties);
	printf("nSubmeshes : %d\n", skin.header.nSubmeshes);
	printf("nTextureUnits : %d\n", skin.header.nTextureUnits);
	printf("\n");
}

/**
 * Print the Views of a BC model.
 * @param model
 */
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
 * @param flags What is printed depends on the three lower bits. Order : translation, rotation, scaling.
 * Example (prints translation and scaling) : 0b101, so it's 5. Values go from 0 to 7.
 */
void print_bones(BCM2 model, char flags) {
	int i;
	for (i = 0; i < model.header.nBones; i++) {
		printf("[Bone #%d]\n", i);
		int j;
		if (flags & 4) {
			printf("Translation:\n");
			printf("\tNumber of Ranges: %d\n", model.bones[i].trans.Ranges.n);
			for (j = 0; j < model.bones[i].trans.Ranges.n; j++) {
				printf("\t\t(%d, %d)\n",
						model.bonesdata[i].trans.ranges[j][0],
						model.bonesdata[i].trans.ranges[j][1]);
			}
			printf("\tNumber of Timestamps: %d", model.bones[i].trans.Times.n);
			printf("\t Number of Keys: %d\n", model.bones[i].trans.Keys.n);
			for (j = 0; j < model.bones[i].trans.Times.n; j++) {
				printf("\t\t%d: (%f, %f, %f)\n",
						model.bonesdata[i].trans.times[j],
						model.bonesdata[i].trans.keys[j][0],
						model.bonesdata[i].trans.keys[j][1],
						model.bonesdata[i].trans.keys[j][2]);
			}
		}

		if (flags & 2) {
			printf("Rotation:\n");
			printf("\tNumber of Ranges: %d\n", model.bones[i].rot.Ranges.n);
			for (j = 0; j < model.bones[i].rot.Ranges.n; j++) {
				printf("\t\t(%d,%d)\n",
						model.bonesdata[i].rot.ranges[j][0],
						model.bonesdata[i].rot.ranges[j][1]);
			}
			printf("\tNumber of Timestamps: %d", model.bones[i].rot.Times.n);
			printf("\t Number of Keys: %d\n", model.bones[i].rot.Keys.n);
			for (j = 0; j < model.bones[i].rot.Times.n; j++) {
				printf("\t\t%d: (%d, %d, %d, %d)\n",
						model.bonesdata[i].rot.times[j],
						model.bonesdata[i].rot.keys[j][0],
						model.bonesdata[i].rot.keys[j][1],
						model.bonesdata[i].rot.keys[j][2],
						model.bonesdata[i].rot.keys[j][3]);
			}
		}

		if (flags & 1) {
			printf("Scaling:\n");
			printf("\tNumber of Ranges: %d\n", model.bones[i].scal.Ranges.n);
			for (j = 0; j < model.bones[i].scal.Ranges.n; j++) {
				printf("\t\t(%d, %d)\n",
						model.bonesdata[i].scal.ranges[j][0],
						model.bonesdata[i].scal.ranges[j][1]);
			}
			printf("\tNumber of Timestamps: %d", model.bones[i].scal.Times.n);
			printf("\t Number of Keys: %d\n", model.bones[i].scal.Keys.n);
			for (j = 0; j < model.bones[i].scal.Times.n; j++) {
				printf("\t\t%d: (%f, %f, %f)\n",
						model.bonesdata[i].scal.times[j],
						model.bonesdata[i].scal.keys[j][0],
						model.bonesdata[i].scal.keys[j][1],
						model.bonesdata[i].scal.keys[j][2]);
			}
		}
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
		if (lk_bone.rot.Keys.n > 0) {
			for (j = 0; j < lk_bone.rot.Keys.n; j++) {
				printf("\t LKAnimation : %d\n", j);
				if (model.animofs[i].rot.keys[j].n > 0) {
					int k;
					for (k = 0; k < model.animofs[i].rot.keys[j].n; k++) {
						printf("\t\tLKValue : (%d,%d,%d,%d)\n",
								model.bonesdata[i].rot[j].keys[k][0],
								model.bonesdata[i].rot[j].keys[k][1],
								model.bonesdata[i].rot[j].keys[k][2],
								model.bonesdata[i].rot[j].keys[k][3]);
					}
				}
			}
		}
	}
}

/**
 * Print the Vertices.
 * @param model
 */
void print_vertices_lk(LKM2 model) {
	int i;
	for (i = 0; i < model.header.nVertices; i++) {
		printf("%d : (%f,%f,%f)\n", i, model.vertices[i].pos[0],
				model.vertices[i].pos[1], model.vertices[i].pos[2]);
	}
}

/**
 * Print the Vertices.
 * @param model
 */
void print_vertices_bc(BCM2 model) {
	int i;
	for (i = 0; i < model.header.nVertices; i++) {
		printf("%d : (%f,%f,%f)\n", i, model.vertices[i].pos[0],
				model.vertices[i].pos[1], model.vertices[i].pos[2]);
	}
}
