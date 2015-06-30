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
typedef int Range[2];
typedef short Quat[4];
typedef float Vec3D[3];
typedef float Vec2D[2];
typedef uint16 Triangle[3]; //Indices for Triangles
typedef uint16 Vertex; //The vertex in the global vertex list
typedef uint32 Property; //Bones Indices into BoneLookupTable
typedef Vec3D BigFloat[3];

typedef struct PlayAnimRecord {
	int16 ID;
	int16 flags;
}PlayAnimRecord;
typedef struct ArrayRef { //Can point to absolutely anything
	uint32 n;
	uint32 ofs;
} ArrayRef;

/*Arrays with an unknown size*/

typedef struct RangeArray {
	Range *values;
} RangeArray;
typedef struct Uint32Array {
	uint32 *values;
} Uint32Array;
typedef struct Vec3DArray {
	Vec3D *values;
} Vec3DArray;
typedef struct QuatArray {
	Quat *values;
} QuatArray;
typedef struct ShortArray {
	short *values;
} ShortArray;

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
	uint32 nEvents; 					//0x100 Events
	uint32 ofsEvents;				//0x104
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
	uint32 nEvents; 					//0x114
	uint32 ofsEvents;				//0x118
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
	uint32 flags;
	int16 probability;
	int16 unused;
	uint32 d1;
	uint32 d2;
	uint32 playSpeed;				//BlendTime
	Vec3D boxA;				//MinimumExtent
	Vec3D boxB;				//MaximumExtent
	float rad;				//BoundsRadius
	int16 NextAnimation;
	uint16 Index;
} LKModelAnimation;

typedef struct ModelAnimation {
	int16 animID;
	int16 subAnimID;
	uint32 timeStart;
	uint32 timeEnd;
	float moveSpeed;
	uint32 flags;				//LoopType
	uint16 probability;
	uint16 unused;
	uint32 d1;
	uint32 d2;
	uint32 playSpeed;
	Vec3D boxA;
	Vec3D boxB;
	float rad;
	int16 NextAnimation;
	uint16 Index;
} ModelAnimation;

typedef struct PlayableAnimationLookup {
	int16 FallbackAnimationID;  //In AnimationData.DBC
	int16 Flags;
} PlayableAnimationLookup;

typedef struct LKAnimationBlock {
	int16 type;
	int16 seq;
	ArrayRef Times;  //links to i ArraysRefs of j uint32
	ArrayRef Keys;  //links to i ArrayRefs of j elements
} LKAnimationBlock;

typedef struct AnimationBlock {
	int16 type;
	int16 seq;
	ArrayRef Ranges;  //links to i interpolations ranges of type (int,int)
	ArrayRef Times;  //links to i uint32
	ArrayRef Keys;  //links to i elements
} AnimationBlock;

//SubBlocks
typedef struct Vec3D_LKSubBlock{
	uint32 *times;
	Vec3D *keys;
}Vec3D_LKSubBlock;
typedef struct Vec3D_SubBlock{
	Range *ranges;
	uint32 *times;
	Vec3D *keys;
}Vec3D_SubBlock;

typedef struct Quat_LKSubBlock{
	uint32 *times;
	Quat *keys;
}Quat_LKSubBlock;
typedef struct Quat_SubBlock{
	Range *ranges;
	uint32 *times;
	Quat *keys;
}Quat_SubBlock;

typedef struct Short_LKSubBlock{
	uint32 *times;
	short *keys;
}Short_LKSubBlock;
typedef struct Short_SubBlock{
	Range *ranges;
	uint32 *times;
	short *keys;
}Short_SubBlock;

typedef struct Int_LKSubBlock{
	uint32 *times;
	int *keys;
}Int_LKSubBlock;
typedef struct Int_SubBlock{
	Range *ranges;
	uint32 *times;
	int *keys;
}Int_SubBlock;

typedef struct BigFloat_LKSubBlock{
	uint32 *times;
	BigFloat *keys;
}BigFloat_LKSubBlock;
typedef struct BigFloat_SubBlock{
	Range *ranges;
	uint32 *times;
	BigFloat *keys;
}BigFloat_SubBlock;

typedef struct AnimRefs{
	ArrayRef *times;
	ArrayRef *keys;
}AnimRefs;

typedef struct ModelVertex {
	Vec3D pos;
	uint8 weights[4];
	uint8 bones[4];
	Vec3D normal;
	Vec2D texcoords;
	Vec2D texcoords2;
} ModelVertex;

