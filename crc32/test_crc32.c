#include<stdio.h>

#define BYTE char
#define _int64 long long

void print_bin(int n)
{
    int l = sizeof(n)*8;//总位数。
    int i;
//    if(i == 0)
//    {
//         printf("0");
//         return;
//     }
    for(i = l-1; i >= 0; i--)//略去高位0.
    {
        if(n & (1<<i))
            break;
    }

    for(; i>=0; i--)
        printf("%d", (n & (1<<i)) != 0);
    printf("\n");
}

void calc_crc32() {
    BYTE POLY=0x13;          //生成项，13H＝10011，这样CRC是4比特
    unsigned short data = 0x035B;  //待测数据是35BH，12比特，注意，数据不是16比特
    unsigned short regi = 0x0000;  // load the register with zero bits

    // augment the data by appending W(4) zero bits to the end of it.
    //按CRC计算的定义，待测数据后加入4个比特0，以容纳4比特的CRC；
    //这样共有16比特待测数据，从第5比特开始做除法，就要做16－5＋1＝12次XOR
    data <<= 4;

    // we do it bit after bit
    for (int cur_bit = 15; cur_bit >= 0; -- cur_bit)   //处理16次，前4次实际上只是加载数据
    {
        // test the highest bit which will be poped later.
        ///     in fact, the 5th bit from right is the hightest bit here
        if (((regi >> 4) & 0x0001) == 0x1)
            regi = regi ^ POLY;

        regi <<= 1;   // shift the register
        // reading the next bit of the augmented data
        unsigned short tmp = (data >> cur_bit) & 0x0001;  //加载待测数据1比特到tmp中，tmp只有1比特
        regi |= tmp;    //这1比特加载到寄存器中
    }
    if (((regi >> 4) & 0x0001) == 0x1)
        regi = regi ^ POLY;    //做最后一次XOR

    print_bin(regi);
}

void common_calc_crc32() {
    _int64  POLY = 0x104C11DB7;   //生成项，需要含有最高位的"1"，这样CRC是32比特
    int crcbitnumber=32;      //crc是32比特

    _int64  data = 0x31323334;      //待测数据，为字串"1234"
    int  databitnumber=32;     //数据是32比特

    _int64  regi = 0x0;        // load the register with zero bits

    // augment the data by appending W zero bits to the end of it.
    //按CRC计算的定义，加入32个比特0，以容纳32比特的CRC；
    //这样共有64比特待测数据，从第33比特开始做除法，就要做64－33＋1＝32次XOR
    data <<= crcbitnumber;

    // we do it bit after bit
    for (int cur_bit = databitnumber+crcbitnumber-1; cur_bit >= 0; -- cur_bit)   //处理64次（32比特待测数据＋32比特扩展0），前32次是加载数据
    {
        // test the highest bit which will be poped later.
        ///     in fact, the 5th bit from right is the hightest bit here
        if (((regi >> crcbitnumber) & 0x0001) == 0x1)
            regi = regi ^ POLY;

        regi <<= 1;   // shift the register
        // reading the next bit of the augmented data
        unsigned short tmp = (data >> cur_bit) & 0x0001;    //加载待测数据1比特到tmp中，tmp只有1比特
        regi |= tmp;    //这1比特加载到寄存器中
    }
    if (((regi >> crcbitnumber) & 0x0001) == 0x1)
        regi = regi ^ POLY;   //做最后一次XOR
    //这时， regi中的值就是CRC
    print_bin(regi);
}

int main() {
    calc_crc32();
    common_calc_crc32();
}

