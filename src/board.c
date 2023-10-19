#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "comm.h"
#include "data.h"

const CliCmdType CMD_BOARD = {
        "board",
        1,
        &doBoard,
        "  board            Display the board status and firmware version number\n",
        "  Usage:           "PROGRAM_NAME" board\n",
        "  Example:         "PROGRAM_NAME" board  Display vcc, temperature, firmware version \n"

};
int doBoard(int argc, char *argv[]) {
	(void)argv;
        if(argc != 2) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev <= 0) {
                return ERR;
        }
        uint8_t buf[7];
        if(OK != i2cMem8Read(dev, I2C_MEM_DIAG_TEMPERATURE, buf, 7)) {
                printf("Fail to read board info!\n");
                return ERR;
        }
        uint8_t temperature = buf[0];
	uint16_t v32;
	memcpy(&v32, buf + 1, 2);
	float fv32 = (float)v32 / 1000;
	uint16_t v5;
	memcpy(&v5, buf + 3, 2);
	float fv5 = (float)v5 / 1000;
	uint16_t v3;
	memcpy(&v3, buf + 5, 2);
	float fv3 = (float)v3 / 1000;
        if(ERR == i2cMem8Read(dev, I2C_MEM_REVISION_MAJOR, buf, 2)) {
                printf("Fail to read board info!\n");
                return ERR;
        }
        printf("Firmware version %d.%d, CPU temperature %d C, Power source %0.2f V\n",
                (int)buf[0], (int)buf[1], temperature, fv32);
	(void)fv5;
	(void)fv3;
	// TODO: ASK about Multiple power source types
        return OK;
}

// vi:fdm=marker
