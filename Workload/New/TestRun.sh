 #!/bin/sh
  echo enter file name
  read fname
   
   exec<$fname
   value=0
   while read line
   do
            ./proxyServer_client $line >> Workload_Random_RandomCache_350k.txt
            echo $line;
   done
   echo "****$line";
