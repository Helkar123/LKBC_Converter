/**
 * @file
 */
#include <stdio.h>
#include "common.h"

char *model_name;

/**
 * The origin of these bugged anims is unknown to the community so far. Known bugged animations :
 * EmoteUseStanding
 * EmoteWorkNoSheathe
 * EmoteUseStandingNoSheathe
 * EmoteEatNoSheathe
 * EmoteSaluteNoSheathe
 * @param ID
 * @return
 */
int isBugged(int flags) {
	//if (ID == 63 || ID == 136 || ID == 138 || ID == 199 || ID == 210) {
	if (flags == 64) {
		return 1;
	}
	return 0;
}
