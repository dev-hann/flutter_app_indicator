#include "flutter_app_indicator.h"

#include <dlfcn.h>
bool FlutterAppIndicator::init(const char* title,
    const char* iconPath,
    const char* label){
  bool ret =false;
  if(!initApi()){
    return false;
  }
  do{
  _app_indicator = _app_indicator_new(title,iconPath,APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
  _app_indicator_set_status(_app_indicator,APP_INDICATOR_STATUS_ACTIVE);
  set_label(label,label);
  ret = true;
  }while(false);
  return ret;
}

bool FlutterAppIndicator::set_menu(GtkWidget* menu){
  bool ret=false;
  do{
  gtk_widget_show_all(menu);
  _app_indicator_set_menu(_app_indicator,GTK_MENU(menu));
  ret=true;
  }while(false);
  return ret;
}

bool FlutterAppIndicator::set_label(const char* label,const char*guide){
  bool ret=false;
  do{
  _app_indicator_set_label(_app_indicator,label,label);
  ret = true;
  }while(false);
  return ret;

}

bool FlutterAppIndicator::set_icon(const char* iconPath,const char* iconDesc){
  bool ret = false;
  do{
    _app_indicator_set_icon(_app_indicator,iconPath,iconDesc);
    ret = true;
  }while(false);
  return ret;
}


bool FlutterAppIndicator::initApi(){
  void* handle = dlopen("libappindicator3.so.1", RTLD_LAZY);
  if (!handle) {
    return false;
    }
  _app_indicator_new = reinterpret_cast<app_inicator_new_fn>(dlsym(handle,"app_indicator_new"));
  _app_indicator_set_status=reinterpret_cast<app_indicator_set_status_fn>(dlsym(handle,"app_indicator_set_status"));
  _app_indicator_set_menu=reinterpret_cast<app_indicator_set_menu_fn>(dlsym(handle,"app_indicator_set_menu"));
  _app_indicator_set_label=reinterpret_cast<app_indicator_set_label_fn>(dlsym(handle,"app_indicator_set_label"));
  _app_indicator_set_icon=reinterpret_cast<app_indicator_set_icon_fn>(dlsym(handle,"app_indicator_set_icon_full"));
  if(!_app_indicator_new || !_app_indicator_set_status ||!_app_indicator_set_menu){
    return false;
  }
  return true;
}









