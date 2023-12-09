#!/usr/bin/bash
function compile_source {
    local compilation_output=$(g++ \
        --std=c++2a \
        -Winvalid-pch \
        -include stdafx.h \
        -Wl,--stack=268435456 \
        -O0 \
        -D_DEBUG \
        -D_GLIBCXX_DEBUG \
        -D_GLIBCXX_DEBUG_PEDANTIC \
        $1 -o $2 2>&1)

		echo "$compilation_output"
}

function run_source {
	$1 <$2 >$3 2>&1
	sed -i 's/\r$//' $3
}

# For compiling
if [ $1 == "compile" ]; then
	compile_source main.cpp a
fi

# For running
if [ $1 == "run" ]; then
	run_source ./a input output
	cat output
fi

# For stress testing
if [ $1 = "stress" ]; then
	# Compile everything
	compile_source main.cpp a.exe
	compile_source gen.cpp gen.exe
	compile_source brute.cpp brute.exe

	# Start running testcases until we find a failed testcase
	for ((i = 0; i < 1000; i++)); do
		echo "RUNNING TEST $i ..."
		./gen.exe $i >input

		run_source ./a.exe input output
		run_source ./brute.exe input brute_output

		diff=$(diff -w output brute_output)
		if [[ "${diff}" != "" ]]; then
			cat input
			echo "FAILED"
			break
		else
			echo "PASSED"
		fi
	done
fi

if [ $1 = "flush" ]; then
	mkdir done
	[ ! -s main.cpp ] || cp main.cpp "./done/$2.cpp"
	[ ! -s brute.cpp ] || cp brute.cpp "./done/$2_brute.cpp"

	# Clean up

	>main.cpp
	>brute.cpp
	>output
	>input

	rm brute_output
	rm *.exe
fi
