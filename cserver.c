#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

struct locker
{
   int password;  
   int NumberOfThings;
};

 int main ()
 {
   int listenfd, connfd, clientlen, temp, selectlockertemp,key, setpasswordtemp, reenterpassword, cnt=0, passwordcnt=0;
   
   char inmsg[MAXLINE],numoflocker[MAXLINE]="-----Number of lockers available-----\n", occupiedlocker[MAXLINE]="occupied", emptylocker[MAXLINE]="empty";
   char selectlocker[MAXLINE]="select locker (Input -1 end) : " , setpassword[MAXLINE]="set password (four digits) : ", wrongpassword[MAXLINE]="wrong password\n", insertpassword[MAXLINE]="insert pssword (four digits) : ",
 correctpassword[MAXLINE] = "Correct. Use this locker\n", question[MAXLINE] = "Do you want to unlock this locker? (Y/N) : " ,rightpassword[MAXLINE]="\nRight password\n\n", Enteritem[MAXLINE]="Enter the number of items",bomb[MAXLINE]="BOMB!", lockerbomb[MAXLINE]="locker bomb!!", selectlockerbomb[MAXLINE]="The loker is bombed and can not be used\n";
   

   
   struct sockaddr_un serverUNIXaddr, clientUNIXaddr;

   signal(SIGCHLD, SIG_IGN);
   clientlen = sizeof(clientUNIXaddr);

   listenfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
   serverUNIXaddr.sun_family = AF_UNIX;
   strcpy(serverUNIXaddr.sun_path, "convert");
   unlink("convert");
   bind(listenfd, &serverUNIXaddr, sizeof(serverUNIXaddr));

   listen(listenfd, 5);
   
   connfd = accept(listenfd, &clientUNIXaddr, &clientlen);
   cnt++;
   printf("set number of locker: ");
   fgets(inmsg, MAXLINE, stdin);
   write(connfd, inmsg ,MAXLINE);
   temp=atoi(inmsg);
   struct locker numberoflocker[temp+1];
  
   for(int i=1; i<=temp; i++)
   {
      numberoflocker[i].password=0;
      numberoflocker[i].NumberOfThings=0;
   }
   
   
   while(1)
   {
           if(cnt!=1) connfd = accept(listenfd, &clientUNIXaddr, &clientlen);
   
	   // Number of lockers available
	   write(connfd,numoflocker,MAXLINE);
	   
	   for(int i=1; i<=temp; i++)
	   {     
	        if(numberoflocker[i].password==-100)
		{
		        numberoflocker[i].NumberOfThings=-100;
		        write(connfd,bomb,MAXLINE);
		}
		else if(numberoflocker[i].password!=0)
		{ 
		 	write(connfd,occupiedlocker,MAXLINE);
		}
		
		else
		{   
			write(connfd,emptylocker,MAXLINE);
		}    
		sprintf(inmsg, "%d", numberoflocker[i].NumberOfThings);
		write(connfd,inmsg,MAXLINE);
		 
	   }
	    
	    write(connfd,selectlocker,MAXLINE);
	    //index
	    read(connfd,inmsg,MAXLINE);
	    
	    selectlockertemp=atoi(inmsg);
	    
	    
	    
	    if(numberoflocker[selectlockertemp].password==-100)
	    {
	        
	        
	        write(connfd,selectlockerbomb,MAXLINE);
	        continue;
            }
            else write(connfd,inmsg,MAXLINE);
	    
	    
	    
	    if(numberoflocker[selectlockertemp].password == 0)
	    {
	      //password
	      write(connfd,setpassword,MAXLINE);
	      read(connfd,inmsg,MAXLINE);
	      setpasswordtemp=atoi(inmsg);
	      
	      read(connfd,inmsg,MAXLINE);
	      reenterpassword=atoi(inmsg);
	      if(setpasswordtemp==reenterpassword)
	      {
	         numberoflocker[selectlockertemp].password = setpasswordtemp;
	         write(connfd,rightpassword,MAXLINE);
	         
	         //Enter the number of things 
	         write(connfd,Enteritem,MAXLINE);
	         
	         read(connfd,inmsg,MAXLINE);
	         //index.things input
	         if(atoi(inmsg)>10)
	         {
	            //write bomb
	            write(connfd,lockerbomb,MAXLINE);
	            //index-> selectlockertemp 
	            numberoflocker[selectlockertemp].password=-100;
	         }
	         numberoflocker[selectlockertemp].NumberOfThings=atoi(inmsg);
	      }
	      else
	      {
	         
	         write(connfd,wrongpassword,MAXLINE);
	         
	         
	         
	         
	      }
	    }
	    else if(numberoflocker[selectlockertemp].password != 0)
	    {  
	       while(1)
	       {
		       write(connfd,insertpassword,MAXLINE);
		       
		       
		       read(connfd,inmsg,MAXLINE);
		       key = atoi(inmsg);
		       if(numberoflocker[selectlockertemp].password != key)
		       {
			  write(connfd,wrongpassword,MAXLINE);
			  read(connfd,inmsg,MAXLINE);
			  passwordcnt=atoi(inmsg);
			  if(passwordcnt==3)
			  {
			     break;
			  }
			  
		       }
		       else
		       {
		          write(connfd,correctpassword,MAXLINE);
		          
		    
		          
		          write(connfd,question,MAXLINE);
		          
		          read(connfd,inmsg,MAXLINE);
		          printf("  %d",inmsg);
		          if(inmsg[0] == 'Y') 
		          { 
		             numberoflocker[selectlockertemp].password = 0;
		             numberoflocker[selectlockertemp].NumberOfThings=0;
		          }
		          
		          break;
		       }        
		}
	    }
   }
      
       
       close(connfd);
         exit (0);
   }  
   

   
   
   

 

