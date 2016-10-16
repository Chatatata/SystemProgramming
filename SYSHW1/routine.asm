        


        ; Assembly to generating 1D cellular automata
        ;
        ; STACK PARAMETERS                                          MUTATED?
        ; ebp+8         : Input array (int32_t[BUFSIZ])                   NO    
        ; ebp+16        : Length of the input array (int32_t)             NO
        ; ebp+24        : 8-bit rule array (int32_t[8])                   NO
        ; ebp+32        : Empty array (int32_t[BUFSIZ])                  YES


        segment     .data
        global      generate_r

generate_r:
        push  ebp                ; Save the old base pointer value
        mov   ebp, esp           ; Load stack pointer to base pointer

                                 ; Binary array               : ebp+8
                                 ; Length of the binary array : ebp+16
                                 ; Rule array                 : ebp+24
                                 ; Draw array                 : ebp+32

        xor   eax, eax           ; Initialize the EAX with 0
        push  eax                ; Push it to the stack

check_completed:
        pop   ecx                ; Fetch the n
        mov   eax, [ebp+0xc]     ; Fetch the binary array length
        cmp   ecx, eax           ; Compare n with the length
        je    bailout            ; Bailout if equal

get_field:
        mov   ebx, [ebp+0x8]     ; Fetch the pointer of binary array
        mov   eax, ecx           ; Move it to the accumulator
        mov   edx, 0x4           ; Write 4 to the EDX
        mul   edx                ; Multiply it by 4
        add   ebx, eax           ; Add it to the EBX as offset
        xor   eax, eax           ; Initialize EAX to 0
        push  ecx                ; Push n to the stack again
        push  eax                ; Push the initial sum value to the stack

check_if_first:
        pop   eax                ; Fetch the summed impact
        pop   ecx                ; Fetch the iterator, n
        push  ecx                ; Push the iterator to the stack
        push  eax                ; Push the total impact to the stack
        cmp   ecx, 0x0           ; Check if it's 0
        je    add_upper_element  ; Branch to the upper element

add_before_element:
        mov   eax, [ebx-0x4]     ; Fetch the n-1th element of the binary array
        mov   edx, 0x4           ; Write 4 to the EDX        
        mul   edx                ; Multiply it by 4
        pop   edx                ; Fetch the summed impact
        add   eax, edx           ; Sum impacts
        push  eax                ; Push the total impact to the stack
        
add_upper_element:
        mov   eax, [ebx]         ; Fetch the nth element of the binary arr
        mov   edx, 0x2           ; Write 2 to the EDX
        mul   edx                ; Multiply it by 2
        pop   edx                ; Fetch the impact of left neighbor from stack
        add   eax, edx           ; Sum impacts
        push  eax                ; Push the total impact to the stack

check_if_last:
        pop   eax                ; Fetch the summed impact
        pop   ecx                ; Fetch the iterator, n
        mov   edx, [ebp+0xc]     ; Fetch the length of the binary array
        dec   edx                ; Decrement it to point the last
        push  ecx                ; Push the iterator to the stack
        push  eax                ; Push the total impact to the stack
        cmp   ecx, edx           ; Check if it's equal to length - 1
        je    compare_rule_arr   ; Branch to the upper element

add_after_element:
        mov   eax, [ebx+0x4]     ; Fetch the n+1th element of the binary arr
        pop   edx                ; Fetch the sum
        add   eax, edx           ; Sum impacts
        push  eax                ; Push the total impact to the stack

compare_rule_arr:
        pop   eax                ; Fetch the sum
        mov   edx, 4             ; Write 4 to DX
        mul   edx                ; Multiply sum by 4
        mov   ebx, [ebp+0x10]    ; Fetch the start address of rule array
        add   ebx, eax           ; Go to the nth rule
        mov   eax, [ebx]         ; Fetch the rule
        cmp   eax, 0             ; Check if rule is zero
        je    not_fill           ; Do not fill if zero
        jmp   fill               ; Fill if not zero

fill:
        mov   ebx, [ebp+0x14]   ; Fetch the start address of draw array
        pop   ecx               ; Pop n from the stack
        mov   eax, ecx          ; Transfer counter to accumulator
        mov   edx, 4            ; Write 8 to the EDX
        mul   edx               ; Multiply it by 8
        add   ebx, eax          ; Add the offset to draw arr pointer
        mov   edx, 1
        mov   [ebx], edx        ; Write TRUE to draw arr element
        push  ecx               ; Push the n to the stack
        jmp   inc_counter       ; Increment the counter

not_fill:
        mov   ebx, [ebp+20]     ; Fetch the start address of draw arr
        pop   ecx               ; Pop n from the stack
        mov   eax, ecx          ; Transfer counter to accumulator
        mov   edx, 4            ; Write 8 to EDX
        mul   edx               ; Multiply it by 8
        add   ebx, eax          ; Add the offset to draw arr pointer
        mov   edx, 0
        mov   [ebx], edx        ; Write FALSE to draw arr element
        push  ecx               ; Push the n to the stack
        jmp   inc_counter	; Increment the counter

inc_counter:
        pop   ecx               ; Pop the n from the stack
        inc   ecx               ; Increment the n
        push  ecx               ; Push it to the stack
        jmp   check_completed   ; Go back to check_fill

bailout:
        xor   eax, eax          ; C ABI expects to see 0 in void return
        pop   ebp               ; Restore base pointer
        ret                     ; Return, jump to return address













