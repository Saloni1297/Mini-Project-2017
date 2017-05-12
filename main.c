/* HEADER FILES */

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>

/* FUNCTIONS DECLARATIONS */

char infix_stack[200];
float post_stack[200];
void push(char);
void push_post(float);
float pop_post();
char pop();
int priority(char);
int is_Operator(char);
int is_Operand(char);
void evalaution(char []);

/* GLOBAL VARIABLES */

int rear=-1;
int top=-1;

/* FILE POINTER */

FILE *fp,*fp1;


/* MAIN FUNCTION */

int main()
{
    int test;
    fp=freopen("file3.txt","r",stdin);
    fp1=freopen("output.txt","w",stdout);

  /* SCANNING NUMBER OF TEST CASE */

    scanf("%d\n",&test);
    while(test--){
    char infix[200],postfix[200],l,symbol,flag=0,num=0;
    int i,j=0,temp,t;

    /* SCANNING THE INFIX EXPRESSION THAT THE USER WANTS TO EVALUATE */

    scanf("%[^\n]%*c",infix);
    push('(');

   /* FINDING THE LENGTH OF INFIX EXPRESSION */

    l=strlen(infix);
    i=0;
    j=0;
       while(i<=l-1)
        {
           symbol=infix[i];

           /* CONDITION FOR WHITESPACE */

                if(symbol==32 && i!=0)
                  {

                      continue;

                  }

           /* CONDITION FOR  CHARACTERS,SPECIAL CHARACTERS AND SOME SYMBOL THAT ARE INVALID FOR EVALUATION */


                else  if((symbol>=58 && symbol<=126) || (symbol>=27 && symbol<=31) || (symbol>=33 && symbol<=39) || (symbol==32 && i==0))
                    {

                        flag++;
                        printf("......Invalid input........\n");
                        break;

                    }

            /* CONDITION FOR CHECKING OPERAND */


                  else if(is_Operand(symbol))
                     {


                               while(infix[i]!=' ')
                               {

                                    postfix[j++]=infix[i++];

                               }

                          postfix[j++]=' ';
                          i++;

                     }

            /* CONIDITION FOR CHECKING UNARY OPERATOR */


                 else  if(symbol=='-' && (i==0 || infix[i-2]=='-' || infix[i-2]=='+' || infix[i-2]=='*' || infix[i-2]=='/' || infix[i-2]=='('))
                    {


                        postfix[j++]='@';
                        i=i+2;

                    }

            /* CONDITION FOR CHECKING OPERATOR */


                 else  if(is_Operator(symbol))
                      {


                                      while(priority(infix_stack[top])>=priority(symbol))
                                       {

                                                temp=pop();
                                                postfix[j++]=temp;
                                                postfix[j++]=' ';

                                       }
                           push(symbol);
                           i=i+2;

                       }

            /* CONDITION FOR OPEN PARENTHESIS */

                else if(symbol=='(')
                     {

                         push(symbol);
                           i=i+2;

                     }
            /* CONDITION FOR CLOSE PARENTHESIS ENCOUNTERED IN EXPRESSION */

                else if(symbol==')')
                  {



                               while(infix_stack[top]!='(')
                                {

                                      temp=pop();
                                      postfix[j++]=temp;
                                      postfix[j++]=' ';

                                }
                      t=pop();
                      i=i+2;

                  }
    }

    /* MAKING FINAL EXPRESSION */


while(infix_stack[top]!='(' && infix_stack[top]!=-1)
        {
            char t;

                  if(infix_stack[top]=='(')
                {


                     t=pop();

                }

            temp=pop();
            postfix[j++]=temp;
            postfix[j++]=' ';

        }
   postfix[j]='\0';


  /* SHOWING POSTFIX EXPRESSION */

   if(flag==0)
    {
    printf("\n.....OUTPUT.....");
    printf("\n");
    i=0;
    printf("\nPOSTFIX EXPRESSION : ");
    puts(postfix);
    printf("\n");

    /* FUNCTION CALLING FOR EVALUATING POSTFIX EXPRESSION */

   evalaution(postfix);
   }


    }
    fclose(fp);
    fclose(fp1);

        return 0;
}

  /* FUNCTION DEFINITION FOR POSTFIX EXPRESSION */


void evalaution(char post[])
{
 char symbol;
 int i=0,x,j,l;
 float value;

  /* CALCULATING LENGTH FOR POSTFIX EVALUATION */

l=strlen(post);

   i=0;
 while(i<=l-1)
 {
        float num=0;
        symbol=post[i];

            if(symbol==' ')
             {

                 continue;

             }

           else if(is_Operand(symbol))
            {



                           while(post[i]!=' ')
                             {

                                 num=num*10+(post[i++]-'0');

                             }

               push_post(num);
               i++;

           }


        else if(symbol=='@' && (is_Operand(post[i+1])))
          {

                 while(post[i+1]!=' ')
                 {

                     num=num*10+(post[i+1]-'0');
                     i++;

                  }
            float res=-1*num;
            push_post(res);
            i=i+2;

          }

          else if(symbol=='@' && post[i+1]=='@')
          {
              while(post[i+2]!=' ')

              {

                  num=num*10+(post[i+2]-'0');
                  i++;
              }

              push_post(num);

              i=i+3;
          }

        else if(is_Operator(symbol))
            {

                float num1,num2,result;

                num1=pop_post();

                num2=pop_post();


                    switch(symbol)
                     {

                         case '+' :result=num2+num1;
                         break;

                         case '-' :result=num2-num1;
                         break;

                         case '*' :result=num2*num1;
                         break;

                         case '/' :result=num2/num1;
                         break;

                    }
             push_post(result);
             i=i+2;
        }



 }

value=pop_post();
printf("Final result is  :  %f\n\n",value);

}

/* FUNCTION FOR PUSH OPERATION */


void push(char x)
{
    infix_stack[++top]=x;

}


void push_post(float elem)
{
    post_stack[++rear]=elem;

}

/* FUNCTION FOR POP OPERATION */

float pop_post()
{

    return post_stack[rear--];

}



char pop()
{

        return infix_stack[top--];

}

 /* FUNCTION FOR CHECKING THE PRIORITY OF OPERATORS */

int priority(char x)
{

    if(x=='(')
    {

        return 0;

    }
    if(x=='*'||x=='/')
    {

        return 1;

    }
    if(x=='+'||x=='-')
    {

        return 2;

    }

}

 /* FUNCTION FOR CHECKING THE OPERAND */

int is_Operand(char val)
{
    if(val>=48 && val<=57)
    {

        return 1;

    }
    else
    {

     return 0;

    }

}

 /* FUNCTION FOR CHECKING THE OPERATOR */


int is_Operator(char o)
{

    if(o=='+' || o=='-' || o=='*' || o=='/')
    {

        return 1;

    }
    else
    {

        return 0;

    }

}

