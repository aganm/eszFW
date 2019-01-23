/**
 * @file Resources.h
 * @ingroup Resources
 */

#ifndef _INIT_H_
#define _INIT_H_

#define ENT_PLAYER       0
#define OBJ_PLAYER_SPAWN 0

#include <eszFW.h>

typedef struct Resources_t
{
    Entity *pstEntity[1];
    Object *pstObject[1];

    Audio      *pstAudio;
    Background *pstBackground;
    Camera     *pstCamera;
    Font       *pstFont;
    Input      *pstInput;
    Map        *pstMap;
    Music      *pstMusic;
    Sprite     *pstSprite;
    Video      *pstVideo;
} Resources;

void FreeResources(Resources **pstResources);
int InitResources(Resources **pstResources);

#endif // _RESOURCES_H_
