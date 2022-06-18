#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./points < $f > ${f/.in./.out.}
done
