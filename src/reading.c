/**
 * @file
 * File reading routines
 */

#include <stdio.h>
#include <stdlib.h>
#include "reading.h"

/**
 * @param skin_files A list of pointers to skin files to read data from.
 * @param ptr A pointer to a list of skins structure where data will be written.
 * @param n The number of skin files. Between 1 and 4.
 */
int read_skins(FILE **skin_files, Skin **ptr, int n) {
	int i;
	*ptr = malloc(n * sizeof(Skin));
	for (i = 0; i < n; i++) {
		//Header
		fseek(skin_files[i], 0, SEEK_SET);
		fread(&(*ptr)[i].header, sizeof(SkinHeader), 1, skin_files[i]);

		//Indices
		if ((*ptr)[i].header.nIndices > 0) {
			(*ptr)[i].Indices = malloc(
					(*ptr)[i].header.nIndices * sizeof(Vertex));
			fseek(skin_files[i], (*ptr)[i].header.ofsIndices, SEEK_SET);
			fread((*ptr)[i].Indices, sizeof(Vertex), (*ptr)[i].header.nIndices,
					skin_files[i]);
		}

		//Triangles
		if ((*ptr)[i].header.nTriangles > 0) {
			(*ptr)[i].Triangles = malloc(
					((*ptr)[i].header.nTriangles / 3) * sizeof(Triangle));
			fseek(skin_files[i], (*ptr)[i].header.ofsTriangles, SEEK_SET);
			fread((*ptr)[i].Triangles, sizeof(Triangle),
					(*ptr)[i].header.nTriangles / 3, skin_files[i]);
		}

		//Properties
		if ((*ptr)[i].header.nProperties > 0) {
			(*ptr)[i].Properties = malloc(
					(*ptr)[i].header.nProperties * sizeof(Property));
			fseek(skin_files[i], (*ptr)[i].header.ofsProperties, SEEK_SET);
			fread((*ptr)[i].Properties, sizeof(Property),
					(*ptr)[i].header.nProperties, skin_files[i]);
		}

		//Submeshes
		if ((*ptr)[i].header.nSubmeshes > 0) {
			(*ptr)[i].Submeshes = malloc(
					(*ptr)[i].header.nSubmeshes * sizeof(LKSubmesh));
			fseek(skin_files[i], (*ptr)[i].header.ofsSubmeshes, SEEK_SET);
			fread((*ptr)[i].Submeshes, sizeof(LKSubmesh),
					(*ptr)[i].header.nSubmeshes, skin_files[i]);
		}

		//TexUnits
		if ((*ptr)[i].header.nTextureUnits > 0) {
			(*ptr)[i].TextureUnits = malloc(
					(*ptr)[i].header.nTextureUnits * sizeof(TexUnit));
			fseek(skin_files[i], (*ptr)[i].header.ofsTextureUnits, SEEK_SET);
			fread((*ptr)[i].TextureUnits, sizeof(TexUnit),
					(*ptr)[i].header.nTextureUnits, skin_files[i]);
		}
	}
	return 0;
}

void read_layer1(FILE *lk_m2_file, LKAnimationBlock *ptrBlock,
		AnimRefs *ptrAnimRefs){
		ptrAnimRefs->times = malloc(ptrBlock->Times.n * sizeof(ArrayRef));
		fseek(lk_m2_file, ptrBlock->Times.ofs, SEEK_SET);
		fread(ptrAnimRefs->times, sizeof(ArrayRef), ptrBlock->Times.n,
				lk_m2_file);

		ptrAnimRefs->keys = malloc(ptrBlock->Keys.n * sizeof(ArrayRef));
		fseek(lk_m2_file, ptrBlock->Keys.ofs, SEEK_SET);
		fread(ptrAnimRefs->keys, sizeof(ArrayRef), ptrBlock->Keys.n,
				lk_m2_file);
}
void read_Vec3DAnimBlock(FILE *lk_m2_file, LKAnimationBlock *ptrBlock,
		AnimRefs *ptrAnimRefs, Vec3D_LKSubBlock **ptrDataBlock) {
	if (ptrBlock->Times.n > 0) {
		//Layer 1
		read_layer1(lk_m2_file, ptrBlock, ptrAnimRefs);
		//Layer 2
		(*ptrDataBlock) = malloc(ptrBlock->Times.n * sizeof(Vec3D_LKSubBlock)); //Each Array_Ref leads to an array of elements (and there are Times.n of them, as seen previously)
		int j;
		for (j = 0; j < ptrBlock->Times.n; j++) {
			if (ptrAnimRefs->times[j].n > 0) {
				(*ptrDataBlock)[j].times = malloc(
						ptrAnimRefs->times[j].n * sizeof(uint32)); //The number of elements was found previously in this function (stored in animofs)
				fseek(lk_m2_file, ptrAnimRefs->times[j].ofs,
				SEEK_SET);
				fread((*ptrDataBlock)[j].times, sizeof(uint32),
						ptrAnimRefs->times[j].n, lk_m2_file);
			}
			if (ptrAnimRefs->keys[j].n > 0) {
				(*ptrDataBlock)[j].keys = malloc(
						ptrAnimRefs->keys[j].n * sizeof(Vec3D));
				fseek(lk_m2_file, ptrAnimRefs->keys[j].ofs,
				SEEK_SET);
				fread((*ptrDataBlock)[j].keys, sizeof(Vec3D),
						ptrAnimRefs->keys[j].n, lk_m2_file);
			}
		}
	}
}

