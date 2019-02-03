/**
 * @file Entity.h
 * @ingroup Entity
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL.h>
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
    double   dSpawnPosX;
    double   dSpawnPosY;
    bool     bIsJumping;
    bool     bOrientation;
    double   dAcceleration;
    double   dVelocityX;
    double   dMaxVelocityX;
    double   dVelocityY;
    uint16_t u16Width;
    uint16_t u16Height;
    uint8_t  u8FrameOffsetX;
    uint8_t  u8FrameOffsetY;
    uint8_t  u8AnimFrame;
    uint8_t  u8AnimStart;
    uint8_t  u8AnimEnd;
    double   dAnimDelay;
    double   dAnimSpeed;
} Entity;

typedef struct Sprite_t
{
    SDL_Texture *pstTexture;
    uint16_t     u16Width;
    uint16_t     u16Height;
    uint16_t     u16ImageOffsetX;
    uint16_t     u16ImageOffsetY;
} Sprite;

void AnimateEntity(bool bAnimate, Entity *pstEntity);
void ConnectHorizontalMapEndsForEntity(const uint16_t u16MapWidth, Entity *pstEntity);
void ConnectMapEndsForEntity(const uint16_t u16MapWidth, const uint16_t u16MapHeight, Entity *pstEntity);
void ConnectVerticalMapEndsForEntity(const uint16_t u16MapHeight, Entity *pstEntity);
int  DrawEntity(const Entity *pstEntity, const Camera *pstCamera, const Sprite *pstSprite, SDL_Renderer *pstRenderer);
void DropEntity(Entity *pstEntity);
void FreeCamera(Camera *pstCamera);
void FreeEntity(Entity *pstEntity);
void FreeSprite(Sprite *pstSprite);
int  InitCamera(Camera **pstCamera);

int InitEntity(
    const double   dPosX,
    const double   dPosY,
    const uint16_t u16Width,
    const uint16_t u16Height,
    Entity       **pstEntity);

int InitSprite(
    const char    *pacFileName,
    const uint16_t u16Width,
    const uint16_t u16Height,
    const uint16_t u16ImageOffsetX,
    const uint16_t u16ImageOffsetY,
    Sprite       **pstSprite,
    SDL_Renderer *pstRenderer);

bool IsCameraLocked(const Camera *pstCamera);
bool IsEntityMoving(const Entity *pstEntity);
bool IsEntityRising(const Entity *pstEntity);
void JumpEntity(const double dForce, Entity *pstEntity);
void LockCamera(Camera *pstCamera);
void MoveEntity(Entity *pstEntity);

void MoveEntityFull(
    const bool    bOrientation,
    const double  dAcceleration,
    const double  dMaxVelocityX,
    const uint8_t u8AnimStart,
    const uint8_t u8AnimEnd,
    const double  dAnimSpeed,
    const uint8_t u8FrameOffsetY,
    Entity       *pstEntity);

void ResetEntity(Entity *pstEntity);
void ResetEntityToSpawnPosition(Entity *pstEntity);

int SetCameraBoundariesToMapSize(
    const int32_t  s32LogicalWindowWidth,
    const int32_t  s32LogicalWindowHeight,
    const uint16_t u16MapWidth,
    const uint16_t u16MapHeight,
    Camera        *pstCamera);

void SetCameraTargetEntity(
    const int32_t s32LogicalWindowWidth,
    const int32_t s32LogicalWindowHeight,
    Camera       *pstCamera,
    const Entity *pstEntity);

void SetAnimation(const uint8_t u8AnimStart, const uint8_t u8AnimEnd, const double dAnimSpeed, Entity *pstEntity);
void SetFrameOffset(const uint8_t u8OffsetX, const uint8_t u8OffsetY, Entity *pstEntity);
void SetOrientation(const bool bOrientation, Entity *pstEntity);
void SetPosition(const double dPosX, const double dPosY, Entity *pstEntity);
void SetSpawnPosition(const double dPosX, const double dPosY, Entity *pstEntity);
void SetSpeed(const double dAcceleration, const double dMaxVelocityX, Entity *pstEntity);
void StopEntity(Entity *pstEntity);
void UnlockCamera(Camera *pstCamera);

void UpdateEntity(
    const double  dDeltaTime,
    const double  dGravitation,
    const uint8_t u8MeterInPixel,
    Entity       *pstEntity);

#endif // _ENTITY_H_
