// Ficheros de cabecera
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
//netbd.h es necesitada por la estructura hostent
char *my_itoa(int num, char *str);
int main(int argc, char *argv[])
{

char palabra[50],lpala[7];
 
if(argc > 2)
{
 //Primer paso, definir variables
 char *ip;
 int fd, numbytes,puerto,fd1;
 //char buf[100];
 puerto=atoi(argv[2]);
 ip=argv[1];
 
struct hostent *he;
 /* estructura que recibirÃ¡ informaciÃ³n sobre el nodo remoto */
 struct sockaddr_in server;
 /* informaciÃ³n sobre la direcciÃ³n del servidor */
 
if ((he=gethostbyname(ip))==NULL){
 /* llamada a gethostbyname() */
 printf("gethostbyname() error\n");
 exit(-1);
 }
 
//Paso 2, definicion de socket
 if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
 /* llamada a socket() */
 printf("socket() error\n");
 exit(-1);
 }
//Datos del servidor
 server.sin_family = AF_INET;
 server.sin_port = htons(puerto);
 server.sin_addr = *((struct in_addr *)he->h_addr);
 /*he->h_addr pasa la informaciÃ³n de ``*he'' a "h_addr" */
 bzero(&(server.sin_zero),8);
 
 //Paso 3, conectarnos al servidor
 if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
 /* llamada a connect() */
 printf("connect() error\n");
 exit(-1);
 }

printf("Escriba mensaje al servidor:");
scanf("%[^\n]",palabra);

strcat(palabra,"\n");
my_itoa(strlen(palabra),lpala);
strcat(lpala,"\n");

send(fd,lpala,strlen(lpala),0);
sleep(1);
send(fd,palabra,strlen(palabra),0);
char buf[50];

if ((numbytes=recv(fd,buf,7,0)) == -1){
	printf("error en recv\n");
	exit(-1);
}

buf[numbytes]='\0';

printf("Espero un numero n de caracteres n= %s",buf);


if ((numbytes=recv(fd,buf,50,0)) == -1){
 	printf("Error en recv() \n");
	exit(-1);
}
buf[numbytes]='\0';
 
printf("Mensaje del Servidor: %s",buf);
 /* muestra el mensaje de bienvenida del servidor =) */
 close(fd1);
close(fd);
}
else{
printf("No se ingreso el ip y puerto por parametro\n");
}
 
}

char *my_itoa(int num, char *str)
{
	        if(str == NULL)
		{
			                return NULL;
					        
		}
		        sprintf(str, "%d", num);
			        return str;
				
}
