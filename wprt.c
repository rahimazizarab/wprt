/*
*  A program to display a file on a web browser.  This allows viewing of printer* listing in a web browser.
*
*  Released to public doomain by Rahim Azizarab  March 29,2015
*/  

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#define PORT    5000

int main(int argc, char **argv)
{
       char *buffer;
       unsigned long fileLen;
       FILE *p;
       if((p=fopen(argv[1],"r"))==NULL){
          printf("\nUnable t open file string.txt");
          exit(1);
         }

//Get file length
	fseek(p, 0, SEEK_END);
	fileLen=ftell(p);
	fseek(p, 0, SEEK_SET);

	//Allocate memory
	buffer=(char *)malloc(fileLen+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                                fclose(p);
		return;
	}

	//Read file contents into buffer
	fread(buffer, fileLen, 1, p);
	fclose(p);
//
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buffer, '0', sizeof(buffer)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        write(connfd, buffer, strlen(buffer)); 
        close(connfd);
        sleep(1);
     }
    free(buffer);
}
