set(CMAKE_CXX_COMPILER "/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/kokkos-3.5.00-qgfi4dsfdllapnctkf7qcaphnp6htekp/bin/nvcc_wrapper")
set(CMAKE_CXX_COMPILER_ARG1 "")
set(CMAKE_CXX_COMPILER_ID "GNU")
set(CMAKE_CXX_COMPILER_VERSION "10.2.0")
set(CMAKE_CXX_COMPILER_VERSION_INTERNAL "")
set(CMAKE_CXX_COMPILER_WRAPPER "")
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "14")
set(CMAKE_CXX_COMPILE_FEATURES "cxx_std_98;cxx_template_template_parameters;cxx_std_11;cxx_alias_templates;cxx_alignas;cxx_alignof;cxx_attributes;cxx_auto_type;cxx_constexpr;cxx_decltype;cxx_decltype_incomplete_return_types;cxx_default_function_template_args;cxx_defaulted_functions;cxx_defaulted_move_initializers;cxx_delegating_constructors;cxx_deleted_functions;cxx_enum_forward_declarations;cxx_explicit_conversions;cxx_extended_friend_declarations;cxx_extern_templates;cxx_final;cxx_func_identifier;cxx_generalized_initializers;cxx_inheriting_constructors;cxx_inline_namespaces;cxx_lambdas;cxx_local_type_template_args;cxx_long_long_type;cxx_noexcept;cxx_nonstatic_member_init;cxx_nullptr;cxx_override;cxx_range_for;cxx_raw_string_literals;cxx_reference_qualified_functions;cxx_right_angle_brackets;cxx_rvalue_references;cxx_sizeof_member;cxx_static_assert;cxx_strong_enums;cxx_thread_local;cxx_trailing_return_types;cxx_unicode_literals;cxx_uniform_initialization;cxx_unrestricted_unions;cxx_user_literals;cxx_variadic_macros;cxx_variadic_templates;cxx_std_14;cxx_aggregate_default_initializers;cxx_attribute_deprecated;cxx_binary_literals;cxx_contextual_conversions;cxx_decltype_auto;cxx_digit_separators;cxx_generic_lambdas;cxx_lambda_init_captures;cxx_relaxed_constexpr;cxx_return_type_deduction;cxx_variable_templates;cxx_std_17;cxx_std_20")
set(CMAKE_CXX98_COMPILE_FEATURES "cxx_std_98;cxx_template_template_parameters")
set(CMAKE_CXX11_COMPILE_FEATURES "cxx_std_11;cxx_alias_templates;cxx_alignas;cxx_alignof;cxx_attributes;cxx_auto_type;cxx_constexpr;cxx_decltype;cxx_decltype_incomplete_return_types;cxx_default_function_template_args;cxx_defaulted_functions;cxx_defaulted_move_initializers;cxx_delegating_constructors;cxx_deleted_functions;cxx_enum_forward_declarations;cxx_explicit_conversions;cxx_extended_friend_declarations;cxx_extern_templates;cxx_final;cxx_func_identifier;cxx_generalized_initializers;cxx_inheriting_constructors;cxx_inline_namespaces;cxx_lambdas;cxx_local_type_template_args;cxx_long_long_type;cxx_noexcept;cxx_nonstatic_member_init;cxx_nullptr;cxx_override;cxx_range_for;cxx_raw_string_literals;cxx_reference_qualified_functions;cxx_right_angle_brackets;cxx_rvalue_references;cxx_sizeof_member;cxx_static_assert;cxx_strong_enums;cxx_thread_local;cxx_trailing_return_types;cxx_unicode_literals;cxx_uniform_initialization;cxx_unrestricted_unions;cxx_user_literals;cxx_variadic_macros;cxx_variadic_templates")
set(CMAKE_CXX14_COMPILE_FEATURES "cxx_std_14;cxx_aggregate_default_initializers;cxx_attribute_deprecated;cxx_binary_literals;cxx_contextual_conversions;cxx_decltype_auto;cxx_digit_separators;cxx_generic_lambdas;cxx_lambda_init_captures;cxx_relaxed_constexpr;cxx_return_type_deduction;cxx_variable_templates")
set(CMAKE_CXX17_COMPILE_FEATURES "cxx_std_17")
set(CMAKE_CXX20_COMPILE_FEATURES "cxx_std_20")
set(CMAKE_CXX23_COMPILE_FEATURES "")

