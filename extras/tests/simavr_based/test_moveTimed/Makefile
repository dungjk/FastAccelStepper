#
# In order to execute the test for one directory use:
#
# 	make -C test_sd_01b_328p -f ../Makefile.test

SRC=$(wildcard ../../../src/*) $(wildcard src/*)

# platformio should contain only one env section.
# This section states the dut name
#		atmega168
#		atmega168p
#		atmega328
#		atmega328p
#		atmega2560_timer1
#		atmega2560_timer3
#		atmega2560_timer4
#		atmega2560_timer5
#

DUT=$(shell gawk '/env:/{print(substr($$1,6,length($$1)-6))}' platformio.ini)

TRACES=-at StepISR=trace@0x25/0x08     # PB3
TRACES+=-at FillISR=trace@0x25/0x10     # PB4

#
ifeq ($(DUT),atmega2560_timer1)
DEVICE=atmega2560
TRACES+=-at StepA=trace@0x025/0x20 #OC1A PB5 11 ATMega2560
TRACES+=-at StepB=trace@0x025/0x40 #OC1B PB6 12 ATMega2560
TRACES+=-at StepC=trace@0x025/0x80 #OC1C PB7 13 ATMega2560
#
else ifeq ($(DUT),atmega2560_timer3)
DEVICE=atmega2560
TRACES+=-at StepA=trace@0x02e/0x08 #OC3A PE3 5 ATMega2560
TRACES+=-at StepB=trace@0x02e/0x10 #OC3B PE4 2 ATMega2560
TRACES+=-at StepC=trace@0x02e/0x20 #OC3C PE5 3 ATMega2560
#
else ifeq ($(DUT),atmega2560_timer4)
DEVICE=atmega2560
TRACES+=-at StepA=trace@0x102/0x08 #OC4A PH3 6 ATMega2560
TRACES+=-at StepB=trace@0x102/0x10 #OC4B PH4 7 ATMega2560
TRACES+=-at StepC=trace@0x102/0x20 #OC4C PH5 8 ATMega2560
#
else ifeq ($(DUT),atmega2560_timer5)
DEVICE=atmega2560
TRACES+=-at StepA=trace@0x10b/0x08 #OC5A PL3 46 ATMega2560
TRACES+=-at StepB=trace@0x10b/0x10 #OC5B PL4 45 ATMega2560
TRACES+=-at StepC=trace@0x10b/0x20 #OC5C PL5 44 ATMega2560

else ifeq ($(DUT),atmega168)
DEVICE=atmega168
TRACES+=-at StepA=trace@0x25/0x02  #OC1A PB1 9  atmega168
TRACES+=-at StepB=trace@0x25/0x04  #OC1B PB2 10 atmega168

else ifeq ($(DUT),atmega168p)
DEVICE=atmega168p
TRACES+=-at StepA=trace@0x25/0x02  #OC1A PB1 9  atmega168p
TRACES+=-at StepB=trace@0x25/0x04  #OC1B PB2 10 atmega168p

else ifeq ($(DUT),atmega328)
DEVICE=atmega328
TRACES+=-at StepA=trace@0x25/0x02  #OC1A PB1 9  ATMega328
TRACES+=-at StepB=trace@0x25/0x04  #OC1B PB2 10 ATMega328

else ifeq ($(DUT),atmega328p)
DEVICE=atmega328p
TRACES+=-at StepA=trace@0x25/0x02  #OC1A PB1 9  ATMega328p
TRACES+=-at StepB=trace@0x25/0x04  #OC1B PB2 10 ATMega328p

else ifeq ($(DUT),atmega32u4)
DEVICE=atmega32u4
TRACES+=-at StepA=trace@0x025/0x20 #OC1A PB5 11
TRACES+=-at StepB=trace@0x025/0x40 #OC1B PB6 12
#TRACES+=-at StepC=trace@0x025/0x80 #OC1C PB7 13

endif

ifeq ($(DEVICE),atmega2560)
TRACES+=-at DirA=trace@0x2b/0x01     # Pin 21 PD0
TRACES+=-at DirB=trace@0x2b/0x02     # Pin 20 PD1
TRACES+=-at DirC=trace@0x10b/0x80    # Pin 42 PL7
TRACES+=-at EnableA=trace@0x2b/0x04  # Pin 19 PD2
TRACES+=-at EnableB=trace@0x2b/0x08  # Pin 18 PD3
TRACES+=-at EnableC=trace@0x10b/0x40 # Pin 43 PL6

else ifeq ($(DEVICE),$(filter $(DEVICE),atmega168 atmega168p atmega328 atmega328p))
TRACES+=-at DirA=trace@0x2b/0x20     # Pin 5  PD5
TRACES+=-at DirB=trace@0x2b/0x80     # Pin 7  PD7
TRACES+=-at EnableA=trace@0x2b/0x40  # Pin 6  PD6
TRACES+=-at EnableB=trace@0x25/0x01  # Pin 8  PB0

else ifeq ($(DUT),atmega32u4)
TRACES+=-at DirA=trace@0x25/0x10     # Pin 26 PB4
TRACES+=-at DirB=trace@0x25/0x08     # Pin 14 PB3
#TRACES+=-at DirC=trace@0x10b/0x80    # Pin 42 PL7
TRACES+=-at EnableA=trace@0x25/0x04  # Pin 16 PB2
TRACES+=-at EnableB=trace@0x25/0x02  # Pin 15 PB1
#TRACES+=-at EnableC=trace@0x10b/0x40 # Pin 43 PL6

endif 

FIRMWARE=".pio/build/$(DUT)/firmware.elf"

DIR=$(shell env pwd)

test: .tested

.tested: result.txt ../judge_pos0.awk
	echo DUT=$(DUT)
	rm -f .tested
	gawk -f ../judge_pos0.awk -v DIR=$(DIR) result.txt
	test -f .tested

result.txt: x.vcd
	gawk -f ../eval.awk x.vcd >x.log
	mv result.txt result.tmp
	gawk -f log2pos.awk x.log
	mv result.tmp result.txt

x.vcd: $(SRC) ../run_avr platformio.ini src/MoveTimed.ino
	~/.platformio/penv/bin/pio run -e $(DUT) || ~/.local/bin/pio run -e $(DUT) || env pio run -e $(DUT)
	../run_avr $(FIRMWARE) -m $(DEVICE) -o x.vcd $(TRACES)

src/MoveTimed.ino:
	mkdir -p src
	cd src; ln -s ../../../../../examples/MoveTimed/MoveTimed.ino .

clean:
	rm -fR .pio .tested x.vcd result.txt

