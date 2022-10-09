/* A simple echo client using TCP */
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		256	/* buffer length */

void send_file(FILE *fp, int sockfd){
	char data[SIZE] = {0};
	
	while(fgets(data, SIZE, fp)!= NULL){
		if(send(sockfd, data, sizeof(data), 0)== -1){
			perror("[-]Error In Sending Data");
			exit(1);
		}
		bzero(data, SIZE);
	}
}

void write_file(int sockfd){
		int *N;
		FILE *fp;

		char *buffer[25];
		char *s;
		char *ptr;

	
		
		if(fp = NULL){
			perror("[-]Error in creating file");
			exit(1);
		}	

		while(1){
			N = recv(sockfd, buffer, 25, 0);
		
			if(N<=0){
			  break;
			  return;
			}
				
			char c = buffer[0];
			if(c=='@'){
			  printf("File not found on Server Device");	
			}

			fp = fopen("output.txt", "a");
			fprintf(fp, "%s", buffer);
			fflush(fp);

			bzero(buffer, 25);
		}


		fclose(fp);
	
		return;
}

int main(int argc, char **argv)
{
	int 	n, i, bytes_to_read;
	int 	sd, port;
	struct	hostent		*hp;
	struct	sockaddr_in server;
	char	*host, *bp, rbuf[BUFLEN], sbuf[BUFLEN], filename[1024];

	switch(argc){
	case 2:
		host = argv[1];
		port = SERVER_TCP_PORT;
		break;
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (hp = gethostbyname(host)) 
	  bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	else if ( inet_aton(host, (struct in_addr *) &server.sin_addr) ){
	  fprintf(stderr, "Can't get server's address\n");
	  exit(1);
	}

	/* Connecting to the server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
	  fprintf(stderr, "Can't connect \n");
	  exit(1);
	}

	
	scanf("%[^\n]", filename);	
	printf(filename);

	write(sd, filename, sizeof(filename)+2);

	write_file(sd);
	

	close(sd);
	return(0);
}
