#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "calib.h"
#include "data.h"
#include "misc.h"


const CliCmdType CMD_RAIN_COUNT_READ =
{
	"rcrd",
	1,
	&doRainCountRead,
	"  rcrd           Read rain sensor counter\n",
	"  Usage:           "PROGRAM_NAME" rcrd\n",
	"  Example:         "PROGRAM_NAME" rcrd\n",
};
int doRainCountRead(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	u32 val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_RAIN_COUNT, buf,
			sizeof (val)))
	{
		printf("Fail to read rain sensor counter\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%d\n", val);
	return OK;
}

const CliCmdType CMD_RAIN_COUNT_RESET =
{
	"rcrst",
	1,
	&doRainCountReset,
	"  rcrst           Reset the  rain sensor counter\n",
	"  Usage:           "PROGRAM_NAME" rcrst\n",
	"  Example:         "PROGRAM_NAME" rcrst\n",
};
int doRainCountReset(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	
	u8 buf[1];
	buf[0] = RESET_CALIBRATION_KEY;
	if (OK
		!= i2cMem8Write(dev, I2C_MEM_RAIN_COUNT_RESET, buf, 1))
	{
		printf("Fail to reset rain sensor counter\n");
		return ERR;
	}
	
	printf("OK\n");
	return OK;
}
const CliCmdType CMD_WIND_DIR_READ =
{
	"wdirrd",
	1,
	&doWindDirRead,
	"  wdirrd           Read wind direction\n",
	"  Usage:           "PROGRAM_NAME" wdirrd\n",
	"  Example:         "PROGRAM_NAME" wdirrd\n",
};
int doWindDirRead(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = 1;
	u16 val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_WIND_DIR + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to read wind direction\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%0.3f\n", val * MV_TO_V);
	return OK;
}

