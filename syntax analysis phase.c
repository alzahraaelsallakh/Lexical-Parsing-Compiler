
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

char S_prod_rules [1][2][10]={"int","T"};
char T_prod_rules [2][3][10]={{"*","int","T"},
                              {"+","int","T"}};
int S_prod_length=2,T_prod_length=3; //second dimension of S ant T
char *input[100];
int input_ptr=0;
char* save[100];
char*rule [100];
int save_ptr,rule_ptr=0;

int save_pos()
{   int i =0;
    save_ptr = rule_ptr;
    while (rule[rule_ptr]!= NULL)
    {
        save[i]=rule[rule_ptr];
        i++;
        rule_ptr++;
    }
    return 0;
}

int trackback ()
{   int i=0;
    rule_ptr = save_ptr;
    i=0;
    while (save[i]!= NULL)
    {
        rule[rule_ptr]=save[i];
        i++;
    }

    return 0;
}

int production (char production[][3][10],int i,int no_of_rules)
{
    int j=0;
    i=i-1;
    while(j<no_of_rules)
    {
        rule[rule_ptr+j]=production[i][j];
        j++;
    }
    return 0;
}


int syntax (FILE *x)
{
    FILE *source_code;
    source_code=x;
    char ch;
    char word[15],op[10];
    char keywords[15][10] = {"if", "else", "int", "char", "break","for","case", "while", "do","void","switch","float","return","main","long"};
    char letters []={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char digits []={"0123456789"};
    char operators [2][5] = {"+","*"};
    char end_of_word_list[]={' ',',','\n','\t','+','/','!','=','<','>',';','(',')','{','}'};
    int valid_character=0,flag,letter_found=0,end_of_word=0,word_process=0,i=0,invalid=0;

    if (source_code == NULL)
    {
        printf("Error opening file");
        exit(0);
    }
    else
    {
        printf("*Parsing Phase*\n\nThe Input is: ");
        while((ch = fgetc(source_code)) != EOF)
        {
            valid_character=0;
            if (scanner(letters,ch)==1)
            {
                word[word_process]= ch;
                word_process++;

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
                    printf("%s ",word);

                    for (i=0;i<15;i++)
                    {
                            if (strcmp(keywords[i],word)==0)
                            {
                                input[input_ptr]=word;
                                input_ptr++;
                                break;
                            }
                    }

            }

            op[0]=ch;
            op[1]='\0';
            for (i=0;i<7;i++)
            {
                if (strcmp(operators[i],op)==0)
                {
                    printf("%s ",op);

                    if (strcmp(op,"*")==0)
                            input[input_ptr]="Multiply";
                    if (strcmp(op,"+")==0)
                            input[input_ptr]="Plus";
                    input_ptr++;
                }
            }

            }

          //Tokens are ready
        }

        //PARSING PHASE

        /*
            The Grammar:
                S >> int T
                T >> * int T | + int T | epsilon
        */



        for (i=0;i<input_ptr;i++)
        {
         if (strcmp(input[i],"Multiply")==0)
            input[i]="*";
         if (strcmp(input[i],"Plus")==0)
            input[i]="+";
        }
        printf(" >>> ");

    input[input_ptr]='\0';
    int rule_index=1;
    input_ptr=0;

     rule[rule_ptr]="S";//start non-terminal

     while (input[input_ptr]!='\0' && invalid==0)
     {

            if (strcmp(input[input_ptr],rule[rule_ptr])==0)
            {
                input_ptr++;
                rule_ptr++;

            }


           else if (strcmp(rule[rule_ptr],"S")==0)
            {
                production(S_prod_rules,rule_index,S_prod_length);
            }



            else if ((strcmp(rule[rule_ptr],"T")==0))
            {

                save_pos();
                if (rule_index==1)
                {
                    production(T_prod_rules,rule_index,T_prod_length);

                }
                else if (rule_index==2)
                {
                    production(T_prod_rules,rule_index,T_prod_length);
                    rule_index = 1;//if another T is coming so the default is rule_index = 1 to put the "*"
                }




            }
            //Track back
            else if ((strcmp(rule[rule_ptr],"*")==0) && rule_index==1)
            {
                rule_index=2;
                trackback();
            }

            else
            {
                printf(" Invalid Syntax\n");
                invalid=1;
            }


        }

        if (invalid==0 && strcmp(rule[rule_ptr],"T")==0 && rule[rule_ptr+1]=='\0')
        {
            printf(" Valid Syntax\n");

        }

}



int main(void)

{
    FILE *source_code;
    source_code= fopen("syntax prog.txt", "r");
    syntax(source_code);
    fclose(source_code);

    return 0;
}
