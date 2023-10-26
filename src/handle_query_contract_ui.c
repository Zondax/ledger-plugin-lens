#include <stdbool.h>
#include "lens_plugin.h"

static bool set_uint265_with_prefix(const uint8_t *amount,
                                    uint8_t amount_size,
                                    const char *unit,
                                    char *out_buffer,
                                    size_t out_buffer_size) {
    char tmp_buffer[100] = {0};

    if (uint256_to_decimal(amount, amount_size, tmp_buffer, sizeof(tmp_buffer)) == false) {
        return false;
    }

    size_t result_len = strlen(tmp_buffer) + strlen(unit) + 1;  // +1 for the space
    if (out_buffer_size < result_len) {
        return false;
    }

    // Concatenate the amount string, space, and unit
    snprintf(out_buffer, out_buffer_size, "%s %s", tmp_buffer, unit);

    return true;
}

// Set UI for any address screen.
static bool set_address_ui(ethQueryContractUI_t *msg, address_t *value) {
    if (msg->msgLength < 42) {
        THROW(EXCEPTION_OVERFLOW);
    }
    // Prefix the address with `0x`.
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;

    // Get the string representation of the address stored in `context->beneficiary`. Put it in
    // `msg->msg`.
    return getEthAddressStringFromBinary(
        value->value,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        msg->pluginSharedRW->sha3,
        chainid);
}

static bool set_addr_ui(ethQueryContractUI_t *msg, address_t *address, const char *title) {
    strlcpy(msg->title, title, msg->titleLength);
    return set_address_ui(msg, address);
}

static bool set_bytes32_as_int_ui(ethQueryContractUI_t *msg, bytes32_t *array, const char *title) {
    strlcpy(msg->title, title, msg->titleLength);
    return uint256_to_decimal(array->value, sizeof(array->value), msg->msg, msg->msgLength);
}

static bool set_bytes32_as_int_unit_ui(ethQueryContractUI_t *msg,
                                       bytes32_t *array,
                                       const char *title,
                                       const char *unit) {
    strlcpy(msg->title, title, msg->titleLength);
    return set_uint265_with_prefix(array->value,
                                   sizeof(array->value),
                                   unit,
                                   msg->msg,
                                   msg->msgLength);
}

