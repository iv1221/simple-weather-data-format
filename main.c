/* README
# - Project 2
This repository contains the source code of Project 2 in C, for module ENG1008-Programming EDE[22/23 T1].

# - Assignment brief
- To read in sensor data into single and multidimensional arrays;
- To carry out data analysis on it

# - Compiling
Building the program can be done using 'Build and Run'.	This program was developed and tested on Codeblocks [Release 20.03 rev 11983 (2020-03-12 18:24:30) gcc 8.1.0 Windows/unicode - 64 bit].

# - Usage
This assumes the user has a .txt file located in the same folder as the .exe file for the program in question.
The program checks for the .txt file named "proj2.txt" from the project folder and run the readings through the program.
Users can also opt to use I/O redirection to a .txt file through cmd in the project folder where the .exe file is located using the command line "> project2.exe < proj2.txt".
The .exe file can be found by compiling and navigating from the project folder to '...bin/Debug/project2'.

The program will display readings analyzed with the input from proj2.txt file for 3 months at once*/


//P.S. Please run the program in full screen so as to ensure the results/output are correctly displayed as intended.
#include <stdio.h>
#include <math.h>

void hourAvg(int x, float data[x], float month[30][16]);            //Function prototypes for Hourly Average, Mean, Standard Deviation and Monthly Hour Average
void dailyMsd(int x, float data[x], float month[30][16]);
float monthHr(float month[30][16], int hour);
void printArray(float month[30][16]);                          //Function to print arrays

int main(void){
    float sum;
    float data[5040];                                               //Declaring arrays for 1D and Month 2D arrays, 5040 derived from the given .txt file
    float april[30][16];                                            //Months declared 30 rows for days, 16 columns for 14 hours and 2 for mean and standard deviation
    float may[30][16];
    float june[30][16];
    FILE *input;
    input = fopen("proj2.txt", "r");                                //File I/O to read data in proj2.txt file

    for(int i = 0;i < 5040;i++){                                    //Reading data from .txt file to 1D array
        fscanf(input, "%f", &data[i]);
    }
    fclose(input);                                                  //Close File I/O

    hourAvg(0,data,april);                                          //Function calls to get 2D arrays
    hourAvg(1680,data,may);                                         //As we have 5040 data for 3 months there will be 1680 readings per month
    hourAvg(3360,data,june);
    dailyMsd(0,data,april);
    dailyMsd(1680,data,may);
    dailyMsd(3360,data,june);

    printf("April  ");                                              //Function calls to print 2D month arrays
    printArray(april);                                              //Calls print array function with month array as parameter
    printf("\nMay    ");
    printArray(may);
    printf("\nJune   ");
    printArray(june);
}

void hourAvg(int x, float data[x], float month[30][16]){    //Hourly average function using x count to differentiate between months
    int row = 0, col = 0;
    float avg;

    for(int i = 0; i < 420; i++){                           //420 readings per month
        avg = 0;                                            //Reset avg value to 0 every loop
        for(int j = 0; j < 4; j++){                         //4 readings per hour
            avg += data[x++];                               //Sum of 4 readings
        }
        month[row][col] = avg/4;                            //Calculates average value and assigns it to month array
        col++;                                              //Col increment
        if(col == 14){                                      //If col = 14, enter new line and set col to 0
            row++;                                          //Row increment
            col = 0;
        }
    }
}

void dailyMsd(int x, float data[x], float month[30][16]){   //Daily Mean and Standard Deviation Function, using x count to differentiate between months
    float mean, sum, sd;
    int y = x;
    for(int row = 0;row < 30; row++){
        sum = 0, sd = 0;                                    //Reset sum and sd values to 0 every loop
        for(int j = 0; j < 56; j++){
            sum += data[x++];                               //Sum of daily temperature
        }
        mean = sum/56;                                      //Average of daily temperature
        month[row][14] = mean;                              //Assign value to column 15 of month array
        for(int col = 0; col < 56; col++){
            sd += pow(data[y++]- mean, 2);                  //Standard deviation calculations
        }
        month[row][15] = sqrt(sd/56);                       //Assign standard deviation value to column 16 of month array
    }
}

float monthHr(float month[30][16], int hour){       //Month Hourly Average Function
    float monthAvg;

    printf("MonthAvg");
    for(;hour < 14; hour++){                        //Loop to obtain values by column
        monthAvg = 0;                               //Sets monthAvg to 0
        for(int row = 0; row < 30; row++){          //Sums 30 days of readings from the same hour
            monthAvg += month[row][hour];
        }
        printf("%8.2f ", monthAvg/30);              //Prints the monthly average in the 31st row
    }
    printf("\n");
}

void printArray(float month[30][16]){                               //Function passed month array to print
    for(int time = 700; time <= 2000; time+=100){                   //24 Hour time header row loop
        printf("%9.4d", time);
    }
    printf("      Mean     StdDev\n");                              //Table header
    for(int i = 0; i < 155; i++) putchar('=');                      //Header separator
    printf("\n");
    for(int row = 0; row < 30; row++){                              //Printing month array
        printf("Day %2d\t", row+1);                                 //Prints day column for table
        for(int col = 0; col < 14; col++){                          //Prints hourly average for 14 hours
            printf("%8.2f ", month[row][col]);
        }
        printf("|%8.2f %8.2f ", month[row][14], month[row][15]);    //Prints Mean, SD and enter a new line
        printf("\n");
    }
    monthHr(month,0);                                               //Function call to print month hourly average
}
