#!/usr/bin/env bash

set -euo pipefail

readonly COMMIT_MSG_FILE="${1:-}"

if [[ -z "${COMMIT_MSG_FILE}" ]]; then
    echo "Usage: check_commit_msg.sh <commit-msg-file>" >&2
    exit 1
fi

if [[ ! -f "${COMMIT_MSG_FILE}" ]]; then
    echo "Commit message file does not exist: ${COMMIT_MSG_FILE}" >&2
    exit 1
fi

commit_message="$(sed -e '/^#/d' -e '/^[[:space:]]*$/d' "${COMMIT_MSG_FILE}" | head -n 1)"

if [[ -z "${commit_message}" ]]; then
    echo "Commit message is empty." >&2
    exit 1
fi

case "${commit_message}" in
    "Merge "*|"fixup! "*|"squash! "*|"Revert "*)
        exit 0
        ;;
esac

branch_name="$(git rev-parse --abbrev-ref HEAD)"

if [[ "${branch_name}" == "main" || "${branch_name}" == "master" ]]; then
    exit 0
fi

if [[ "${branch_name}" == "HEAD" ]]; then
    echo "Detached HEAD detected. Commit message validation is skipped." >&2
    exit 0
fi

if [[ ! "${branch_name}" =~ ^(ET-[0-9]+)-.+$ ]]; then
    echo "Invalid branch name format." >&2
    echo "Expected development branches to match: ET-<number>-..." >&2
    echo "Actual branch: ${branch_name}" >&2
    exit 1
fi

required_prefix="${BASH_REMATCH[1]}"

if [[ ! "${commit_message}" =~ ^${required_prefix}([[:space:]]|:|$) ]]; then
    echo "Invalid commit message." >&2
    echo "Branch: ${branch_name}" >&2
    echo "Commit message must start with: ${required_prefix}" >&2
    echo "Actual message: ${commit_message}" >&2
    echo >&2
    echo "Example:" >&2
    echo "  ${required_prefix} add observer unit tests" >&2
    exit 1
fi

exit 0