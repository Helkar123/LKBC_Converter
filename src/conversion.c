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
	ptr->header.nameOfs = lk_header.nameOfs;//0x150
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

	ptr->header.nTransparency = 0; //FIXME Unimplemented features
	ptr->header.ofsTransparency = 0;
	ptr->header.nAttachments = 0;
	ptr->header.ofsAttachments = 0;
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
		//translation
		if (lk_m2.bones[i].trans.Times.n > 0) {
			ptr->bones[i].trans.Ranges.n = ptr->header.nAnimations + 1;
			ptr->bonesdata[i].t_ranges.values = malloc(
					ptr->bones[i].trans.Ranges.n * sizeof(Range));
			ptr->bonesdata[i].t_ranges.values[ptr->header.nAnimations][0] = 0; //No idea why the last (int,int) is always 0
			ptr->bonesdata[i].t_ranges.values[ptr->header.nAnimations][1] = 0;

			size_t t_times_size = 0; //Number of Timestamps (equal to the number of keys) for this bone
			int j;
			for (j = 0; j < lk_m2.bones[i].trans.Times.n; j++) {
				t_times_size += lk_m2.animofs[i].t_times[j].n;
			}

			ptr->bones[i].trans.Times.n = t_times_size;
			ptr->bones[i].trans.Keys.n = t_times_size;

			ptr->bonesdata[i].t_times.values = malloc(
					(t_times_size + 1) * sizeof(uint32));

			ptr->bonesdata[i].t_keys.values = malloc(
					(t_times_size + 1) * sizeof(Vec3D));

			int range_time = 0;
			int times_index = 0; //Not reset when we finish the extraction of timestamps from 1 animation
			int keys_index = 0;	//Not reset when we finish the extraction of keys from 1 animation
			for (j = 0; j < lk_m2.bones[i].trans.Times.n; j++) {//Often the number of animations
				//Interpolation range
				if (lk_m2.animofs[i].t_times[j].n == 0) {
					ptr->bonesdata[i].t_ranges.values[j][0] = range_time;
					ptr->bonesdata[i].t_ranges.values[j][1] = range_time + 1;
				} else {				//Usual case
					if (j > 0) {
						range_time++;
					}
					ptr->bonesdata[i].t_ranges.values[j][0] = range_time;
					range_time += lk_m2.animofs[i].t_times[j].n - 1;
					ptr->bonesdata[i].t_ranges.values[j][1] = range_time;
				}

				//TIMESTAMPS
				if (lk_m2.animofs[i].t_times[j].n > 0) {
					int k;
					for (k = 0; k < lk_m2.animofs[i].t_times[j].n; k++) {//Take each value for this anim and put it in the BC data
						ptr->bonesdata[i].t_times.values[times_index] =
								ptr->animations[j].timeStart
										+ lk_m2.bonesdata[i].t_times[j].values[k];//Start Timestamp + animation-relative time
						times_index++;
					}
				}

				//KEYS
				if (lk_m2.animofs[i].t_keys[j].n > 0) {
					int k;
					for (k = 0; k < lk_m2.animofs[i].t_keys[j].n; k++) {//Take each value for this anim and put it in the BC data
						int m;
						for (m = 0; m < 3; m++) {
							ptr->bonesdata[i].t_keys.values[keys_index][m] =
									lk_m2.bonesdata[i].t_keys[j].values[k][m];//Start Timestamp + animation-relative time
						}
						keys_index++;
					}
				}
			}

			//Extra Timestamp&Vector if the last Time was not the TimeEnd to "loop" it
			int final_time =
					ptr->animations[ptr->header.nAnimations - 1].timeEnd;
			if (ptr->bonesdata[i].t_times.values[t_times_size - 1]
					< final_time) {
				t_times_size++;
				ptr->bones[i].trans.Times.n++;
				ptr->bones[i].trans.Keys.n++;

				ptr->bonesdata[i].t_times.values[t_times_size - 1] = final_time;
			}
		}
		//END translation

		//rotation
		if (lk_m2.bones[i].rot.Times.n > 0) {
			ptr->bones[i].rot.Ranges.n = ptr->header.nAnimations + 1;
			ptr->bonesdata[i].r_ranges.values = malloc(
					ptr->bones[i].rot.Ranges.n * sizeof(Range));
			ptr->bonesdata[i].r_ranges.values[ptr->header.nAnimations][0] = 0; //No idea why the last (int,int) is always 0
			ptr->bonesdata[i].r_ranges.values[ptr->header.nAnimations][1] = 0;

			size_t r_times_size = 0; //Number of Timestamps (equal to the number of keys) for this bone
			int j;
			for (j = 0; j < lk_m2.bones[i].rot.Times.n; j++) {
				r_times_size += lk_m2.animofs[i].r_times[j].n;
			}

			ptr->bones[i].rot.Times.n = r_times_size;
			ptr->bones[i].rot.Keys.n = r_times_size;

			ptr->bonesdata[i].r_times.values = malloc(
					(r_times_size + 1) * sizeof(uint32));

			ptr->bonesdata[i].r_keys.values = malloc(
					(r_times_size + 1) * sizeof(Quat));

			int range_time = 0;
			int times_index = 0; //Not reset when we finish the extraction of timestamps from 1 animation
			int keys_index = 0;	//Not reset when we finish the extraction of keys from 1 animation
			for (j = 0; j < lk_m2.bones[i].rot.Times.n; j++) {
				//Interpolation range
				if (lk_m2.animofs[i].r_times[j].n == 0) {
					ptr->bonesdata[i].r_ranges.values[j][0] = range_time;
					ptr->bonesdata[i].r_ranges.values[j][1] = range_time + 1;
				} else {				//Usual case
					if (j > 0) {
						range_time++;
					}
					ptr->bonesdata[i].r_ranges.values[j][0] = range_time;
					range_time += lk_m2.animofs[i].r_times[j].n - 1;
					ptr->bonesdata[i].r_ranges.values[j][1] = range_time;
				}
				//TIMESTAMPS
				if (lk_m2.animofs[i].r_times[j].n > 0) {
					int k;
					for (k = 0; k < lk_m2.animofs[i].r_times[j].n; k++) {//Take each value for this anim and put it in the BC data
						ptr->bonesdata[i].r_times.values[times_index] =
								ptr->animations[j].timeStart
										+ lk_m2.bonesdata[i].r_times[j].values[k];//Start Timestamp + animation-relative time
						times_index++;
					}
				}

				//KEYS
				if (lk_m2.animofs[i].r_keys[j].n > 0) {
					int k;
					for (k = 0; k < lk_m2.animofs[i].r_keys[j].n; k++) {//Take each value for this anim and put it in the BC data
						int m;
						for (m = 0; m < 4; m++) {
							ptr->bonesdata[i].r_keys.values[keys_index][m] =
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
				ptr->bones[i].rot.Times.n++;
				ptr->bones[i].rot.Keys.n++;

				ptr->bonesdata[i].r_times.values[r_times_size - 1] = final_time;
				//For 3D vectors (0,0,0) is fine but it's different for 4D
				ptr->bonesdata[i].r_keys.values[r_times_size - 1][0] = 32767;
				ptr->bonesdata[i].r_keys.values[r_times_size - 1][1] = 32767;
				ptr->bonesdata[i].r_keys.values[r_times_size - 1][2] = 32767;
				ptr->bonesdata[i].r_keys.values[r_times_size - 1][3] = -1;
			}
		}
		//END rotation

		//scaling
		if (lk_m2.bones[i].scal.Times.n > 0) {
			ptr->bones[i].scal.Ranges.n = ptr->header.nAnimations + 1;
			ptr->bonesdata[i].s_ranges.values = malloc(
					ptr->bones[i].scal.Ranges.n * sizeof(Range));
			ptr->bonesdata[i].s_ranges.values[ptr->header.nAnimations][0] = 0; //No idea why the last (int,int) is always 0
			ptr->bonesdata[i].s_ranges.values[ptr->header.nAnimations][1] = 0;

			size_t s_times_size = 0; //Number of Timestamps (equal to the number of keys) for this bone
			int j;
			for (j = 0; j < lk_m2.bones[i].scal.Times.n; j++) {
				s_times_size += lk_m2.animofs[i].s_times[j].n;
			}

			ptr->bones[i].scal.Times.n = s_times_size;
			ptr->bones[i].scal.Keys.n = s_times_size;

			ptr->bonesdata[i].s_times.values = malloc(
					(s_times_size + 1) * sizeof(uint32));

			ptr->bonesdata[i].s_keys.values = malloc(
					(s_times_size + 1) * sizeof(Vec3D));

			int range_time = 0;
			int times_index = 0; //Not reset when we finish the extraction of timestamps from 1 animation
			int keys_index = 0;	//Not reset when we finish the extraction of keys from 1 animation
			for (j = 0; j < lk_m2.bones[i].scal.Times.n; j++) {
				//Interpolation range
				if (lk_m2.animofs[i].s_times[j].n == 0) {
					ptr->bonesdata[i].s_ranges.values[j][0] = range_time;
					ptr->bonesdata[i].s_ranges.values[j][1] = range_time + 1;
				} else {				//Usual case
					if (j > 0) {
						range_time++;
					}
					ptr->bonesdata[i].s_ranges.values[j][0] = range_time;
					range_time += lk_m2.animofs[i].s_times[j].n - 1;
					ptr->bonesdata[i].s_ranges.values[j][1] = range_time;
				}

				//TIMESTAMPS
				if (lk_m2.animofs[i].s_times[j].n > 0) {
					int k;
					for (k = 0; k < lk_m2.animofs[i].s_times[j].n; k++) {//Take each value for this anim and put it in the BC data
						ptr->bonesdata[i].s_times.values[times_index] =
								ptr->animations[j].timeStart
										+ lk_m2.bonesdata[i].s_times[j].values[k];//Start Timestamp + animation-relative time
						times_index++;
					}
				}

				//KEYS
				if (lk_m2.animofs[i].s_keys[j].n > 0) {
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
				s_times_size++;
				ptr->bones[i].scal.Times.n++;
				ptr->bones[i].scal.Keys.n++;

				ptr->bonesdata[i].s_times.values[s_times_size - 1] = final_time;
			}

			/*FIXME Interp Range bug fix (Possibly useless now)
			ptr->bonesdata[i].s_ranges.values[6][1] = ptr->bones[i].scal.Times.n
					- 1;
					*/
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

	//TODO SubmeshAnimations/Colors

	ptr->textures_def = malloc(ptr->header.nTextures * sizeof(ModelTextureDef));
	for (i = 0; i < ptr->header.nTextures; i++) {
		ptr->textures_def[i] = lk_m2.textures_def[i];
		ptr->texture_names = malloc(ptr->header.nTextures * sizeof(char *));
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
