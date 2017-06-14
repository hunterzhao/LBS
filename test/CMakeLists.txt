set(SERVER_SOURCE server.cpp)
set(CLIENT_SOURCE client.cpp)

add_executable(server ${SERVER_SOURCE})
target_link_libraries(server lbs_framework)

add_executable(client ${CLIENT_SOURCE})
target_link_libraries(client)