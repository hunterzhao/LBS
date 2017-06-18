#!bin/bash
protoc message.proto -I=. --cpp_out=.

if test -e /include/message.pb.h
then
rm /include/message.pb.h && rm /src/message.pb.cc && rm /test/message.pb.cc
fi
mv message.pb.h /include/message.pb.h && cp message.pb.cc src/message.pb.cc && mv message.pb.cc test/message.pb.cc


