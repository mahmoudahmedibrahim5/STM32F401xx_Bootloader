/*
 * HEX_PARSER.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Mahmoud Ahmed
 */

#include "PARSER.h"

u8 PARSER_u8AsciiTOHex(u8 ascii)
{
	if(ascii >= '0' && ascii <= '9')
		return ascii - '0';
	else if(ascii >= 'A' && ascii <= 'F')
		return ascii-'A'+10;
	else
		return 0xFF;
}

u8 PARSER_u8RecordParser(u8* record)
{
	u8 index = 1;   // index start from one dueto the presence of (:) in the start of the record
    u8 byte[4];     // local variables to be used in readings as buffers

    /* Variables for the Data of the record */
    u8 dataSize, recordType, checkSum;
    u32 flashingAddress;
    u32 data[20];
    static u16 baseAddr = 0x0801;
	u8 calculatedCheckSum = 0;


    /* Data Size */
	byte[0] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
	index += 2;
    calculatedCheckSum += byte[0];

    dataSize = byte[0];


    /* Data Address */
    byte[0] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
    index += 2;
    byte[1] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
    index += 2;
    calculatedCheckSum += byte[0] + byte[1];

    flashingAddress = (baseAddr<<16) | (byte[0]<<8) | (byte[1]);


    /* Record Type */
    byte[0] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
    index += 2;
    calculatedCheckSum += byte[0];

    recordType = byte[0];


    /* Main Data */
    if(recordType == 0)
    {
        for(u8 i=0; i<dataSize/4; i++)
        {
            data[i] = 0;
            for(u8 j=0; j<4; j++)
            {
                byte[j] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
                index += 2;
                calculatedCheckSum += byte[j];
            }
            data[i] = (byte[0]<<24) | (byte[1]<<16) | (byte[2]<<8) | (byte[3]<<0);
        }
        FMI_voidFlashWrite(flashingAddress, data, dataSize/4);
    }
    else if(recordType == 4)
    {
        byte[0] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
        index += 2;
        byte[1] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
        index += 2;
        calculatedCheckSum += byte[0] + byte[1];

        baseAddr = (byte[0]<<8) | (byte[1]);
    }
    // There are 6 record types


    /* Check Sum */
    byte[0] = (PARSER_u8AsciiTOHex(record[index])<<4) | PARSER_u8AsciiTOHex(record[index+1]);
    index += 2;

    checkSum = byte[0];


    /* Check whether the data is correct using check sum */
    calculatedCheckSum = (~calculatedCheckSum) + 1;
    if(checkSum == calculatedCheckSum)
        return 1;
    else
        return 0;
}
