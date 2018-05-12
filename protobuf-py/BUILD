load("@com_google_protobuf//:protobuf.bzl", "py_proto_library")

py_proto_library(
    name = "a_py_proto",
    srcs = ["a.proto"],
    visibility = ["//visibility:public"],
    protoc = "@com_google_protobuf//:protoc",
    default_runtime = "@com_google_protobuf//:protobuf_python",
)

py_binary(
	name = "t",
	srcs = ["t.py"],
	deps = [":a_py_proto"],
)
