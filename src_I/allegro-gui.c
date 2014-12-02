#include "ibm.h"
#include "allegro-main.h"
#include "allegro-gui.h"
#include "device.h"
#include "ide.h"

static int file_return(void)
{
        return D_CLOSE;
}

static int file_exit(void)
{
        quited = 1;
        return D_CLOSE;
}

static int file_reset(void)
{
        resetpchard();
        return D_CLOSE;
}

static MENU file_menu[]=
{
	{"&Return",     file_return, NULL, 0, NULL},
        {"&Hard Reset", file_reset, NULL, 0, NULL},
        {"E&xit",       file_exit,  NULL, 0, NULL},
        {NULL,NULL,NULL,0,NULL}
};

static int disc_load_a()
{
        char fn[260];
        int ret;
        int xsize = SCREEN_W - 32, ysize = SCREEN_H - 64;
        strcpy(fn, discfns[0]);
        ret = file_select_ex("Please choose a disc image", fn, "IMG;IMA", 260, xsize, ysize);
        if (ret)
        {
                savedisc(0);
                loaddisc(0, fn);
                saveconfig();
        }
        return D_O_K;
}

static int disc_load_b()
{
        char fn[260];
        int ret;
        int xsize = SCREEN_W - 32, ysize = SCREEN_H - 64;
        strcpy(fn, discfns[1]);
        ret = file_select_ex("Please choose a disc image", fn, "IMG;IMA", 260, xsize, ysize);
        if (ret)
        {
                savedisc(1);
                loaddisc(1, fn);
                saveconfig();
        }
        return D_O_K;
}

static int disc_eject_a()
{
        savedisc(0);
        ejectdisc(0);
        saveconfig();
        
        return D_O_K;
}

static int disc_eject_b()
{
        savedisc(1);
        ejectdisc(1);
        saveconfig();
        
        return D_O_K;
}

static MENU disc_menu[]=
{
        {"Load drive &A:...",   disc_load_a, NULL, 0, NULL},
        {"Load drive &B:...",   disc_load_b, NULL, 0, NULL},
        {"&Eject drive &A:", disc_eject_a, NULL, 0, NULL},
        {"Eject drive &B:",  disc_eject_b, NULL, 0, NULL},
        {"&Configure hard discs...", disc_hdconf, NULL, 0, NULL},
        {NULL,NULL,NULL,0,NULL}
};

static MENU cdrom_menu[];

static void cdrom_update()
{
	int c;
       
	for (c = 0; cdrom_menu[c].text; c++)
		cdrom_menu[c].flags = 0;

	if (!cdrom_enabled)
		cdrom_menu[0].flags = D_SELECTED;
	else
		cdrom_menu[1].flags = D_SELECTED;

	return D_O_K;
}

static int cdrom_disabled()
{
	if (!cdrom_enabled)
		return D_O_K;

	if (alert("This will reset PCem!", "Okay to continue?", NULL, "OK", "Cancel", 0, 0) == 1)
	{
		atapi->exit();
		cdrom_enabled = 0;                                             
		saveconfig();
		resetpchard();
		cdrom_update();
	}

	return D_O_K;
}

static int cdrom_empty()
{
	if (cdrom_enabled)
	{
		atapi->exit();
		cdrom_drive = -1;
		cdrom_null_open(cdrom_drive);
		return D_O_K;
	}

	if (alert("This will reset PCem!", "Okay to continue?", NULL, "OK", "Cancel", 0, 0) == 1)
	{
		cdrom_drive = -1;
		cdrom_enabled = 1;
		cdrom_null_open(cdrom_drive);
		saveconfig();
		resetpchard();
		cdrom_update();
	}
}

static int cdrom_dev()
{
	if (cdrom_enabled)
	{
		atapi->exit();
		cdrom_drive = 0;
		ioctl_open(cdrom_drive);
		return D_O_K;
	}

	if (alert("This will reset PCem!", "Okay to continue?", NULL, "OK", "Cancel", 0, 0) == 1)
	{
		cdrom_drive = 0;
		cdrom_enabled = 1;
		ioctl_open(cdrom_drive);
		saveconfig();
		resetpchard();
		cdrom_update();
	}
}

static MENU cdrom_menu[] =
{
        {"&Disabled", cdrom_disabled, NULL, 0, NULL},
        {"&Empty", cdrom_empty, NULL, 0, NULL},
        {"/dev/cdrom", cdrom_dev, NULL, 0, NULL},
        {NULL,NULL,NULL,0,NULL}
};

static MENU settings_menu[]=
{
        {"&Configure...",   settings_configure, NULL, 0, NULL},
	{"CD-ROM", NULL, cdrom_menu, 0, NULL},
        {NULL,NULL,NULL,0,NULL}
};

static MENU main_menu[]=
{
        {"&File", NULL, file_menu, 0, NULL},
        {"&Disc", NULL, disc_menu, 0, NULL},
        {"&Settings", NULL, settings_menu, 0, NULL},
        {NULL,NULL,NULL,0,NULL}
};

static DIALOG pcem_gui[]=
{
        {d_menu_proc,  0,   0,   0,  0, 15, 0, 0, 0, 0, 0, main_menu, NULL, NULL},
        {d_yield_proc, 0,   0,   0,  0, 15, 0, 0, 0, 0, 0, NULL,      NULL, NULL},
        {0,0,0,0,0,0,0,0,0,0,0,NULL,NULL,NULL}
};

void gui_enter()
{
        DIALOG_PLAYER *dp;
        int x = 1;
        infocus = 0;

        dp = init_dialog(pcem_gui, 0);
        show_mouse(screen);
        while (x && !(mouse_b & 2) && !key[KEY_ESC])
        {
                x = update_dialog(dp);
        }
        show_mouse(NULL);
        shutdown_dialog(dp);

        clear(screen);
        clear_keybuf();
        
        infocus = 1;

	device_force_redraw();
}
