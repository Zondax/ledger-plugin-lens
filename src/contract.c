#include "lens_plugin.h"
static const uint8_t ACT_SEL[SELECTOR_SIZE] = {0xc5, 0xd5, 0xd9, 0x6a};
static const uint8_t ACT_WITH_SIGN_SEL[SELECTOR_SIZE] = {0xc8, 0x66, 0x42, 0xc7};
static const uint8_t BURN_SEL[SELECTOR_SIZE] = {0x42, 0x96, 0x6c, 0x68};
static const uint8_t CHANGE_DELEGATE_EXE_CONFIG_1_SEL[SELECTOR_SIZE] = {0x51, 0xc3, 0x65, 0x9c};
static const uint8_t CHANGE_DELEGATE_EXE_CONFIG_2_SEL[SELECTOR_SIZE] = {0xc1, 0xf4, 0xb4, 0x0a};
static const uint8_t CHANGE_DELEGATE_EXE_CONFIG__WITH_SIGN_SEL[SELECTOR_SIZE] = {0x49,
                                                                                 0x26,
                                                                                 0xc4,
                                                                                 0xed};
static const uint8_t COLLECT_SEL[SELECTOR_SIZE] = {0x47, 0x27, 0xce, 0x3a};
static const uint8_t COLLECT_WITH_SIGN_SEL[SELECTOR_SIZE] = {0xb7, 0x90, 0x2e, 0x73};
static const uint8_t COMMENT_SEL[SELECTOR_SIZE] = {0xb2, 0x73, 0xb4, 0xa7};
static const uint8_t COMMENT_WITH_SIGN_SEL[SELECTOR_SIZE] = {0xb4, 0x2d, 0xf5, 0x1a};
static const uint8_t CREATE_PROFILE_SEL[SELECTOR_SIZE] = {0x56, 0x0a, 0x4d, 0xb1};
static const uint8_t FOLLOW_SEL[SELECTOR_SIZE] = {0x4b, 0x73, 0x12, 0xa9};
static const uint8_t FOLLOW_WITH_SIGN_SEL[SELECTOR_SIZE] = {0x4d, 0x7b, 0x35, 0xa0};
static const uint8_t LINK_SEL[SELECTOR_SIZE] = {0x86, 0xCF, 0x48, 0xE7};
static const uint8_t LINK_WITH_SIG_SEL[SELECTOR_SIZE] = {0x7e, 0x50, 0x2f, 0xe0};
static const uint8_t MINT_SEL[SELECTOR_SIZE] = {0xf0, 0x8e, 0x8f, 0x5e};
static const uint8_t MIRROR_SEL[SELECTOR_SIZE] = {0xf9, 0x06, 0x04, 0xd1};
static const uint8_t MIRROR_WITH_SIGN_SEL[SELECTOR_SIZE] = {0xe6, 0xa4, 0x02, 0xb5};
static const uint8_t POST_SEL[SELECTOR_SIZE] = {0x66, 0xb0, 0xdc, 0xd3};
static const uint8_t POST_WITH_SIGN_SEL[SELECTOR_SIZE] = {0x90, 0x7c, 0xd7, 0xd2};
static const uint8_t QUOTE_SEL[SELECTOR_SIZE] = {0xF0, 0xba, 0x35, 0xf0};
static const uint8_t QUOTE_WITH_SIGN_SEL[SELECTOR_SIZE] = {0x65, 0xf2, 0x9f, 0x27};
static const uint8_t SET_BLOCK_STATUS_SEL[SELECTOR_SIZE] = {0xfb, 0x82, 0x7e, 0x82};
static const uint8_t SET_BLOCK_STATUS_WITH_SIG_SEL[SELECTOR_SIZE] = {0xC6, 0xd4, 0x59, 0x44};
static const uint8_t SET_FOLLOW_MOD_SEL[SELECTOR_SIZE] = {0x6d, 0xea, 0x40, 0xb3};
static const uint8_t SET_FOLLOW_MOD_WITH_SIG_SEL[SELECTOR_SIZE] = {0xce, 0x30, 0xbb, 0x4f};
static const uint8_t SET_PROFILE_METADATA_SEL[SELECTOR_SIZE] = {0xef, 0xe4, 0xfd, 0x83};
static const uint8_t SET_PROFILE_METADATA_WITH_SIGN_SEL[SELECTOR_SIZE] = {0x6d, 0x0f, 0xd6, 0x58};
static const uint8_t UNFOLLOW_SEL[SELECTOR_SIZE] = {0x81, 0x5e, 0xd0, 0x4a};
static const uint8_t UNFOLLOW_WITH_SIGN_SEL[SELECTOR_SIZE] = {0x80, 0x9d, 0x89, 0x47};
static const uint8_t WHITE_LIST_PROFILE_CREATE_SEL[SELECTOR_SIZE] = {0x20, 0x90, 0x55, 0x06};
static const uint8_t UNLINK_SEL[SELECTOR_SIZE] = {0x0c, 0x65, 0xb3, 0x9d};
static const uint8_t UNLINK_WITH_SIG_SEL[SELECTOR_SIZE] = {0x82, 0x5a, 0xb1, 0x64};
static const uint8_t DISABLE_TOKEN_GUARDIAN_SEL[SELECTOR_SIZE] = {0x22, 0x48, 0xf7, 0x6d};

// Array of all the different ens selectors. Make sure this follows the same order as the
// enum defined in `lens_plugin.h`
const uint8_t *const LENS_SELECTORS[NUM_SELECTORS] = {ACT_SEL,
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
