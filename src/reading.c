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
 * @param lk_model Structure with M2 file content
 */
int read_texanims(FILE* lk_m2, LKM2File lk_model){
	if (lk_model.header.nTexAnims > 0) {
		lk_model.lk_tex_anims=malloc(lk_model.header.nTexAnims*sizeof(LKTextureAnimation));
		fseek(lk_m2, lk_model.header.ofsTexAnims, SEEK_SET);
		fread(&lk_model.lk_tex_anims, sizeof(LKTextureAnimation),
				lk_model.header.nTexAnims, lk_m2);

		//read addresses to real animation data
		int i;
		for (i = 0; i < lk_model.header.nTexAnims; i++) {
			//translation
			lk_model.lk_temp_anim_ofs=malloc(lk_model.header.nTexAnims*sizeof(LKAnimOfs));
			if (lk_model.lk_tex_anims[i].Translation.nTimes > 0) {
				fseek(lk_m2, lk_model.lk_tex_anims[i].Translation.ofsTimes,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].t_ntimes, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2,
						lk_model.lk_tex_anims[i].Translation.ofsTimes + 0x4,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].t_ofstimes, sizeof(int), 1,
						lk_m2);
			} else {
				lk_model.lk_temp_anim_ofs[i].t_ntimes = 0;
				lk_model.lk_temp_anim_ofs[i].t_ofstimes = 0;
			}
			if (lk_model.lk_tex_anims[i].Translation.nKeys > 0) {
				fseek(lk_m2, lk_model.lk_tex_anims[i].Translation.ofsKeys,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].t_nkeys, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, lk_model.lk_tex_anims[i].Translation.ofsKeys + 0x4,
				SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].t_ofskeys, sizeof(int), 1,
						lk_m2);
			} else {
				lk_model.lk_temp_anim_ofs[i].t_nkeys = 0;
				lk_model.lk_temp_anim_ofs[i].t_ofskeys = 0;
			}
			//Rotation
			if (lk_model.lk_tex_anims[i].Rotation.nTimes > 0) {
				fseek(lk_m2, lk_model.lk_tex_anims[i].Rotation.ofsTimes,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].r_ntimes, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, lk_model.lk_tex_anims[i].Rotation.ofsTimes + 0x4,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].r_ofstimes, sizeof(int), 1,
						lk_m2);
			} else {
				lk_model.lk_temp_anim_ofs[i].r_ntimes = 0;
				lk_model.lk_temp_anim_ofs[i].r_ofstimes = 0;
			}
			if (lk_model.lk_tex_anims[i].Rotation.nKeys > 0) {
				fseek(lk_m2, lk_model.lk_tex_anims[i].Rotation.ofsKeys,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].r_nkeys, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, lk_model.lk_tex_anims[i].Rotation.ofsKeys + 0x4,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].r_ofskeys, sizeof(int), 1,
						lk_m2);
			} else {
				lk_model.lk_temp_anim_ofs[i].r_nkeys = 0;
				lk_model.lk_temp_anim_ofs[i].r_ofskeys = 0;
			}
			//Scaling
			if (lk_model.lk_tex_anims[i].Scaling.nTimes > 0) {
				fseek(lk_m2, lk_model.lk_tex_anims[i].Scaling.ofsTimes,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].s_ntimes, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, lk_model.lk_tex_anims[i].Scaling.ofsTimes + 0x4,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].s_ofstimes, sizeof(int), 1,
						lk_m2);
			} else {
				lk_model.lk_temp_anim_ofs[i].s_ntimes = 0;
				lk_model.lk_temp_anim_ofs[i].s_ofstimes = 0;
			}
			if (lk_model.lk_tex_anims[i].Scaling.nKeys > 0) {
				fseek(lk_m2, lk_model.lk_tex_anims[i].Scaling.ofsKeys,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].s_nkeys, sizeof(int), 1,
						lk_m2);

				fseek(lk_m2, lk_model.lk_tex_anims[i].Scaling.ofsKeys + 0x4,
						SEEK_SET);
				fread(&lk_model.lk_temp_anim_ofs[i].s_ofskeys, sizeof(int), 1,
						lk_m2);
			} else {
				lk_model.lk_temp_anim_ofs[i].s_nkeys = 0;
				lk_model.lk_temp_anim_ofs[i].s_ofskeys = 0;
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
int read_model(FILE *lk_m2, LKM2File lk_model) {
	//Header
	fseek(lk_m2, 0, SEEK_SET);
	fread(&lk_model.header, sizeof(lk_model.header), 1, lk_m2);

	//Name
	lk_model.lk_filename = malloc(lk_model.header.nameLength);
	fseek(lk_m2, lk_model.header.nameOfs, SEEK_SET);
	fread(&lk_model.lk_filename, sizeof(char), lk_model.header.nameLength,
			lk_m2);

	//Global sequences
	lk_model.globalsequences = malloc(
			lk_model.header.nGlobalSequences * sizeof(unsigned int));
	if (lk_model.header.nGlobalSequences > 0) {
		fseek(lk_m2, lk_model.header.ofsGlobalSequences, SEEK_SET);
		fread(&lk_model.globalsequences, sizeof(unsigned int),
				lk_model.header.nGlobalSequences, lk_m2);
	}

	//Animations
	lk_model.lk_animations = malloc(
			lk_model.header.nAnimations * sizeof(LKModelAnimation));
	fseek(lk_m2, lk_model.header.ofsAnimations, SEEK_SET);
	fread(&lk_model.lk_animations, sizeof(LKModelAnimation),
			lk_model.header.nAnimations, lk_m2);

	//Bones
	lk_model.lk_bones = malloc(lk_model.header.nBones * sizeof(LKModelBoneDef));
	fseek(lk_m2, lk_model.header.ofsBones, SEEK_SET);
	fread(&lk_model.lk_bones, sizeof(LKModelBoneDef), lk_model.header.nBones,
			lk_m2);

	//Skeleton Bone Lookup
	lk_model.keybonelookup = malloc(
			lk_model.header.nKeyBoneLookup * sizeof(short));
	fseek(lk_m2, lk_model.header.ofsKeyBoneLookup, SEEK_SET);
	fread(&lk_model.keybonelookup, sizeof(short),
			lk_model.header.nKeyBoneLookup, lk_m2);

	//Vertices
	lk_model.vertices = malloc(lk_model.header.nVertices * sizeof(ModelVertex));
	fseek(lk_m2, lk_model.header.ofsVertices, SEEK_SET);
	fread(&lk_model.vertices, sizeof(ModelVertex), lk_model.header.nVertices,
			lk_m2);

//FIXME malloc()s... inside or before the "if" ?
	//Colors
	if (lk_model.header.nColors > 0) {
		lk_model.lkcolors = malloc(
				lk_model.header.nColors * sizeof(LKColorDef));
		lk_model.colorsdata = malloc(
				lk_model.header.nColors * sizeof(ColorDataBlock));
		fseek(lk_m2, lk_model.header.ofsColors, SEEK_SET);
		fread(&lk_model.lkcolors, sizeof(LKColorDef), lk_model.header.nColors,
				lk_m2);

		//Color data block
		int temp_ofs[2];
		fseek(lk_m2, lk_model.lkcolors[0].RGB.ofsTimes, SEEK_SET);
		fread(&temp_ofs, sizeof(int), 2, lk_m2);
		fseek(lk_m2, temp_ofs[1], SEEK_SET);
		fread(&lk_model.colorsdata, sizeof(ColorDataBlock),
				lk_model.header.nColors, lk_m2);
	};
	//Textures definition
	lk_model.textures_def = malloc(
			lk_model.header.nTextures * sizeof(ModelTextureDef));
	fseek(lk_m2, lk_model.header.ofsTextures, SEEK_SET);
	fread(&lk_model.textures_def, sizeof(ModelTextureDef),
			lk_model.header.nTextures, lk_m2);

	//TRANSPARENCY
	if (lk_model.header.nTransparency > 0) {
		lk_model.transparencies=malloc(lk_model.header.nTransparency*sizeof(Transparency));
		fseek(lk_m2, lk_model.header.ofsTransparency, SEEK_SET);
		fread(&lk_model.transparencies, sizeof(Transparency),
				lk_model.header.nTransparency, lk_m2);
	}

	//TEXANIMS
	read_texanims(lk_m2, lk_model);


	//Render flags
	lk_model.renderflags=malloc(lk_model.header.nRenderFlags*sizeof(int));
	fseek(lk_m2, lk_model.header.ofsRenderFlags, SEEK_SET);
	fread(&lk_model.renderflags, sizeof(int), lk_model.header.nRenderFlags,
			lk_m2);

	//Bone lookup table
	lk_model.BoneLookupTable=malloc(lk_model.header.nBoneLookupTable*sizeof(short));
	fseek(lk_m2, lk_model.header.ofsBoneLookupTable, SEEK_SET);
	fread(&lk_model.BoneLookupTable, sizeof(short),
			lk_model.header.nBoneLookupTable, lk_m2);

	//Texture lookup table
	lk_model.TexLookupTable=malloc(lk_model.header.nTexLookup*sizeof(short));
	fseek(lk_m2, lk_model.header.ofsTexLookup, SEEK_SET);
	fread(&lk_model.TexLookupTable, sizeof(short), lk_model.header.nTexLookup,
			lk_m2);

	//TexUnit
	lk_model.TexUnit=malloc(lk_model.header.nTexUnitLookup*sizeof(short));
	fseek(lk_m2, lk_model.header.ofsTexUnitLookup, SEEK_SET);
	fread(&lk_model.TexUnit, sizeof(short), lk_model.header.nTexUnitLookup,
			lk_m2);

	//TransLookup
	lk_model.TransparencyLookup=malloc(lk_model.header.nTransparencyLookup*sizeof(short));
	fseek(lk_m2, lk_model.header.ofsTransparencyLookup, SEEK_SET);
	fread(&lk_model.TransparencyLookup, sizeof(short),
			lk_model.header.nTransparencyLookup, lk_m2);

	//TexAnimLookup
	lk_model.TexAnimLookup=malloc(lk_model.header.nTexAnimLookup*sizeof(short));
	fseek(lk_m2, lk_model.header.ofsTexAnimLookup, SEEK_SET);
	fread(&lk_model.TexAnimLookup, sizeof(short),
			lk_model.header.nTexAnimLookup, lk_m2);

	//BoundingTriangles
	lk_model.BoundingTriangles=malloc(lk_model.header.nBoundingTriangles*sizeof(short));
	fseek(lk_m2, lk_model.header.ofsBoundingTriangles, SEEK_SET);
	fread(&lk_model.BoundingTriangles, sizeof(short),
			lk_model.header.nBoundingTriangles, lk_m2);

	//BoundingVertices
	lk_model.BoundingVertices=malloc(lk_model.header.nBoundingVertices*sizeof(BoundingVertice));
	fseek(lk_m2, lk_model.header.ofsBoundingVertices, SEEK_SET);
	fread(&lk_model.BoundingVertices, sizeof(BoundingVertice),
			lk_model.header.nBoundingVertices, lk_m2);

	//BoundingNormals
	lk_model.BoundingNormals=malloc(lk_model.header.nBoundingNormals*sizeof(BoundingNormal));
	fseek(lk_m2, lk_model.header.ofsBoundingNormals, SEEK_SET);
	fread(&lk_model.BoundingNormals, sizeof(BoundingNormal),
			lk_model.header.nBoundingNormals, lk_m2);

	return 0;
}
