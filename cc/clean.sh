#########################################################################
# File Name: clean.sh
# Author: JayGuan
# mail:
# Created Time: Mon 13 Sep 2021 11:24:51 PM PDT
#########################################################################
#!/bin/bash
i=0
for one in $(ls | cat)
do
  #cat $i
  i=$(expr $i + 1);
  #cat 'and $i'
  id=$(ipcs -m | awk  '{print $2}' | awk "NR == $i ") 
  echo "echo:"$id

  ipcrm --shmem-id $id
  #ipcrm --semaphore-id $id

done
