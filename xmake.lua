-- the debug mode
if is_mode("debug") then
    
    -- enable the debug symbols
    set_symbols("debug")

    -- disable optimization
    set_optimize("none")
end

-- the release mode
if is_mode("release") then

    -- set the symbols visibility: hidden
    set_symbols("hidden")

    -- enable fastest optimization
    set_optimize("fastest")

    -- strip all symbols
    set_strip("all")
end

add_includedirs("src/lib")
-- define target
target("tlpi_hdr")

    -- set kind
    set_kind("static")

    -- add files
    add_files("src/lib/error_functions.c")
    add_files("src/lib/get_num.c")
    add_files("src/lib/ugid_functions.c")

-- define target
target("fileio_seek_io")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/fileio/seek_io.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("proc_setjmp_vars")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proc/setjmp_vars.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("4-10-2-mycp")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/4-10-2-mycp.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("users_group_check_password")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/users_groups/check_password.c")
    add_ldflags("-lcrypt")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("proc_modify_env")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proc/modify_env.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("5-14-1-fileio_large_file")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/5-14-1-fileio_large_file.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("4-10-1-mytee")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/4-10-1-mytee.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("8-7-2-my_getpwnam")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/8-7-2-my_getpwnam.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("5-14-7-my_readv_writev")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/5-14-7-my_readv_writev.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("proc_longjmp")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proc/longjmp.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("5-14-3-atomic_append")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/5-14-3-atomic_append.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("6-9-3-my_setenv_unsetenv")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/6-9-3-my_setenv_unsetenv.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("fileio_t_readv")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/fileio/t_readv.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("fileio_copy")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/fileio/copy.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("5-14-5-check_fd_dup")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/5-14-5-check_fd_dup.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("proc_display_env")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proc/display_env.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("proc_necho")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proc/necho.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("memalloc_free_and_sbrk")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/memalloc/free_and_sbrk.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("fileio_large_file")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/fileio/large_file.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("proc_mem_segments")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proc/mem_segments.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("5-14-4-mydup")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/5-14-4-mydup.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("7-4-2-my_malloc_free")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/7-4-2-my_malloc_free.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("6-9-2-longjmp_fail")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/6-9-2-longjmp_fail.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("5-14-2-file_append")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/5-14-2-file_append.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("7-4-1-memalloc_free_and_sbrk")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/exercises/7-4-1-memalloc_free_and_sbrk.c")

    -- add deps
    add_deps("tlpi_hdr")

-- define target
target("idshow")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/proccred/idshow.c")

    -- add deps
    add_deps("tlpi_hdr")
