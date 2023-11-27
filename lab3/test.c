#include <stdint.h>
#include <stdio.h>

int main()
{
    uint32_t input_number;
    uint32_t masked_number, page, offset;
    uint32_t initial_mask = 0xffff;
    uint32_t page_mask = 0xff00;
    uint32_t offset_mask = 0x00ff;

    scanf("%d", &input_number);

    masked_number = input_number & initial_mask;
    page = masked_number & page_mask;
    page = page >> 8;
    offset = masked_number & offset_mask;

    printf("the page number is %d \n", page);
    printf("the offset number is %d \n", offset);
}