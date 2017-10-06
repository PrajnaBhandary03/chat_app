/**
 * @prajnaga_assignment1
 * @author  PRAJNA GANGADHAR BHANDARY <prajnaga@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/global.h"
#include "../include/logger.h"

int printhelp(char *filename);

/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */
int main(int argc, char **argv)
{
    
	/*Init. Logger*/
	cse4589_init_log(argv[2]);

	/*Clear LOGFILE*/
	fclose(fopen(LOGFILE, "w"));

	/*Start Here*/
    
    printf("Invoked client_server file.");
    char *FILENAME = argv[0];
    if(argc != 3) {
        printhelp(FILENAME);
    }
    //Defining input arguments
    char *IDENTITY = argv[1];
    char *PORT = argv[2];
    
    if( strcmp(IDENTITY, "s") == 0){
        printf("This is a server file");
        //call server
    }
    else if(strcmp(IDENTITY, "c") == 0){
        printf("This is a client file");
        // get IP Address of the host
        //call client
        
    }else {
        printhelp(FILENAME);
    }
	return 0;
}

int printhelp(char *filename){
    printf("Usage:%s [s/c] [port]\n", filename);
    exit(-1);
}
