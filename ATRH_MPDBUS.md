# Mdbus addresses for ATRH Sensor

## Modbus object types
All Modbus RTU object types with standard addresses are implemented: Coils, Discrete Inputs, Input registers, Holding registers.

### Coils

Access level Read/Write, Size 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |

### Discrete Inputs

Access level Read Only, Size 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |


### Input registers

Access level Read Only, Size 16 bits

| Device function | Register Address | Description | Measurement Unit |
| --- | --- | --- | --- |
| IR_PRESSURE_HI | 30001 | Measured pressure High part | kPa |
| IR_PRESSURE_LO | 30002 |  Measured pressure High part | kPa |
| IR_TEMPERATURE1_HI | 30003 | Pressure sensor temperarure High | degC |
| IR_TEMPERATURE1_LO | 30004 | Pressure sensor temperarure Low | degC |
| IR_HUMIDITY_HI | 30005 | Humidity High | % |
| IR_HUMIDITY_LO | 30006 | Humidity Low | % |
| IR_TEMPERATURE2_HI | 30007 | Humidity sensor temperature Hi | degC |
| IR_TEMPERATURE2_LO | 30008 | Humidity sensor temperature Low | degC |
| IR_DENSITY_HI | 30009 | Density High | kg/m^3 |
| IR_DENSITY_LO | 30010 | Density LOW | kg/m^3  |
| IR_FW_VERSION | 30011 | Firmware version  |  |

### Holding registers

Access level Read/Write, Size 16 bits

| Device function | Register Address | Modbus Address | Description | Range |
| --- | --- | --- | --- | --- |
| HR_BAUDRATE | 40001 | 0x01 | Modbus RS485 Baudrate /100 | 12..9216 |
| HR_ADDRESS | 40002 | 0x02 | Modbus device address | 1..255 |
| HR_PARITY | 40003 | 0x03 | RS485 parity | 0- none; 1 - even; 2 - odd |



## Function codes implemented

* Read Coils (0x01)
* Read Discrete Inputs (0x02)
* Read Holding Registers (0x03)
* Read Input Registers (0x04)
* Write Single Coil (0x05)
* Write Single Register (0x06)
* Write Multiple Coils (0x0f)
* Write Multiple registers (0x10)