set(CMAKE_CXX_PLATFORM_ID "Linux")
set(CMAKE_CXX_SIMULATE_ID "")
set(CMAKE_CXX_COMPILER_FRONTEND_VARIANT "")
set(CMAKE_CXX_SIMULATE_VERSION "")




set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_CXX_COMPILER_AR "/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/bin/gcc-ar")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_CXX_COMPILER_RANLIB "/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/bin/gcc-ranlib")
set(CMAKE_LINKER "/usr/bin/ld")
set(CMAKE_MT "")
set(CMAKE_COMPILER_IS_GNUCXX 1)
set(CMAKE_CXX_COMPILER_LOADED 1)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_CXX_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_CXX_COMPILER_ENV_VAR "CXX")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_CXX_COMPILER_ID_RUN 1)
set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS C;M;c++;cc;cpp;cxx;m;mm;mpp;CPP)
set(CMAKE_CXX_IGNORE_EXTENSIONS inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC)

foreach (lang C OBJC OBJCXX)
  if (CMAKE_${lang}_COMPILER_ID_RUN)
    foreach(extension IN LISTS CMAKE_${lang}_SOURCE_FILE_EXTENSIONS)
      list(REMOVE_ITEM CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${extension})
    endforeach()
  endif()
endforeach()

set(CMAKE_CXX_LINKER_PREFERENCE 30)
set(CMAKE_CXX_LINKER_PREFERENCE_PROPAGATES 1)

# Save compiler ABI information.
set(CMAKE_CXX_SIZEOF_DATA_PTR "8")
set(CMAKE_CXX_COMPILER_ABI "ELF")
set(CMAKE_CXX_BYTE_ORDER "LITTLE_ENDIAN")
set(CMAKE_CXX_LIBRARY_ARCHITECTURE "x86_64-pc-linux-gnu")

if(CMAKE_CXX_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_CXX_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_CXX_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_CXX_COMPILER_ABI}")
endif()

