
all:



JLinkGDBServer:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	remove -f *.o *.out *.h


.PHONY: JLinkGDBServer clean