void read_QuatAnimBlock(FILE *lk_m2_file, LKAnimationBlock *ptrBlock,
		AnimRefs *ptrAnimRefs, Quat_LKSubBlock **ptrDataBlock) {
	if (ptrBlock->Times.n > 0) {
		//Layer 1
		read_layer1(lk_m2_file, ptrBlock, ptrAnimRefs);
		//Layer 2
		(*ptrDataBlock) = malloc(ptrBlock->Times.n * sizeof(Quat_LKSubBlock)); //Each Array_Ref leads to an array of elements (and there are Times.n of them, as seen previously)
		int j;
		for (j = 0; j < ptrBlock->Times.n; j++) {
			if (ptrAnimRefs->times[j].n > 0) {
				(*ptrDataBlock)[j].times = malloc(
						ptrAnimRefs->times[j].n * sizeof(uint32)); //The number of elements was found previously in this function (stored in animofs)
				fseek(lk_m2_file, ptrAnimRefs->times[j].ofs,
				SEEK_SET);
				fread((*ptrDataBlock)[j].times, sizeof(uint32),
						ptrAnimRefs->times[j].n, lk_m2_file);
			}
			if (ptrAnimRefs->keys[j].n > 0) {
				(*ptrDataBlock)[j].keys = malloc(
						ptrAnimRefs->keys[j].n * sizeof(Quat));
				fseek(lk_m2_file, ptrAnimRefs->keys[j].ofs,
				SEEK_SET);
				fread((*ptrDataBlock)[j].keys, sizeof(Quat),
						ptrAnimRefs->keys[j].n, lk_m2_file);
			}
		}
	}
}

void read_ShortAnimBlock(FILE *lk_m2_file, LKAnimationBlock *ptrBlock,
		AnimRefs *ptrAnimRefs, Short_LKSubBlock **ptrDataBlock) {
	if (ptrBlock->Times.n > 0) {
		//Layer 1
		read_layer1(lk_m2_file, ptrBlock, ptrAnimRefs);
		//Layer 2
		(*ptrDataBlock) = malloc(ptrBlock->Times.n * sizeof(Short_LKSubBlock)); //Each Array_Ref leads to an array of elements (and there are Times.n of them, as seen previously)
		int j;
		for (j = 0; j < ptrBlock->Times.n; j++) {
			if (ptrAnimRefs->times[j].n > 0) {
				(*ptrDataBlock)[j].times = malloc(
						ptrAnimRefs->times[j].n * sizeof(uint32)); //The number of elements was found previously in this function (stored in animofs)
				fseek(lk_m2_file, ptrAnimRefs->times[j].ofs,
				SEEK_SET);
				fread((*ptrDataBlock)[j].times, sizeof(uint32),
						ptrAnimRefs->times[j].n, lk_m2_file);
			}
			if (ptrAnimRefs->keys[j].n > 0) {
				(*ptrDataBlock)[j].keys = malloc(
						ptrAnimRefs->keys[j].n * sizeof(short));
				fseek(lk_m2_file, ptrAnimRefs->keys[j].ofs,
				SEEK_SET);
				fread((*ptrDataBlock)[j].keys, sizeof(short),
						ptrAnimRefs->keys[j].n, lk_m2_file);
			}
		}
	}
}
/**
 * Read model bones with animations. WIP
 * @param lk_m2_file The file to read data.
 * @param ptr Pointer to a M2/WotLK structure.
 * i is a bone number, j is an animation number
 */
