genrule(
  name = "build_readline",
	srcs = glob(["**"]) + [
		"@local_config_cc//:toolchain",
  ],
	cmd = """
				 set -e
				 DEST_DIR=$$PWD/$(@D)
				 export CC=$$PWD/$(CC)
         export CXX=$$PWD/$(CC)
				 export CXXFLAGS=$(CC_FLAGS)
			   export NM=$$PWD/$(NM)
				 export AR=$$PWD/$(AR)
			   cd $$(dirname $(location :README))
         mkdir build
         ./configure --disable-shared --prefix=$$PWD/build
         make
         make install
         cp build/lib/*.a $$DEST_DIR
         cp -r build/include $$DEST_DIR
	""",
	outs = [
    "include/readline/chardefs.h",
    "include/readline/history.h",
    "include/readline/keymaps.h",
    "include/readline/readline.h",
    "include/readline/rlconf.h",
    "include/readline/rlstdc.h",
    "include/readline/rltypedefs.h",
    "include/readline/tilde.h",
    "libreadline.a",
    "libhistory.a",
	]	
)

cc_library(
    name = "readline",
    hdrs = [
      "include/readline/chardefs.h",
      "include/readline/history.h",
      "include/readline/keymaps.h",
      "include/readline/readline.h",
      "include/readline/rlconf.h",
      "include/readline/rlstdc.h",
      "include/readline/rltypedefs.h",
      "include/readline/tilde.h",
    ],
    strip_include_prefix = "include",
		srcs = [
      "libreadline.a",
      "libhistory.a",
    ],
    visibility = ["//visibility:public"],
)
