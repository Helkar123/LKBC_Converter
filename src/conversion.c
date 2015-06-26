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
	ptr->header.nameOfs = lk_header.nameOfs; //0x150
	ptr->header.GlobalModelFlags = lk_header.GlobalModelFlags;
	ptr->header.nGlobalSequences = lk_header.nGlobalSequences;
	ptr->header.ofsGlobalSequences = lk_header.ofsGlobalSequences;
	ptr->header.nAnimations = lk_header.nAnimations;
	ptr->header.ofsAnimations = lk_header.ofsAnimations;
	ptr->header.nAnimationLookup = lk_header.nAnimationLookup;
	ptr->header.ofsAnimationLookup = lk_header.ofsAnimationLookup;
	ptr->header.nPlayableAnimationLookup = 0x00; //TODO Placeholder. I don't know where this data is in WotLK.
	ptr->header.ofsPlayableAnimationLookup = 0x00;
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

	ptr->header.nTransparency = 0; //TODO Unimplemented features
	ptr->header.ofsTransparency = 0;
	ptr->header.nAttachLookup = 0;
	ptr->header.ofsAttachLookup = 0;
	ptr->header.nAttachments_2 = 0;
	ptr->header.ofsAttachments_2 = 0;
	ptr->header.nLights = 0;
	ptr->header.ofsLights = 0;
	ptr->header.nCameras = 0;
	ptr->header.ofsCameras = 0;
	ptr->header.nCameraLookup = 0;
	ptr->header.ofsCameraLookup = 0;
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
		ptr->animations[i].subAnimID = lk_m2.animations[i].subAnimID;
		ptr->animations[i].timeStart = timeline;
		timeline += lk_m2.animations[i].length;
		ptr->animations[i].timeEnd = timeline;
		ptr->animations[i].moveSpeed = lk_m2.animations[i].moveSpeed;
		ptr->animations[i].flags = lk_m2.animations[i].flags;
		ptr->animations[i].flags -= 0x20; //Flags difference ?
		ptr->animations[i].probability = lk_m2.animations[i].probability;
		ptr->animations[i].unused = lk_m2.animations[i].unused; //The Wiki says it's unused, but just in case, it's always better to convert it ;)
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
		ptr->animations[i].Index = 0; //In LK, it has the value. In TBC it seems to always be 0
	}
	return 0;
}

/**
 * Compute interpolation ranges
 * @param AnimRefs
 * @param ptrDataBlock
 * @param ptrRange Pointer to range_time.
 * @param j Animation index.
 */
void compute_ranges(LKAnimationBlock LKBlock, AnimRefs AnimRefs,
		Range **ptrRangeList) {
	int range_time = 0;
	int j;
	for (j = 0; j < LKBlock.Times.n; j++) {
		if (AnimRefs.times[j].n == 0) {
			(*ptrRangeList)[j][0] = range_time;
			range_time++;
			(*ptrRangeList)[j][1] = range_time;
			range_time++;
		} else if (AnimRefs.times[j].n == 1) {
			if (j == 0) { //If it's the first anim, you obviously can't take the end of the previous range
				(*ptrRangeList)[j][0] = range_time;
				range_time++;
				(*ptrRangeList)[j][1] = range_time;
				range_time++;
			} else {
				(*ptrRangeList)[j][0] = (*ptrRangeList)[j - 1][1];
				(*ptrRangeList)[j][1] = range_time;
				range_time++;
			}
		} else {				//n > 1
			(*ptrRangeList)[j][0] = range_time;
			range_time += AnimRefs.times[j].n - 1;
			(*ptrRangeList)[j][1] = range_time;
			range_time++;
		}
	}
}

int get_keyframes_number(LKAnimationBlock LKBlock, AnimRefs AnimRefs){
		size_t keyframes_size = 0; //Number of (Timestamp, key) tuples
		int j;
		for (j = 0; j < LKBlock.Times.n; j++) {
			if (AnimRefs.times[j].n > 1) {
				keyframes_size += AnimRefs.times[j].n;
			} else if (AnimRefs.times[j].n == 1) {
				if (j == 0) {
					keyframes_size += 2;
				} else {
					keyframes_size += 1;
				}
			} else { //n=0
				keyframes_size += 2;
			}
		}
		return keyframes_size;
}
/**
 * Converts an AnimBlock of 3D Vectors values from LK to BC.
 * @param LKBlock Layer 0.
 * @param AnimRefs Layer 1 (ArrayRefs with n&ofs to data).
 * @param LKDataBlock Layer 2 (Data).
 * @param ptrBlock Layer 0.
 * @param ptrDataBlock Layer 1 (Data).
 * @param animations
 * @param nAnimations
 */
