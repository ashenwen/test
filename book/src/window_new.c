#include "awtk.h"
#include "cJSON.h"
#include"stdio.h"
widget_t* view;
widget_t* view1;
widget_t* win;
int i=0;
int page;
char booknum1[128]={'\0'};


static ret_t init_widget(void* ctx, const void* iter) 
{
widget_t* button=WIDGET(ctx);
widget_t* widget=WIDGET(iter);
	str_t str;
	str_init(&str, 0);
str_from_wstr(&str, widget_get_text(widget));
	str_t str1;
	str_init(&str1, 0);
str_from_wstr(&str1, widget_get_text(button));
if(str.str!=NULL)
{
	if(tk_str_cmp(str.str,str1.str)==0)
		{
			char mp3[16];
			sprintf(mp3,"play %d.mp3",i-1);
			system(mp3);					
		}
}
i++;
str_reset(&str1);
str_reset(&str);
return RET_OK;
}

static ret_t on_r_click(void* ctx, event_t* e) {
	widget_t* target = WIDGET(e->target);
	i=0;
	widget_foreach(view, init_widget, target);

	return RET_OK;
}

void viewinit(char* page,char*booknum)
{
 cJSON* result=getReadingPageList(page,booknum);
	cJSON* englishtext=cJSON_GetObjectItem(result, "englishtext");
	cJSON* chinatext=cJSON_GetObjectItem(result, "chinatext");
	cJSON* en=cJSON_GetObjectItem(englishtext,page);
	cJSON* ch=cJSON_GetObjectItem(chinatext,page);
	int size=cJSON_GetArraySize(en);
	for(int i=0;i<size;i++)
	{
		cJSON* mp3=cJSON_GetArrayItem(en, i);
		char *mp3url=mp3->valuestring;
		widget_t* label = button_create(view, NULL, NULL, 50,20);
		widget_set_text_utf8(label, mp3url);
		widget_on(label,EVT_CLICK,on_r_click,view);			
	}
	int size1=cJSON_GetArraySize(ch);
	for(int i=0;i<size1;i++)
	{
		cJSON* mp3=cJSON_GetArrayItem(ch, i);
		char *mp3url=mp3->valuestring;
		widget_t* label = button_create(view1, NULL, NULL, 50,20);
		widget_set_text_utf8(label, mp3url);
				
	}
cJSON_Delete(result);
}
static ret_t on_next_click(void* ctx, event_t* e) {
page+=1;
char page_str[24];
sprintf(page_str,"p%03d",page);
widget_destroy_children(view);
widget_destroy_children(view1);
viewinit(page_str,booknum1);
return RET_OK;
}

static ret_t on_previous_click(void* ctx, event_t* e) {
if(page>=1)
{
page-=1;
char page_str[24];
sprintf(page_str,"p%03d",page);
widget_destroy_children(view);
widget_destroy_children(view1);
viewinit(page_str,booknum1);
}
return RET_OK;
}




ret_t open_new_window(char* jgcode, char* pageId,char*booknum)
{	
win = window_open("new");
view=widget_lookup(win,"view",TRUE);
view1=widget_lookup(win,"view1",TRUE);
sprintf(booknum1,"%s",booknum);
	widget_t* previous= widget_lookup(win, "button", TRUE);
        widget_t* next = widget_lookup(win, "button1", TRUE);
	widget_on(next,EVT_CLICK,on_next_click,win);
	widget_on(previous,EVT_CLICK,on_previous_click,win);
viewinit("p001",booknum1);

}
