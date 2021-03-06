/*
 * app.h
 *
 *  Created on: Jun 26, 2018
 *      Author: conor
 */

#ifndef SRC_APP_H_
#define SRC_APP_H_

#include <stdint.h>

#define IS_BOOTLOADER

#define DEBUG_LEVEL 0

//#define PRINTING_USE_VCOM

//#define USING_DEV_BOARD

#define BRIDGE_TO_WALLET

#define JUMP_LOC	0x4000

#ifdef USING_DEV_BOARD
#define PUSH_BUTTON		gpioPortF,6
#else
#define PUSH_BUTTON		gpioPortD,13
#endif

//#define DISABLE_CTAPHID_PING
#define DISABLE_CTAPHID_WINK
#define DISABLE_CTAPHID_CBOR

void printing_init();

int bootloader_bridge(uint8_t klen, uint8_t * keyh);

int is_authorized_to_boot();

#define LED_INIT_VALUE			0x101000

extern uint8_t REBOOT_FLAG;

#endif /* SRC_APP_H_ */
