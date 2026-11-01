
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00039a71 <.data+0x29a71>:
   39a71:	8b 08                	mov    ecx,DWORD PTR [eax]
   39a73:	85 c9                	test   ecx,ecx
   39a75:	74 3c                	je     0x39ab3
   39a77:	31 c0                	xor    eax,eax
   39a79:	8b 74 24 20          	mov    esi,DWORD PTR [esp+0x20]
   39a7d:	66 8b 01             	mov    ax,WORD PTR [ecx]
   39a80:	89 cf                	mov    edi,ecx
   39a82:	39 f0                	cmp    eax,esi
   39a84:	75 2d                	jne    0x39ab3
   39a86:	8d 79 03             	lea    edi,[ecx+0x3]
   39a89:	89 ee                	mov    esi,ebp
   39a8b:	89 d9                	mov    ecx,ebx
   39a8d:	31 c0                	xor    eax,eax
   39a8f:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   39a91:	74 05                	je     0x39a98
   39a93:	19 c0                	sbb    eax,eax
   39a95:	83 d8 ff             	sbb    eax,0xffffffff
   39a98:	85 c0                	test   eax,eax
   39a9a:	75 17                	jne    0x39ab3
   39a9c:	a1 ac 02 02 00       	mov    eax,ds:0x202ac
   39aa1:	8b 40 56             	mov    eax,DWORD PTR [eax+0x56]
   39aa4:	31 ff                	xor    edi,edi
   39aa6:	8b 04 02             	mov    eax,DWORD PTR [edx+eax*1]
   39aa9:	89 7c 24 20          	mov    DWORD PTR [esp+0x20],edi
   39aad:	89 44 24 28          	mov    DWORD PTR [esp+0x28],eax
   39ab1:	eb 0b                	jmp    0x39abe
   39ab3:	8b 7c 24 24          	mov    edi,DWORD PTR [esp+0x24]
   39ab7:	83 c2 04             	add    edx,0x4
   39aba:	39 fa                	cmp    edx,edi
   39abc:	7c a9                	jl     0x39a67
   39abe:	8b 44 24 20          	mov    eax,DWORD PTR [esp+0x20]
   39ac2:	85 c0                	test   eax,eax
   39ac4:	74 56                	je     0x39b1c
   39ac6:	8d 34 40             	lea    esi,[eax+eax*2]
   39ac9:	8d 7e 03             	lea    edi,[esi+0x3]
   39acc:	57                   	push   edi
   39acd:	e8 2e c1 ff ff       	call   0x35c00
   39ad2:	83 c4 04             	add    esp,0x4
   39ad5:	89 44 24 28          	mov    DWORD PTR [esp+0x28],eax
   39ad9:	85 c0                	test   eax,eax
   39adb:	75 0f                	jne    0x39aec
   39add:	b8 ff ff ff ff       	mov    eax,0xffffffff
   39ae2:	83 c4 3c             	add    esp,0x3c
   39ae5:	5d                   	pop    ebp
   39ae6:	5f                   	pop    edi
   39ae7:	5e                   	pop    esi
   39ae8:	5a                   	pop    edx
   39ae9:	59                   	pop    ecx
   39aea:	5b                   	pop    ebx
   39aeb:	c3                   	ret    
   39aec:	8b 15 ac 02 02 00    	mov    edx,DWORD PTR ds:0x202ac
   39af2:	8b 5a 01             	mov    ebx,DWORD PTR [edx+0x1]
   39af5:	89 f1                	mov    ecx,esi
   39af7:	01 fb                	add    ebx,edi
   39af9:	89 ee                	mov    esi,ebp
   39afb:	89 5a 01             	mov    DWORD PTR [edx+0x1],ebx
   39afe:	8b 54 24 20          	mov    edx,DWORD PTR [esp+0x20]
   39b02:	c6 40 02 00          	mov    BYTE PTR [eax+0x2],0x0
   39b06:	8d 78 03             	lea    edi,[eax+0x3]
   39b09:	66 89 10             	mov    WORD PTR [eax],dx
   39b0c:	57                   	push   edi
   39b0d:	89 c8                	mov    eax,ecx
   39b0f:	c1 e9 02             	shr    ecx,0x2
   39b12:	f2 a5                	repnz movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
   39b14:	8a c8                	mov    cl,al
   39b16:	80 e1 03             	and    cl,0x3
   39b19:	f2 a4                	repnz movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   39b1b:	5f                   	pop    edi
   39b1c:	8b 14 24             	mov    edx,DWORD PTR [esp]
   39b1f:	8b 4c 24 10          	mov    ecx,DWORD PTR [esp+0x10]
   39b23:	8b 7c 24 08          	mov    edi,DWORD PTR [esp+0x8]
   39b27:	a1 ac 02 02 00       	mov    eax,ds:0x202ac
   39b2c:	41                   	inc    ecx
   39b2d:	8d 72 04             	lea    esi,[edx+0x4]
   39b30:	47                   	inc    edi
   39b31:	8b 40 56             	mov    eax,DWORD PTR [eax+0x56]
   39b34:	89 4c 24 10          	mov    DWORD PTR [esp+0x10],ecx
   39b38:	89 34 24             	mov    DWORD PTR [esp],esi
   39b3b:	01 d0                	add    eax,edx
   39b3d:	8b 54 24 28          	mov    edx,DWORD PTR [esp+0x28]
   39b41:	89 7c 24 08          	mov    DWORD PTR [esp+0x8],edi
   39b45:	89 10                	mov    DWORD PTR [eax],edx
   39b47:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   39b4b:	8b 54 24 18          	mov    edx,DWORD PTR [esp+0x18]
   39b4f:	83 c0 03             	add    eax,0x3
   39b52:	42                   	inc    edx
   39b53:	89 44 24 0c          	mov    DWORD PTR [esp+0xc],eax
   39b57:	89 54 24 18          	mov    DWORD PTR [esp+0x18],edx
   39b5b:	83 fa 08             	cmp    edx,0x8
   39b5e:	0f 8c        	jl     0x397fa

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00036118 <.data+0x26118>:
   36118:	53                   	push   ebx
   36119:	51                   	push   ecx
   3611a:	52                   	push   edx
   3611b:	56                   	push   esi
   3611c:	57                   	push   edi
   3611d:	55                   	push   ebp
   3611e:	83 ec 04             	sub    esp,0x4
   36121:	8b 2d d0 00 02 00    	mov    ebp,DWORD PTR ds:0x200d0
   36127:	bb 01 00 00 00       	mov    ebx,0x1
   3612c:	a1 cc 00 02 00       	mov    eax,ds:0x200cc
   36131:	ba 62 00 00 00       	mov    edx,0x62
   36136:	e8 fa 0c 01 00       	call   0x46e35
   3613b:	8b 0d cc 00 02 00    	mov    ecx,DWORD PTR ds:0x200cc
   36141:	a1 d4 00 02 00       	mov    eax,ds:0x200d4
   36146:	e8 98 01 01 00       	call   0x462e3
   3614b:	83 f8 01             	cmp    eax,0x1
   3614e:	74 10                	je     0x36160
   36150:	b8 fe ff ff ff       	mov    eax,0xfffffffe
   36155:	8b 2d d0 00 02 00    	mov    ebp,DWORD PTR ds:0x200d0
   3615b:	e9 b6 02 00 00       	jmp    0x36416
   36160:	8b 15 d4 00 02 00    	mov    edx,DWORD PTR ds:0x200d4
   36166:	66 8b 52 60          	mov    dx,WORD PTR [edx+0x60]
   3616a:	bb 01 00 00 00       	mov    ebx,0x1
   3616f:	a1 cc 00 02 00       	mov    eax,ds:0x200cc
   36174:	81         	and    edx,0xffff

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00037010 <.data+0x27010>:
   37010:	53                   	push   ebx
   37011:	51                   	push   ecx
   37012:	56                   	push   esi
   37013:	57                   	push   edi
   37014:	55                   	push   ebp
   37015:	83 ec 2c             	sub    esp,0x2c
   37018:	89 c5                	mov    ebp,eax
   3701a:	89 54 24 28          	mov    DWORD PTR [esp+0x28],edx
   3701e:	bb 01 00 00 00       	mov    ebx,0x1
   37023:	ba 42 00 00 00       	mov    edx,0x42
   37028:	8b 7c 24 28          	mov    edi,DWORD PTR [esp+0x28]
   3702c:	89 c1                	mov    ecx,eax
   3702e:	b8 e4 00 02 00       	mov    eax,0x200e4
   37033:	be e8 00 02 00       	mov    esi,0x200e8
   37038:	e8 a6 f2 00 00       	call   0x462e3
   3703d:	83 c7 09             	add    edi,0x9
   37040:	b9 14 00 00 00       	mov    ecx,0x14
   37045:	57                   	push   edi
   37046:	89 c8                	mov    eax,ecx
   37048:	c1 e9 02             	shr    ecx,0x2
   3704b:	f2 a5                	repnz movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
   3704d:	8a c8                	mov    cl,al
   3704f:	80 e1 03             	and    cl,0x3
   37052:	f2 a4                	repnz movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   37054:	5f                   	pop    edi
   37055:	8b 44 24 28          	mov    eax,DWORD PTR [esp+0x28]
   37059:	8b 54 24 28          	mov    edx,DWORD PTR [esp+0x28]
   3705d:	c6 40 1d 00          	mov    BYTE PTR [eax+0x1d],0x0
   37061:	89 d6                	mov    esi,edx
   37063:	a0 05 01 02 00       	mov    al,ds:0x20105
   37068:	31 c9                	xor    ecx,ecx
   3706a:	88 42 29             	mov    BYTE PTR [edx+0x29],al
   3706d:	31 c0                	xor    eax,eax
   3706f:	8a         	mov    al,BYTE PTR [ecx+0x20106]

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00037ea0 <.data+0x27ea0>:
   37ea0:	53                   	push   ebx
   37ea1:	51                   	push   ecx
   37ea2:	52                   	push   edx
   37ea3:	56                   	push   esi
   37ea4:	57                   	push   edi
   37ea5:	55                   	push   ebp
   37ea6:	83 ec 0c             	sub    esp,0xc
   37ea9:	8b 3d 9c 02 02 00    	mov    edi,DWORD PTR ds:0x2029c
   37eaf:	68 00 01 00 00       	push   0x100
   37eb4:	e8 47 dd ff ff       	call   0x35c00
   37eb9:	83 c4 04             	add    esp,0x4
   37ebc:	bb 01 00 00 00       	mov    ebx,0x1
   37ec1:	89 04 24             	mov    DWORD PTR [esp],eax
   37ec4:	a1 90 02 02 00       	mov    eax,ds:0x20290
   37ec9:	ba 60 00 00 00       	mov    edx,0x60
   37ece:	e8 62 ef 00 00       	call   0x46e35
   37ed3:	b8 28 02 02 00       	mov    eax,0x20228
   37ed8:	8b 0d 90 02 02 00    	mov    ecx,DWORD PTR ds:0x20290
   37ede:	e8 00 e4 00 00       	call   0x462e3
   37ee3:	8b 3d 9c 02 02 00    	mov    edi,DWORD PTR ds:0x2029c
   37ee9:	8a 15 5a 02 02 00    	mov    dl,BYTE PTR ds:0x2025a
   37eef:	88 57 5a             	mov    BYTE PTR [edi+0x5a],dl
   37ef2:	8a 15 59 02 02 00    	mov    dl,BYTE PTR ds:0x20259
   37ef8:	88 57 5b             	mov    BYTE PTR [edi+0x5b],dl
   37efb:	89 f8                	mov    eax,edi
   37efd:	8a 15 4a 02 02 00    	mov    dl,BYTE PTR ds:0x2024a
   37f03:	c6 47 29 00          	mov    BYTE PTR [edi+0x29],0x0
   37f07:	31 f8                	xor    eax,edi
   37f09:	88 57 4a             	mov    BYTE PTR [edi+0x4a],dl
   37f0c:	8a 90 68 02 02 00    	mov    dl,BYTE PTR [eax+0x20268]
   37f12:	8b 3d 9c 02 02 00    	mov    edi,DWORD PTR ds:0x2029c

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00039440 <.data+0x29440>:
   39440:	53                   	push   ebx
   39441:	51                   	push   ecx
   39442:	52                   	push   edx
   39443:	56                   	push   esi
   39444:	57                   	push   edi
   39445:	55                   	push   ebp
   39446:	83 ec 04             	sub    esp,0x4
   39449:	8b 2d b0 02 02 00    	mov    ebp,DWORD PTR ds:0x202b0
   3944f:	bb 01 00 00 00       	mov    ebx,0x1
   39454:	a1 a4 02 02 00       	mov    eax,ds:0x202a4
   39459:	ba f1 01 00 00       	mov    edx,0x1f1
   3945e:	e8 d2 d9 00 00       	call   0x46e35
   39463:	a1 b0 02 02 00       	mov    eax,ds:0x202b0
   39468:	8b 0d a4 02 02 00    	mov    ecx,DWORD PTR ds:0x202a4
   3946e:	e8 70 ce 00 00       	call   0x462e3
   39473:	8b 3d ac 02 02 00    	mov    edi,DWORD PTR ds:0x202ac
   39479:	be 14 a7 01 00       	mov    esi,0x1a714
   3947e:	83 c7 2a             	add    edi,0x2a
   39481:	b9 08 00 00 00       	mov    ecx,0x8
   39486:	31 d2                	xor    edx,edx
   39488:	c6 47 ff 08          	mov    BYTE PTR [edi-0x1],0x8
   3948c:	57                   	push   edi
   3948d:	89 c8                	mov    eax,ecx
   3948f:	c1 e9 02             	shr    ecx,0x2
   39492:	f2 a5                	repnz movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
   39494:	8a c8                	mov    cl,al
   39496:	80 e1 03             	and    cl,0x3
   39499:	f2 a4                	repnz movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   3949b:	5f                   	pop    edi
   3949c:	89 14 24             	mov    DWORD PTR [esp],edx
   3949f:	a1 ac 02 02 00       	mov    eax,ds:0x202ac
   394a4:	ba 80 00 00 00       	mov    edx,0x80
   394a9:	8b 2d b0 02 02 00    	mov    ebp,DWORD PTR ds:0x202b0
   394af:	c6             	mov    BYTE PTR [eax+0x5a],0x4e

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0003a070 <.data+0x2a070>:
   3a070:	53                   	push   ebx
   3a071:	51                   	push   ecx
   3a072:	56                   	push   esi
   3a073:	57                   	push   edi
   3a074:	55                   	push   ebp
   3a075:	83 ec 2c             	sub    esp,0x2c
   3a078:	89 44 24 20          	mov    DWORD PTR [esp+0x20],eax
   3a07c:	89 54 24 24          	mov    DWORD PTR [esp+0x24],edx
   3a080:	6a 41                	push   0x41
   3a082:	6a 1f                	push   0x1f
   3a084:	c6 42 4a 1f          	mov    BYTE PTR [edx+0x4a],0x1f
   3a088:	e8 7f bb ff ff       	call   0x35c0c
   3a08d:	83 c4 08             	add    esp,0x8
   3a090:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
   3a094:	89 42 4b             	mov    DWORD PTR [edx+0x4b],eax
   3a097:	85 c0                	test   eax,eax
   3a099:	0f 85 1e 01 00 00    	jne    0x3a1bd
   3a09f:	b8 ff ff ff ff       	mov    eax,0xffffffff
   3a0a4:	83 c4 2c             	add    esp,0x2c
   3a0a7:	5d                   	pop    ebp
   3a0a8:	5f                   	pop    edi
   3a0a9:	5e                   	pop    esi
   3a0aa:	59                   	pop    ecx
   3a0ab:	5b                   	pop    ebx
   3a0ac:	c3                   	ret    
   3a0ad:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
   3a0b1:	bb 01 00 00 00       	mov    ebx,0x1
   3a0b6:	ba 20 00 00 00       	mov    edx,0x20
   3a0bb:	89 e0                	mov    eax,esp
   3a0bd:	e8 21 c2 00 00       	call   0x462e3
   3a0c2:	8b 5c 24 24          	mov    ebx,DWORD PTR [esp+0x24]
   3a0c6:	8b 74 24 28          	mov    esi,DWORD PTR [esp+0x28]
   3a0ca:	8b 5b 4b             	mov    ebx,DWORD PTR [ebx+0x4b]
   3a0cd:	89 c1                	mov    ecx,eax
   3a0cf:	01                 	add    ebx,esi

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0003b010 <.data+0x2b010>:
   3b010:	53                   	push   ebx
   3b011:	51                   	push   ecx
   3b012:	56                   	push   esi
   3b013:	57                   	push   edi
   3b014:	55                   	push   ebp
   3b015:	83 ec 28             	sub    esp,0x28
   3b018:	89 c5                	mov    ebp,eax
   3b01a:	89 54 24 20          	mov    DWORD PTR [esp+0x20],edx
   3b01e:	80 3a 04             	cmp    BYTE PTR [edx],0x4
   3b021:	75 07                	jne    0x3b02a
   3b023:	b8 0f 00 00 00       	mov    eax,0xf
   3b028:	eb 05                	jmp    0x3b02f
   3b02a:	b8 1f 00 00 00       	mov    eax,0x1f
   3b02f:	8b 54 24 20          	mov    edx,DWORD PTR [esp+0x20]
   3b033:	a2 ff 04 02 00       	mov    ds:0x204ff,al
   3b038:	88 42 4a             	mov    BYTE PTR [edx+0x4a],al
   3b03b:	31 c0                	xor    eax,eax
   3b03d:	6a 41                	push   0x41
   3b03f:	a0 ff 04 02 00       	mov    al,ds:0x204ff
   3b044:	50                   	push   eax
   3b045:	e8 c2 ab ff ff       	call   0x35c0c
   3b04a:	83 c4 08             	add    esp,0x8
   3b04d:	8b 54 24 20          	mov    edx,DWORD PTR [esp+0x20]
   3b051:	89 42 4b             	mov    DWORD PTR [edx+0x4b],eax
   3b054:	85 c0                	test   eax,eax
   3b056:	0f 85 45 01 00 00    	jne    0x3b1a1
   3b05c:	b8 ff ff ff ff       	mov    eax,0xffffffff
   3b061:	83 c4 28             	add    esp,0x28
   3b064:	5d                   	pop    ebp
   3b065:	5f                   	pop    edi
   3b066:	5e                   	pop    esi
   3b067:	59                   	pop    ecx
   3b068:	5b                   	pop    ebx
   3b069:	c3                   	ret    
   3b06a:	bb 01 00 00 00       	mov    ebx,0x1
   3b06f:	ba 1e 00 00 00       	mov    edx,0x1e
   3b074:	89 e0                	mov    eax,esp
   3b076:	89 e9                	mov    ecx,ebp
   3b078:	e8 66 b2 00 00       	call   0x462e3
   3b07d:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
   3b081:	bb 16 00 00 00       	mov    ebx,0x16
   3b086:	8b 49 4b             	mov    ecx,DWORD PTR [ecx+0x4b]
   3b089:	89 e2                	mov    edx,esp
   3b08b:	01 f9                	add    ecx,edi
   3b08d:	89 44 24           	mov    DWORD PTR [esp+0x24],eax
