#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
int main()
{
 int i,s;

 struct addrinfo hints,*res,*p;

 memset(&hints,0,sizeof (hints));

 hints.ai_family=AF_INET6;
 hints.ai_socktype=SOCK_STREAM;

 i=getaddrinfo("fe80::a00:27ff:fe64:7d33%eth4","7002",&hints,&res);//because the system in which server code is has IPv6 address fe80::20c:29ff:fe60:7593

 if(i!=0)
  { printf("\n Fail 1 \n"); return 0;}

	for(p=res;p!=NULL;p=p->ai_next)
	 { 
	   if((s=socket(p->ai_family,p->ai_socktype,p->ai_protocol))==-1)
		{perror("socket"); continue;}

	   if(connect(s,p->ai_addr,p->ai_addrlen)==-1)
		{ close(s); perror("connect"); continue;}

	   break;
	 }

 if(p==NULL)
 {
  fprintf(stderr,"failed to connect\n");
   return 0;
  }

 close(s);
 return 0;
}