void convert_Vec3DAnimBlock(LKAnimationBlock LKBlock, AnimRefs AnimRefs,
		Vec3D_LKSubBlock *LKDataBlock, AnimationBlock *ptrBlock,
		Vec3D_SubBlock *ptrDataBlock, ModelAnimation *animations,
		int nAnimations) {
	if (LKBlock.Times.n > 1) {
		//Interpolation ranges
		ptrBlock->Ranges.n = nAnimations + 1;
		ptrDataBlock->ranges = malloc(ptrBlock->Ranges.n * sizeof(Range));
		ptrDataBlock->ranges[nAnimations][0] = 0; //No idea why the last (int,int) is always 0
		ptrDataBlock->ranges[nAnimations][1] = 0;
		compute_ranges(LKBlock, AnimRefs, &ptrDataBlock->ranges);

		size_t keyframes_size = get_keyframes_number(LKBlock, AnimRefs); //Number of (Timestamp, key) tuples
		ptrBlock->Times.n = keyframes_size;
		ptrBlock->Keys.n = keyframes_size;
		ptrDataBlock->times = malloc((keyframes_size) * sizeof(uint32));
		ptrDataBlock->keys = malloc((keyframes_size) * sizeof(Vec3D));

		int keyframes_index = 0; //Not reset when we finish the extraction of keys from 1 animation
		int j;
		for (j = 0; j < LKBlock.Times.n; j++) {
			//Keyframes
			if (AnimRefs.times[j].n > 1) { //scal.times[j].n = s_keys[j].n (everything is symmetric since it's a keyframe tuple)
				int k;
				for (k = 0; k < AnimRefs.times[j].n; k++) {	//Take each value for this anim and put it in the BC data
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart + LKDataBlock[j].times[k]; //Start Time + animation-relative time
					//KEY
					int m;
					for (m = 0; m < 3; m++) {
						ptrDataBlock->keys[keyframes_index][m] =
								LKDataBlock[j].keys[k][m];
					}
					keyframes_index++;
				}
			} else if (AnimRefs.times[j].n == 1) {
				if (j > 0) {
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeEnd;
					//KEY
					int m;
					for (m = 0; m < 3; m++) {
						ptrDataBlock->keys[keyframes_index][m] =
								LKDataBlock[j].keys[0][m];
					}
					keyframes_index++;
				} else {						//First animation (j=0)
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart;
					ptrDataBlock->times[keyframes_index + 1] =
							animations[j].timeEnd;
					//KEY
					int m;
					for (m = 0; m < 3; m++) {
						ptrDataBlock->keys[keyframes_index][m] =
								LKDataBlock[j].keys[0][m];
						ptrDataBlock->keys[keyframes_index + 1][m] =
								LKDataBlock[j].keys[0][m];
					}
					keyframes_index += 2;
				}
			} else {						//n=0
				//TIMESTAMP
				ptrDataBlock->times[keyframes_index] = animations[j].timeStart;
				ptrDataBlock->times[keyframes_index + 1] =
						animations[j].timeEnd;
				//KEY
				int m;
				for (m = 0; m < 3; m++) {
					ptrDataBlock->keys[keyframes_index][m] = 0;
					ptrDataBlock->keys[keyframes_index + 1][m] = 0;
				}
				keyframes_index += 2;
			}
		}
	} else if (LKBlock.Times.n == 1) { //Constant value across all animations for the bone
		ptrBlock->Ranges.n = 0;
		ptrDataBlock->times = malloc(sizeof(uint32));
		ptrDataBlock->keys = malloc(sizeof(Vec3D));
		ptrDataBlock->times[0] = LKDataBlock[0].times[0];
		int m;
		for (m = 0; m < 3; m++) {
			ptrDataBlock->keys[0][m] = LKDataBlock[0].keys[0][m];
		}
	}
}

/**
 * Converts an AnimBlock of Quaternions values from LK to BC.
 * @param LKBlock Layer 0.
 * @param AnimRefs Layer 1 (ArrayRefs with n&ofs to data).
 * @param LKDataBlock Layer 2 (Data).
 * @param ptrBlock Layer 0.
 * @param ptrDataBlock Layer 1 (Data).
 * @param animations
 * @param nAnimations
 */
