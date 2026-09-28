# COMPX203 Exercise 5, Question 3
# kernel_q3.s
# Initialises the timer to generate 100 interrupts per second
# Jumps and links to the entry point of the serial task

.equ tmrctrl, 0x72000              # Timer Control Register
.equ tmrload, 0x72001              # Timer Load Register
.equ tmrackn, 0x72003              # Timer Acknowledge Register

.text
.global main
main:
    # Setup 'Exception Vector Register'
    movsg $2, $evec             # Get old handler address
    sw    $2, oldvector($0)     # Save back up address
    la    $2, handler           # Load this handler address
    movgs $evec, $2             # Save as current address
   
    # Setup 'CPU Control Register'
    movsg $2, $cctrl            # Get current control value
    andi  $2, $2, 0x000f        # Reset the mask setting
    ori   $2, $2, 0x42          # Enable IRQ2 and IE
    movgs $cctrl, $2            # Save new control settings

    # Set up 'Timer Control Register'
    lw    $2, tmrctrl($0)
    addi  $2, $0, 3             # Enable auto restart
    sw    $2, tmrctrl($0)       # Set timer to GO

    # Setup 'Timer Load Register'
    lw    $2, tmrload($0)
    addi  $2, $0, 240           # 2400hz * 0.1s = 240
    sw    $2, tmrload($0)       # Save autorestart at 0.1s

    jal serial_main

# Global handler checks 'Exception Status Register' for cause
.global handler
handler:
    # Check if interrupt cause is 'Timer Interrupt'
    movsg $13, $estat           # Get current status value 
    andi  $13, $13, 0xffb0      # Mask for IRQ2 interrupt
    beqz  $13, handle_irq2      # Branch to handle time

    # If not then restore the 'Exception Vector Register'
    lw    $13, oldvector($0)    # Load the old address
    jr $13                      # Jump to default handler 

# Timer interrupt handle
handle_irq2:
    sw    $0, tmrackn($0)       # Acknowledge the interrupt
    addi  $13, $13, 1
    sw    $13, counter($0)      # Increment the counter by 1
    rfe                         # Return from exception

.data
    oldvector:
          .word 0