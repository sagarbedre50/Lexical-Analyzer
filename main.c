#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include"lexical_analyzer.h"

int parenthesis=0,curly_bracket=0,data_type=0,d_count=0;
int k_count=0;

void check_error(void)
{
  if(k_count>0)
  {
    printf("\033[31mERROR : LINE TERMINATOR NOT FOUND\033[0m\n");
    k_count--;
  }
  else if(k_count<0)
  {
    printf("\033[31mERROR : SYNTAX ERROR\033[0m\n");
    k_count++;
  }

  if(parenthesis!=0)
  {
    printf("\033[31mERROR :  INVALID PARANTHESIS !\033[0m\n");
    parenthesis=0;
  }
}

void print_output(char const problem[],char const answer[])  //To print output on console
{
    static int count=1;
    printf("| %-10d | %-23s | %-23s |\n",count,problem,answer);
    count++;
}

int check_keyword(char str[])    //To check keywords
{
    int count=0;
    static int ffound=0;
    char key_words[32][10] = {"auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","int","long","register","return","short",    
    "signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    
    for ( int i = 0; i < 32; i++)
    {
        if(strcmp(key_words[i],str)==0)
        {
            if(strcmp(key_words[i],"if")!=0 && strcmp(key_words[i],"else")!=0 && strcmp(key_words[i],"for")!=0
             && strcmp(key_words[i],"do")!=0 && strcmp(key_words[i],"if")!=0 && strcmp(key_words[i],"while")!=0 )
            {
                if(strcmp(key_words[i],"int")==0 && ffound!=0)
                {
                    k_count++;
                    ffound++;
                }
                else if(strcmp(key_words[i],"int")==0)
                {
                    ffound++;
                }
                else if(k_count!=1)
                {
                    k_count++;
                }
                if(strcmp(key_words[i],"int")==0 || strcmp(key_words[i],"float")==0)
                {
                    data_type=1;
                }
                else{
                    data_type=0;
                }
            }
            print_output(str,"KEYWORD");
            count++;
        }
    }
    if(count==0)
    {
        if(strcmp(str,"main")!=0 && k_count!=1)
        k_count++;
       print_output(str,"IDENTIFIER");
    }
}
int line = 1;
int read_char(FILE *fp)   
{
    int ch = fgetc(fp);

    if (ch == '\n')
    {
        check_error();
        line++;
    }
    return ch;
}
int main()
{
    FILE *fp;
    fp=fopen("sample.txt","r");
    if(fp==NULL)
    {
        perror("ERROR :");
        return -1;
    }
    int ch;
    char str[100];
    char  directives[200];
    char alfa[100];
    char symoperator[10];
    char digit[100];
    char character[10];
        int count=0;
    printf("        +----------------------------------------+\n");
    printf("        |          Lexical analyzer output       |\n");
    printf("        +----------------------------------------+\n\n");
    printf("+----------------------------------------------------------------+\n");
    printf("| %-10s | %-23s | %-23s |\n","Sr.No","Value","Type");
    printf("+----------------------------------------------------------------+\n");
    int line=0;
    int privious=0;
    while ((ch=read_char(fp))!=EOF)
    { 
         if(ch=='#')
         {
            int found=0;
            char libraries[20][30] = {"#include<stdio.h>","#include<stdlib.h>","#include<string.h>","#include<ctype.h>",
                                      "#include<math.h>","#include<time.h>","#include<stdbool.h>","#include<stdint.h>",
                                      "#include<stddef.h>","#include<limits.h>","#include<float.h>","#include<errno.h>",
                                      "#include<assert.h>","#include<signal.h>","#include<setjmp.h>","#include<stdarg.h>",
                                      "#include<locale.h>","#include<wchar.h>","#include<wctype.h>","#include<inttypes.h>"};
            count=0;
            directives[count]='#';
            count++;
            while ((ch=read_char(fp))!='\n'){
              directives[count]=ch;
              count++; 
            }
            directives[count-1]='\0';
            count=0;
            for (int i = 0; i < 20; i++)
            {
                if(strcmp(libraries[i],directives)==0)
                {
                    print_output(libraries[i],"PREPROCESSOR");
                    found++;
                    break;
                }
            }
            if(found==0)
            printf("\033[31mERROR : INVALID PREPROCESSOR  \033[0m\n");
         }
         else if(ch=='"')
         {
              str[count]='"';
                count++;
            while ((ch=read_char(fp))!='"')
            {
               str[count]=ch;
               count++; 
            }
            if(k_count!=1)
            k_count++;
            str[count]='"';
            count++;
            str[count]='\0';
            count=0;
            
            print_output(str,"STRING"); 
        }
        else if(isalpha(ch))
        {
            alfa[count]=ch;
            count++;
            while (isalpha(ch=read_char(fp)))
            {
                alfa[count]=ch;
                count++;
            }
            alfa[count]='\0';
            check_keyword(alfa);
            char in_variable[20];
            count=0;
            if(data_type==1)
            {
               if(isdigit(fgetc(fp)))
               {
                  fseek(fp,-1,SEEK_CUR);
                  while ((ch=read_char(fp))!=';')
                  {
                    in_variable[count]=ch;
                    count++;
                  }
                  in_variable[count]='\0';
                  printf("\033[31mERROR : %s IS INVALID VARIABLE \033[0m\n",in_variable);
                  fseek(fp,-1,SEEK_CUR);
               }
               else
               {
                fseek(fp,-2,SEEK_CUR);
               }
               count=0;
               data_type=0;
            }
            else
            fseek(fp,-1,SEEK_CUR);
            count=0;
        }
        else if(isdigit(ch))
        {
            int dot=0;
            digit[count]=ch;
            count++;
            while ((ch=read_char(fp))!=';' && isdigit(ch) || ch=='.' )
            {
                if(ch=='.')
                dot++;
                digit[count]=ch;
                count++;
            }
            
            digit[count]='\0';
            count=0;
            if(dot==0 || dot==1)
            print_output(digit,"NUMBER");
            else
            printf("\033[31mERROR : %s CANNOT HAVE MULTIPLE FLOATING POINTS \033[0m\n",digit);
            fseek(fp,-1,SEEK_CUR);
        }
        else if(ch=='\'')
        {
            character[count]='\'';
            count++;
            ch=read_char(fp);
            character[count]=ch;
            count++;
            ch=read_char(fp);
            character[count]=ch;
            count++;
            character[count]='\0';
            count=0;
            print_output(character,"SINGLE CHARACTER");
        }
        else if(ch==';')
        {
            print_output(";","END OF LINE");
            k_count--; 
        }
        else 
        {
            if(ch!=' '&& ch!='\n' && ch!='\t')
            {
                symoperator[0]=ch;
                symoperator[1]=read_char(fp);
                symoperator[2]='\0';
                int found=0;
                char operators[25][3] ={"+", "-", "*", "/", "%","++", "--","=", "+=", "-=", "*=", "/=", "%=",
                                    "==", "!=", ">", "<", ">=", "<=","&&", "||", "!","&", "|", "^"};
                    for (int i = 0; i < 25; i++)
                    {
                        if(strcmp(operators[i],symoperator)==0)
                        {
                            print_output(operators[i],"OPERATOR");
                            found++;
                            found++;
                            break;
                        }
                    }
                    if(found==0)
                    { 
                        symoperator[1]='\0';
                        for (int i = 0; i < 25; i++)
                        {
                            if(strcmp(operators[i],symoperator)==0)
                            {
                                found++;
                                print_output(operators[i],"OPERATOR");
                                break;
                            }
                        }
                    }
                    char symbols[11][2] ={"(", ")", "{", "}", "[", "]",";", ",", ".", ":", "?"};
                    if(found==0)
                    {
                        for (int i = 0; i < 11; i++)
                        {
                            if(strcmp(symbols[i],symoperator)==0)
                            {
                                found++;
                                if(strcmp(symbols[i],"(")==0 || strcmp(symbols[i],"[")==0)
                                parenthesis++;
                                if(strcmp(symbols[i],")")==0 || strcmp(symbols[i],"]")==0)
                                parenthesis--;
                                if(strcmp(symbols[i],"{")==0)
                                curly_bracket++;
                                 if(strcmp(symbols[i],"}")==0)
                                 curly_bracket--;
                                print_output(symbols[i],"SYMBOL");
                                break;
                            }
                        }   
                    }
                    if(found==1 && fgetc(fp)!=EOF)
                    fseek(fp,-2,SEEK_CUR);
            }
        }     
    }
    if(curly_bracket!=0)
    {
        printf("\033[31mERROR :  INVALID CURLY_BRACKET \033[0m\n");
    }
    printf("+----------------------------------------------------------------+\n");
    return 0;
}


                
                 
                
           
           