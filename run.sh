#!/bin/sh

module load cfitsio-3.370
export RTALIB=/home/zollino/testing/RTAlib
export MYSQL_CXX_CNT=/home/zollino/mysql-connector-cpp-install/
export BOOST_PATH=/home/zollino/boost_1_67_0
export LD_LIBRARY_PATH=/home/zollino/mysql-connector-cpp-install/lib64:$LD_LIBRARY_PATH 

make clean
make
