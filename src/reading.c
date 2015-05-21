/**
 * @file
 * File reading routines
 */

#include <stdio.h>
#include <stdlib.h>
#include "reading.h"

/**
 * @param skin_files A list of pointers to skin files to read data from.
 * @param skins A pointer to a list of skins structure where data will be written.
 * @param n The number of skin files. Between 1 and 4.
 */
int read_skins(FILE **skin_files, Skin **ptr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		ptr[i] = malloc(sizeof(Skin));
		//Header
		fseek(skin_files[i], 0, SEEK_SET);
		fread(&ptr[i]->header, sizeof(SkinHeader), 1, skin_files[i]);

		//Indices
		ptr[i]->Indices = malloc(ptr[i]->header.nIndices * sizeof(Vertex));
		fseek(skin_files[i], ptr[i]->header.ofsIndices, SEEK_SET);
		fread(ptr[i]->Indices, sizeof(Vertex), ptr[i]->header.nIndices,
				skin_files[i]);

		//Triangles
		ptr[i]->Triangles = malloc(ptr[i]->header.nTriangles * sizeof(Indices));
		fseek(skin_files[i], ptr[i]->header.ofsTriangles, SEEK_SET);
		fread(ptr[i]->Triangles, sizeof(Indices), ptr[i]->header.nTriangles,
				skin_files[i]);

		//Properties
		ptr[i]->Properties = malloc(
				ptr[i]->header.nProperties * sizeof(Property));
		fseek(skin_files[i], ptr[i]->header.ofsProperties, SEEK_SET);
		fread(ptr[i]->Properties, sizeof(Property), ptr[i]->header.nProperties,
				skin_files[i]);

		//Submeshes
		ptr[i]->Submeshes = malloc(
				ptr[i]->header.nSubmeshes * sizeof(LKSubmesh));
		fseek(skin_files[i], ptr[i]->header.ofsSubmeshes, SEEK_SET);
		fread(ptr[i]->Submeshes, sizeof(LKSubmesh), ptr[i]->header.nSubmeshes,
				skin_files[i]);

		//TexUnits
		ptr[i]->TextureUnits = malloc(
				ptr[i]->header.nTextureUnits * sizeof(TexUnit));
		fseek(skin_files[i], ptr[i]->header.ofsTextureUnits, SEEK_SET);
		fread(ptr[i]->TextureUnits, sizeof(TexUnit),
				ptr[i]->header.nTextureUnits, skin_files[i]);
	}
	return 0;
}

/**
 * Read model bones with animations. WIP
 * @param lk_m2_file The file to read data.
 * @param ptr Pointer to a M2/WotLK structure.
 * i is a bone number, j is an animation number
 */
