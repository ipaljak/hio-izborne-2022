[ -e temp ] || mkfifo temp
./server $2 flog foutput < temp | ./$1 > temp
tail flog -n 2
