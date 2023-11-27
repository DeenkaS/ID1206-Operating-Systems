#include <stdint.h>
#include <stdio.h>

int main()
{
    uint32_t input_number;
    uint32_t masked_number, offset, page;
    uint32_t initial_mask = 0xffff;
    uint32_t offset_mask = 0xff00;
    uint32_t page_mask = 0x00ff;

    scanf("%d", &input_number);

    masked_number = input_number & initial_mask;
    offset = masked_number & offset_mask;
    offset = offset >> 8;
    page = masked_number & page_mask;

    printf("the offset number is %d \n", offset);
    printf("the page number is %d \n", page);
}