int read_bones(FILE *lk_m2_file, LKM2 *ptr) {
	ptr->bones = malloc(ptr->header.nBones * sizeof(LKModelBoneDef));
	fseek(lk_m2_file, ptr->header.ofsBones, SEEK_SET);
	fread(ptr->bones, sizeof(LKModelBoneDef), ptr->header.nBones, lk_m2_file);

	/*This function is a good example about reading LK Animation Blocks and ArrayRefs.
	 * In the Block, you have what I call an ArrayRef : a number of elements and a file-relative offset to the first element.
	 * In LKAnimBlock, you have ArrayRefs of ArrayRefs. So you have to work by layers. One structure is required per layer.
	 *
	 * In the first, you store the n ArrayRefs you got by following the Block ArrayRef.
	 *
	 * In the second, you store the arrays of elements you get by following each layer 1 ArrayRef obtained in step one. So there are n of them.
	 * Remember each of these arrays of elements in the layer 2 has a custom size, given by its corresponding layer 1 ArrayRef.
	 */

	//Store animofs (layer 1)
	//You will access each ArrayRef by animofs[n of the bone].(t/r/s)_(times/keys).(n/ofs)
	//This allows later to read the real animation data, by following each ArrayRef.
	ptr->animofs = malloc(ptr->header.nBones * sizeof(LKAnimOfs));//1 LKAnimOfs per bone
	int i;
	for (i = 0; i < ptr->header.nBones; i++) {
		LKModelBoneDef lk_bone = ptr->bones[i];
		//translation
		if (lk_bone.trans.Times.n > 0) {
			ptr->animofs[i].t_times = malloc(
					lk_bone.trans.Times.n * sizeof(ArrayRef));
			fseek(lk_m2_file, lk_bone.trans.Times.ofs, SEEK_SET);
			fread(ptr->animofs[i].t_times, sizeof(ArrayRef),
					lk_bone.trans.Times.n, lk_m2_file);
		}
		if (lk_bone.trans.Keys.n > 0) {
			ptr->animofs[i].t_keys = malloc(
					lk_bone.trans.Times.n * sizeof(ArrayRef));
			fseek(lk_m2_file, lk_bone.trans.Keys.ofs, SEEK_SET);
			fread(ptr->animofs[i].t_keys, sizeof(ArrayRef),
					lk_bone.trans.Keys.n, lk_m2_file);
		}
		//rotation
		if (lk_bone.rot.Times.n > 0) {
			ptr->animofs[i].r_times = malloc(
					lk_bone.rot.Times.n * sizeof(ArrayRef));
			fseek(lk_m2_file, lk_bone.rot.Times.ofs, SEEK_SET);
			fread(ptr->animofs[i].r_times, sizeof(ArrayRef),
					lk_bone.rot.Times.n, lk_m2_file);
		}
		if (lk_bone.rot.Keys.n > 0) {
			ptr->animofs[i].r_keys = malloc(
					lk_bone.rot.Times.n * sizeof(ArrayRef));
			fseek(lk_m2_file, lk_bone.rot.Keys.ofs, SEEK_SET);
			fread(ptr->animofs[i].r_keys, sizeof(ArrayRef), lk_bone.rot.Keys.n,
					lk_m2_file);
		}
		//scaling
		if (lk_bone.scal.Times.n > 0) {
			ptr->animofs[i].s_times = malloc(
					lk_bone.scal.Times.n * sizeof(ArrayRef));
			fseek(lk_m2_file, lk_bone.scal.Times.ofs, SEEK_SET);
			fread(ptr->animofs[i].s_times, sizeof(ArrayRef),
					lk_bone.scal.Times.n, lk_m2_file);
		}
		if (lk_bone.scal.Keys.n > 0) {
			ptr->animofs[i].s_keys = malloc(
					lk_bone.scal.Times.n * sizeof(ArrayRef));
			fseek(lk_m2_file, lk_bone.scal.Keys.ofs, SEEK_SET);
			fread(ptr->animofs[i].s_keys, sizeof(ArrayRef), lk_bone.scal.Keys.n,
					lk_m2_file);
		}
	}

	//Store bones data (layer 2)
	//bonesdata[n of the bone].(t/r/s)_(times/keys)[index based on ntimes].values[index based on its n in animofs]
	ptr->bonesdata = malloc(ptr->header.nBones * sizeof(BonesDataBlock));
	for (i = 0; i < ptr->header.nBones; i++) {
		LKModelBoneDef lk_bone = ptr->bones[i];
		int j;
		//translation
		if (lk_bone.trans.Times.n > 0) {
			ptr->bonesdata[i].t_times = malloc(
					lk_bone.trans.Times.n * sizeof(Uint32Array));//Each Array_Ref leads to an array of elements (and there are Times.n of them, as seen previously)
			for (j = 0; j < lk_bone.trans.Times.n; j++) {
				if (ptr->animofs[i].t_times[j].n > 0) {
					ptr->bonesdata[i].t_times[j].values = malloc(
							ptr->animofs[i].t_times[j].n * sizeof(uint32));//The number of elements was found previously in this function (stored in animofs)
					fseek(lk_m2_file, ptr->animofs[i].t_times[j].ofs, SEEK_SET);
					fread(ptr->bonesdata[i].t_times[j].values, sizeof(uint32),
							ptr->animofs[i].t_times[j].n, lk_m2_file);
				}
			}
		}
		if (ptr->bones[i].trans.Keys.n > 0) {
			ptr->bonesdata[i].t_keys = malloc(
					lk_bone.trans.Keys.n * sizeof(Vec3DArray));
			for (j = 0; j < lk_bone.trans.Keys.n; j++) {
				if (ptr->animofs[i].t_keys[j].n > 0) {
					ptr->bonesdata[i].t_keys[j].values = malloc(
							ptr->animofs[i].t_keys[j].n * sizeof(Vec3D));
					fseek(lk_m2_file, ptr->animofs[i].t_keys[j].ofs, SEEK_SET);
					fread(ptr->bonesdata[i].t_keys[j].values, sizeof(Vec3D),
							ptr->animofs[i].t_keys[j].n, lk_m2_file);
				}
			}
		}
		//rotation
		if (ptr->bones[i].rot.Times.n > 0) {
			ptr->bonesdata[i].r_times = malloc(
					lk_bone.rot.Times.n * sizeof(Uint32Array));
			for (j = 0; j < lk_bone.rot.Times.n; j++) {
				if (ptr->animofs[i].r_times[j].n > 0) {
					ptr->bonesdata[i].r_times[j].values = malloc(
							ptr->animofs[i].r_times[j].n * sizeof(uint32));
					fseek(lk_m2_file, ptr->animofs[i].r_times[j].ofs, SEEK_SET);
					fread(ptr->bonesdata[i].r_times[j].values, sizeof(uint32),
							ptr->animofs[i].r_times[j].n, lk_m2_file);
				}
			}
		}
		if (ptr->bones[i].rot.Keys.n > 0) {
			ptr->bonesdata[i].r_keys = malloc(
					lk_bone.rot.Keys.n * sizeof(QuatArray));
			for (j = 0; j < lk_bone.rot.Keys.n; j++) {
				if (ptr->animofs[i].r_keys[j].n > 0) {
					ptr->bonesdata[i].r_keys[j].values = malloc(
							ptr->animofs[i].r_keys[j].n * sizeof(Quat));
					fseek(lk_m2_file, ptr->animofs[i].r_keys[j].ofs, SEEK_SET);
					int test;
					test = fread(ptr->bonesdata[i].r_keys[j].values,
							sizeof(Quat), ptr->animofs[i].r_keys[j].n,
							lk_m2_file);
				}
			}
		}
		//scaling
		if (ptr->bones[i].scal.Times.n > 0) {
			ptr->bonesdata[i].s_times = malloc(
					lk_bone.scal.Times.n * sizeof(Uint32Array));
			for (j = 0; j < lk_bone.scal.Times.n; j++) {
				if (ptr->animofs[i].s_times[j].n > 0) {
					ptr->bonesdata[i].s_times[j].values = malloc(
							ptr->animofs[i].s_times[j].n * sizeof(uint32));
					fseek(lk_m2_file, ptr->animofs[i].s_times[j].ofs, SEEK_SET);
					fread(ptr->bonesdata[i].s_times[j].values, sizeof(uint32),
							ptr->animofs[i].s_times[j].n, lk_m2_file);
				}
			}
		}
		if (ptr->bones[i].scal.Keys.n > 0) {
			ptr->bonesdata[i].s_keys = malloc(
					lk_bone.scal.Keys.n * sizeof(Vec3DArray));
			for (j = 0; j < lk_bone.scal.Keys.n; j++) {
				if (ptr->animofs[i].s_keys[j].n > 0) {
					ptr->bonesdata[i].s_keys[j].values = malloc(
							ptr->animofs[i].s_keys[j].n * sizeof(Vec3D));
					fseek(lk_m2_file, ptr->animofs[i].s_keys[j].ofs, SEEK_SET);
					fread(ptr->bonesdata[i].s_keys[j].values, sizeof(Vec3D),
							ptr->animofs[i].s_keys[j].n, lk_m2_file);
				}
			}
		}
	}
	return 0;
}

