set(SERVER_SOURCE server.cpp)
set(CLIENT_SOURCE client.cpp message.pb.cc)
set(UNIT_TESTR_SOURCE unit_test.cpp)

add_executable(server ${SERVER_SOURCE})
target_link_libraries(server lbs_framework protobuf geo glog)

add_executable(client ${CLIENT_SOURCE})
target_link_libraries(client protobuf)

#add_executable(unittest ${UNIT_TESTR_SOURCE})
#target_link_libraries(unittest lbs_framework protobuf geo)

