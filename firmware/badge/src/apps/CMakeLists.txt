# Add all our apps
FILE(GLOB app_sources *.c)
target_sources(app PRIVATE ${app_sources})