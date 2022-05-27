#!/bin/bash

for f in test/*.in.*
do
  echo $f
  ./$1 < $f > a1out
  ./checker actor1 $f ${f/\.in\./\.config\.} a1out a2in
  ./$1 < a2in > a2out
  ./checker actor2 $f ${f/\.in\./\.config\.} a1out a2in a2out
done
