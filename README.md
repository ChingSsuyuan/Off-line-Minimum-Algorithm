# Off-line-minimum-Algorithm
Off-Line-Minimum(m, n) 

    for i = 1 to n determine j such that i is in K_j 
    
        if j not equal to m + 1 
        
            extracted[j] = i 
            
        let l be the smallest value greater than j for which set K_l exists 
        
        K_l = union( K_j, K_l), destroying K_j return extracted