void convert_QuatAnimBlock(LKAnimationBlock LKBlock, AnimRefs AnimRefs,
		Quat_LKSubBlock *LKDataBlock, AnimationBlock *ptrBlock,
		Quat_SubBlock *ptrDataBlock, ModelAnimation *animations,
		int nAnimations) {
	if (LKBlock.Times.n > 1) {
		//Interpolation ranges
		ptrBlock->Ranges.n = nAnimations + 1;
		ptrDataBlock->ranges = malloc(ptrBlock->Ranges.n * sizeof(Range));
		ptrDataBlock->ranges[nAnimations][0] = 0; //No idea why the last (int,int) is always 0
		ptrDataBlock->ranges[nAnimations][1] = 0;
		compute_ranges(LKBlock, AnimRefs, &ptrDataBlock->ranges);

		size_t keyframes_size = get_keyframes_number(LKBlock, AnimRefs); //Number of (Timestamp, key) tuples
		ptrBlock->Times.n = keyframes_size;
		ptrBlock->Keys.n = keyframes_size;
		ptrDataBlock->times = malloc((keyframes_size) * sizeof(uint32));
		ptrDataBlock->keys = malloc((keyframes_size) * sizeof(Quat));

		int keyframes_index = 0; //Not reset when we finish the extraction of keys from 1 animation
		int j;
		for (j = 0; j < LKBlock.Times.n; j++) {
			//Keyframes
			if (AnimRefs.times[j].n > 1) { //scal.times[j].n = s_keys[j].n (everything is symmetric since it's a keyframe tuple)
				int k;
				for (k = 0; k < AnimRefs.times[j].n; k++) {	//Take each value for this anim and put it in the BC data
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart + LKDataBlock[j].times[k]; //Start Time + animation-relative time
					//KEY
					int m;
					for (m = 0; m < 4; m++) {
						ptrDataBlock->keys[keyframes_index][m] =
								LKDataBlock[j].keys[k][m];
					}
					keyframes_index++;
				}
			} else if (AnimRefs.times[j].n == 1) {
				if (j > 0) {
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeEnd;
					//KEY
					int m;
					for (m = 0; m < 4; m++) {
						ptrDataBlock->keys[keyframes_index][m] =
								LKDataBlock[j].keys[0][m];
					}
					keyframes_index++;
				} else {						//First animation (j=0)
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart;
					ptrDataBlock->times[keyframes_index + 1] =
							animations[j].timeEnd;
					//KEY
					int m;
					for (m = 0; m < 4; m++) {
						ptrDataBlock->keys[keyframes_index][m] =
								LKDataBlock[j].keys[0][m];
						ptrDataBlock->keys[keyframes_index + 1][m] =
								LKDataBlock[j].keys[0][m];
					}
					keyframes_index += 2;
				}
			} else {						//n=0
				//TIMESTAMP
				ptrDataBlock->times[keyframes_index] = animations[j].timeStart;
				ptrDataBlock->times[keyframes_index + 1] =
						animations[j].timeEnd;
				//KEY
				int m;
				for (m = 0; m < 3; m++) {
					ptrDataBlock->keys[keyframes_index][m] = -32767;
					ptrDataBlock->keys[keyframes_index + 1][m] = -32767;
				}
				ptrDataBlock->keys[keyframes_index][m] = -1;
				ptrDataBlock->keys[keyframes_index + 1][m] = -1;
				keyframes_index += 2;
			}
		}
	} else if (LKBlock.Times.n == 1) { //Constant value across all animations for the bone
		ptrBlock->Ranges.n = 0;
		ptrDataBlock->times = malloc(sizeof(uint32));
		ptrDataBlock->keys = malloc(sizeof(Quat));
		ptrDataBlock->times[0] = LKDataBlock[0].times[0];
		int m;
		for (m = 0; m < 4; m++) {
			ptrDataBlock->keys[0][m] = LKDataBlock[0].keys[0][m];
		}
	}
}

