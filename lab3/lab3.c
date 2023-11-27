#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    char input[10];

    file = fopen("addresses.txt", "r");

    uint32_t input_number;
    uint32_t masked_number, offset, page;
    uint32_t initial_mask = 0xffff;
    uint32_t offset_mask = 0xff00;
    uint32_t page_mask = 0x00ff;
    int page_table[256];

    // scanf("%d", &input_number);

    while (fgets(input, 10, file) != NULL)
    {
        input_number = atoi(input);

        masked_number = input_number & initial_mask;
        offset = masked_number & offset_mask;
        offset = offset >> 8;
        page = masked_number & page_mask;


        printf("the page number is %d ", page);
        printf("the offset number is %d \n", offset);
    }

    fclose(file);
    return 0;
}