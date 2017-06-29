#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>//For socket()
#include <netinet/in.h>//For sockaddr_in and htons()
#include <netdb.h> //For getaddrinfo()
#include <errno.h> //For errno var
#include <sys/stat.h> //For open(), read(),write()
#include <fcntl.h> // and close()

const int	BUFFER_LEN		= 256;
const int	DEFAULT_PORT_NUM	= 20001;
#define		DEFAULT_HOSTNAME	"localhost.localdomain"

int	main	()
{
  char	buffer[BUFFER_LEN];
  char	machineName[BUFFER_LEN];
  int	port;

  printf("Machine name [%s]? ",DEFAULT_HOSTNAME);
  fgets(machineName,BUFFER_LEN,stdin);

  char*	cPtr	= strchr(machineName,'\n');

  if  (cPtr != NULL)
    *cPtr = '\0';

  if  (machineName[0] == '\0')
    strncpy(machineName,DEFAULT_HOSTNAME,BUFFER_LEN);

  printf("Port number [%d]? ",DEFAULT_PORT_NUM);
  fgets(buffer,BUFFER_LEN,stdin);

  if  ( (buffer[0] == '\0')  ||  (buffer[0] == '\n') )
    port = DEFAULT_PORT_NUM;
  else
    port = strtol(buffer,NULL,10);

  // Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
				SOCK_STREAM, // Reliable TCP
				0);
  struct addrinfo* hostPtr;
  int status = getaddrinfo(machineName,NULL,NULL,&hostPtr);

  if (status != 0)
  {
    fprintf(stderr,gai_strerror(status));
    exit(EXIT_FAILURE);
  }

  // Connect to server
  struct sockaddr_in server;
  // Clear server datastruct
  memset(&server, 0, sizeof(server));

  // Use TCP/IP
  server.sin_family = AF_INET;

  // Tell port # in proper network byte order
  server.sin_port = htons(port);

  // Copy connectivity info from info on server ("hostPtr")
  server.sin_addr.s_addr =
  ((struct sockaddr_in*)hostPtr->ai_addr)->sin_addr.s_addr;

  status = connect(socketDescriptor,(struct sockaddr*)&server,sizeof(server));

  if  (status < 0)
  {
    fprintf(stderr,"Could not connect %s:%d\n",machineName,port);
    return(EXIT_FAILURE);
  }

  printf("Please enter a string to send: ");
  fgets(buffer,BUFFER_LEN,stdin);
  write(socketDescriptor,buffer,BUFFER_LEN);
  read (socketDescriptor,buffer,BUFFER_LEN);

  printf("%s\n",buffer);
  close(socketDescriptor);
  return(EXIT_SUCCESS);
}
