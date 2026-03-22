#!/usr/bin/env bash

set -euo pipefail

readonly COMMIT_MSG_FILE=".git/COMMIT_EDITMSG"
readonly MAIN_BRANCH="main"
readonly MASTER_BRANCH="master"

get_commit_message() {
    sed -e '/^#/d' -e '/^[[:space:]]*$/d' "${COMMIT_MSG_FILE}" | head -n 1
}

get_branch_name() {
    git rev-parse --abbrev-ref HEAD
}

is_mainline_branch() {
    local branch_name="$1"

    [[ "${branch_name}" == "${MAIN_BRANCH}" || "${branch_name}" == "${MASTER_BRANCH}" ]]
}

is_merge_commit() {
    local git_dir

    git_dir="$(git rev-parse --git-dir)"
    [[ -f "${git_dir}/MERGE_HEAD" ]]
}

is_exempt_commit_message() {
    local commit_message="$1"

    case "${commit_message}" in
        "fixup! "*|"squash! "*|"Revert "*)
            return 0
            ;;
        *)
            return 1
            ;;
    esac
}

extract_required_prefix() {
    local branch_name="$1"

    if [[ "${branch_name}" =~ ^(ET-[0-9]+)-.+$ ]]; then
        printf '%s\n' "${BASH_REMATCH[1]}"
        return 0
    fi

    return 1
}

validate_commit_message() {
    local commit_message="$1"
    local required_prefix="$2"

    [[ "${commit_message}" =~ ^${required_prefix}:[[:space:]]+.+$ ]]
}

main() {
    local branch_name
    local commit_message
    local required_prefix

    if [[ ! -f "${COMMIT_MSG_FILE}" ]]; then
        echo "Commit message file was not found: ${COMMIT_MSG_FILE}" >&2
        exit 1
    fi

    commit_message="$(get_commit_message)"

    if [[ -z "${commit_message}" ]]; then
        echo "Commit message must not be empty." >&2
        exit 1
    fi

    if is_merge_commit; then
        exit 0
    fi

    if is_exempt_commit_message "${commit_message}"; then
        exit 0
    fi

    branch_name="$(get_branch_name)"

    if [[ "${branch_name}" == "HEAD" ]]; then
        exit 0
    fi

    if is_mainline_branch "${branch_name}"; then
        exit 0
    fi

    if ! required_prefix="$(extract_required_prefix "${branch_name}")"; then
        echo "Invalid branch name format: ${branch_name}" >&2
        echo "Expected format: ET-<number>-<description>" >&2
        exit 1
    fi

    if ! validate_commit_message "${commit_message}" "${required_prefix}"; then
        echo "Invalid commit message: ${commit_message}" >&2
        echo "Expected format: ${required_prefix}: <message>" >&2
        exit 1
    fi

    exit 0
}

main "$@"