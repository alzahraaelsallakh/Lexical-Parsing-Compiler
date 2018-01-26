
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int scanner(char scan[],char check)
{
    int i=0;
    while (scan[i]!= NULL)
    {
        if (scan[i]== check)
            return 1;
        i++;
    }
}



int lexical (FILE *x)
{
    FILE *source_code;
    source_code=x;
    char ch;
    char word[15],op[10];
    char keywords[15][10] = {"if", "else", "int", "char", "break","for","case", "while", "do","void","switch","float","return","main","long"};
    char digits []={"0123456789"};
    char letters []={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char operators [2][5] = {"+","*"};
    char symbols [] = {",;(){}"};
    char end_of_word_list[]={' ',',','\n','\t','+','/','!','=','<','>',';','(',')','{','}'};
    int valid_character=0,flag,letter_found=0,end_of_word=0,word_process=0,i=0,invalid=0;

    if (source_code == NULL)
    {
        printf("Error opening file");
        exit(0);
    }
    else
    {
        printf("*Lexical Phase*\n\n");
        while((ch = fgetc(source_code)) != EOF)
        {
            valid_character=0;
            if (scanner(letters,ch)==1)
            {
                word[word_process]= ch;
                word_process++;
                letter_found=1; //to declare constants
                valid_character=1;

            }


            if (scanner(digits,ch)==1)
            {
                word[word_process]= ch;
                word_process++;
                valid_character=1;
            }



            if (scanner(end_of_word_list,ch)==1 && word_process !=0)
                end_of_word=1;
            if((end_of_word==1)) //end of word
            {       word[word_process]= '\0';
                    word_process=0;
                    end_of_word=0;
                    if(letter_found==0)
                    {
                        printf("%s is a constant \n",word);
                        valid_character=1;
                    }

                    else
                    {
                        for (i=0;i<15;i++)
                        {
                                if (strcmp(keywords[i],word)==0)
                                {
                                    flag=1;
                                    break;
                                }
                        }



                        if (flag==1)
                        {
                            printf("%s is a keyword \n",word);
                            flag=0;
                            valid_character=1;
                        }
                        else //identifier
                        {
                            if (scanner(digits,word[0])==1)
                                {
                                    printf("%s is an invalid identifier \n",word);
                                    valid_character=1;
                                }
                            else
                            {
                                printf("%s is an identifier \n",word);
                                valid_character=1;
                            }
                        }
                        letter_found=0;
                    }

            }

            op[0]=ch;
            op[1]='\0';
            for (i=0;i<7;i++)
            {
                if (strcmp(operators[i],op)==0)
                {
                    printf("%s is an operator \n",op);
                    valid_character=1;
                }
            }


            if (scanner(symbols,ch)==1)
            {
                printf("%c is a symbol \n",ch);
                valid_character=1;
            }

            if (valid_character==0 && ch!= '\n' && ch!= '\t' && ch != ' ')
                printf("%c is an invalid character \n", ch);
            }

        }

}



int main(void)

{
    FILE *source_code;
    source_code= fopen("lexical prog.txt", "r");
    lexical(source_code);
    fclose(source_code);

    return 0;
}
