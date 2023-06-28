#include "lens_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    // The total number of screen you will need.
    switch (context->selectorIndex) {
        case BURN:
        case FOLLOW:
        case MINT:
        case SET_BLOCK_STATUS:
        case SET_PROFILE_METADATA:
        case UNFOLLOW:
            msg->numScreens = 1;
            break;
        case CREATE_PROFILE:
        case FOLLOW_WITH_SIGN:
        case LINK:
        case POST:
        case SET_BLOCK_STATUS_WITH_SIG:
        case SET_FOLLOW_MOD:
        case SET_PROFILE_METADATA_WITH_SIGN:
        case UNFOLLOW_WITH_SIGN:
        case UNLINK:
        case WHITE_LIST_PROFILE_CREATE:
            msg->numScreens = 2;
            break;
        case ACT:
        case CHANGE_DELEGATE_EXE_CONFIG_2:
        case COLLECT:
        case COMMENT:
        case LINK_WITH_SIG:
        case MIRROR:
        case POST_WITH_SIGN:
        case QUOTE:
        case SET_FOLLOW_MOD_WITH_SIG:
        case UNLINK_WITH_SIG:
            msg->numScreens = 3;
            break;
        case ACT_WITH_SIGN:
        case COLLECT_WITH_SIGN:
        case COMMENT_WITH_SIGN:
        case MIRROR_WITH_SIGN:
        case QUOTE_WITH_SIGN:
            msg->numScreens = 4;
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_1:
        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
            msg->numScreens = 5;
            break;
        default:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
