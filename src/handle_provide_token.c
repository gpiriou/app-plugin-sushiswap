#include "sushiswap_plugin.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideToken_t *msg = (ethPluginProvideToken_t *) parameters;
    sushiswap_parameters_t *context = (sushiswap_parameters_t *) msg->pluginContext;
    PRINTF("plugin provide token: 0x%p, 0x%p\n", msg->token1, msg->token2);

    // No need to check token1 for transactions involving sending ETH
    if (!(context->selectorIndex == ADD_LIQUIDITY_ETH) &&
        !(context->selectorIndex == SWAP_EXACT_ETH_FOR_TOKENS) &&
        !(context->selectorIndex == SWAP_EXACT_ETH_FOR_TOKENS_FEE)) {
        if (msg->token1) {
            context->decimals_token_a = msg->token1->decimals;
            strncpy(context->ticker_token_a,
                    (char *) msg->token1->ticker,
                    sizeof(context->ticker_token_a));
        } else {
            context->decimals_token_a = DEFAULT_DECIMAL;
            strncpy(context->ticker_token_a, DEFAULT_TICKER, sizeof(context->ticker_token_a));
            // We will need an additional screen to display a warning message.
            context->screen_array |= WARNING_TOKEN_A_UI;
            msg->additionalScreens++;
        }
    }

    // No need to check token2 for REMOVE_LIQUIDITY_ETH_PERMIT     ?????? The token address is in
    // the parameter data so what is the difference ?
    if (context->selectorIndex == REMOVE_LIQUIDITY_ETH ||
        context->selectorIndex == REMOVE_LIQUIDITY_ETH_PERMIT ||
        context->selectorIndex == REMOVE_LIQUIDITY_ETH_FEE ||
        context->selectorIndex == REMOVE_LIQUIDITY_ETH_PERMIT_FEE) {
        context->decimals_token_b = WETH_DECIMALS;
        strncpy(context->ticker_token_b, "WETH ", 5);
        msg->result = ETH_PLUGIN_RESULT_OK;
        return;
    }

    if (msg->token2) {
        context->decimals_token_b = msg->token2->decimals;
        strncpy(context->ticker_token_b,
                (char *) msg->token2->ticker,
                sizeof(context->ticker_token_b));
    } else {
        context->decimals_token_b = DEFAULT_DECIMAL;
        strncpy(context->ticker_token_b, DEFAULT_TICKER, sizeof(context->ticker_token_b));
        context->screen_array |= WARNING_TOKEN_B_UI;
        msg->additionalScreens++;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}