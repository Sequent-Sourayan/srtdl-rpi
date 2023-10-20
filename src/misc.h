#ifndef MISC_H
#define MISC_H

#include "cli.h"

extern const CliCmdType CMD_WIND_DIR_READ;
extern const CliCmdType CMD_WIND_DIR_CAL;
extern const CliCmdType CMD_WIND_SPEED_READ;
extern const CliCmdType CMD_PANEL_VOLT_READ;
extern const CliCmdType CMD_PANEL_VOLT_CAL;
extern const CliCmdType CMD_PANEL_CRT_READ;
extern const CliCmdType CMD_FAN_PWR_READ;
extern const CliCmdType CMD_FAN_PWR_WRITE;
extern const CliCmdType CMD_PRESSURE_READ;
extern const CliCmdType CMD_TEMP_READ;
extern const CliCmdType CMD_PANEL_SHORT_CMD;

int doWindDirRead(int argc, char *argv[]);
int doWindDirCal(int argc, char *argv[]);
int doWindSpeedRead(int argc, char *argv[]);
int doPanelVoltRead(int argc, char *argv[]);
int doPanelVoltCal(int argc, char *argv[]);
int doPanelCrtRead(int argc, char *argv[]);
int doFanPwrRead(int argc, char *argv[]);
int doFanPwrWrite(int argc, char *argv[]);
int doPressureRead(int argc, char *argv[]);
int doTempRead(int argc, char *argv[]);
int doPanelShortCmd(int argc, char *argv[]);

#endif /* MISC_H */
