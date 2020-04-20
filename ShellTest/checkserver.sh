#########################################################################
# File Name: checkserver.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2020年04月20日 星期一 17时49分52秒
#########################################################################
#!/bin/bash
#定时执行的脚本，检查某个进行是否存在，不存在就拉起

#检查参数
#echo "\$2:$2 \$#:$#"
if [ 2 -ne $# ]
then
	echo "usage:$0 check_name exe_shell"
	exit
fi
servername=$1
exeshell=$2

#检查进程是否运行
result=`ps -aux | grep -v 'grep' | grep $servername | grep -v $0`
#echo "result=$result"
if [[ "" == $result ]]
then 

	echo "exec $exeshell" 
	$exeshell
else 
	echo "$1 is running"
fi

