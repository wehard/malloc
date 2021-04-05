#!/bin/bash

if [ $(uname -s) = "Darwin" ]; then
	export DYLD_LIBRARY_PATH=$PWD
	export DYLD_INSERT_LIBRARIES=$PWD/libft_malloc.so
	export DYLD_FORCE_FLAT_NAMESPACE=1
else
	export LD_LIBRARY_PATH=$PWD
	export LD_INSERT_LIBRARIES=$PWD/libft_malloc.so
	export LD_FORCE_FLAT_NAMESPACE=1
fi
