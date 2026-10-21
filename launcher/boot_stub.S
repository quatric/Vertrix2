# Copies a DOL's sections to their addresses and jumps to its entry point. app.c copies this code
# to 0x81700000 and calls it with interrupts off, after SYS_ResetSystem(SYS_SHUTDOWN):
#   r3 = the DOL in memory, r4 = the argument block (magic, command line, length) or 0.
# It is position independent and uses no stack. When the entry point is followed by the argv
# magic, as libogc's and dolxz's crt0 are ("b start; .long 0x5f617267; 3 words"), the block is
# stored after it, as the Homebrew Channel does. The program starts on a fresh stack just below
# the stub: dolxz's crt0 keeps the stack it is given, and the caller's lay in the BSS that crt0
# clears.

    .section .rodata.vertrix_boot_stub, "a"
    .balign 32
    .globl vertrix_boot_stub, vertrix_boot_stub_end
vertrix_boot_stub:
    mr      31, 3                   # the DOL
    mr      30, 4                   # the argument block
    li      29, 0                   # section 0..17
1:  slwi    5, 29, 2
    lwzx    6, 31, 5                # file offset
    addi    7, 5, 0x48
    lwzx    7, 31, 7                # address
    addi    8, 5, 0x90
    lwzx    8, 31, 8                # size
    cmpwi   8, 0
    beq     4f
    add     6, 6, 31
    mr      9, 7
    mtctr   8
2:  lbz     10, 0(6)
    stb     10, 0(9)
    addi    6, 6, 1
    addi    9, 9, 1
    bdnz    2b
    rlwinm  9, 7, 0, 0, 26          # write the section back and drop stale instructions
    add     10, 7, 8
3:  dcbst   0, 9
    sync
    icbi    0, 9
    addi    9, 9, 32
    cmplw   9, 10
    blt     3b
4:  addi    29, 29, 1
    cmpwi   29, 18
    blt     1b
    sync
    isync
    lwz     11, 0xe0(31)            # entry point
    cmpwi   30, 0
    beq     5f
    lwz     9, 4(11)
    lis     10, 0x5f61
    ori     10, 10, 0x7267
    cmpw    9, 10
    bne     5f
    lwz     9, 0(30)
    stw     9, 8(11)
    lwz     9, 4(30)
    stw     9, 12(11)
    lwz     9, 8(30)
    stw     9, 16(11)
    addi    9, 11, 8
    dcbst   0, 9
    addi    9, 11, 16
    dcbst   0, 9
    sync
    addi    9, 11, 8
    icbi    0, 9
    addi    9, 11, 16
    icbi    0, 9
    sync
    isync
5:  lis     1, 0x816f
    ori     1, 1, 0xfff0
    li      0, 0
    stw     0, 0(1)
    mtlr    11
    blr
vertrix_boot_stub_end:

# A system call handler that needs nothing else in memory, for 0x80000c00. dolxz's crt0 flushes
# the data cache with "sc" before it installs its own handler; the launcher's libogc handler
# jumps into code the stub has just overwritten. This one, as libogc's classic one, sets and
# clears HID0's ABE bit to drain the bus, then returns.
    .globl vertrix_sc_handler, vertrix_sc_handler_end
vertrix_sc_handler:
    mtspr   274, 9                  # SPRG2
    mtspr   275, 10                 # SPRG3
    mfspr   9, 1008                 # HID0
    ori     10, 9, 0x0008
    mtspr   1008, 10
    isync
    sync
    mtspr   1008, 9
    mfspr   9, 274
    mfspr   10, 275
    rfi
vertrix_sc_handler_end:
