/**
 * @file
 * Conversion functions
 */

#include "structures.h"

/**
 * Header conversion
 * @param lk_header LK M2 Header.
 * @return A TBC Header.
 */
ModelHeader header_converter(LKModelHeader lk_header) {
	ModelHeader tbc_header;

	tbc_header.id = lk_header.id;
	//TODO version=0x107 if the model has particles
	tbc_header.version = 0x104;
	tbc_header.nameLength = lk_header.nameLength;
	tbc_header.nameOfs = 0x150;
	tbc_header.GlobalModelFlags = lk_header.GlobalModelFlags;
	tbc_header.nGlobalSequences = lk_header.nGlobalSequences;
	tbc_header.ofsGlobalSequences = lk_header.ofsGlobalSequences;
	tbc_header.nAnimations = lk_header.nAnimations;
	tbc_header.ofsAnimations = lk_header.ofsAnimations;
	tbc_header.nAnimationLookup = lk_header.nAnimationLookup;
	tbc_header.ofsAnimationLookup = lk_header.ofsAnimationLookup;
	tbc_header.nPlayableAnimationLookup = 0xcb; //Placeholder
	tbc_header.ofsPlayableAnimationLookup = 0x00; //Determine where you insert the Data block from above
	tbc_header.nBones = lk_header.nBones;
	tbc_header.ofsBones = lk_header.ofsBones;
	tbc_header.nKeyBoneLookup = lk_header.nKeyBoneLookup;
	tbc_header.ofsKeyBoneLookup = lk_header.ofsKeyBoneLookup;
	tbc_header.nVertices = lk_header.nVertices;
	tbc_header.ofsVertices = lk_header.ofsVertices;
	tbc_header.nViews = lk_header.nViews;
	tbc_header.ofsViews = 0x00;
	tbc_header.nColors = lk_header.nColors;
	tbc_header.ofsColors = lk_header.ofsColors;
	tbc_header.nTextures = lk_header.nTextures;
	tbc_header.ofsTextures = lk_header.ofsTextures;
	tbc_header.nTransparency = lk_header.nTransparency;
	tbc_header.ofsTransparency = lk_header.ofsTransparency;
	tbc_header.nI = 0x00;
	tbc_header.ofsI = 0x00;
	tbc_header.nTexAnims = lk_header.nTexAnims;
	tbc_header.ofsTexAnims = lk_header.ofsTexAnims;
	tbc_header.nTexReplace = lk_header.nTexReplace;
	tbc_header.ofsTexReplace = lk_header.ofsTexReplace;
	tbc_header.nRenderFlags = lk_header.nRenderFlags;
	tbc_header.ofsRenderFlags = lk_header.ofsRenderFlags;
	tbc_header.nBoneLookupTable = lk_header.nBoneLookupTable;
	tbc_header.ofsBoneLookupTable = lk_header.ofsBoneLookupTable;
	tbc_header.nTexLookup = lk_header.nTexLookup;
	tbc_header.ofsTexLookup = lk_header.ofsTexLookup;
	tbc_header.nTexUnitLookup = lk_header.nTexUnitLookup;
	tbc_header.ofsTexUnitLookup = lk_header.ofsTexUnitLookup;
	tbc_header.nTransparencyLookup = lk_header.nTransparencyLookup;
	tbc_header.ofsTransparencyLookup = lk_header.ofsTransparencyLookup;
	tbc_header.nTexAnimLookup = lk_header.nTexAnimLookup;
	tbc_header.ofsTexAnimLookup = lk_header.ofsTexAnimLookup;
	tbc_header.nBoundingTriangles = lk_header.nBoundingTriangles;
	tbc_header.ofsBoundingTriangles = lk_header.ofsBoundingTriangles;
	tbc_header.nBoundingVertices = lk_header.nBoundingVertices;
	tbc_header.ofsBoundingVertices = lk_header.ofsBoundingVertices;
	tbc_header.nBoundingNormals = lk_header.nBoundingNormals;
	tbc_header.ofsBoundingNormals = lk_header.ofsBoundingNormals;
	tbc_header.nAttachments = lk_header.nAttachments;
	tbc_header.ofsAttachments = lk_header.ofsAttachments;
	tbc_header.nAttachLookup = lk_header.nAttachLookup;
	tbc_header.ofsAttachLookup = lk_header.ofsAttachLookup;
	tbc_header.nAttachments_2 = lk_header.nAttachments_2;
	tbc_header.ofsAttachments_2 = lk_header.ofsAttachments_2;
	tbc_header.nLights = lk_header.nLights;
	tbc_header.ofsLights = lk_header.ofsLights;
	tbc_header.nCameras = lk_header.nCameras;
	tbc_header.ofsCameras = lk_header.ofsCameras;
	tbc_header.nCameraLookup = lk_header.nCameraLookup;
	tbc_header.ofsCameraLookup = lk_header.ofsCameraLookup;
	tbc_header.nRibbonEmitters = lk_header.nRibbonEmitters;
	tbc_header.ofsRibbonEmitters = lk_header.ofsRibbonEmitters;
	tbc_header.nParticleEmitters = lk_header.nParticleEmitters;
	tbc_header.ofsParticleEmitters = lk_header.ofsParticleEmitters;
	int i = 0;
	for (i = 0; i < 14; i++) {
		tbc_header.floats[i] = lk_header.floats[i];
	}
	return tbc_header;
}

