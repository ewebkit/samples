/* gcc simple_popup.c `pkg-config --cflags --libs elementary ewebkit2
 *
 *  This example shows how to support alert/confirm/prompt popup,
 *  so explains how to extend ewebkit using smart method.
 */
#include <Elementary.h>
// Include header file.
#include <EWebKit2.h>

void on_done(void *user_data, Evas_Object *web_view, void *event_info)
{
   elm_exit();
}

static Evas_Object* g_win;

static void
quit_event_loop(void *user_data, Evas_Object *obj, void *event_info)
{
    ecore_main_loop_quit();
}

static void
on_javascript_alert(Ewk_View_Smart_Data *smartData, const char *message)
{
   Evas_Object *popup = elm_popup_add(g_win);

   evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(popup, message);
   elm_object_part_text_set(popup, "title,text", "Alert");

   /* Popup buttons */
   Evas_Object *button = elm_button_add(popup);
   elm_object_text_set(button, "OK");
   elm_object_part_content_set(popup, "button1", button);
   evas_object_smart_callback_add(button, "clicked", quit_event_loop, NULL);
   elm_object_focus_set(button, EINA_TRUE);
   evas_object_show(popup);

   /* Make modal */
   ecore_main_loop_begin();

   evas_object_del(popup);
}

static Eina_Bool
on_javascript_confirm(Ewk_View_Smart_Data *smartData, const char *message)
{
}

static const char *
on_javascript_prompt(Ewk_View_Smart_Data *smartData, const char *message, const char *default_value)
{
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   // Initialize ewebkit.
   ewk_init();

   g_win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
   elm_win_title_set(g_win, "sample");
   evas_object_smart_callback_add(g_win, "delete,request", on_done, NULL);
   elm_win_autodel_set(g_win, EINA_TRUE);

   Evas_Object* bg = elm_bg_add(g_win);
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_bg_color_set(bg, 0, 0, 255);
   elm_win_resize_object_add(g_win, bg);
   evas_object_show(bg);

   // Creates Ewk_View_Smart_Class.
   static Ewk_View_Smart_Class ewk_view_class = EWK_VIEW_SMART_CLASS_INIT_NAME_VERSION("SimpleEwkClass");
   ewk_view_smart_class_set(&ewk_view_class);
   ewk_view_class.run_javascript_alert = on_javascript_alert;
   ewk_view_class.run_javascript_confirm = on_javascript_confirm;
   ewk_view_class.run_javascript_prompt = on_javascript_prompt;

   Evas_Smart *smart = evas_smart_class_new(&ewk_view_class.sc);
   // create very simple ewk_view.
   Evas_Object *ewk = ewk_view_smart_add(evas_object_evas_get(g_win), smart, ewk_context_default_get(), ewk_page_group_create(NULL));
   ewk_view_theme_set(ewk, "/usr/elocal/share/ewebkit2-1/themes/default.edj");

   // load from string. last argument is unreachableUrl
   ewk_view_html_string_load(ewk, "<!doctype html><body><input type=button onclick=\"window.alert('hello');\"></body>", NULL, NULL);
   // ewk_view_html_string_load(ewk, "<!doctype html><body>Hello <img src=\"./logo.png\"></body>", "http://enlightenment.org/p/index/d/", NULL);

   // locate ewk_view at (0,0,400,400)
   evas_object_resize(ewk, 400, 400);
   evas_object_move(ewk, 0, 0);
   evas_object_show(ewk);

   evas_object_resize(g_win, 400, 400);
   evas_object_show(g_win);

   // execute main loop, ewk_view will do a lot of operation for loading url.
   elm_run();

   // Before terminated process, please deinitialize ewebkit.
   ewk_shutdown();
}
ELM_MAIN()

