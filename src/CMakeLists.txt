find_package(Magnum REQUIRED GL Shaders Trade MeshTools Primitives)

if(NOT CORRADE_TARGET_ANDROID)
    find_package(Magnum REQUIRED Sdl2Application)
else()
    find_package(Magnum REQUIRED AndroidApplication)
endif()

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

file(GLOB native_heads "*.h")
file(GLOB native_srcs "*.cpp")

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

corrade_add_resource(MagnumBootstrapData_RESOURCES resources/resources.conf)

if(NOT CORRADE_TARGET_ANDROID)
    add_executable(MyApplication ${native_heads} ${native_srcs} ${MagnumBootstrapData_RESOURCES})
else()
    add_library(MyApplication SHARED ${native_heads} ${native_srcs} ${MagnumBootstrapData_RESOURCES})
endif()

target_link_libraries(MyApplication PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::Shaders
    Magnum::Trade
    Magnum::MeshTools
    Magnum::Primitives)
