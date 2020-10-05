#ifndef _SD_CMD_ARGUMENTS_H_
#define _SD_CMD_ARGUMENTS_H_

#include <stdint.h>

#define _CMD8_ARGUMENT(_VHS_, _CHECK_PATTERN_)  (uint32_t)(((uint16_t)_VHS_ << 8) | _CHECK_PATTERN_)
#define _ACMD41_ARGUMENT(_HCS_)                 (uint32_t)((uint32_t)_HCS_ << 30)

#endif /* _SD_CMD_ARGUMENTS_H_ */