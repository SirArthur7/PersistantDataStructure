load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "ITER_MAIN",
    srcs = ["iteration_main.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:Headers_preprocessors",
	"//src/lib:PPDS_LinkedList",
	"//src/lib:Util",
    ],
)

cc_binary(
    name = "UPDATION_MAIN",
    srcs = ["updation_main.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:Headers_preprocessors",
	"//src/lib:PPDS_LinkedList",
	"//src/lib:Util",
    ],
)
