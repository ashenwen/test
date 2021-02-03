#include "awtk.h"

/**
 * 初始化
 */
ret_t application_init(void) {

  widget_t* system_bar = NULL;
  widget_t* system_bar_b = NULL;
  widget_t* win = window_open("home_page");
  //open_feng_window("494950374949503749495037","82818");
  open_new_window("494950374949503749495037","1568898");
  return RET_OK;
}

/**
 * 退出
 */
ret_t application_exit(void) {
  log_debug("application_exit\n");
  file_remove("res/assets/default/raw/images/xx/sb.jpg");
  system("find . -name \"*.mp3\"  | xargs rm -f");	
  return RET_OK;
}
