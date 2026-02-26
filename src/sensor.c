#include "comm.h"
#include "data.h"
#include "board.h"
#include "sensor.h"
#include <string.h>
#include <stdio.h>


int valFloatGet(int dev, int addr, float* val) {
	
	// TODO: check if addr in I2C_MEM_SIZE
	uint8_t buf[sizeof(float)];
    if(val == NULL) {
        return ERR;
    }
	if(OK != i2cMem8Read(dev, addr, buf, sizeof(float))) {
		return ERR;
	}
	
	memcpy(val, buf, sizeof(float));
	
	return OK;
}


int doSnsPressRd(int argc, char *argv[]);
const CliCmdType CMD_SENS_PRES_RD = {/*{{{*/
	"snsprd",
	1,
	&doSnsPressRd,
	"  snsprd           Read ATRH external sensor (connected over I2C) pressure value(kPa)\n",
	"  Usage:           "PROGRAM_NAME" snsprd \n",
	"  Example:         "PROGRAM_NAME" snsprd #Read pressure reported by the external sensor\n",
};
int doSnsPressRd(int argc, char *argv[]) {
    (void)argv;
    if(argc != 2) {
        return ARG_CNT_ERR;
    }
    int dev = doSensorInit();
    if(dev < 0) {
        return ERR;
    }
    float val;
    if(OK != valFloatGet(dev, I2C_MEM_PRESSURE_ADD, &val)) {
        printf("Fail to read pressure from sensor!\n");
        return ERR;
    }
    printf("%.3f\n", val);
    return OK;
}/*}}}*/


int doSnsTempRd(int argc, char *argv[]);
const CliCmdType CMD_SENS_TEMP_RD = {/*{{{*/
    "snstrd",   
    1,
    &doSnsTempRd,
    "  snstrd           Read ATRH external sensor (connected over I2C) temperature value(C)\n",
    "  Usage:           "PROGRAM_NAME" snstrd \n",
    "  Example:         "PROGRAM_NAME" snstrd #Read temperature reported by the external sensor\n",
};
int doSnsTempRd(int argc, char *argv[]) {
    (void)argv;
    if(argc != 2) {
        return ARG_CNT_ERR;
    }
    int dev = doSensorInit();
    if(dev < 0) {
        return ERR;
    }
    float val;
    if(OK != valFloatGet(dev, I2C_MEM_TEMPERATURE_ADD, &val)) {
        printf("Fail to read temperature from sensor!\n");
        return ERR;
    }
    printf("%.3f\n", val);
    return OK;
}/*}}}*/

int doSnsDensRd(int argc, char *argv[]);
const CliCmdType CMD_SENS_DENS_RD = {/*{{{*/
    "snsdrd",
    1,
    &doSnsDensRd,
    "  snsdrd           Read ATRH external sensor (connected over I2C) density value(kg/m3)\n",
    "  Usage:           "PROGRAM_NAME" snsdrd \n",
    "  Example:         "PROGRAM_NAME" snsdrd #Read density reported by the external sensor\n",
};
int doSnsDensRd(int argc, char *argv[]) {
    (void)argv;
    if(argc != 2) {
        return ARG_CNT_ERR;
    }
    int dev = doSensorInit();
    if(dev < 0) {
        return ERR;
    }
    float val;
    if(OK != valFloatGet(dev, I2C_MEM_DENSITY_ADD, &val)) {
        printf("Fail to read density from sensor!\n");
        return ERR;
    }
    printf("%.3f\n", val);
    return OK;
}/*}}}*/

int doSnsHumidRd(int argc, char *argv[]);
const CliCmdType CMD_SENS_HUMID_RD = {/*{{{*/
    "snshrd",
    1,
    &doSnsHumidRd,
    "  snshrd           Read ATRH external sensor (connected over I2C) humidity value(%%)\n",
    "  Usage:           "PROGRAM_NAME" snshrd \n",
    "  Example:         "PROGRAM_NAME" snshrd #Read humidity reported by the external sensor\n",
};
int doSnsHumidRd(int argc, char *argv[]) {
    (void)argv;
    if(argc != 2) {
        return ARG_CNT_ERR;
    }
    int dev = doSensorInit();
    if(dev < 0) {
        return ERR;
    }
    float val;
    if(OK != valFloatGet(dev, I2C_MEM_HUMIDITY_ADD, &val)) {
        printf("Fail to read humidity from sensor!\n");
        return ERR;
    }
    printf("%.3f\n", val);
    return OK;
}/*}}}*/    

int doSnsSecTempRd(int argc, char *argv[]);
const CliCmdType CMD_SENS_SEC_TEMP_RD = {/*{{{*/
    "snst2rd",
    1,
    &doSnsSecTempRd,
    "  snst2rd          Read ATRH external sensor (connected over I2C) secondary temperature value(C)\n",
    "  Usage:           "PROGRAM_NAME" snst2rd \n",
    "  Example:         "PROGRAM_NAME" snst2rd #Read secondary temperature reported by the external sensor\n",
};
int doSnsSecTempRd(int argc, char *argv[]) {
    (void)argv;
    if(argc != 2) {
        return ARG_CNT_ERR;
    }
    int dev = doSensorInit();
    if(dev < 0) {
        return ERR;
    }
    float val;
    if(OK != valFloatGet(dev, I2C_MEM_SECONDARY_TEMPERATURE_ADD, &val)) {
        printf("Fail to read secondary temperature from sensor!\n");
        return ERR;
    }
    printf("%.3f\n", val);
    return OK;
}/*}}}*/    