/**
 *
 * @param lk_tex_anim
 * @return
 */
TextureAnimation tex_anim_converter(LKTextureAnimation lk_tex_anim) {
	//TODO proper ranges
	TextureAnimation tex_anim;
	tex_anim.Translation.type = lk_tex_anim.Translation.type;
	tex_anim.Translation.seq = lk_tex_anim.Translation.seq;
	tex_anim.Translation.Ranges.n = 0;
	tex_anim.Translation.Ranges.ofs = 0;
	tex_anim.Translation.Times.n = lk_tex_anim.Translation.Times.n;
	tex_anim.Translation.Times.ofs = lk_tex_anim.Translation.Times.ofs;
	tex_anim.Translation.Keys.n = lk_tex_anim.Translation.Keys.n;
	tex_anim.Translation.Keys.ofs = lk_tex_anim.Translation.Keys.ofs;

	tex_anim.Rotation.type = lk_tex_anim.Rotation.type;
	tex_anim.Rotation.seq = lk_tex_anim.Rotation.seq;
	tex_anim.Rotation.Ranges.n = 0;
	tex_anim.Rotation.Ranges.ofs = 0;
	tex_anim.Rotation.Times.n = lk_tex_anim.Rotation.Times.n;
	tex_anim.Rotation.Times.ofs = lk_tex_anim.Rotation.Times.ofs;
	tex_anim.Rotation.Keys.n = lk_tex_anim.Rotation.Keys.n;
	tex_anim.Rotation.Keys.ofs = lk_tex_anim.Rotation.Keys.ofs;

	tex_anim.Scaling.type = lk_tex_anim.Scaling.type;
	tex_anim.Scaling.seq = lk_tex_anim.Scaling.seq;
	tex_anim.Scaling.Ranges.n = 0;
	tex_anim.Scaling.Ranges.ofs = 0;
	tex_anim.Scaling.Times.n = lk_tex_anim.Scaling.Times.n;
	tex_anim.Scaling.Times.ofs = lk_tex_anim.Scaling.Times.ofs;
	tex_anim.Scaling.Keys.n = lk_tex_anim.Scaling.Keys.n;
	tex_anim.Scaling.Keys.ofs = lk_tex_anim.Scaling.Keys.ofs;

	return tex_anim;
}

/**
 * Convert a LKM2
 */
int lk_to_bc(LKM2 lk_m2, Skin *skins, BCM2 *ptr) {
	ptr->header = header_converter(lk_m2.header);

	/*
	 //views_header = views_converter(skin_header);

	 int i;
	 for (i = 0; i < ptr->header.nAnimations; i++) {
	 ptr->animations[i] = animation_converter(lk_m2.animations[i]);
	 }

	 // The amount of nAnimationLookup is assigned so far as the amount of animations
	 ptr->header.nAnimationLookup = lk_m2.header.nAnimations;

	 // The amount of PlayableAnimationLookup is assigned so far as the amount of animations
	 ptr->header.nPlayableAnimationLookup = lk_m2.header.nAnimations;

	 for (i = 0; i < ptr->header.nBones; i++) {
	 ptr->bones[i] = bone_converter(lk_m2.bones[i]);
	 }
	 */
	return 0;
}
