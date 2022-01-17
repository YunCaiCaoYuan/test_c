#include<stdio.h>

#define BYTE char

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
    unsigned long int crc32_table[256];
    unsigned long int ulPolynomial = 0x04c11db7;
    unsigned long int crc,temp;

    for(int i = 0; i <= 0xFF; i++)   // 生成CRC32“正规查询表”
    {
      temp=Reflect(i, 8);
      crc32_table[i]= temp<< 24;
      for (int j = 0; j < 8; j++)
      {
        unsigned long int t1,t2;
        unsigned long int flag=crc32_table[i]&0x80000000;
        t1=(crc32_table[i] << 1);
        if(flag==0)
          t2=0;
        else
          t2=ulPolynomial;
        crc32_table[i] =t1^t2 ;
      }
      crc=crc32_table[i];
      crc32_table[i] = Reflect(crc32_table[i], 32);
    }


    //计算CRC32值
    unsigned   long   CRC32;
    BYTE  DataBuf[512]={0x31,0x32,0x33,0x34};   //待测数据，为字串"1234"
    unsigned   long   len;
    unsigned   long   ii;
    unsigned   long   m_CRC = 0xFFFFFFFF;   //寄存器中预置初始值
    BYTE   *p;

    len=4;             //待测数据的字节长度
    p = DataBuf;
    for(ii=0;  ii <len;  ii++)
    {
      m_CRC = crc32_table[( m_CRC^(*(p+ii)) ) & 0xff] ^ (m_CRC >> 8);  //计算
    }
    CRC32= ~m_CRC;     //取反。经WINRAR对比，CRC32值正确！！
    //这时， CRC32中的值就是CRC
    print_bin(CRC32);
}

int main() {
    calc_crc32();
}
