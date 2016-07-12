#!/bin/bash
d=`date "+%Y%m%d%H%M%S"`
echo git begin 
git add *
git commit -m $d
#git push
