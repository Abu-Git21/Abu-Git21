#include <stdio.h>
#include <ctype.h>

/*
 * Level 3 - String Inspector
 *
 * Complete the four functions below.
 * The newline read by fgets() should not be counted.
 */

int countVowels(const char text[]);
int countDigits(const char text[]);
int countSpaces(const char text[]);
void printReverse(const char text[]);

int main(void)
{
    char text[200];

    printf("Enter text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        return 1;
    }

    printf("Vowels: %d\n", countVowels(text));
    printf("Digits: %d\n", countDigits(text));
    printf("Spaces: %d\n", countSpaces(text));
    printf("Reverse: ");
    printReverse(text);
    printf("\n");

    return 0;
}

int countVowels(const char text[])
{
    int vowels_count = 0;

    for(int i = 0; text[i] != '\0' && text[i] != '\n'; i++)
    {
        if(text[i] == 'a' ||  text[i] == 'e'||  text[i] == 'i' ||  
        text[i] == 'o' ||  text[i] == 'u')
        {
            vowels_count++;
        }
        else if(text[i] == 'A' ||  text[i] == 'E'||  text[i] == 'I' ||  
        text[i] == 'O' ||  text[i] == 'U')
        {
            vowels_count++;
        }
    }
    return vowels_count;
}

int countDigits(const char text[])
{
    int digits_count= 0;

    for(int i = 0; text[i] != '\0' && text[i] != '\n'; i++)
    {
        if(text[i] >= '0' && text[i] <= '9')
        digits_count++;
    }

    return digits_count;
}

int countSpaces(const char text[])
{
    int space_count = 0;
    for(int i = 0; text[i] != '\0' && text[i] != '\n'; i++)
    {
        if(text[i] == ' ')
        {
            space_count++;        
        }
    }
    return space_count;
}

void printReverse(const char text[])
{
    int length = 0;

    for(int i = 0; text[i] != '\0' && text[i] != '\n'; i++)
    {
        length += 1;
    }
    for(int i = length - 1; i >= 0;i--)
    {
        printf("%c",text[i]);
    }

}
