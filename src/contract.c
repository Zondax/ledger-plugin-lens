#include "lens_plugin.h"
static const uint32_t ACT_SEL = 0xc5d5d96a;
static const uint32_t ACT_WITH_SIGN_SEL = 0xc86642c7;
static const uint32_t BURN_SEL = 0x42966c68;
static const uint32_t CHANGE_DELEGATE_EXE_CONFIG_1_SEL = 0x51c3659c;
static const uint32_t CHANGE_DELEGATE_EXE_CONFIG_2_SEL = 0xc1f4b40a;
static const uint32_t CHANGE_DELEGATE_EXE_CONFIG__WITH_SIGN_SEL = 0x4926c4ed;
static const uint32_t COLLECT_SEL = 0x4727ce3a;
static const uint32_t COLLECT_WITH_SIGN_SEL = 0xb7902e73;
static const uint32_t COMMENT_SEL = 0xb273b4a7;
static const uint32_t COMMENT_WITH_SIGN_SEL = 0xb42df51a;
static const uint32_t CREATE_PROFILE_SEL = 0x560a4db1;
static const uint32_t FOLLOW_SEL = 0x4b7312a9;
static const uint32_t FOLLOW_WITH_SIGN_SEL = 0x4d7b35a0;
static const uint32_t LINK_SEL = 0x86CF48E7;
static const uint32_t LINK_WITH_SIG_SEL = 0x7e502fe0;
static const uint32_t MINT_SEL = 0xf08e8f5e;
static const uint32_t MIRROR_SEL = 0xf90604d1;
static const uint32_t MIRROR_WITH_SIGN_SEL = 0xe6a402b5;
static const uint32_t POST_SEL = 0x66b0dcd3;
static const uint32_t POST_WITH_SIGN_SEL = 0x907cd7d2;
static const uint32_t QUOTE_SEL = 0xF0ba35f0;
static const uint32_t QUOTE_WITH_SIGN_SEL = 0x65f29f27;
static const uint32_t SET_BLOCK_STATUS_SEL = 0xfb827e82;
static const uint32_t SET_BLOCK_STATUS_WITH_SIG_SEL = 0xC6d45944;
static const uint32_t SET_FOLLOW_MOD_SEL = 0x6dea40b3;
static const uint32_t SET_FOLLOW_MOD_WITH_SIG_SEL = 0xce30bb4f;
static const uint32_t SET_PROFILE_METADATA_SEL = 0xefe4fd83;
static const uint32_t SET_PROFILE_METADATA_WITH_SIGN_SEL = 0x6d0fd658;
static const uint32_t UNFOLLOW_SEL = 0x815ed04a;
static const uint32_t UNFOLLOW_WITH_SIGN_SEL = 0x809d8947;
static const uint32_t WHITE_LIST_PROFILE_CREATE_SEL = 0x20905506;
static const uint32_t UNLINK_SEL = 0x0c65b39d;
static const uint32_t UNLINK_WITH_SIG_SEL = 0x825ab164;
static const uint32_t DISABLE_TOKEN_GUARDIAN_SEL = 0x2248f76d;

// Array of all the different ens selectors. Make sure this follows the same order as the
// enum defined in `lens_plugin.h`
const uint32_t LENS_SELECTORS[NUM_SELECTORS] = {ACT_SEL,
                                                ACT_WITH_SIGN_SEL,
                                                BURN_SEL,
                                                CHANGE_DELEGATE_EXE_CONFIG_1_SEL,
                                                CHANGE_DELEGATE_EXE_CONFIG_2_SEL,
                                                CHANGE_DELEGATE_EXE_CONFIG__WITH_SIGN_SEL,
                                                COLLECT_SEL,
                                                COLLECT_WITH_SIGN_SEL,
                                                COMMENT_SEL,
                                                COMMENT_WITH_SIGN_SEL,
                                                CREATE_PROFILE_SEL,
                                                FOLLOW_SEL,
                                                FOLLOW_WITH_SIGN_SEL,
                                                LINK_SEL,
                                                LINK_WITH_SIG_SEL,
                                                MINT_SEL,
                                                MIRROR_SEL,
                                                MIRROR_WITH_SIGN_SEL,
                                                POST_SEL,
                                                POST_WITH_SIGN_SEL,
                                                QUOTE_SEL,
                                                QUOTE_WITH_SIGN_SEL,
                                                SET_BLOCK_STATUS_SEL,
                                                SET_BLOCK_STATUS_WITH_SIG_SEL,
                                                SET_FOLLOW_MOD_SEL,
                                                SET_FOLLOW_MOD_WITH_SIG_SEL,
                                                SET_PROFILE_METADATA_SEL,
                                                SET_PROFILE_METADATA_WITH_SIGN_SEL,
                                                UNFOLLOW_SEL,
                                                UNFOLLOW_WITH_SIGN_SEL,
                                                WHITE_LIST_PROFILE_CREATE_SEL,
                                                UNLINK_SEL,
                                                UNLINK_WITH_SIG_SEL,
                                                DISABLE_TOKEN_GUARDIAN_SEL};
