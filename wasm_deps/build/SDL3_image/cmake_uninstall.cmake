if (NOT EXISTS "/home/runner/workspace/wasm_deps/build/SDL3_image/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/home/runner/workspace/wasm_deps/build/SDL3_image/install_manifest.txt\"")
endif()

file(READ "/home/runner/workspace/wasm_deps/build/SDL3_image/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /nix/store/29ax4k0a83zhz43lb73cv610d95wdsx1-cmake-3.31.6/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach()
