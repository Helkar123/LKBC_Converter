/**
 * @file
 * Conversion functions
 */

#include "structures.h"
int lk_to_bc(LKM2 lk_m2, Skin skin, BCM2 *ptr) {
	/*
	ptr->header = header_converter(lk_m2.header);

	//views_header = views_converter(skin_header);

	int i;
	for (i = 0; i < ptr->header.nAnimations; i++) {
		ptr->animations[i] = animation_converter(lk_m2.animations[i]);
	}

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
