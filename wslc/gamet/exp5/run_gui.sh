#!/bin/bash
# Run the Dynamic Prisoner's Dilemma GUI
# Uses software rendering to avoid WSL display issues

cd /home/kkkzbh/code/gamet/exp5
source ../.venv/bin/activate

# Locate PySide6 path dynamically involved python
PYSIDE_DIR=$(python -c "import os, PySide6; print(os.path.dirname(PySide6.__file__))")
echo "Found PySide6 at: $PYSIDE_DIR"

# Use software rendering for WSL compatibility
export QT_QPA_PLATFORM=xcb
export LIBGL_ALWAYS_SOFTWARE=1

# Prepend PySide6 libraries to LD_LIBRARY_PATH to take precedence over system Qt
# PySide6 6.x usually keeps libs in PYSIDE_DIR or PYSIDE_DIR/Qt/lib depending on packaging
# We include both for safety.
export LD_LIBRARY_PATH="$PYSIDE_DIR/Qt/lib:$PYSIDE_DIR:$LD_LIBRARY_PATH"

# Set Plugin Path explicitely
export QT_PLUGIN_PATH="$PYSIDE_DIR/Qt/plugins"

echo "Starting GUI..."
python main_gui_.py
