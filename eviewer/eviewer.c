//Compile with:
//gcc -o photocam_example_01 photocam_example_01.c -g `pkg-config --cflags --libs elementary` -DDATA_DIR="\"<directory>\""
//where directory is the path where images/insanely_huge_test_image.jpg can be found.

#include <Elementary.h>

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *bg;
   Evas_Object *panes, *right_pane;
   char buf[PATH_MAX];

   win = elm_win_add(NULL, "Evince", ELM_WIN_BASIC);
   elm_win_title_set(win, "Panes");
   elm_win_autodel_set(win, EINA_TRUE);

   bg = elm_button_add(win);
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win,bg);
   elm_win_focus_highlight_enabled_set(win, EINA_TRUE);
   evas_object_show(bg);

   panes = elm_panes_add(win);
   evas_object_size_hint_weight_set(panes, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, panes);
   evas_object_show(panes);

   right_pane = elm_panes_add(win);
   elm_panes_horizontal_set(right_pane, EINA_TRUE);
   evas_object_size_hint_weight_set(right_pane, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(right_pane, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(right_pane);

   evas_object_resize(win, 400, 600);
   evas_object_show(win);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
