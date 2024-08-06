#define VRAM 0x40000
#define KEYBOARD 0xC0000
#define TABLE 0x10000
#define uint unsigned long  
unsigned long state = 12345678;  



unsigned long xorshift32() {
    // Ensure state is non-zero
    if (state == 0) {
        state = 12345678;
    }
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;

    return state;
}

int main()
{
    unsigned long head_cnt = 0;
    uint *key_ptr = (uint *)(KEYBOARD);

    uint *shifted_ptr;

    unsigned long snake_head =  0x55ffff10;
    unsigned long apple = xorshift32();
    unsigned long len = 2;

    while (1)
    {
            shifted_ptr = (uint*)(VRAM);
            if (head_cnt == 64)
                head_cnt = 0;
            switch (*key_ptr){ 
            case 1:
                snake_head += 0x10000000;
                break;    
            case 2:
                snake_head = ((snake_head - 0x01000000) & 0x0f000000) +  (snake_head & 0xf0ffffff); 
                break;    
            case 4:
                snake_head -= 0x10000000;
                break;    
            case 8:
                snake_head = ((snake_head + 0x01000000) & 0x0f000000) +  (snake_head & 0xf0ffffff); 
                break;    
            }
            shifted_ptr = shifted_ptr + head_cnt;
            uint* sub = (uint*)((((uint)shifted_ptr - (len<<2)) & (0x00000ff)) + VRAM);
            if (*(uint*)(TABLE + (snake_head>>22)) == 1)
            {
                for (uint i = 0; i < 16; i++)
                {
                    *(((uint*)VRAM)+i) = 0x00ff0000 + (i<<24);
                    *(((uint*)VRAM)+i + 16) = 0xf0ff0000 + (i<<24);
                    *(((uint*)VRAM)+i + 32) = 0x00ff0000 + (i<<28);
                    *(((uint*)VRAM)+i + 48) = 0x0fff0000 + (i<<28);
                }
                *shifted_ptr = 0xffffffff;
                while (1)
                    __asm__ ("nop \n\t");
            }
            *(uint*)(TABLE + (*sub>>22)) = 0;
            *(uint*)(TABLE + (snake_head>>22)) = 1;
            *sub = 0;
            *shifted_ptr = snake_head;   
            head_cnt++;

            shifted_ptr = (uint*)(VRAM) + 66;

            *shifted_ptr = apple;

            if (~(snake_head ^ apple) >> 24 == 0xff)
            {
                len++;
                apple = xorshift32();
            }   
               

            *shifted_ptr = 0xffffffff;
            while (*(key_ptr + 1) == 1)
                __asm__ ("nop \n\t");
    }

}
