#!/bin/sh
is_regular_file(){
    if [ -e ${1} ]
    then
        echo "anonymous file exist"
        if [ -f ${1} ]
        then
            echo "regular file"
            return 0
        fi
        if [ -d ${1} ]
        then
            echo "directory file or socket file"
            return 1
        fi
    fi
    echo "file not exist"
    return 1
}   

main(){
    echo "positional arg 1 : ${1}"
    is_regular_file ${1}
    res=$?
    if [ 1 -eq $res ]
    then 
        echo "file non regular"
        exit 1
    fi
    echo `readelf -h ${1} | grep "Entry point address"`
    echo `readelf -S ${1} | grep ".text"`
    exit 0
}

main ${1}
