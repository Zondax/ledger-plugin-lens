#include "lens_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    // The total number of screen you will need.
    switch (context->selectorIndex) {
        case BURN:
            __attribute__((fallthrough));
        case FOLLOW:
            __attribute__((fallthrough));
        case MINT:
            __attribute__((fallthrough));
        case SET_BLOCK_STATUS:
            __attribute__((fallthrough));
        case SET_PROFILE_METADATA:
            __attribute__((fallthrough));
        case UNFOLLOW:
            msg->numScreens = 1;
            break;
        case CREATE_PROFILE:
            __attribute__((fallthrough));
        case FOLLOW_WITH_SIGN:
            __attribute__((fallthrough));
        case LINK:
            __attribute__((fallthrough));
        case POST:
            __attribute__((fallthrough));
        case SET_BLOCK_STATUS_WITH_SIG:
            __attribute__((fallthrough));
        case SET_FOLLOW_MOD:
            __attribute__((fallthrough));
        case SET_PROFILE_METADATA_WITH_SIGN:
            __attribute__((fallthrough));
        case UNFOLLOW_WITH_SIGN:
            __attribute__((fallthrough));
        case UNLINK:
            __attribute__((fallthrough));
        case WHITE_LIST_PROFILE_CREATE:
            msg->numScreens = 2;
            break;
        case ACT:
            __attribute__((fallthrough));
        case CHANGE_DELEGATE_EXE_CONFIG_2:
            __attribute__((fallthrough));
        case COLLECT:
            __attribute__((fallthrough));
        case COMMENT:
            __attribute__((fallthrough));
        case LINK_WITH_SIG:
            __attribute__((fallthrough));
        case MIRROR:
            __attribute__((fallthrough));
        case POST_WITH_SIGN:
            __attribute__((fallthrough));
        case QUOTE:
            __attribute__((fallthrough));
        case SET_FOLLOW_MOD_WITH_SIG:
            __attribute__((fallthrough));
        case UNLINK_WITH_SIG:
            msg->numScreens = 3;
            break;
        case ACT_WITH_SIGN:
            __attribute__((fallthrough));
        case COLLECT_WITH_SIGN:
            __attribute__((fallthrough));
        case COMMENT_WITH_SIGN:
            __attribute__((fallthrough));
        case MIRROR_WITH_SIGN:
            __attribute__((fallthrough));
        case QUOTE_WITH_SIGN:
            msg->numScreens = 4;
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_1:
            __attribute__((fallthrough));
        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
            msg->numScreens = 5;
            break;
        default:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
