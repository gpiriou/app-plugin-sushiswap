/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "os.h"
#include "cx.h"
#include "sushiswap_plugin.h"

// Define here all the selectors you wish to support.

static const uint8_t SUSHISWAP_ADD_LIQUIDITY[SELECTOR_SIZE] = {0xe8, 0xe3, 0x37, 0x00};
static const uint8_t SUSHISWAP_ADD_LIQUIDITY_ETH[SELECTOR_SIZE] = {0xf3, 0x05, 0xd7, 0x19};
static const uint8_t SUSHISWAP_REMOVE_LIQUIDITY[SELECTOR_SIZE] = {0xba, 0xa2, 0xab, 0xde};
static const uint8_t SUSHISWAP_REMOVE_LIQUIDITY_PERMIT[SELECTOR_SIZE] = {0x21, 0x95, 0x99, 0x5c};
static const uint8_t SUSHISWAP_REMOVE_LIQUIDITY_ETH[SELECTOR_SIZE] = {0x02, 0x75, 0x1c, 0xec};
static const uint8_t SUSHISWAP_REMOVE_LIQUIDITY_ETH_PERMIT[SELECTOR_SIZE] = {0xde,
                                                                             0xd9,
                                                                             0x38,
                                                                             0x2a};
static const uint8_t SUSHISWAP_REMOVE_LIQUIDITY_ETH_FEE[SELECTOR_SIZE] = {0xaf, 0x29, 0x79, 0xeb};
static const uint8_t SUSHISWAP_REMOVE_LIQUIDITY_ETH_PERMIT_FEE[SELECTOR_SIZE] = {0x5b,
                                                                                 0x0d,
                                                                                 0x59,
                                                                                 0x84};
static const uint8_t SUSHISWAP_SWAP_ETH_FOR_EXACT_TOKENS[SELECTOR_SIZE] = {0xfb, 0x3b, 0xdb, 0x41};
static const uint8_t SUSHISWAP_SWAP_EXACT_ETH_FOR_TOKENS[SELECTOR_SIZE] = {0x7f, 0xf3, 0x6a, 0xb5};
static const uint8_t SUSHISWAP_SWAP_EXACT_ETH_FOR_TOKENS_FEE[SELECTOR_SIZE] = {0xb6,
                                                                               0xf9,
                                                                               0xde,
                                                                               0x95};
static const uint8_t SUSHISWAP_SWAP_EXACT_TOKENS_FOR_ETH[SELECTOR_SIZE] = {0x18, 0xcb, 0xaf, 0xe5};
static const uint8_t SUSHISWAP_SWAP_EXACT_TOKENS_FOR_ETH_FEE[SELECTOR_SIZE] = {0x79,
                                                                               0x1a,
                                                                               0xc9,
                                                                               0x47};
static const uint8_t SUSHISWAP_SWAP_EXACT_TOKENS_FOR_TOKENS[SELECTOR_SIZE] = {0x38,
                                                                              0xed,
                                                                              0x17,
                                                                              0x39};
static const uint8_t SUSHISWAP_SWAP_EXACT_TOKENS_FOR_TOKENS_FEE[SELECTOR_SIZE] = {0x5c,
                                                                                  0x11,
                                                                                  0xd7,
                                                                                  0x95};
static const uint8_t SUSHISWAP_SWAP_TOKENS_FOR_EXACT_ETH[SELECTOR_SIZE] = {0x4a, 0x25, 0xd9, 0x4a};
static const uint8_t SUSHISWAP_SWAP_TOKENS_FOR_EXACT_TOKENS[SELECTOR_SIZE] = {0x88,
                                                                              0x03,
                                                                              0xdb,
                                                                              0xee};

