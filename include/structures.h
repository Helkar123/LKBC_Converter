/**
 * @file
 * M2 structures
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef float Vec3D[3];
typedef float Vec2D[2];

typedef struct LKModelHeader {
	uint32 id;								//0x000
	uint32 version;							//0x004
	uint32 nameLength;						//0x008
	uint32 nameOfs;							//0x00c
	uint32 GlobalModelFlags;				//0x010

	uint32 nGlobalSequences;				//0x014
	uint32 ofsGlobalSequences;				//0x018
	uint32 nAnimations;						//0x01c
	uint32 ofsAnimations;					//0x020
	uint32 nAnimationLookup;				//0x024
	uint32 ofsAnimationLookup;				//0x028
	uint32 nBones;							//0x02c
	uint32 ofsBones;						//0x030
	uint32 nKeyBoneLookup;					//0x034
	uint32 ofsKeyBoneLookup;				//0x038

	uint32 nVertices;						//0x03c
	uint32 ofsVertices;						//0x040
	uint32 nViews;							//0x044

	uint32 nColors;							//0x048
	uint32 ofsColors;						//0x04c

	uint32 nTextures;						//0x050
	uint32 ofsTextures;						//0x054

	uint32 nTransparency; 					//0x058
	uint32 ofsTransparency;					//0x05c
	uint32 nTexAnims;						//0x060
	uint32 ofsTexAnims;						//0x064
	uint32 nTexReplace;						//0x068
	uint32 ofsTexReplace;					//0x06c

	uint32 nRenderFlags;					//0x070
	uint32 ofsRenderFlags;					//0x074
	uint32 nBoneLookupTable;				//0x078
	uint32 ofsBoneLookupTable;				//0x07c

	uint32 nTexLookup;						//0x080
	uint32 ofsTexLookup;					//0x084

	uint32 nTexUnitLookup;					//0x088
	uint32 ofsTexUnitLookup;				//0x08c
	uint32 nTransparencyLookup; 			//0x090
	uint32 ofsTransparencyLookup;			//0x094
	uint32 nTexAnimLookup;					//0x098
	uint32 ofsTexAnimLookup;				//0x09c

	float floats[14];						//0x0a0

	uint32 nBoundingTriangles;				//0x0d8
	uint32 ofsBoundingTriangles;			//0x0dc
	uint32 nBoundingVertices;				//0x0e0
	uint32 ofsBoundingVertices;				//0x0e4
	uint32 nBoundingNormals;				//0x0e8
	uint32 ofsBoundingNormals;				//0x0ec

	uint32 nAttachments; 					//0x0f0
	uint32 ofsAttachments;					//0x0f4
	uint32 nAttachLookup; 					//0x0f8
	uint32 ofsAttachLookup;					//0x0fc
	uint32 nAttachments_2; 					//0x100
	uint32 ofsAttachments_2;				//0x104
	uint32 nLights; 						//0x108
	uint32 ofsLights;						//0x10c
	uint32 nCameras; 						//0x110
	uint32 ofsCameras;						//0x114
	uint32 nCameraLookup;					//0x118
	uint32 ofsCameraLookup;					//0x11c
	uint32 nRibbonEmitters; 				//0x120
	uint32 ofsRibbonEmitters;				//0x124
	uint32 nParticleEmitters; 				//0x128
	uint32 ofsParticleEmitters;				//0x12c

} LKModelHeader;

typedef struct ModelHeader {
	uint32 id;								//0x000
	uint32 version;							//0x004
	uint32 nameLength;						//0x008
	uint32 nameOfs;							//0x00c
	uint32 GlobalModelFlags;				//0x010

	uint32 nGlobalSequences;				//0x014
	uint32 ofsGlobalSequences;				//0x018
	uint32 nAnimations;						//0x01c
	uint32 ofsAnimations;					//0x020
	uint32 nAnimationLookup;				//0x024
	uint32 ofsAnimationLookup;				//0x028
	uint32 nPlayableAnimationLookup;		//0x02c
	uint32 ofsPlayableAnimationLookup;		//0x030
	uint32 nBones;							//0x034
	uint32 ofsBones;						//0x038
	uint32 nKeyBoneLookup;					//0x03c
	uint32 ofsKeyBoneLookup;				//0x040

	uint32 nVertices;						//0x044
	uint32 ofsVertices;						//0x048
	uint32 nViews;							//0x04c
	uint32 ofsViews;						//0x050

	uint32 nColors;							//0x054
	uint32 ofsColors;						//0x058

	uint32 nTextures;						//0x05c
	uint32 ofsTextures;						//0x060

	uint32 nTransparency; 					//0x064
	uint32 ofsTransparency;					//0x068
	uint32 nI;   							//0x06c
	uint32 ofsI;							//0x070
	uint32 nTexAnims;						//0x074
	uint32 ofsTexAnims;						//0x078
	uint32 nTexReplace;						//0x07c
	uint32 ofsTexReplace;					//0x080

	uint32 nRenderFlags;					//0x084
	uint32 ofsRenderFlags;					//0x088
	uint32 nBoneLookupTable;				//0x08c
	uint32 ofsBoneLookupTable;				//0x090

	uint32 nTexLookup;						//0x094
	uint32 ofsTexLookup;					//0x098

	uint32 nTexUnitLookup;					//0x09c
	uint32 ofsTexUnitLookup;				//0x0a0
	uint32 nTransparencyLookup; 			//0x0a4
	uint32 ofsTransparencyLookup;			//0x0a8
	uint32 nTexAnimLookup;					//0x0ac
	uint32 ofsTexAnimLookup;				//0x0b0

	float floats[14];						//0x0b4

	uint32 nBoundingTriangles;				//0x0ec
	uint32 ofsBoundingTriangles;			//0x0f0
	uint32 nBoundingVertices;				//0x0f4
	uint32 ofsBoundingVertices;				//0x0f8
	uint32 nBoundingNormals;				//0x0fc
	uint32 ofsBoundingNormals;				//0x100

	uint32 nAttachments; 					//0x104
	uint32 ofsAttachments;					//0x108
	uint32 nAttachLookup; 					//0x10c
	uint32 ofsAttachLookup;					//0x110
	uint32 nAttachments_2; 					//0x114
	uint32 ofsAttachments_2;				//0x118
	uint32 nLights; 						//0x11c
	uint32 ofsLights;						//0x120
	uint32 nCameras; 						//0x124
	uint32 ofsCameras;						//0x128
	uint32 nCameraLookup;					//0x12c
	uint32 ofsCameraLookup;					//0x130
	uint32 nRibbonEmitters; 				//0x134
	uint32 ofsRibbonEmitters;				//0x138
	uint32 nParticleEmitters; 				//0x13c
	uint32 ofsParticleEmitters;				//0x140

} ModelHeader;

typedef struct LKModelAnimation {
	int16 animID;
	int16 subAnimID;
	uint32 length;
	float moveSpeed;
	uint32 loopType;
	uint32 flags;
	uint32 d1;
	uint32 d2;
	uint32 playSpeed;
	Vec3D boxA, boxB;
	float rad;
	int16 NextAnimation;
	int16 Index;
} LKModelAnimation;

typedef struct ModelAnimation {
	uint32 animID;
	uint32 timeStart;
	uint32 timeEnd;
	float moveSpeed;
	uint32 loopType;
	uint32 flags;
	uint32 d1;
	uint32 d2;
	uint32 playSpeed;
	Vec3D boxA, boxB;
	float rad;
	int16 s[2];
} ModelAnimation;

typedef struct PlayableAnimationLookup {
	int16 FallbackAnimationID;  //In AnimationData.DBC
	int16 Flags;
} PlayableAnimationLookup;

typedef struct LKAnimationBlock {
	int16 type;
	int16 seq;
	uint32 nTimes;
	uint32 ofsTimes;
	uint32 nKeys;
	uint32 ofsKeys;
} LKAnimationBlock;

typedef struct AnimationBlock {
	int16 type;
	int16 seq;
	uint32 nRanges;
	uint32 ofsRanges;
	uint32 nTimes;
	uint32 ofsTimes;
	uint32 nKeys;
	uint32 ofsKeys;
} AnimationBlock;

typedef struct LKModelBoneDef {
	int32 animid;
	uint32 flags;
	int16 parent;
	uint16 geoid;
	int32 unk;

	int16 trans_type;
	int16 trans_seq;
	uint32 trans_nTimes;
	uint32 trans_ofsTimes;
	uint32 trans_nKeys;
	uint32 trans_ofsKeys;

	int16 rot_type;
	int16 rot_seq;
	uint32 rot_nTimes;
	uint32 rot_ofsTimes;
	uint32 rot_nKeys;
	uint32 rot_ofsKeys;

	int16 scal_type;
	int16 scal_seq;
	uint32 scal_nTimes;
	uint32 scal_ofsTimes;
	uint32 scal_nKeys;
	uint32 scal_ofsKeys;

	float pivot[3];
} LKModelBoneDef;

typedef struct ModelBoneDef {
	int32 animid;
	int32 flags;
	int16 parent;
	int16 geoid;
	int32 unk;

	int16 trans_type;
	int16 trans_seq;
	uint32 trans_nRanges;
	uint32 trans_ofsRanges;
	uint32 trans_nTimes;
	uint32 trans_ofsTimes;
	uint32 trans_nKeys;
	uint32 trans_ofsKeys;

	int16 rot_type;
	int16 rot_seq;
	uint32 rot_nRanges;
	uint32 rot_ofsRanges;
	uint32 rot_nTimes;
	uint32 rot_ofsTimes;
	uint32 rot_nKeys;
	uint32 rot_ofsKeys;

	int16 scal_type;
	int16 scal_seq;
	uint32 scal_nRanges;
	uint32 scal_ofsRanges;
	uint32 scal_nTimes;
	uint32 scal_ofsTimes;
	uint32 scal_nKeys;
	uint32 scal_ofsKeys;

	float pivot[3];
} ModelBoneDef;

typedef struct ModelVertex {
	Vec3D pos;
	uint8 weights[4];
	uint8 bones[4];
	Vec3D normal;
	Vec2D texcoords;
	int unk1, unk2;
} ModelVertex;

typedef struct LKAnimOfs {
	uint32 t_ntimes;
	uint32 t_ofstimes;
	uint32 t_nkeys;
	uint32 t_ofskeys;
	uint32 r_ntimes;
	uint32 r_ofstimes;
	uint32 r_nkeys;
	uint32 r_ofskeys;
	uint32 s_ntimes;
	uint32 s_ofstimes;
	uint32 s_nkeys;
	uint32 s_ofskeys;
} LKAnimOfs;

typedef struct SkinHeader {
	char ID[4];
	uint32 nIndices;
	uint32 ofsIndices;
	uint32 nTriangles;
	uint32 ofsTriangles;
	uint32 nProperties;
	uint32 ofsProperties;
	uint32 nSubmeshes;
	uint32 ofsSubmeshes;
	uint32 nTextureUnits;
	uint32 ofsTextureUnits;
	uint32 LOD;
} SkinHeader;

typedef struct ViewsHeader {
	uint32 nIndices;
	uint32 ofsIndices;
	uint32 nTriangles;
	uint32 ofsTriangles;
	uint32 nProperties;
	uint32 ofsProperties;
	uint32 nSubmeshes;
	uint32 ofsSubmeshes;
	uint32 nTextureUnits;
	uint32 ofsTextureUnits;
	uint32 LOD;
} ViewsHeader;

typedef struct Submesh {
	uint32 ID;
	uint16 StartVertex;
	uint16 nVertices;
	uint16 StartTriangle;
	uint16 nTriangles;
	uint16 nBones;
	uint16 StartBones;
	uint16 Unknown;
	uint16 RootBone;
	float Position[3];
	float Floats[4];
} Submesh;

typedef struct TexUnit {
	uint16 Flags;
	uint16 RenderOrder;
	uint16 SubmeshIndex1;
	uint16 SubmeshIndex2;
	int16 ColorIndex;
	uint16 RenderFlags;
	uint16 TexUnitNumber;
	uint16 one;
	uint16 Texture;
	uint16 TexUnitNumer2;
	uint16 Transparency;
	uint16 TexAnim;
} TexUnit;

typedef struct ModelTextureDef {
	uint32 type;
	uint32 flags;
	uint32 nameLen;
	uint32 nameOfs;
} ModelTextureDef;

typedef struct Transparency {
	AnimationBlock values;
} Transparency;

typedef struct TempOffset {
	int temp_n;
	int temp_ofs;
} TempOffset;

typedef struct BoundingVertice {
	Vec3D vertice;
} BoundingVertice;

typedef struct BoundingNormal {
	Vec3D normal;
} BoundingNormal;

typedef struct LKColorDef {
	LKAnimationBlock RGB;
	LKAnimationBlock Opacity;
} LKColorDef;

typedef struct ColorDef {
	AnimationBlock RGB;
	AnimationBlock Opacity;
} ColorDef;

typedef struct ColorDataBlock {
	int d1[4];
	int d2[4];
	int d3[4];
	int d4[4];

} ColorDataBlock;

typedef struct LKTextureAnimation {
	LKAnimationBlock Translation;
	LKAnimationBlock Rotation;
	LKAnimationBlock Scaling;
} LKTextureAnimation;

typedef struct TextureAnimation {
	AnimationBlock Translation;
	AnimationBlock Rotation;
	AnimationBlock Scaling;
} TextureAnimation;

///FILES///

/**
 * Structure of a M2/WotLK model
 */