//Bones
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
typedef struct RefBlock {
	AnimRefs trans;
	AnimRefs rot;
	AnimRefs scal;
} RefBlock;
typedef struct LKBonesDataBlock {
	Vec3D_LKSubBlock *trans;
	Quat_LKSubBlock *rot;
	Vec3D_LKSubBlock *scal;
} LKBonesDataBlock;
typedef struct BonesDataBlock {
	Vec3D_SubBlock trans;
	Quat_SubBlock rot;
	Vec3D_SubBlock scal;
} BonesDataBlock;

//Attachments
typedef struct LKAttachment {
	uint32 ID;
	uint32 bone;
	Vec3D position;
	LKAnimationBlock data;
} LKAttachment;
typedef struct Attachment {
	uint32 ID;
	uint32 bone;
	Vec3D position;
	AnimationBlock data;
} Attachment;
typedef struct AttachmentsRefBlock {
	AnimRefs data;
} AttachmentsRefBlock;
typedef struct LKAttachmentsDataBlock {
	Int_LKSubBlock *data;
} LKAttachmentsDataBlock;
typedef struct AttachmentsDataBlock {
	Int_SubBlock data;
} AttachmentsDataBlock;

//Cameras
typedef struct LKCamera {
	uint32 Type;
	float FOV;
	float farClipping;
	float nearClipping;
	LKAnimationBlock transpos;
	Vec3D position;
	LKAnimationBlock transtar;
	Vec3D target;
	LKAnimationBlock scal;
} LKCamera;
typedef struct Camera {
	uint32 Type;
	float FOV;
	float farClipping;
	float nearClipping;
	AnimationBlock transpos;
	Vec3D position;
	AnimationBlock transtar;
	Vec3D target;
	AnimationBlock scal;
} Camera;
typedef struct CamerasRefBlock {
	AnimRefs transpos;
	AnimRefs transtar;
	AnimRefs scal;
} CamerasRefBlock;
typedef struct LKCamerasDataBlock {
	BigFloat_LKSubBlock *transpos;
	BigFloat_LKSubBlock *transtar;
	Vec3D_LKSubBlock *scal;
} LKCamerasDataBlock;
typedef struct CamerasDataBlock {
	BigFloat_SubBlock transpos;
	BigFloat_SubBlock transtar;
	Vec3D_SubBlock scal;
} CamerasDataBlock;

//Colors
typedef struct LKColorDef {
	LKAnimationBlock rgb;
	LKAnimationBlock opacity;
} LKColorDef;
typedef struct ColorDef {
	AnimationBlock rgb;
	AnimationBlock opacity;
} ColorDef;
typedef struct ColorRefBlock {
	AnimRefs rgb;
	AnimRefs opacity;
} ColorRefBlock;
typedef struct LKColorDataBlock {
	Vec3D_LKSubBlock *rgb;
	Short_LKSubBlock *opacity;
} LKColorDataBlock;
typedef struct ColorDataBlock {
	Vec3D_SubBlock rgb;
	Short_SubBlock opacity;
} ColorDataBlock;

//Transparency
typedef struct LKTransparency {
	LKAnimationBlock alpha;
} LKTransparency;
typedef struct Transparency {
	AnimationBlock alpha;
} Transparency;
typedef struct TransparencyRefBlock{
	AnimRefs alpha;
}TransparencyRefBlock;
typedef struct LKTransparencyDataBlock {
	Short_LKSubBlock *alpha;
} LKTransparencyDataBlock;
typedef struct TransparencyDataBlock {
	Short_SubBlock alpha;
} TransparencyDataBlock;


//TODO TexAnims
typedef struct RefBlockSimple { //Temporary, for TexAnims. Remnant of Stan84's code.
	ArrayRef t_times;
	ArrayRef t_keys;
	ArrayRef r_times;
	ArrayRef r_keys;
	ArrayRef s_times;
	ArrayRef s_keys;
} RefBlockSimple;

typedef struct SkinHeader {
	uint32 ID;
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
	uint16 ID;
	uint16 Level; //level*(2^16)+StartThing
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
	uint16 ID;
	uint16 Level; //EXPERIMENTAL : No mention of this in the Wiki, but the LK level might have always been there.
	uint16 StartVertex;
	uint16 nVertices;
	uint16 StartTriangle;
	uint16 nTriangles;
	uint16 nBones;
	uint16 StartBones;
	uint16 boneInfluences; //Amount of bones up the parent-chain affecting the submesh
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
	Triangle* Triangles;
	Property *Properties;
	Submesh *Submeshes;
	TexUnit *TextureUnits;
} View;

