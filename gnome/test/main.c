#include <gtk/gtk.h>

extern GtkWidget* CreateWidget();

static void on_active(GtkApplication* app)
{
    GtkWindow* window = gtk_application_get_active_window(app);
    if(!window)
    {
        window = GTK_WINDOW(gtk_application_window_new(app));
        gtk_widget_set_size_request(GTK_WIDGET(window), 800, 600);

        gtk_container_add(GTK_CONTAINER(window), CreateWidget());
    }
    gtk_window_present(window);
}
int main(int argc, char* argv[])
{
    GtkApplication* app = gtk_application_new("com.chinahuanghe.softclient", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_active), NULL);
    int ret = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return ret;
}
