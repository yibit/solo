/*
   Copyright 2018 Conor Patrick

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
#ifndef _CTAPHID_H_H
#define _CTAPHID_H_H

#include "device.h"
#include "ctap_errors.h"

#define TYPE_INIT               0x80
#define TYPE_CONT               0x00

#define CTAPHID_PING         (TYPE_INIT | 0x01)
#define CTAPHID_MSG          (TYPE_INIT | 0x03)
#define CTAPHID_LOCK         (TYPE_INIT | 0x04)
#define CTAPHID_INIT         (TYPE_INIT | 0x06)
#define CTAPHID_WINK         (TYPE_INIT | 0x08)
#define CTAPHID_CBOR         (TYPE_INIT | 0x10)
#define CTAPHID_CANCEL       (TYPE_INIT | 0x11)
#define CTAPHID_ERROR        (TYPE_INIT | 0x3f)

    #define ERR_INVALID_CMD         0x01
    #define ERR_INVALID_PAR         0x02
    #define ERR_INVALID_SEQ         0x04
    #define ERR_MSG_TIMEOUT         0x05
    #define ERR_CHANNEL_BUSY        0x06


#define CTAPHID_INIT_PAYLOAD_SIZE  (HID_MESSAGE_SIZE-7)
#define CTAPHID_CONT_PAYLOAD_SIZE  (HID_MESSAGE_SIZE-5)

#define CTAPHID_BROADCAST_CID       0xffffffff

#define CTAPHID_BUFFER_SIZE         7609

#define CAPABILITY_WINK             0x01
#define CAPABILITY_LOCK             0x02
#define CAPABILITY_CBOR             0x04
#define CAPABILITY_NMSG             0x08

#define CTAP_CAPABILITIES           (CAPABILITY_WINK | CAPABILITY_CBOR)

typedef struct
{
    uint32_t cid;
    union{
        struct{
            uint8_t cmd;
            uint8_t bcnth;
            uint8_t bcntl;
            uint8_t payload[CTAPHID_INIT_PAYLOAD_SIZE];
        } init;
        struct{
            uint8_t seq;
            uint8_t payload[CTAPHID_CONT_PAYLOAD_SIZE];
        } cont;
    } pkt;
} CTAPHID_PACKET;


typedef struct
{
    uint8_t nonce[8];
    uint32_t cid;
    uint8_t protocol_version;
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t build_version;
    uint8_t capabilities;
} __attribute__((packed)) CTAPHID_INIT_RESPONSE;



void ctaphid_init();

void ctaphid_handle_packet(uint8_t * pkt_raw);

void ctaphid_check_timeouts();


#define ctaphid_packet_len(pkt)     ((uint16_t)((pkt)->pkt.init.bcnth << 8) | ((pkt)->pkt.init.bcntl))

#endif
