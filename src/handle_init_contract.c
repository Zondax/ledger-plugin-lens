#include "lens_plugin.h"

// Called once to init.
void handle_init_contract(ethPluginInitContract_t *msg) {
    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    uint8_t i;
    for (i = 0; i < NUM_SELECTORS; i++) {
        if (memcmp((uint8_t *) PIC(LENS_SELECTORS[i]), msg->selector, SELECTOR_SIZE) == 0) {
            context->selectorIndex = i;
            break;
        }
    }

    if (i == NUM_SELECTORS) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case BURN:
            context->next_param = TOKEN_ID;
            break;
        case MINT:
            context->next_param = TO;
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_1:
            __attribute__((fallthrough));
        case CHANGE_DELEGATE_EXE_CONFIG_2:
            __attribute__((fallthrough));
        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
            __attribute__((fallthrough));
        case FOLLOW:
            __attribute__((fallthrough));
        case FOLLOW_WITH_SIGN:
            __attribute__((fallthrough));
        case SET_BLOCK_STATUS:
            __attribute__((fallthrough));
        case SET_BLOCK_STATUS_WITH_SIG:
            __attribute__((fallthrough));
        case SET_FOLLOW_MOD:
            __attribute__((fallthrough));
        case SET_FOLLOW_MOD_WITH_SIG:
            __attribute__((fallthrough));
        case SET_PROFILE_METADATA:
            __attribute__((fallthrough));
        case SET_PROFILE_METADATA_WITH_SIGN:
            __attribute__((fallthrough));
        case UNFOLLOW:
            __attribute__((fallthrough));
        case UNFOLLOW_WITH_SIGN:
            context->next_param = PROFILE_ID;
            break;
        case LINK:
            __attribute__((fallthrough));
        case LINK_WITH_SIG:
            __attribute__((fallthrough));
        case UNLINK:
            __attribute__((fallthrough));
        case UNLINK_WITH_SIG:
            context->next_param = HANDLE_ID;
            break;
        case ACT:
            __attribute__((fallthrough));
        case ACT_WITH_SIGN:
            __attribute__((fallthrough));
        case COLLECT:
            __attribute__((fallthrough));
        case COLLECT_WITH_SIGN:
            __attribute__((fallthrough));
        case COMMENT:
            __attribute__((fallthrough));
        case COMMENT_WITH_SIGN:
            __attribute__((fallthrough));
        case CREATE_PROFILE:
            __attribute__((fallthrough));
        case MIRROR:
            __attribute__((fallthrough));
        case MIRROR_WITH_SIGN:
            __attribute__((fallthrough));
        case POST:
            __attribute__((fallthrough));
        case QUOTE:
            __attribute__((fallthrough));
        case QUOTE_WITH_SIGN:
            context->next_param = DATA_OFFSET;
            break;
        case POST_WITH_SIGN:
            context->next_param = PROFILE_ID_OFFSET;
            break;
        case WHITE_LIST_PROFILE_CREATE:
            context->next_param = MODULE;
            break;
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
