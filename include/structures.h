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
typedef short Quat[4];
typedef float Vec3D[3];
typedef float Vec2D[2];
typedef uint16 Indices[3]; //Indices for Triangles
typedef uint16 Vertex; //The vertex in the global vertex list
typedef uint8 Property[4]; //Bones Indices into BoneLookupTable

typedef struct ArrayRef {
	uint32 n;
	uint32 ofs;
} ArrayRef;

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
	ArrayRef Times;//links to i ArraysRefs of j uint32
	ArrayRef Keys;//links to i ArrayRefs of j elements
} LKAnimationBlock;

typedef struct AnimationBlock {
	int16 type;
	int16 seq;
	ArrayRef Ranges;//links to i interpolations ranges of type (uint32,uint32)
	ArrayRef Times;//links to i uint32
	ArrayRef Keys;//links to i elements
} AnimationBlock;

typedef struct LKModelBoneDef {
	int32 animid;
	uint32 flags;
	int16 parent;
	uint16 geoid;
	int32 unk;

	//Offsets link to a new nX ofsX
	LKAnimationBlock trans;
	LKAnimationBlock rot;
	LKAnimationBlock scal;

	Vec3D pivot;
} LKModelBoneDef;

typedef struct ModelBoneDef {
	int32 animid;
	int32 flags;
	int16 parent;
	int16 geoid;
	int32 unk;

	AnimationBlock trans;
	AnimationBlock rot;
	AnimationBlock scal;

	Vec3D pivot;
} ModelBoneDef;

typedef struct Uint32Array {
	uint32 *values;
} Uint32Array;
typedef struct Vec3DArray {
	Vec3D *values;
} Vec3DArray;
typedef struct QuatArray {
	Quat *values;
} QuatArray;

typedef struct BonesDataBlock {
	Uint32Array *t_times;
	Vec3DArray *t_keys;
	Uint32Array *r_times;
	QuatArray *r_keys;
	Uint32Array *s_times;
	Vec3DArray *s_keys;
} BonesDataBlock;

typedef struct ModelVertex {
	Vec3D pos;
	uint8 weights[4];
	uint8 bones[4];
	Vec3D normal;
	Vec2D texcoords;
	int unk1, unk2;
} ModelVertex;

typedef struct LKAnimOfs {
	ArrayRef *t_times;
	ArrayRef *t_keys;
	ArrayRef *r_times;
	ArrayRef *r_keys;
	ArrayRef *s_times;
	ArrayRef *s_keys;
} LKAnimOfs;

typedef struct LKAnimOfsSimple {//Temporary, for TexAnims. Remnant of Stan84's code.
	ArrayRef t_times;
	ArrayRef t_keys;
	ArrayRef r_times;
	ArrayRef r_keys;
	ArrayRef s_times;
	ArrayRef s_keys;
} LKAnimOfsSimple;

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

typedef struct LKSubmesh {
	uint32 ID;
	uint16 StartVertex;
	uint16 nVertices;
	uint16 StartTriangle;
	uint16 nTriangles;
	uint16 nBones;
	uint16 StartBones;
	uint16 boneInfluences;
	uint16 RootBone;
	Vec3D CenterMass;
	Vec3D CenterBoundingBox;
	float Radius;
} LKSubmesh;

typedef struct Submesh {
	uint32 ID;
	uint16 StartVertex;
	uint16 nVertices;
	uint16 StartTriangle;
	uint16 nTriangles;
	uint16 nBones;
	uint16 StartBones;
	uint16 Unknown;  //Amount of bones up the parent-chain affecting the submesh
	uint16 RootBone;
	Vec3D Position;
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

typedef struct View { //Only present in 2.x models. Replaced by Skin files in 3.x
	ViewsHeader header;
	Vertex *Indices;
	Indices* Triangles;
	Property *Properties;
	Submesh *Submeshes;
	TexUnit *TextureUnits;
} View;

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
	LKAnimOfs *animofs; //bones layer 1
	BonesDataBlock *bonesdata; //bones layer 2
	short *keybonelookup;
	ModelVertex *vertices;
	LKColorDef *colors;
	ColorDataBlock *colorsdata;
	ModelTextureDef *textures_def;
	Transparency *transparencies;
	LKTextureAnimation *tex_anims;
	LKAnimOfsSimple *temp_anim_ofs;
	int *renderflags;
	short *BoneLookupTable;
	short *TexLookupTable;
	short *TexUnit;
	short *TransparencyLookup;
	short *TexAnimLookup;
	short *BoundingTriangles;
	BoundingVertice *BoundingVertices;
	BoundingNormal *BoundingNormals;
/*TODO Attachments, AttachLookup, Events, Lights, Cameras,
 * CameraLookup, RibbonEmitters, ParticleEmmiters.
 */
} LKM2;

/**
 * Structure of Skin/WotLK resources
 */
typedef struct Skin {
	SkinHeader header;
	Vertex *Indices;
	Indices* Triangles;
	Property *Properties;
	LKSubmesh *Submeshes;
	TexUnit *TextureUnits;
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
	View *views;
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
/*TODO Attachments, AttachLookup, Attachments_2, Lights, Cameras,
 * CameraLookup, RibbonEmitters, ParticleEmmiters.
 */
} BCM2;
#endif
