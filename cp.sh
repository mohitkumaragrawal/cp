#!/usr/bin/bash

function compile_source {
	echo "Compiling $1 to $2"
	local compilation_result=$(g++ \
		--std=c++2a \
		-Wall \
		-Wextra \
		-Wshadow \
		-O2 \
		-Wno-sign-compare \
		-Wno-unused-parameter \
		-D_DEBUG -D_GLIBCXX_DEBUG \
		-D_GLIBCXX_DEBUG_PEDANTIC \
		$1 -o $2)
	echo $compilation_result
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
	compile_source main.cpp a
	compile_source gen.cpp gen
	compile_source brute.cpp brute

	# Start running testcases until we find a failed testcase
	for ((i = 0; i < 1000; i++)); do
		echo "RUNNING TEST $i ..."
		./gen $i >input

		run_source ./a input output
		run_source ./brute input brute_output

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
