/*
 The program is useful to create a server on a windows machine in order to receive data
 from an arduino wifi shield and save them to a .txt file.
  
   Before compiling and running the TCP Server:
 * Link the ws2_32.lib library in Run->Set Project Conf->Customised
 ->Linker->Add library: C:\MinGW\lib\libws2_32
 * Set the server PORT_NUMBER. It have to be the same on the shield sketch.
  
 * After compilation and before running the windows firewall must be set to allow the program to run on public networks.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "wavfile.h"
#include "winsock.h"
#include "signal_processing.h"

int main() {
    extern FILE * f;

    //initialise the server socket    
    init_win_sock();

    //open the file for writing
    f = wavfile_open("sound.wav");
    if(!f){
        printf("couldn't open sound.wav for writing: %s",strerror(errno));
	return 1;
    }

    //get only 10 samples than close the file and clean the memory
    for(int samples=0; samples<10;samples++){
        server_listen();
        //converting the string buffer to int values
        modify_by_frequence();
        }
    
    //close the file and cleanup the memory
    wavfile_close(f);
    socket_cleanup();
    return 0;
}
