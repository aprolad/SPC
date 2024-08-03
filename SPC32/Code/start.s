.globl _start

_start:
	lui sp, 0x8 # 0x8000
	lui gp, 0x9 # 0x9000
	jal ra, main