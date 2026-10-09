        .text   # program start at 0
# -------------------------------------------------------------
# Comprehensive self-test for the 32-bit multicycle CPU
# After each ALU/branch/jump operation the result (or an
# observable side-effect like $ra) is written to MEM[i]
# where i = 0..31 using `sw  rx, i*4($zero)`.
# All addresses therefore stay in the 0-31 word window.
# -------------------------------------------------------------
# ----------  Basic arithmetic / logic  -----------------------
        addi  $t0,$zero,5       # 0: 5
        sw    $t0,0($zero)

        addiu $t1,$zero,10      # 1: 10
        sw    $t1,4($zero)

        add   $t2,$t0,$t1       # 2: 15
        sw    $t2,8($zero)

        addu  $t3,$t1,$t0       # 3: 15 (unsigned add)
        sw    $t3,12($zero)

        sub   $t4,$t1,$t0       # 4: 5
        sw    $t4,16($zero)

        subu  $t5,$t1,$t0       # 5: 5 (unsigned sub)
        sw    $t5,20($zero)

        slt   $t6,$t0,$t1       # 6: 1 (signed <)
        sw    $t6,24($zero)

        sltu  $t7,$t1,$t0       # 7: 0 (unsigned <)
        sw    $t7,28($zero)

        and   $s0,$t1,$t2       # 8: 0x0A
        sw    $s0,32($zero)

        andi  $s1,$t2,0x0F      # 9: 15
        sw    $s1,36($zero)

        or    $s2,$t1,$t2       # 10: 0x0F
        sw    $s2,40($zero)

        ori   $s3,$t0,0xF0      # 11: 0xF5
        sw    $s3,44($zero)

        xor   $s4,$t1,$t0       # 12: 0x0F
        sw    $s4,48($zero)

        xori  $s5,$t2,0xFF      # 13: 0xF0
        sw    $s5,52($zero)

        nor   $s6,$t0,$t1       # 14: 0xFFFFFFF0
        sw    $s6,56($zero)

        lui   $s7,0x1234        # 15: 0x12340000
        sw    $s7,60($zero)

# ----------  Shift group  ------------------------------------
        sll   $t8,$t0,2         # 16: 20
        sw    $t8,64($zero)

        srl   $t9,$t8,1         # 17: 10
        sw    $t9,68($zero)

        sra   $k0,$t8,2         # 18: 5
        sw    $k0,72($zero)

        sllv  $k1,$t0,$t1       # 19: 5 << 10 = 5120
        sw    $k1,76($zero)

        srlv  $k2,$t8,$t0       # 20: 20 >> 5 = 0
        sw    $k2,80($zero)

        srav  $k3,$t8,$t0       # 21: 20 >>> 5 = 0 (arith)
        sw    $k3,84($zero)

# ----------  Branch / jump tests  ----------------------------
        beq   $t0,$t0,beq_taken # always taken
        sw    $zero,88($zero)   # skipped when branch works
beq_taken:
        bne   $t0,$t1,bne_taken # always taken (5!=10)
        sw    $zero,92($zero)   # skipped when branch works
bne_taken:

        jal   save_ra           # $ra <- PC+4
        nop
save_ra:
        sw    $ra,96($zero)     # 24: store return addr for JAL
        j     end_prog
        nop

end_prog:
        j end_prog             # halt: spin forever
        nop