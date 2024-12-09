#!/bin/bash

# Print an error message and exit.
function bail {
    echo -e "$@" 1>&2
    exit 1
}

# Make sure we are being run from the build directory.
if [ ! -f "CMakeCache.txt" ] ; then
    bail "This script should be run from the build directory, i.e. where there is a CMakeCache.txt."
fi

# Gather directories.
source_dir=`grep "AdventOfCode-2024_SOURCE_DIR" "CMakeCache.txt" | cut -d '=' -f 2`
base_dir=`realpath "${source_dir}/../../"`
build_dir=`realpath .`
if [ -z "${source_dir}" ] ; then
    bail "Could not find source directory from CMakeCache.txt"
fi
if [ ! -d "${source_dir}" ] ; then
    bail "Source directory '${source_dir}' does not exists."
fi
if [ ! -d "${base_dir}" ] ; then
    bail  "Base directory '${base_dir}' does not exists."
fi
if [ ! -d "${build_dir}" ] ; then
    bail "Build directory '${buid_dir}' does not exists."
fi

year=`date +%Y`

clean="no"
day=""
tidy="no"

options="cd:th"

while getopts $options opt ; do
    case $opt in
        c)
            clean="yes"
            ;;
        d)
            day=$OPTARG
            ;;
        t)
            tidy="yes"
            ;;
        ?)
            bail "Usage: `basename $0` -$options\n" \
                "  c=clean build\n" \
                "  d=day INT\n" \
                "  t=cland-tidy\n" \
                "  h=help"
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

if [ "${clean}" == "yes" ] ; then
    make clean
fi
if [ "${tidy}" == "yes" ] ; then
    clang_tidy "${source_dir}/day${day}/day${day}_part1.cpp"
    clang_tidy "${source_dir}/day${day}/day${day}_part2.cpp"
fi
make day${day}_part1 day${day}_part2
if [ $? -ne 0 ] ; then
    bail "Compilation failed."
fi

function run_part {
    part=$1
    echo -e "\nRunning test cases for day ${day} part ${part}."

    cases_dir=`realpath "${base_dir}/cases/$year/day${day}/part${part}"`
    if [ ! -d "${cases_dir}" ] ; then
        bail "No test cases for day ${day} part ${part} at '${cases_dir}'."
    fi

    output_dir="./output/day${day}/part${part}"
    mkdir -p "${output_dir}"

    for test_case in "${cases_dir}/"*.input ; do
        test_name=`basename "$test_case" .input`
        expected_output="${cases_dir}/${test_name}.expected"
        output_file="${output_dir}/${test_name}.output"


        # Run the program.
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
