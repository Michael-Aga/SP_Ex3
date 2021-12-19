#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TXT 1024
#define WORD 30

char txt[TXT];
char word[WORD];

//Get the word from the user
void getWord()
{
    char stop_condition = 0;
    scanf("%c", &stop_condition);
    int i;
    for (i = 0; stop_condition != ' ' && stop_condition != '\t' && stop_condition != '\n' && i < WORD ; i++)
    {
        word[i] = stop_condition;
        scanf("%c", &stop_condition);
    }
    word[i] = '\0';
}

//Get the text from the user
void getTxt()
{
    char stop_condition = 0;
    scanf("%c", &stop_condition);
    int i;
    for (i = 0; stop_condition != '~' && i < TXT ; i++)
    {
        txt[i] = stop_condition;
        scanf("%c", &stop_condition);
    }
    txt[i] = '\0';
}

//Helping function to convert a word to its gematria value
int convert_word_to_gematria()
{
    int converted_word = 0;
    int i = 0;

    while (word[i] != '\0')
    {
        if (word[i] >= 'a' && word[i] <= 'z') converted_word += word[i] - 'a' + 1;
        
        else if (word[i] >= 'A' && word[i] <= 'Z') converted_word += word[i] - 'A' + 1;

        ++i;
    }
    return converted_word;
}

//Prints all minimum sequences in text with the same gematria value as the value of the received word.
void gematriaSequences()
{
    int converted_word = convert_word_to_gematria();
    int printed = 0;
    int i = 0;

    printf("Gematria Sequences: ");
    
    while (txt[i] != '\0')
    {
        int sum = 0;
        int j = i;
        if ((txt[i] >= 'a' && txt[i] <= 'z') || (txt[i] >= 'A' && txt[i] <= 'Z'))
        {
            while (txt[j] != '\0' && sum < converted_word)
            {
                if (txt[j] >= 'a' && txt[j] <= 'z') sum += txt[j] - 'a' + 1;
                
                else if (txt[j] >= 'A' && txt[j] <= 'Z') sum += txt[j] - 'A' + 1;

                ++j;
            }
            --j;
            if (sum == converted_word)
            {
                if (printed) printf("~");
                
                for (int k = i; k <= j; k++){
                    printf("%c", txt[k]);
                }

                printed++;
            }
        }
        ++i;
    }
}

//Helping function that coneverts to atbash
char *convert_to_atbash()
{
    int i = 0;
    char *atbash_word = (char *)malloc(sizeof(char) * WORD);

    while (word[i] != '\0' || i <= WORD)
    {
        if (word[i] >= 'a' && word[i] <= 'm') atbash_word[i] = 'z' - word[i] + 'a';

        else if (word[i] >= 'A' && word[i] <= 'M') atbash_word[i] = 'Z' - word[i] + 'A';

        else if (word[i] >= 'n' && word[i] <= 'z') atbash_word[i] = 'a' - word[i] + 'z';

        else if (word[i] >= 'N' && word[i] <= 'Z') atbash_word[i] = 'A' - word[i] + 'Z';

        else atbash_word[i] = word[i];

        ++i;
    }
    atbash_word[i] = '\0';
    return atbash_word;
}

//Helping function that reverses the atbash word
char *reverse(char *atbash_word)
{
    char *reversed_atbash_word = (char *)malloc(sizeof(char) * WORD);
    int atbash_len = strlen(atbash_word);

    for (int i = 0; i < atbash_len; i++)
    {
        reversed_atbash_word[i] = atbash_word[atbash_len - i - 1];
    }

    reversed_atbash_word[atbash_len] = '\0';
    return reversed_atbash_word;
}

//Prints all the minimum sequences in the text so that ignoring blank characters are the same as the word or the opposite in atbash writing
void atbashSequences()
{
    char *atbash_word = convert_to_atbash();
    char *reverse_atbash = reverse(atbash_word);
    int printed = 0;
    int i = 0;

    printf("Atbash Sequences: ");
    
    while (txt[i] != '\0')
    {
        if (txt[i] == atbash_word[0])
        {
            int flag = 0;
            int j = i;
            int a = 0;

            while (txt[j] != '\0' && atbash_word[a] != '\0' && a >= 0)
            {
                if ((txt[j] >= 'a' && txt[j] <= 'z') || (txt[j] >= 'A' && txt[j] <= 'Z'))
                {
                    if (txt[j] == atbash_word[a])
                    {
                        a++;
                        if (atbash_word[a] == '\0')
                        {
                            flag = 1;
                            a = -1;
                        }
                    }
                    else a = -1;
                }
                j++;
            }
            j--;

            if (flag)
            {
                if (printed) printf("~");

                for (int a = i; a <= j; a++)
                {
                    printf("%c", txt[a]);
                }
                printed++;
            }
        }
        else if (txt[i] == reverse_atbash[0])
        {
            int flag = 0;
            int j = i;
            int a = 0;

            while (txt[j] != '\0' && reverse_atbash[a] != '\0' && a >= 0)
            {
                if ((txt[j] >= 'a' && txt[j] <= 'z') || (txt[j] >= 'A' && txt[j] <= 'Z'))
                {
                    if (txt[j] == reverse_atbash[a])
                    {
                        a++;
                        if (reverse_atbash[a] == '\0')
                        {
                            flag = 1;
                            a = -1;
                        }
                    }
                    else a = -1;
                }
                ++j;
            }
            --j;
            if (flag)
            {
                if (printed) printf("~");
                
                for (int a = i; a <= j; a++)
                {
                    printf("%c", txt[a]);
                }
                ++printed;
            }
        }
        ++i;
    }
    free(atbash_word);
    free(reverse_atbash);
}

//Prints all minimum sequences in the text consisting of the characters of the received word and empty characters only .
void anagramSequences()
{
    int printed = 0;
    int i = 0;
    printf("Anagram Sequences: ");

    while (txt[i] != '\0')
    {
        if (txt[i] != ' ' && txt[i] != '\t' && txt[i] != '\n')
        {
            char copy[WORD];
            strcpy(copy, word);
            int flag = 0;
            int j = i;

            while (txt[j] != '\0' && flag == 0)
            {
                if (txt[j] != ' ' && txt[j] != '\t' && txt[j] != '\n')
                {
                    flag = -1;

                    for (int a = 0; copy[a] != '\0' && flag <= -1; a++)
                    {
                        if (txt[j] == copy[a])
                        {
                            copy[a] *= -1;
                            flag = 0;
                        }
                    }

                    if (flag == 0)
                    {
                        flag = 1;

                        for (int a = 0; copy[a] != '\0' && flag == 1; a++)
                        {
                            if (copy[a] > 0)
                            {
                                flag = 0;
                            }
                        }
                    }
                }
                j++;
            }

            j--;

            if (flag == 1)
            {
                if (printed) printf("~");

                for (int a = i; a <= j; a++)
                {
                    printf("%c", txt[a]);
                }

                printed++;
            }
        }
        i++;
    }
}

int main()
{
    getWord();
    getTxt();
    gematriaSequences();
    printf("\n");
    atbashSequences();
    printf("\n");
    anagramSequences();
}
