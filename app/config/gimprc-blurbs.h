/*  gimprc-blurbs.h  --  descriptions for gimprc properties  */

#ifndef __GIMP_RC_BLURBS_H__
#define __GIMP_RC_BLURBS_H__


#define RESTORE_SESSION_BLURB \
"Let GIMP try to restore your last saved session."

#define BRUSH_PATH_BLURB \
"Sets the brush search path."

#define CANVAS_PADDING_MODE_BLURB \
"Sets the canvas padding mode."

#define CANVAS_PADDING_COLOR_BLURB \
"Sets the canvas padding color."

#define COLORMAP_CYCLING_BLURB \
"Specify that marching ants for selected regions will be drawn with " \
"colormap cycling as oposed to redrawing with different stipple masks. " \
"This color cycling option works only with 8-bit displays."

#define CONFIRM_ON_CLOSE_BLURB \
"Ask for confirmation before closing an image without saving."

#define CURSOR_MODE_BLURB \
"Sets the mode of cursor the GIMP will use."

#define CURSOR_UPDATING_BLURB \
"Context-dependent cursors are cool.  They are enabled by default. " \
"However, they require overhead that you may want to do without."

#define DEFAULT_BRUSH_BLURB \
"Specify a default brush.  The brush is searched for in the " \
"specified brush path."

#define DEFAULT_COMMENT_BLURB \
"Sets the default comment."

#define DEFAULT_DOT_FOR_DOT_BLURB \
"When set to yes, this will ensure that each pixel of an image gets " \
"mapped to a pixel on the screen."

#define DEFAULT_GRADIENT_BLURB \
"Specify a default gradient.  The gradient is searched for in the " \
"specified gradient path."

#define DEFAULT_IMAGE_WIDTH_BLURB \
"Sets the default image width in the File/New dialog."

#define DEFAULT_IMAGE_HEIGHT_BLURB \
"Sets the default image height in the File/New dialog."

#define DEFAULT_IMAGE_TYPE_BLURB \
"Sets the default image type in the File/New dialog."

#define DEFAULT_PATTERN_BLURB \
"Specify a default pattern. The pattern is searched for in the " \
"specified pattern path."

#define DEFAULT_PALETTE_BLURB \
"Specify a default palette.  The palette is searched for in the " \
"specified palette path."

#define DEFAULT_RESOLUTION_UNIT_BLURB \
"Sets the units for the display of the default resolution in the " \
"File/New dialog."

#define DEFAULT_THRESHOLD_BLURB \
"Tools such as fuzzy-select and bucket fill find regions based on a " \
"seed-fill algorithm.  The seed fill starts at the intially selected " \
"pixel and progresses in all directions until the difference of pixel " \
"intensity from the original is greater than a specified threshold. " \
"This value represents the default threshold."

#define DEFAULT_UNIT_BLURB \
"Sets the default unit for new images and for the File/New dialog. " \
"This units will be used for coordinate display when not in dot-for-dot " \
"mode."

#define DEFAULT_XRESOLUTION_BLURB \
"Sets the default horizontal resolution for new images and for the " \
"File/New dialog. This value is always in dpi (dots per inch)."

#define DEFAULT_YRESOLUTION_BLURB \
"Sets the default vertical resolution for new images and for the " \
"File/New dialog. This value is always in dpi (dots per inch)."

#define ENVIRON_PATH_BLURB \
"Sets the environ search path."

#define FRACTALEXPLORER_PATH_BLURB \
"Where to search for fractals used by the Fractal Explorer plug-in."

#define GAMMA_CORRECTION_BLURB \
"This setting is ignored."
#if 0
"Sets the gamma correction value for the display. 1.0 corresponds to no " \
"gamma correction.  For most displays, gamma correction should be set " \
"to between 2.0 and 2.6. One important thing to keep in mind: Many images " \
"that you might get from outside sources will in all likelihood already " \
"be gamma-corrected.  In these cases, the image will look washed-out if " \
"the GIMP has gamma-correction turned on.  If you are going to work with " \
"images of this sort, turn gamma correction off by setting the value to 1.0."
#endif

