load("@rules_cc//cc:defs.bzl", "cc_library")

cc_test(
    name = "VALIDATION_TEST",
    srcs = ["validation.cpp"],

    deps = [
        "@com_google_benchmark//:benchmark",
	"//src/lib:Headers_preprocessors",
	"//src/lib:PPDS_LinkedList",
	"//src/lib:Util",
	"//src/lib:Test_with_Vector_and_PDSLL",
	"@com_google_googletest//:gtest_main",
    ],
)