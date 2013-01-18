//Compile with:
//gcc -o photocam_example_01 photocam_example_01.c -g `pkg-config --cflags --libs elementary` -DDATA_DIR="\"<directory>\""
//where directory is the path where images/insanely_huge_test_image.jpg can be found.

#include <Elementary.h>

typedef struct _Interface Eview_Iface;

struct _Interface
{
    Evas_Object *bg;
    Evas_Object *fs;
    Evas_Object *win;
    Evas_Object *hbox;
    Evas_Object *grid;
    Evas_Object *panes;
    Evas_Object *image;
};

Evas_Object *
_thumb_gen(const char *path, Eview_Iface *iface)
{
    Evas_Object *th;
    th = elm_thumb_add(iface->win);
    elm_thumb_file_set(th, path, NULL);
    evas_object_size_hint_weight_set(th, EVAS_HINT_EXPAND,
                                         EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(th, EVAS_HINT_FILL,
                                        EVAS_HINT_FILL);
    elm_thumb_editable_set(th, EINA_FALSE);
    evas_object_show(th);

    return th;
}

void
_image_select(void *data, Evas_Object *obj, void *event_info)
{
}


static void
_image_process(const char *name, const char *path, void *data)
{
    Elm_Gengrid_Item_Class *gic;
    Eview_Iface *iface = data;

    gic = elm_gengrid_item_class_new();
    gic->item_style = "default";
    gic->func.text_get = name;
    gic->func.content_get = _thumb_gen(path, iface);
    gic->func.state_get = EINA_FALSE;

    printf("file %s in %s\n", name, path);
    elm_gengrid_item_append (iface->grid, gic, NULL, _image_select, NULL);

}

EAPI_MAIN int
_populate_grid(Eview_Iface *iface)
{
    eina_file_dir_list("/home/puppetmaster/images/wallpaper", EINA_FALSE,
                       _image_process, iface);       
    return 0;
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
    Eview_Iface *iface;

    iface = calloc(1, sizeof(Eview_Iface));

    // Building Main iface->window
    iface->win = elm_win_add(NULL, "Eviewer", ELM_WIN_BASIC);
    elm_win_title_set(iface->win, "Eviewer");
    elm_win_autodel_set(iface->win, EINA_TRUE);

    // Main background
    iface->bg = elm_bg_add(iface->win);
    evas_object_size_hint_weight_set(iface->bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(iface->win, iface->bg);
    //elm_win_focus_highlight_enabled_set(iface->win, EINA_TRUE);
    evas_object_show(iface->bg);

    // Hbox container
    iface->hbox = elm_box_add(iface->win);
    elm_box_horizontal_set(iface->hbox, EINA_TRUE);
    evas_object_size_hint_weight_set(iface->hbox, EVAS_HINT_EXPAND, EVAS_HINT_FILL);
    evas_object_size_hint_align_set(iface->hbox, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_win_resize_object_add(iface->win,iface->hbox);

    // Building Main Pane
    iface->panes = elm_panes_add(iface->win);
    evas_object_size_hint_weight_set(iface->panes, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(iface->panes, EVAS_HINT_FILL, EVAS_HINT_FILL);
    //elm_win_resize_object_add(iface->win, panes);
    elm_box_pack_end(iface->hbox, iface->panes);
    evas_object_show(iface->panes);

    // Building File selector
    iface->fs = elm_fileselector_add(iface->win);
    /* disable the fs file name entry */
    elm_fileselector_is_save_set(iface->fs, EINA_FALSE);
    /* make the file list a tree with dir expandable in place */
    elm_fileselector_expandable_set(iface->fs, EINA_TRUE);
    /* start the fileselector in the home dir */
    elm_fileselector_path_set(iface->fs, getenv("PWD"));
    /* allow fs to expand in x & y */
    evas_object_size_hint_weight_set(iface->fs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(iface->fs, EVAS_HINT_FILL, EVAS_HINT_FILL);
    /* the 'done' cb is called when the user press ok/cancel */
    //evas_object_smart_callback_add(fs, "done", my_fileselector_done, iface->win);
    /* the 'selected' cb is called when the user click on a file/dir */
    //evas_object_smart_callback_add(fs, "selected", my_fileselector_selected,
    //                               iface->win);
    evas_object_show(iface->fs);
    elm_object_part_content_set(iface->panes, "left", iface->fs);

    // Building Photo preview
    iface->image = elm_image_add(iface->win);
    elm_image_file_set(iface->image, "/home/puppetmaster/images/photos/raoul/IMG_3036_01.jpg", NULL);
    elm_image_resizable_set(iface->image, EINA_TRUE, EINA_TRUE);
    evas_object_size_hint_weight_set(iface->image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(iface->image, EVAS_HINT_FILL, EVAS_HINT_FILL);
    //elm_object_part_content_set(panes, "right", image);
    //evas_object_show(image);

    // Thumb view
    iface->grid = elm_gengrid_add(iface->win);                 
    elm_gengrid_item_size_set(iface->grid, 150, 150); 
    elm_gengrid_group_item_size_set(iface->grid, 31, 31); 
    elm_gengrid_horizontal_set(iface->grid, EINA_FALSE); 
    evas_object_size_hint_weight_set(iface->grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);  
    elm_gengrid_align_set(iface->grid, 0.1, 0.3);          
    elm_object_part_content_set(iface->panes, "right", iface->grid);
    evas_object_show(iface->grid);

    _populate_grid(iface);

    // Sizing main iface->window
    evas_object_resize(iface->win, 400, 600);
    evas_object_show(iface->hbox);
    evas_object_show(iface->win);

    // Running App
    elm_run();
    elm_shutdown();

    return 0;
}
ELM_MAIN()
