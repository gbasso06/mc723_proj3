#!/bin/sh

export LD_LIBRARY_PATH=/home/staff/lucas/mc723/hw_tools/systemc-2.3.1/lib-linux64/:$LD_LIBRARY_PATH
export PATH=$PATH:/home/staff/lucas/mc723/hw_tools/ArchC-2.2.0/installed/bin:/home/staff/lucas/mc723/hw_tools/mips-newlib-elf/bin/

MIPS_PATH='/home/ec2010/ra082674/MC723-LucasWanner/MC723A-profLucas/projeto3_grupo/mc723_proj3/mips-tlm-single/mips-tlm'

echo
echo "cd ${MIPS_PATH}/"

cd ${MIPS_PATH}/

echo
echo "acsim mips.ac -abi"
acsim mips.ac -abi


echo
orig='SRCS := main.cpp $(ACSRCS) $(ACFILES)  $(MODULE)_syscall.cpp'
repl='SRCS := main.cpp $(ACSRCS) $(ACFILES) $(MODULE)_syscall.cpp ac_tlm_peripheral.cpp ac_tlm_mem.cpp ac_tlm_router.cpp'
#echo "sed \"s/${orig}/${repl}/\" Makefile.archc> _Makefile.archc"
sed "s/${orig}/${repl}/" Makefile.archc > _Makefile.archc

#make -C ${MIPS_PATH}/ -f ${MIPS_PATH}/Makefile.archc clean
make -f ${MIPS_PATH}/_Makefile.archc clean
make -f ${MIPS_PATH}/_Makefile.archc 
#make -C ${MIPS_PATH}/ -f ${MIPS_PATH}/Makefile.archc 
