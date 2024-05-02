global example1
example1:
    push ebp
    mov ebp, esp
    finit
    fld1
    fld qword[esp+8]
    fdivp
    leave
    ret
    
global example2
example2:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp+8]
    fld qword[esp+8]
    fmulp
    leave 
    ret

global f1
f1: ;f1(double x) = ln(x);
    push ebp
    mov ebp, esp
    finit
    fld1
    fld qword[esp+8];!
    fyl2x
    fldl2e
    fdivp
    leave
    ret
    
global f2
f2: ;f2(double x) = -2 * x + 14;
    push ebp
    mov ebp, esp
    finit
    fld qword[esp+8]
    fld1
    fld1
    faddp
    fchs ; a = -a
    fmulp
    fld1
    fld1 ; 2
    faddp
    fld1
    fld1
    fld1
    fld1
    faddp
    faddp    
    faddp ;4
    fld1
    fld1
    fld1
    faddp
    faddp
    faddp ;7
    fmulp
    faddp 
    leave 
    ret

global f3
f3: ;1/(2-x) + 6
    push ebp
    mov ebp, esp
    finit 
    fld1
    fld qword[esp+8]
    fchs
    fld1
    fld1
    faddp
    faddp
    fdivp
    fld1
    fld1
    fld1
    faddp
    faddp
    fld1
    fld1
    faddp
    fmulp
    faddp
    leave
    ret
    
global second_der_f1 
second_der_f1:
    push ebp
    mov ebp, esp
    finit
    fld1
    fchs
    fld qword[esp+8]
    fdivp
    fld qword[esp+8]
    fdivp
    leave
    ret

global second_der_f2
second_der_f2:
    push ebp
    mov ebp, esp
    finit
    fldz
    leave 
    ret
    
global second_der_f3
second_der_f3:
    push ebp
    mov ebp, esp
    finit
    fld1
    fld1
    faddp
    
    fld1
    fld1
    faddp
    fld qword[esp+8]
    fchs
    faddp
    
    fld1
    fld1
    faddp
    fld qword[esp+8]
    fchs
    faddp
    
    fmulp
    
    fld1
    fld1
    faddp
    fld qword[esp+8]
    fchs
    faddp
    
    fmulp
    fdivp
    leave
    ret
    
global second_der_example1
second_der_example1:
    push ebp
    mov ebp, esp
    finit
    fld1
    fld1
    faddp
    fld qword[esp+8]
    fld qword[esp+8]
    fmulp
    fld qword[esp++8]
    fmulp
    fdivp
    leave
    ret
    
    

; check!