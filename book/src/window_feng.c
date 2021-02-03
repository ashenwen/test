#include "awtk.h"
#include"stdio.h"
char booknum[128]={'\0'};
static ret_t on_new_click(void* ctx, event_t* e) {

	open_new_window("bbb", "ddd",booknum);
	return RET_OK;
}

ret_t open_feng_window(char* jgcode, char* book_id)
{	
	char bookname[128]={'\0'};
	char page[128]={'\0'};
	
	widget_t* win = window_open("feng");
	getWtPageIdReadingInfo(jgcode, book_id,bookname,page,booknum);
	widget_t* button=widget_lookup(win,"button",TRUE);
	widget_t* name = widget_lookup(win, "bookname", TRUE);
	widget_t* count_page= widget_lookup(win, "count_page", TRUE);
	widget_t* img= widget_lookup(win, "feng_img", TRUE);
	widget_set_text_utf8(name, bookname);
	printf("######%s#########",page);
	widget_set_text_utf8(count_page, page);
	image_set_image(img, "sb.jpg");
	widget_on(button,EVT_CLICK,on_new_click,win);
	return 0;
}