static bool set_bool_ui(ethQueryContractUI_t *msg, uint16_t val, const char *title) {
    strlcpy(msg->title, title, msg->titleLength);

    if (val == 0) {
        snprintf(msg->msg, msg->msgLength, "%s", "False");
        return true;
    } else {
        snprintf(msg->msg, msg->msgLength, "%s", "True");
        return true;
    }
    return false;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case ACT:
        case ACT_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.act.pubprofileId,
                                                "Pub Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg, &context->tx.body.act.publicationId, "Pub Id");
                    break;
                case 2:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.act.actorprofileId,
                                                "Actor Profile Id");
                    break;
                case 3:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.act.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case BURN:
            if (msg->screenIndex == 0) {
                ret = set_bytes32_as_int_ui(msg, &context->tx.body.burn.token_id, "Token Id");
            } else {
                PRINTF("Received an invalid screenIndex\n");
                ret = false;
            }
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_1:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_1.delegatorProfileId,
                        "Profile Id");
                    break;
                case 1:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.change_delegated_exec_1.delegatedExecutors,
                                      "Profile Manager");
                    break;
                case 2:
                    ret = set_bool_ui(msg,
                                      context->tx.body.change_delegated_exec_1.approvals,
                                      "Approvals");
                    break;
                case 3:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_1.configNumber,
                        "Config Number");
                    break;
                case 4:
                    ret = set_bool_ui(msg,
                                      context->tx.body.change_delegated_exec_1.switchToGivenConfig,
                                      "Switch to Config");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case CHANGE_DELEGATE_EXE_CONFIG_2:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_2.delegatorProfileId,
                        "Profile Id");
                    break;
                case 1:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.change_delegated_exec_2.delegatedExecutors,
                                      "Profile Manager");
                    break;
                case 2:
                    ret = set_bool_ui(msg,
                                      context->tx.body.change_delegated_exec_2.approvals,
                                      "Approvals");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_with_sign.delegatorProfileId,
                        "Profile Id");
                    break;
                case 1:
                    ret = set_addr_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_with_sign.delegatedExecutors,
                        "Profile Manager");
                    break;
                case 2:
                    ret = set_bool_ui(msg,
                                      context->tx.body.change_delegated_exec_with_sign.approvals,
                                      "Approvals");
                    break;
                case 3:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_with_sign.configNumber,
                        "Config Number");
                    break;
                case 4:
                    ret = set_bytes32_as_int_unit_ui(
                        msg,
                        &context->tx.body.change_delegated_exec_with_sign.deadline,
                        "Sig Deadline",
                        "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case COLLECT:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.collect.publicationCollectedProfileId,
                        "Collected Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.collect.publicationCollectedId,
                                                "Collected Id");
                    break;
                case 2:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.collect.collectorProfileId,
                                                "Collector Profile Id");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case COLLECT_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(
                        msg,
                        &context->tx.body.collect.publicationCollectedProfileId,
                        "Collected Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.collect.publicationCollectedId,
                                                "Collected Id");
                    break;
                case 2:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.collect.collectorProfileId,
                                                "Collector Profile Id");
                    break;
                case 3:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.collect.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case COMMENT:
        case COMMENT_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.comment.profile_id,
                                                "Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.comment.profile_id_pointed,
                                                "Profile Id Pointed");
                    break;
                case 2:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.comment.pubid_pointed,
                                                "Pub Id Pointed");
                    break;
                case 3:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.comment.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case CREATE_PROFILE:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_addr_ui(msg, &context->tx.body.create_profile.to, "To");
                    break;
                case 1:
                    ret =
                        set_addr_ui(msg, &context->tx.body.create_profile.followMod, "Follow Mod");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case FOLLOW:
        case FOLLOW_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.follow.followerProfileId,
                                                "Follower Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.follow.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case LINK:
        case UNLINK:
        case LINK_WITH_SIG:
        case UNLINK_WITH_SIG:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.link_unlink.handle_id,
                                                "Handle Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.link_unlink.profile_id,
                                                "Profile Id");
                    break;
                case 2:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.link_unlink.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case MINT:
            if (msg->screenIndex == 0) {
                ret = set_addr_ui(msg, &context->tx.body.mint.to, "To");
            } else {
                PRINTF("Received an invalid screenIndex\n");
                ret = false;
            }
            break;
        case MIRROR:
        case MIRROR_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.mirror.profile_id,
                                                "Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.mirror.profile_id_pointed,
                                                "Profile Id Pointed");
                    break;
                case 2:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.mirror.pubid_pointed,
                                                "Pub Id Pointed");
                    break;
                case 3:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.mirror.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case POST:
        case POST_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret =
                        set_bytes32_as_int_ui(msg, &context->tx.body.post.profileId, "Profile Id");
                    break;
                case 1:
                    ret = set_addr_ui(msg, &context->tx.body.post.referenceModule, "Reference Mod");
                    break;
                case 2:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.post.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case QUOTE:
        case QUOTE_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.quote.profile_id,
                                                "Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.quote.profile_id_pointed,
                                                "Profile Id Pointed");
                    break;
                case 2:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.quote.pubid_pointed,
                                                "Pub Id Pointed");
                    break;
                case 3:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.quote.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case SET_BLOCK_STATUS:
        case SET_BLOCK_STATUS_WITH_SIG:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.set_block_status.byProfileId,
                                                "Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.set_block_status.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case SET_FOLLOW_MOD:
        case SET_FOLLOW_MOD_WITH_SIG:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.set_follow.profile_id,
                                                "Profile Id");
                    break;
                case 1:
                    ret = set_addr_ui(msg, &context->tx.body.set_follow.follow_mod, "Follow Mod");
                    break;
                case 2:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.set_follow.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case SET_PROFILE_METADATA:
        case SET_PROFILE_METADATA_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.metadata.profile_id,
                                                "Profile Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.metadata.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case UNFOLLOW:
        case UNFOLLOW_WITH_SIGN:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_bytes32_as_int_ui(msg,
                                                &context->tx.body.unfollow.unfollowerProfileId,
                                                "Unfollower Id");
                    break;
                case 1:
                    ret = set_bytes32_as_int_unit_ui(msg,
                                                     &context->tx.body.unfollow.deadline,
                                                     "Sig Deadline",
                                                     "s");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;

        case WHITE_LIST_PROFILE_CREATE:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_addr_ui(msg, &context->tx.body.white_list_mod.mod, "Profile Creator");
                    break;
                case 1:
                    ret = set_bool_ui(msg, context->tx.body.white_list_mod.whitelist, "WhiteList");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            ret = false;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
