#pragma once

#include<stdio.h>

#define MAX 100

struct course
{
    double grade = 0.0;
    double credit = 0.0;
    double gpa = 0.0;
};

double grade_to_gpa(double grade)
{
    if(grade >= 95) return 5.0;
    else if(grade < 60) return 0.0;
    else
    {
        return 2.0 + (grade-65.0)/10.0;
    }
}

void GPA()
{
    course g[MAX];
    int top = 0;
    double credit = 0.0;
    freopen("../header/gpa.in","r",stdin);
    while(scanf("%lf%lf",&g[top].grade,&g[top].credit) && !feof(stdin))
    {
        g[top].gpa = grade_to_gpa(g[top].grade);
        credit += g[top].credit;
        ++top;
    }
    fclose(stdin);
    double gpa = 0;
    for(int i = 0;i<top;++i)
    {
        gpa += g[i].gpa * g[i].credit;
    }
    gpa /= credit;
    printf("your gpa is %lf",gpa);
}












