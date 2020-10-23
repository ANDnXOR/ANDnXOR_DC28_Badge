# Add all our sources
FILE(GLOB_RECURSE mybasic_sources *.c)
target_sources(app PRIVATE ${mybasic_sources})