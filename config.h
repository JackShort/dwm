/*                          __ _         _     
*           ___ ___  _ __  / _(_) __ _  | |__  
*          / __/ _ \| '_ \| |_| |/ _` | | '_ \
*         | (_| (_) | | | |  _| | (_| |_| | | |
*          \___\___/|_| |_|_| |_|\__, (_)_| |_|
*                                |___/         
*	dwm's configuration file (yes, config file)
*/

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int attachbelow		    = 1;	/* 1 means attach after the currently active winow */

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
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { fore,      back,      back   }, // \x0b
	[SchemeSel]      = { fore,      back,      col4   }, // \x0c
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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */

	{ "[M]",      monocle }, /* All windows on top of each other */

	{ "|M|",      centeredmaster }, /* Master in the middle, slaves on the side */
	{ ">M>",      centeredfloatingmaster }, /* Same but master floats*/

 	{ "[@]",      spiral }, /* fib */
 	{ "[\\]",      dwindle }, /* reverse fib */

 	{ "[DD]",      doubledeck }, /* double deck */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *volumeup[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *volumedown[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevolume[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *pausetrack[]  = { "playerctl", "play-pause", NULL };
static const char *nexttrack[]  = { "playerctl", "next", NULL };
static const char *prevtrack[]  = { "playerctl", "previous", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    toggleAttachBelow,      {0} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,			XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[7]} }, /* float */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} }, /* monacle */
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[2]} }, /* centeredmaster */
	/*{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[3]} }, centeredmaster floating*/
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} }, /* spiral */
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[5]} }, /* dwindle */
	{ MODKEY,			XK_d,      setlayout,      {.v = &layouts[6]} }, /* doubledeck */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
	{ MODKEY,			XK_u,	    spawn,	    {.v = nexttrack } },
	{ MODKEY|ShiftMask,             XK_u,	    spawn,	    {.v = prevtrack } },
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
};

