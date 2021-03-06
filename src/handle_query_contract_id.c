#include "sushiswap_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    sushiswap_parameters_t *context = (sushiswap_parameters_t *) msg->pluginContext;

    // set 'Sushiswap' title.
    strncpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case ADD_LIQUIDITY_ETH:
        case ADD_LIQUIDITY:
            strncpy(msg->version, "Add liquidity", msg->versionLength);
            break;
        case REMOVE_LIQUIDITY:
        case REMOVE_LIQUIDITY_PERMIT:
        case REMOVE_LIQUIDITY_ETH:
        case REMOVE_LIQUIDITY_ETH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_FEE:
        case REMOVE_LIQUIDITY_ETH_PERMIT_FEE:
            strncpy(msg->version, "Remove liquidity", msg->versionLength);
            break;
        case SWAP_ETH_FOR_EXACT_TOKENS:
        case SWAP_EXACT_ETH_FOR_TOKENS:
        case SWAP_EXACT_ETH_FOR_TOKENS_FEE:
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_TOKENS_FOR_ETH_FEE:
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_TOKENS_FEE:
        case SWAP_TOKENS_FOR_EXACT_ETH:
        case SWAP_TOKENS_FOR_EXACT_TOKENS:
            strncpy(msg->version, "Swap tokens", msg->versionLength);
            break;
        default:
            PRINTF("Selector Index :%d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}