int read_bones(FILE *lk_m2_file, LKM2 *ptr) {
	if (ptr->header.nBones > 0) { //I think lights and other non-geometric things don't have any
		ptr->bones = malloc(ptr->header.nBones * sizeof(LKModelBoneDef));
		fseek(lk_m2_file, ptr->header.ofsBones, SEEK_SET);
		fread(ptr->bones, sizeof(LKModelBoneDef), ptr->header.nBones,
				lk_m2_file);

		/*This function is a good example of reading LK Animation Blocks and ArrayRefs.
		 * In the Block, you have what I call an ArrayRef : a number of elements and a file-relative offset to the first element.
		 * In LKAnimBlock, you have ArrayRefs of ArrayRefs. So you have to work by layers. One structure is required per layer.
		 *
		 * In the first, you store the n ArrayRefs you got by following the Block ArrayRef.
		 *
		 * In the second, you store the arrays of elements you get by following each layer 1 ArrayRef obtained in step one. So there are n of them.
		 * Remember each of these arrays of elements in the layer 2 has a custom size, given by its corresponding layer 1 ArrayRef.
		 */

		//Store animofs (layer 1)
		//This allows later to read the real animation data, by following each ArrayRef.
		ptr->animofs = malloc(ptr->header.nBones * sizeof(RefBlock));//1 LKRefBlock per bone
		//Store bones data (layer 2)
		ptr->bonesdata = malloc(ptr->header.nBones * sizeof(LKBonesDataBlock));
		int i;
		for (i = 0; i < ptr->header.nBones; i++) {
			LKAnimationBlock *ptrBlock;
			AnimRefs *ptrAnimRefs;
			Vec3D_LKSubBlock **Vec3D_ptrDataBlock;
			Quat_LKSubBlock **Quat_ptrDataBlock;

			//Translation
			ptrBlock = &ptr->bones[i].trans;
			ptrAnimRefs = &ptr->animofs[i].trans;
			Vec3D_ptrDataBlock = &ptr->bonesdata[i].trans;
			read_Vec3DAnimBlock(lk_m2_file, ptrBlock, ptrAnimRefs,
					Vec3D_ptrDataBlock);
			//Rotation
			ptrBlock = &ptr->bones[i].rot;
			ptrAnimRefs = &ptr->animofs[i].rot;
			Quat_ptrDataBlock = &ptr->bonesdata[i].rot;
			read_QuatAnimBlock(lk_m2_file, ptrBlock, ptrAnimRefs,
					Quat_ptrDataBlock);
			//Scaling
			ptrBlock = &ptr->bones[i].scal;
			ptrAnimRefs = &ptr->animofs[i].scal;
			Vec3D_ptrDataBlock = &ptr->bonesdata[i].scal;
			read_Vec3DAnimBlock(lk_m2_file, ptrBlock, ptrAnimRefs,
					Vec3D_ptrDataBlock);
		}
		return 0;
	}
	return -1;
}

/**
 * Read colors (also known as submesh animations)
 * @param lk_m2_file
 * @param ptr
 * @return
 */
int read_colors(FILE *lk_m2_file, LKM2 *ptr) {
	if (ptr->header.nColors > 0) {
		ptr->colors = malloc(ptr->header.nColors * sizeof(LKColorDef));
		fseek(lk_m2_file, ptr->header.ofsColors, SEEK_SET);
		fread(ptr->colors, sizeof(LKColorDef), ptr->header.nColors,
				lk_m2_file);
		ptr->coloranimofs = malloc(ptr->header.nColors * sizeof(ColorRefBlock));
		ptr->colorsdata = malloc(ptr->header.nColors * sizeof(LKColorDataBlock));
		int i;
		for (i = 0; i < ptr->header.nColors; i++) {
			LKAnimationBlock *ptrBlock;
			AnimRefs *ptrAnimRefs;
			Vec3D_LKSubBlock **Vec3D_ptrDataBlock;
			Short_LKSubBlock **Short_ptrDataBlock;

			//RGB
			ptrBlock = &ptr->colors[i].rgb;
			ptrAnimRefs = &ptr->coloranimofs[i].rgb;
			Vec3D_ptrDataBlock = &ptr->colorsdata[i].rgb;
			read_Vec3DAnimBlock(lk_m2_file, ptrBlock, ptrAnimRefs,
					Vec3D_ptrDataBlock);
			//Opacity
			ptrBlock = &ptr->colors[i].opacity;
			ptrAnimRefs = &ptr->coloranimofs[i].opacity;
			Short_ptrDataBlock = &ptr->colorsdata[i].opacity;
			read_ShortAnimBlock(lk_m2_file, ptrBlock, ptrAnimRefs,
					Short_ptrDataBlock);
		}
		return 0;
	}
	return -1;
}

