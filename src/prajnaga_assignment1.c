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
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>

//To get err no
#include <errno.h>

#include "../include/global.h"
#include "../include/logger.h"


#define TRUE 1
#define MSG_SIZE 256
#define BUFFER_SIZE 256


int connect_to_host(char *server_ip, int server_port);
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
    
    cse4589_print_and_log("Invoked client_server file.");
    char *FILENAME = argv[0];
    if(argc != 3) {
        printhelp(FILENAME);
    }
    //Defining input arguments
    char *IDENTITY = argv[1];
    char *PORT = argv[2];
    
    if( strcmp(IDENTITY, "s") == 0){
        cse4589_print_and_log("This is a server file");
        //call server

        
    }
    else if(strcmp(IDENTITY, "c") == 0){
        cse4589_print_and_log("This is a client file");
        // get IP Address of the host
                      
            //Defining arguments for the server
            int server;
            char *IP = "127.0.0.1";
            server = connect_to_host(IP, atoi(PORT));
            //Test ptint
            cse4589_print_and_log(" Test : Client has been succesfully invoked");

            while(TRUE){
                cse4589_print_and_log("\n[PA1-Client@CSE489/589]$ ");
                fflush(stdout);

                char *msg = (char*) malloc(sizeof(char)*MSG_SIZE);
                memset(msg, '\0', MSG_SIZE);
                if(fgets(msg, MSG_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to msg
                    exit(-1);

                cse4589_print_and_log("I got: %s(size:%ld chars)", msg, strlen(msg));

                cse4589_print_and_log("\nSENDing it to the remote server ... ");
                if(send(server, msg, strlen(msg), 0) == strlen(msg))
                    cse4589_print_and_log("Done!\n");
                fflush(stdout);

                /* Initialize buffer to receieve response */
                char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
                memset(buffer, '\0', BUFFER_SIZE);

                if(recv(server, buffer, BUFFER_SIZE, 0) >= 0){
                    cse4589_print_and_log("Server responded: %s", buffer);
                    fflush(stdout);
                }
            }
        
    }else {
        printhelp(FILENAME);
    }
	return 0;
}

int printhelp(char *filename){
    cse4589_print_and_log("Usage:%s [s/c] [port]\n", filename);
    exit(-1);
}



int connect_to_host(char *server_ip, int server_port)
{
    int fdsocket, len;
    struct sockaddr_in remote_server_addr;
      //Test ptint
      cse4589_print_and_log(" Test : Called connect to host");
      

    fdsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(fdsocket < 0)
       perror("Failed to create socket");

    bzero(&remote_server_addr, sizeof(remote_server_addr));
    remote_server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
    remote_server_addr.sin_port = htons(server_port);

    if(connect(fdsocket, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0)
        perror("Connect failed");

    return fdsocket;
}