//Events
typedef struct EventsRefBlock{
	ArrayRef *times;
}EventsRefBlock;
typedef struct LKEventsDataBlock {
	uint32 **times;
} LKEventsDataBlock;
typedef struct EventsDataBlock {
	Range *ranges;
	uint32 *times;
} EventsDataBlock;

typedef struct LKEventAnimBlock {
	int16 type;
	int16 seq;
	ArrayRef Times;  //links to i ArraysRefs of j uint32
} LKEventAnimBlock;

typedef struct EventAnimBlock {
	int16 type;
	int16 seq;
	ArrayRef Ranges;  //links to i interpolations ranges of type (int,int)
	ArrayRef Times;  //links to i uint32
} EventAnimBlock;

typedef struct LKEvent {
	char ID[4];
	uint32 data;
	uint32 bone;
	Vec3D position;
	LKEventAnimBlock timer;
}LKEvent;
typedef struct Event {
	char ID[4];
	uint32 data;
	uint32 bone;
	Vec3D position;
	EventAnimBlock timer;
}Event;

//FILES

/**
 * Structure of a M2/WotLK model
 */
typedef struct LKM2 {
	LKModelHeader header;
	char *filename;
	unsigned int *globalsequences;
	LKModelAnimation *animations;
	int16 *AnimLookup;

	LKModelBoneDef *bones;
	RefBlock *animofs; //bones layer 1
	LKBonesDataBlock *bonesdata; //bones layer 2

	short *keybonelookup;
	ModelVertex *vertices;

	LKColorDef *colors;
	ColorRefBlock *coloranimofs;
	LKColorDataBlock *colorsdata;

	ModelTextureDef *textures_def;
	char **texture_names;

	LKTransparency *transparencyrefs;
	TransparencyRefBlock *transparencyanimofs;
	LKTransparencyDataBlock *transparencydata;

	LKTextureAnimation *tex_anims;
	RefBlockSimple *temp_anim_ofs;

	short *TexReplace;
	int *renderflags;
	int16 *BoneLookupTable;
	short *TexLookupTable;
	short *TexUnit;
	short *TransparencyLookup;
	short *TexAnimLookup;
	Triangle *BoundingTriangles;
	Vec3D *BoundingVertices;
	Vec3D *BoundingNormals;

	LKAttachment *attachments;
	AttachmentsRefBlock *attachmentsanimofs;
	LKAttachmentsDataBlock *attachmentsdata;
	uint16 *AttachLookup;

	LKEvent *events;
	EventsRefBlock *eventsanimofs;
	LKEventsDataBlock *eventsdata;

	LKCamera *cameras;
	CamerasRefBlock *camerasanimofs;
	LKCamerasDataBlock *camerasdata;
	uint16 *CameraLookup;
/*TODO Events, Lights, Cameras,
 * CameraLookup, RibbonEmitters, ParticleEmmiters.
 */
} LKM2;

/**
 * Structure of Skin/WotLK resources
 */
typedef struct Skin {
	SkinHeader header;
	Vertex *Indices;
	Triangle* Triangles;
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
	int16 *AnimLookup;
	PlayAnimRecord *PlayAnimLookup;

	ModelBoneDef *bones;
	BonesDataBlock *bonesdata;

	short *keybonelookup; //Skeletal Bone Lookup
	ModelVertex *vertices;
	View *views;

	ColorDef *colors;
	ColorDataBlock *colorsdata;

	ModelTextureDef *textures_def;
	char **texture_names;

	Transparency *transparencyrefs;
	TransparencyDataBlock *transparencydata;

	TextureAnimation *tex_anims;
	short *TexReplace;
	int *renderflags;
	int16 *BoneLookupTable;
	short *TexLookupTable;
	short *TexUnit;
	short *TransparencyLookup;
	short *TexAnimLookup;
	Triangle *BoundingTriangles;
	Vec3D *BoundingVertices;
	Vec3D *BoundingNormals;

	Attachment *attachments;
	AttachmentsDataBlock *attachmentsdata;
	uint16 *AttachLookup;

	Event *events;
	EventsDataBlock *eventsdata;

	Camera *cameras;
	CamerasDataBlock *camerasdata;
	uint16 *CameraLookup;
/*TODO Lights, Cameras,
 * CameraLookup, RibbonEmitters, ParticleEmmiters.
 */
} BCM2;

#endif
