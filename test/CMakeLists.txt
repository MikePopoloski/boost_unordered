find_package(Boost CONFIG COMPONENTS unit_test_framework REQUIRED)

function(def_test SOURCE)
  set(NAME ${SOURCE})
  get_filename_component(NAME ${NAME} NAME_WE)
  string(MAKE_C_IDENTIFIER ${NAME} NAME)

  add_executable(${NAME} ${SOURCE})
  target_link_libraries(${NAME} PRIVATE Boost::unit_test_framework)
  target_compile_definitions(${NAME} PRIVATE BOOST_UNORDERED_FOA_TESTS)
  target_include_directories(${NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

  add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()

def_test(unordered/fwd_set_test.cpp)
