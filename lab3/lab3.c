#include <stdint.h>
#include <stdio.h>

int main()
{
    uint32_t testnumber;
    uint32_t masked_number, page, offset;

    uint32_t initial_mask = 0xffff;
    printf("0b%d\n", initial_mask);

    uint32_t page_mask = 0xff00;
    printf("0b%d\n", page_mask);

    uint32_t offset_mask = 0x00ff;
    printf("0b%d\n", offset_mask);

    

    scanf("%d", &testnumber);

    masked_number = testnumber & initial_mask;
    page = masked_number & page_mask;
    page = page >> 8;
    offset = masked_number & offset_mask;

    printf("the page number is %d \n", page);
    printf("the offset number is %d \n", offset);
}