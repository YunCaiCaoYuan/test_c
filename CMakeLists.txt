CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(test_c)

#AUX_SOURCE_DIRECTORY(io_reuse/select_server SRC_LIST)
#ADD_EXECUTABLE(test_sh ${SRC_LIST})
#AUX_SOURCE_DIRECTORY(io_reuse/select_client SRC_LIST2)
#ADD_EXECUTABLE(test_sh2 ${SRC_LIST2})

#AUX_SOURCE_DIRECTORY(io_reuse SRC_LIST)
#ADD_EXECUTABLE(io_reuse ${SRC_LIST})

#AUX_SOURCE_DIRECTORY(io_reuse/poll_server2 SRC_LIST)
#ADD_EXECUTABLE(poll_server2 ${SRC_LIST})

AUX_SOURCE_DIRECTORY(io_reuse/mytalk/mytalk_server SRC_LIST)
ADD_EXECUTABLE(mytalk_server ${SRC_LIST})
#AUX_SOURCE_DIRECTORY(io_reuse/mytalk/mytalk_client SRC_LIST2)
#ADD_EXECUTABLE(mytalk_client ${SRC_LIST2})