#include "include/flutter_app_indicator/flutter_app_indicator_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#include "flutter_app_indicator.h"

#define FLUTTER_APP_INDICATOR_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), flutter_app_indicator_plugin_get_type(), \
                              FlutterAppIndicatorPlugin))

const static char init[]="init";
const static char icon[]="icon";
const static char label[]="label";
const static char menu[]="menu";
const static char title[]="title";

const static int64_t menu_item_type_index=0;
const static int64_t menu_list_type_index=1;
const static int64_t menu_divider_type_index=2;

struct _FlutterAppIndicatorPlugin {
  GObject parent_instance;
  FlutterAppIndicator app_indicator;
  FlMethodChannel* channel;
};

G_DEFINE_TYPE(FlutterAppIndicatorPlugin, flutter_app_indicator_plugin, g_object_get_type())
  FlutterAppIndicatorPlugin* g_plugin = nullptr;
  static void menu_callback(GtkMenuItem* item,gpointer user_data){

    int64_t hash_code = GPOINTER_TO_INT(user_data);
    g_autoptr(FlValue) result = fl_value_new_int(hash_code);
    fl_method_channel_invoke_method(
        g_plugin->channel,
        "menuOnTap",
        result,
        nullptr,
        nullptr,
        nullptr);

  }
static GtkWidget* menu_item(FlValue* args);
static GtkWidget* fl_value_to_menu(FlValue* args){
  GtkWidget* menu= gtk_menu_new();
  for(size_t i=0;i<fl_value_get_length(args);++i){
    GtkWidget* item = menu_item(fl_value_get_list_value(args,i));
      if(item!=nullptr){
        gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
      }
  }
  return menu;
}
static GtkWidget* menu_item(FlValue* args){
    FlValue* type_value = fl_value_lookup_string(args,"typeIndex");
    if(type_value==nullptr 
        ){
      return nullptr;
    }
    GtkWidget* item = nullptr;
    
    const int64_t index = fl_value_get_int(type_value);
    if(index==menu_divider_type_index){
      item = gtk_separator_menu_item_new();
    }else if(index==menu_item_type_index){
      FlValue* label_value = fl_value_lookup_string(args, "name");
      const gchar* label =fl_value_get_string(label_value);
      item = gtk_menu_item_new_with_label(label);
      FlValue* hash_code = fl_value_lookup_string(args,"hashCode");
      g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(menu_callback),
          GINT_TO_POINTER(fl_value_get_int(hash_code)));
    }else if(index==menu_list_type_index){
      FlValue* label_value = fl_value_lookup_string(args, "name");
      const gchar* label =fl_value_get_string(label_value);
      item = gtk_menu_item_new_with_label(label);
      GtkWidget* sub_menu= fl_value_to_menu(fl_value_lookup_string(args,"itemList"));
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(item),sub_menu);
    }
    return item;
}
// Called when a method call is received from Flutter.
static void flutter_app_indicator_plugin_handle_method_call(
    FlutterAppIndicatorPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;
  const gchar* method = fl_method_call_get_name(method_call);
  FlValue* args = fl_method_call_get_args(method_call);
  g_autoptr(FlValue) result = fl_value_new_bool(FALSE);
  if (strcmp(method, init) == 0) {
    /// init
    const gchar* title = nullptr;
    const gchar* iconPath = nullptr;
    const gchar* label = nullptr;
   FlValue* titleValue = fl_value_lookup_string(args, "title");
    if (titleValue && fl_value_get_type(titleValue) == FL_VALUE_TYPE_STRING) {
      title = fl_value_get_string(titleValue);
    }

   FlValue* iconPathValue = fl_value_lookup_string(args, "iconPath");
    if (iconPathValue && fl_value_get_type(iconPathValue) == FL_VALUE_TYPE_STRING) {
      iconPath = fl_value_get_string(iconPathValue);
    }
   FlValue* labelValue = fl_value_lookup_string(args, "label");
    if (labelValue && fl_value_get_type(labelValue) == FL_VALUE_TYPE_STRING) {
      label= fl_value_get_string(labelValue);
    }
      result =fl_value_new_bool(self->app_indicator.init(title,iconPath,label));
    response =FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else if(strcmp(method,icon)==0){
    /// change Icon
    const gchar* iconPath = nullptr;
    FlValue* pathValue = fl_value_lookup_string(args,"iconPath");
    if(pathValue && fl_value_get_type(pathValue)== FL_VALUE_TYPE_STRING){
      iconPath = fl_value_get_string(pathValue);
    }
      result =fl_value_new_bool(self->app_indicator.set_icon(iconPath,"icon"));
    response =FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else if(strcmp(method,label)==0){
    /// change Label
    const gchar* label = nullptr;
    FlValue* labelValue = fl_value_lookup_string(args,"label");
    if(labelValue && fl_value_get_type(labelValue)== FL_VALUE_TYPE_STRING){
      label = fl_value_get_string(labelValue);
    }
      result =fl_value_new_bool(self->app_indicator.set_label(label,"label"));
    response =FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else if(strcmp(method,title)==0){
    /// change title
    // const title = nullptr;
    // FlValue* labelValue = fl_value_lookup_string(args,"title");
    // if(titleValue && fl_value_get_type(titleValue)== FL_VALUE_TYPE_STRING){
      // title = fl_value_get_string(titleValue);
    // }
      // result =fl_value_new_bool(self->app_indicator.set_title(label,"label"));
    // response =FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else if(strcmp(method,menu)==0){
    /// set MenuList
    GtkWidget* menu =fl_value_to_menu(args);
    result = fl_value_new_bool(self->app_indicator.set_menu(menu));
    response =FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  }else{
    
  }

  fl_method_call_respond(method_call, response, nullptr);
}




static void flutter_app_indicator_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(flutter_app_indicator_plugin_parent_class)->dispose(object);
}

static void flutter_app_indicator_plugin_class_init(FlutterAppIndicatorPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = flutter_app_indicator_plugin_dispose;
}

static void flutter_app_indicator_plugin_init(FlutterAppIndicatorPlugin* self) {
  g_plugin = self;
}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  FlutterAppIndicatorPlugin* plugin = FLUTTER_APP_INDICATOR_PLUGIN(user_data);
  flutter_app_indicator_plugin_handle_method_call(plugin, method_call);
}

void flutter_app_indicator_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  FlutterAppIndicatorPlugin* plugin = FLUTTER_APP_INDICATOR_PLUGIN(
      g_object_new(flutter_app_indicator_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "flutter_app_indicator",
                            FL_METHOD_CODEC(codec));
plugin->app_indicator = FlutterAppIndicator();
plugin->channel=channel;

  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
