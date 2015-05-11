/**
 * @file
 * File reading routines
 */

#include "structures.h"

/**
 * Structure of a M2/WotLK model
 */
typedef struct LKM2File{
	LKModelHeader lk_header;
	char *lk_filename;
	unsigned int *globalsequences;
	LKModelAnimation *lk_animations;
	LKModelBoneDef *lk_bones;
	short *keybonelookup;
	ModelVertex *vertices;
	LKColorDef *lkcolors;
	ColorDataBlock *colorsdata;
	ModelTextureDef *textures_def;
	Transparency *transparencies;
	LKTextureAnimation *lk_tex_anims;
	LKAnimOfs *lk_temp_anim_ofs;
	int *renderflags;
	short *BoneLookupTable;
	short *TexLookupTable;
	short *TexUnit;
	short *TransparencyLookup;
	short *TexAnimLookup;
	short *BoundingTriangles;
	BoundingVertice *BoundingVertices;
	BoundingNormal *BoundingNormals;
}LKM2File;
