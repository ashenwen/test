#include "awtk.h"
#include "stdio.h"
//#include <arpa/inet.h>
//#include "unistd.h"
//#include <netdb.h>
//#include "sys/types.h"
//#include "sys/socket.h"
//#include <netinet/in.h>
#include "cJSON.h"
//#include "cJSON.c"
unsigned char *base64_encode(unsigned char *str)  
{  
    long len;  
    long str_len;  
    unsigned char *res;  
    int i,j;  
//����base64�����  
    unsigned char *base64_table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  
  
//���㾭��base64�������ַ�������  
    str_len=strlen(str);  
    if(str_len % 3 == 0)  
        len=str_len/3*4;  
    else  
        len=(str_len/3+1)*4;  
  
    res=malloc(sizeof(unsigned char)*len+1);  
    res[len]='\0';  
  
//��3��8λ�ַ�Ϊһ����б���  
    for(i=0,j=0;i<len-2;j+=3,i+=4)  
    {  
        res[i]=base64_table[str[j]>>2]; //ȡ����һ���ַ���ǰ6λ���ҳ���Ӧ�Ľ���ַ�  
        res[i+1]=base64_table[(str[j]&0x3)<<4 | (str[j+1]>>4)]; //����һ���ַ��ĺ�λ��ڶ����ַ���ǰ4λ������ϲ��ҵ���Ӧ�Ľ���ַ�  
        res[i+2]=base64_table[(str[j+1]&0xf)<<2 | (str[j+2]>>6)]; //���ڶ����ַ��ĺ�4λ��������ַ���ǰ2λ��ϲ��ҳ���Ӧ�Ľ���ַ�  
        res[i+3]=base64_table[str[j+2]&0x3f]; //ȡ���������ַ��ĺ�6λ���ҳ�����ַ�  
    }  
  
    switch(str_len % 3)  
    {  
        case 1:  
            res[i-2]='=';  
            res[i-1]='=';  
            break;  
        case 2:  
            res[i-1]='=';  
            break;  
    }  
  
    return res;  
}  
  
unsigned char *base64_decode(unsigned char *code)  
{  
//����base64�����ַ��ҵ���Ӧ��ʮ��������  
    int table[]={0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,62,0,0,0,
    		 63,52,53,54,55,56,57,58,
    		 59,60,61,0,0,0,0,0,0,0,0,
    		 1,2,3,4,5,6,7,8,9,10,11,12,
    		 13,14,15,16,17,18,19,20,21,
    		 22,23,24,25,0,0,0,0,0,0,26,
    		 27,28,29,30,31,32,33,34,35,
    		 36,37,38,39,40,41,42,43,44,
    		 45,46,47,48,49,50,51
    	       };  
    long len;  
    long str_len;  
    unsigned char *res;  
    int i,j;  
  
//����������ַ�������  
    len=strlen(code);  
//�жϱ������ַ������Ƿ���=  
    if(strstr(code,"=="))  
        str_len=len/4*3-2;  
    else if(strstr(code,"="))  
        str_len=len/4*3-1;  
    else  
        str_len=len/4*3;  
  
    res=malloc(sizeof(unsigned char)*str_len+1);  
    res[str_len]='\0';  
  
//��4���ַ�Ϊһλ���н���  
    for(i=0,j=0;i < len-2;j+=3,i+=4)  
    {  
        res[j]=((unsigned char)table[code[i]])<<2 | (((unsigned char)table[code[i+1]])>>4); //ȡ����һ���ַ���Ӧbase64���ʮ��������ǰ6λ��ڶ����ַ���Ӧbase64���ʮ�������ĺ�2λ�������  
        res[j+1]=(((unsigned char)table[code[i+1]])<<4) | (((unsigned char)table[code[i+2]])>>2); //ȡ���ڶ����ַ���Ӧbase64���ʮ�������ĺ�4λ��������ַ���Ӧbas464���ʮ�������ĺ�4λ�������  
        res[j+2]=(((unsigned char)table[code[i+2]])<<6) | ((unsigned char)table[code[i+3]]); //ȡ���������ַ���Ӧbase64���ʮ�������ĺ�2λ���4���ַ��������  
    }  
  
    return res;  
  
}
int setstr(char* rep, char* temp)
{
	char* p = strstr(rep, "data");
		p+=7;

		while ((*p) != '\"')
		{
			printf("%c",*p);
			*temp++ = *p++;
			
		}
		*temp = '\0';
		printf("\r\n");
	



}

