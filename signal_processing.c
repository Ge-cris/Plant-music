/*
 * Library for processing and transform the received data into music 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "wavfile.h"
#include "winsock.h"


FILE * f;

// Function to wrap value within a specified range
int wrap(int value, int min, int max) {
    int range = max - min + 1;
    return (value - min + range) % range + min;
}
//Function to modify the music by frequency
void modify_by_frequence (){
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);
    extern int recv_size;
    extern char buffer[BUFFER_SIZE];
    short waveform[NUM_SAMPLES];
    int frequency;
    short volume = 32000;
    unsigned length = NUM_SAMPLES;
    bool vol_slider;
    unsigned short noise_amp = 3;
    int val;
    char str_val[4];
    
    for(int i=0, j=0; i<= recv_size; i++){
        if(buffer[i] == '\n'){
            str_val[j]='\0';
            j=0;
            val = atoi(str_val);
            frequency = wrap(val, 200, 600);
            printf("%d\n", val);
            //create the wave note
            for(int l=0; l<length; l++){
		double t = (double) l / WAVFILE_SAMPLES_PER_SECOND;
                if(l%2 == 0)
                    waveform[l] = volume*sin(frequency*t*2*M_PI);
                else{
                    waveform[l] = volume*sin((frequency+noise_amp)*t*2*M_PI);
                
                    if(volume>1000 && vol_slider==0)        //if the volume is high
                        volume -=2;                         //lower the volume
                    else if(volume<=1000 && vol_slider==0)  //if the volume reached the bottom
                        vol_slider = 1;                     //move the volume slider towards top
                    else if(volume<32000 && vol_slider==1)  //if the volume is low
                        volume +=2;                         //increase the volume
                    else if(volume>=32000 && vol_slider==1) //if the volume reached the top
                        vol_slider = 1;                     //move the volume slider towards bottom
                }
            }
            wavfile_write(f,waveform,length);
        }
        else{
            str_val[j] = buffer[i];
            j++;
        }        
    }
}

