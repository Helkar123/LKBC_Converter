/**
 * @file
 * File reading routines
 */

#include <stdio.h>
#include <stdlib.h>
#include "reading.h"

/**
 * Read texture animations. WIP
 * @param lk_m2 The file to read data.
 * @param ptr Pointer to a M2/WotLK structure.
 */
int read_texanims(FILE* lk_m2, LKM2File *ptr) {
	if (ptr->header.nTexAnims > 0) {
		ptr->tex_anims = malloc(
				ptr->header.nTexAnims * sizeof(LKTextureAnimation));
		fseek(lk_m2, ptr->header.ofsTexAnims, SEEK_SET);
		fread(&ptr->tex_anims, sizeof(LKTextureAnimation),
				ptr->header.nTexAnims, lk_m2);

		//read addresses to real animation data
		int i;
		for (i = 0; i < ptr->header.nTexAnims; i++) {
			//translation
			ptr->temp_anim_ofs = malloc(
					ptr->header.nTexAnims * sizeof(LKAnimOfs));
			if (ptr->tex_anims[i].Translation.nTimes > 0) {
				fseek(lk_m2, ptr->tex_anims[i].Translation.ofsTimes,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_ntimes, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, ptr->tex_anims[i].Translation.ofsTimes + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_ofstimes, sizeof(int), 1,
						lk_m2);
			} else {
				ptr->temp_anim_ofs[i].t_ntimes = 0;
				ptr->temp_anim_ofs[i].t_ofstimes = 0;
			}
			if (ptr->tex_anims[i].Translation.nKeys > 0) {
				fseek(lk_m2, ptr->tex_anims[i].Translation.ofsKeys,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_nkeys, sizeof(int), 1, lk_m2);

				fseek(lk_m2, ptr->tex_anims[i].Translation.ofsKeys + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_ofskeys, sizeof(int), 1,
						lk_m2);
			} else {
				ptr->temp_anim_ofs[i].t_nkeys = 0;
				ptr->temp_anim_ofs[i].t_ofskeys = 0;
			}
			//Rotation
			if (ptr->tex_anims[i].Rotation.nTimes > 0) {
				fseek(lk_m2, ptr->tex_anims[i].Rotation.ofsTimes,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_ntimes, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, ptr->tex_anims[i].Rotation.ofsTimes + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_ofstimes, sizeof(int), 1,
						lk_m2);
			} else {
				ptr->temp_anim_ofs[i].r_ntimes = 0;
				ptr->temp_anim_ofs[i].r_ofstimes = 0;
			}
			if (ptr->tex_anims[i].Rotation.nKeys > 0) {
				fseek(lk_m2, ptr->tex_anims[i].Rotation.ofsKeys,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_nkeys, sizeof(int), 1, lk_m2);

				fseek(lk_m2, ptr->tex_anims[i].Rotation.ofsKeys + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_ofskeys, sizeof(int), 1,
						lk_m2);
			} else {
				ptr->temp_anim_ofs[i].r_nkeys = 0;
				ptr->temp_anim_ofs[i].r_ofskeys = 0;
			}
			//Scaling
			if (ptr->tex_anims[i].Scaling.nTimes > 0) {
				fseek(lk_m2, ptr->tex_anims[i].Scaling.ofsTimes,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_ntimes, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, ptr->tex_anims[i].Scaling.ofsTimes + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_ofstimes, sizeof(int), 1,
						lk_m2);
			} else {
				ptr->temp_anim_ofs[i].s_ntimes = 0;
				ptr->temp_anim_ofs[i].s_ofstimes = 0;
			}
			if (ptr->tex_anims[i].Scaling.nKeys > 0) {
				fseek(lk_m2, ptr->tex_anims[i].Scaling.ofsKeys,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_nkeys, sizeof(int), 1, lk_m2);

				fseek(lk_m2, ptr->tex_anims[i].Scaling.ofsKeys + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_ofskeys, sizeof(int), 1,
						lk_m2);
			} else {
				ptr->temp_anim_ofs[i].s_nkeys = 0;
				ptr->temp_anim_ofs[i].s_ofskeys = 0;
			}
		}
		return 0;
	}
	return -1;
}

/**
 * Each substructure in the M2 has a variable size except the header.
 * Memory for each substructure must therefore be allocated at reading depending on header values.
 * @param lk_m2 The file to read data.
 * @param lk_model Structure with M2 file content
 */
