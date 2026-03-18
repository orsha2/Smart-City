#!/usr/bin/env bash

set -euo pipefail

PYTHON_BIN="${PYTHON_BIN:-python3.14}"
VENV_DIR="${VENV_DIR:-.venv}"
C_GUARD_TIDY_WHEEL_PATH="${C_GUARD_TIDY_WHEEL_PATH:-.deps/c_guard_tidy-0.2.0-cp314-cp314-linux_x86_64.whl}"

echo "Checking Python interpreter: ${PYTHON_BIN}"
if ! command -v "${PYTHON_BIN}" >/dev/null 2>&1; then
    echo "Error: ${PYTHON_BIN} was not found in PATH."
    exit 1
fi

echo "Checking wheel file: ${C_GUARD_TIDY_WHEEL_PATH}"
if [ ! -f "${C_GUARD_TIDY_WHEEL_PATH}" ]; then
    echo "Error: wheel file not found at ${C_GUARD_TIDY_WHEEL_PATH}"
    exit 1
fi

echo "Creating virtual environment at ${VENV_DIR}"
"${PYTHON_BIN}" -m venv "${VENV_DIR}"

echo "Activating virtual environment"
source "${VENV_DIR}/bin/activate"

echo "Upgrading pip"
python -m pip install --upgrade pip

echo "Installing dependency from ${C_GUARD_TIDY_WHEEL_PATH}"
python -m pip install "${C_GUARD_TIDY_WHEEL_PATH}"

echo
echo "Done."
echo "Virtual environment: ${VENV_DIR}"
echo "Python version inside venv:"
python --version