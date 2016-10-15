    segment     .data
    global      _generate_r

_generate_r:

      push  ebp
      mov   ebp,esp

      mov   ebx,[ebp+8]
      mov   ecx,[ebp+12]
      mov   edx,[ebp+20]
