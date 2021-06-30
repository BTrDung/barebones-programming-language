clear x; 

incr x; 
incr x; 
incr x; 
incr x; 
incr x; 

clear y;
clear dem; 

incr dem;
incr dem;
incr dem;
incr dem;
incr dem;
incr dem;
incr dem;
incr dem;
incr dem;

incr y; 

while dem not 0 do;
    decr dem; 

    clear newX; 
    clear flag; 
    clear tmp; 
    
    while x not 0 do; 
        incr tmp; 
        incr newX; 
        decr x; 
    end; 

    while tmp not 0 do; 
        incr x; 
        decr tmp;
    end; 
 
    while y not 0 do; 
        decr y;
        incr flag; 
        while newX not 0 do; 
            incr x; 
            incr tmp;
            decr newX; 
        end; 

        while tmp not 0 do; 
            decr tmp; 
            incr newX; 
        end;
        
    end;    

    while flag not 0 do; 
        decr flag; 
        incr y; 
    end; 

    while newX not 0 do; 
        decr newX; 
    end;
    
    print dem;
    incr y;
end; 

print x; 