typedef struct LKM2 {
	LKModelHeader header;
	char *filename;
	unsigned int *globalsequences;
	LKModelAnimation *animations;
	LKModelBoneDef *bones;
	LKAnimOfs *animofs;
	short *keybonelookup;
	ModelVertex *vertices;
	LKColorDef *colors;
	ColorDataBlock *colorsdata;
	ModelTextureDef *textures_def;
	Transparency *transparencies;
	LKTextureAnimation *tex_anims;
	LKAnimOfs *temp_anim_ofs;
	int *renderflags;
	short *BoneLookupTable;
	short *TexLookupTable;
	short *TexUnit;
	short *TransparencyLookup;
	short *TexAnimLookup;
	short *BoundingTriangles;
	BoundingVertice *BoundingVertices;
	BoundingNormal *BoundingNormals;
} LKM2;

/**
 * Structure of Skin/WotLK resources
 */
typedef struct Skin {
	SkinHeader header;
	//TODO Finish the structure
} Skin;

/**
 * Structure of a M2/BC model
 */
typedef struct BCM2 {
	ModelHeader header;
	char *filename;
	unsigned int *globalsequences;
	ModelAnimation *animations;
	ModelBoneDef *bones;
	short *keybonelookup;
	ModelVertex *vertices;
	ColorDef *colors;
	ColorDataBlock *colorsdata;
	ModelTextureDef *textures_def;
	Transparency *transparencies;
	TextureAnimation *tex_anims;
	int *renderflags;
	short *BoneLookupTable;
	short *TexLookupTable;
	short *TexUnit;
	short *TransparencyLookup;
	short *TexAnimLookup;
	short *BoundingTriangles;
	BoundingVertice *BoundingVertices;
	BoundingNormal *BoundingNormals;
} BCM2;
#endif
