for f in test/*.in.*
do
  echo $f
  timeout 1s ./$1 < $f > out
  DIFF=$(diff out ${f/.in/.out})
  if [ "$DIFF" != "" ]
  then
    echo "WA"
  fi
done