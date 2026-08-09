#include <stdio.h>

//Abubakar Imran
//July 6th 2026

int main(void)
{
    printf("======================================\n");
    printf("\tENGINEER TRADING CARD\n");
    printf("======================================\n");
    printf("| NAME: %-27s  |\n" , "Abubakar Imran");           //Similar here with other programs but uses strings.
    printf("| DATE: %-27s  |\n" , "July 6th 2026");            // the %-# is used for a string to be placed in there with that set about of characters
    printf("| MAJOR: %-27s |\n" , "Computer Engineering");
    printf("| FACT: %-27s  |\n" , "I like swimming.");         // the "\" is used for putting actual / they need to quotes to be there to actually print.
    printf("| SUPERPOWER: %-22s |\n" , "\"Superspeed\"");           // The /t and /n are for tabs and new lines
    printf("======================================\n");

    
    return 0;
}
