set(SOURCE_FILES
             lbsserver.cpp
             task.cpp
             clientinfo.cpp
             until.cpp
             message.pb.cc
             )

add_library(lbs_framework STATIC ${SOURCE_FILES})
target_link_libraries(lbs_framework)
add_library(lbs_framework_so SHARED ${SOURCE_FILES})
set_target_properties(lbs_framework_so PROPERTIES OUTPUT_NAME "lbs_framework")