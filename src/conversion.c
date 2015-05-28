/**
 * @file
 * Conversion functions
 */

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

/**
 * Header conversion
 * @param ptr Pointer to the BCM2 file which will be modified.
 * @param lk_header LK M2 Header.
 * @return A TBC Header.
 */
int header_converter(BCM2 *ptr, LKModelHeader lk_header) {
	ptr->header.id = lk_header.id;
	//TODO version=0x107 if the model has particles
	ptr->header.version = 0x104;
	ptr->header.nameLength = lk_header.nameLength;
	ptr->header.nameOfs = 0x150;
	ptr->header.GlobalModelFlags = lk_header.GlobalModelFlags;
	ptr->header.nGlobalSequences = lk_header.nGlobalSequences;
	ptr->header.ofsGlobalSequences = lk_header.ofsGlobalSequences;
	ptr->header.nAnimations = lk_header.nAnimations;
	ptr->header.ofsAnimations = lk_header.ofsAnimations;
	ptr->header.nAnimationLookup = lk_header.nAnimationLookup;
	ptr->header.ofsAnimationLookup = lk_header.ofsAnimationLookup;
	ptr->header.nPlayableAnimationLookup = 0xcb; //Placeholder
	ptr->header.ofsPlayableAnimationLookup = 0x00; //Determine where you insert the Data block from above
	ptr->header.nBones = lk_header.nBones;
	ptr->header.ofsBones = lk_header.ofsBones;
	ptr->header.nKeyBoneLookup = lk_header.nKeyBoneLookup;
	ptr->header.ofsKeyBoneLookup = lk_header.ofsKeyBoneLookup;
	ptr->header.nVertices = lk_header.nVertices;
	ptr->header.ofsVertices = lk_header.ofsVertices;
	ptr->header.nViews = lk_header.nViews;
	ptr->header.ofsViews = 0x00;
	ptr->header.nColors = lk_header.nColors;
	ptr->header.ofsColors = lk_header.ofsColors;
	ptr->header.nTextures = lk_header.nTextures;
	ptr->header.ofsTextures = lk_header.ofsTextures;
	ptr->header.nTransparency = lk_header.nTransparency;
	ptr->header.ofsTransparency = lk_header.ofsTransparency;
	ptr->header.nI = 0x00;
	ptr->header.ofsI = 0x00;
	ptr->header.nTexAnims = lk_header.nTexAnims;
	ptr->header.ofsTexAnims = lk_header.ofsTexAnims;
	ptr->header.nTexReplace = lk_header.nTexReplace;
	ptr->header.ofsTexReplace = lk_header.ofsTexReplace;
	ptr->header.nRenderFlags = lk_header.nRenderFlags;
	ptr->header.ofsRenderFlags = lk_header.ofsRenderFlags;
	ptr->header.nBoneLookupTable = lk_header.nBoneLookupTable;
	ptr->header.ofsBoneLookupTable = lk_header.ofsBoneLookupTable;
	ptr->header.nTexLookup = lk_header.nTexLookup;
	ptr->header.ofsTexLookup = lk_header.ofsTexLookup;
	ptr->header.nTexUnitLookup = lk_header.nTexUnitLookup;
	ptr->header.ofsTexUnitLookup = lk_header.ofsTexUnitLookup;
	ptr->header.nTransparencyLookup = lk_header.nTransparencyLookup;
	ptr->header.ofsTransparencyLookup = lk_header.ofsTransparencyLookup;
	ptr->header.nTexAnimLookup = lk_header.nTexAnimLookup;
	ptr->header.ofsTexAnimLookup = lk_header.ofsTexAnimLookup;
	ptr->header.nBoundingTriangles = lk_header.nBoundingTriangles;
	ptr->header.ofsBoundingTriangles = lk_header.ofsBoundingTriangles;
	ptr->header.nBoundingVertices = lk_header.nBoundingVertices;
	ptr->header.ofsBoundingVertices = lk_header.ofsBoundingVertices;
	ptr->header.nBoundingNormals = lk_header.nBoundingNormals;
	ptr->header.ofsBoundingNormals = lk_header.ofsBoundingNormals;
	ptr->header.nAttachments = lk_header.nAttachments;
	ptr->header.ofsAttachments = lk_header.ofsAttachments;
	ptr->header.nAttachLookup = lk_header.nAttachLookup;
	ptr->header.ofsAttachLookup = lk_header.ofsAttachLookup;
	ptr->header.nAttachments_2 = lk_header.nAttachments_2;
	ptr->header.ofsAttachments_2 = lk_header.ofsAttachments_2;
	ptr->header.nLights = lk_header.nLights;
	ptr->header.ofsLights = lk_header.ofsLights;
	ptr->header.nCameras = lk_header.nCameras;
	ptr->header.ofsCameras = lk_header.ofsCameras;
	ptr->header.nCameraLookup = lk_header.nCameraLookup;
	ptr->header.ofsCameraLookup = lk_header.ofsCameraLookup;
	ptr->header.nRibbonEmitters = lk_header.nRibbonEmitters;
	ptr->header.ofsRibbonEmitters = lk_header.ofsRibbonEmitters;
	ptr->header.nParticleEmitters = lk_header.nParticleEmitters;
	ptr->header.ofsParticleEmitters = lk_header.ofsParticleEmitters;
	int i = 0;
	for (i = 0; i < 14; i++) {
		ptr->header.floats[i] = lk_header.floats[i];
	}
	return 0;
}

