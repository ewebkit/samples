/* gcc simple_load_elm.c `pkg-config --cflags --libs elementary ewebkit2
 *
 *  This example shows very simple ewebkit example that load my blog.
 */
#include <Elementary.h>
// Include header file.
#include <EWebKit2.h>

void on_done(void *user_data, Evas_Object *web_view, void *event_info)
{
   elm_exit();
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   // Initialize ewebkit.
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

   // create very simple ewk_view.
   Evas_Object* ewk = ewk_view_add(evas_object_evas_get(win));

   // load specific url.
   ewk_view_url_set(ewk, "http://bunhere.tistory.com");

   // locate ewk_view at (0,0,400,400)
   evas_object_resize(ewk, 400, 400);
   evas_object_move(ewk, 0, 0);
   evas_object_show(ewk);

   evas_object_resize(win, 400, 400);
   evas_object_show(win);

   // execute main loop, ewk_view will do a lot of operation for loading url.
   elm_run();

   // Before terminated process, please deinitialize ewebkit.
   ewk_shutdown();
}
ELM_MAIN()
