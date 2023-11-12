#!/bin/bash

for f in $(ls ./tests/*.txt); do 
	./a.out <$f > ./tests/`basename $f .txt`.output; 
    echo "========================================================";
	echo "FILE:" `basename $f .output`;
	cat ./tests/`basename $f .txt`.output;
	echo "--------------------------------------------------------";
	cat ./tests/`basename $f `.expected;
	echo "========================================================";
done;

rm tests/*.output
