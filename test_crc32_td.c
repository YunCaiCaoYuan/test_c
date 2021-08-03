#include<stdio.h>

void print_bin(int n)
{
    int l = sizeof(n)*8;//总位数。
    int i;
    for(i = l-1; i >= 0; i--)//略去高位0.
    {
        if(n & (1<<i))
            break;
    }

    for(; i>=0; i--)
        printf("%d", (n & (1<<i)) != 0);
    printf("\n");
}

void table_driven() {
    // 注意：因生成项POLY最高位一定为“1”，故略去最高位的"1"，
    unsigned short cnCRC_16 = 0x8005;    // CRC-16 = X16 + X15 + X2 + X0
    unsigned short cnCRC_CCITT = 0x1021; // CRC-CCITT = X16 + X12 + X5 + X0，据说这个 16 位 CRC 多项式比上一个要好
    unsigned long cnCRC_32 = 0x04C11DB7; //采用正规的CRC32的POLY
    unsigned long Table_CRC16[256];     // CRC16 表
    unsigned long Table_CRC32[256];     // CRC32 表


    // 构造 16 位 CRC 表 "直接查询表"
    unsigned short i16, j16;
    unsigned short nData16;
    unsigned short nAccum16;
    for (i16 = 0; i16 < 256; i16++)
    {
      nData16 = (unsigned short)(i16 << 8);
      nAccum16 = 0;
      for (j16 = 0; j16 < 8; j16++)
      {
        if ((nData16 ^ nAccum16) & 0x8000)
            nAccum16 = (nAccum16 << 1) ^ cnCRC_16;   //也可以用cnCRC_CCITT
        else
            nAccum16 <<= 1;
        nData16 <<= 1;
      }
      Table_CRC16[i16] = (unsigned long)nAccum16;
    }

    // 构造 32 位 CRC 表 "直接查询表"
    unsigned long i32, j32;
    unsigned long nData32;
    unsigned long nAccum32;
    for (i32 = 0; i32 < 256; i32++)
    {
      nData32 = (unsigned long)(i32 << 24);
      nAccum32 = 0;
      for (j32 = 0; j32 < 8; j32++)
      {
        if ((nData32 ^ nAccum32) & 0x80000000)
          nAccum32 = (nAccum32 << 1) ^ cnCRC_32;
        else
          nAccum32 <<= 1;
        nData32 <<= 1;
      }
      Table_CRC32[i32] = nAccum32;
    }

    //打印查询表的语句：（在TC中实现）
    /*
    for ( i16 = 0; i16 < 256; i16++ )
    {
        printf("%02xh    %04x  %04x  %04x  %04x\n",i16,(unsigned short)Table_CRC16[i16],(unsigned short)Table_CRC16[i16+1],(unsigned short)Table_CRC16[i16+2],(unsigned short)Table_CRC16[i16+3]);
        i16++;
        i16++;
        i16++;
    }

    for ( i16 = 0; i16 < 256; i16++ )
    {
        printf("%02xh    %08lx  %08lx  %08lx %08lx\n",i16,Table_CRC32[i16],Table_CRC32[i16+1],Table_CRC32[i16+2],Table_CRC32[i16+3]);
        i16++;
        i16++;
        i16++;
    }
    */

    unsigned char aData[512]={0x31,0x32,0x33,0x34};      //待测数据，为字串"1234"
    unsigned long aSize;
    unsigned long i;
    unsigned char *point;

    // 计算 16 位 CRC 值，CRC-16 或 CRC-CCITT
    //Table-Driven驱动表法，需要用到“直接查询表”（不能用“正规查询表”）；待测数据需扩展0
    unsigned short CRC16_1;
    aSize=4;       //数据长度字节（不包含扩展0）
    CRC16_1 = 0;      //寄存器归0
    point=aData;
    while (aSize--)
      CRC16_1 = ((CRC16_1 << 8) | *point++) ^ Table_CRC16[(CRC16_1 >> 8) & 0xFF];
    for ( i = 0; i < 2; i++ )
      CRC16_1 = ((CRC16_1 << 8) ) ^ Table_CRC16[(CRC16_1 >> 8) & 0xFF];  //加入2字节的扩展0
    //这时， CRC16_1中的值就是CRC
    print_bin(CRC16_1);

    // 计算 32 位 CRC-32 值
    //Table-Driven驱动表法，需要用到“直接查询表”（不能用“正规查询表”）；待测数据需扩展0
    unsigned long CRC32_1;
    aSize=4;       //数据长度字节（不包含扩展0）
    CRC32_1=0x0;      //寄存器归0
    point=aData;
    while (aSize--)
      CRC32_1 = ((CRC32_1 << 8) | *point++) ^ Table_CRC32[(CRC32_1 >> 24) & 0xFF];
    for (i = 0; i < 4; i++)
        CRC32_1 = ((CRC32_1 << 8)) ^ Table_CRC32[(CRC32_1 >> 24) & 0xFF];//加入4字节的扩展0
    //这时， CRC32_1中的值就是CRC
    print_bin(CRC32_1);

    // 计算 16 位 CRC 值，CRC-16 或 CRC-CCITT
    //DIRECT TABLE直驱表法，需要用到“直接查询表”（不能用“正规查询表”）；待测数据不需要扩展0
    unsigned short CRC16_2;
    aSize=4;       //数据长度字节（数据不用扩展0了）
    CRC16_2 = 0;      //寄存器中预置初始值
    point=aData;
    for (i = 0; i < aSize; i++)
      CRC16_2 = (CRC16_2 << 8) ^ (unsigned short) Table_CRC16[(CRC16_2 >> 8) ^ *point++];
    //这时， CRC16_2中的值就是CRC
    print_bin(CRC16_2);

    // 计算 32 位 CRC-32 值
    //DIRECT TABLE直驱表法，需要用到“直接查询表”（不能用“正规查询表”）；待测数据不需要扩展0
    unsigned long CRC32_2;
    aSize=4;       //数据长度字节（数据不用扩展0了）
    CRC32_2 = 0x0;    //寄存器中预置初始值
    point=aData;
    for (i = 0; i < aSize; i++)
      CRC32_2 = (CRC32_2 << 8) ^ Table_CRC32[(CRC32_2 >> 24) ^ *point++];
    //这时， CRC32_2中的值就是CRC
    print_bin(CRC32_2);
}

int main() {
    printf("sizeof(int)=%d\n", sizeof(int));
    table_driven();
}
