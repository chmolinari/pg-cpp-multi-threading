# Helpers to place the shared libraries a target needs at runtime next to the
# target itself, so it can be started straight from the build tree.

# Collects, recursively, every non-imported target reachable through the link
# libraries of <target>. Those are the targets that still have to be built
# before their shared libraries exist on disk. Imported targets (Conan, system
# packages, ...) are skipped: their binaries are already there.
function(_collect_buildable_link_dependencies target out_var)
    set(collected ${${out_var}})
    foreach (property IN ITEMS LINK_LIBRARIES INTERFACE_LINK_LIBRARIES)
        get_target_property(dependencies ${target} ${property})
        if (NOT dependencies)
            continue()
        endif ()
        foreach (dependency IN LISTS dependencies)
            if (NOT TARGET ${dependency})
                continue()
            endif ()
            get_target_property(imported ${dependency} IMPORTED)
            if (imported OR ${dependency} IN_LIST collected)
                continue()
            endif ()
            list(APPEND collected ${dependency})
            _collect_buildable_link_dependencies(${dependency} collected)
        endforeach ()
    endforeach ()
    set(${out_var} ${collected} PARENT_SCOPE)
endfunction()

# Adds a "<target>_runtime_dependencies" custom target that copies every shared
# library <target> depends on into the runtime output directory of <target>.
# The custom target is wired as a dependency of <target>, so it runs on every
# build of <target>, and only the files that actually changed are copied.
#
# <target> must be an executable, a SHARED library or a MODULE library.
# On platforms without DLLs the copy resolves to nothing and the target
# becomes a no-op, the run time linker resolving the dependencies through
# RPATH instead.
function(add_runtime_dependencies_target target)
    set(copy_target ${target}_runtime_dependencies)

    add_custom_target(
            ${copy_target}

            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${target}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different -t $<TARGET_FILE_DIR:${target}> $<TARGET_RUNTIME_DLLS:${target}>
            COMMAND_EXPAND_LISTS
            VERBATIM
            COMMENT "Copying shared library dependencies of ${target}"
    )

    # In-tree shared libraries must be linked before they can be copied.
    set(producers "")
    _collect_buildable_link_dependencies(${target} producers)
    if (producers)
        add_dependencies(${copy_target} ${producers})
    endif ()

    add_dependencies(${target} ${copy_target})
endfunction()
