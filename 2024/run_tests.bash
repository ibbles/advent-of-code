#!/bin/bash

function bail {
    echo "$1" 1>&2
    exit 1
}

if [ ! -f "Makefile" ] ; then
    bail "This script should be run from the build directory, i.e. where there is a CMakeLists.txt."
fi

day=""
year=`date +%Y`

while getopts "d:" opt ; do
    case $opt in
        d)
            day=$OPTARG
            ;;
    esac
done

if [ -z "$day" ] ; then
    bail "-d must be used to provide a day number."
fi

function clang_tidy {
    file=$1
    clang_tidy_disabled_checks="-llvmlibc-*,-modernize-use-trailing-return-type,-altera-unroll-loops"
    clang-tidy --warnings-as-errors="*" -checks="*,${clang_tidy_disabled_checks}" "$file" --
    if [ $? -ne 0 ] ; then
        bail "Clang Tidy failed."
    fi
}

make clean
clang_tidy ../repository/2024/day${day}/day${day}_part1.cpp
clang_tidy ../repository/2024/day${day}/day${day}_part2.cpp
make day${day}_part1 day${day}_part2
if [ $? -ne 0 ] ; then
    bail "Compilation failed."
fi

function run_part {
    part=$1
    echo -e "\nRunning test cases for day ${day} part ${part}."

    cases_dir=`realpath "../cases/$year/day${day}/part${part}"`
    if [ ! -d "${cases_dir}" ] ; then
        bail "No test cases for day ${day} part ${part} at '${cases_dir}'."
    fi

    output_dir="./output/day${day}/part${part}"
    mkdir -p "${output_dir}"

    for test_case in "${cases_dir}/"*.input ; do
        test_name=`basename "$test_case" .input`
        expected_output="${cases_dir}/${test_name}.expected"
        output_file="${output_dir}/${test_name}.output"


        # Runt he program.
        # The ugly bit at the start is a workaround for a bug with the santizers
        # in combination with adress space layout randomization.
        # See https://stackoverflow.com/a/78302537
        # The symptom is an infinite loop of
        #    AddressSanitizer:DEADLYSIGNAL
        # when running the application.
        /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 ./day${day}/day${day}_part${part} < "${test_case}" > "${output_file}"


        diff "${expected_output}" "${output_file}"
        if [ $? -ne 0 ] ; then
            echo "Failed test case '${test_name}'."
            echo "Expected:"
            cat "${expected_output}"
            echo "Actual:"
            cat "${output_file}"
        else
            echo "Passed '${test_name}'."
        fi
    done
}

run_part 1
run_part 2
