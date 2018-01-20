#ifndef _IMU_IIC_H_
#define _IMU_IIC_H_

#include "sys.h"

#define SCL            PCout(10)
#define SDA_OUT        PCout(11)
#define SDA_IN         PCin(11)

#define IIC_SCL_PIN    (10)
#define IIC_SCL_PORT   PTC
 
#define IIC_SDA_PIN    (11)
#define IIC_SDA_PORT   PTC
#define IIC_SDA_PORTx  PORTC

void IIC_start(void);
void IIC_stop(void);
void IIC_ack_main(uint8_t ack_main);
void send_byte(uint8_t c);
uint8_t read_byte(void);
void send_to_byte(uint8_t ad_main,uint8_t c);
void send_to_nbyte(uint8_t ad_main,uint8_t ad_sub,uint8_t *buf,uint8_t num);
void read_from_byte(uint8_t ad_main,uint8_t *buf);
void read_from_nbyte(uint8_t ad_main,uint8_t ad_sub,uint8_t *buf,uint8_t num);
void IMU_IIC_Init();


#endif