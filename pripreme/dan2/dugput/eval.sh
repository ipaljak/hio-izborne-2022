for f in test/*.in.*
do
  echo "Testing..." $f
  time ./$1 < $f > out
  ./checker $f ${f/in/out} out ${f/in/conf}
done
