#ifndef _dot_microkernel_arm_cortex_m_H_
#define _dot_microkernel_arm_cortex_m_H_

/*
    optimized for int16 quantization
*/

/*
    - simd optimzed
    - load 8 things, compute 8 things
    - utilization 8/(8+8) = 0.5  [50%]

 800047c:	f853 4c2c 	ldr.w	r4, [r3, #-44]  //loading, vaste time
 8000480:	f851 ec2c 	ldr.w	lr, [r1, #-44]
 8000484:	f853 5c28 	ldr.w	r5, [r3, #-40]
 8000488:	f851 8c28 	ldr.w	r8, [r1, #-40]
 800048c:	f853 0c24 	ldr.w	r0, [r3, #-36]
 8000490:	f851 9c24 	ldr.w	r9, [r1, #-36]
 8000494:	f853 6c20 	ldr.w	r6, [r3, #-32]
 8000498:	f851 7c20 	ldr.w	r7, [r1, #-32]

 800049c:	fb12 bb0c 	smlabb	fp, r2, ip, fp  //computing
 80004a0:	fb1e bb34 	smlatt	fp, lr, r4, fp
 80004a4:	fb14 bb0e 	smlabb	fp, r4, lr, fp
 80004a8:	fb18 bb35 	smlatt	fp, r8, r5, fp
 80004ac:	fb15 bb08 	smlabb	fp, r5, r8, fp
 80004b0:	fb19 bb30 	smlatt	fp, r9, r0, fp
 80004b4:	fb10 b009 	smlabb	r0, r0, r9, fp
*/



/*
    - naive code
    - load 8 things, compute 4 things
    - utilization 4/(8+4) = 33%, in practice is much less due to huge memory access


 8000524:	f8b1 a032 	ldrh.w	sl, [r1, #50]	; 0x32  //loading, vaste time
 8000528:	f8b3 e032 	ldrh.w	lr, [r3, #50]	; 0x32
 800052c:	f8b3 c034 	ldrh.w	ip, [r3, #52]	; 0x34
 8000530:	f8b1 9034 	ldrh.w	r9, [r1, #52]	; 0x34

 8000534:	8ede      	ldrh	r6, [r3, #54]	; 0x36
 8000536:	8eca      	ldrh	r2, [r1, #54]	; 0x36
 8000538:	8f1d      	ldrh	r5, [r3, #56]	; 0x38
 800053a:	f8b1 8038 	ldrh.w	r8, [r1, #56]	; 0x38

 800053e:	fb10 440b 	smlabb	r4, r0, fp, r4          //computing
 8000542:	fb1e 440a 	smlabb	r4, lr, sl, r4
 8000546:	fb1c 4409 	smlabb	r4, ip, r9, r4
 800054a:	fb16 4602 	smlabb	r6, r6, r2, r4
 */


inline int32_t _smlad16(int32_t x, int32_t y, int32_t sum)
{
    return (sum + ((int16_t) (x >> 16) * (int16_t) (y >> 16)) + ((int16_t) x * (int16_t) y));
}

template<const unsigned int vector_size, class DATA_VA_t, class DATA_VB_t, class ACC_t>
ACC_t dot_microkernel(const DATA_VA_t *va, const DATA_VB_t *vb)
{    
    ACC_t result = 0;

    unsigned int size = vector_size;

    while (size >= 32) 
    {                 
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;

        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;

        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;

        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        
        size-= 32;
    }

    while (size >= 16) 
    {                 
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;

        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;
        result = _smlad16(*(int32_t*)va, *(int32_t*)vb, result); va+= 2; vb+= 2;

        size-= 16;
    }

    while (size > 0)
    {
        result+= (int16_t)(*va)*(int16_t)(*vb); va++; vb++;
        size--;
    }

    return result;
}


#endif