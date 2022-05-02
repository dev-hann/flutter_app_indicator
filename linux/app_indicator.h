#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>


class FlutterAppIndicator{

  public:
    bool init(const chatr* title,
        const char* iconPath,
        const chat* label,
        GtkWidget* menuList);

}
