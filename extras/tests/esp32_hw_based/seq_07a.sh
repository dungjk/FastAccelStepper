#!/bin/sh
TTY=${1:-ttyUSB0}
DEV="-d /dev/${TTY} -b 115200"
MOTOR=${MOTOR:-M1}

CMD="$MOTOR p7,-32767,32767 V40 A1000 R54 W R-54 W"
PASS=">> $MOTOR: @0 \\[0\\]"

LOG="$0.log"

grabserial $DEV -c ' x reset ' -q "$MOTOR:" -e 10
sleep 2

grabserial $DEV -c "$CMD" -q "$PASS" -e 3 -o $LOG
echo

#if [ `gawk -f judge_pcnt_sync.awk $LOG | grep -c PASS` -ne 1 ]
#then
#	grabserial $DEV -c 'r ' -q StepperDemo -e 1
#	echo
#	echo FAIL $0 pulse counter mismatch
#	exit 1
#fi

if [ `grep -c "$PASS" $LOG` -eq 1 ]
then
	echo PASS
else
	grabserial $DEV -c ' r ' -q StepperDemo -e 1
	echo
	echo "FAIL $0 result pattern: $PASS"
	exit 1
fi

