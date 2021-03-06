#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "calc.h"

#define MAXOP 100
#define NUMBER '0'
#define MAXLINE 500

char line[MAXLINE];
int line_i;

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = line[line_i++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;  
    i = 0;
    if (isdigit(c)) 
        while (isdigit(s[++i] = c = line[line_i++]))
            ;
    if (c =='.') 
        while (isdigit(s[++i] = line[line_i++]))
            ;
    s[i] = '\0';
    line_i--;
    
    return NUMBER;
}

int getl(char s[], int lim)
{
    int c, i;
    i = 0;
    
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}



int main () {
    int type;
    double op2, op3;
    char s[MAXOP];
    int t, g;

    while (getl(line, MAXLINE) != 0) {
        line_i = 0;

        while ((type = getop(s)) != EOF) {
            switch (type)
            {
            case NUMBER:
                push (atof(s));
                break;
            case '+':
                push (pop() + pop());
                break;
            case '*':
                push (pop() * pop());
                break;
            case '-':
                op2 = pop();
                push (pop() + op2);
                break;
            case '%' :
                op2 = pop();
                if (op2 != 0.0) {
                    t = (pop() / op2);
                    trunc (t);
                    push (t);

                } else {
                    printf("error: zero divisor\n");
                    return -1;
                }
                break;
            case '^' :
                op2 = pop ();
                op3 = pop ();
                push (pow(op3, op2));
                break;    
            case '/' :
                op2 = pop();
                if (op2 != 0.0) {
                    push (pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                    return -1;
                }
                break;

            case 's' :
                op2 = pop ();
                op3 = sin (op2);
                push (op3);
                break;
            case 'c' :
                op2 = pop ();
                op3 = cos (op2);
                push (op3);
                break;    
            case '\n': 
                printf("\t%.8g\n", pop());
                break;

            default:
                printf("Successful\n");
                return 0;
            }
        }
    }
    return 0;
}