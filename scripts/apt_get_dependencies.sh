#!/bin/bash

# update apt-get
apt-get update

# sed reads the file, skipping lines 1,2,3 (omit header)
# pipes it into a while loop and reads line by line
# see docs: `man sed` for more info

sed "1,2d" ./dependencies.csv | while read line
do
    # use awk to extract the lib name from the line, and replace the ',' with a linebreak
    # see docs: `man awk`, `man tr` for more info
    LIB=$(echo $line | awk '{print $1}' | tr ',' '\n')
    echo "Apt-getting $LIB"
    apt-get install $LIB
    echo ""
done
