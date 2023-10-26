#include "lens_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case ACT:
            strlcpy(msg->version, "Act", msg->versionLength);
            break;
        case ACT_WITH_SIGN:
            strlcpy(msg->version, "Act with Sign", msg->versionLength);
            break;
        case BURN:
            strlcpy(msg->version, "Burn", msg->versionLength);
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_1:
        case CHANGE_DELEGATE_EXE_CONFIG_2:
            strlcpy(msg->version, "Change Delegate Executer Config", msg->versionLength);
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
            strlcpy(msg->version, "Change Delegate Executer Config With Sign", msg->versionLength);
            break;
        case COLLECT:
            strlcpy(msg->version, "Collect", msg->versionLength);
            break;
        case COLLECT_WITH_SIGN:
            strlcpy(msg->version, "Collect with Sign", msg->versionLength);
            break;
        case COMMENT:
            strlcpy(msg->version, "Comment", msg->versionLength);
            break;
        case COMMENT_WITH_SIGN:
            strlcpy(msg->version, "Comment with Sign", msg->versionLength);
            break;
        case CREATE_PROFILE:
            strlcpy(msg->version, "Create Profile", msg->versionLength);
            break;
        case FOLLOW:
            strlcpy(msg->version, "Follow", msg->versionLength);
            break;
        case FOLLOW_WITH_SIGN:
            strlcpy(msg->version, "Follow with Sign", msg->versionLength);
            break;
        case LINK:
            strlcpy(msg->version, "Link", msg->versionLength);
            break;
        case LINK_WITH_SIG:
            strlcpy(msg->version, "Link With Sign", msg->versionLength);
            break;
        case MINT:
            strlcpy(msg->version, "Mint", msg->versionLength);
            break;
        case MIRROR:
            strlcpy(msg->version, "Mirror", msg->versionLength);
            break;
        case MIRROR_WITH_SIGN:
            strlcpy(msg->version, "Mirror with Sign", msg->versionLength);
            break;
        case POST:
            strlcpy(msg->version, "Post", msg->versionLength);
            break;
        case POST_WITH_SIGN:
            strlcpy(msg->version, "Post with Sign", msg->versionLength);
            break;
        case QUOTE:
            strlcpy(msg->version, "Quote", msg->versionLength);
            break;
        case QUOTE_WITH_SIGN:
            strlcpy(msg->version, "Quote With Sign", msg->versionLength);
            break;
        case SET_BLOCK_STATUS:
            strlcpy(msg->version, "Set Block Status", msg->versionLength);
            break;
        case SET_BLOCK_STATUS_WITH_SIG:
            strlcpy(msg->version, "Set Block Status With Sign", msg->versionLength);
            break;
        case SET_FOLLOW_MOD:
            strlcpy(msg->version, "Set Follow Mod", msg->versionLength);
            break;
        case SET_FOLLOW_MOD_WITH_SIG:
            strlcpy(msg->version, "Set Follow Mod With Sign", msg->versionLength);
            break;
        case SET_PROFILE_METADATA:
            strlcpy(msg->version, "Set Metadata URI", msg->versionLength);
            break;
        case SET_PROFILE_METADATA_WITH_SIGN:
            strlcpy(msg->version, "Set Metadata URI with Sign", msg->versionLength);
            break;
        case UNFOLLOW:
            strlcpy(msg->version, "Unfollow", msg->versionLength);
            break;
        case UNFOLLOW_WITH_SIGN:
            strlcpy(msg->version, "Unfollow with Sign", msg->versionLength);
            break;
        case UNLINK:
            strlcpy(msg->version, "Unlink", msg->versionLength);
            break;
        case UNLINK_WITH_SIG:
            strlcpy(msg->version, "Unlink With Sign", msg->versionLength);
            break;
        case WHITE_LIST_PROFILE_CREATE:
            strlcpy(msg->version, "Whitelist Profile Creator", msg->versionLength);
            break;

        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
