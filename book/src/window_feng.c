#include "awtk.h"
#include"stdio.h"


ret_t open_feng_window(char* jgcode, char* pageId)
{	
	char bookname[128]={'\0'};
	char page[128]={'\0'};
	
	widget_t* win = window_open("feng");
	getWtPageIdReadingInfo(jgcode, pageId,bookname,page); 
	
	widget_t* name = widget_lookup(win, "bookname", TRUE);
	widget_t* count_page= widget_lookup(win, "count_page", TRUE);
	widget_t* img= widget_lookup(win, "feng_img", TRUE);
	widget_set_text_utf8(name, bookname);
	printf("######%s#########",page);
	widget_set_text_utf8(count_page, page);
	image_set_image(img, "sb.jpg");
	return 0;
}
