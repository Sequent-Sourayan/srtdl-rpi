#ifndef SENSOR_H
#define SENSOR_H
#include "comm.h"
#include "cli.h"

extern const CliCmdType CMD_SENS_PRES_RD;
extern const CliCmdType CMD_SENS_TEMP_RD;
extern const CliCmdType CMD_SENS_DENS_RD;
extern const CliCmdType CMD_SENS_HUMID_RD;
extern const CliCmdType CMD_SENS_SEC_TEMP_RD;

int doSnsPressRd(int argc, char *argv[]);
int doSnsTempRd(int argc, char *argv[]);
int doSnsDensRd(int argc, char *argv[]);
int doSnsHumidRd(int argc, char *argv[]);
int doSnsSecTempRd(int argc, char *argv[]);






#endif /* SENSOR_H */