/**
 * Converts animations
 * @param ptr Pointer to BC M2 structure
 * @param lk_m2 LK M2 structure (no need for pointer as we should not modify it)
 * @return 0 if successful
 */
int animations_converter(BCM2 *ptr, LKM2 lk_m2) {
	//Animation Sequence (also known as the easy part)
	ptr->animations = malloc(ptr->header.nAnimations * sizeof(ModelAnimation));
	uint32 timeline = 0;
	int i;
	for (i = 0; i < ptr->header.nAnimations; i++) {
		timeline += 3333; //FIXME Time between anims. I chose a random number. Not sure how Blizzard decided its values. Should not matter.
		ptr->animations[i].animID = lk_m2.animations[i].animID;
		ptr->animations[i].timeStart = timeline;
		timeline += lk_m2.animations[i].length;
		ptr->animations[i].timeEnd = timeline;
		ptr->animations[i].moveSpeed = lk_m2.animations[i].moveSpeed;
		ptr->animations[i].loopType = 0; //FIXME I really don't know where this information disappeared in LK. There is no doc.
		ptr->animations[i].flags = lk_m2.animations[i].flags;
		ptr->animations[i].d1 = lk_m2.animations[i].d1;
		ptr->animations[i].d2 = lk_m2.animations[i].d2;
		ptr->animations[i].playSpeed = lk_m2.animations[i].playSpeed;
		int j;
		for (j = 0; j < 3; j++) {
			ptr->animations[i].boxA[j] = lk_m2.animations[i].boxA[j];
			ptr->animations[i].boxB[j] = lk_m2.animations[i].boxB[j];
		}
		ptr->animations[i].rad = lk_m2.animations[i].rad;
		ptr->animations[i].NextAnimation = lk_m2.animations[i].NextAnimation;
		ptr->animations[i].Index = lk_m2.animations[i].Index;
	}

	ptr->bones = malloc(ptr->header.nBones * sizeof(ModelBoneDef));

	//BonesDataBlock
	ptr->bonesdata = malloc(ptr->header.nBones * sizeof(BonesDataBlock));
	for (i = 0; i < ptr->header.nBones; i++) {
		printf("Bone : %d\n", i);

		//translation
		if (lk_m2.bones[i].trans.Times.n > 0) {
			int j;
			int times_index = 0; //Not reset when we finish the extraction of timestamps from 1 animation
			int keys_index = 0;	//Not reset when we finish the extraction of keys from 1 animation
			ptr->bonesdata[i].t_ranges.values = malloc(
					(ptr->header.nAnimations + 1) * sizeof(Range));
			ptr->bonesdata[i].t_ranges.values[ptr->header.nAnimations][0] = 0;//No idea why the last (int,int) is always 0
			ptr->bonesdata[i].t_ranges.values[ptr->header.nAnimations][1] = 0;

			int t_times_size = 0;//Number of Timestamps (equal to the number of keys) for this bone
			for (j = 0; j < lk_m2.header.nAnimations; j++) {
				t_times_size += lk_m2.animofs[i].t_times[j].n;
			}

			ptr->bones[i].trans.Times.n = t_times_size;
			printf("Number of Timestamps&Keys for this bone : %d\n",
					t_times_size);

			ptr->bonesdata[i].t_times.values = malloc(
					t_times_size * sizeof(uint32));

			ptr->bonesdata[i].t_keys.values = malloc(
					t_times_size * sizeof(Vec3D));

			int intertime;

			for (j = 0; j < ptr->header.nAnimations; j++) {
				printf("\tAnimation : %d\n", j);	//FIXME DEBUG
				intertime = times_index;
				if (lk_m2.animofs[i].t_times[j].n > 0) {//TIMESTAMPS & INTERPOLATION RANGE
					ptr->bonesdata[i].t_ranges.values[j][0] = intertime;//Range : keep the records FIXME
					int k;
					for (k = 0; k < lk_m2.animofs[i].t_times[j].n; k++) {//Take each value for this anim and put it in the BC data
						ptr->bonesdata[i].t_times.values[times_index] =
								ptr->animations[j].timeStart
										+ lk_m2.bonesdata[i].t_times[j].values[k];//Start Timestamp + animation-relative time
						printf("\t\tAdded Timestamp : %d\n",
								ptr->bonesdata[i].t_times.values[times_index]);
						times_index++;
						intertime++;
					}
					ptr->bonesdata[i].t_ranges.values[j][1] = intertime - 1;
					intertime++;
				} else {
					ptr->bonesdata[i].t_ranges.values[j][0] = intertime - 1;
					ptr->bonesdata[i].t_ranges.values[j][1] = intertime;
				}

				if (lk_m2.animofs[i].t_keys[j].n > 0) {	//KEYS
					int k;
					for (k = 0; k < lk_m2.animofs[i].t_keys[j].n; k++) {//Take each value for this anim and put it in the BC data
						int m;
						for (m = 0; m < 3; m++) {
							ptr->bonesdata[i].t_keys.values[keys_index][m] =
									lk_m2.bonesdata[i].t_keys[j].values[k][m];//Start Timestamp + animation-relative time
						}
						printf("\t\tAdded Vector : (%f,%f,%f)\n",
								ptr->bonesdata[i].t_keys.values[keys_index][0],
								ptr->bonesdata[i].t_keys.values[keys_index][1],
								ptr->bonesdata[i].t_keys.values[keys_index][2]);
						keys_index++;
					}
				}
				printf(
						"\t\tInterpolation range : (%d,%d)\n",	//FIXME DEBUG
						ptr->bonesdata[i].t_ranges.values[j][0],
						ptr->bonesdata[i].t_ranges.values[j][1]);
			}
			//Extra Timestamp&Vector if the last Time was not the TimeEnd to "loop" it

			int final_time =
					ptr->animations[ptr->header.nAnimations - 1].timeEnd;
			if (ptr->bonesdata[i].t_times.values[t_times_size - 1]
					< final_time) {

				t_times_size++;	//I dont know why but there is one more Timestamp.

				ptr->bonesdata[i].t_times.values[t_times_size - 1] = final_time;

				printf("\t\tFinal Timestamp : %d\n",
						ptr->bonesdata[i].t_times.values[t_times_size - 1]);
				printf("\t\tFinal Vector : (%f,%f,%f)\n",
						ptr->bonesdata[i].t_keys.values[t_times_size - 1][0],
						ptr->bonesdata[i].t_keys.values[t_times_size - 1][1],
						ptr->bonesdata[i].t_keys.values[t_times_size - 1][2]);
			}
		}
		//END translation

		//rotation
		if (lk_m2.bones[i].rot.Times.n > 0) {
			int j;
			int times_index = 0; //Not reset when we finish the extraction of timestamps from 1 animation
			int keys_index = 0;	//Not reset when we finish the extraction of keys from 1 animation
			ptr->bonesdata[i].r_ranges.values = malloc(
					(ptr->header.nAnimations + 1) * sizeof(Range));
			ptr->bonesdata[i].r_ranges.values[ptr->header.nAnimations][0] = 0;//No idea why the last (int,int) is always 0
			ptr->bonesdata[i].r_ranges.values[ptr->header.nAnimations][1] = 0;

			size_t r_times_size = 0;//Number of Timestamps (equal to the number of keys) for this bone
			for (j = 0; j < lk_m2.header.nAnimations; j++) {
				r_times_size += lk_m2.animofs[i].r_times[j].n;
			}

			ptr->bones[i].rot.Times.n = r_times_size;

			ptr->bonesdata[i].r_times.values = malloc(
					r_times_size * sizeof(uint32));

			/*FIXME I don't know why but sometimes there are very large value and we can't store them
			 * The size itself is probably flawed as usual size are in 1E2-1E3 range and this one is like 1E9
			 */
			if (r_times_size >= 100000000) {
				fprintf(stderr, "ERROR : Rotation number too large\n");
				fprintf(stderr, "\tSize of array : %d\n", r_times_size);
				size_t memory = r_times_size * sizeof(Quat);
				fprintf(stderr, "\tMemory that would have been allocated : %lu\n", (unsigned long)memory);
			} else {
				ptr->bonesdata[i].r_keys.values = malloc(
						r_times_size * sizeof(Quat));
			}

			int intertime;

			for (j = 0; j < ptr->header.nAnimations; j++) {
				intertime = times_index;
				if (lk_m2.animofs[i].r_times[j].n > 0
						& (r_times_size < 100000000)) {	//TIMESTAMPS & INTERPOLATION RANGE
					ptr->bonesdata[i].r_ranges.values[j][0] = intertime;//Range : keep the records FIXME
					int k;
					for (k = 0; k < lk_m2.animofs[i].r_times[j].n; k++) {//Take each value for this anim and put it in the BC data
						ptr->bonesdata[i].r_times.values[times_index] =
								ptr->animations[j].timeStart
										+ lk_m2.bonesdata[i].r_times[j].values[k];//Start Timestamp + animation-relative time
						times_index++;
						intertime++;
					}
					ptr->bonesdata[i].r_ranges.values[j][1] = intertime - 1;
					intertime++;
				} else {
					ptr->bonesdata[i].r_ranges.values[j][0] = intertime - 1;
					ptr->bonesdata[i].r_ranges.values[j][1] = intertime;
				}

				if (lk_m2.animofs[i].r_keys[j].n > 0
						& (r_times_size < 100000000)) {	//KEYS
					int k;
					for (k = 0; k < lk_m2.animofs[i].r_keys[j].n; k++) {//Take each value for this anim and put it in the BC data
						int m;
						for (m = 0; m < 4; m++) {
							ptr->bonesdata[i].r_keys.values[0][m] =
									lk_m2.bonesdata[i].r_keys[j].values[k][m];
						}
						keys_index++;
					}
				}
			}
			//Extra Timestamp&Vector if the last Time was not the TimeEnd to "loop" it

			int final_time =
					ptr->animations[ptr->header.nAnimations - 1].timeEnd;
			if (ptr->bonesdata[i].r_times.values[r_times_size - 1]
					< final_time) {

				r_times_size++;

				ptr->bonesdata[i].r_times.values[r_times_size - 1] = final_time;
			}
		}
		//END rotation

		//scaling
		if (lk_m2.bones[i].scal.Times.n > 0) {
			int j;
			int times_index = 0; //Not reset when we finish the extraction of timestamps from 1 animation
			int keys_index = 0;	//Not reset when we finish the extraction of keys from 1 animation
			ptr->bonesdata[i].s_ranges.values = malloc(
					(ptr->header.nAnimations + 1) * sizeof(Range));
			ptr->bonesdata[i].s_ranges.values[ptr->header.nAnimations][0] = 0;//No idea why the last (int,int) is always 0
			ptr->bonesdata[i].s_ranges.values[ptr->header.nAnimations][1] = 0;

			int s_times_size = 0;//Number of Timestamps (equal to the number of keys) for this bone
			for (j = 0; j < lk_m2.header.nAnimations; j++) {
				s_times_size += lk_m2.animofs[i].s_times[j].n;
			}

			ptr->bonesdata[i].s_times.values = malloc(
					(s_times_size + 1) * sizeof(uint32));

			ptr->bonesdata[i].s_keys.values = malloc(
					(s_times_size + 1) * sizeof(Vec3D));

			int intertime;

			for (j = 0; j < ptr->header.nAnimations; j++) {
				intertime = times_index;
				if (lk_m2.animofs[i].s_times[j].n > 0) {//TIMESTAMPS & INTERPOLATION RANGE
					ptr->bonesdata[i].s_ranges.values[j][0] = intertime;//Range : keep the records FIXME
					int k;
					for (k = 0; k < lk_m2.animofs[i].s_times[j].n; k++) {//Take each value for this anim and put it in the BC data
						ptr->bonesdata[i].s_times.values[times_index] =
								ptr->animations[j].timeStart
										+ lk_m2.bonesdata[i].s_times[j].values[k];//Start Timestamp + animation-relative time
						times_index++;
						intertime++;
					}
					ptr->bonesdata[i].s_ranges.values[j][1] = intertime - 1;
					intertime++;
				} else {
					ptr->bonesdata[i].s_ranges.values[j][0] = intertime - 1;
					ptr->bonesdata[i].s_ranges.values[j][1] = intertime;
				}

				if (lk_m2.animofs[i].s_keys[j].n > 0) {	//KEYS
					int k;
					for (k = 0; k < lk_m2.animofs[i].s_keys[j].n; k++) {//Take each value for this anim and put it in the BC data
						int m;
						for (m = 0; m < 3; m++) {
							ptr->bonesdata[i].s_keys.values[keys_index][m] =
									lk_m2.bonesdata[i].s_keys[j].values[k][m];
						}
						keys_index++;
					}
				}
			}
			//Extra Timestamp&Vector if the last Time was not the TimeEnd to "loop" it

			int final_time =
					ptr->animations[ptr->header.nAnimations - 1].timeEnd;
			if (ptr->bonesdata[i].s_times.values[s_times_size - 1]
					< final_time) {

				s_times_size++;	// I dont know why but there is one more Timestamp.
				ptr->bonesdata[i].s_times.values[s_times_size - 1] = final_time;
			}
			ptr->bones[i].scal.Times.n = s_times_size;
		}
		//END scaling
	}

	//Bones
	//numbers in animblocks are already done in the Data procedure
	for (i = 0; i < ptr->header.nBones; i++) {
		ptr->bones[i].animid = lk_m2.bones[i].animid;
		ptr->bones[i].flags = lk_m2.bones[i].flags;
		ptr->bones[i].parent = lk_m2.bones[i].parent;
		ptr->bones[i].geoid = lk_m2.bones[i].geoid;
		ptr->bones[i].unk = lk_m2.bones[i].unk;
		//translation
		ptr->bones[i].trans.type = lk_m2.bones[i].trans.type;
		ptr->bones[i].trans.seq = lk_m2.bones[i].trans.seq;
		//rotation
		ptr->bones[i].rot.type = lk_m2.bones[i].rot.type;
		ptr->bones[i].rot.seq = lk_m2.bones[i].rot.seq;
		//scaling
		ptr->bones[i].scal.type = lk_m2.bones[i].scal.type;
		ptr->bones[i].scal.seq = lk_m2.bones[i].scal.seq;
		int j;
		for (j = 0; j < 3; j++) {
			ptr->bones[i].pivot[j] = lk_m2.bones[i].pivot[j];
		}
	}
	return 0;
}

