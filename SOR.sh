#!/bin/bash
INPUT="$1"
OUTPUT="$2"

CONVERGES=0
BAD_OMEGA=1
BAD_DIAGONAL=2
SNPD=3
NON_SPD=4

# Check for correct invocation

if [[ ! -f "$INPUT" ]] || [[ ! -f "$OUTPUT" ]]; then
	echo "usage: ./SOR.sh input_file output_file"
	exit
fi

# Build C++ dependencies
make -s check || exit
make -s SOR || exit

# Run pre eigenvalues check
./build/check "$INPUT" "$OUTPUT"
CPP_CHECK=$?
case "$CPP_CHECK" in
"$CONVERGES")
	python3 ./src/inverse.py "$INPUT"
	./build/SOR "$INPUT" "$OUTPUT"
	exit
	;;
"$BAD_OMEGA" | "$BAD_DIAGONAL" | "$SNPD")
	exit
	;;
esac

# Run eigenvalues check
python3 ./src/check.py "$INPUT" "$OUTPUT"
EIGENVALUES_CHECK=$?
if [[ $EIGENVALUES_CHECK -eq 0 ]]; then
	python3 ./src/inverse.py "$INPUT"
	./build/SOR "$INPUT" "$OUTPUT"
	exit
fi
