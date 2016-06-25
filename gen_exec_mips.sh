#!/bin/sh

export LD_LIBRARY_PATH=/home/staff/lucas/mc723/hw_tools/systemc-2.3.1/lib-linux64/:$LD_LIBRARY_PATH
export PATH=$PATH:/home/staff/lucas/mc723/hw_tools/ArchC-2.2.0/installed/bin:/home/staff/lucas/mc723/hw_tools/mips-newlib-elf/bin/

MIPS_PATH='/home/ec2010/ra082674/MC723-LucasWanner/MC723A-profLucas/projeto3_grupo/mc723_proj3/mips-tlm-single/mips-tlm'

echo
echo $1
file="$1"
obj_mips="${file/.c/.mips}"

cd ${MIPS_PATH}/
mips-newlib-elf-gcc -specs=archc ${file} -o ${obj_mips} -O3
echo
echo "---------------------------------"
echo "eis o nome do objeto:"
echo ${obj_mips}
echo "---------------------------------"
./mips.x --load=${obj_mips}

