#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./dugput < $f > ${f/in/out}
  echo "bla" $f
  #./dugput_output_gen < $f > ${f/in/conf}
done
