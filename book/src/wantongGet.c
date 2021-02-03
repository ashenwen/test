#include "awtk.h"
#include "cJSON.h"
#include"stdio.h"

unsigned char* base64_encode(unsigned char* str)
{
    long len;
    long str_len;
    unsigned char* res;
    int i, j;
    //定义base64编码表  
    unsigned char* base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    //计算经过base64编码后的字符串长度  
    str_len = strlen(str);
    if (str_len % 3 == 0)
        len = str_len / 3 * 4;
    else
        len = (str_len / 3 + 1) * 4;
    res = malloc(sizeof(unsigned char) * len + 1);
    res[len] = '\0';
    //以3个8位字符为一组进行编码  
    for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
    {
        res[i] = base64_table[str[j] >> 2]; //取出第一个字符的前6位并找出对应的结果字符  
        res[i + 1] = base64_table[(str[j] & 0x3) << 4 | (str[j + 1] >> 4)]; //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符  
        res[i + 2] = base64_table[(str[j + 1] & 0xf) << 2 | (str[j + 2] >> 6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符  
        res[i + 3] = base64_table[str[j + 2] & 0x3f]; //取出第三个字符的后6位并找出结果字符  
    }
    switch (str_len % 3)
    {
    case 1:
        res[i - 2] = '=';
        res[i - 1] = '=';
        break;
    case 2:
        res[i - 1] = '=';
        break;
    }
    return res;
}

unsigned char* base64_decode(unsigned char* code)
{
    //根据base64表，以字符找到对应的十进制数据  
    int table[] = { 0,0,0,0,0,0,0,0,0,0,0,0,
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
    unsigned char* res;
    int i, j;
    //计算解码后的字符串长度  
    len = strlen(code);
    //判断编码后的字符串后是否有=  
    if (strstr(code, "=="))
        str_len = len / 4 * 3 - 2;
    else if (strstr(code, "="))
        str_len = len / 4 * 3 - 1;
    else
        str_len = len / 4 * 3;
    res = malloc(sizeof(unsigned char) * str_len + 1);
    res[str_len] = '\0';
    //以4个字符为一位进行解码  
    for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
    {
        res[j] = ((unsigned char)table[code[i]]) << 2 | (((unsigned char)table[code[i + 1]]) >> 4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合  
        res[j + 1] = (((unsigned char)table[code[i + 1]]) << 4) | (((unsigned char)table[code[i + 2]]) >> 2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合  
        res[j + 2] = (((unsigned char)table[code[i + 2]]) << 6) | ((unsigned char)table[code[i + 3]]); //取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合  
    }
    return res;



}

void getmp3(char* url,int j)
{
    int len1;
    socket_init();
    char buff[4096] = { '\0' };
    int sockfd1 = tcp_connect("readbook.koo6.cn", 80);

    memset(buff, 0, sizeof(buff));

    snprintf(buff, sizeof(buff) - 1,

        "GET %s HTTP/1.1\r\n"

        "Accept: */*\r\n"
        "Host:readbook.koo6.cn\r\n"
        "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"
        "Content-Type:application/download\r\n"
        "\r\n", url
    );
    if (write(sockfd1, buff, strlen(buff)) != strlen(buff)) { printf("erro"); }
    FILE* fp1 = fdopen(sockfd1, "r");
    char* img = (char*)malloc(1024 * 600);
      //memset(img, 0, 600*1024*sizeof(char));
    char* imglen = NULL;
    while (fgets(img, 1024, fp1))
    {
        printf("%s",img);
        if (!strcmp(img, "\r\n"))
        {
            break;   /* 头解析正常 */
        }

        if (imglen = strstr(img, "Content-Length"))
        {
            imglen = strchr(imglen, ':');
            imglen += 2;     // 跳过冒号和后面的空格
            len1 = atoi(imglen);

        }
    }
    memset(img, 0, len1* sizeof(char));
    fread(img, sizeof(char), len1, fp1);
    close(fp1);
    socket_close(sockfd1);
 /*   if(j==0)
{
 file_write("l.mp3", img, len1 * sizeof(char));
}else if(j==1)
{
file_write("r.mp3", img, len1 * sizeof(char));
}
*/
char mp3name[16];
sprintf(mp3name,"%d.mp3",j);
file_write(mp3name, img, len1 * sizeof(char));
    free(img);
printf("\n###@@@@@@@@###########\n");

}





void getimg(char* url,int type)
{
    int len1;
    socket_init();
    char buff[4096] = { '\0' };

    int sockfd1 = tcp_connect("readbook.koo6.cn", 80);

    memset(buff, 0, sizeof(buff));

    snprintf(buff, sizeof(buff) - 1,

        "GET %s HTTP/1.1\r\n"

        "Accept: */*\r\n"
        "Host:readbook.koo6.cn\r\n"
        "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"
        "Content-Type:application/download\r\n"
        "\r\n", url
    );
    if (write(sockfd1, buff, strlen(buff)) != strlen(buff)) { printf("erro"); }
    FILE* fp1 = fdopen(sockfd1, "r");
    char* img = (char*)malloc(1024 * 300);
    char* imglen = NULL;
    while (fgets(img, 1024, fp1))
    {
        printf("%s",img);
        if (!strcmp(img, "\r\n"))
        {
            break;   /* 头解析正常 */
        }

        if (imglen = strstr(img, "Content-Length"))
        {
            imglen = strchr(imglen, ':');
            imglen += 2;     // 跳过冒号和后面的空格
            len1 = atoi(imglen);

        }
    }
    memset(img, 0, len1* sizeof(char));
    fread(img, sizeof(char), len1, fp1);
    close(fp1);
    socket_close(sockfd1);
    if(type==0){
	file_write("res/assets/default/raw/images/xx/sb.jpg", img, len1 * sizeof(char));
		}
    else if(type==1){
	file_write("res/assets/default/raw/images/xx/left.jpg", img, len1 * sizeof(char));
		}
    else if(type==2){
	file_write("res/assets/default/raw/images/xx/right.jpg", img, len1 * sizeof(char));
		}
    free(img);

}



void getWtPageIdReadingInfo(char *jgcode, char *book_id,char* booknamestr,char * count_pagestr)
{
    char* jgcode64 = base64_encode(jgcode);
    char* pageId64 = base64_encode(book_id);
    int len;
 char buff[4096] = { '\0' };
    int sockfd = tcp_connect("yunstudy.koo6.cn", 80);
   
    memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff) - 1,
        "GET /Apis/wantongGet/getWtPageIdReadingInfo?jgcode=%s&book_id=%s HTTP/1.1\r\n"
        "Accept: */*\r\n"
        "Host:yunstudy.koo6.cn\r\n"
        "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"
        "Content-Type:application/download\r\n"
        "\r\n", jgcode64, pageId64
    );
    if (write(sockfd, buff, strlen(buff)) != strlen(buff)) { printf("erro"); }
    FILE* fp = fdopen(sockfd, "r");
    char* buffer = (char*)malloc(1024 * 300);

    char* p = NULL;
    while (fgets(buffer, 1024, fp))
    {
        printf("%s", buffer);
        if (!strcmp(buffer, "\r\n"))
        {
            break;   /* 头解析正常 */
        }
        if (p = strstr(buffer, "Content-Length"))
        {
            p = strchr(p, ':');
            p += 2;     // 跳过冒号和后面的空格
            len = atoi(p);
        }
    }
	
    memset(buffer, 0, len * sizeof(char));

    fread(buffer, sizeof(char), len, fp);

    close(fp);

    socket_close(sockfd);

    cJSON* json = cJSON_Parse(buffer);

    cJSON* result = cJSON_GetObjectItem(json, "result");

    cJSON* book = cJSON_GetObjectItem(result, "books");
	cJSON* bookname= cJSON_GetObjectItem(book, "bookname");
	cJSON* count_page= cJSON_GetObjectItem(book, "count_page");
	cJSON* feng_img= cJSON_GetObjectItem(book, "feng_img");
	sprintf(booknamestr,"%s",bookname->valuestring);
	sprintf(count_pagestr,"%s",count_page->valuestring);
  	char *p_img=strstr(feng_img->valuestring,"cn/");
	p_img+=2;
	printf("%s",p_img);
    	getimg(p_img,0);
    free(buffer);
}

void getWtPageResource(char *jgcode,char *pageId,char*l_ch,char*r_ch)
{

    char* jgcode64 = base64_encode(jgcode);
    char* pageId64 = base64_encode(pageId);
	printf("jgcode:  %s\njgcode64=  %s\npageId=  %s\npageId64=  %s\n#####",jgcode,jgcode64,pageId,pageId64);
    int len;
 char buff[4096] = { '\0' };
    int sockfd = tcp_connect("yunstudy.koo6.cn", 80);
   
    memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff) - 1,
        "GET /Apis/wantongGet/getWtPageResource?jgcode=%s&pageId=%s HTTP/1.1\r\n"
        "Accept: */*\r\n"
        "Host:yunstudy.koo6.cn\r\n"
        "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"

        "Content-Type:application/download\r\n"
        "\r\n", jgcode64, pageId64
    );
	
    if (write(sockfd, buff, strlen(buff)) != strlen(buff)) { printf("erro"); }
    FILE* fp = fdopen(sockfd, "r");
    char* buffer = (char*)malloc(1024 * 300);

    char* p = NULL;
    while (fgets(buffer, 1024, fp))
    {
        printf("%s", buffer);
        if (!strcmp(buffer, "\r\n"))
        {
            break;   /* 头解析正常 */
        }
        if (p = strstr(buffer, "Content-Length"))
        {
            p = strchr(p, ':');
            p += 2;     // 跳过冒号和后面的空格
            len = atoi(p);
        }
    }
	
    memset(buffer, 0, len * sizeof(char));

    fread(buffer, sizeof(char), len, fp);

    close(fp);
    socket_close(sockfd);

    cJSON* json = cJSON_Parse(buffer);

    cJSON* result = cJSON_GetObjectItem(json, "result");
    cJSON* left = cJSON_GetObjectItem(result, "left");
    cJSON* right = cJSON_GetObjectItem(result, "right");
    cJSON* left_inimg = cJSON_GetObjectItem(result, "left_inimg");
    cJSON* right_inimg = cJSON_GetObjectItem(result, "right_inimg");
    cJSON* left_text = cJSON_GetObjectItem(result, "left_text");
    cJSON* right_text = cJSON_GetObjectItem(result, "right_text");
    cJSON* right_en_text = cJSON_GetObjectItem(right_text, "englishtext");
    cJSON* right_ch_text = cJSON_GetObjectItem(right_text, "chinatext");
    cJSON* left_en_text= cJSON_GetObjectItem(left_text, "englishtext");
    cJSON* left_ch_text = cJSON_GetObjectItem(left_text, "chinatext");
	
  //  sprintf(l_en,"%s",cJSON_Print( left_en_text));
    sprintf(l_ch,"%s",cJSON_Print( left_ch_text));
  //  sprintf(r_en,"%s",cJSON_Print( right_en_text));
    sprintf(r_ch,"%s",cJSON_Print( right_ch_text));
    char *l_url=strstr(left->valuestring,"cn/");
	l_url+=2;
    char *r_url=strstr(right->valuestring,"cn/");
	r_url+=2;
	getmp3(l_url,0);
	getmp3(r_url,1);
 
	printf("\n###1###########\n");
    char *l_img=strstr(left_inimg->valuestring,"cn/");
printf("\n############2##\n");
	l_img+=2;
    char *r_img=strstr(right_inimg->valuestring,"cn/");
printf("\n#############3#\n");
	r_img+=2;
	getimg(l_img,1);
	getimg(r_img,2);
	 free(buffer);
}


cJSON *getReadingPageList(char *page)
{	int chunked_flag=0;
	char* page64 = base64_encode(page);
printf("\npagd=  %s\npage64=  %s\n#####",page,page64);
    //char* jgcode64 = base64_encode(jgcode);
    //char* pageId64 = base64_encode(pageId);
	//printf("jgcode:  %s\njgcode64=  %s\npageId=  %s\npageId64=  %s\n#####",jgcode,jgcode64,pageId,pageId64);
    int len;
 char buff[4096] = { '\0' };
    int sockfd = tcp_connect("yunstudy.koo6.cn", 80);
   
    memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff) - 1,
        "GET /Apis/wantongGet/getReadingPageList?jgcode=NDk0OTUwMzc0OTQ5NTAzNzQ5NDk1MDM3&booknum=Y3RyZ2h5YnRyeG5hbnJzbQ==&page=%s HTTP/1.1\r\n"
        "Accept: */*\r\n"
        "Host:yunstudy.koo6.cn\r\n"
        "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"
        "Content-Type:application/download\r\n"
        "\r\n",page64
    );
	
    if (write(sockfd, buff, strlen(buff)) != strlen(buff)) { printf("erro"); }
    FILE* fp = fdopen(sockfd, "r");
    char* buffer = (char*)malloc(1024 * 600);

    char* p = NULL;
    while (fgets(buffer, 1024, fp))
    {
        printf("%s", buffer);
        if (!strcmp(buffer, "\r\n"))
        {
            break;   /* 头解析正常 */
        }
        if (p = strstr(buffer, "Content-Length"))
        {
            p = strchr(p, ':');
            p += 2;     // 跳过冒号和后面的空格
            len = atoi(p);
        }
	if(p = strstr(buffer, "Transfer-Encoding"))
	{

	     if(strstr(buffer, "chunked"))
            {
                chunked_flag = 1;
            }			
	}
    }
    if(chunked_flag==0)
	{
    		memset(buffer, 0, len * sizeof(char));

    		fread(buffer, sizeof(char), len, fp);
	}
    else if(chunked_flag==1)
	{	memset(buffer, 0, 1024*5* sizeof(char));
		int part_len=1;
		char *part = (char*)malloc(1024 * 300);
		char *part_buffer=buffer;
		while(part_len>0)
			{
				fgets(part,1024,fp);
				part_len = strtol(part, NULL, 16);
				printf("\n%d\n",part_len);
				fread(part_buffer, sizeof(char), part_len, fp);
				printf("\n%s\n",buffer);
				part_buffer+=part_len;
				fread(part, sizeof(char), 2, fp);
			}
		free(part);			
	}

    close(fp);
    socket_close(sockfd);

    cJSON* json = cJSON_Parse(buffer);

    cJSON* result = cJSON_GetObjectItem(json, "result");
    cJSON*  english_radio = cJSON_GetObjectItem(result,  "english_radio");
   
	cJSON* radio=cJSON_GetObjectItem(english_radio,page);
	int size=cJSON_GetArraySize(radio);
	for(int i=0;i<size;i++)
	{
		cJSON* mp3=cJSON_GetArrayItem(radio, i);
		char *mp3url=mp3->valuestring;
		mp3url+=2;
		getmp3(mp3url,i);
		
	}
	printf("\n######11111111######\n");
	 free(buffer);
return result;
}



