#!/bin/bash

# argv[1]: the number of triangles (counting degenerate cases)
# argv[2]: the halfwidth of the world
# argv[3]: the minimal halfwidth of any bounding box
# argv[4]: the maximal halfwidht of any bounding box

green="\033[1;32m"
red="\033[1;31m"
default="\033[0m"

top_dir="../../"
build_dir="${top_dir}build/"
data="data/"

test_generator="generator"
test_driver="driver"

function build_from_sources
{
    cmake ${top_dir} -B ${build_dir} -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++-11

    echo -en "\n"
    echo "Building test generator..."
    cmake --build ${build_dir} --target ${test_generator}
    echo -en "\n"

    echo "Building test driver..."
    cmake --build ${build_dir} --target ${test_driver}
    echo -en "\n"

    echo "Installing test generator and test driver..."
    cmake --install ${build_dir}
    echo -en "\n"
}

function generate_test
{
    local n_shapes=$1
    local world_halfwidth=$2
    local min_bb_halfwidth=$3
    local max_bb_halfwidth=$4

    mkdir -p ${data}

    echo "Generating test..."
    bin/generator ${n_shapes} ${world_halfwidth} ${min_bb_halfwidth} ${max_bb_halfwidth} > "${data}${n_shapes}.test"
    echo -en "\n"
}

function generate_answer
{
    local n_shapes=$1

    echo "Generating answer..."
    python3 src/model_collision_manager.py "${data}${n_shapes}.test" > "${data}${n_shapes}.ans"
    echo -en "\n"
}

function run_test
{
    local n_shapes=$1

    echo "Running test..."
    bin/driver < "${data}${n_shapes}.test" > "${data}${n_shapes}.res"
    echo -en "\n"

    echo -en "Result: "
    if diff -Z "${data}${n_shapes}.ans" "${data}${n_shapes}.res" > /dev/null
    then
        echo -e "${green}passed${default}"
    else
        echo -e "${red}failed${default}"
    fi
}

if [ $# -ne 4 ]
then
    echo "Testing script requires exactly 4 arguments"
else
    n_shapes=$1

    if [ $n_shapes -le 0 ]
    then
        echo "The number of trianges should be a positive integer number"
    else
        # Positivity of next variables is checked in the generator of tests
        world_halfwidth=$2
        min_bb_halfwidth=$3
        max_bb_halfwidth=$4

        build_from_sources
        generate_test $n_shapes $world_halfwidth $min_bb_halfwidth $max_bb_halfwidth
        generate_answer $n_shapes
        run_test $n_shapes
    fi
fi
