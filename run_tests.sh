#!/usr/bin/env bash

make clean
make all

cd build || { echo "Build-Verzeichnis nicht gefunden"; exit 1; }
pwd

TEST_DIR="../test-directory"

if [ ! -d "$TEST_DIR" ]; then
    echo "Testverzeichnis '$TEST_DIR' nicht gefunden."
    exit 1
fi

echo "Starte Tests auf Verzeichnis: $TEST_DIR"

function run_test {
    echo -e "\n# Test: $1"
    eval "$2" > output.txt 2> error.txt
    if [ $? -ne 0 ]; then
        echo "FEHLER: Der Test ist fehlgeschlagen!"
        echo "Kommando: $2"
        echo "Fehlerausgabe:"
        cat error.txt
        exit 1
    fi
    echo "Test erfolgreich!"
    cat output.txt
}

run_test "Normales grep (einzelne Datei)" \
    "./grep 'specialword' $TEST_DIR/subdir_0/file_1.txt"

run_test "Normales grep mit Zeilennummern (einzelne Datei)" \
    "./grep -n 'specialword' $TEST_DIR/subdir_0/file_1.txt"

run_test "Rekursives grep" \
    "./grep -r 'specialword' $TEST_DIR"

run_test "Normales grep mit Count" \
    "./grep -c 'specialword' $TEST_DIR/subdir_0/file_1.txt"

run_test "Rekursives grep (case-insensitive)" \
    "./grep -r -i 'specialword' $TEST_DIR"

run_test "Rekursives grep (inverted match)" \
    "./grep -r -v 'specialword' $TEST_DIR"

run_test "Rekursives grep (inverted + case-insensitive)" \
    "./grep -r -v -i 'specialword' $TEST_DIR"

run_test "Rekursives grep mit Zeilennummern" \
    "./grep -r -n 'specialword' $TEST_DIR"

run_test "Rekursives grep (inverted + case-insensitive + Zeilennummern)" \
    "./grep -r -v -i -n 'specialword' $TEST_DIR"

run_test "Rekursives grep mit Count" \
    "./grep -r -c 'specialword' $TEST_DIR"

run_test "Rekursives grep (Count + case-insensitive)" \
    "./grep -r -i -c 'specialword' $TEST_DIR"

run_test "Rekursives grep (Count + inverted match)" \
    "./grep -r -v -c 'specialword' $TEST_DIR"

run_test "Grep auf leere Datei" \
    "./grep 'specialword' $TEST_DIR/subdir_0/empty_file.txt"

run_test "Grep auf Binärdatei (soll keine Fehler werfen)" \
    "./grep 'specialword' $TEST_DIR/subdir_0/binary_file.bin"

echo -e "\nAlle Tests erfolgreich abgeschlossen!"