int get(char *msg,char *data,char *sign)
{	
	char buff[4096] = { '\0' };
	socket_init();
	/*int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(80);
inet_pton(AF_INET, "47.106.26.194", &serveraddr.sin_addr.s_addr);*/
	int sockfd =tcp_connect ("47.106.26.194",80);

memset(buff, 0, sizeof(buff));

snprintf(buff, sizeof(buff) - 1,

	"POST /php/dictionary/dictionary.api/dictionary_ainfo?data=%s&sign=%s HTTP/1.1\r\n"

	"Host:pm.abc5.cn\r\n"

	"x-token:eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJwYWQuaWV4dWUxMDAuY29tIiwiYXVkIjoiYXVkIiwiaWF0IjoxNjEwNzgxODg1LCJuYmYiOjE2MTA3ODE4OTUsImV4cCI6MTc2ODQ2MTg4NSwiZGF0YSI6eyJ1c2VyaWQiOjF9fQ.QwqJGwzsJOI3Xbc4xWjBMTmHCc-qdK-wCP2L1wSX8pc\r\n"
	"\r\n",data,sign



);
 // if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)  
       // printf("connect error\n");
	if(write(sockfd, buff, strlen(buff))!=strlen(buff)){printf("erro");}
	printf("\r\nbuff#############\r\n%s#############\r\n",buff);
	char* readbuff=(char*)malloc(1024*16);
	char * read_p=readbuff;	
	memset(read_p, 0, 1024*3* sizeof(char));
	//socket_wait_for_data (sockfd,1000);
	size_t size;
	int i=1;
	while( i !=0)
	{	memset(read_p, 0,  1024*3*sizeof(char));
		i=read(sockfd, read_p, sizeof(char));
		read_p+=i;
	}
	printf("readbuff#################\r\n%send#############\r\n",readbuff);
	//char* ptr=(char*)malloc(4300);
	char*p;
	printf("#################erro1#############\r\n");
 	p= strstr(readbuff, "data");
	printf("#################erro2#############\r\n");
	free(readbuff);
	printf("#################erro3#############\r\n");
	p+=7;
	printf("#################erro4#############\r\n");	
	//printf("#################3%s#############",buff);


	
	while ((*p) != '\"')
		{

			if ( '\r'==*p )
			{
					p+=1;

				for(int j=0;j<16;j++)
						
					{	if ('\r'==*p) 
						{	p+=2;
							
							break;
						}
					
						p++;
					}	
					
			}
			
			
			//if(*p=='\n'){p++;*msg++='#';}
			//else if(*p=='\r'){p++;*msg++='$';}
			else{*msg++ = *p++;}		
		}
		*msg = '\0';
		printf("#################erro5#############\r\n");
	close(sockfd);
	
	//free(ptr);
	return 0;
}
/*void getdata(char *data)
{
char c[2048]={'\0'};

get(c);

 unsigned char *buf =NULL;

buf = base64_decode(c);
cJSON * json=cJSON_Parse(buf);

data=cJSON_Print(json);


}*/

/*int main( void)
{
char c[2048]={'\0'};
get(c);
 unsigned char *buf =NULL;
buf = base64_decode(c);
//printf("%s\n",buf); 
cJSON * json=cJSON_Parse(buf);
char * b =cJSON_Print(json);
cJSON * value=cJSON_GetObjectItem(json,"data");
char * d=cJSON_Print(value);
printf("data:%s\n",b);
return 0;
}*/

