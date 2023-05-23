#! /bin/bash
array=(1 2 3 4 5) # 赋值操作必须没有空格
i=0
for var in ${array[@]}
do
    echo "array[$i]: $var"
    i=`expr $i + 1` # 赋值操作必须没有空格
i=0
done

declare -A MAP
MAP[key1]=1
MAP[key2]=2
MAP[key3]=hello

for key in ${!MAP[@]}
do 
    echo "$key ------------> ${MAP[$key]}"
done