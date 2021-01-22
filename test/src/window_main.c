#include "awtk.h"
widget_t* label;
extern ret_t open_en_window(char* text);

static ret_t on_action_event(void* ctx, event_t* evt) {
	widget_t* target = WIDGET(evt->target);
	str_t str;
	str_init(&str, 0);
	str_from_wstr(&str, widget_get_text(target));
	open_en_window(str.str);
	str_reset(&str);
	return RET_OK;
}
static ret_t on_changing(void* ctx, event_t* evt) {
	widget_t* target = WIDGET(evt->target);
	widget_t* widget = WIDGET(ctx);
	widget_t* win1 = widget_get_window(widget);
	str_t str;
	str_init(&str, 0);
	str_from_wstr(&str, widget_get_text(target));
	label = widget_lookup(win1, "label", TRUE);
	widget_set_text_utf8(label, str.str);
	str_reset(&str);

	return RET_OK;
}


/**
 * 初始化
 */
ret_t application_init(void) {

  widget_t* system_bar = NULL;
  widget_t* system_bar_b = NULL;
  widget_t* win = window_open("home_page");

  widget_t* edit = widget_lookup(win, "edit", TRUE);
  
  widget_on(edit, EVT_IM_ACTION, on_action_event, NULL);
  widget_on(edit, EVT_VALUE_CHANGING, on_changing, win);

  return RET_OK;
}

/**
 * 退出
 */
ret_t application_exit(void) {
  log_debug("application_exit\n");
  return RET_OK;
}
