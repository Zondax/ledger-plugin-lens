#include "lens_plugin.h"
#include "cx.h"

static void handle_collect(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.collect.publicationCollectedProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.publicationCollectedProfileId.value));
            context->next_param = PUB_ID;
            break;
        case PUB_ID:
            copy_parameter(context->tx.body.collect.publicationCollectedId.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.publicationCollectedId.value));
            context->next_param = COLLECTOR;
            break;
        case COLLECTOR:
            copy_parameter(context->tx.body.collect.collectorProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.collectorProfileId.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_collect_with_sign(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case DATA_OFFSET:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.collect.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.collect.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.deadline.value));
            context->offset = context->tx.body.collect.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.collect.publicationCollectedProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.publicationCollectedProfileId.value));
            context->next_param = PUB_ID;
            break;
        case PUB_ID:
            copy_parameter(context->tx.body.collect.publicationCollectedId.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.publicationCollectedId.value));
            context->next_param = COLLECTOR;
            break;
        case COLLECTOR:
            copy_parameter(context->tx.body.collect.collectorProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.collect.collectorProfileId.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_whitelist_mod(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case MODULE:
            copy_address(context->tx.body.white_list_mod.mod.value,
                         msg->parameter,
                         sizeof(context->tx.body.white_list_mod.mod.value));
            context->next_param = WHITE_LIST;
            break;
        case WHITE_LIST:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.white_list_mod.whitelist)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_set_follow_mod(ethPluginProvideParameter_t *msg,
                                  context_t *context,
                                  uint16_t selector) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(context->tx.body.set_follow.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.set_follow.profile_id.value));
            context->next_param = MODULE;
            break;
        case MODULE:
            copy_address(context->tx.body.set_follow.follow_mod.value,
                         msg->parameter,
                         sizeof(context->tx.body.set_follow.follow_mod.value));

            if (selector == SET_FOLLOW_MOD) {
                context->next_param = NONE;
                break;
            }

            context->next_param = DATA_OFFSET;
            break;
        case DATA_OFFSET:
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.set_follow.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.set_follow.deadline.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_comment(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.comment.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.profile_id.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = PROFILE_ID_POINTED;
            break;
        case PROFILE_ID_POINTED:
            copy_parameter(context->tx.body.comment.profile_id_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.profile_id_pointed.value));
            context->next_param = PUB_ID_POINTED;
            break;
        case PUB_ID_POINTED:
            copy_parameter(context->tx.body.comment.pubid_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.pubid_pointed.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_comment_with_sign(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case DATA_OFFSET:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.comment.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.comment.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.deadline.value));
            context->offset = context->tx.body.comment.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.comment.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.profile_id.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = PROFILE_ID_POINTED;
            break;
        case PROFILE_ID_POINTED:
            copy_parameter(context->tx.body.comment.profile_id_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.profile_id_pointed.value));
            context->next_param = PUB_ID_POINTED;
            break;
        case PUB_ID_POINTED:
            copy_parameter(context->tx.body.comment.pubid_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.comment.pubid_pointed.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_mirror(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.mirror.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.profile_id.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = PROFILE_ID_POINTED;
            break;
        case PROFILE_ID_POINTED:
            copy_parameter(context->tx.body.mirror.profile_id_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.profile_id_pointed.value));
            context->next_param = PUB_ID_POINTED;
            break;
        case PUB_ID_POINTED:
            copy_parameter(context->tx.body.mirror.pubid_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.pubid_pointed.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_mirror_with_sign(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case DATA_OFFSET:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.mirror.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.mirror.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.deadline.value));
            context->offset = context->tx.body.mirror.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.mirror.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.profile_id.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = PROFILE_ID_POINTED;
            break;
        case PROFILE_ID_POINTED:
            copy_parameter(context->tx.body.mirror.profile_id_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.profile_id_pointed.value));
            context->next_param = PUB_ID_POINTED;
            break;
        case PUB_ID_POINTED:
            copy_parameter(context->tx.body.mirror.pubid_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.mirror.pubid_pointed.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_follow(ethPluginProvideParameter_t *msg, context_t *context, uint16_t selector) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            context->next_param = IDS_OFFSET;
            copy_parameter(context->tx.body.follow.followerProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.follow.followerProfileId.value));

            if (selector == FOLLOW) {
                context->next_param = NONE;
                break;
            }
            context->next_param = DATA_OFFSET;
            break;
        case DATA_OFFSET:
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = IDS_OFFSET;
            break;
        case IDS_OFFSET:
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.follow.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.follow.deadline.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_burn(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case TOKEN_ID:
            copy_parameter(context->tx.body.burn.token_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.burn.token_id.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_metadata(ethPluginProvideParameter_t *msg,
                            context_t *context,
                            uint16_t selector) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(context->tx.body.metadata.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.metadata.profile_id.value));

            if (selector == SET_PROFILE_METADATA) {
                context->next_param = NONE;
                break;
            }

            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.metadata.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.metadata.deadline.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_link(ethPluginProvideParameter_t *msg, context_t *context, uint16_t selector) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case HANDLE_ID:
            copy_parameter(context->tx.body.link_unlink.handle_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.link_unlink.handle_id.value));
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.link_unlink.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.link_unlink.profile_id.value));

            if (selector == LINK || selector == UNLINK) {
                context->next_param = NONE;
                break;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.link_unlink.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.link_unlink.deadline.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_mint(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case TO:
            copy_address(context->tx.body.mint.to.value,
                         msg->parameter,
                         sizeof(context->tx.body.mint.to.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_unfollow(ethPluginProvideParameter_t *msg,
                            context_t *context,
                            uint16_t selector) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(context->tx.body.unfollow.unfollowerProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.unfollow.unfollowerProfileId.value));

            if (selector == UNFOLLOW) {
                context->next_param = NONE;
                break;
            }

            context->next_param = DATA_OFFSET;
            break;
        case DATA_OFFSET:
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.unfollow.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.unfollow.deadline.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_set_block_status(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(context->tx.body.set_block_status.byProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.set_block_status.byProfileId.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_set_block_status_with_sign(ethPluginProvideParameter_t *msg,
                                              context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID_OFFSET:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.set_block_status.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.set_block_status.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.set_block_status.deadline.value));
            context->offset = context->tx.body.set_block_status.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.set_block_status.byProfileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.set_block_status.byProfileId.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_change_delegated_exec_2(ethPluginProvideParameter_t *msg, context_t *context) {
    uint16_t n_execs = 0;
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(
                context->tx.body.change_delegated_exec_2.delegatorProfileId.value,
                msg->parameter,
                sizeof(context->tx.body.change_delegated_exec_2.delegatorProfileId.value));
            context->next_param = EXECS_OFFSET;
            break;
        case EXECS_OFFSET:
            if (!U2BE_from_parameter(
                    msg->parameter,
                    &context->tx.body.change_delegated_exec_2.delegatedExecutors_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = APPROVALS_OFFSET;
            break;
        case APPROVALS_OFFSET:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.change_delegated_exec_2.approvals_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->offset = context->tx.body.change_delegated_exec_2.delegatedExecutors_offset;
            context->go_to_offset = true;
            context->next_param = EXECS_NUMBER;
            break;
        case EXECS_NUMBER:
            if (!U2BE_from_parameter(msg->parameter, &n_execs) && n_execs > 1) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = EXECS;
            break;
        case EXECS:
            copy_address(context->tx.body.change_delegated_exec_2.delegatedExecutors.value,
                         msg->parameter,
                         sizeof(context->tx.body.change_delegated_exec_2.delegatedExecutors.value));
            context->offset = context->tx.body.change_delegated_exec_2.approvals_offset;
            context->go_to_offset = true;
            context->next_param = APPROVALS_NUMBER;
            break;
        case APPROVALS_NUMBER:
            context->next_param = APPROVALS;
            break;
        case APPROVALS:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.change_delegated_exec_2.approvals)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_change_delegated_exec_1(ethPluginProvideParameter_t *msg, context_t *context) {
    uint16_t n_execs = 0;
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(
                context->tx.body.change_delegated_exec_1.delegatorProfileId.value,
                msg->parameter,
                sizeof(context->tx.body.change_delegated_exec_1.delegatorProfileId.value));
            context->next_param = EXECS_OFFSET;
            break;
        case EXECS_OFFSET:
            context->next_param = APPROVALS_OFFSET;
            break;
        case APPROVALS_OFFSET:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.change_delegated_exec_1.approvals_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = CONFIG_NUMBER;
            break;
        case CONFIG_NUMBER:
            copy_parameter(context->tx.body.change_delegated_exec_1.configNumber.value,
                           msg->parameter,
                           sizeof(context->tx.body.change_delegated_exec_1.configNumber.value));
            context->next_param = SWITCH_TO_CONFIG;
            break;
        case SWITCH_TO_CONFIG:
            if (!U2BE_from_parameter(
                    msg->parameter,
                    &context->tx.body.change_delegated_exec_1.switchToGivenConfig)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = EXECS_NUMBER;
            break;
        case EXECS_NUMBER:
            if (!U2BE_from_parameter(msg->parameter, &n_execs) && n_execs > 1) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = EXECS;
            break;
        case EXECS:
            copy_address(context->tx.body.change_delegated_exec_1.delegatedExecutors.value,
                         msg->parameter,
                         sizeof(context->tx.body.change_delegated_exec_1.delegatedExecutors.value));
            context->offset = context->tx.body.change_delegated_exec_1.approvals_offset;
            context->go_to_offset = true;
            context->next_param = APPROVALS_NUMBER;
            break;
        case APPROVALS_NUMBER:
            context->next_param = APPROVALS;
            break;
        case APPROVALS:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.change_delegated_exec_1.approvals)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_change_delegated_exec_with_sign(ethPluginProvideParameter_t *msg,
                                                   context_t *context) {
    uint16_t n_execs = 0;
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID:
            copy_parameter(
                context->tx.body.change_delegated_exec_with_sign.delegatorProfileId.value,
                msg->parameter,
                sizeof(context->tx.body.change_delegated_exec_with_sign.delegatorProfileId.value));
            context->next_param = EXECS_OFFSET;
            break;
        case EXECS_OFFSET:
            context->next_param = APPROVALS_OFFSET;
            break;
        case APPROVALS_OFFSET:
            if (!U2BE_from_parameter(
                    msg->parameter,
                    &context->tx.body.change_delegated_exec_with_sign.approvals_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = CONFIG_NUMBER;
            break;
        case CONFIG_NUMBER:
            copy_parameter(
                context->tx.body.change_delegated_exec_with_sign.configNumber.value,
                msg->parameter,
                sizeof(context->tx.body.change_delegated_exec_with_sign.configNumber.value));
            context->next_param = SWITCH_TO_CONFIG;
            break;
        case SWITCH_TO_CONFIG:
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.change_delegated_exec_with_sign.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.change_delegated_exec_with_sign.deadline.value));
            context->next_param = EXECS_NUMBER;
            break;
        case EXECS_NUMBER:
            if (!U2BE_from_parameter(msg->parameter, &n_execs) && n_execs > 1) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = EXECS;
            break;
        case EXECS:
            copy_address(
                context->tx.body.change_delegated_exec_with_sign.delegatedExecutors.value,
                msg->parameter,
                sizeof(context->tx.body.change_delegated_exec_with_sign.delegatedExecutors.value));
            context->offset = context->tx.body.change_delegated_exec_with_sign.approvals_offset;
            context->go_to_offset = true;
            context->next_param = APPROVALS_NUMBER;
            break;
        case APPROVALS_NUMBER:
            context->next_param = APPROVALS;
            break;
        case APPROVALS:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.change_delegated_exec_with_sign.approvals)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_post(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.post.profileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.post.profileId.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = OFFSET;
            break;
        case OFFSET:
            context->next_param = ACTION_OFFSET;
            break;
        case ACTION_OFFSET:
            context->next_param = REFERENCE_MOD;
            break;
        case REFERENCE_MOD:
            copy_address(context->tx.body.post.referenceModule.value,
                         msg->parameter,
                         sizeof(context->tx.body.post.referenceModule.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_post_with_sign(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case PROFILE_ID_OFFSET:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.post.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.post.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.post.deadline.value));
            context->offset = context->tx.body.post.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.post.profileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.post.profileId.value));
            context->next_param = OFFSET;
            break;
        case OFFSET:
            context->next_param = ACTION_OFFSET;
            break;
        case ACTION_OFFSET:
            break;
        case DATA_OFFSET:
            context->next_param = REFERENCE_MOD;
            break;
        case REFERENCE_MOD:
            copy_address(context->tx.body.post.referenceModule.value,
                         msg->parameter,
                         sizeof(context->tx.body.post.referenceModule.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_act(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.act.pubprofileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.pubprofileId.value));
            context->next_param = PUB_ID;
            break;
        case PUB_ID:
            copy_parameter(context->tx.body.act.publicationId.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.publicationId.value));
            context->next_param = ACTOR_ID;
            break;
        case ACTOR_ID:
            copy_parameter(context->tx.body.act.actorprofileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.actorprofileId.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_act_with_sign(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case DATA_OFFSET:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.act.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.act.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.deadline.value));
            context->offset = context->tx.body.act.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.act.pubprofileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.pubprofileId.value));
            context->next_param = PUB_ID;
            break;
        case PUB_ID:
            copy_parameter(context->tx.body.act.publicationId.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.publicationId.value));
            context->next_param = ACTOR_ID;
            break;
        case ACTOR_ID:
            copy_parameter(context->tx.body.act.actorprofileId.value,
                           msg->parameter,
                           sizeof(context->tx.body.act.actorprofileId.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_create_profile(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = TO;
            break;
        case TO:
            copy_address(context->tx.body.create_profile.to.value,
                         msg->parameter,
                         sizeof(context->tx.body.create_profile.to.value));
            context->next_param = FOLLOW;
            break;
        case FOLLOW:
            copy_address(context->tx.body.create_profile.followMod.value,
                         msg->parameter,
                         sizeof(context->tx.body.create_profile.followMod.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_quote(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case DATA_OFFSET:
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.quote.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.profile_id.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = PROFILE_ID_POINTED;
            break;
        case PROFILE_ID_POINTED:
            copy_parameter(context->tx.body.quote.profile_id_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.profile_id_pointed.value));
            context->next_param = PUB_ID_POINTED;
            break;
        case PUB_ID_POINTED:
            copy_parameter(context->tx.body.quote.pubid_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.pubid_pointed.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_quote_with_sign(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case DATA_OFFSET:
            if (!U2BE_from_parameter(msg->parameter, &context->tx.body.quote.profileId_offset)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = SIGNATURE_SIGNER;
            break;
        case SIGNATURE_SIGNER:
            context->offset = msg->parameterOffset + DEADLINE_OFFSET_INSIDE_SIG;
            context->go_to_offset = true;
            context->next_param = DEADLINE;
            break;
        case DEADLINE:
            copy_parameter(context->tx.body.quote.deadline.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.deadline.value));
            context->offset = context->tx.body.quote.profileId_offset;
            context->go_to_offset = true;
            context->next_param = PROFILE_ID;
            break;
        case PROFILE_ID:
            copy_parameter(context->tx.body.quote.profile_id.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.profile_id.value));
            context->next_param = STRING_OFFSET;
            break;
        case STRING_OFFSET:
            context->next_param = PROFILE_ID_POINTED;
            break;
        case PROFILE_ID_POINTED:
            copy_parameter(context->tx.body.quote.profile_id_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.profile_id_pointed.value));
            context->next_param = PUB_ID_POINTED;
            break;
        case PUB_ID_POINTED:
            copy_parameter(context->tx.body.quote.pubid_pointed.value,
                           msg->parameter,
                           sizeof(context->tx.body.quote.pubid_pointed.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case ACT:
            handle_act(msg, context);
            break;
        case ACT_WITH_SIGN:
            handle_act_with_sign(msg, context);
            break;
        case BURN:
            handle_burn(msg, context);
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_1:
            handle_change_delegated_exec_1(msg, context);
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_2:
            handle_change_delegated_exec_2(msg, context);
            break;
        case CHANGE_DELEGATE_EXE_CONFIG_WITH_SIGN:
            handle_change_delegated_exec_with_sign(msg, context);
            break;
        case COLLECT:
            handle_collect(msg, context);
            break;
        case COLLECT_WITH_SIGN:
            handle_collect_with_sign(msg, context);
            break;
        case COMMENT:
            handle_comment(msg, context);
            break;
        case COMMENT_WITH_SIGN:
            handle_comment_with_sign(msg, context);
            break;
        case CREATE_PROFILE:
            handle_create_profile(msg, context);
            break;
        case FOLLOW:
        case FOLLOW_WITH_SIGN:
            handle_follow(msg, context, context->selectorIndex);
            break;
        case LINK:
        case UNLINK:
        case LINK_WITH_SIG:
        case UNLINK_WITH_SIG:
            handle_link(msg, context, context->selectorIndex);
            break;
        case MIRROR:
            handle_mirror(msg, context);
            break;
        case MIRROR_WITH_SIGN:
            handle_mirror_with_sign(msg, context);
            break;
        case MINT:
            handle_mint(msg, context);
            break;
        case POST:
            handle_post(msg, context);
            break;
        case POST_WITH_SIGN:
            handle_post_with_sign(msg, context);
            break;
        case QUOTE:
            handle_quote(msg, context);
            break;
        case QUOTE_WITH_SIGN:
            handle_quote_with_sign(msg, context);
            break;
        case SET_BLOCK_STATUS:
            handle_set_block_status(msg, context);
            break;
        case SET_BLOCK_STATUS_WITH_SIG:
            handle_set_block_status_with_sign(msg, context);
            break;
        case SET_FOLLOW_MOD:
        case SET_FOLLOW_MOD_WITH_SIG:
            handle_set_follow_mod(msg, context, context->selectorIndex);
            break;
        case SET_PROFILE_METADATA:
        case SET_PROFILE_METADATA_WITH_SIGN:
            handle_metadata(msg, context, context->selectorIndex);
            break;
        case UNFOLLOW:
        case UNFOLLOW_WITH_SIGN:
            handle_unfollow(msg, context, context->selectorIndex);
            break;
        case WHITE_LIST_PROFILE_CREATE:
            handle_whitelist_mod(msg, context);
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
