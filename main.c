#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

/************************************
FND  - (c) Nikita Donskov 2021.
This program hides message
in file , using number of whitespace,
with binary code.
There's also a function to
read hidden message.
*************************************/

#define MAXSTR  255 /* Max characters num in str */
#define BYTE    8   /* Bits in byte constant */

/* to_binary: converts (x) into binary code.
   Returns bit with number (bit_num)       */
int to_binary (char x, int bit_num){
    return (x << bit_num & 128);
}

/* un_binary: converts (s) - sring with
   binary code, to number.                 */
int un_binary (char *s){
    int i = 0, sum = 0, p;
    p = strlen(s) - 1;
    for (; p >= 0; p--)
        sum += ((s[i++] == '1') ? 1 : 0) * pow(2, p);
    return sum;
}

/* next: returns value to write.
   Return [1] - if it is time to write probel
   Return [0] - ignnore it.                 */
int next (char *txt){
    static int letter = 0, digit = 0;
    if (digit == BYTE){
        digit = 0;
        ++letter;
    }
    ++digit;
    return (letter < strlen(txt)) ? to_binary(txt[letter], digit) : 0;
}

main (int argc, char *argv[]){
    int i, ws, flength;
    FILE *f = fopen(argv[1], "r");

    if (argc != 2){
        printf("usage: FND [file]");
        return 1;
    } else if (f == NULL){
        printf("error: can't open '%s'", argv[1]);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    flength = ftell(f);
    rewind(f);
    i = ws = 0;

    char *text = (char*)malloc(flength * sizeof(char));
    
    if (text == NULL) {
        printf("error: no such memory.");
        return 1;
    }

    while(!feof(f))
        if((text[i++] = fgetc(f)) == ' ')
            ++ws;
    text[--i] = '\0';

    char ch, *message = (char*)malloc(ws / 8 * sizeof(char));

    printf("\nFND - (c) Nikita Donskov 2021.\n[read] - 'r'\n[write] - 'w'\n> ");
    scanf("\n%c", &ch);

    if (ch == 'w' || ch == 'W'){
        printf("\n[warning] can write no more than %d characters\n> ", ws / 8);
        scanf("\n%s", message);

        fclose(f);
        f = fopen(argv[1], "w");
        i = -1;
        while (text[++i] != '\0'){
            fprintf(f, "%c", text[i]);
            if(text[i] == ' ' && next(message))
                fprintf(f, " ");
        }
        fclose(f);
        printf("\nwriting message \"%s\" completed successfully.", message);
    } else if (ch == 'r' || ch == 'R'){
        char prom[MAXSTR];
        int j = 0;
        printf("\nmessage: ");
        for(i = 0; text[i] != '\0'; i++){
            if (text[i] == ' '){
                if(text[i + 1] == ' ')
                    prom[j++] = '1';
                else
                    prom[j++] = '0';
                ++i;

                if (j % BYTE == 0){
                    prom[j - 1] = '\0';
                    printf("%c", (char)un_binary(prom));
                    strcpy(prom, "");
                    j = 0;
                }
            }
        }
    } else printf("error: unknown command: '%c'.", ch);
    free(text);
    free(message);
    return 0;
}