const CliCmdType CMD_WIND_DIR_CAL =
{
	"wdircal",
	1,
	&doWindDirCal,
	"  wdircal          Calibrate wind direction(V)\n",
	"  Usage:           "PROGRAM_NAME" wdircal <value(V)>\n",
	"  Example:         "PROGRAM_NAME" wdircal 3.2; Calibrate wind direction at 3.2V\n",
};
int doWindDirCal(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int ch = 1;
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	if (strcasecmp(argv[3], "reset") == 0)
	{
		if (OK != calibReset(dev, CAL_CH_WIND_DIR_IN + (ch - 1)))
		{
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[3]);
	if (OK != calibSet(dev, CAL_CH_WIND_DIR_IN + (ch - 1), value))
	{
		return ERR;
	}
	return OK;
}

const CliCmdType CMD_WIND_SPEED_READ =
{
	"wspdrd",
	1,
	&doWindSpeedRead,
	"  wspdrd           Read wind speed(Pulse per second)\n",
	"  Usage:           "PROGRAM_NAME" wspdrd\n",
	"  Example:         "PROGRAM_NAME" wspdrd\n",
};
int doWindSpeedRead(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = 1;
	u16 val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_WIND_SPEED + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to read wind speed!\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%d\n", val);
	return OK;
}

const CliCmdType CMD_PANEL_SHORT_CMD =
{
	"pscm",
	1,
	&doPanelShortCmd,
	"  pscm             Measure short circuit current for both panels (short-circit for one sec and measure the current)\n",
	"  Usage:           "PROGRAM_NAME" pscm\n",
	"  Example:         "PROGRAM_NAME" pscm; Card make short circuit for 1 sec to the both pannels and measure the current\n",
};
int doPanelShortCmd(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	u8 key = CALIBRATION_KEY;
	if (OK != i2cMem8Write(dev, I2C_MEM_PANEL_CMD, &key, 1))
		{
			printf("Fail to start measurement!\n");
			return ERR;
		}
	return OK;
}

const CliCmdType CMD_PANEL_VOLT_READ =
{
	"pvrd",
	1,
	&doPanelVoltRead,
	"  pvrd             Read panel voltage(V)\n",
	"  Usage:           "PROGRAM_NAME" pvrd <ch>\n",
	"  Example:         "PROGRAM_NAME" pvrd <ch>\n",
};
int doPanelVoltRead(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = atoi(argv[2]);
	if (! (1 <= ch && ch <= PANEL_CH_NO))
	{
		printf("Invalid panel channel[1.."STR(PANEL_CH_NO)"]!\n");
		return ARG_RANGE_ERR;
	}
	u16 val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_PANEL_VOLT1 + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to read panel voltage\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	float fval = (float)val * MV_TO_V;
	printf("%.3f\n", fval);
	return OK;
}

const CliCmdType CMD_PANEL_VOLT_CAL =
{
	"pvcal",
	1,
	&doPanelVoltCal,
	"  pvcal             Calibrate solar panel voltage(V)\n",
	"  Usage:           "PROGRAM_NAME" pvcal <ch> <value(V)>\n",
	"  Example:         "PROGRAM_NAME" pvcal 2 10; Calibrate solar panel #2 at 10V\n",
};
int doPanelVoltCal(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[2]);
	if (! (1 <= ch && ch <= PANEL_CH_NO))
	{
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	if (strcasecmp(argv[3], "reset") == 0)
	{
		if (OK != calibReset(dev, CAL_CH_SOL_V1 + (ch - 1)))
		{
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[3]);
	if (OK != calibSet(dev, CAL_CH_SOL_V1 + (ch - 1), value))
	{
		return ERR;
	}
	return OK;
}

const CliCmdType CMD_PANEL_CRT_READ =
{
	"pcrd",
	1,
	&doPanelCrtRead,
	"  pcrd             Read panel short circuit current(mA)\n",
	"  Usage:           "PROGRAM_NAME" pcrd <ch>\n",
	"  Example:         "PROGRAM_NAME" pcrd <ch>\n",
};
int doPanelCrtRead(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = atoi(argv[2]);
	if (! (1 <= ch && ch <= PANEL_CH_NO))
	{
		printf("Invalid panel channel[1.."STR(PANEL_CH_NO)"]!\n");
		return ARG_RANGE_ERR;
	}
	u16 val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_PANEL_CRT1 + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to read panel short circuit current!\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%0.3f\n", val * MV_TO_V);
	return OK;
}

const CliCmdType CMD_FAN_PWR_READ =
{
	"fanrd",
	1,
	&doFanPwrRead,
	"  fanrd            Read fan power\n",
	"  Usage:           "PROGRAM_NAME" fanrd\n",
	"  Example:         "PROGRAM_NAME" fanrd\n",
};
int doFanPwrRead(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = 1;
	u8 val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_FAN_PWR + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to read fan power!\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%d\n", val);
	return OK;
}

const CliCmdType CMD_FAN_PWR_WRITE =
{
	"fanwr",
	1,
	&doFanPwrWrite,
	"  fanwr            Set fan power\n",
	"  Usage:           "PROGRAM_NAME" fanwr <value(%)>\n",
	"  Example:         "PROGRAM_NAME" fanwr 75\n",
};
int doFanPwrWrite(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = 1;
	u8 val = (u8)atoi(argv[2]);
	if (! (val <= 100))
	{
		printf("Value out of range[0..100]!\n");
		return ARG_CNT_ERR;
	}
	u8 buf[sizeof (val)];
	memcpy(buf, &val, sizeof (val));
	if (OK
		!= i2cMem8Write(dev, I2C_MEM_FAN_PWR + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to set fan power!\n");
		return ERR;
	}
	return OK;
}

const CliCmdType CMD_PRESSURE_READ =
{
	"presrd",
	1,
	&doPressureRead,
	"  presrd           Read internal sensor pressure(milibars)\n",
	"  Usage:           "PROGRAM_NAME" pressrd\n",
	"  Example:         "PROGRAM_NAME" pressrd\n",
};
int doPressureRead(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = 1;
	float val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_INT_PRESSURE + (ch - 1) * sizeof (val), buf,
			sizeof (val)))
	{
		printf("Fail to read internal pressure!\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%f Pa\n", val);
	return OK;
}

const CliCmdType CMD_TEMP_READ =
{
	"temprd",
	1,
	&doTempRead,
	"  temprd           Read internal internal temperature(degree Celsius)\n",
	"  Usage:           "PROGRAM_NAME" temprd\n",
	"  Example:         "PROGRAM_NAME" temprd\n",
};
int doTempRead(int argc, char *argv[])
{
	(void)argv;
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERR;
	}
	int ch = 1;
	float val;
	u8 buf[sizeof (val)];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_INT_TEMPERATURE + (ch - 1) * sizeof (val),
			buf, sizeof (val)))
	{
		printf("Fail to read internal temperature!\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof (val));
	printf("%f C\n", val);
	return OK;
}
