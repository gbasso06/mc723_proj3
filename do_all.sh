#!/bin/sh

if [ $# -lt 1 ];
  then
   echo "usage:./do_all.sh nome_do_arquivo.c"
   exit 1
fi


SCRIPTS_PATH='/home/ec2010/ra082674/MC723-LucasWanner/MC723A-profLucas/projeto3_grupo/mc723_proj3/'
cd ${SCRIPTS_PATH}/
./compile.sh

echo "---------------------------------"
echo "arquivo a ser loaded no mips.x:"
echo $1
echo "---------------------------------"
./gen_exec_mips.sh $1
