#!/bin/bash
SGOS_CONF_DIR=/etc/smart_getway
SGOS_BIN_DIR=/usr/local/bin/smart_getway
SGOS_LIB_DIR=/usr/local/lib/smart_getway
SGOS_INC_DIR=/usr/local/include/smart_getway
SGOS_USR_LOCAL_LIB_DIR=/usr/local/lib/


sys_file_clear_check()
{
	if [ -d ${SGOS_CONF_DIR} ];then
		echo ${SGOS_CONF_DIR} is exsist
		return 0
	fi
	if [ -d ${SGOS_BIN_DIR} ];then
		echo ${SGOS_BIN_DIR} is exsist
		return 0
	fi
	if [ -d ${SGOS_LIB_DIR} ];then
		echo ${SGOS_LIB_DIR} is exsist
		return 0
	fi
	if [ -d ${SGOS_INC_DIR} ];then
		echo ${SGOS_INC_DIR} is exsist
		return 0
	fi
	return 1
}
sys_file_exsist_check()
{
	if [ ! -d ${SGOS_CONF_DIR} ];then
		echo ${SGOS_CONF_DIR} is not exsist
		return 0
	fi
	if [ ! -d ${SGOS_BIN_DIR} ];then
		echo ${SGOS_BIN_DIR} is not exsist
		return 0
	fi
	if [ ! -d ${SGOS_LIB_DIR} ];then
		echo ${SGOS_LIB_DIR} is not exsist
		return 0
	fi
	if [ ! -d ${SGOS_INC_DIR} ];then
		echo ${SGOS_INC_DIR} is not exsist
		return 0
	fi
	return 1
}
sys_uninstall()
{
	rm ${SGOS_CONF_DIR} -fr
	rm ${SGOS_BIN_DIR} -fr
	rm ${SGOS_LIB_DIR} -fr
	rm ${SGOS_INC_DIR} -fr
}

sys_install()
{
	mkdir -p ${SGOS_CONF_DIR}
	mkdir -p ${SGOS_BIN_DIR}
	mkdir -p ${SGOS_LIB_DIR}
	mkdir -p ${SGOS_INC_DIR}

	cp ../build/install/etc/* ${SGOS_CONF_DIR}/ -a
	cp ../build/install/bin/* ${SGOS_BIN_DIR}/ -a
	cp ../build/install/lib/* ${SGOS_LIB_DIR}/ -a
	cp ../build/install/include/* ${SGOS_INC_DIR}/ -a


	chmod 777 ${SGOS_CONF_DIR}/*
	chmod 777 ${SGOS_BIN_DIR}/*
	chmod 777 ${SGOS_LIB_DIR}/*
	chmod 777 ${SGOS_INC_DIR}/*
}

sys_uninstall
sys_file_clear_check
if [ $? != 1 ]; then
	echo dcos uninstall failed
	exit 1
fi

sys_install
sys_file_exsist_check
if [ $? != 1 ]; then
	echo dcos install failed
	exit 1
fi
echo smart_getway finish install

exit 0
