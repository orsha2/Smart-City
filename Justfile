set shell := ["bash", "-cu"]

build_dir := "build"
src_dir := "src"

default:
    @just --list

_configure:
    cmake -S . -B {{build_dir}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug 

build_debug: _configure
    cmake --build {{build_dir}} --parallel

run_debug: build_debug
    ./{{build_dir}}/app

test: build_debug
    pushd  {{build_dir}}; ctest --output-on-failure; popd

format:
    find {{src_dir}} -type f -regextype posix-extended -regex '.*\.(c|h)' -print0 | \
        xargs -0 clang-format-18 -i

format-check:
    find {{src_dir}} -type f -regextype posix-extended -regex '.*\.(c|h)' -print0 | \
        xargs -0 clang-format-18 --dry-run --Werror

lint: _configure
    find {{src_dir}} -type f -regextype posix-extended -regex '.*\.c' -print0 | \
        xargs -0 clang-tidy-18 -p {{build_dir}}

check: format-check lint test

clean:
    rm -rf {{build_dir}}