void convert_IntAnimBlock(LKAnimationBlock LKBlock, AnimRefs AnimRefs,
		Int_LKSubBlock *LKDataBlock, AnimationBlock *ptrBlock,
		Int_SubBlock *ptrDataBlock, ModelAnimation *animations,
		int nAnimations) {
	if (LKBlock.Times.n > 1) {
		//Interpolation ranges
		ptrBlock->Ranges.n = nAnimations + 1;
		ptrDataBlock->ranges = malloc(ptrBlock->Ranges.n * sizeof(Range));
		ptrDataBlock->ranges[nAnimations][0] = 0; //No idea why the last (int,int) is always 0
		ptrDataBlock->ranges[nAnimations][1] = 0;
		compute_ranges(LKBlock, AnimRefs, &ptrDataBlock->ranges);

		size_t keyframes_size = get_keyframes_number(LKBlock, AnimRefs); //Number of (Timestamp, key) tuples
		ptrBlock->Times.n = keyframes_size;
		ptrBlock->Keys.n = keyframes_size;
		ptrDataBlock->times = malloc((keyframes_size) * sizeof(uint32));
		ptrDataBlock->keys = malloc((keyframes_size) * sizeof(int));

		int keyframes_index = 0; //Not reset when we finish the extraction of keys from 1 animation
		int j;
		for (j = 0; j < LKBlock.Times.n; j++) {
			//Keyframes
			if (AnimRefs.times[j].n > 1) { //scal.times[j].n = s_keys[j].n (everything is symmetric since it's a keyframe tuple)
				int k;
				for (k = 0; k < AnimRefs.times[j].n; k++) {	//Take each value for this anim and put it in the BC data
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart + LKDataBlock[j].times[k]; //Start Time + animation-relative time
					//KEY
						ptrDataBlock->keys[keyframes_index] =
								LKDataBlock[j].keys[k];
					keyframes_index++;
				}
			} else if (AnimRefs.times[j].n == 1) {
				if (j > 0) {
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeEnd;
					//KEY
						ptrDataBlock->keys[keyframes_index] =
								LKDataBlock[j].keys[0];
					keyframes_index++;
				} else {						//First animation (j=0)
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart;
					ptrDataBlock->times[keyframes_index + 1] =
							animations[j].timeEnd;
					//KEY
						ptrDataBlock->keys[keyframes_index] =
								LKDataBlock[j].keys[0];
						ptrDataBlock->keys[keyframes_index + 1] =
								LKDataBlock[j].keys[0];
					keyframes_index += 2;
				}
			} else {						//n=0
				//TIMESTAMP
				ptrDataBlock->times[keyframes_index] = animations[j].timeStart;
				ptrDataBlock->times[keyframes_index + 1] =
						animations[j].timeEnd;
				//KEY
					ptrDataBlock->keys[keyframes_index] = 0;
					ptrDataBlock->keys[keyframes_index + 1] = 0;
				keyframes_index += 2;
			}
		}
	} else if (LKBlock.Times.n == 1) { //Constant value across all animations for the bone
		ptrBlock->Ranges.n = 0;
		ptrDataBlock->times = malloc(sizeof(uint32));
		ptrDataBlock->keys = malloc(sizeof(int));
		ptrDataBlock->times[0] = LKDataBlock[0].times[0];
		ptrDataBlock->keys[0] = LKDataBlock[0].keys[0];
	}
}
void convert_ShortAnimBlock(LKAnimationBlock LKBlock, AnimRefs AnimRefs,
		Short_LKSubBlock *LKDataBlock, AnimationBlock *ptrBlock,
		Short_SubBlock *ptrDataBlock, ModelAnimation *animations,
		int nAnimations) {
	if (LKBlock.Times.n > 1) {
		//Interpolation ranges
		ptrBlock->Ranges.n = nAnimations + 1;
		ptrDataBlock->ranges = malloc(ptrBlock->Ranges.n * sizeof(Range));
		ptrDataBlock->ranges[nAnimations][0] = 0; //No idea why the last (int,int) is always 0
		ptrDataBlock->ranges[nAnimations][1] = 0;
		compute_ranges(LKBlock, AnimRefs, &ptrDataBlock->ranges);

		size_t keyframes_size = get_keyframes_number(LKBlock, AnimRefs); //Number of (Timestamp, key) tuples
		ptrBlock->Times.n = keyframes_size;
		ptrBlock->Keys.n = keyframes_size;
		ptrDataBlock->times = malloc((keyframes_size) * sizeof(uint32));
		ptrDataBlock->keys = malloc((keyframes_size) * sizeof(short));

		int keyframes_index = 0; //Not reset when we finish the extraction of keys from 1 animation
		int j;
		for (j = 0; j < LKBlock.Times.n; j++) {
			//Keyframes
			if (AnimRefs.times[j].n > 1) { //scal.times[j].n = s_keys[j].n (everything is symmetric since it's a keyframe tuple)
				int k;
				for (k = 0; k < AnimRefs.times[j].n; k++) {	//Take each value for this anim and put it in the BC data
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart + LKDataBlock[j].times[k]; //Start Time + animation-relative time
					//KEY
						ptrDataBlock->keys[keyframes_index] =
								LKDataBlock[j].keys[k];
					keyframes_index++;
				}
			} else if (AnimRefs.times[j].n == 1) {
				if (j > 0) {
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeEnd;
					//KEY
						ptrDataBlock->keys[keyframes_index] =
								LKDataBlock[j].keys[0];
					keyframes_index++;
				} else {						//First animation (j=0)
					//TIMESTAMP
					ptrDataBlock->times[keyframes_index] =
							animations[j].timeStart;
					ptrDataBlock->times[keyframes_index + 1] =
							animations[j].timeEnd;
					//KEY
						ptrDataBlock->keys[keyframes_index] =
								LKDataBlock[j].keys[0];
						ptrDataBlock->keys[keyframes_index + 1] =
								LKDataBlock[j].keys[0];
					keyframes_index += 2;
				}
			} else {						//n=0
				//TIMESTAMP
				ptrDataBlock->times[keyframes_index] = animations[j].timeStart;
				ptrDataBlock->times[keyframes_index + 1] =
						animations[j].timeEnd;
				//KEY
					ptrDataBlock->keys[keyframes_index] = 0;
					ptrDataBlock->keys[keyframes_index + 1] = 0;
				keyframes_index += 2;
			}
		}
	} else if (LKBlock.Times.n == 1) { //Constant value across all animations for the bone
		ptrBlock->Ranges.n = 0;
		ptrDataBlock->times = malloc(sizeof(uint32));
		ptrDataBlock->keys = malloc(sizeof(short));
		ptrDataBlock->times[0] = LKDataBlock[0].times[0];
		ptrDataBlock->keys[0] = LKDataBlock[0].keys[0];
	}
}

