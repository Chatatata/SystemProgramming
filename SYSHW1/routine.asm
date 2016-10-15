    segment     .data
    global      generate_r

generate_r:

      push  ebp
      mov   ebp,esp

      mov   ebx,[ebp+8]
      mov   ecx,[ebp+12]
      mov   edx,[ebp+20]