/**
 * Read texture animations. WIP
 * @param lk_m2_file The file to read data.
 * @param ptr Pointer to a M2/WotLK structure.
 */
int read_texanims(FILE *lk_m2_file, LKM2 *ptr) {
	if (ptr->header.nTexAnims > 0) {
		ptr->tex_anims = malloc(
				ptr->header.nTexAnims * sizeof(LKTextureAnimation));
		fseek(lk_m2_file, ptr->header.ofsTexAnims, SEEK_SET);
		fread(&ptr->tex_anims, sizeof(LKTextureAnimation),
				ptr->header.nTexAnims, lk_m2_file);

		//read addresses to real animation data
		int i;
		for (i = 0; i < ptr->header.nTexAnims; i++) {
			//translation
			ptr->temp_anim_ofs = malloc(
					ptr->header.nTexAnims * sizeof(LKAnimOfs));
			if (ptr->tex_anims[i].Translation.Times.n > 0) {
				fseek(lk_m2_file, ptr->tex_anims[i].Translation.Times.ofs,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_times.n, sizeof(int), 1,
						lk_m2_file);

				fseek(lk_m2_file, ptr->tex_anims[i].Translation.Times.ofs + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_times.ofs, sizeof(int), 1,
						lk_m2_file);
			} else {
				ptr->temp_anim_ofs[i].t_times.n = 0;
				ptr->temp_anim_ofs[i].t_times.ofs = 0;
			}
			if (ptr->tex_anims[i].Translation.Keys.n > 0) {
				fseek(lk_m2_file, ptr->tex_anims[i].Translation.Keys.ofs,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_keys.n, sizeof(int), 1,
						lk_m2_file);

				fseek(lk_m2_file, ptr->tex_anims[i].Translation.Keys.ofs + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].t_keys.ofs, sizeof(int), 1,
						lk_m2_file);
			} else {
				ptr->temp_anim_ofs[i].t_keys.n = 0;
				ptr->temp_anim_ofs[i].t_keys.ofs = 0;
			}
			//Rotation
			if (ptr->tex_anims[i].Rotation.Times.n > 0) {
				fseek(lk_m2_file, ptr->tex_anims[i].Rotation.Times.ofs,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_times.n, sizeof(int), 1,
						lk_m2_file);

				fseek(lk_m2_file, ptr->tex_anims[i].Rotation.Times.ofs + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_times.ofs, sizeof(int), 1,
						lk_m2_file);
			} else {
				ptr->temp_anim_ofs[i].r_times.n = 0;
				ptr->temp_anim_ofs[i].r_times.ofs = 0;
			}
			if (ptr->tex_anims[i].Rotation.Keys.n > 0) {
				fseek(lk_m2_file, ptr->tex_anims[i].Rotation.Keys.ofs,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_keys.n, sizeof(int), 1,
						lk_m2_file);

				fseek(lk_m2_file, ptr->tex_anims[i].Rotation.Keys.ofs + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].r_keys.ofs, sizeof(int), 1,
						lk_m2_file);
			} else {
				ptr->temp_anim_ofs[i].r_keys.n = 0;
				ptr->temp_anim_ofs[i].r_keys.ofs = 0;
			}
			//Scaling
			if (ptr->tex_anims[i].Scaling.Times.n > 0) {
				fseek(lk_m2_file, ptr->tex_anims[i].Scaling.Times.ofs,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_times.n, sizeof(int), 1,
						lk_m2_file);

				fseek(lk_m2_file, ptr->tex_anims[i].Scaling.Times.ofs + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_times.ofs, sizeof(int), 1,
						lk_m2_file);
			} else {
				ptr->temp_anim_ofs[i].s_times.n = 0;
				ptr->temp_anim_ofs[i].s_times.ofs = 0;
			}
			if (ptr->tex_anims[i].Scaling.Keys.n > 0) {
				fseek(lk_m2_file, ptr->tex_anims[i].Scaling.Keys.ofs,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_keys.n, sizeof(int), 1,
						lk_m2_file);

				fseek(lk_m2_file, ptr->tex_anims[i].Scaling.Keys.ofs + 0x4,
				SEEK_SET);
				fread(&ptr->temp_anim_ofs[i].s_keys.ofs, sizeof(int), 1,
						lk_m2_file);
			} else {
				ptr->temp_anim_ofs[i].s_keys.n = 0;
				ptr->temp_anim_ofs[i].s_keys.ofs = 0;
			}
		}
		return 0;
	}
	return -1;
}

