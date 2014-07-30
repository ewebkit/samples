// gcc simplen.cpp `pkg-config --cflags --libs elementary ewebkit2
#include <Elementary.h>
#include <EWebKit2.h>

void on_done(void *userData, Evas_Object *webView, void *eventInfo)
{
   elm_exit();
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   ewk_init();

   Evas_Object* win;
   win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
   elm_win_title_set(win, "sample");
   evas_object_smart_callback_add(win, "delete,request", on_done, NULL);
   elm_win_autodel_set(win, EINA_TRUE);

   Evas_Object* bg = elm_bg_add(win);
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_bg_color_set(bg, 0, 0, 255);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   Evas_Object* ewk = ewk_view_add(evas_object_evas_get(win));
   ewk_view_url_set(ewk, "http://bunhere.tistory.com");

   evas_object_resize(ewk, 400, 400);
   evas_object_move(ewk, 0, 0);
   evas_object_show(ewk);

   evas_object_resize(win, 400, 400);
   evas_object_show(win);

   elm_run();

   ewk_shutdown();
}
ELM_MAIN()
