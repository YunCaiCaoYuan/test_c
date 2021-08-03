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

unsigned long int Reflect(unsigned long int ref, char ch)
{
    unsigned long int value=0;
    // 交换bit0和bit7，bit1和bit6，类推
    for(int i = 1; i < (ch + 1); i++)
    {
      if(ref & 1)
        value |= 1 << (ch - i);
      ref >>= 1;
    }
    return value;
}

void calc_crc32() {
    // 注意：因生成项POLY最高位一定为“1”，故略去最高位的"1"，
    unsigned long cnCRC_32 = 0x04C11DB7; //采用正规的CRC32的POLY
    unsigned long Table_CRC32[256];     // CRC32 表

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

    unsigned char aData[512]={0x31,0x32,0x33,0x34};      //待测数据，为字串"1234"
    unsigned long aSize;
    unsigned long i;
    unsigned char *point;
    unsigned char chtemp;
    // 计算 32 位 CRC-32 值
    //Table-Driven驱动表法，需要用到“直接查询表”（不能用“正规查询表”）；待测数据需扩展0
    unsigned long ii;
    unsigned long CRC32_1;
    aSize=4;       //数据长度字节（不包含扩展0）
    CRC32_1=0x0;      //寄存器归0
    point=aData;
    ii=0;
    while (aSize--)
    {
      chtemp=*point++;
      chtemp=(unsigned char)Reflect(chtemp, 8);   //将数据字节内部的比特进行颠倒
      CRC32_1 = ((CRC32_1 << 8) | chtemp) ^ Table_CRC32[(CRC32_1 >> 24) & 0xFF];
      ii++;
      if (ii==4)
        CRC32_1=CRC32_1^0xffffffff; //当寄存器装满4个字节后，用预置值0xffffffff去XOR寄存器，这样寄存器就被这个值初始化了！
    }

    for (i = 0; i < 4; i++)
    {
      CRC32_1 = ((CRC32_1 << 8)) ^ Table_CRC32[(CRC32_1 >> 24) & 0xFF];  //加入4字节的扩展0
      ii++;
      if (ii==4)
        CRC32_1=CRC32_1^0xffffffff;//如果待测数据小于4字节，则只有在这里寄存器才会装满4个字节，才进行初始化
    }
    CRC32_1=Reflect(CRC32_1, 32);  //颠倒寄存器的值
    CRC32_1=CRC32_1^0xffffffff;   //寄存器的值与0xffffffff异或
    //这时， CRC32_1中的值就是CRC
    print_bin(CRC32_1);

    //DIRECT TABLE直驱表法，需要用到“直接查询表”（不能用“正规查询表”）；待测数据不需要扩展0
    unsigned long CRC32_2;
    aSize=4;       //数据长度字节（数据不用扩展0了）
    CRC32_2 = 0xffffffff;      //寄存器中直接预置初始值0xffffffff即可
    point=aData;
    for (i = 0; i < aSize; i++)
    {
      chtemp=*point++;
      chtemp=(unsigned char)Reflect(chtemp, 8);   //将数据字节内部的比特进行颠倒
      CRC32_2 = (CRC32_2 << 8) ^ Table_CRC32[(CRC32_2 >> 24) ^ chtemp];
    }

    CRC32_2=Reflect(CRC32_2, 32);  //颠倒寄存器的值
    CRC32_2=CRC32_2^0xffffffff;     //寄存器的值与0xffffffff异或
    //这时， CRC32_2中的值就是CRC
    print_bin(CRC32_2);
}

int main() {
    calc_crc32();
}
