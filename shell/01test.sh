#! /bin/bash    # 说明使用的解释器类型

DATA=1  # 等号两边不能有空格
echo "DATA : $DATA\n"   #变量使用要加钱$

DATA2="hello $DATA"
DATA3='hello $DATA' # 单引号会全部转换成字符串

echo "$DATA2\n"
echo "$DATA3\n"