#define GFIG_PATH_BLURB \
"Where to search for Gfig figures used by the Gfig plug-in."

#define GFLARE_PATH_BLURB \
"Where to search for gflares used by the GFlare plug-in."

#define GIMPRESSIONIST_PATH_BLURB \
"Where to search for data used by the Gimpressionist plug-in."

#define GRADIENT_PATH_BLURB \
"Sets the gradient search path."

#define HELP_BROWSER_BLURB \
"Sets the browser gimp-help will use."

#define IMAGE_STATUS_FORMAT_BLURB \
"Sets the text to appear in image window status bars. See image-title-format " \
"for the list of possible % sequences."

#define IMAGE_TITLE_FORMAT_BLURB \
"Sets the text to appear in image window titles.  Certain % character " \
"sequences are recognised and expanded as follows:\n" \
"\n" \
"%%  literal percent sign\n" \
"%f  bare filename, or \"Untitled\"\n" \
"%F  full path to file, or \"Untitled\"\n" \
"%p  PDB image id\n" \
"%i  view instance number\n" \
"%t  image type (RGB, grayscale, indexed)\n" \
"%z  zoom factor as a percentage\n" \
"%s  source scale factor\n" \
"%d  destination scale factor\n" \
"%Dx expands to x if the image is dirty, the empty string otherwise\n" \
"%Cx expands to x if the image is clean, the empty string otherwise\n" \
"%m  memory used by the image\n" \
"%l  the number of layers\n" \
"%L  the name of the active layer/channel\n" \
"%w  image width in pixels\n" \
"%W  image width in real-world units\n" \
"%h  image height in pixels\n" \
"%H  image height in real-world units\n" \
"%u  unit symbol\n" \
"%U  unit abbreviation\n\n"

#define INFO_WINDOW_PER_DISPLAY_BLURB \
"When set to yes, the GIMP will use a different info window per image " \
"view."

#define INSTALL_COLORMAP_BLURB \
"Install a private colormap; might be useful on pseudocolor visuals."

#define INTERPOLATION_TYPE_BLURB \
"Sets the level of interpolation used for scaling and other transformations."

#define LAST_OPENED_SIZE_BLURB \
"How many recently opened image filenames to keep on the File menu."

#define MARCHING_ANTS_SPEED_BLURB \
"Speed of marching ants in the selection outline.  This value is in " \
"milliseconds (less time indicates faster marching)."

#define MAX_NEW_IMAGE_SIZE_BLURB  \
"Sets the max-new-image-size limit."

#define MIN_COLORS_BLURB  \
"Generally only a concern for 8-bit displays, this sets the minimum " \
"number of colors."

#define MODULE_PATH_BLURB \
"Sets the module search path."

#define MODULE_LOAD_INHIBIT_BLURB \
"To inhibit loading of a module, add its name here."

#define MONITOR_RES_FROM_GDK_BLURB \
"Set to yes if the GIMP should use the monitor resolution from " \
"the windowing system."

#define MONITOR_XRESOLUTION_BLURB \
"Sets the monitor's horizontal resolution, in dots per inch.  If set to " \
"0, forces the X server to be queried for both horizontal and vertical " \
"resolution information."

#define MONITOR_YRESOLUTION_BLURB \
"Sets the monitor's vertical resolution, in dots per inch.  If set to " \
"0, forces the X server to be queried for both horizontal and vertical " \
"resolution information."

#define NAVIGATION_PREVIEW_SIZE_BLURB \
"Sets the navigation preview size."

#define NUM_PROCESSORS_BLURB \
"On multiprocessor machines, if GIMP has been compiled with --enable-mp " \
"this sets how many processors GIMP should use simultaneously."

#define PALETTE_PATH_BLURB \
"Sets the palette search path."

#define PATTERN_PATH_BLURB \
"Sets the pattern search path."

#define PERFECT_MOUSE_BLURB \
"When set to yes, the X server is queried for the mouse's current " \
"position on each motion event, rather than relying on the position " \
"hint.  This means painting with large brushes should be more accurate, " \
"but it may be slower.  Perversely, on some X servers turning on this " \
"option results in faster painting."

