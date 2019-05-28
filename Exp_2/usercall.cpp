#include <stdio.h>
#include <ctime>
#include <sys/timeb.h>

using namespace std;

long operation(int* result,int num1,int num2,char* op)
{
    if(op)
    {
        if(*op == '+')
        {
            *result = num1 + num2;
        }
        else if(*op == '-')
        {
            *result = num1 - num2;
        }
        else if(*op == '*')
        {
            *result = num1*num2;
        }
        else if(*op == '\\')
        {
            if(num2!=0)
                *result = num1/num2;
            else
                printf("divided number can't be zero!\n");
        }else
            printf("unrecongized operator %c\n", *op);
    }else
    {
        printf("operation is empty.\n");
    }
    return 0;
}
int main()
{
    /**
     * total:10000*10000 times
     * + - * / each 2500000 times
     */
    //struct timeval tstart,tend;
    //do_gettimeofday(&tstart);
    //gettimeofday(&tstart);
    struct timeb starttime,endtime;
    ftime(&starttime);
    int i;
    const int count = 100000000;
    for(i=0;i<count;i++) // +
    {
        int result;
        char op_add = '+';
        operation(&result, i, 10, &op_add);
    }
    for(i=0;i<count;i++) // -
    {
        int result;
        char op_sub = '-';
        operation(&result, i, 10, &op_sub);
    }
    for(i=0;i<count;i++) // *
    {
        int result;
        char op_mul = '*';
        operation(&result, i, 2, &op_mul);
    }
    for(i=0;i<count;i++) // '//'
    {
        int result;
        char op_div = '\\';
        operation(&result, i, 10, &op_div);
    }
    //gettimeofday(&tend);
    ftime(&endtime);
    printf("Usrcall time use:%ld msec.\n", 1000*(endtime.time - starttime.time) + (endtime.millitm - starttime.millitm));
    return 0;
}
