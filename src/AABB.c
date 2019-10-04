/**
 * @file      AABB.c
 * @ingroup   AABB
 * @defgroup  AABB Axis-aligned bounding boxes handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <SDL.h>
#include "AABB.h"

/**
 * @brief  Check if two axis-aligned bounding boxes intersect.
 * @param  stBoxA
 *         Bounding box A.
 * @param  stBoxB
 *         Bounding box B.
 * @return 1 if boxes are intersecting, 0 if not.
 */
SDL_bool BoxesDoIntersect(const AABB stBoxA, const AABB stBoxB)
{
    double dAx = stBoxB.dLeft - stBoxA.dRight;
    double dAy = stBoxB.dTop  - stBoxA.dBottom;
    double dBx = stBoxA.dLeft - stBoxB.dRight;
    double dBy = stBoxA.dTop  - stBoxB.dBottom;

    if (dAx > 0.0 || dAy > 0.0)
    {
        return SDL_FALSE;
    }

    if (dBx > 0.0 || dBy > 0.0)
    {
        return SDL_FALSE;
    }

    return SDL_TRUE;
}