if(CMAKE_CXX_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-pc-linux-gnu")
endif()

set(CMAKE_CXX_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_CXX_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_CXX_CL_SHOWINCLUDES_PREFIX}")
endif()





set(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES "/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/cuda-11.5.1-qxr5lhjy626b6zf77kdpjp5jtam4amf6/targets/x86_64-linux/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/openmpi-4.1.2-2ygzubx5saylt3srmwplotbzfw4x4jfz/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libedit-3.1-20210216-ubfoiupgd3lz7mwxkfhfrn6oydz4kbcm/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/numactl-2.0.14-ctxictth6dmehlxlsg5n73ww3uoiwvfg/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libevent-2.1.12-odk4eetmnuyquq5dpl4lafc4mymmtqaa/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/openssl-1.1.1m-wg2ikoe4qp3pfrsrvxxvb3wch5xgxaza/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/hwloc-2.7.0-ten3shrb2vwb35hdhb324zj5gmtvanha/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/ncurses-6.2-o4athxcmby42uy7s5xclwnmwoli5iupg/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libpciaccess-0.16-s3lpkcutvgjkhdd3lzcq5qeumueqv36c/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libxml2-2.9.12-hteuc6odznp4irqdq6sodhxiqa6bqwoh/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/zlib-1.2.11-eelg7kokrgqczzhcmlxloww27vuv3vtw/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/xz-5.2.5-nczv6iijfczdetwst2jrg6it27t64l6z/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libiconv-1.16-2u23i6ksozqy7fog3nyuvejyh7cuwq4k/include;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/kokkos-3.5.00-qgfi4dsfdllapnctkf7qcaphnp6htekp/include;/opt/intel/compilers_and_libraries_2020.2.254/linux/mpi/intel64/include;/users/aalasand/hpcResearch/spack/var/spack/environments/kokkosTest/.spack-env/view/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/zstd-1.4.5-3boiausohz77fqap2ptmbwpoyy5a4ufg/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/zlib-1.2.11-pkmj6e72vggig3epxjcwxgzmxncaqnmp/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/mpc-1.1.0-g6zd7obocygw34horwj3qpbc4agdf5ao/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/mpfr-4.0.2-kluqbcjse55qsxxfjwuh6c4ffftf6an2/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/isl-0.21-ikicpxegev6vxa2trc3eudgpmsymci2x/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gmp-6.1.2-zn55wh7voutcbk46jzwgfyjfincjyuhh/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/include/c++/10.2.0;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/include/c++/10.2.0/x86_64-pc-linux-gnu;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/include/c++/10.2.0/backward;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include;/usr/local/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/include;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include-fixed;/usr/include")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "cudadevrt;cudart_static;rt;pthread;dl;stdc++;m;gcc_s;gcc;c;gcc_s;gcc")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/cuda-11.5.1-qxr5lhjy626b6zf77kdpjp5jtam4amf6/targets/x86_64-linux/lib/stubs;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/cuda-11.5.1-qxr5lhjy626b6zf77kdpjp5jtam4amf6/targets/x86_64-linux/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/kokkos-3.5.00-qgfi4dsfdllapnctkf7qcaphnp6htekp/lib64;/users/aalasand/hpcResearch/spack/var/spack/environments/kokkosTest/.spack-env/view/lib64;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/lib64;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/lib/gcc/x86_64-pc-linux-gnu/10.2.0;/lib64;/usr/lib64;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/openmpi-4.1.2-2ygzubx5saylt3srmwplotbzfw4x4jfz/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libedit-3.1-20210216-ubfoiupgd3lz7mwxkfhfrn6oydz4kbcm/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/numactl-2.0.14-ctxictth6dmehlxlsg5n73ww3uoiwvfg/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libevent-2.1.12-odk4eetmnuyquq5dpl4lafc4mymmtqaa/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/openssl-1.1.1m-wg2ikoe4qp3pfrsrvxxvb3wch5xgxaza/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/hwloc-2.7.0-ten3shrb2vwb35hdhb324zj5gmtvanha/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/ncurses-6.2-o4athxcmby42uy7s5xclwnmwoli5iupg/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libpciaccess-0.16-s3lpkcutvgjkhdd3lzcq5qeumueqv36c/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/cuda-11.5.1-qxr5lhjy626b6zf77kdpjp5jtam4amf6/lib64;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libxml2-2.9.12-hteuc6odznp4irqdq6sodhxiqa6bqwoh/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/zlib-1.2.11-eelg7kokrgqczzhcmlxloww27vuv3vtw/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/xz-5.2.5-nczv6iijfczdetwst2jrg6it27t64l6z/lib;/users/aalasand/hpcResearch/spack/opt/spack/linux-centos7-haswell/gcc-10.2.0/libiconv-1.16-2u23i6ksozqy7fog3nyuvejyh7cuwq4k/lib;/opt/intel/compilers_and_libraries_2020.2.254/linux/mpi/intel64/libfabric/lib;/opt/intel/compilers_and_libraries_2020.2.254/linux/mpi/intel64/lib;/users/aalasand/hpcResearch/spack/var/spack/environments/kokkosTest/.spack-env/view/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gcc-10.2.0-3kjqvw7masskmxqtxblo5khyshwe6zuw/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/zstd-1.4.5-3boiausohz77fqap2ptmbwpoyy5a4ufg/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/zlib-1.2.11-pkmj6e72vggig3epxjcwxgzmxncaqnmp/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/mpc-1.1.0-g6zd7obocygw34horwj3qpbc4agdf5ao/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/mpfr-4.0.2-kluqbcjse55qsxxfjwuh6c4ffftf6an2/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/isl-0.21-ikicpxegev6vxa2trc3eudgpmsymci2x/lib;/opt/spack/opt/spack/linux-centos7-haswell/gcc-4.8.5/gmp-6.1.2-zn55wh7voutcbk46jzwgfyjfincjyuhh/lib")
set(CMAKE_CXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
