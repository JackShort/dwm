/*                          __ _         _     
*           ___ ___  _ __  / _(_) __ _  | |__  
*          / __/ _ \| '_ \| |_| |/ _` | | '_ \
*         | (_| (_) | | | |  _| | (_| |_| | | |
*          \___\___/|_| |_|_| |_|\__, (_)_| |_|
*                                |___/         
*	dwm's configuration file (yes, config file)
*/

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int attachbelow		        = 1;	/* 1 means attach after the currently active winow */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */

/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= False;               /* False means bottom tab bar */

static const char *fonts[]          = { "Fira Code:size=11" };
static const char dmenufont[]       = "Fira Code:size=11";

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char back[]   = "#1C1E27";
static const char fore[]   = "#CACACC";
static const char border[] = "#CACACC";
static const char col0[]   = "#6C6F93";
static const char col1[]   = "#E4436F";
static const char col2[]   = "#24E39D";
static const char col3[]   = "#EDA685";
static const char col4[]   = "#00A5AF";

static const char nordFG[] = "#3B4252";
static const char nordBG[] = "#FFFFFF"; static const char nordBorderUnselected[] = "#4C566A";
static const char nordBorderSelected[] = "#5E81AC";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { fore,      back,      nordBorderUnselected   }, // \x0b
	[SchemeSel]      = { "#3b4252", "#88c0d0", nordBorderSelected   }, // \x0c
	[SchemeNormMon]  = { fore,      back,      nordBorderSelected   }, // \x0c
	[SchemeSelMon]   = { "#88c0d0", back,      nordBorderSelected   }, // \x0c
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Spotify",	NULL,       NULL,       0,            0,           0,           1 },
};

/* layout(s) */
static const float mfact     = 0.67; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	/*{ "[]=",      tile },*/    /* first entry is default */
	{ "[M]",      monocle }, /* All windows on top of each other */
 	{ "[t]",      tile }, /* double deck */

	{ "|M|",      centeredmaster }, /* Master in the middle, slaves on the side */
	{ ">M>",      centeredfloatingmaster }, /* Same but master floats*/

 	{ "[@]",      spiral }, /* fib */
 	{ "[\\]",     dwindle }, /* reverse fib */

 	{ "[DD]",     doubledeck }, /* double deck */
 	{ "[|||]",    col }, /* col */

 	{ "[3]",      thirds }, /* double deck */

	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_v,     ACTION##stack, {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", back, "-nf", col4, "-sb", col1, "-sf", back, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL};
static const char *rofiwindowcmd[] = { "rofi", "-show", "window", NULL};
static const char *termcmd[]  = { "st", NULL };
static const char *volumeup[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *volumedown[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevolume[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *pausetrack[]  = { "playerctl", "play-pause", NULL };
static const char *nexttrack[]  = { "playerctl", "next", NULL };
static const char *prevtrack[]  = { "playerctl", "previous", NULL };
static const char *openchrome[]  = { "chromium", NULL };
static const char *openspotify[]  = { "spotify", NULL };
static const char *openemacs[]  = { "emacs", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = rofiwindowcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      tabmode,        {-1} },
	{ MODKEY|ShiftMask,             XK_Tab,    toggleAttachBelow,      {0} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_z,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,			            XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} }, /* tile */
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[9]} }, /* float */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} }, /* monacle */
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[2]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,             XK_semicolon, togglermaster,      { 0 } }, /* centeredmaster floating*/
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} }, /* spiral */
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[5]} }, /* dwindle */
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[8]} }, /* thirds */
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[7]} }, /* cols */
	{ MODKEY,                       XK_s,	   togglesticky,   {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefakefullscreen, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_BackSpace, quit,        {0} },
	{ MODKEY,                       XK_equal,   spawn,          {.v = volumeup } },
	{ MODKEY,                       XK_minus,   spawn,          {.v = volumedown } },
	{ MODKEY,                       XK_backslash,   spawn,      {.v = mutevolume } },
	{ MODKEY|ShiftMask,             XK_i,	    spawn,	    {.v = pausetrack } },
	{ MODKEY,			            XK_u,	    spawn,	    {.v = nexttrack } },
	{ MODKEY|ShiftMask,             XK_u,	    spawn,	    {.v = prevtrack } },
	{ MODKEY,			            XK_w,	    spawn,	    {.v = openchrome } },
	{ MODKEY|ShiftMask,             XK_w,	    spawn,	    {.v = openspotify } },
	{ MODKEY|ShiftMask,             XK_e,	    spawn,	    {.v = openemacs } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

