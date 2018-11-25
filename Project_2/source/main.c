/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
// SDK Included Files
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "MKL25Z4.h"
#include "fsl_tpm_driver.h"
#include "fsl_debug_console.h"
#include "uart_driver.h"
////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
// Timer period: 500000uS
#define TMR_PERIOD                          (500000U)
#define TX_BUFFER_LEN						(256)
#define RX_BUFFER_LEN						(64)

#define BLOCKING_MODE
#if defined(TWR_KV46F150M)
#define LPTMR0_IDX LPTMR_IDX
#endif

uint8_t* message = 0;
volatile char chara = '\0';
////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief LPTMR interrupt call back function.
 * The function is used to toggle LED1.
 */
void lptmr_call_back(void)
{
    // Toggle LED1
    LED1_TOGGLE;
}

//
/*!
 * @brief Main function
 */
int main (void)
{
    // UART HANDLE
    UART_handle_t uart_handle  = {

    	.status = UART_STATE_RESET,
		.rx_buffer_size = RX_BUFFER_LEN,
		.tx_buffer_size = TX_BUFFER_LEN,
    	.baudrate = BAUDRATE_38400
    };

	// Initialize LED1
    LED1_EN;

	// UART INIT
	UART_init(&uart_handle);

    while(1)
    {
#ifdef BLOCKING_MODE
		   /*wait till data register is empty*/
		   while((UART0_S1 & UART_S1_RDRF_MASK) == 0);
    	   chara = UART0->D;
    	   if((UART0_S1 & UART0_S1_TDRE_MASK ) && (UART0_S1 & UART0_C2_TIE_MASK)) {
    	    	UART0->D = chara;
    	    }
#endif
    }

    return 0;
}
