set(SOURCE_FILES
             geointerface.cpp
             )

add_library(geo STATIC ${SOURCE_FILES})
target_link_libraries(geo kdtree)

add_library(geo_so SHARED ${SOURCE_FILES})
target_link_libraries(geo_so kdtree)
set_target_properties(geo_so PROPERTIES OUTPUT_NAME "geo")

#add_library(geo_so SHARED ${SOURCE_FILES})
#