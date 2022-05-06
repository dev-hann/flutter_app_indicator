#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>


typedef AppIndicator* (*app_inicator_new_fn)(const gchar*, const gchar*, AppIndicatorCategory);

typedef void (*app_indicator_set_status_fn)(AppIndicator*, AppIndicatorStatus);

typedef void (*app_indicator_set_menu_fn)(AppIndicator*, GtkMenu*);

typedef void (*app_indicator_set_label_fn)(AppIndicator*,const gchar*, const gchar*);

typedef void (*app_indicator_set_icon_fn)(AppIndicator*,const gchar*,const gchar*);


class FlutterAppIndicator{
 public:
  bool init(const char* title,const char* iconPath,const char* label);

  bool set_label(const char* label,const char* guide);
  
  bool set_icon(const char* iconPath,const char* iconDesc);
  
  bool set_menu(GtkWidget* menu);

 protected:
  bool initApi();

 protected:
  app_inicator_new_fn _app_indicator_new = nullptr;
  app_indicator_set_status_fn _app_indicator_set_status =nullptr;
  app_indicator_set_menu_fn _app_indicator_set_menu =nullptr;
  app_indicator_set_label_fn _app_indicator_set_label=nullptr;
  app_indicator_set_icon_fn _app_indicator_set_icon=nullptr;
  AppIndicator* _app_indicator=nullptr;

};

