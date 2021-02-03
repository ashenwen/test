#include "awtk.h"
#include"stdio.h"
int page;
char code[32];
widget_t* left_en ;
widget_t* left_ch ;
widget_t* right_en;
widget_t* right_ch ;
widget_t* right_ch;
widget_t* win;
static ret_t on_l_click(void* ctx, event_t* e) {
	system("play l.mp3");
	return RET_OK;
}
static ret_t on_r_click(void* ctx, event_t* e) {
	system("play r.mp3");
	return RET_OK;
}
static ret_t on_next_click(void* ctx, event_t* e) {
	page+=1;
	printf("\n##############1##############\n");
	char page_str[24];
	char r_ch[1024]={'\0'};
	char l_ch[1024]={'\0'};
printf("\n################2############\n");
	sprintf(page_str,"%d",page);
	getWtPageResource(code, page_str,l_ch,r_ch);
	left_en = widget_lookup(win, "left", TRUE);
	left_ch = widget_lookup(win, "rich_text", TRUE);
	right_en = widget_lookup(win, "right", TRUE);
	right_ch = widget_lookup(win, "rich_text1", TRUE);
printf("\n##############3##############\n");
	image_set_image(left_en, "left.jpg");
	image_set_image(right_en, "right.jpg");
printf("\n############4################\n");
	//widget_set_text_utf8(left_en, l_en);
	widget_set_text_utf8(left_ch, l_ch);
printf("\n#############5###############\n");
	//widget_set_text_utf8(right_en, r_en);
	widget_set_text_utf8(right_ch, r_ch);
printf("\n############6################\n");
	return RET_OK;
}
static ret_t on_previous_click(void* ctx, event_t* e) {
	page-=1;
	char page_str[11];
	char r_ch[1024]={'\0'};
	char l_ch[1024]={'\0'};
	sprintf(page_str,"%d",page);
	getWtPageResource(code, page_str,l_ch,r_ch);
	image_set_image(left_en, "left.jpg");
	image_set_image(right_en, "right.jpg");
	//widget_set_text_utf8(left_en, l_en);
	widget_set_text_utf8(left_ch, l_ch);
	//widget_set_text_utf8(right_en, r_en);
	widget_set_text_utf8(right_ch, r_ch);
	return RET_OK;
}


ret_t open_book1_window(char* jgcode, char* pageId)
{	 page=atoi(pageId);
	sprintf(code,"%s",jgcode);
	char l_en[1024]={'\0'};
	char l_ch[1024]={'\0'};
	char r_en[1024]={'\0'};
	char r_ch[1024]={'\0'};
	 win = window_open("book1");
	getWtPageResource(jgcode, pageId,l_ch,r_ch);
	left_en = widget_lookup(win, "left", TRUE);
	left_ch = widget_lookup(win, "rich_text", TRUE);
	right_en = widget_lookup(win, "right", TRUE);
	right_ch = widget_lookup(win, "rich_text1", TRUE);
	widget_t* b_l = widget_lookup(win, "button", TRUE);
        widget_t* b_r = widget_lookup(win, "button1", TRUE);
	widget_t* next= widget_lookup(win, "button2", TRUE);
        widget_t* previous = widget_lookup(win, "button3", TRUE);
	image_set_image(left_en, "left.jpg");
	image_set_image(right_en, "right.jpg");
	//widget_set_text_utf8(left_en, l_en);
	widget_set_text_utf8(left_ch, l_ch);
	//widget_set_text_utf8(right_en, r_en);
	widget_set_text_utf8(right_ch, r_ch);	
	widget_on(b_l, EVT_CLICK, on_l_click, win);
	widget_on(b_r, EVT_CLICK, on_r_click, win);
	widget_on(next,EVT_CLICK,on_next_click,win);
	widget_on(previous,EVT_CLICK,on_previous_click,win);

}
