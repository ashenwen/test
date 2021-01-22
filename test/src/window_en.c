#include "awtk.h"#include"stdio.h"#include "cJSON.h"#include "md5.h"#include <iconv.h>//extern int get(char* text)extern widget_t* button_view = NULL;extern widget_t* win = NULL;extern widget_t* rich_text = NULL;/** * 获取指定key的值 */void getstr(char* str, char* buff, char* key){	printf("#################erro14#############\r\n");	char* p = strstr(buff, key);	printf("#################erro15#############\r\n");	p += 4 + strlen(key);	printf("%s", p);	while (*p != '\"')	{		if (*p == '\\')		{			p += 3;		}		else { *str++ = *p++; }	}	*str = '\0';	printf("#################erro16#############\r\n");	printf("#################erro17#############\r\n");	printf("#################erro18#############\r\n");}/***调用api获取数据*/void getinterpret(char* text) {	widget_t* label = widget_lookup(win, "rich_text", TRUE);	char data[128];	char sign[128];	char md5sign[32];	//sprintf(data,"abc");	sprintf(data, "{\"name\":\"%s\",\"type\":2}", text);	sprintf(sign, "%s,2upduttktmnzh6ytb9fpey4ymvgzwtmoz", text);	char* data64 = NULL;	data64 = base64_encode(data);	unsigned char decrypt[16];	MD5_CTX md5;	MD5Init(&md5);	MD5Update(&md5, sign, strlen((char*)sign));	MD5Final(&md5, decrypt);	sprintf(md5sign, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", decrypt[0], decrypt[1], decrypt[2], decrypt[3], decrypt[4], decrypt[5], decrypt[6], decrypt[7], decrypt[8], decrypt[9], decrypt[10], decrypt[11], decrypt[12], decrypt[13], decrypt[14], decrypt[15]);	char* buff = (char*)malloc(1024 * 16);	get(buff, data64, md5sign);	char* buf = NULL;	// getdata (buf);	buf = base64_decode(buff);	printf("#################erro6#############\r\n");	printf("buff#################\r\n%s\r\n####################\r\n", buff);	printf("#################erro7#############\r\n");	//printf("%s\n",buf); 	cJSON* json = cJSON_Parse(buf);	//char * b =cJSON_Print(json);	cJSON* json_data = cJSON_GetObjectItem(json, "data");	printf("#################erro8#############\r\n");	cJSON* json_list = cJSON_GetObjectItem(json_data, "list");	printf("#################erro9#############\r\n");	char* list = cJSON_Print(json_list);	printf("#################erro10%s#############\r\n", list);	char* interpret = (char*)malloc(1024 * 16);	printf("#################erro11#############\r\n");	getstr(interpret, list, "interpret");	printf("#################erro12#############\r\n");	printf("%s", interpret);	printf("#################erro25#############\r\n");	widget_set_text_utf8(label, interpret);	printf("#################erro26#############\r\n");	free(buff);	free(interpret);	return 0;}/***按钮事件*/static ret_t on_button_click(void* ctx, event_t* e) {	widget_t* target = WIDGET(e->target);	str_t str;	str_init(&str, 0);	str_from_wstr(&str, widget_get_text(target));	//widget_set_text_utf8(rich_text, str.str);	getinterpret(str.str);	str_reset(&str);	return RET_OK;}/***分割英语句子单词*/void split(char* text){	int p = 0;	char* buf = (char*)malloc(1024);	char* str = buf;	for (int i = 0; i < strlen(text); i++)	{		*(str + p) = *(text + i);		p++;		if (*(text + i + 1) == ',' || *(text + i + 1) == '.' || *(text + i + 1) == '!' || *(text + i + 1) == '?' || *(text + i + 1) == ' '|| i == strlen(text) - 1)		{			widget_t* label = button_create(button_view, NULL, NULL, 37, 31);			*(str + p) = '\0';			widget_set_text_utf8(label, str);			widget_on(label, EVT_CLICK, on_button_click, button_view);			p = 0;			i++;		}	}	free(buf);}/***界面入口*/ret_t open_en_window(char* intext){	win = window_open("en");	rich_text = widget_lookup(win, "rich_text", TRUE);	button_view = widget_lookup(win, "button_view", TRUE);	printf("#################1%s#############\r\n", intext);	split(intext);	printf("#################2#############\r\n");}