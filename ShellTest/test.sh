#########################################################################
# File Name: test.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2020年04月18日 星期六 16时21分25秒
#########################################################################
#!/bin/bash
#将 字符串"A=8&B=100"中的A和B的值解析出来

str="A=8&B=100"
index=`expr index "$str" \&`
if [ 0 -eq $index  ]
then 
	echo "找不到指定字符"
	exit 0
elif [ 0 -ne $index ] 
then
	echo "value not 0"
fi

#从分隔符开始将字符串分割
str1=${str:0:$(($index-1))}
str2=${str:$index}

#再分别查找字符"="
index=`expr index "$str1" =`
if [[ 0 == $index ]]
then 
	echo "not found ="
	exit
fi 

A=${str1:index}
echo "A 的值: $A"





