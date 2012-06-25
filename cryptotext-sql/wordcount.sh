#!/bin/bash
for i in {1..5048}
do
  for word in `cat files/body-$i.txt`
  do
    echo "$word" 
  done | echo "\"`sort -uf|wc -l`\"," >> words.csv
done
