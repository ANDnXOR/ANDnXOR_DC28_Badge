# Add all our sources
FILE(GLOB app_sources *.c gfx/*.c)
target_sources(app PRIVATE ${app_sources})

add_subdirectory(apps)
add_subdirectory(drivers)
add_subdirectory(lib)

#Disable custom sections
#zephyr_linker_sources(SECTIONS wh_app.ld)