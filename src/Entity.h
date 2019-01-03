/**
 * @file Entity.h
 * @ingroup Entity
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#define RIGHT 0
#define LEFT  1

#include <stdbool.h>
#include <stdint.h>
#include "AABB.h"

typedef struct Camera_t
{
    uint16_t u16Flags;
    double   dPosX;
    double   dPosY;
    int32_t  s32MaxPosX;
    int32_t  s32MaxPosY;
} Camera;

typedef struct Entity_t
{
    AABB     stBB;
    uint16_t u16Flags;
    double   dPosX;
    double   dPosY;
    bool     bOrientation;
    double   dAcceleration;
    double   dVelocityX;
    double   dMaxVelocityX;
    double   dVelocityY;
    uint8_t  u8Width;
    uint8_t  u8Height;
    uint8_t  u8FrameOffsetX;
    uint8_t  u8FrameOffsetY;
    uint8_t  u8AnimFrame;
    uint8_t  u8AnimStart;
    uint8_t  u8AnimEnd;
    double   dAnimDelay;
} Entity;

typedef struct Sprite_t
{
    SDL_Texture *pstTexture;
    uint16_t     u16Width;
    uint16_t     u16Height;
    uint16_t     u16ImageOffsetX;
    uint16_t     u16ImageOffsetY;
} Sprite;

void ConnectHorizontalMapEndsForEntity(
    const uint16_t u16MapWidth,
    Entity       **pstEntity);

void ConnectMapEndsForEntity(
    const uint16_t u16MapWidth,
    const uint16_t u16MapHeight,
    Entity       **pstEntity);

void ConnectVerticalMapEndsForEntity(
    const uint16_t u16MapHeight,
    Entity       **pstEntity);

int DrawEntity(
    Entity       **pstEntity,
    Camera       **pstCamera,
    Sprite       **pstSprite,
    SDL_Renderer **pstRenderer);

void Drop(Entity **pstEntity);
void FreeCamera(Camera **pstCamera);
void FreeEntity(Entity **pstEntity);
void FreeSprite(Sprite **pstSprite);
int InitCamera(Camera **pstCamera);

int InitEntity(
    const double dPosX,
    const double dPosY,
    Entity     **pstEntity);

int InitSprite(
    const char    *pacFileName,
    const uint16_t u16Width,
    const uint16_t u16Height,
    const uint16_t u16ImageOffsetX,
    const uint16_t u16ImageOffsetY,
    Sprite       **pstSprite,
    SDL_Renderer **pstRenderer);

void Move(
    const bool    bOrientation,
    const double  dAcceleration,
    const double  dMaxVelocityX,
    const uint8_t u8AnimStart,
    const uint8_t u8AnimEnd,
    Entity      **pstEntity);

void ResetEntity(Entity **pstEntity);

void SetCameraBoundariesToMapSize(
    const int32_t  s32WindowWidth,
    const int32_t  s32WindowHeight,
    const double   dZoomLevel,
    const uint16_t u16MapWidth,
    const uint16_t u16MapHeight,
    Camera       **pstCamera);

void SetCameraTargetEntity(
    const int32_t s32WindowWidth,
    const int32_t s32WindowHeight,
    const double  dZoomLevel,
    Camera      **pstCamera,
    Entity      **pstEntity);

void SetAnimation(
    const uint8_t u8AnimStart,
    const uint8_t u8AnimEnd,
    Entity      **pstEntity);

void SetFrameOffset(
    const uint8_t u8OffsetX,
    const uint8_t u8OffsetY,
    Entity      **pstEntity);

void SetOrientation(const bool bOrientation, Entity **pstEntity);

void SetPosition(
    const double dPosX,
    const double dPosY,
    Entity     **pstEntity);

void SetSpeed(
    const double dAcceleration,
    const double dMaxVelocityX,
    Entity     **pstEntity);

void UpdateEntity(
    const double dDeltaTime,
    const double dGravitation,
    Entity     **pstEntity);

#endif // _ENTITY_H_
