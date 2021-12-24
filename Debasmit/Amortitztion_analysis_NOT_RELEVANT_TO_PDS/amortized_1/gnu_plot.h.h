//
//  gnu_plot.h.h
//  adv_DSA
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#ifndef gnu_plot_h
#define gnu_plot_h

#include<stdio.h>
#include<stdlib.h>
// "set xlabel \"number of elements\"","set ylabel \"time elapsed (in unity)\"",
void plotData_real_amt_norm(int *N, int *real, int *amt, int* norm, int n)
{
    FILE *fp = NULL;
    FILE *gnupipe = NULL;
    char *gnuCommands [] = {"set title \"Performance Comparison\"",
        "plot '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:2 with linespoints title 'RealTime', '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:3 with linespoints title 'Amortized Time', '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:4 with linespoints title 'Naive Time Complexity'"};
    
    fp = fopen("/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv", "w");
    gnupipe = popen("gnuplot -persitent", "w");
    

    for(int i =0;i<n;i++)
    {
        fprintf(fp, "%d, %d, %d, %d\n",N[i],real[i],amt[i],norm[i]);
    }
    
    for(int i=0;i<2;i++)
    {
        fprintf(gnupipe, "%s\n",gnuCommands[i]);
    }
}


void plotData_real_amt(int *N, int *real, int *amt,  int n)
{
    FILE *fp = NULL;
    FILE *gnupipe = NULL;
    char *gnuCommands [] = {"set title \"Performance Comparison\"",
        "plot '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:2 with linespoints title 'RealTime', '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:3 with linespoints title 'Amortized Time'"};
    
    fp = fopen("/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv", "w");
    gnupipe = popen("gnuplot -persitent", "w");
    

    for(int i =0;i<n;i++)
    {
        fprintf(fp, "%d, %d, %d\n",N[i],real[i],amt[i]);
    }
    
    for(int i=0;i<2;i++)
    {
        fprintf(gnupipe, "%s\n",gnuCommands[i]);
    }
}

void plotData_real_amt_tDayAvg(int *N, int *real, int *amt, float *tDayAvg, int n)
{
    FILE *fp = NULL;
    FILE *gnupipe = NULL;
    char *gnuCommands [] = {"set title \"Performance Comparison\"",
        "plot '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:2 with linespoints title 'RealTime', '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:3 with linespoints title 'Amortized Time','/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:4 with linespoints title 't Day Avg'"};
    
    fp = fopen("/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv", "w");
    gnupipe = popen("gnuplot -persitent", "w");
    

    for(int i =0;i<n;i++)
    {
        fprintf(fp, "%d, %d, %d, %f\n",N[i],real[i],amt[i],tDayAvg[i]);
    }
    
    for(int i=0;i<2;i++)
    {
        fprintf(gnupipe, "%s\n",gnuCommands[i]);
    }
}



#endif


/*
 
 plot '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:2 with linespoints title 'RealTime', '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:3 with linespoints title 'Amortized Time', '/Users/debasmitroy/Desktop/programming/XcodePrj/adv_DSA/amortized_1/data.csv' using 1:4 with linespoints title 'Naive Time Complexity'

 */
