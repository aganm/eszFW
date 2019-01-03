/**
 * @file Video.h
 * @ingroup Video
 */

#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <SDL2/SDL.h>
#include <stdint.h>
#include "Config.h"

typedef struct Video_t
{
    SDL_Renderer *pstRenderer;
    SDL_Window   *pstWindow;
    int32_t       s32WindowHeight;
    int32_t       s32WindowWidth;
    double        dZoomLevel;
    double        dInitialZoomLevel;
} Video;

void FreeVideo(Video **pstVideo);

int InitVideo(
    const int32_t s32WindowWidth,
    const int32_t s32WindowHeight,
    const bool    bFullscreen,
    Video       **pstVideo);

void RenderScene(SDL_Renderer **pstRenderer);
int SetFullscreen(const bool dFullscreen, Video **pstVideo);
int SetZoomLevel(const double dZoomLevel, Video **pstVideo);

#endif // _VIDEO_H_
