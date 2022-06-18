#!/bin/bash

python gen.py

for f in test/*.in.*
do
  echo "bla" $f
  ./dugput < $f > ${f/in/out}
  ./dugput_output_gen < $f > ${f/in/conf}
done
