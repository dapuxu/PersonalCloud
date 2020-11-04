#!/bin/sh

cd app_server
make clean;make all
cp cloud-server ../install/
cd ../app_service
make clean;make all
cp cloud-service ../install/
cd ..

