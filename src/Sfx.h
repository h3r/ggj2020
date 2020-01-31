#ifndef SFX_HEADER__
#define SFX_HEADER__

#include <stdbool.h>
#include <psxspu.h>

/* *************************************
 *  Includes
 * *************************************/

/* *************************************
 *  Defines
 * *************************************/

#define MAX_VOLUME SPU_MAXVOL

#ifdef __cplusplus
#define EXTERNC extern "C"
#else /* __cplusplus */
#define EXTERNC
#endif /* __cplusplus */

 /* *************************************
 *  Structs and enums
 * *************************************/

/* *************************************
 *  Global prototypes
 * *************************************/
EXTERNC void SfxPlaySound(SsVag* sound);
EXTERNC void SfxStopSound(SsVag* sound);
EXTERNC void SfxPlaySoundVolVoice(SsVag* sound, const unsigned char voice, const unsigned short vol);
EXTERNC bool SfxUploadSound(const char* const file_path, SsVag* const vag);
EXTERNC void SfxVoiceVol(const unsigned char voice, const unsigned short volume);

#endif //SFX_HEADER__
