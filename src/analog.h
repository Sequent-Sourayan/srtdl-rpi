#ifndef ANALOG_H
#define ANALOG_H

#include "cli.h"

extern const CliCmdType CMD_U_RES_WRITE;
extern const CliCmdType CMD_U5_IN_READ;
extern const CliCmdType CMD_U5_IN_CAL;
extern const CliCmdType CMD_U30M_IN_READ;
extern const CliCmdType CMD_U30M_IN_CAL;
extern const CliCmdType CMD_I_IN_READ;
extern const CliCmdType CMD_I_IN_CAL;


int doUResWrite(int argc, char *argv[]);
int doU5InRead(int argc, char *argv[]);
int doU5Cal(int argc, char *argv[]);
int doU30MInRead(int argc, char *argv[]);
int doU30Cal(int argc, char *argv[]);
int doIInRead(int argc, char *argv[]);
int doIInCal(int argc, char *argv[]);

#endif /* ANALOG_H */

// vi:fdm=marker
