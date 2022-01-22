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

cc_binary(
    name = "ITER_MAIN_KANKO",
    srcs = ["iteration_main_kanko.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:Headers_preprocessors",
	"//src/lib:Kanko_Array",
    ],
)

cc_binary(
    name = "FP_STACK_MAIN_PUSH",
    srcs = ["FP_STACK_MAIN_PUSH.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:FP_STACK",
    ],
)

cc_binary(
    name = "FP_STACK_MAIN_POP",
    srcs = ["FP_STACK_MAIN_POP.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:FP_STACK",
    ],
)

cc_binary(
    name = "FP_STACK_MAIN_PUSH_POP",
    srcs = ["FP_STACK_MAIN_PUSH_POP.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:FP_STACK",
    ],
)

cc_binary(
    name = "FP_QUEUE_MAIN_ENQ",
    srcs = ["FP_QUEUE_MAIN_ENQ.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:FP_QUEUE",
    ],
)

cc_binary(
    name = "FP_QUEUE_MAIN_DEQ",
    srcs = ["FP_QUEUE_MAIN_DEQ.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:FP_QUEUE",
    ],
)

cc_binary(
    name = "FP_QUEUE_MAIN_ENQ_DEQ",
    srcs = ["FP_QUEUE_MAIN_ENQ_DEQ.cpp"],
    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:FP_QUEUE",
    ],
)


