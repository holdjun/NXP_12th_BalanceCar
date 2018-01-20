#include "data_sent.h"
#include "uart.h"
#include "camera.h"
#include "extern.h"
//#include "ini_flash.h"

Data_Type DATA_ALL;

Data_Type *Sent_Data=(Data_Type *)&DATA_ALL;



void Set_DataToCon(void)
{
	
    uint8_t *Data_Con=Sent_Data->Data_Con;  

    #if(DataNum>=1)
    {
        *(float *)Data_Con=DefaultParValue1;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=2)
    {
        *(float *)Data_Con=DefaultParValue2;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=3)
    {
        *(float *)Data_Con=DefaultParValue3;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=4)
    {
        *(float *)Data_Con=DefaultParValue4;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=5)
    {
        *(float *)Data_Con=DefaultParValue5;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=6)
    {
        *(float *)Data_Con=DefaultParValue6;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=7)
    {
        *(float *)Data_Con=DefaultParValue7;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=8)
    {
        *(float *)Data_Con=DefaultParValue8;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=9)
    {
        *(float *)Data_Con=DefaultParValue9;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=10)
    {
        *(float *)Data_Con=DefaultParValue10;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=11)
    {
        *(float *)Data_Con=DefaultParValue11;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=12)
    {
        *(float *)Data_Con=DefaultParValue12;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=13)
    {
        *(float *)Data_Con=DefaultParValue13;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=14)
    {
        *(float *)Data_Con=DefaultParValue14;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=15)
    {
        *(float *)Data_Con=DefaultParValue15;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=16)
    {
        *(float *)Data_Con=DefaultParValue16;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=17)
    {
        *(float *)Data_Con=DefaultParValue17;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=18)
    {
        *(float *)Data_Con=DefaultParValue18;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=19)
    {
        *(float *)Data_Con=DefaultParValue19;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=20)
    {
        *(float *)Data_Con=DefaultParValue20;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=21)
    {
        *(float *)Data_Con=DefaultParValue21;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=22)
    {
        *(float *)Data_Con=DefaultParValue22;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=23)
    {
        *(float *)Data_Con=DefaultParValue23;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=24)
    {
        *(float *)Data_Con=DefaultParValue24;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=25)
    {
        *(float *)Data_Con=DefaultParValue25;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=26)
    {
        *(float *)Data_Con=DefaultParValue26;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=27)
    {
        *(float *)Data_Con=DefaultParValue27;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=28)
    {
        *(float *)Data_Con=DefaultParValue28;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=29)
    {
        *(float *)Data_Con=DefaultParValue29;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=30)
    {
        *(float *)Data_Con=DefaultParValue30;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=31)
    {
        *(float *)Data_Con=DefaultParValue31;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=32)
    {
        *(float *)Data_Con=DefaultParValue32;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=33)
    {
        *(float *)Data_Con=DefaultParValue33;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=34)
    {
        *(float *)Data_Con=DefaultParValue34;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=35)
    {
        *(float *)Data_Con=DefaultParValue35;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=36)
    {
        *(float *)Data_Con=DefaultParValue36;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=37)
    {
        *(float *)Data_Con=DefaultParValue37;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=38)
    {
        *(float *)Data_Con=DefaultParValue38;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=39)
    {
        *(float *)Data_Con=DefaultParValue39;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=40)
    {
        *(float *)Data_Con=DefaultParValue40;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=41)
    {
        *(float *)Data_Con=DefaultParValue41;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=42)
    {
        *(float *)Data_Con=DefaultParValue42;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=43)
    {
        *(float *)Data_Con=DefaultParValue43;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=44)
    {
        *(float *)Data_Con=DefaultParValue44;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=45)
    {
        *(float *)Data_Con=DefaultParValue45;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=46)
    {
        *(float *)Data_Con=DefaultParValue46;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=47)
    {
        *(float *)Data_Con=DefaultParValue47;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=48)
    {
        *(float *)Data_Con=DefaultParValue48;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=49)
    {
        *(float *)Data_Con=DefaultParValue49;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=50)
    {
        *(float *)Data_Con=DefaultParValue50;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=51)
    {
        *(float *)Data_Con=DefaultParValue51;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=52)
    {
        *(float *)Data_Con=DefaultParValue52;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=53)
    {
        *(float *)Data_Con=DefaultParValue53;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=54)
    {
        *(float *)Data_Con=DefaultParValue54;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=55)
    {
        *(float *)Data_Con=DefaultParValue55;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=56)
    {
        *(float *)Data_Con=DefaultParValue56;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=57)
    {
        *(float *)Data_Con=DefaultParValue57;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=58)
    {
        *(float *)Data_Con=DefaultParValue58;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=59)
    {
        *(float *)Data_Con=DefaultParValue59;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=60)
    {
        *(float *)Data_Con=DefaultParValue60;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=61)
    {
        *(float *)Data_Con=DefaultParValue61;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=62)
    {
        *(float *)Data_Con=DefaultParValue62;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=63)
    {
        *(float *)Data_Con=DefaultParValue63;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=64)
    {
        *(float *)Data_Con=DefaultParValue64;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=65)
    {
        *(float *)Data_Con=DefaultParValue65;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=66)
    {
        *(float *)Data_Con=DefaultParValue66;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=67)
    {
        *(float *)Data_Con=DefaultParValue67;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=68)
    {
        *(float *)Data_Con=DefaultParValue68;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=69)
    {
        *(float *)Data_Con=DefaultParValue69;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=70)
    {
        *(float *)Data_Con=DefaultParValue70;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=71)
    {
        *(float *)Data_Con=DefaultParValue71;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=72)
    {
        *(float *)Data_Con=DefaultParValue72;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=73)
    {
        *(float *)Data_Con=DefaultParValue73;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=74)
    {
        *(float *)Data_Con=DefaultParValue74;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=75)
    {
        *(float *)Data_Con=DefaultParValue75;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=76)
    {
        *(float *)Data_Con=DefaultParValue76;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=77)
    {
        *(float *)Data_Con=DefaultParValue77;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=78)
    {
        *(float *)Data_Con=DefaultParValue78;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=79)
    {
        *(float *)Data_Con=DefaultParValue79;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=80)
    {
        *(float *)Data_Con=DefaultParValue80;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=81)
    {
        *(float *)Data_Con=DefaultParValue81;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=82)
    {
        *(float *)Data_Con=DefaultParValue82;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=83)
    {
        *(float *)Data_Con=DefaultParValue83;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=84)
    {
        *(float *)Data_Con=DefaultParValue84;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=85)
    {
        *(float *)Data_Con=DefaultParValue85;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=86)
    {
        *(float *)Data_Con=DefaultParValue86;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=87)
    {
        *(float *)Data_Con=DefaultParValue87;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=88)
    {
        *(float *)Data_Con=DefaultParValue88;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=89)
    {
        *(float *)Data_Con=DefaultParValue89;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=90)
    {
        *(float *)Data_Con=DefaultParValue90;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=91)
    {
        *(float *)Data_Con=DefaultParValue91;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=92)
    {
        *(float *)Data_Con=DefaultParValue92;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=93)
    {
        *(float *)Data_Con=DefaultParValue93;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=94)
    {
        *(float *)Data_Con=DefaultParValue94;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=95)
    {
        *(float *)Data_Con=DefaultParValue95;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=96)
    {
        *(float *)Data_Con=DefaultParValue96;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=97)
    {
        *(float *)Data_Con=DefaultParValue97;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=98)
    {
        *(float *)Data_Con=DefaultParValue98;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=99)
    {
        *(float *)Data_Con=DefaultParValue99;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=100)
    {
        *(float *)Data_Con=DefaultParValue100;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=101)
    {
        *(float *)Data_Con=DefaultParValue101;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=102)
    {
        *(float *)Data_Con=DefaultParValue102;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=103)
    {
        *(float *)Data_Con=DefaultParValue103;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=104)
    {
        *(float *)Data_Con=DefaultParValue104;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=105)
    {
        *(float *)Data_Con=DefaultParValue105;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=106)
    {
        *(float *)Data_Con=DefaultParValue106;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=107)
    {
        *(float *)Data_Con=DefaultParValue107;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=108)
    {
        *(float *)Data_Con=DefaultParValue108;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=109)
    {
        *(float *)Data_Con=DefaultParValue109;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=110)
    {
        *(float *)Data_Con=DefaultParValue110;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=111)
    {
        *(float *)Data_Con=DefaultParValue111;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=112)
    {
        *(float *)Data_Con=DefaultParValue112;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=113)
    {
        *(float *)Data_Con=DefaultParValue113;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=114)
    {
        *(float *)Data_Con=DefaultParValue114;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=115)
    {
        *(float *)Data_Con=DefaultParValue115;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=116)
    {
        *(float *)Data_Con=DefaultParValue116;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=117)
    {
        *(float *)Data_Con=DefaultParValue117;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=118)
    {
        *(float *)Data_Con=DefaultParValue118;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=119)
    {
        *(float *)Data_Con=DefaultParValue119;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=120)
    {
        *(float *)Data_Con=DefaultParValue120;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=121)
    {
        *(float *)Data_Con=DefaultParValue121;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=122)
    {
        *(float *)Data_Con=DefaultParValue122;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=123)
    {
        *(float *)Data_Con=DefaultParValue123;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=124)
    {
        *(float *)Data_Con=DefaultParValue124;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=125)
    {
        *(float *)Data_Con=DefaultParValue125;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=126)
    {
        *(float *)Data_Con=DefaultParValue126;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=127)
    {
        *(float *)Data_Con=DefaultParValue127;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=128)
    {
        *(float *)Data_Con=DefaultParValue128;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=129)
    {
        *(float *)Data_Con=DefaultParValue129;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=130)
    {
        *(float *)Data_Con=DefaultParValue130;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=131)
    {
        *(float *)Data_Con=DefaultParValue131;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=132)
    {
        *(float *)Data_Con=DefaultParValue132;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=133)
    {
        *(float *)Data_Con=DefaultParValue133;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=134)
    {
        *(float *)Data_Con=DefaultParValue134;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=135)
    {
        *(float *)Data_Con=DefaultParValue135;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=136)
    {
        *(float *)Data_Con=DefaultParValue136;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=137)
    {
        *(float *)Data_Con=DefaultParValue137;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=138)
    {
        *(float *)Data_Con=DefaultParValue138;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=139)
    {
        *(float *)Data_Con=DefaultParValue139;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=140)
    {
        *(float *)Data_Con=DefaultParValue140;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=141)
    {
        *(float *)Data_Con=DefaultParValue141;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=142)
    {
        *(float *)Data_Con=DefaultParValue142;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=143)
    {
        *(float *)Data_Con=DefaultParValue143;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=144)
    {
        *(float *)Data_Con=DefaultParValue144;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=145)
    {
        *(float *)Data_Con=DefaultParValue145;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=146)
    {
        *(float *)Data_Con=DefaultParValue146;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=147)
    {
        *(float *)Data_Con=DefaultParValue147;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=148)
    {
        *(float *)Data_Con=DefaultParValue148;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=149)
    {
        *(float *)Data_Con=DefaultParValue149;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=150)
    {
        *(float *)Data_Con=DefaultParValue150;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=151)
    {
        *(float *)Data_Con=DefaultParValue151;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=152)
    {
        *(float *)Data_Con=DefaultParValue152;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=153)
    {
        *(float *)Data_Con=DefaultParValue153;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=154)
    {
        *(float *)Data_Con=DefaultParValue154;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=155)
    {
        *(float *)Data_Con=DefaultParValue155;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=156)
    {
        *(float *)Data_Con=DefaultParValue156;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=157)
    {
        *(float *)Data_Con=DefaultParValue157;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=158)
    {
        *(float *)Data_Con=DefaultParValue158;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=159)
    {
        *(float *)Data_Con=DefaultParValue159;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=160)
    {
        *(float *)Data_Con=DefaultParValue160;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=161)
    {
        *(float *)Data_Con=DefaultParValue161;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=162)
    {
        *(float *)Data_Con=DefaultParValue162;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=163)
    {
        *(float *)Data_Con=DefaultParValue163;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=164)
    {
        *(float *)Data_Con=DefaultParValue164;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=165)
    {
        *(float *)Data_Con=DefaultParValue165;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=166)
    {
        *(float *)Data_Con=DefaultParValue166;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=167)
    {
        *(float *)Data_Con=DefaultParValue167;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=168)
    {
        *(float *)Data_Con=DefaultParValue168;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=169)
    {
        *(float *)Data_Con=DefaultParValue169;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=170)
    {
        *(float *)Data_Con=DefaultParValue170;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=171)
    {
        *(float *)Data_Con=DefaultParValue171;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=172)
    {
        *(float *)Data_Con=DefaultParValue172;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=173)
    {
        *(float *)Data_Con=DefaultParValue173;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=174)
    {
        *(float *)Data_Con=DefaultParValue174;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=175)
    {
        *(float *)Data_Con=DefaultParValue175;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=176)
    {
        *(float *)Data_Con=DefaultParValue176;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=177)
    {
        *(float *)Data_Con=DefaultParValue177;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=178)
    {
        *(float *)Data_Con=DefaultParValue178;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=179)
    {
        *(float *)Data_Con=DefaultParValue179;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=180)
    {
        *(float *)Data_Con=DefaultParValue180;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=181)
    {
        *(float *)Data_Con=DefaultParValue181;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=182)
    {
        *(float *)Data_Con=DefaultParValue182;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=183)
    {
        *(float *)Data_Con=DefaultParValue183;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=184)
    {
        *(float *)Data_Con=DefaultParValue184;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=185)
    {
        *(float *)Data_Con=DefaultParValue185;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=186)
    {
        *(float *)Data_Con=DefaultParValue186;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=187)
    {
        *(float *)Data_Con=DefaultParValue187;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=188)
    {
        *(float *)Data_Con=DefaultParValue188;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=189)
    {
        *(float *)Data_Con=DefaultParValue189;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=190)
    {
        *(float *)Data_Con=DefaultParValue190;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=191)
    {
        *(float *)Data_Con=DefaultParValue191;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=192)
    {
        *(float *)Data_Con=DefaultParValue192;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=193)
    {
        *(float *)Data_Con=DefaultParValue193;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=194)
    {
        *(float *)Data_Con=DefaultParValue194;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=195)
    {
        *(float *)Data_Con=DefaultParValue195;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=196)
    {
        *(float *)Data_Con=DefaultParValue196;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=197)
    {
        *(float *)Data_Con=DefaultParValue197;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=198)
    {
        *(float *)Data_Con=DefaultParValue198;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=199)
    {
        *(float *)Data_Con=DefaultParValue199;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=200)
    {
        *(float *)Data_Con=DefaultParValue200;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=201)
    {
        *(float *)Data_Con=DefaultParValue201;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=202)
    {
        *(float *)Data_Con=DefaultParValue202;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=203)
    {
        *(float *)Data_Con=DefaultParValue203;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=204)
    {
        *(float *)Data_Con=DefaultParValue204;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=205)
    {
        *(float *)Data_Con=DefaultParValue205;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=206)
    {
        *(float *)Data_Con=DefaultParValue206;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=207)
    {
        *(float *)Data_Con=DefaultParValue207;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=208)
    {
        *(float *)Data_Con=DefaultParValue208;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=209)
    {
        *(float *)Data_Con=DefaultParValue209;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=210)
    {
        *(float *)Data_Con=DefaultParValue210;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=211)
    {
        *(float *)Data_Con=DefaultParValue211;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=212)
    {
        *(float *)Data_Con=DefaultParValue212;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=213)
    {
        *(float *)Data_Con=DefaultParValue213;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=214)
    {
        *(float *)Data_Con=DefaultParValue214;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=215)
    {
        *(float *)Data_Con=DefaultParValue215;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=216)
    {
        *(float *)Data_Con=DefaultParValue216;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=217)
    {
        *(float *)Data_Con=DefaultParValue217;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=218)
    {
        *(float *)Data_Con=DefaultParValue218;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=219)
    {
        *(float *)Data_Con=DefaultParValue219;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=220)
    {
        *(float *)Data_Con=DefaultParValue220;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=221)
    {
        *(float *)Data_Con=DefaultParValue221;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=222)
    {
        *(float *)Data_Con=DefaultParValue222;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=223)
    {
        *(float *)Data_Con=DefaultParValue223;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=224)
    {
        *(float *)Data_Con=DefaultParValue224;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=225)
    {
        *(float *)Data_Con=DefaultParValue225;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=226)
    {
        *(float *)Data_Con=DefaultParValue226;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=227)
    {
        *(float *)Data_Con=DefaultParValue227;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=228)
    {
        *(float *)Data_Con=DefaultParValue228;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=229)
    {
        *(float *)Data_Con=DefaultParValue229;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=230)
    {
        *(float *)Data_Con=DefaultParValue230;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=231)
    {
        *(float *)Data_Con=DefaultParValue231;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=232)
    {
        *(float *)Data_Con=DefaultParValue232;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=233)
    {
        *(float *)Data_Con=DefaultParValue233;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=234)
    {
        *(float *)Data_Con=DefaultParValue234;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=235)
    {
        *(float *)Data_Con=DefaultParValue235;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=236)
    {
        *(float *)Data_Con=DefaultParValue236;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=237)
    {
        *(float *)Data_Con=DefaultParValue237;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=238)
    {
        *(float *)Data_Con=DefaultParValue238;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=239)
    {
        *(float *)Data_Con=DefaultParValue239;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=240)
    {
        *(float *)Data_Con=DefaultParValue240;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=241)
    {
        *(float *)Data_Con=DefaultParValue241;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=242)
    {
        *(float *)Data_Con=DefaultParValue242;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=243)
    {
        *(float *)Data_Con=DefaultParValue243;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=244)
    {
        *(float *)Data_Con=DefaultParValue244;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=245)
    {
        *(float *)Data_Con=DefaultParValue245;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=246)
    {
        *(float *)Data_Con=DefaultParValue246;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=247)
    {
        *(float *)Data_Con=DefaultParValue247;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=248)
    {
        *(float *)Data_Con=DefaultParValue248;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=249)
    {
        *(float *)Data_Con=DefaultParValue249;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=250)
    {
        *(float *)Data_Con=DefaultParValue250;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=251)
    {
        *(float *)Data_Con=DefaultParValue251;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=252)
    {
        *(float *)Data_Con=DefaultParValue252;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=253)
    {
        *(float *)Data_Con=DefaultParValue253;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=254)
    {
        *(float *)Data_Con=DefaultParValue254;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=255)
    {
        *(float *)Data_Con=DefaultParValue255;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif
    #if(DataNum>=256)
    {
        *(float *)Data_Con=DefaultParValue256;
        *(uint32_t *)(Data_Con + 4) = ~*(uint32_t *)Data_Con;
        Data_Con+=8;
    }
    #endif


 


}

void Compressed_Data(void)//8位数据压缩成一位数据
{
		uint8_t *P;
    uint8_t H,W;
    uint8_t *Data_Pixels=Sent_Data->Pixels;  
    union//定义一个公用体
    {	
        uint8_t  Byte;
        struct Byte8_Struct Byte_Bit;
    } BIT;
    P=*Pixels;//将指针指向当前需要处理的行
    for(H=0;H<Image_Height;H++)
    {
        for(W=0;W<(Image_Width>>3);W++)
        {
            BIT.Byte_Bit.bit8=*P++;
            BIT.Byte_Bit.bit7=*P++;
            BIT.Byte_Bit.bit6=*P++;
            BIT.Byte_Bit.bit5=*P++;
            BIT.Byte_Bit.bit4=*P++;
            BIT.Byte_Bit.bit3=*P++;
            BIT.Byte_Bit.bit2=*P++;
            BIT.Byte_Bit.bit1=*P++; 
            *Data_Pixels++=BIT.Byte;
        }
    }
}




void UART_Send_Con(void)
{
    #if(Send_Mode==PicBazMODE)//暂时不发
    {

		Set_DataToCon();

       // SetFlashDataToCon();

        Compressed_Data();
        //初始化基本参数
        Sent_Data->Verific[0]=1;
        
        Sent_Data->Verific[1]=2;

        Sent_Data->Verific[2]=3;
        
        Sent_Data->Verific[3]=4;

        Sent_Data->Verific[4]=5;  

        Sent_Data->Pixels_width=Image_Width;
        
        Sent_Data->Pixels_height=Image_Height;

        Sent_Data->Coefficient_Num=DataNum;

        Sent_Data->Parameter_Num=Par_Num;

        while(DMA_IsComplete(DMA_UART_CHx) == FALSE);//判断DMA UART是否发送完毕

        Set_Uart_DMA_DAddr((uint32_t)Sent_Data);//设置DMA UART发送源地址
        
        Set_Uart_DMA_Enable(ENABLE);//开始发送

    }
    #endif
    #if(Send_Mode==ParMODE)
    {

        Set_DataToCon();

        SetFlashDataToCon();
        //初始化基本参数
        Sent_Data->Verific[0]=1;
        
        Sent_Data->Verific[1]=2;

        Sent_Data->Verific[2]=3;
        
        Sent_Data->Verific[3]=4;

        Sent_Data->Verific[4]=5;  

        Sent_Data->Pixels_width=Image_Width;
        
        Sent_Data->Pixels_height=Image_Height;

        Sent_Data->Parameter_Num=Par_Num;

        Sent_Data->Coefficient_Num=DataNum;

        while(DMA_IsComplete(DMA_UART_CHx) == FALSE);//判断DMA UART是否发送完毕

        Set_Uart_DMA_DAddr((uint32_t)Sent_Data);//设置DMA UART发送源地址
        
        Set_Uart_DMA_Enable(ENABLE);//开始发送


    }
    #endif
}


void Data_Uart_Init(void)
{
    DMA_InitTypeDef DMA_InitStruct1;
    UART_DebugPortInit(UART5_RX_E9_TX_E8,DMAUART_BANDRATE);
    
    UART_ITConfig(UART5,UART_IT_TDRE,ENABLE);
    
    UART_DMACmd(UART5,UART_DMAReq_Tx,ENABLE);
    
  DMA_InitStruct1.Channelx = DMA_UART_CHx;                         //使用DMA0通道  (0-15)
	DMA_InitStruct1.DMAAutoClose = ENABLE;                      //传输完毕后自动关闭
	DMA_InitStruct1.EnableState = ENABLE;                       //初始化后不立即开始传输
	DMA_InitStruct1.MinorLoopLength = Data_All_Length;   //传输次数
	DMA_InitStruct1.PeripheralDMAReq  = UARTx_TRAN_DMAREQ;      //UART 传输完成触发
	DMA_InitStruct1.TransferBytes = 1;                          //每次传输一个字节
	//配置目的地址传输参数
	DMA_InitStruct1.DestBaseAddr = (uint32_t)DMA_UART_TX_DB;       //指向目的地址
	DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;                //数组为1Byte
	DMA_InitStruct1.DestMajorInc = 0;                           //执行一次大循环后 地址不增加
	DMA_InitStruct1.DestMinorInc = 0;                           //每次传输完地址不增加
 
	//配置源地址传输参数
	DMA_InitStruct1.SourceBaseAddr =  (uint32_t)DMA_UART_TX_SB;
	DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct1.SourceMajorInc = 0;
	DMA_InitStruct1.SourceMinorInc = 1;
	DMA_Init(&DMA_InitStruct1); 
    //DMA_ITConfig(DMA0,DMA_IT_MAJOR,DMA_CH5,ENABLE);不启动DMA5中断服务函数
    //NVIC_EnableIRQ(DMA5_IRQn);
}
void  DMA_Uart_ClearITPendingBit(void)//清除UART DMA中断标记
{
   DMA0->INT |= (1 << DMA_UART_CHx);
}


void Set_Uart_DMA_Enable(FunctionalState DMA_ON_OFF)//开启或关闭uartDMA
{
		    if(DMA_ON_OFF == ENABLE)
			{  
				DMA0->ERQ |= (1<<DMA_UART_CHx);
			}
			else
			{
				DMA0->ERQ &= ~(1<<DMA_UART_CHx);
			}
}

void Set_Uart_DMA_DAddr(uint32_t DMA_Addr)//修改DMA目的地址
{
    DMA0->TCD[DMA_UART_CHx].SADDR = DMA_Addr;
}


