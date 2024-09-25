#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(void) 
{
    int m=10, n=5,count=1, mult=1;
    while(count <3)
    { 
        if(m != 0)
        {
            m = fork(); n = n+25;
        }
        else
        { 
            m = fork(); n = n+20; mult = mult*n;
        }
        printf("n = %d mult = %d\n", n, mult);
        count =count + 1;
    }
}