/**
 * Read texture animations. WIP
 * @param lk_m2_file The file to read data.
 * @param ptr Pointer to a M2/WotLK structure.
 * @return 0 if successful
 * @author Stan84
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
			//Translation
			ptr->temp_anim_ofs = malloc(
					ptr->header.nTexAnims * sizeof(RefBlockSimple));
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
 * At the moment, this function is used to debug the converter by checking data on genuine BC models.
 * @param bc_m2_file
 * @param ptr
 * @return
 */
int read_model_bc(FILE *bc_m2_file, BCM2 *ptr) {
	//Header
	fseek(bc_m2_file, 0, SEEK_SET);
	fread(&ptr->header, sizeof(ModelHeader), 1, bc_m2_file);

	//Animations
	ptr->animations = malloc(ptr->header.nAnimations * sizeof(ModelAnimation));
	fseek(bc_m2_file, ptr->header.ofsAnimations, SEEK_SET);
	fread(ptr->animations, sizeof(ModelAnimation), ptr->header.nAnimations,
			bc_m2_file);

	//Bones
	if (ptr->header.nBones > 0) { //I think lights and other non-geometric things don't have any
		ptr->bones = malloc(ptr->header.nBones * sizeof(ModelBoneDef));
		ptr->bonesdata = malloc(ptr->header.nBones * sizeof(BonesDataBlock));
		fseek(bc_m2_file, ptr->header.ofsBones, SEEK_SET);
		fread(ptr->bones, sizeof(ModelBoneDef), ptr->header.nBones, bc_m2_file);
		int i;
		for (i = 0; i < ptr->header.nBones; i++) {
			//Translation
			if (ptr->bones[i].trans.Ranges.n > 0) {
				ptr->bonesdata[i].trans.ranges = malloc(
						ptr->bones[i].trans.Ranges.n * sizeof(Range));
				fseek(bc_m2_file, ptr->bones[i].trans.Ranges.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].trans.ranges, sizeof(Range),
						ptr->bones[i].trans.Ranges.n, bc_m2_file);
			}
			if (ptr->bones[i].trans.Times.n > 0) {
				ptr->bonesdata[i].trans.times = malloc(
						ptr->bones[i].trans.Times.n * sizeof(uint32));
				fseek(bc_m2_file, ptr->bones[i].trans.Times.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].trans.times, sizeof(uint32),
						ptr->bones[i].trans.Times.n, bc_m2_file);
			}
			if (ptr->bones[i].trans.Keys.n > 0) {
				ptr->bonesdata[i].trans.keys = malloc(
						ptr->bones[i].trans.Keys.n * sizeof(Vec3D));
				fseek(bc_m2_file, ptr->bones[i].trans.Keys.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].trans.keys, sizeof(Vec3D),
						ptr->bones[i].trans.Keys.n, bc_m2_file);
			}
			//Rotation
			if (ptr->bones[i].rot.Ranges.n > 0) {
				ptr->bonesdata[i].rot.ranges = malloc(
						ptr->bones[i].rot.Ranges.n * sizeof(Range));
				fseek(bc_m2_file, ptr->bones[i].rot.Ranges.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].rot.ranges, sizeof(Range),
						ptr->bones[i].rot.Ranges.n, bc_m2_file);
			}
			if (ptr->bones[i].rot.Times.n > 0) {
				ptr->bonesdata[i].rot.times = malloc(
						ptr->bones[i].rot.Times.n * sizeof(uint32));
				fseek(bc_m2_file, ptr->bones[i].rot.Times.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].rot.times, sizeof(uint32),
						ptr->bones[i].rot.Times.n, bc_m2_file);
			}
			if (ptr->bones[i].rot.Keys.n > 0) {
				ptr->bonesdata[i].rot.keys = malloc(
						ptr->bones[i].rot.Keys.n * sizeof(Quat));
				fseek(bc_m2_file, ptr->bones[i].rot.Keys.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].rot.keys, sizeof(Quat),
						ptr->bones[i].rot.Keys.n, bc_m2_file);
			}
			//Scaling
			if (ptr->bones[i].scal.Ranges.n > 0) {
				ptr->bonesdata[i].scal.ranges = malloc(
						ptr->bones[i].scal.Ranges.n * sizeof(Range));
				fseek(bc_m2_file, ptr->bones[i].scal.Ranges.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].scal.ranges, sizeof(Range),
						ptr->bones[i].scal.Ranges.n, bc_m2_file);
			}
			if (ptr->bones[i].scal.Times.n > 0) {
				ptr->bonesdata[i].scal.times = malloc(
						ptr->bones[i].scal.Times.n * sizeof(uint32));
				fseek(bc_m2_file, ptr->bones[i].scal.Times.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].scal.times, sizeof(uint32),
						ptr->bones[i].scal.Times.n, bc_m2_file);
			}
			if (ptr->bones[i].scal.Keys.n > 0) {
				ptr->bonesdata[i].scal.keys = malloc(
						ptr->bones[i].scal.Keys.n * sizeof(Vec3D));
				fseek(bc_m2_file, ptr->bones[i].scal.Keys.ofs, SEEK_SET);
				fread(ptr->bonesdata[i].scal.keys, sizeof(Vec3D),
						ptr->bones[i].scal.Keys.n, bc_m2_file);
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

	//Animations Lookup Table
	ptr->AnimLookup = malloc(ptr->header.nAnimationLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsAnimationLookup, SEEK_SET);
	fread(ptr->AnimLookup, sizeof(short), ptr->header.nAnimationLookup,
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

	//Colors
	read_colors(lk_m2_file, ptr);

	//Textures Definition
	if (ptr->header.nTextures > 0) {
		ptr->textures_def = malloc(
				ptr->header.nTextures * sizeof(ModelTextureDef));
		fseek(lk_m2_file, ptr->header.ofsTextures, SEEK_SET);
		fread(ptr->textures_def, sizeof(ModelTextureDef), ptr->header.nTextures,
				lk_m2_file);
		//textures names
		ptr->texture_names = malloc(ptr->header.nTextures * sizeof(char *));
		int i;
		for (i = 0; i < ptr->header.nTextures; i++) {
			if (ptr->textures_def[i].type == 0) { //Filename is referenced in the m2 only when the type is 0
				if (ptr->textures_def[i].nameLen >= 256) {
					fprintf(stderr,
							"nameLen too large : %d\nPlease report this issue.",
							ptr->textures_def[i].nameLen);
					return -1;
				}
				ptr->texture_names[i] = malloc(ptr->textures_def[i].nameLen);
				fseek(lk_m2_file, ptr->textures_def[i].nameOfs, SEEK_SET);
				fread(ptr->texture_names[i], sizeof(char),
						ptr->textures_def[i].nameLen, lk_m2_file);
			}
		}
	}

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
	ptr->BoneLookupTable = malloc(ptr->header.nBoneLookupTable * sizeof(int16));
	fseek(lk_m2_file, ptr->header.ofsBoneLookupTable, SEEK_SET);
	fread(ptr->BoneLookupTable, sizeof(int16), ptr->header.nBoneLookupTable,
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
			ptr->header.nBoundingTriangles / 3 * sizeof(Triangle));
	fseek(lk_m2_file, ptr->header.ofsBoundingTriangles, SEEK_SET);
	fread(ptr->BoundingTriangles, sizeof(Triangle),
			ptr->header.nBoundingTriangles / 3, lk_m2_file);

	//BoundingVertices
	ptr->BoundingVertices = malloc(
			ptr->header.nBoundingVertices * sizeof(Vec3D));
	fseek(lk_m2_file, ptr->header.ofsBoundingVertices, SEEK_SET);
	fread(ptr->BoundingVertices, sizeof(Vec3D), ptr->header.nBoundingVertices,
			lk_m2_file);

	//BoundingNormals
	ptr->BoundingNormals = malloc(ptr->header.nBoundingNormals * sizeof(Vec3D));
	fseek(lk_m2_file, ptr->header.ofsBoundingNormals, SEEK_SET);
	fread(ptr->BoundingNormals, sizeof(Vec3D), ptr->header.nBoundingNormals,
			lk_m2_file);

	//TODO Attachments

	//Attachment Lookup Table
	ptr->AttachLookup = malloc(ptr->header.nAttachLookup * sizeof(short));
	fseek(lk_m2_file, ptr->header.ofsAttachLookup, SEEK_SET);
	fread(ptr->AttachLookup, sizeof(short), ptr->header.nAttachLookup,
			lk_m2_file);
	return 0;
}
