#include "lens_plugin.h"

// Called once to init.
void handle_init_contract(void *parameters) {
    // Cast the msg to the type of structure we expect (here, ethPluginInitContract_t).
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

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
        case CHANGE_DELEGATE_EXE_CONFIG_2:
        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
        case FOLLOW:
        case FOLLOW_WITH_SIGN:
        case SET_BLOCK_STATUS:
        case SET_FOLLOW_MOD:
        case SET_FOLLOW_MOD_WITH_SIG:
        case SET_PROFILE_METADATA:
        case SET_PROFILE_METADATA_WITH_SIGN:
        case UNFOLLOW:
        case UNFOLLOW_WITH_SIGN:
            context->next_param = PROFILE_ID;
            break;
        case LINK:
        case LINK_WITH_SIG:
        case UNLINK:
        case UNLINK_WITH_SIG:
            context->next_param = HANDLE_ID;
            break;
        case ACT:
        case ACT_WITH_SIGN:
        case COLLECT:
        case COLLECT_WITH_SIGN:
        case COMMENT:
        case COMMENT_WITH_SIGN:
        case CREATE_PROFILE:
        case MIRROR:
        case MIRROR_WITH_SIGN:
        case POST:
        case QUOTE:
        case QUOTE_WITH_SIGN:
            context->next_param = DATA_OFFSET;
            break;
        case POST_WITH_SIGN:
        case SET_BLOCK_STATUS_WITH_SIG:
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
