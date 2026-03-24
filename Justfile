set shell := ["bash", "-cu"]

build_dir := "build"
src_dir := "src"

default:
    @just --list

_configure_debug:
    cmake -S . -B {{build_dir}} -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: _configure_debug
    cmake --build {{build_dir}} --parallel

test: build
    pushd build; ctest --output-on-failure -V; popd

format:
    find {{src_dir}} -type f -regextype posix-extended -regex '.*\.(c|h)' -print0 | \
        xargs -0 clang-format-21 -i

format-check:
    find {{src_dir}} -type f -regextype posix-extended -regex '.*\.(c|h)' -print0 | \
        xargs -0 clang-format-21 --dry-run --Werror

lint: _configure_debug
    find {{src_dir}} -type f -regextype posix-extended -regex '.*\.c' -print0 | \
        xargs -0 clang-tidy-21 -p {{build_dir}}

check: format-check lint test

clean:
    rm -rf {{build_dir}}