/**
 * Each substructure in the M2 has a variable size except the header.
 * Memory for each substructure must therefore be allocated at reading depending on header values.
 * @param lk_m2_file The file to read data.
 * @param ptr Pointer to a M2/WotLK structure.
 */
int read_model(FILE *lk_m2_file, LKM2 *ptr) {
	//Header
	fseek(lk_m2_file, 0, SEEK_SET);
	fread(&ptr->header, sizeof(LKModelHeader), 1, lk_m2_file);

	//Name
	ptr->filename = malloc(ptr->header.nameLength);
	fseek(lk_m2_file, ptr->header.nameOfs, SEEK_SET);
	fread(ptr->filename, sizeof(char), ptr->header.nameLength, lk_m2_file);

	//Global Sequences
	ptr->globalsequences = malloc(
			ptr->header.nGlobalSequences * sizeof(unsigned int));
	if (ptr->header.nGlobalSequences > 0) {
		fseek(lk_m2_file, ptr->header.ofsGlobalSequences, SEEK_SET);
		fread(ptr->globalsequences, sizeof(unsigned int),
				ptr->header.nGlobalSequences, lk_m2_file);
	}

	//Animations
	ptr->animations = malloc(
			ptr->header.nAnimations * sizeof(LKModelAnimation));
	fseek(lk_m2_file, ptr->header.ofsAnimations, SEEK_SET);
	fread(ptr->animations, sizeof(LKModelAnimation), ptr->header.nAnimations,
			lk_m2_file);

	//Bones
	read_bones(lk_m2_file, ptr);

	//Skeleton Bone Lookup
	ptr->keybonelookup = malloc(ptr->header.nKeyBoneLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsKeyBoneLookup, SEEK_SET);
	fread(ptr->keybonelookup, sizeof(short), ptr->header.nKeyBoneLookup,
			lk_m2_file);

	//Vertices
	ptr->vertices = malloc(ptr->header.nVertices * sizeof(ModelVertex));
	fseek(lk_m2_file, ptr->header.ofsVertices, SEEK_SET);
	fread(ptr->vertices, sizeof(ModelVertex), ptr->header.nVertices,
			lk_m2_file);

//FIXME malloc()s... inside or before the "if" ?
	//Colors
	if (ptr->header.nColors > 0) {
		ptr->colors = malloc(ptr->header.nColors * sizeof(LKColorDef));
		ptr->colorsdata = malloc(ptr->header.nColors * sizeof(ColorDataBlock));
		fseek(lk_m2_file, ptr->header.ofsColors, SEEK_SET);
		fread(ptr->colors, sizeof(LKColorDef), ptr->header.nColors, lk_m2_file);

		//Color Data Block
		int temp_ofs[2];
		fseek(lk_m2_file, ptr->colors[0].RGB.Times.ofs, SEEK_SET);
		fread(&temp_ofs, sizeof(int), 2, lk_m2_file);
		fseek(lk_m2_file, temp_ofs[1], SEEK_SET);
		fread(ptr->colorsdata, sizeof(ColorDataBlock), ptr->header.nColors,
				lk_m2_file);
	};

	//Textures Definition
	ptr->textures_def = malloc(ptr->header.nTextures * sizeof(ModelTextureDef));
	fseek(lk_m2_file, ptr->header.ofsTextures, SEEK_SET);
	fread(ptr->textures_def, sizeof(ModelTextureDef), ptr->header.nTextures,
			lk_m2_file);

	//Transparency
	if (ptr->header.nTransparency > 0) {
		ptr->transparencies = malloc(
				ptr->header.nTransparency * sizeof(Transparency));
		fseek(lk_m2_file, ptr->header.ofsTransparency, SEEK_SET);
		fread(ptr->transparencies, sizeof(Transparency),
				ptr->header.nTransparency, lk_m2_file);
	}

	//TexAnims
	read_texanims(lk_m2_file, ptr);

	//Render Flags
	ptr->renderflags = malloc(ptr->header.nRenderFlags * sizeof(int));
	fseek(lk_m2_file, ptr->header.ofsRenderFlags, SEEK_SET);
	fread(ptr->renderflags, sizeof(int), ptr->header.nRenderFlags, lk_m2_file);

	//Bone Lookup Table
	ptr->BoneLookupTable = malloc(ptr->header.nBoneLookupTable * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsBoneLookupTable, SEEK_SET);
	fread(ptr->BoneLookupTable, sizeof(short), ptr->header.nBoneLookupTable,
			lk_m2_file);

	//Texture Lookup Table
	ptr->TexLookupTable = malloc(ptr->header.nTexLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsTexLookup, SEEK_SET);
	fread(ptr->TexLookupTable, sizeof(short), ptr->header.nTexLookup,
			lk_m2_file);

	//TexUnit
	ptr->TexUnit = malloc(ptr->header.nTexUnitLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsTexUnitLookup, SEEK_SET);
	fread(ptr->TexUnit, sizeof(short), ptr->header.nTexUnitLookup, lk_m2_file);

	//TransLookup
	ptr->TransparencyLookup = malloc(
			ptr->header.nTransparencyLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsTransparencyLookup, SEEK_SET);
	fread(ptr->TransparencyLookup, sizeof(short),
			ptr->header.nTransparencyLookup, lk_m2_file);

	//TexAnimLookup
	ptr->TexAnimLookup = malloc(ptr->header.nTexAnimLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsTexAnimLookup, SEEK_SET);
	fread(ptr->TexAnimLookup, sizeof(short), ptr->header.nTexAnimLookup,
			lk_m2_file);

	//BoundingTriangles
	ptr->BoundingTriangles = malloc(
			ptr->header.nBoundingTriangles * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsBoundingTriangles, SEEK_SET);
	fread(ptr->BoundingTriangles, sizeof(short), ptr->header.nBoundingTriangles,
			lk_m2_file);
	//BoundingVertices
	ptr->BoundingVertices = malloc(
			ptr->header.nBoundingVertices * sizeof(BoundingVertice));
	fseek(lk_m2_file, ptr->header.ofsBoundingVertices, SEEK_SET);
	fread(ptr->BoundingVertices, sizeof(BoundingVertice),
			ptr->header.nBoundingVertices, lk_m2_file);

	//BoundingNormals
	ptr->BoundingNormals = malloc(
			ptr->header.nBoundingNormals * sizeof(BoundingNormal));
	fseek(lk_m2_file, ptr->header.ofsBoundingNormals, SEEK_SET);
	fread(ptr->BoundingNormals, sizeof(BoundingNormal),
			ptr->header.nBoundingNormals, lk_m2_file);
	return 0;
}
