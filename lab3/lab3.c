#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;             //deklarerar bara filen. 
    char input[10];         //char array för siffrorna i adresses.txt

    file = fopen("addresses.txt", "r"); //fil "adresses.txt" öppnad i "r" read mode

    uint32_t input_number;                  //32 bitars int för input
    uint32_t masked_number, page, offset;   //3 stycken 32 bitars int
    uint32_t initial_mask = 0xffff;         //Mask för att få den 16 bitarna till höger
    uint32_t page_mask = 0xff00;          //Mask för att få den 8 vänstar bitarna
    uint32_t offset_mask = 0x00ff;            //Mask för att få den 8 högra bitarna
    int page_table[256];                    //offset table används inte ännu (itn array)

    // scanf("%d", &input_number);

    while (fgets(input, 10, file) != NULL)  //while det finns rader i "file" så läser vi in i "input" med längd "10" 
    {
        input_number = atoi(input);     //atoi konverterar string till int.

        masked_number = input_number & initial_mask; //första masken så ingen smuts hänger med. egentligen onödig
        page = masked_number & page_mask;        //bitwise OR (& inte &&) för page  
        page = page >> 8;                        //pushar bitarna så vi får 0x00FF istället för 0xFF00. 
        offset = masked_number & offset_mask;            //bitwise OR för offset nummer


        printf("the page number is %d", page);   //print decimalt page
        printf("the offset number is %d \n", offset);        //print decimalt pagenumret
    }

    fclose(file);
    return 0;
}