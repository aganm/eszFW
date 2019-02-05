/**
 * @file Video.c
 * @ingroup Video
 * @defgroup Video
 * @author Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include "Video.h"

void FreeVideo(Video *pstVideo)
{
    IMG_Quit();
    if (pstVideo)
    {
        if (pstVideo->pstRenderer)
        {
            SDL_DestroyRenderer(pstVideo->pstRenderer);
        }
        if (pstVideo->pstWindow)
        {
            SDL_DestroyWindow(pstVideo->pstWindow);
        }
        free(pstVideo);
        SDL_Log("Terminate window.\n");
    }
}

int InitVideo(
    const char   *pacWindowTitle,
    const int32_t s32WindowWidth,
    const int32_t s32WindowHeight,
    const int32_t s32LogicalWindowWidth,
    const int32_t s32LogicalWindowHeight,
    const bool    bFullscreen,
    Video       **pstVideo)
{
    uint32_t u32Flags = 0;

    *pstVideo = malloc(sizeof(struct Video_t));
    if (! *pstVideo)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "InitVideo(): error allocating memory.\n");
        return -1;
    }

    (*pstVideo)->pstRenderer            = NULL;
    (*pstVideo)->pstWindow              = NULL;
    (*pstVideo)->s32WindowHeight        = s32WindowHeight;
    (*pstVideo)->s32WindowWidth         = s32WindowWidth;
    (*pstVideo)->s32LogicalWindowWidth  = s32LogicalWindowWidth;
    (*pstVideo)->s32LogicalWindowHeight = s32LogicalWindowHeight;

    if (0 > SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return -1;
    }

    if (IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", IMG_GetError());
        return -1;
    }

    if (bFullscreen)
    {
        u32Flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    #ifdef __ANDROID__
    u32Flags = 0;
    SDL_DisplayMode stDisplayMode;
    if (0 == SDL_GetCurrentDisplayMode(0, &stDisplayMode))
    {
        (*pstVideo)->s32WindowWidth  = stDisplayMode.w;
        (*pstVideo)->s32WindowHeight = stDisplayMode.h;
    }
    #endif

    (*pstVideo)->pstWindow = SDL_CreateWindow(
        pacWindowTitle,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        (*pstVideo)->s32WindowWidth,
        (*pstVideo)->s32WindowHeight,
        u32Flags);

    if (! (*pstVideo)->pstWindow)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return -1;
    }

    if (0 > SDL_ShowCursor(SDL_DISABLE))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_GetWindowSize(
        (*pstVideo)->pstWindow,
        &(*pstVideo)->s32WindowWidth,
        &(*pstVideo)->s32WindowHeight);

    (*pstVideo)->dZoomLevel =
        (double)(*pstVideo)->s32WindowHeight / (double)s32LogicalWindowHeight;
    (*pstVideo)->dInitialZoomLevel = (*pstVideo)->dZoomLevel;

    (*pstVideo)->pstRenderer = SDL_CreateRenderer(
        (*pstVideo)->pstWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    if (! (*pstVideo)->pstRenderer)
    {
        SDL_DestroyWindow((*pstVideo)->pstWindow);
        return -1;
    }

    SDL_Log(
        "Setting up window at resolution %dx%d.\n",
        (*pstVideo)->s32WindowWidth, (*pstVideo)->s32WindowHeight);

    SetZoomLevel((*pstVideo)->dZoomLevel, *pstVideo);
    SDL_Log("Set initial zoom-level to factor %f.\n", (*pstVideo)->dZoomLevel);

    return 0;
}

void RenderScene(SDL_Renderer *pstRenderer)
{
    SDL_RenderPresent(pstRenderer);
    SDL_RenderClear(pstRenderer);
}

int SetZoomLevel(const double dZoomLevel, Video *pstVideo)
{
    pstVideo->dZoomLevel             = dZoomLevel;
    pstVideo->s32LogicalWindowWidth  = pstVideo->s32WindowWidth  / dZoomLevel;
    pstVideo->s32LogicalWindowHeight = pstVideo->s32WindowHeight / dZoomLevel;

    if (0 != SDL_RenderSetLogicalSize(
            pstVideo->pstRenderer,
            pstVideo->s32LogicalWindowWidth,
            pstVideo->s32LogicalWindowHeight))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return -1;
    }

    #ifdef DEBUG
    if (dZoomLevel != (*pstVideo)->dZoomLevel)
    {
        SDL_Log("Set zoom-level to factor %f.\n", dZoomLevel);
    }
    #endif

    return 0;
}

int ToggleFullscreen(Video *pstVideo)
{
    int      sReturnValue;
    uint32_t u32WindowFlags;

    u32WindowFlags = SDL_GetWindowFlags(pstVideo->pstWindow);

    if (u32WindowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP)
    {
        SDL_SetWindowPosition(pstVideo->pstWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        sReturnValue = SDL_SetWindowFullscreen(pstVideo->pstWindow, 0);
        SDL_Log("Set window to windowed mode.\n");
    }
    else
    {
        sReturnValue = SDL_SetWindowFullscreen(pstVideo->pstWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_Log("Set window to fullscreen mode.\n");
    }

    if (0 != sReturnValue)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
    }

    return sReturnValue;
}
