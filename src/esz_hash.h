// SPDX-License-Identifier: MIT
/**
 * @file  esz_hash.h
* @brief eszFW hash table and hash generator
 */

#ifndef ESZ_HASHES_H
#define ESZ_HASHES_H

#include <stdint.h>

enum {
    H_acceleration                 0xce26e518186a848f,
    H_anim_id_idle                 0xce63c6afa347d913,
    H_anim_id_jump                 0xce63c6afa348adf1,
    H_anim_id_run                  0xc06fa12c1c38a36a,
    H_anim_id_walk                 0xce63c6afa34f79a4,
    H_animated_tile_fps            0xf16ba347de2debdd,
    H_background_constant_velocity 0x1cb19bb15ad8b7fc,
    H_background_is_top_aligned    0xe10d87b900773f85,
    H_background_layer_shift       0xf42f15f4c255007e,
    H_climbable                    0x0377c455420b8600,
    H_connect_horizontal_map_ends  0xb2d77d5c88cb679e,
    H_connect_vertical_map_ends    0x8fd9bf6992bca50e,
    H_actor                        0x000000310f128ebe,
    H_gravitation                  0xc090e5ec12404d2d,
    H_height                       0x0000065301d688de,
    H_is_affected_by_gravity       0xd7df2608f228f6d1,
    H_is_animated                  0xc09beeb13eae4983,
    H_is_in_background             0xdba806855b4839b6,
    H_is_in_foreground             0xdba8c1d8d43eb8f1,
    H_is_in_midground              0x7b0525da0f6ff45f,
    H_is_left_oriented             0x1af19f00c7d179a4,
    H_is_moving                    0x0377cc4471f37f30,
    H_is_player                    0x0377cc4478b16e8d,
    H_jumping_power                0x702da8a7606d92ab,
    H_max_velocity_x               0xa1d4b1b096163590,
    H_meter_in_pixel               0xfbbc8a6d4a407cf9,
    H_opengl                       0x0000065312ef9eea,
    H_scancode_down                0x339db31fc86859fc,
    H_scancode_jump                0x339db31fc86bbc80,
    H_scancode_left                0x339db31fc86c904f,
    H_scancode_right               0xa7541718d66d61e2,
    H_scancode_up                  0xc0cfb7feda9252a9,
    H_scancode_quit                0x339db31fc86f92a7,
    H_scancode_run                 0xdac6b7da2cdc9c19,
    H_scancode_toggle_fullscreen   0xebb406be8e806258,
    H_scancode_unlock_camera       0x657e367e0c361b38,
    H_solid_above                  0xc0d1c0679690db0c,
    H_solid_below                  0xc0d1c06796a48b18,
    H_solid_left                   0x7272f650b702b58a,
    H_solid_right                  0xc0d1c06797c82e7d,
    H_sprite_sheet_id              0xe2141daae50cd180,
    H_width                        0x0000003110a3b0a5,
};

#ifndef USE_LIBTMX // (cute_tiled.h)
enum {
    H_objectgroup                  0xc0b9d518970be349,
    H_tilelayer                    0x0377d9f70e844fb0,
};
#endif

uint64_t generate_hash(const unsigned char* name);

#endif // ESZ_HASHES_H
