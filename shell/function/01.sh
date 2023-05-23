#! /bin/bash

fun_test1()
{
    echo "test1 start"
    var=20
    return $var
}

fun_test2()
{
    echo "test2 start"

    echo '$#' :  $#
    echo '$0' :  $0
    echo '$1' :  $1
    echo '$2' :  $2

    return `expr $1 + $2`
}

echo $0 start
echo "====================="

fun_test1
var=$?
echo $var
echo "====================="

fun_test2 10 20
var2=$?
echo $var2

