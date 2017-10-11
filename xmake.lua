--target("debug")
--    add_cflags("-g");

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
    add_files("src/lib/file_perms.c")

target("fileio_seek_io")
    set_kind("binary")
    add_files("src/fileio/seek_io.c")
    add_deps("tlpi_hdr")

target("proc_setjmp_vars")
    set_kind("binary")
    add_files("src/proc/setjmp_vars.c")
    add_deps("tlpi_hdr")

target("4-10-2-mycp")
    set_kind("binary")
    add_files("src/exercises/4-10-2-mycp.c")
    add_deps("tlpi_hdr")

target("users_group_check_password")
    set_kind("binary")
    add_files("src/users_groups/check_password.c")
    add_ldflags("-lcrypt")
    add_deps("tlpi_hdr")

target("proc_modify_env")
    set_kind("binary")
    add_files("src/proc/modify_env.c")
    add_deps("tlpi_hdr")

target("5-14-1-fileio_large_file")
    set_kind("binary")
    add_files("src/exercises/5-14-1-fileio_large_file.c")
    add_deps("tlpi_hdr")

target("4-10-1-mytee")
    set_kind("binary")
    add_files("src/exercises/4-10-1-mytee.c")
    add_deps("tlpi_hdr")

target("8-7-2-my_getpwnam")
    set_kind("binary")
    add_files("src/exercises/8-7-2-my_getpwnam.c")
    add_deps("tlpi_hdr")

target("5-14-7-my_readv_writev")
    set_kind("binary")
    add_files("src/exercises/5-14-7-my_readv_writev.c")
    add_deps("tlpi_hdr")

target("proc_longjmp")
    set_kind("binary")
    add_files("src/proc/longjmp.c")
    add_deps("tlpi_hdr")

target("5-14-3-atomic_append")
    set_kind("binary")
    add_files("src/exercises/5-14-3-atomic_append.c")
    add_deps("tlpi_hdr")

target("6-9-3-my_setenv_unsetenv")
    set_kind("binary")
    add_files("src/exercises/6-9-3-my_setenv_unsetenv.c")
    add_deps("tlpi_hdr")

target("fileio_t_readv")
    set_kind("binary")
    add_files("src/fileio/t_readv.c")
    add_deps("tlpi_hdr")

target("fileio_copy")
    set_kind("binary")
    add_files("src/fileio/copy.c")
    add_deps("tlpi_hdr")

target("5-14-5-check_fd_dup")
    set_kind("binary")
    add_files("src/exercises/5-14-5-check_fd_dup.c")
    add_deps("tlpi_hdr")

target("proc_display_env")
    set_kind("binary")
    add_files("src/proc/display_env.c")
    add_deps("tlpi_hdr")

target("proc_necho")
    set_kind("binary")
    add_files("src/proc/necho.c")
    add_deps("tlpi_hdr")

target("memalloc_free_and_sbrk")
    set_kind("binary")
    add_files("src/memalloc/free_and_sbrk.c")
    add_deps("tlpi_hdr")

target("fileio_large_file")
    set_kind("binary")
    add_files("src/fileio/large_file.c")
    add_deps("tlpi_hdr")

target("proc_mem_segments")
    set_kind("binary")
    add_files("src/proc/mem_segments.c")
    add_deps("tlpi_hdr")

target("5-14-4-mydup")
    set_kind("binary")
    add_files("src/exercises/5-14-4-mydup.c")
    add_deps("tlpi_hdr")

target("7-4-2-my_malloc_free")
    set_kind("binary")
    add_files("src/exercises/7-4-2-my_malloc_free.c")
    add_deps("tlpi_hdr")

target("6-9-2-longjmp_fail")
    set_kind("binary")
    add_files("src/exercises/6-9-2-longjmp_fail.c")
    add_deps("tlpi_hdr")

target("5-14-2-file_append")
    set_kind("binary")
    add_files("src/exercises/5-14-2-file_append.c")
    add_deps("tlpi_hdr")

target("7-4-1-memalloc_free_and_sbrk")
    set_kind("binary")
    add_files("src/exercises/7-4-1-memalloc_free_and_sbrk.c")
    add_deps("tlpi_hdr")

target("idshow")
    set_kind("binary")
    add_files("src/proccred/idshow.c")
    add_deps("tlpi_hdr")

target("9-9-3-my_initgroups")
    set_kind("binary")
    add_files("src/exercises/9-9-3-my_initgroups.c")
    add_deps("tlpi_hdr")

target("calendar_time")
    set_kind("binary")
    add_files("src/time/calendar_time.c")
    add_deps("tlpi_hdr")

target("strtime")
    set_kind("binary")
    add_files("src/time/strtime.c")
    add_deps("tlpi_hdr")

target("show_time")
    set_kind("binary")
    add_files("src/time/show_time.c")
    add_deps("tlpi_hdr")

target("process_time")
    set_kind("binary")
    add_files("src/time/process_time.c")
    add_deps("tlpi_hdr")

target("t_sysconf")
    set_kind("binary")
    add_files("src/syslim/t_sysconf.c")
    add_deps("tlpi_hdr")

target("t_fpathconf")
    set_kind("binary")
    add_files("src/syslim/t_fpathconf.c")
    add_deps("tlpi_hdr")

target("procfs_pidmax")
    set_kind("binary")
    add_files("src/sysinfo/procfs_pidmax.c")
    add_deps("tlpi_hdr")

target("t_uname")
    set_kind("binary")
    add_files("src/sysinfo/t_uname.c")
    add_deps("tlpi_hdr")

target("direct_read")
    set_kind("binary")
    add_files("src/filebuff/direct_read.c")
    add_deps("tlpi_hdr")

target("13-9-4-printf_write")
    set_kind("binary")
    add_files("src/exercises/13-9-4-printf_write.c")
    add_deps("tlpi_hdr")

target("13-9-5-my_tail")
    set_kind("binary")
    add_files("src/exercises/13-9-5-my_tail.c")
    add_deps("tlpi_hdr")

target("t_mount")
    set_kind("binary")
    add_files("src/filesys/t_mount.c")
    add_deps("tlpi_hdr")

target("t_stat")
    set_kind("binary")
    add_files("src/files/t_stat.c")
    add_deps("tlpi_hdr")

target("t_chown")
    set_kind("binary")
    add_files("src/files/t_chown.c")
    add_deps("tlpi_hdr")

target("t_umask")
    set_kind("binary")
    add_files("src/files/t_umask.c")
    add_deps("tlpi_hdr")

target("15-7-3-nano-sec-time")
    set_kind("binary")
    add_files("src/exercises/15-7-3-nano-sec-time.c")
    add_deps("tlpi_hdr")