#ifndef __ISR_H__
#define __ISR_H__

#include "sys.h"
#include "gpio.h"
#include "uart.h"
#include "rtc.h"
#include "dma.h"
#include "tsi.h"
#include "pit.h"
#include "pdb.h"
#include "i2c.h"
#include "spi.h"
#include "lptm.h"
#include "can.h"
#include "sd.h"
#endif /* __ISR_H__ */

//        void ImageProcess()//ÕºœÒ––¥¶¿Ì
//        {
//            byte j, i;
//            Lcr[RowNum].LBlack = 0;

//            Lcr[RowNum].Center = 0;

//            Lcr[RowNum].RBlack = 0;
//           for (i = 0; i < 70; i++)
//            {
//                if (i == 0)
//                {
//                    for (j = Mid; j < 200; j++)
//                    {
//                        if (P_Pixels[0, j] == 0)
//                            break;
//                    }
//                    if (j == 200)
//                        Lcr[0].LBlack = 199;
//                    else
//                        Lcr[0].LBlack = j;
//                    for (j = Mid; j > 0; j--)
//                    {
//                        if (P_Pixels[0, j - 1] == 0)
//                            break;
//                    }
//                    if (j == 0)
//                        Lcr[0].RBlack = 0;
//                    else
//                        Lcr[0].RBlack = (byte)(j - 1);
//                }
//                else if (P_Pixels[i, Lcr[i - 1].Center] > 0)
//                {
//                    for (j = Lcr[i - 1].Center; j < 200; j++)
//                    {
//                        if (P_Pixels[i, j] == 0)
//                            break;
//                    }
//                    if (j == 200)
//                        Lcr[i].LBlack = 199;
//                    else
//                        Lcr[i].LBlack = j;
//                    for (j = Lcr[i - 1].Center; j > 0; j--)
//                    {
//                        if (P_Pixels[i, j - 1] == 0)
//                            break;
//                    }
//                    if (j == 0)
//                        Lcr[i].RBlack = 0;
//                    else
//                        Lcr[i].RBlack = (byte)(j - 1);

//                }
//                else
//                    break;
//                Lcr[i].Center = (byte)((Lcr[i].LBlack + Lcr[i].RBlack)>>1);
//                if(i==2)
//                    Mid = Lcr[i].Center;

//            }
