#ifndef UAV_UAV_H
#define UAV_UAV_H

#define UAV_PKG_CONFIG          0xf0  //for setting package baudrates
//The reason for having different codes for arm and motor is that
  //we can control them independently and at different rates
#define UAV_DEV_MOTORS         0x10
#define UAV_DEV_IMU            0x20
#define UAV_DEV_RANGER         0x30
#define UAV_DEV_LED            0x40
#define UAV_DEV_MAG            0x50
#define UAV_DEV_ARM            0x60
#define UAV_DEV_ENC            0x70


#define UAV_CMD_SYS            0x00
#define UAV_CMD_ON             0x01
#define UAV_CMD_OFF            0x02
#define UAV_CMD_READ           0x03
#define UAV_CMD_WRITE          0x04
#define UAV_CMD_RESET          0x05
#define UAV_CMD_SLEEP          0x06
#define UAV_CMD_CALIB          0x07
#define UAV_CMD_TEST           0x08


//----------------------UAV STATUS MESSAGES only sent by UAV not by Ground Control Station--------//

#define UAV_DEBUG_MSG         0x04
#define UAV_HEARTBEAT          0x05

#define BUF_LEN 60


#endif
