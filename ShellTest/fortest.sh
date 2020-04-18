#########################################################################
# File Name: test.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2020年04月18日 星期六 16时21分25秒
#########################################################################
#!/bin/bash
#将 字符串"A=8&B=100"中的A和B的值解析出来

echo "shell p0=$0"
str="A=8&B=100&C=209"
idx=`expr index "$str" \&`

count=0
arrKey=()
arrValue=()

function myfun()
{
	echo "my function,p0=$0 p1=$1"
	local s=$1
	local idx1=`expr index "$s" =`
	if [ 0 != $idx1 ]
	then 
		key=${s:0:$(($idx1-1))}
		value=${s:$idx1}
		arrKey[$count]=$key
		arrValue[$count]=$value
		count=$(($count+1 ))
		echo -e "$key=$value count=$count\n"
	fi
}
while [ 0 != $idx ]
do 
	s=${str:0:$(($idx-1))}
	myfun $s
	str=${str:$idx}
	idx=`expr index "$str" \&`
done

if [[ "" != $str ]]
then 
	myfun $str
fi

for item in ${arrKey[*]}
do 
	echo "key:$item"
done

for item in ${arrValue[*]}
do 
	echo "value:$item"
done