int read_model(FILE *lk_m2, LKM2File *ptr) {
	//Header
	fseek(lk_m2, 0, SEEK_SET);
	fread(&ptr->header, sizeof(LKModelHeader), 1, lk_m2);

	//Name
	ptr->filename = malloc(ptr->header.nameLength);
	fseek(lk_m2, ptr->header.nameOfs, SEEK_SET);
	fread(ptr->filename, sizeof(char), ptr->header.nameLength, lk_m2);

	//Global Sequences
	ptr->globalsequences = malloc(
			ptr->header.nGlobalSequences * sizeof(unsigned int));
	if (ptr->header.nGlobalSequences > 0) {
		fseek(lk_m2, ptr->header.ofsGlobalSequences, SEEK_SET);
		fread(&ptr->globalsequences, sizeof(unsigned int),
				ptr->header.nGlobalSequences, lk_m2);
	}

	//Animations
	ptr->animations = malloc(
			ptr->header.nAnimations * sizeof(LKModelAnimation));
	fseek(lk_m2, ptr->header.ofsAnimations, SEEK_SET);
	fread(ptr->animations, sizeof(LKModelAnimation),
			ptr->header.nAnimations, lk_m2);

	//Bones
	ptr->bones = malloc(ptr->header.nBones * sizeof(LKModelBoneDef));
	fseek(lk_m2, ptr->header.ofsBones, SEEK_SET);
	fread(ptr->bones, sizeof(LKModelBoneDef), ptr->header.nBones, lk_m2);

	//Skeleton Bone Lookup
	ptr->keybonelookup = malloc(ptr->header.nKeyBoneLookup * sizeof(short));
	fseek(lk_m2, ptr->header.ofsKeyBoneLookup, SEEK_SET);
	fread(&ptr->keybonelookup, sizeof(short), ptr->header.nKeyBoneLookup,
			lk_m2);


	//Vertices
	ptr->vertices = malloc(ptr->header.nVertices * sizeof(ModelVertex));
	fseek(lk_m2, ptr->header.ofsVertices, SEEK_SET);
	fread(ptr->vertices, sizeof(ModelVertex), ptr->header.nVertices, lk_m2);

//FIXME malloc()s... inside or before the "if" ?
	//Colors
	if (ptr->header.nColors > 0) {
		ptr->lkcolors = malloc(ptr->header.nColors * sizeof(LKColorDef));
		ptr->colorsdata = malloc(ptr->header.nColors * sizeof(ColorDataBlock));
		fseek(lk_m2, ptr->header.ofsColors, SEEK_SET);
		fread(&ptr->lkcolors, sizeof(LKColorDef), ptr->header.nColors, lk_m2);

		//Color Data Block
		int temp_ofs[2];
		fseek(lk_m2, ptr->lkcolors[0].RGB.ofsTimes, SEEK_SET);
		fread(&temp_ofs, sizeof(int), 2, lk_m2);
		fseek(lk_m2, temp_ofs[1], SEEK_SET);
		fread(&ptr->colorsdata, sizeof(ColorDataBlock), ptr->header.nColors,
				lk_m2);
	};

	//Textures Definition
	ptr->textures_def = malloc(ptr->header.nTextures * sizeof(ModelTextureDef));
	fseek(lk_m2, ptr->header.ofsTextures, SEEK_SET);
	fread(&ptr->textures_def, sizeof(ModelTextureDef), ptr->header.nTextures,
			lk_m2);

	//Transparency
	if (ptr->header.nTransparency > 0) {
		ptr->transparencies = malloc(
				ptr->header.nTransparency * sizeof(Transparency));
		fseek(lk_m2, ptr->header.ofsTransparency, SEEK_SET);
		fread(&ptr->transparencies, sizeof(Transparency),
				ptr->header.nTransparency, lk_m2);
	}

	//TexAnims
	read_texanims(lk_m2, ptr);

	//Render Flags
	ptr->renderflags = malloc(ptr->header.nRenderFlags * sizeof(int));
	fseek(lk_m2, ptr->header.ofsRenderFlags, SEEK_SET);
	fread(&ptr->renderflags, sizeof(int), ptr->header.nRenderFlags, lk_m2);

	//Bone Lookup Table
	ptr->BoneLookupTable = malloc(ptr->header.nBoneLookupTable * sizeof(short));
	fseek(lk_m2, ptr->header.ofsBoneLookupTable, SEEK_SET);
	fread(ptr->BoneLookupTable, sizeof(short), ptr->header.nBoneLookupTable,
			lk_m2);

	//Texture Lookup Table
	ptr->TexLookupTable = malloc(ptr->header.nTexLookup * sizeof(short));
	fseek(lk_m2, ptr->header.ofsTexLookup, SEEK_SET);
	fread(&ptr->TexLookupTable, sizeof(short), ptr->header.nTexLookup, lk_m2);

	//TexUnit
	ptr->TexUnit = malloc(ptr->header.nTexUnitLookup * sizeof(short));
	fseek(lk_m2, ptr->header.ofsTexUnitLookup, SEEK_SET);
	fread(&ptr->TexUnit, sizeof(short), ptr->header.nTexUnitLookup, lk_m2);

	//TransLookup
	ptr->TransparencyLookup = malloc(
			ptr->header.nTransparencyLookup * sizeof(short));
	fseek(lk_m2, ptr->header.ofsTransparencyLookup, SEEK_SET);
	fread(&ptr->TransparencyLookup, sizeof(short),
			ptr->header.nTransparencyLookup, lk_m2);

	//TexAnimLookup
	ptr->TexAnimLookup = malloc(ptr->header.nTexAnimLookup * sizeof(short));
	fseek(lk_m2, ptr->header.ofsTexAnimLookup, SEEK_SET);
	fread(&ptr->TexAnimLookup, sizeof(short), ptr->header.nTexAnimLookup,
			lk_m2);

	//BoundingTriangles
	ptr->BoundingTriangles = malloc(
			ptr->header.nBoundingTriangles * sizeof(short));
	fseek(lk_m2, ptr->header.ofsBoundingTriangles, SEEK_SET);
	fread(ptr->BoundingTriangles, sizeof(short),
			ptr->header.nBoundingTriangles, lk_m2);
	//BoundingVertices
	ptr->BoundingVertices = malloc(
			ptr->header.nBoundingVertices * sizeof(BoundingVertice));
	fseek(lk_m2, ptr->header.ofsBoundingVertices, SEEK_SET);
	fread(ptr->BoundingVertices, sizeof(BoundingVertice),
			ptr->header.nBoundingVertices, lk_m2);

	//BoundingNormals
	ptr->BoundingNormals = malloc(
			ptr->header.nBoundingNormals * sizeof(BoundingNormal));
	fseek(lk_m2, ptr->header.ofsBoundingNormals, SEEK_SET);
	fread(ptr->BoundingNormals, sizeof(BoundingNormal),
			ptr->header.nBoundingNormals, lk_m2);
	return 0;
}
