    segment     .data
    global      generate_r

generate_r:

      push  ebp               ; Save the old base pointer value
      mov   ebp,esp           ; Load stack pointer to base pointer

      mov   ecx,[ebp+8]       ; Load first argument to 32-bit AP register
      mov   edx,[ebp+16]      ; Load second argument to 32-bit AP register
      xor   eax,eax           ; Clear EAX

      mov   eax,edx

      pop   ebp               ; Restore base pointer
      ret                     ; Bailout, jump to return address
