#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

/*
 Example:
 
 ./[objectFile] [targetCSVFile_pathname]
 
 */
void plotData(string s)
{
    FILE *gnupipe = NULL;
    
    string command2 = "plot '"+s+"' using 1:2 with linespoints";
    
    char *command2_ = new char[command2.length() + 1];
    strcpy(command2_, command2.c_str());

        
    char *gnuCommands [] = {"set title \"Performance Comparison (Byte allocated for nodes(along y-axis) vs max number of mods per node(along x-axis))\"",command2_};
    
    gnupipe = popen("gnuplot -persitent", "w");
    
    for(int i=0;i<2;i++){
        fprintf(gnupipe, "%s\n",gnuCommands[i]);
    }
    
    fclose(gnupipe);
}

int main(int argc, const char * argv[])
{
    string s(argv[1]);
    plotData(s);
}
/*
 /csv_Mods/
 */
