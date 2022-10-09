/* A simple echo server using TCP */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#define BUFLEN		256
#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		256	/* buffer length */

#define SIZE 1024

int echod(int);
void reaper(int);



int main(int argc, char **argv)
{
	int 	sd, new_sd, client_len, port;
	struct	sockaddr_in server, client;

	switch(argc){
	case 1:
		port = SERVER_TCP_PORT;
		break;
	case 2:
		port = atoi(argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %d [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	/* Bind an address to the socket	*/
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
		fprintf(stderr, "Can't bind name to socket\n");
		exit(1);
	}

	/* queue up to 5 connect requests  */
	listen(sd, 1);

	(void) signal(SIGCHLD, reaper);

	  client_len = sizeof(client);
	  new_sd = accept(sd, (struct sockaddr *)&client, &client_len);
	  if(new_sd < 0){
	    fprintf(stderr, "Can't accept client \n");
	    exit(1);
	  }
	  
		(void) close(sd);
		exit(echod(new_sd));
	  
}


void send_file(FILE *fp, int sockfd, int error){
    char data[25] = {0};
    char data2[25] = {'D','D', 'D', 'D', 'D','D','D', 'D', 'D', 'D','D','D', 'D', 'D', 'D','D','D', 'D', 'D', 'D','D','D', 'D', 'D', 'D'};
	//Char is of one byte in C so each packets payload will be of 25 bytes + 
	//Each packet has some fixed overhead (source and destination addresses etc) TCP packets have a max overhead of 60 bytes. 
	//So we have 85 bytes as the size of the packet.
	
	if(fp==NULL){	
	    data2[0] = '@';
	    
            if(send(sockfd, data2, 25, 0) == -1){
		printf("Error in sending data");
		exit(1);
	    }
	    bzero(data2, 25);
            return;
	}

	while(fgets(data, 25, fp)!= NULL){
		
		if(send(sockfd, data, 25, 0) == -1){
			perror("[-]Error in sending data");
			exit(1);
		}
		bzero(data, 25);
	}
}



/*	echod program	*/
int echod(int sd)
{
	FILE *fptr;
	char	*bp, buf[BUFLEN];
	int 	n, bytes_to_read;
	char *str = "Hello"; 
	int error = 0;	
	
	read(sd, buf, BUFLEN);

	fptr = fopen(buf, "r");
	
	if(fptr == NULL){
		printf("Error!");
		error = 1;
		send_file(fptr, sd, error);
		exit(1);
	}
	
	send_file(fptr, sd, error);
	
	fclose(fptr);

	printf(buf);
	close(sd);

	return(0);
}

/*	reaper		*/
void	reaper(int sig)
{
	int	status;
	while(wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}
