#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 33

// Name of the plugin.
#define PLUGIN_NAME "LENS"

// Placeholder variant to be set when parsing is done but data is still being sent.
#define NONE                       100
#define MAX_NUMBER_OF_IDS          3
#define DEADLINE_OFFSET_INSIDE_SIG (0x80 - SELECTOR_SIZE)

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    ACT = 0,
    ACT_WITH_SIGN,
    BURN,
    CHANGE_DELEGATE_EXE_CONFIG_1,
    CHANGE_DELEGATE_EXE_CONFIG_2,
    CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN,
    COLLECT,
    COLLECT_WITH_SIGN,
    COMMENT,
    COMMENT_WITH_SIGN,
    CREATE_PROFILE,
    FOLLOW,
    FOLLOW_WITH_SIGN,
    LINK,
    LINK_WITH_SIG,
    MINT,
    MIRROR,
    MIRROR_WITH_SIGN,
    POST,
    POST_WITH_SIGN,
    QUOTE,
    QUOTE_WITH_SIGN,
    SET_BLOCK_STATUS,
    SET_BLOCK_STATUS_WITH_SIG,
    SET_FOLLOW_MOD,
    SET_FOLLOW_MOD_WITH_SIG,
    SET_PROFILE_METADATA,
    SET_PROFILE_METADATA_WITH_SIGN,
    UNFOLLOW,
    UNFOLLOW_WITH_SIGN,
    WHITE_LIST_PROFILE_CREATE,
    UNLINK,
    UNLINK_WITH_SIG,

} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    ACTION_OFFSET,
    ACTOR_ID,
    ADDRESS_OFFSET,
    APPROVALS,
    APPROVALS_NUMBER,
    APPROVALS_OFFSET,
    COLLECTOR,
    CONFIG_NUMBER,
    DATA_OFFSET,
    DEADLINE,
    EXECS,
    EXECS_NUMBER,
    EXECS_OFFSET,
    HANDLE_ID,
    IDS_OFFSET,
    MODULE,
    OFFSET,
    PUB_ID,
    PUB_ID_POINTED,
    PROFILE_ID,
    PROFILE_ID_OFFSET,
    PROFILE_ID_POINTED,
    PROFILE_NUMBER,
    REFERENCE_MOD,
    SIGNATURE_SIGNER,
    STRING_OFFSET,
    SWITCH_TO_CONFIG,
    TOKEN_ID,
    TO,
    UNFOLLOW_PROFILES,
    WHITE_LIST,
} parameter;

extern const uint8_t *const LENS_SELECTORS[NUM_SELECTORS];

typedef struct {
    uint8_t value[ADDRESS_LENGTH];
} address_t;

typedef struct {
    uint8_t value[INT256_LENGTH];
} bytes32_t;

typedef struct {
    union {
        struct {
            bytes32_t actorprofileId;
            bytes32_t deadline;
            bytes32_t pubprofileId;
            bytes32_t publicationId;
            uint16_t profileId_offset;
        } act;

        struct {
            address_t collector;
            bytes32_t profile_id;
            bytes32_t pub_id;
        } collect_with_sign;

        struct {
            bytes32_t publicationCollectedId;
            bytes32_t publicationCollectedProfileId;
            bytes32_t collectorProfileId;
            bytes32_t deadline;
            uint16_t profileId_offset;
        } collect;

        struct {
            bytes32_t delegatorProfileId;
            address_t delegatedExecutors;
            uint16_t approvals;
            uint16_t approvals_offset;
            bytes32_t configNumber;
            uint16_t switchToGivenConfig;
        } change_delegated_exec_1;

        struct {
            bytes32_t delegatorProfileId;
            address_t delegatedExecutors;
            uint16_t approvals;
            uint16_t approvals_offset;
            bytes32_t configNumber;
            bytes32_t deadline;
        } change_delegated_exec_with_sign;

        struct {
            bytes32_t delegatorProfileId;
            address_t delegatedExecutors;
            uint16_t delegatedExecutors_offset;
            uint16_t approvals;
            uint16_t approvals_offset;
        } change_delegated_exec_2;

        struct {
            bytes32_t profile_id;
            bytes32_t profile_id_pointed;
            bytes32_t pubid_pointed;
            uint16_t profileId_offset;
            bytes32_t deadline;
        } comment;

        struct {
            address_t to;
            address_t followMod;
        } create_profile;

        struct {
            bytes32_t profileId;
            address_t referenceModule;
            uint16_t profileId_offset;
            bytes32_t deadline;
        } post;

        struct {
            bytes32_t profile_id;
            bytes32_t profile_id_pointed;
            bytes32_t pubid_pointed;
            uint16_t profileId_offset;
            bytes32_t deadline;
        } quote;

        struct {
            bytes32_t profile_id;
            address_t follow_mod;
            bytes32_t deadline;
        } set_follow;

        struct {
            bytes32_t profile_id;
            bytes32_t profile_id_pointed;
            bytes32_t pubid_pointed;
            uint16_t profileId_offset;
            bytes32_t deadline;
        } mirror;

        struct {
            bytes32_t followerProfileId;
            bytes32_t deadline;
        } follow;

        struct {
            bytes32_t token_id;
        } burn;

        struct {
            address_t to;
        } mint;

        struct {
            bytes32_t handle_id;
            bytes32_t profile_id;
            bytes32_t deadline;
        } link_unlink;

        struct {
            bytes32_t profile_id;
            bytes32_t deadline;
        } metadata;

        struct {
            bytes32_t unfollowerProfileId;
            bytes32_t deadline;
        } unfollow;

        struct {
            bytes32_t unfollowerProfileId;
            bytes32_t idsOfProfilesToUnfollow;
            uint16_t n_profiles;
        } unfollow_with_sign;

        struct {
            address_t mod;
            uint16_t whitelist;
        } white_list_mod;

        struct {
            bytes32_t byProfileId;
            bytes32_t deadline;
            uint16_t profileId_offset;
        } set_block_status;

    } body;
} lens_tx_t;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;

    // Tx related context
    lens_tx_t tx;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");