/**
 * Converts bones with their animations data
 * @param ptr Pointer to BC M2 structure
 * @param lk_m2 LK M2 structure (no need for pointer as we should not modify it)
 * @return 0 if successful
 */
int bones_converter(BCM2 *ptr, LKM2 lk_m2) {
	ptr->bones = malloc(ptr->header.nBones * sizeof(ModelBoneDef));

	//BonesDataBlock
	ptr->bonesdata = malloc(ptr->header.nBones * sizeof(BonesDataBlock));
	int i;
	for (i = 0; i < ptr->header.nBones; i++) {
		//INIT
		ModelAnimation *animations = ptr->animations;
		int nAnimations = ptr->header.nAnimations;

		//translation
		convert_Vec3DAnimBlock(lk_m2.bones[i].trans, lk_m2.animofs[i].trans, lk_m2.bonesdata[i].trans, &ptr->bones[i].trans,
				&ptr->bonesdata[i].trans, animations, nAnimations);

		//rotation
		convert_QuatAnimBlock(lk_m2.bones[i].rot, lk_m2.animofs[i].rot, lk_m2.bonesdata[i].rot, &ptr->bones[i].rot,
				&ptr->bonesdata[i].rot, animations, nAnimations);

		//scaling
		convert_Vec3DAnimBlock(lk_m2.bones[i].scal, lk_m2.animofs[i].scal, lk_m2.bonesdata[i].scal, &ptr->bones[i].scal,
				&ptr->bonesdata[i].scal, animations, nAnimations);
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

int attachments_converter(BCM2 *ptr, LKM2 lk_m2) {
	ptr->attachments = malloc(ptr->header.nAttachments * sizeof(Attachment));
	ptr->attachmentsdata = malloc(ptr->header.nAttachments * sizeof(AttachmentsDataBlock));
	int i;
	for (i = 0; i < ptr->header.nAttachments; i++) {
		//INIT
		ModelAnimation *animations = ptr->animations;
		int nAnimations = ptr->header.nAnimations;

		//data
		convert_IntAnimBlock(lk_m2.attachments[i].data, lk_m2.attachmentsanimofs[i].data, lk_m2.attachmentsdata[i].data, &ptr->attachments[i].data,
				&ptr->attachmentsdata[i].data, animations, nAnimations);
	}

	for (i = 0; i < ptr->header.nAttachments; i++) {
		ptr->attachments[i].ID = lk_m2.attachments[i].ID;
		ptr->attachments[i].bone = lk_m2.attachments[i].bone;
		int j;
		for (j = 0; j < 3; j++) {
			ptr->attachments[i].position[j] = lk_m2.attachments[i].position[j];
		}
		//data
		ptr->attachments[i].data.type = lk_m2.attachments[i].data.type;
		ptr->attachments[i].data.seq = lk_m2.attachments[i].data.seq;
	}
	return 0;
}

int colors_converter(BCM2 *ptr, LKM2 lk_m2) {
	ptr->colors = malloc(ptr->header.nColors * sizeof(ColorDef));
	ptr->colorsdata = malloc(ptr->header.nColors * sizeof(ColorDataBlock));
	int i;
	for (i = 0; i < ptr->header.nColors; i++) {
		//INIT
		ModelAnimation *animations = ptr->animations;
		int nAnimations = ptr->header.nAnimations;

		//RGB
		convert_Vec3DAnimBlock(lk_m2.colors[i].rgb, lk_m2.coloranimofs[i].rgb, lk_m2.colorsdata[i].rgb, &ptr->colors[i].rgb,
				&ptr->colorsdata[i].rgb, animations, nAnimations);
		//Opacity
		convert_ShortAnimBlock(lk_m2.colors[i].opacity, lk_m2.coloranimofs[i].opacity, lk_m2.colorsdata[i].opacity, &ptr->colors[i].opacity,
				&ptr->colorsdata[i].opacity, animations, nAnimations);
	}

	for (i = 0; i < ptr->header.nColors; i++) {
		//RGB
		ptr->colors[i].rgb.type = lk_m2.colors[i].rgb.type;
		ptr->colors[i].rgb.seq = lk_m2.colors[i].rgb.seq;
		//Opacity
		ptr->colors[i].opacity.type = lk_m2.colors[i].opacity.type;
		ptr->colors[i].opacity.seq = lk_m2.colors[i].opacity.seq;
	}
	return 0;
}

/**
 * Convert skins to views
 * @param ptr
 * @param skins
 * @return 0 if successful
 */
int views_converter(BCM2 *ptr, Skin *skins) {
	ptr->views = malloc(4 * sizeof(View));	//In BC there are always 4 views
	int i;
	for (i = 0; i < ptr->header.nViews; i++) {
		//header
		ptr->views[i].header.nIndices = skins[i].header.nIndices;
		ptr->views[i].header.ofsIndices = skins[i].header.ofsIndices;
		ptr->views[i].header.nTriangles = skins[i].header.nTriangles;
		ptr->views[i].header.ofsTriangles = skins[i].header.ofsTriangles;
		ptr->views[i].header.nProperties = skins[i].header.nProperties;
		ptr->views[i].header.ofsProperties = skins[i].header.ofsProperties;
		ptr->views[i].header.nSubmeshes = skins[i].header.nSubmeshes;
		ptr->views[i].header.ofsSubmeshes = skins[i].header.ofsSubmeshes;
		ptr->views[i].header.nTextureUnits = skins[i].header.nTextureUnits;
		ptr->views[i].header.ofsTextureUnits = skins[i].header.ofsTextureUnits;

		if (ptr->views[i].header.nIndices > 0) {
			ptr->views[i].Indices = malloc(
					ptr->views[i].header.nIndices * sizeof(Vertex));
			int j;
			for (j = 0; j < ptr->views[i].header.nIndices; j++) {
				ptr->views[i].Indices[j] = skins[i].Indices[j];
			}
		}
		if (ptr->views[i].header.nTriangles > 0) {
			ptr->views[i].Triangles = malloc(
					(ptr->views[i].header.nTriangles / 3) * sizeof(Triangle));
			int j;
			for (j = 0; j < (ptr->views[i].header.nTriangles / 3); j++) {
				ptr->views[i].Triangles[j][0] = skins[i].Triangles[j][0];
				ptr->views[i].Triangles[j][1] = skins[i].Triangles[j][1];
				ptr->views[i].Triangles[j][2] = skins[i].Triangles[j][2];
			}
		}
		if (ptr->views[i].header.nProperties > 0) {
			ptr->views[i].Properties = malloc(
					ptr->views[i].header.nProperties * sizeof(Property));
			int j;
			for (j = 0; j < ptr->views[i].header.nProperties; j++) {
				ptr->views[i].Properties[j] = skins[i].Properties[j];
			}
		}
		//submeshes
		if (ptr->views[i].header.nSubmeshes > 0) {
			ptr->views[i].Submeshes = malloc(
					ptr->views[i].header.nSubmeshes * sizeof(Submesh));
			int j;
			for (j = 0; j < ptr->views[i].header.nSubmeshes; j++) {
				ptr->views[i].Submeshes[j].ID = skins[i].Submeshes[j].ID;
				ptr->views[i].Submeshes[j].Level = skins[i].Submeshes[j].Level;
				ptr->views[i].Submeshes[j].StartVertex =
						skins[i].Submeshes[j].StartVertex;
				ptr->views[i].Submeshes[j].nVertices =
						skins[i].Submeshes[j].nVertices;
				ptr->views[i].Submeshes[j].StartTriangle =
						skins[i].Submeshes[j].StartTriangle;
				ptr->views[i].Submeshes[j].nTriangles =
						skins[i].Submeshes[j].nTriangles;
				ptr->views[i].Submeshes[j].nBones =
						skins[i].Submeshes[j].nBones;
				ptr->views[i].Submeshes[j].StartBones =
						skins[i].Submeshes[j].StartBones;

				ptr->views[i].Submeshes[j].boneInfluences =
						skins[i].Submeshes[j].boneInfluences;
				ptr->views[i].Submeshes[j].RootBone =
						skins[i].Submeshes[j].RootBone;

				ptr->views[i].Submeshes[j].Position[0] =
						skins[i].Submeshes[j].CenterMass[0];
				ptr->views[i].Submeshes[j].Position[1] =
						skins[i].Submeshes[j].CenterMass[1];
				ptr->views[i].Submeshes[j].Position[2] =
						skins[i].Submeshes[j].CenterMass[2];
				ptr->views[i].Submeshes[j].Floats[0] =
						skins[i].Submeshes[j].CenterBoundingBox[0];
				ptr->views[i].Submeshes[j].Floats[1] =
						skins[i].Submeshes[j].CenterBoundingBox[1];
				ptr->views[i].Submeshes[j].Floats[2] =
						skins[i].Submeshes[j].CenterBoundingBox[2];
				ptr->views[i].Submeshes[j].Floats[3] =
						skins[i].Submeshes[j].Radius;
			}
		}

		ptr->views[i].TextureUnits = skins[i].TextureUnits;
	}
	return 0;
}

/**
 * In WotLK, nViews is a number between 1 and 4. But in Burning Crusade, it's always 4, so there must be some kind of fake views.
 * @param ptr
 * @return
 */
int views_filler(BCM2 *ptr) {
	if (ptr->header.nViews < 4) {
		int last = ptr->header.nViews - 1;//index of the last view. Schlumpf's advice to fill with the last
		int i;
		for (i = ptr->header.nViews; i < 4; i++) {
			//header
			ptr->views[i].header.nIndices = ptr->views[last].header.nIndices;
			ptr->views[i].header.ofsIndices =
					ptr->views[last].header.ofsIndices;
			ptr->views[i].header.nTriangles =
					ptr->views[last].header.nTriangles;
			ptr->views[i].header.ofsTriangles =
					ptr->views[last].header.ofsTriangles;
			ptr->views[i].header.nProperties =
					ptr->views[last].header.nProperties;
			ptr->views[i].header.ofsProperties =
					ptr->views[last].header.ofsProperties;
			ptr->views[i].header.nSubmeshes =
					ptr->views[last].header.nSubmeshes;
			ptr->views[i].header.ofsSubmeshes =
					ptr->views[last].header.ofsSubmeshes;
			ptr->views[i].header.nTextureUnits =
					ptr->views[last].header.nTextureUnits;
			ptr->views[i].header.ofsTextureUnits =
					ptr->views[last].header.ofsTextureUnits;

			if (ptr->views[i].header.nIndices > 0) {
				ptr->views[i].Indices = malloc(
						ptr->views[i].header.nIndices * sizeof(Vertex));
				int j;
				for (j = 0; j < ptr->views[i].header.nIndices; j++) {
					ptr->views[i].Indices[j] = ptr->views[last].Indices[j];
				}
			}
			if (ptr->views[i].header.nTriangles > 0) {
				ptr->views[i].Triangles = malloc(
						(ptr->views[i].header.nTriangles / 3)
								* sizeof(Triangle));
				int j;
				for (j = 0; j < (ptr->views[i].header.nTriangles / 3); j++) {
					ptr->views[i].Triangles[j][0] =
							ptr->views[last].Triangles[j][0];
					ptr->views[i].Triangles[j][1] =
							ptr->views[last].Triangles[j][1];
					ptr->views[i].Triangles[j][2] =
							ptr->views[last].Triangles[j][2];
				}
			}
			if (ptr->views[i].header.nProperties > 0) {
				ptr->views[i].Properties = malloc(
						ptr->views[i].header.nProperties * sizeof(Property));
				int j;
				for (j = 0; j < ptr->views[i].header.nProperties; j++) {
					ptr->views[i].Properties[j] =
							ptr->views[last].Properties[j];
				}
			}
			//submeshes
			if (ptr->views[i].header.nSubmeshes > 0) {
				ptr->views[i].Submeshes = malloc(
						ptr->views[i].header.nSubmeshes * sizeof(Submesh));
				int j;
				for (j = 0; j < ptr->views[i].header.nSubmeshes; j++) {
					ptr->views[i].Submeshes[j].ID =
							ptr->views[last].Submeshes[j].ID;
					ptr->views[i].Submeshes[j].Level =
							ptr->views[last].Submeshes[j].Level;
					ptr->views[i].Submeshes[j].StartVertex =
							ptr->views[last].Submeshes[j].StartVertex;
					ptr->views[i].Submeshes[j].nVertices =
							ptr->views[last].Submeshes[j].nVertices;
					ptr->views[i].Submeshes[j].StartTriangle =
							ptr->views[last].Submeshes[j].StartTriangle;
					ptr->views[i].Submeshes[j].nTriangles =
							ptr->views[last].Submeshes[j].nTriangles;
					ptr->views[i].Submeshes[j].nBones =
							ptr->views[last].Submeshes[j].nBones;
					ptr->views[i].Submeshes[j].StartBones =
							ptr->views[last].Submeshes[j].StartBones;
					ptr->views[i].Submeshes[j].boneInfluences =
							ptr->views[last].Submeshes[j].boneInfluences;
					ptr->views[i].Submeshes[j].RootBone =
							ptr->views[last].Submeshes[j].RootBone;

					ptr->views[i].Submeshes[j].Position[0] =
							ptr->views[last].Submeshes[j].Position[0];
					ptr->views[i].Submeshes[j].Position[1] =
							ptr->views[last].Submeshes[j].Position[1];
					ptr->views[i].Submeshes[j].Position[2] =
							ptr->views[last].Submeshes[j].Position[2];
					ptr->views[i].Submeshes[j].Floats[0] =
							ptr->views[last].Submeshes[j].Floats[0];
					ptr->views[i].Submeshes[j].Floats[1] =
							ptr->views[last].Submeshes[j].Floats[1];
					ptr->views[i].Submeshes[j].Floats[2] =
							ptr->views[last].Submeshes[j].Floats[2];
					ptr->views[i].Submeshes[j].Floats[3] =
							ptr->views[last].Submeshes[j].Floats[3];
				}
			}
			ptr->views[i].TextureUnits = ptr->views[last].TextureUnits;
		}
		ptr->header.nViews = 4;
		return 0;
	}
	return -1;
}

/**
 * Convert a LKM2
 * @param lk_m2
 * @param skins
 * @param ptr
 * @return
 */
int lk_to_bc(LKM2 lk_m2, Skin *skins, BCM2 *ptr) {
	//header
	header_converter(ptr, lk_m2.header);

	//filename
	ptr->filename = lk_m2.filename;

	//global sequences
	ptr->globalsequences = malloc(ptr->header.nGlobalSequences * sizeof(int));
	int i;
	for (i = 0; i < ptr->header.nGlobalSequences; i++) {
		ptr->globalsequences[i] = lk_m2.globalsequences[i];
	}

	//animations sequences
	animations_converter(ptr, lk_m2);

	//bones
	bones_converter(ptr, lk_m2);

	//Animlookup
	ptr->AnimLookup = malloc(ptr->header.nAnimationLookup * sizeof(int16));
	for (i = 0; i < ptr->header.nAnimationLookup; i++) {
		ptr->AnimLookup[i] = lk_m2.AnimLookup[i];
	}

	//KeyboneLookup
	ptr->keybonelookup = malloc(ptr->header.nKeyBoneLookup * sizeof(short));
	for (i = 0; i < ptr->header.nKeyBoneLookup; i++) {
		ptr->keybonelookup[i] = lk_m2.keybonelookup[i];
	}

	//Vertices
	ptr->vertices = malloc(ptr->header.nVertices * sizeof(ModelVertex));
	for (i = 0; i < ptr->header.nVertices; i++) {
		ptr->vertices[i] = lk_m2.vertices[i];
	}

	//views
	views_converter(ptr, skins);
	views_filler(ptr);

	//SubmeshAnimations/Colors
	colors_converter(ptr, lk_m2);

	ptr->textures_def = malloc(ptr->header.nTextures * sizeof(ModelTextureDef));
	ptr->texture_names = malloc(ptr->header.nTextures * sizeof(char *));
	for (i = 0; i < ptr->header.nTextures; i++) {
		ptr->textures_def[i] = lk_m2.textures_def[i];
		if (ptr->textures_def[i].type == 0) {
			ptr->texture_names[i] = malloc(ptr->textures_def[i].nameLen);
			ptr->texture_names[i] = lk_m2.texture_names[i];
		}
	}
	ptr->renderflags = lk_m2.renderflags;
	ptr->BoneLookupTable = lk_m2.BoneLookupTable;
	ptr->TexLookupTable = lk_m2.TexLookupTable;
	ptr->TexUnit = lk_m2.TexUnit;
	ptr->TransparencyLookup = lk_m2.TransparencyLookup;
	ptr->TexAnimLookup = lk_m2.TexAnimLookup;
	ptr->BoundingTriangles = lk_m2.BoundingTriangles;
	ptr->BoundingVertices = lk_m2.BoundingVertices;
	ptr->BoundingNormals = lk_m2.BoundingNormals;

	//Attachments
	attachments_converter(ptr, lk_m2);

	ptr->AttachLookup = lk_m2.AttachLookup;
	/*TODO
	 Transparency;
	 TexAnims;
	 renderflags;
	 BoneLookupTable;
	 TexLookupTable;
	 TexUnit;
	 TransparencyLookup;
	 TexAnimLookup;
	 BoundingTriangles;
	 BoundingVertice *BoundingVertices;
	 BoundingNormals;
	 Attachments;
	 AttachLookup;
	 */

	return 0;
}