// Array of all the different sushiswap selectors. Make sure this follows the same order as the
// enum defined in `sushiswap_plugin.h`
const uint8_t *const SUSHISWAP_SELECTORS[NUM_SUSHISWAP_SELECTORS] = {
    SUSHISWAP_ADD_LIQUIDITY,
    SUSHISWAP_ADD_LIQUIDITY_ETH,
    SUSHISWAP_REMOVE_LIQUIDITY,
    SUSHISWAP_REMOVE_LIQUIDITY_PERMIT,
    SUSHISWAP_REMOVE_LIQUIDITY_ETH,
    SUSHISWAP_REMOVE_LIQUIDITY_ETH_PERMIT,
    SUSHISWAP_REMOVE_LIQUIDITY_ETH_FEE,
    SUSHISWAP_REMOVE_LIQUIDITY_ETH_PERMIT_FEE,
    SUSHISWAP_SWAP_ETH_FOR_EXACT_TOKENS,
    SUSHISWAP_SWAP_EXACT_ETH_FOR_TOKENS,
    SUSHISWAP_SWAP_EXACT_ETH_FOR_TOKENS_FEE,
    SUSHISWAP_SWAP_EXACT_TOKENS_FOR_ETH,
    SUSHISWAP_SWAP_EXACT_TOKENS_FOR_ETH_FEE,
    SUSHISWAP_SWAP_EXACT_TOKENS_FOR_TOKENS,
    SUSHISWAP_SWAP_EXACT_TOKENS_FOR_TOKENS_FEE,
    SUSHISWAP_SWAP_TOKENS_FOR_EXACT_ETH,
    SUSHISWAP_SWAP_TOKENS_FOR_EXACT_TOKENS,
};

// Function to dispatch calls from the ethereum app.
void dispatch_plugin_calls(int message, void *parameters) {
    PRINTF("just in: message: %d\n", message);
    switch (message) {
        case ETH_PLUGIN_INIT_CONTRACT:
            PRINTF("INIT CONTRACT\n");
            handle_init_contract(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_PARAMETER:
            PRINTF("PROVIDE PARAMETER\n");
            handle_provide_parameter(parameters);
            break;
        case ETH_PLUGIN_FINALIZE:
            PRINTF("FINALIZE\n");
            handle_finalize(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_TOKEN:
            PRINTF("PROVIDE TOKEN\n");
            handle_provide_token(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_ID:
            PRINTF("QUERY CONTRACT ID\n");
            handle_query_contract_id(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            PRINTF("QUERY CONTRACT UI\n");
            handle_query_contract_ui(parameters);
            break;
        default:
            PRINTF("Unhandled message %d\n", message);
            break;
    }
}

// Calls the ethereum app.
void call_app_ethereum() {
    unsigned int libcall_params[3];
    libcall_params[0] = (unsigned int) "Ethereum";
    libcall_params[1] = 0x100;
    libcall_params[2] = RUN_APPLICATION;
    os_lib_call((unsigned int *) &libcall_params);
}

// Weird low-level black magic.
__attribute__((section(".boot"))) int main(int arg0) {
    // Low-level black magic, don't touch.
    // exit critical section
    __asm volatile("cpsie i");

    // Low-level black magic, don't touch.
    // ensure exception will work as planned
    os_boot();

    // Try catch block. Please read the docs for more information on how to use those!
    BEGIN_TRY {
        TRY {
            // Low-level black magic. Don't touch.
            check_api_level(CX_COMPAT_APILEVEL);

            // Check if we are called from the dashboard.
            if (!arg0) {
                // called from dashboard, launch Ethereum app
                call_app_ethereum();
                return 0;
            } else {
                // not called from dashboard: called from the ethereum app!
                unsigned int *args = (unsigned int *) arg0;

                // If `ETH_PLUGIN_CHECK_PRESENCE`, we can skip `dispatch_plugin_calls`.
                if (args[0] != ETH_PLUGIN_CHECK_PRESENCE) {
                    dispatch_plugin_calls(args[0], (void *) args[1]);
                }

                // Call `os_lib_end`, go back to the ethereum app.
                os_lib_end();
            }
        }
        FINALLY {
        }
    }
    END_TRY;

    // Will not get reached.
    return 0;
}
