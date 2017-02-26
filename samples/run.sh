#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELL='\033[0;33m' # bold yellow

NC='\033[0m' # No Color

dir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
colorDiff="s/^-/\x1b[31m-/;s/^+/\x1b[32m+/;s/^@/\x1b[34m@/;s/$/\x1b[0m/"

cd $dir
set -o pipefail

for f in *.glsl; do
    if [ "${f:0:11}" == "extraCredit" ] && [ "$#" -ne 0 ] ; then
	    printf "${YELL}Skipping $f${NC}\n"
	    continue
    else
     
        diff -uw <(../glc <$f 2>&1 ) ${f%%.*}.out | sed $colorDiff
        result=$?
    	printf "Test case %s: " ${f%%.*} 
 
    	
    	if (exit $result) ; then
        	printf "${GREEN}PASS${NC}\n"
   	else
        	printf "${RED}FAIL${NC} (${GREEN}+Reference output ${RED}-Your output${NC})\n"  
    	fi
    fi
   
done



