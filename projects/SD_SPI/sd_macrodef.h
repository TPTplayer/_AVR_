#ifndef SD_MACRODEF_H_
#define SD_MACRODEF_H_

#include <avr/io.h>
#include "GPIO_SPI.h"

#define _DDR_SD_SS      _DDR_SS
#define _DDR_SD_SCK     _DDR_SCK
#define _DDR_SD_MOSI    _DDR_MOSI
#define _DDR_SD_MISO    _DDR_MISO

#define _PORT_SD_SS     _PORT_SS
#define _PORT_SD_SCK    _PORT_SCK
#define _PORT_SD_MOSI   _PORT_MOSI
#define _PORT_SD_MISO   _PORT_MISO

#define _PIN_SD_SS      _PIN_SS
#define _PIN_SD_SCK     _PIN_SCK
#define _PIN_SD_MOSI    _PIN_MOSI
#define _PIN_SD_MISO    _PIN_MISO

#define _SD_SS      _SS
#define _SD_SCK     _SCK
#define _SD_MOSI    _MOSI
#define _SD_MISO    _MISO

#define _CMD0   0
#define _CMD1   1
#define _CMD6   6
#define _CMD8   8
#define _CMD9   9
#define _CMD10  10
#define _CMD12  12
#define _CMD13  13
#define _CMD16  16
#define _CMD17  17
#define _CMD18  18
#define _CMD24  24
#define _CMD25  25
#define _CMD27  27
#define _CMD28  28
#define _CMD29  29
#define _CMD30  30
#define _CMD32  32
#define _CMD33  33
#define _CMD38  38
#define _CMD42  42
#define _CMD55  55
#define _CMD56  56
#define _CMD58  58
#define _CMD59  59

#define _ACMD13 13
#define _ACMD22 22
#define _ACMD23 23
#define _ACMD41 41
#define _ACMD42 42
#define _ACMD51 51

#define _CMD_BYTE_LEN   6
#define _CMD_BIT_LEN    _CMD_BYTE_LEN * 8

#define _BLOCK_BYTE_LEN	512
#define _BLOCK_BIT_LEN	_BLOCK_BYTE_LEN * 8

#define _CMD_HEADER(x)  (0x40 | (x & 0x3F))
#define _CMD_CRC7(x)    ((x << 1) | 0x01)
#define _CMD_PACKET(_HEADER_, _ARGUMENT_, _CRC_) (uint64_t)(((uint64_t)_HEADER_ << 40) | ((uint64_t)_ARGUMENT_ << 8) | _CRC_)

#define _OCR_BIT_LEN    32

#define _RESP1_BIT_LEN  8
#define _RESP2_BIT_LEN  _RESP1_BIT_LEN + 8
#define _RESP3_BIT_LEN  _RESP1_BIT_LEN + _OCR_BIT_LEN
#define _RESP7_BIT_LEN  _RESP1_BIT_LEN + 32

#define _RESP1  1
#define _RESP2  2
#define _RESP3  3
#define _RESP7  7

#define _R1_IN_IDLE_STATE           0
#define _R1_ERASE_RESET             1
#define _R1_ILLEGAL_COMMAND         2
#define _R1_COM_CRC_ERROR           3
#define _R1_ERASE_SEQUENCE_ERROR    4
#define _R1_ADDRESS_ERROR           5
#define _R1_PARAMETER_ERROR         6

#define _R2_CARD_IS_LOCKED          0
#define _R2_WP_ERASE_SKIP           1
#define _R2_LOCK_UNLOCK_CMD_FAILED  1
#define _R2_ERROR                   2
#define _R2_CC_ERROR                3
#define _R2_CARD_ECC_FAILED         4
#define _R2_WP_VIOLATION            5
#define _R2_ERASE_PARAM             6
#define _R2_OUT_OF_RANGE            7
#define _R2_CSD_OVERWRITE           7

#define _OCR_VRANGE_2728            15
#define _OCR_VRANGE_2829            16
#define _OCR_VRANGE_2930            17
#define _OCR_VRANGE_3031            18
#define _OCR_VRANGE_3132            19
#define _OCR_VRANGE_3233            20
#define _OCR_VRANGE_3334            21
#define _OCR_VRANGE_3435            22
#define _OCR_VRANGE_3536            23
#define _OCR_S18A                   24
#define _OCR_CO2T                   27
#define _OCR_UHS2                   29
#define _OCR_CCS                    30
#define _OCR_BUSY                   31

#define _R2_MASK_R1(_RESP2_)            (uint8_t)((_RESP2_ & ((uint16_t)0xFF << (_RESP2_BIT_LEN - _RESP1_BIT_LEN))) >> (_RESP2_BIT_LEN - _RESP1_BIT_LEN))
#define _R2_MASK_R2(_RESP2_)            (uint8_t)(_RESP2_ & 0xFF)
#define _R3_MASK_R1(_RESP3_)            (uint8_t)((_RESP3_ & ((uint64_t)0xFF << (_RESP3_BIT_LEN - _RESP1_BIT_LEN))) >> (_RESP3_BIT_LEN - _RESP1_BIT_LEN))
#define _R3_MASK_OCR(_RESP3_)           (uint32_t)(_RESP3_ & 0xFFFFFFFF)
#define _R7_MASK_R1(_RESP7_)            (uint8_t)((_RESP7_ & ((uint64_t)0xFF << (_RESP7_BIT_LEN - _RESP1_BIT_LEN))) >> (_RESP7_BIT_LEN - _RESP1_BIT_LEN))
#define _R7_MASK_VCA(_RESP7_)           (uint8_t)((_RESP7_ & ((uint16_t)0x0F << 8)) >> 8)
#define _R7_MASK_CHECKPATTERN(_RESP7_)  (uint8_t)(_RESP7_ & 0xFF)

#define _MASK(_DATA_, _BITNUM_)    (uint8_t)((_DATA_ & (1 << _BITNUM_)) >> _BITNUM_)

#define _CMD8_ARGUMENT(_VHS_, _CHECK_PATTERN_)  (uint32_t)(((uint16_t)_VHS_ << 8) | _CHECK_PATTERN_)
#define _ACMD41_ARGUMENT(_HCS_)                 (uint32_t)((uint32_t)_HCS_ << 30)

#define _ATTEMPT_LIMIT	20
#define _SD_ERROR	-1
#define _SD_SUCCESS	0

#endif /* SD_MACRODEF_H_ */