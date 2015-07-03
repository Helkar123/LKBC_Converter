#ifndef PRINTER_H
#define PRINTER_H
#include "structures.h"

void print_anims_lk(LKM2 model);
void print_anims_bc(BCM2 model);
void print_skin(Skin skin);
void print_views(BCM2 model);
void print_transparency_bc(BCM2 model);
void print_transparency_lk(LKM2 model);
void print_events_lk(LKM2 model);
void print_events_bc(BCM2 model);
void print_cameras_bc(BCM2 model);
void print_bones(BCM2 model, char flags);
void print_bonesdata(LKM2 model);
void print_vertices_lk(LKM2 model);
void print_vertices_bc(BCM2 model);
void print_animlookup(BCM2 model);
void print_playanimlookup(BCM2 model);
void print_texnames_bc(BCM2 model);
void print_texnames_lk(LKM2 model);
void printBits(size_t const size, void const * const ptr);

#endif
