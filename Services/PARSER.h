/*
 * HEX_PARSER.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef HEX_PARSER_H_
#define HEX_PARSER_H_

#include "../Utilities/STD_TYPES.h"
#include "../MCAL/FMI/FMI_Interface.h"

u8 PARSER_u8AsciiTOHex(u8 ascii);
u8 PARSER_u8RecordParser(u8* record);

#endif /* HEX_PARSER_H_ */