/**
 * Convert a LKM2
 */
int lk_to_bc(LKM2 lk_m2, Skin *skins, BCM2 *ptr) {
	header_converter(ptr, lk_m2.header);

	ptr->filename = lk_m2.filename;

	ptr->globalsequences = malloc(ptr->header.nGlobalSequences * sizeof(int));
	int i;
	for (i = 0; i < ptr->header.nGlobalSequences; i++) {
		ptr->globalsequences[i] = lk_m2.globalsequences[i];
	}

	animations_converter(ptr, lk_m2);

	ptr->AnimLookup = malloc(ptr->header.nAnimationLookup * sizeof(int16));
	for (i = 0; i < ptr->header.nAnimationLookup; i++) {
		ptr->AnimLookup[i] = lk_m2.AnimLookup[i];
	}
	//TODO Bonelookup

	ptr->keybonelookup = malloc(ptr->header.nKeyBoneLookup * sizeof(short));
	for (i = 0; i < ptr->header.nKeyBoneLookup; i++) {
		ptr->keybonelookup[i] = lk_m2.keybonelookup[i];
	}
	/*
	 //views_header = views_converter(skin_header);


	 // The amount of nAnimationLookup is assigned so far as the amount of animations
	 ptr->header.nAnimationLookup = lk_m2.header.nAnimations;

	 // The amount of PlayableAnimationLookup is assigned so far as the amount of animations
	 ptr->header.nPlayableAnimationLookup = lk_m2.header.nAnimations;

	 for (i = 0; i < ptr->header.nBones; i++) {
	 ptr->bones[i] = bone_converter(lk_m2.bones[i]);
	 }
	 */
	return 0;
}
