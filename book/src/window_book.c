#include "awtk.h"
#include"stdio.h"

static ret_t on_l_click(void* ctx, event_t* e) {
	system("play l.mp3");
	return RET_OK;
}
static ret_t on_r_click(void* ctx, event_t* e) {
	system("play r.mp3");
	return RET_OK;
}

ret_t open_book_window(char* jgcode, char* pageId)
{
	char l_en[1024]={'\0'};
	char l_ch[1024]={'\0'};
	char r_en[1024]={'\0'};
	char r_ch[1024]={'\0'};
	widget_t* win = window_open("book");
	getWtPageResource(jgcode, pageId,l_en,l_ch,r_en,r_ch);
	widget_t* left_en = widget_lookup(win, "left_en", TRUE);
	widget_t* left_ch = widget_lookup(win, "left_ch", TRUE);
	widget_t* right_en = widget_lookup(win, "right_en", TRUE);
	widget_t* right_ch = widget_lookup(win, "right_ch", TRUE);
	widget_t* b_l = widget_lookup(win, "button", TRUE);
        widget_t* b_r = widget_lookup(win, "button1", TRUE);
	widget_set_text_utf8(left_en, l_en);
	widget_set_text_utf8(left_ch, l_ch);
	widget_set_text_utf8(right_en, r_en);
	widget_set_text_utf8(right_ch, r_ch);	
	widget_on(b_l, EVT_CLICK, on_l_click, win);
	widget_on(b_r, EVT_CLICK, on_r_click, win);

}
