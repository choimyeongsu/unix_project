#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

 int main ( )
 {
   int clientfd, result, temp, k, setpassword, temp1, reenterk, check=0, cnt=0, gaze=0, numberofthings=0;
   char numoflocker[100];
   int selectlocker;
   char last, need, check1 = 'a';
   char inmsg[MAXLINE], outmsg[MAXLINE];
   struct sockaddr_un serverUNIXaddr;
   


   clientfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
   serverUNIXaddr.sun_family = AF_UNIX;
   strcpy(serverUNIXaddr.sun_path, "convert");
   do { 
      result = connect(clientfd, &serverUNIXaddr, sizeof(serverUNIXaddr));
      if (result == -1) sleep(1);
   } while (result == -1);
   
   read(clientfd, inmsg, MAXLINE);
   temp1=atoi(inmsg);
   
   while(1)
   {
	   read(clientfd,numoflocker,MAXLINE);
	   printf("%s\n",numoflocker);
	   for(int i=1; i<=temp1; i++)
	   {
	   	printf("%4d   " , i);
		read(clientfd,inmsg,MAXLINE);
		printf(":%10s",inmsg);
		
		read(clientfd,inmsg,MAXLINE);
		gaze=atoi(inmsg);
		if(gaze>=0)
		{
		    printf("     |");		
		    for(int j=0; j<10; j++)
		    {
		       if(j<gaze)
		       {
		       printf("■ ");
		       }
		       else printf("□ ");
		   
		    }
		    printf("|");
		    printf("\n");
	        
	        }
	        else
	        {
	           printf("     |");	
	           printf("💣 💣 💣 💀 💣 💣 💣");
	           printf("|");
		   printf("\n");
	        }		
		
		
		
	   }
	   printf("\n");
	   
	   // index
	   read(clientfd,inmsg,MAXLINE);
	   printf("%s",inmsg);
	   // index input
	   fgets(inmsg,MAXLINE,stdin);
	   if(atoi(inmsg)==-1) exit(0);
	   write(clientfd,inmsg,MAXLINE);
	   printf("\n");
	   
	   
	   
	   read(clientfd,inmsg,MAXLINE);
	   if(strcmp(inmsg,"The loker is bombed and can not be used\n")==0)
	   {
	      printf("%s", inmsg);
	      continue;
	   }
	     
	   
	   

	   
	   while(1)
	   {
		   read(clientfd,inmsg,MAXLINE);
		   if(strcmp(inmsg,"set password (four digits) : ") == 0) //same 
		   {
		     //password
		     printf("%s",inmsg);
		     fgets(inmsg,MAXLINE,stdin);
		     write(clientfd,inmsg,MAXLINE);		 
		     printf("\n");
		     printf("Re-enter password (four digits) : ");
		     fgets(inmsg,MAXLINE,stdin);
		     write(clientfd, inmsg, MAXLINE);
		     
		     
		     
		     read(clientfd,inmsg,MAXLINE);
		     printf("%s", inmsg);
		     if(strcmp(inmsg,"wrong password\n")==0)
		     {
		         
		         break;
		         
		     }
		     
		     //Enter the number of things
		     read(clientfd,inmsg,MAXLINE);
		     printf("%s : ", inmsg);
		     fgets(inmsg,MAXLINE,stdin);		  
		     write(clientfd,inmsg,MAXLINE);
		     
		     if(atoi(inmsg)>10)
		     {
		        read(clientfd,inmsg,MAXLINE);
		        printf("%s\n", inmsg);
		        
		     }
		     
		     
		     break;
		     
		     
		      
		   }	        
		     
		     
		   
		   else
		   { 
		     // insert password print
		     printf("%s",inmsg);
		     // password input
		     fgets(inmsg,MAXLINE,stdin);
		     write(clientfd,inmsg,MAXLINE);
		     printf("\n");
		   
		     read(clientfd,inmsg,MAXLINE);
		     if(strcmp(inmsg,"wrong password\n") == 0)
		     { 
			printf("%s\n",inmsg);
			cnt++;
			sprintf(inmsg, "%d", cnt);
			write(clientfd,inmsg,MAXLINE);
			if(cnt==3)
			{		
			   printf("Incorrect password 3 times can be used after 10 seconds\n\n");
			   for(int i = 10; i>0; i--)
			   {
			      printf("Locker available after %d seconds\n", i);
			      if(i==1)
			      {
			         printf("\nGo back to the first\n\n");
			      }
			      sleep(1);
			   }	                  
                          
                          cnt=0;
                          break;
                       }
		     }
		     else
		     {
			printf("%s",inmsg);
			
			
			
			read(clientfd,inmsg,MAXLINE);			
			printf("%s",inmsg);			
			fgets(inmsg,MAXLINE,stdin);
		        write(clientfd,inmsg,MAXLINE);
		        break;
		     }  
		   }
	   }

   }
 }

