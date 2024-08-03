int main()
{
    int *vram_ptr = 0;
    unsigned long addr = (unsigned long)vram_ptr;
    // Bit shift the address
    unsigned long shifted_addr = (addr + 1) << 18; // Right shift by 1 bit
    // Cast the shifted address back to a pointer
    volatile int *shifted_ptr = (int *)shifted_addr;
    *shifted_ptr = 0x05ffff10;

    volatile int t =  0x05ffff10;
    shifted_ptr += 1;
    for (;;)
    {
        shifted_ptr -= 1;
        *shifted_ptr = t;
        t += 0x01ffffff;
        shifted_ptr += 1;
        *shifted_ptr = ~0;
    }



}