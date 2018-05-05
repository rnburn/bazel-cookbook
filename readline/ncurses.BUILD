genrule(
  name = "build_ncurses",
	srcs = glob(["**"]) + [
		"@local_config_cc//:toolchain",
  ],
	cmd = """
				 set -e
				 DEST_DIR=$$PWD/$(@D)
				 export CC=$$PWD/$(CC)
         export CXX=$$PWD/$(CC)
				 export CXXFLAGS=$(CC_FLAGS)
			   cd $$(dirname $(location :README))
         ./configure --disable-shared --prefix=$$PWD/build
         make
         make install
         cp build/lib/*.a $$DEST_DIR
         cp -r build/include $$DEST_DIR
	""",
	outs = [
    "include/ncurses/curses.h",
    "include/ncurses/cursesapp.h",
    "include/ncurses/cursesf.h",
    "include/ncurses/cursesm.h",
    "include/ncurses/cursesp.h",
    "include/ncurses/cursesw.h",
    "include/ncurses/cursslk.h",
    "include/ncurses/eti.h",
    "include/ncurses/etip.h",
    "include/ncurses/form.h",
    "include/ncurses/menu.h",
    "include/ncurses/nc_tparm.h",
    "include/ncurses/ncurses.h",
    "include/ncurses/ncurses_dll.h",
    "include/ncurses/panel.h",
    "include/ncurses/term.h",
    "include/ncurses/term_entry.h",
    "include/ncurses/termcap.h",
    "include/ncurses/tic.h",
    "include/ncurses/unctrl.h",
    "libform.a",
    "libform_g.a",
    "libmenu.a",
    "libmenu_g.a",
    "libncurses++.a",
    "libncurses++_g.a",
    "libncurses.a",
    "libncurses_g.a",
    "libpanel.a",
    "libpanel_g.a",
	]	
)

cc_library(
    name = "ncurses",
    hdrs = [
    ],
    strip_include_prefix = "include",
		srcs = [
      "libncurses.a",
    ],
    visibility = ["//visibility:public"],
)