#define PLUG_IN_PATH_BLURB \
"Sets the plug-in search path."

#define PLUGINRC_PATH_BLURB \
"Sets the pluginrc search path."

#define PREVIEW_SIZE_BLURB \
"Sets the default preview size."

#define RESIZE_WINDOWS_ON_RESIZE_BLURB \
"When the physical image size changes, setting this option to yes " \
"enables the automatic resizing of windows."

#define RESIZE_WINDOWS_ON_ZOOM_BLURB \
"When zooming into and out of images, this setting this option to " \
"yes enables the automatic resizing of windows."

#define SAVE_DEVICE_STATUS_BLURB \
"Remember the current tool, pattern, color, and brush across GIMP " \
"sessions."

#define SAVE_SESSION_INFO_BLURB \
"Remember the positions and sizes of the main dialogs and asks your " \
"window-manager to place them there again the next time you use the " \
"GIMP."

#define SCRIPT_FU_PATH_BLURB \
"This path will be searched for scripts when the Script-Fu plug-in is run."

#define SHOW_MENUBAR_BLURB \
"Sets the menubar visibility. This can also be toggled with the "\
"View->Toggle Menubar command."

#define SHOW_RULERS_BLURB \
"Sets the ruler visibility. This can also be toggled with the " \
"View->Toggle Rulers command."

#define SHOW_STATUSBAR_BLURB \
"Set to yes to make the statusbar visible. This can also be toggled "\
"with the View->Toggle Statusbar command."

#define SHOW_TIPS_BLURB \
"To display a handy GIMP tip on startup, set to yes."

#define SHOW_TOOL_TIPS_BLURB \
"To display tooltips, set to yes."

#define STINGY_MEMORY_USE_BLURB \
"There is always a tradeoff between memory usage and speed.  In most " \
"cases, the GIMP opts for speed over memory.  However, if memory is a " \
"big issue, set stingy-memory-use to yes."

#define SWAP_PATH_BLURB \
"Sets the swap file location. The gimp uses a tile based memory " \
"allocation scheme. The swap file is used to quickly and easily " \
"swap tiles out to disk and back in. Be aware that the swap file " \
"can easily get very large if the GIMP is used with large images. " \
"Also, things can get horribly slow if the swap file is created on " \
"a directory that is mounted over NFS.  For these reasons, it may " \
"be desirable to put your swap file in \"/tmp\"."

#define TEAROFF_MENUS_BLURB  \
"When set to yes, enables tear off menus." 

#define TEMP_PATH_BLURB \
"Sets the temporary storage directory. Files will appear here " \
"during the course of running the GIMP.  Most files will disappear " \
"when the GIMP exits, but some files are likely to remain, " \
"such as working palette files, so it is best if this directory " \
"not be one that is shared by other users or is cleared on machine " \
"reboot such as /tmp."

#define THEME_BLURB  \
"The name of the theme to use." 

#define THEME_PATH_BLURB  \
"Sets the theme search path."

#define THUMBNAIL_SIZE_BLURB \
"Sets the thumbnail size."

#define TILE_CACHE_SIZE_BLURB \
"The tile cache is used to make sure the GIMP doesn't thrash " \
"tiles between memory and disk. Setting this value higher will " \
"cause the GIMP to use less swap space, but will also cause " \
"the GIMP to use more memory. Conversely, a smaller cache size " \
"causes the GIMP to use more swap space and less memory."

#define TOOL_PLUG_IN_PATH_BLURB \
"Sets the tool-plug-in search path."

#define TRANSPARENCY_TYPE_BLURB \
"Sets the manner in which transparency is displayed in images."

#define TRANSPARENCY_SIZE_BLURB \
"Sets the size of the checkerboard used to display transparency."

#define TRUST_DIRTY_FLAG_BLURB \
"When set to yes, the GIMP will not save if the image is unchanged since " \
"opening it."

#define UNDO_LEVELS_BLURB \
"Sets the number of operations kept on the undo stack."

#define USE_HELP_BLURB  \
"When set to no the F1 help binding will be disabled." 


#endif  /* __GIMP_RC_BLURBS_H__ */
