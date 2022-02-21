// Ficheros de cabecera
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h> 
//FunciÃ³n principal
char *my_itoa(int num, char *str);

int main(int argc, char **argv)
{

char palabra[50];
char lpala[7];
if(argc > 1)
{
 
//Primer paso, definir variables
int fd,fd2,longitud_cliente,puerto,numbytes;
puerto=atoi(argv[1]);
 
//Se necesitan dos estructuras del tipo sockaddr
//La primera guarda info del server
//La segunda del cliente
 struct sockaddr_in server;
 struct sockaddr_in client;
 
//Configuracion del servidor
 server.sin_family= AF_INET; //Familia TCP/IP
 server.sin_port = htons(puerto); //Puerto
 server.sin_addr.s_addr = INADDR_ANY; //Cualquier cliente puede conectarse
 bzero(&(server.sin_zero),8); //Funcion que rellena con 0's
 
 //Paso 2, definicion de socket
 if (( fd=socket(AF_INET,SOCK_STREAM,0) )<0){
 perror("Error de apertura de socket");
 exit(-1);
 }
 
 //Paso 3, avisar al sistema que se creo un socket
 if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
 printf("error en bind() \n");
 exit(-1);
 }
 
 //Paso 4, establecer el socket en modo escucha
if(listen(fd,5) == -1) {
 printf("error en listen()\n");
 exit(-1);
 }
 
 //Paso5, aceptar conexiones


while(1) {
 longitud_cliente= sizeof(struct sockaddr_in);
 /* A continuaciÃ³n la llamada a accept() */
 if ((fd2 = accept(fd,(struct sockaddr *)&client,&longitud_cliente))==-1) {
 printf("error en accept()\n");
 exit(-1);
 }


char buf[50];

if ((numbytes=recv(fd2,buf,7,0)) == -1){
	printf("error en recv\n");
	exit(-1);
}

buf[numbytes]='\0';

printf("Espero un numero n de caracteres n= %s",buf);


if ((numbytes=recv(fd2,buf,50,0)) == -1){
	printf("error en recv\n");
	exit(-1);
}

buf[numbytes]='\0';

printf("Mensaje del Cliente: %s",buf);
int num1 = atoi(buf);
if (num1 == 0){ return 0;}
//printf("Numero = %d",num1);
//int num2 = num1 + 1 ;
//printf("Suna = %d",num2);

//printf("Escriba mensaje al cliente:");
//scanf("%[^\n]",palabra);
//printf("%s\n",palabra );

char suma[16];
sprintf(suma, "%d", num1 + 1);
printf("El nuevo numero es %s",suma);

strcat(suma,"\n");
my_itoa(strlen(suma),lpala);
strcat(lpala,"\n");



send(fd2,lpala,strlen(lpala),0);
sleep(1);
send(fd2,suma,strlen(suma),0);


//write(fd2,suma,strlen(suma));
close(fd2); /* cierra fd2 */
 }
close(fd);
}
else{
printf("NO se ingreso el puerto por parametro\n");
}
 
return 0;
 
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
