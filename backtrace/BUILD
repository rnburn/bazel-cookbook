cc_library(
    name = "backtrace",
    hdrs = [
        "backtrace.h",
    ],
    srcs = [
        "backtrace.cc",
    ],
)

cc_library(
    name = "pestcontrol",
    hdrs = [
        "pestcontrol.h",
    ],
    srcs = [
        "pestcontrol.cc",
    ],
)

cc_library(
    name = "runway",
    hdrs = [
        "runway.h",
    ],
    srcs = [
        "runway.cc",
    ],
    deps = [
        ":pestcontrol",
    ],
)

cc_binary(
    name = "rocket",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":runway",
        ":backtrace",
    ],
)
