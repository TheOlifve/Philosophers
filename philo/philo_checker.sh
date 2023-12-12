#!/bin/bash

p_cnt=$1
d_time=$2
e_time=$3
s_time=$4
m_cnt=$5

if [ -e "checker_out" ]
then
	rm checker_out
fi

if [ $m_cnt ]
then
		./philo $p_cnt $d_time $e_time $s_time $m_cnt >checker_out
else
		./philo $p_cnt $d_time $e_time $s_time $m_cnt
fi

for ((i=1; i<=$p_cnt; i++))
do
	meal=$(cat <checker_out | grep -c "$i is eating")
	echo "philo[$i] ate $meal times"
	if [ $(cat <checker_out | grep -c "$i died") != "0" ]
	then
		d_check="philo[$i] died"
	fi
done

echo -n $d_check