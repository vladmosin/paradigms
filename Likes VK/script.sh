#!/bin/bash

function ins_sort() {
for ((i=1;i<ind;i++))
do
  curlike=${lk[$i]}
  curlink=${lin[$i]}
  j=$(($i - 1))
    while (( $curlike > ${lk[j]} ))
    do
      lk[$j+1]=${lk[j]}
      lin[$j+1]=${lin[j]}
      j=$(($j-1))
      if (( $j == -1 ))
      then
        break
      fi
    done
  lk[$j+1]=$curlike
  lin[$j+1]=$curlink
done      
for((i=0;i<ind;i++))
do
    echo "${lin[$i]} ${lk[$i]}"
done    
}

bit=0
ind=0
end=0
even=0
for((i=0;i<1000;i++))
do
    base[$i]=0
done
while (( $end == 0 ))
do
while read line;
do
    links[$ind]=$line
    ind=$((ind+1))
done < <(wget -O - 2> /dev/null https://vk.com/album1_0 | grep -oP 'url(.*?\.jpg)' | sed -r 's/url\(//g')
ind=0
while read photo;
do
    photos[$ind]=$photo
    ind=$((ind+1))
done < <(wget -O - 2> /dev/null https://vk.com/album1_0 | grep -oP '\"\/photo1_[0-9]*\"' | sed -r 's/\"//g
                                                                                                    s/\///')
for((i=0;i<$((ind - 1));i++))
do
    num=0
    while read like;
    do
        lik[$num]=$like
        num=$((num+1))
    done < <(wget -O - 2> /dev/null https://vk.com/${photos[$i]} | grep -oP '\"likes\"\:[0-9]*' | sed 's/\"//g
                                                                                                       s/likes\://g')
    likes[$i]=${lik[$(($num / 2))]}
done
likes[$((ind-1))]=${lik[$(($num/2+1))]}
if (( $bit == 0 ))
then
    for ((i=0;i<ind;i++))
    do
        base[$i]=${likes[$i]}
        lk[$i]=${likes[$i]}
        lin[$i]=${links[$i]}
    done
    ins_sort
    bit=1
else
for((i=0;i<ind;i++))
do
    if ! ((${likes[$i]} == ${base[$i]}))
    then
        dif=$((${likes[$i]} - ${base[$i]}))
        echo "${links[$i]} $dif"
        base[$i]=${likes[$i]}
    fi
done
fi
sleep 600
done
