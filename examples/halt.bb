clear x; 
clear y; 
clear x12y21;
incr x; 

print x; 
while x not 0 do; 
    clear z; 
    incr z; 
    incr z;
    while z not 0 do;
        incr y; 
        incr y; 
        decr z; 
    end; 
    decr x; 
end; 
