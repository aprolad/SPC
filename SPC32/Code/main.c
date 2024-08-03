
int main()
{

    unsigned long shifted_addr = 1 << 18;
    unsigned long key_addr = (1 << 19) + shifted_addr;
    volatile int *key_ptr = (int *)key_addr;
    volatile int *shifted_ptr = (int *)shifted_addr;
    *shifted_ptr = 0x05ffff10;
    volatile int t =  0x05ffff10;
    shifted_ptr += 1;
    while (1)
    {
            shifted_ptr -= 1;
            *shifted_ptr = t;
            switch (*key_ptr){ 
            case 1:
                t += 0x10000000;
                break;    
            case 2:
                t = ((t - 0x01000000) & 0x0f000000) +  (t & 0xf0ffffff); 
                break;    
            case 4:
                t -= 0x10000000;
                break;    
            case 8:
                t = ((t + 0x01000000) & 0x0f000000) +  (t & 0xf0ffffff); 
                break;    
            }                     
            shifted_ptr += 1;
            *shifted_ptr = ~0;
    }

}
