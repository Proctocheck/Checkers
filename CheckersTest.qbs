import qbs

Project {
minimumQbsVersion: "1.7.1"

CppApplication {
consoleApplication: true

cpp.cxxLanguageVersion: "c++14"

property path graph_lib_dir: "../Graph_lib"

files: [
        "../../source/repos/seminars graph/seminars graph/std_lib_facilities.h",
        "../Graph_lib/GUI.h",
        "../Graph_lib/Graph.h",
        "../Graph_lib/Point.h",
        "../Graph_lib/Simple_window.h",
        "../Graph_lib/Window.h",
        "../Graph_lib/fltk.h",
        "board.cpp",
        "board.cpp",
        "board.h",
        "board.h",
        "cell.cpp",
        "cell.cpp",
        "cell.h",
        "cell.h",
        "core.cpp",
        "core.h",
        "engine.cpp",
        "engine.h",
        "graphics.cpp",
        "graphics.h",
        "std_lib_facilities.h",
        graph_lib_dir +"/Graph.cpp",
        graph_lib_dir +"/GUI.cpp",
        graph_lib_dir +"/Window.cpp",
        "main.cpp",
    ]

cpp.includePaths: "../fltk_win64/include"
cpp.libraryPaths: "../fltk_win64/lib"
cpp.cxxFlags: "-Wno-unused-parameter"
cpp.driverLinkerFlags: "-mwindows"
cpp.staticLibraries: [
"fltk_images",
"fltk",
"fltk_png",
"z",
"fltk_jpeg",
"ole32",
"uuid",
"comctl32",
]

Group { // Properties for the produced executable
fileTagsFilter: "application"
qbs.install: true
}
}
}
