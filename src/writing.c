/**
 * @file
 * File writing routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writing.h"

/**
 * Find the address of the file's end.
 * @param file A file opened as stream.
 */
unsigned int getPos(FILE *file) {
	unsigned int file_end;
	fseek(file, 0, SEEK_END);
	file_end = ftell(file);
	return file_end;
}

/**
 * Check position after writing and fill with zeros
 * @param file
 * @return the number of zeros written
 */
int align(FILE *file) {
	unsigned int get_pos = getPos(file);
	size_t count = 16 - (get_pos & 0xF);
	char zeros[count];
	memset(zeros, 0, count * sizeof(char));
	fwrite(zeros, sizeof(char), count, file);
	return count;
}

/**
 * @param bc_m2_file The file to write data.
 * @param ptr A pointer to a M2/BC structure.
 * Write a M2/BC file from its corresponding structure
 */
int write_model(FILE *bc_m2_file, BCM2 *ptr) {
	//header
	fwrite(&ptr->header, sizeof(ModelHeader), 1, bc_m2_file);
	align(bc_m2_file);

	//filename
	ptr->header.nameOfs = getPos(bc_m2_file);
	fwrite(ptr->filename, sizeof(char), ptr->header.nameLength, bc_m2_file);
	align(bc_m2_file);

	//animations
	if (ptr->header.nAnimations > 0) {
		ptr->header.ofsAnimations = getPos(bc_m2_file);
		fwrite(ptr->animations, sizeof(ModelAnimation), ptr->header.nAnimations,
				bc_m2_file);
		align(bc_m2_file);
	}

	//bones
	if (ptr->header.nBones > 0) {
		ptr->header.ofsBones = getPos(bc_m2_file);
		fwrite(ptr->bones, sizeof(ModelBoneDef), ptr->header.nBones,
				bc_m2_file);
		align(bc_m2_file);
		int i;
		for (i = 0; i < ptr->header.nBones; i++) {
			//translation
			if (ptr->bones[i].trans.Ranges.n > 0) {
				ptr->bones[i].trans.Ranges.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].t_ranges.values, sizeof(Range),
						ptr->bones[i].trans.Ranges.n, bc_m2_file);
				align(bc_m2_file);
			}

			if (ptr->bones[i].trans.Times.n > 0) {
				ptr->bones[i].trans.Times.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].t_times.values, sizeof(uint32),
						ptr->bones[i].trans.Times.n, bc_m2_file);
				align(bc_m2_file);
			}

			if (ptr->bones[i].trans.Keys.n > 0) {
				ptr->bones[i].trans.Keys.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].t_keys.values, sizeof(Vec3D),
						ptr->bones[i].trans.Keys.n, bc_m2_file);
				align(bc_m2_file);
			}
			//rotation
			if (ptr->bones[i].rot.Ranges.n > 0) {
				ptr->bones[i].rot.Ranges.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].r_ranges.values, sizeof(Range),
						ptr->bones[i].rot.Ranges.n, bc_m2_file);
				align(bc_m2_file);
			}

			if (ptr->bones[i].rot.Times.n > 0) {
				ptr->bones[i].rot.Times.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].r_times.values, sizeof(uint32),
						ptr->bones[i].rot.Times.n, bc_m2_file);
				align(bc_m2_file);
			}

			if (ptr->bones[i].rot.Keys.n > 0) {
				ptr->bones[i].rot.Keys.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].r_keys.values, sizeof(Quat),
						ptr->bones[i].rot.Keys.n, bc_m2_file);
				align(bc_m2_file);
			}
			//scaling
			if (ptr->bones[i].scal.Ranges.n > 0) {
				ptr->bones[i].scal.Ranges.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].s_ranges.values, sizeof(Range),
						ptr->bones[i].scal.Ranges.n, bc_m2_file);
				align(bc_m2_file);
			}

			if (ptr->bones[i].scal.Times.n > 0) {
				ptr->bones[i].scal.Times.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].s_times.values, sizeof(uint32),
						ptr->bones[i].scal.Times.n, bc_m2_file);
				align(bc_m2_file);
			}

			if (ptr->bones[i].scal.Keys.n > 0) {
				ptr->bones[i].scal.Keys.ofs = getPos(bc_m2_file);
				fwrite(ptr->bonesdata[i].s_keys.values, sizeof(Vec3D),
						ptr->bones[i].scal.Keys.n, bc_m2_file);
				align(bc_m2_file);
			}
		}
	}
	fseek(bc_m2_file, ptr->header.ofsBones, SEEK_SET);
	fwrite(ptr->bones, sizeof(ModelBoneDef), ptr->header.nBones, bc_m2_file);
	fseek(bc_m2_file, 0, SEEK_END);

	//animlookup
	if (ptr->header.nAnimationLookup > 0) {
		ptr->header.ofsAnimationLookup = getPos(bc_m2_file);
		fwrite(ptr->AnimLookup, sizeof(int16), ptr->header.nAnimationLookup,
				bc_m2_file);
		align(bc_m2_file);
	}

	//keybonelookup
	if (ptr->header.nKeyBoneLookup > 0) {
		ptr->header.ofsKeyBoneLookup = getPos(bc_m2_file);
		fwrite(ptr->keybonelookup, sizeof(short), ptr->header.nKeyBoneLookup,
				bc_m2_file);
		align(bc_m2_file);
	}

	//vertices
	if (ptr->header.nVertices > 0) {
		ptr->header.ofsVertices = getPos(bc_m2_file);
		fwrite(ptr->vertices, sizeof(ModelVertex), ptr->header.nVertices,
				bc_m2_file);
		align(bc_m2_file);
	}
	//views
	if (ptr->header.nViews > 0) {
		ptr->header.ofsViews = getPos(bc_m2_file);
		int i;
		for (i = 0; i < ptr->header.nViews; i++) {
			int header_offset = getPos(bc_m2_file);
			fwrite(&ptr->views[i].header, sizeof(ViewsHeader), 1, bc_m2_file);
			align(bc_m2_file);

			if (ptr->views[i].header.nIndices > 0) {
				ptr->views[i].header.ofsIndices = getPos(bc_m2_file);
				fwrite(ptr->views[i].Indices, sizeof(Vertex),
						ptr->views[i].header.nIndices, bc_m2_file);
				align(bc_m2_file);
			}
			if (ptr->views[i].header.nTriangles > 0) {
				ptr->views[i].header.ofsTriangles = getPos(bc_m2_file);
				fwrite(ptr->views[i].Triangles, sizeof(Indices),
						ptr->views[i].header.nTriangles / 3, bc_m2_file);
				align(bc_m2_file);
			}
			if (ptr->views[i].header.nProperties > 0) {
				ptr->views[i].header.ofsProperties = getPos(bc_m2_file);
				fwrite(ptr->views[i].Properties, sizeof(Property),
						ptr->views[i].header.nProperties, bc_m2_file);
				align(bc_m2_file);
			}
			if (ptr->views[i].header.nSubmeshes > 0) {
				ptr->views[i].header.ofsSubmeshes = getPos(bc_m2_file);
				fwrite(ptr->views[i].Submeshes, sizeof(Submesh),
						ptr->views[i].header.nSubmeshes, bc_m2_file);
				align(bc_m2_file);
			}
			if (ptr->views[i].header.nTextureUnits > 0) {
				ptr->views[i].header.ofsTextureUnits = getPos(bc_m2_file);
				fwrite(ptr->views[i].TextureUnits, sizeof(TexUnit),
						ptr->views[i].header.nTextureUnits, bc_m2_file);
				align(bc_m2_file);
			}

			fseek(bc_m2_file, header_offset, SEEK_SET);
			fwrite(&ptr->views[i].header, sizeof(ViewsHeader), 1, bc_m2_file);
			fseek(bc_m2_file, 0, SEEK_END);
		}
	}

	//TODO Colors

	//textures
	if (ptr->header.nTextures > 0) {
		ptr->header.ofsTextures = getPos(bc_m2_file);
		fwrite(ptr->textures_def, sizeof(ModelTextureDef),
				ptr->header.ofsTextures, bc_m2_file);
		align(bc_m2_file);
		int i;
		for(i=0; i <ptr->header.nTextures; i++){
			if(ptr->textures_def[i].type == 0){
				ptr->textures_def[i].nameOfs = getPos(bc_m2_file);
				fwrite(ptr->texture_names[i], sizeof(char), ptr->textures_def[i].nameLen, bc_m2_file);
				align(bc_m2_file);
			}
		}

		fseek(bc_m2_file, ptr->header.ofsTextures, SEEK_SET);
		fwrite(ptr->textures_def, sizeof(ModelTextureDef),
				ptr->header.ofsTextures, bc_m2_file);
		fseek(bc_m2_file, 0, SEEK_END);
	}

	//rewrite the header with updated offsets
	fseek(bc_m2_file, 0, SEEK_SET);
	fwrite(&ptr->header, sizeof(ModelHeader), 1, bc_m2_file);

	return 0;
}
