#include<stdio.h>

unsigned short calculate_checksum()
{
    printf("Enter the IP header in 16 bit word : ");

    unsigned fields[10];
    int sum = 0;

    for(int i = 0; i < 10; i++)
    {
        scanf("%x", &fields[i]);
        sum = sum + (unsigned short) fields[i];

        while(sum >> 16)
            sum = (sum & 0xFFFF) + (sum >> 16);
    }

    sum = ~sum;

    return (unsigned short)sum;
}


int main()
{
    //--------------------------------------------------------------------------------
    //  > Sender side
    //--------------------------------------------------------------------------------
        unsigned short result1 = calculate_checksum();

        printf("Checksum at sender side = %x\n", result1);
    //--------------------------------------------------------------------------------
    //  > Receiver side
    //--------------------------------------------------------------------------------
        unsigned short result2 = calculate_checksum();

        printf("Checksum at receiver side = %x\n", result2);
    //--------------------------------------------------------------------------------
    //  > Errror detection
    //--------------------------------------------------------------------------------
        if(result2 == 0x0000)
            printf("No error\n");
        else
            printf("Error in packet received\n");
    //--------------------------------------------------------------------------------
}
