
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010790 <.data+0x790>:
   10790:	66 83 3d 80 10 00 00 	cmp    WORD PTR ds:0x1080,0x0
   10797:	00 
   10798:	75 35                	jne    0x107cf
   1079a:	66 b8 08 35          	mov    ax,0x3508
   1079e:	cd 21                	int    0x21
   107a0:	89 1d 7c 10 00 00    	mov    DWORD PTR ds:0x107c,ebx
   107a6:	66 8c 05 80 10 00 00 	data16 mov WORD PTR ds:0x1080,es
   107ad:	66 b8 00 00          	mov    ax,0x0
   107b1:	8e d8                	mov    ds,eax
   107b3:	ba 4d 08 00 00       	mov    edx,0x84d
   107b8:	66 b8 08 25          	mov    ax,0x2508
   107bc:	cd 21                	int    0x21
   107be:	66 b8 00 00          	mov    ax,0x0
   107c2:	8e d8                	mov    ds,eax
   107c4:	8e c0                	mov    es,eax
   107c6:	66 bb 68 42          	mov    bx,0x4268
   107ca:	e8 3f 00 00 00       	call   0x1080e
   107cf:	c3                   	ret    
   107d0:	66 83 3d 80 10 00 00 	cmp    WORD PTR ds:0x1080,0x0
   107d7:	00 
   107d8:	74 33                	je     0x1080d
   107da:	66 bb ff ff          	mov    bx,0xffff
   107de:	e8 2b 00 00 00       	call   0x1080e
   107e3:	8b 15 7c 10 00 00    	mov    edx,DWORD PTR ds:0x107c
   107e9:	8e 1d 80 10 00 00    	mov    ds,WORD PTR ds:0x1080
   107ef:	66 b8 08 25          	mov    ax,0x2508
   107f3:	cd 21                	int    0x21
   107f5:	66 b8 00 00          	mov    ax,0x0
   107f9:	8e d8                	mov    ds,eax
   107fb:	66 bb ff ff          	mov    bx,0xffff
   107ff:	e8 0a 00 00 00       	call   0x1080e
   10804:	66 c7 05 80 10 00 00 	mov    WORD PTR ds:0x1080,0x0
   1080b:	00 00 
   1080d:	c3                   	ret    
   1080e:	66 9c                	pushfw 
   10810:	fa                   	cli    
   10811:	66 ba 43 00          	mov    dx,0x43
   10815:	b0 36                	mov    al,0x36
   10817:	ee                   	out    dx,al
   10818:	b2 40                	mov    dl,0x40
   1081a:	8a c3                	mov    al,bl
   1081c:	ee                   	out    dx,al
   1081d:	8a c7                	mov    al,bh
   1081f:	ee                   	out    dx,al
   10820:	66 9d                	popfw  
   10822:	c3                   	ret    
   10823:	66 83 3d 80 10 00 00 	cmp    WORD PTR ds:0x1080,0x0
   1082a:	00 
   1082b:	75 10                	jne    0x1083d
   1082d:	66 ba da 03          	mov    dx,0x3da
   10831:	ec                   	in     al,dx
   10832:	a8 08                	test   al,0x8
   10834:	75 fb                	jne    0x10831
   10836:	ec                   	in     al,dx
   10837:	a8 08                	test   al,0x8
   10839:	74 fb                	je     0x10836
   1083b:	eb 0f                	jmp    0x1084c
   1083d:	66 a1 82 10 00 00    	mov    ax,ds:0x1082
   10843:	66 3b 05 82 10 00 00 	cmp    ax,WORD PTR ds:0x1082
   1084a:	74 f7                	je     0x10843
   1084c:	c3                   	ret    
   1084d:	60                   	pusha  
   1084e:	1e                   	push   ds
   1084f:	06                   	push   es
   10850:	0f a0                	push   fs
   10852:	0f a8                	push   gs
   10854:	66 b8 00 00          	mov    ax,0x0
   10858:	8e d8                	mov    ds,eax
   1085a:	8e c0                	mov    es,eax
   1085c:	b3 ff                	mov    bl,0xff
   1085e:	b0 36                	mov    al,0x36
   10860:	e6 43                	out    0x43,al
   10862:	8a c3                	mov    al,bl
   10864:	e6 40                	out    0x40,al
   10866:	8a c3                	mov    al,bl
   10868:	e6 40                	out    0x40,al
   1086a:	a0 dd 10 00 00       	mov    al,ds:0x10dd
   1086f:	0a c0                	or     al,al
   10871:	74 0a                	je     0x1087d
   10873:	3c ff                	cmp    al,0xff
   10875:	74 06                	je     0x1087d
   10877:	fe 05 dd 10 00 00    	inc    BYTE PTR ds:0x10dd
   1087d:	a0 e9 10 00 00       	mov    al,ds:0x10e9
   10882:	0a c0                	or     al,al
   10884:	74 0a                	je     0x10890
   10886:	3c ff                	cmp    al,0xff
   10888:	74 06                	je     0x10890
   1088a:	fe 05 e9 10 00 00    	inc    BYTE PTR ds:0x10e9
   10890:	66 ff 05 82 10 00 00 	inc    WORD PTR ds:0x1082
   10897:	fe 05 84 10 00 00    	inc    BYTE PTR ds:0x1084
   1089d:	ff 05 90 c3 01 00    	inc    DWORD PTR ds:0x1c390
   108a3:	66 83 3d 86 10 00 00 	cmp    WORD PTR ds:0x1086,0x0
   108aa:	00 
   108ab:	74 07                	je     0x108b4
   108ad:	66 ff 0d 86 10 00 00 	dec    WORD PTR ds:0x1086
   108b4:	e8 72 fd ff ff       	call   0x1062b
   108b9:	e8 4a fd ff ff       	call   0x10608
   108be:	66 83 3d 64 9b 01 00 	cmp    WORD PTR ds:0x19b64,0xffff
   108c5:	ff 
   108c6:	0f 84 e4 00 00 00    	je     0x109b0
   108cc:	80 3d e2 fa 01 00 0a 	cmp    BYTE PTR ds:0x1fae2,0xa
   108d3:	75 05                	jne    0x108da
   108d5:	e8 cb d1 02 00       	call   0x3daa5
   108da:	fe 0d 93 10 00 00    	dec    BYTE PTR ds:0x1093
   108e0:	79 0c                	jns    0x108ee
   108e2:	e8 be 49 03 00       	call   0x452a5
   108e7:	c6 05 93 10 00 00 05 	mov    BYTE PTR ds:0x1093,0x5
   108ee:	a1 ac 9a 01 00       	mov    eax,ds:0x19aac
   108f3:	48                   	dec    eax
   108f4:	78 10                	js     0x10906
   108f6:	8b 1d b0 9a 01 00    	mov    ebx,DWORD PTR ds:0x19ab0
   108fc:	4b                   	dec    ebx
   108fd:	3b c3                	cmp    eax,ebx
   108ff:	73 05                	jae    0x10906
   10901:	e8 15 88 00 00       	call   0x1911b
   10906:	66 a1 82 10 00 00    	mov    ax,ds:0x1082
   1090c:	66 25 03 00          	and    ax,0x3
   10910:	0f 85 9a 00 00 00    	jne    0x109b0
   10916:	80 3d bf 10 00 00 00 	cmp    BYTE PTR ds:0x10bf,0x0
   1091d:	74 22                	je     0x10941
   1091f:	83 3d b0 9a 01 00 00 	cmp    DWORD PTR ds:0x19ab0,0x0
   10926:	7e 19                	jle    0x10941
   10928:	a1 b0 9a 01 00       	mov    eax,ds:0x19ab0
   1092d:	ff 0d b0 9a 01 00    	dec    DWORD PTR ds:0x19ab0
   10933:	39 05 ac 9a 01 00    	cmp    DWORD PTR ds:0x19aac,eax
   10939:	75 06                	jne    0x10941
   1093b:	48                   	dec    eax
   1093c:	e8 da 87 00 00       	call   0x1911b
   10941:	80 3d c0 10 00 00 00 	cmp    BYTE PTR ds:0x10c0,0x0
   10948:	74 22                	je     0x1096c
   1094a:	83 3d b0 9a 01 00 40 	cmp    DWORD PTR ds:0x19ab0,0x40
   10951:	7d 19                	jge    0x1096c
   10953:	a1 b0 9a 01 00       	mov    eax,ds:0x19ab0
   10958:	ff 05 b0 9a 01 00    	inc    DWORD PTR ds:0x19ab0
   1095e:	39 05 ac 9a 01 00    	cmp    DWORD PTR ds:0x19aac,eax
   10964:	75 06                	jne    0x1096c
   10966:	40                   	inc    eax
   10967:	e8 af 87 00 00       	call   0x1911b
   1096c:	80 3d cd 10 00 00 00 	cmp    BYTE PTR ds:0x10cd,0x0
   10973:	74 19                	je     0x1098e
   10975:	83 3d b4 9a 01 00 00 	cmp    DWORD PTR ds:0x19ab4,0x0
   1097c:	7e 10                	jle    0x1098e
   1097e:	ff 0d b4 9a 01 00    	dec    DWORD PTR ds:0x19ab4
   10984:	a1 b4 9a 01 00       	mov    eax,ds:0x19ab4
   10989:	e8 bc 87 00 00       	call   0x1914a
   1098e:	80 3d ce 10 00 00 00 	cmp    BYTE PTR ds:0x10ce,0x0
   10995:	74 19                	je     0x109b0
   10997:	83 3d b4 9a 01 00 40 	cmp    DWORD PTR ds:0x19ab4,0x40
   1099e:	7d 10                	jge    0x109b0
   109a0:	ff 05 b4 9a 01 00    	inc    DWORD PTR ds:0x19ab4
   109a6:	a1 b4 9a 01 00       	mov    eax,ds:0x19ab4
   109ab:	e8 9a 87 00 00       	call   0x1914a
   109b0:	b0 20                	mov    al,0x20
   109b2:	e6 20                	out    0x20,al
   109b4:	66 bb 36 2e          	mov    bx,0x2e36
   109b8:	b0 36                	mov    al,0x36
   109ba:	e6 43                	out    0x43,al
   109bc:	8a c3                	mov    al,bl
   109be:	e6 40                	out    0x40,al
   109c0:	8a c7                	mov    al,bh
   109c2:	e6 40                	out    0x40,al
   109c4:	fb                   	sti    
   109c5:	0f a9                	pop    gs
   109c7:	0f a1                	pop    fs
   109c9:	07                   	pop    es
   109ca:	1f                   	pop    ds
   109cb:	61                   	popa   
   109cc:	cf                   	iret   

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000109cf <.data+0x9cf>:
   109cf:	66 9c                	pushfw 
   109d1:	fa                   	cli    
   109d2:	66 b8 00 00          	mov    ax,0x0
   109d6:	8e d8                	mov    ds,eax
   109d8:	ba 4d 08 00 00       	mov    edx,0x84d
   109dd:	66 b8 08 25          	mov    ax,0x2508
   109e1:	cd 21                	int    0x21
   109e3:	66 b8 00 00          	mov    ax,0x0
   109e7:	8e d8                	mov    ds,eax
   109e9:	66 9d                	popfw  
   109eb:	a1 89 10 00 00       	mov    eax,ds:0x1089
   109f0:	a3 8d 10 00 00       	mov    ds:0x108d,eax
   109f5:	8b 35 8d 10 00 00    	mov    esi,DWORD PTR ds:0x108d
   109fb:	83 05 8d 10 00 00 0c 	add    DWORD PTR ds:0x108d,0xc
   10a02:	66 8b 5e 0a          	mov    bx,WORD PTR [esi+0xa]
   10a06:	66 01 1d 91 10 00 00 	add    WORD PTR ds:0x1091,bx
   10a0d:	66 39 1d a0 10 00 00 	cmp    WORD PTR ds:0x10a0,bx
   10a14:	74 18                	je     0x10a2e
   10a16:	66 89 1d a0 10 00 00 	mov    WORD PTR ds:0x10a0,bx
   10a1d:	66 9c                	pushfw 
   10a1f:	fa                   	cli    
   10a20:	b0 36                	mov    al,0x36
   10a22:	e6 43                	out    0x43,al
   10a24:	8a c3                	mov    al,bl
   10a26:	e6 40                	out    0x40,al
   10a28:	8a c7                	mov    al,bh
   10a2a:	e6 40                	out    0x40,al
   10a2c:	66 9d                	popfw  
   10a2e:	fb                   	sti    
   10a2f:	33 db                	xor    ebx,ebx
   10a31:	66 8b 1e             	mov    bx,WORD PTR [esi]
   10a34:	8b 9b 94 10 00 00    	mov    ebx,DWORD PTR [ebx+0x1094]
   10a3a:	ff d3                	call   ebx
   10a3c:	c3                   	ret    
   10a3d:	66 9c                	pushfw 
   10a3f:	fa                   	cli    
   10a40:	66 ba c8 03          	mov    dx,0x3c8
   10a44:	8a 46 02             	mov    al,BYTE PTR [esi+0x2]
   10a47:	ee                   	out    dx,al
   10a48:	fe c2                	inc    dl
   10a4a:	8a 46 04             	mov    al,BYTE PTR [esi+0x4]
   10a4d:	32 e4                	xor    ah,ah
   10a4f:	b3 3f                	mov    bl,0x3f
   10a51:	66 03 05 a2 10 00 00 	add    ax,WORD PTR ds:0x10a2
   10a58:	79 03                	jns    0x10a5d
   10a5a:	66 33 c0             	xor    ax,ax
   10a5d:	3a c3                	cmp    al,bl
   10a5f:	76 02                	jbe    0x10a63
   10a61:	8a c3                	mov    al,bl
   10a63:	ee                   	out    dx,al
   10a64:	8a 46 06             	mov    al,BYTE PTR [esi+0x6]
   10a67:	66 03 05 a2 10 00 00 	add    ax,WORD PTR ds:0x10a2
   10a6e:	79 03                	jns    0x10a73
   10a70:	66 33 c0             	xor    ax,ax
   10a73:	3a c3                	cmp    al,bl
   10a75:	76 02                	jbe    0x10a79
   10a77:	8a c3                	mov    al,bl
   10a79:	ee                   	out    dx,al
   10a7a:	8a 46 08             	mov    al,BYTE PTR [esi+0x8]
   10a7d:	66 03 05 a2 10 00 00 	add    ax,WORD PTR ds:0x10a2
   10a84:	79 03                	jns    0x10a89
   10a86:	66 33 c0             	xor    ax,ax
   10a89:	3a c3                	cmp    al,bl
   10a8b:	76 02                	jbe    0x10a8f
   10a8d:	8a c3                	mov    al,bl
   10a8f:	ee                   	out    dx,al
   10a90:	66 9d                	popfw  
   10a92:	c3                   	ret    
   10a93:	66 bb 36 2e          	mov    bx,0x2e36
   10a97:	66 89 1d a0 10 00 00 	mov    WORD PTR ds:0x10a0,bx
   10a9e:	66 2b 5e 0a          	sub    bx,WORD PTR [esi+0xa]
   10aa2:	66 2b 1d 91 10 00 00 	sub    bx,WORD PTR ds:0x1091
   10aa9:	66 9c                	pushfw 
   10aab:	fa                   	cli    
   10aac:	b0 36                	mov    al,0x36
   10aae:	e6 43                	out    0x43,al
   10ab0:	8a c3                	mov    al,bl
   10ab2:	e6 40                	out    0x40,al
   10ab4:	8a c7                	mov    al,bh
   10ab6:	e6 40                	out    0x40,al
   10ab8:	66 b8 00 00          	mov    ax,0x0
   10abc:	8e d8                	mov    ds,eax
   10abe:	ba 4d 08 00 00       	mov    edx,0x84d
   10ac3:	66 b8 08 25          	mov    ax,0x2508
   10ac7:	cd 21                	int    0x21
   10ac9:	66 9d                	popfw  
   10acb:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010b98 <.data+0xb98>:
   10b98:	66 83 3d b0 10 00 00 	cmp    WORD PTR ds:0x10b0,0x0
   10b9f:	00 
   10ba0:	75 3a                	jne    0x10bdc
   10ba2:	66 b8 09 35          	mov    ax,0x3509
   10ba6:	cd 21                	int    0x21
   10ba8:	89 1d ac 10 00 00    	mov    DWORD PTR ds:0x10ac,ebx
   10bae:	66 8c 05 b0 10 00 00 	data16 mov WORD PTR ds:0x10b0,es
   10bb5:	66 b8 00 00          	mov    ax,0x0
   10bb9:	8e d8                	mov    ds,eax
   10bbb:	ba 0a 0c 00 00       	mov    edx,0xc0a
   10bc0:	66 b8 09 25          	mov    ax,0x2509
   10bc4:	cd 21                	int    0x21
   10bc6:	66 b8 00 00          	mov    ax,0x0
   10bca:	8e d8                	mov    ds,eax
   10bcc:	8e c0                	mov    es,eax
   10bce:	bf b3 10 00 00       	mov    edi,0x10b3
   10bd3:	b9 20 00 00 00       	mov    ecx,0x20
   10bd8:	33 c0                	xor    eax,eax
   10bda:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   10bdc:	c3                   	ret    
   10bdd:	66 83 3d b0 10 00 00 	cmp    WORD PTR ds:0x10b0,0x0
   10be4:	00 
   10be5:	74 21                	je     0x10c08
   10be7:	8b 15 ac 10 00 00    	mov    edx,DWORD PTR ds:0x10ac
   10bed:	8e 1d b0 10 00 00    	mov    ds,WORD PTR ds:0x10b0
   10bf3:	66 b8 08 25          	mov    ax,0x2508
   10bf7:	cd 21                	int    0x21
   10bf9:	66 b8 00 00          	mov    ax,0x0
   10bfd:	8e d8                	mov    ds,eax
   10bff:	66 c7 05 b0 10 00 00 	mov    WORD PTR ds:0x10b0,0x0
   10c06:	00 00 
   10c08:	c3                   	ret    
   10c09:	c3                   	ret    
   10c0a:	1e                   	push   ds
   10c0b:	06                   	push   es
   10c0c:	66 50                	push   ax
   10c0e:	53                   	push   ebx
   10c0f:	e4 60                	in     al,0x60
   10c11:	8a e0                	mov    ah,al
   10c13:	e4 61                	in     al,0x61
   10c15:	0c 80                	or     al,0x80
   10c17:	e6 61                	out    0x61,al
   10c19:	24 7f                	and    al,0x7f
   10c1b:	e6 61                	out    0x61,al
   10c1d:	66 bb 00 00          	mov    bx,0x0
   10c21:	8e db                	mov    ds,ebx
   10c23:	8e c3                	mov    es,ebx
   10c25:	88 25 b2 10 00 00    	mov    BYTE PTR ds:0x10b2,ah
   10c2b:	33 db                	xor    ebx,ebx
   10c2d:	8a dc                	mov    bl,ah
   10c2f:	80 e3 7f             	and    bl,0x7f
   10c32:	32 c0                	xor    al,al
   10c34:	d0 e4                	shl    ah,1
   10c36:	0f 82 81 00 00 00    	jb     0x10cbd
   10c3c:	80 fb 2a             	cmp    bl,0x2a
   10c3f:	74 05                	je     0x10c46
   10c41:	80 fb 36             	cmp    bl,0x36
   10c44:	75 04                	jne    0x10c4a
   10c46:	fe c0                	inc    al
   10c48:	eb 02                	jmp    0x10c4c
   10c4a:	b0 ff                	mov    al,0xff
   10c4c:	80 fb 4b             	cmp    bl,0x4b
   10c4f:	74 0f                	je     0x10c60
   10c51:	80 fb 4d             	cmp    bl,0x4d
   10c54:	74 0a                	je     0x10c60
   10c56:	80 fb 48             	cmp    bl,0x48
   10c59:	74 05                	je     0x10c60
   10c5b:	80 fb 50             	cmp    bl,0x50
   10c5e:	75 20                	jne    0x10c80
   10c60:	80 3d dd 10 00 00 00 	cmp    BYTE PTR ds:0x10dd,0x0
   10c67:	74 07                	je     0x10c70
   10c69:	c6 05 dd 10 00 00 00 	mov    BYTE PTR ds:0x10dd,0x0
   10c70:	80 3d dd 10 00 00 00 	cmp    BYTE PTR ds:0x10dd,0x0
   10c77:	74 07                	je     0x10c80
   10c79:	c6 05 e9 10 00 00 00 	mov    BYTE PTR ds:0x10e9,0x0
   10c80:	80 3d 3d 11 00 00 00 	cmp    BYTE PTR ds:0x113d,0x0
   10c87:	74 34                	je     0x10cbd
   10c89:	56                   	push   esi
   10c8a:	8b 35 33 11 00 00    	mov    esi,DWORD PTR ds:0x1133
   10c90:	3a 1e                	cmp    bl,BYTE PTR [esi]
   10c92:	75 1e                	jne    0x10cb2
   10c94:	ff 05 33 11 00 00    	inc    DWORD PTR ds:0x1133
   10c9a:	80 7e 01 ff          	cmp    BYTE PTR [esi+0x1],0xff
   10c9e:	75 10                	jne    0x10cb0
   10ca0:	c6 05 8a 9a 01 00 ff 	mov    BYTE PTR ds:0x19a8a,0xff
   10ca7:	66 c7 05 3e 11 00 00 	mov    WORD PTR ds:0x113e,0x64
   10cae:	64 00 
   10cb0:	eb 0a                	jmp    0x10cbc
   10cb2:	c7 05 33 11 00 00 37 	mov    DWORD PTR ds:0x1133,0x1137
   10cb9:	11 00 00 
   10cbc:	5e                   	pop    esi
   10cbd:	88 83 b3 10 00 00    	mov    BYTE PTR [ebx+0x10b3],al
   10cc3:	b0 20                	mov    al,0x20
   10cc5:	e6 20                	out    0x20,al
   10cc7:	5b                   	pop    ebx
   10cc8:	66 58                	pop    ax
   10cca:	07                   	pop    es
   10ccb:	1f                   	pop    ds
   10ccc:	cf                   	iret   

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010234 <.data+0x234>:
   10234:	66 8b 35 72 15 00 00 	mov    si,WORD PTR ds:0x1572
   1023b:	66 03 35 e2 73 01 00 	add    si,WORD PTR ds:0x173e2
   10242:	83 e6 07             	and    esi,0x7
   10245:	b8 40 01 00 00       	mov    eax,0x140
   1024a:	0f af f0             	imul   esi,eax
   1024d:	03 35 9c 03 00 00    	add    esi,DWORD PTR ds:0x39c
   10253:	33 c9                	xor    ecx,ecx
   10255:	fa                   	cli    
   10256:	8a 0d 84 10 00 00    	mov    cl,BYTE PTR ds:0x1084
   1025c:	c6 05 84 10 00 00 00 	mov    BYTE PTR ds:0x1084,0x0
   10263:	fb                   	sti    
   10264:	88 0d 85 10 00 00    	mov    BYTE PTR ds:0x1085,cl
   1026a:	bf 00 00 0a 00       	mov    edi,0xa0000
   1026f:	b9 80 3e 00 00       	mov    ecx,0x3e80
   10274:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
   10276:	66 c7 05 e2 73 01 00 	mov    WORD PTR ds:0x173e2,0x0
   1027d:	00 00 
   1027f:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00011799 <.data+0x1799>:
   11799:	33 db                	xor    ebx,ebx
   1179b:	66 8b 1d 8a 15 00 00 	mov    bx,WORD PTR ds:0x158a
   117a2:	c1 e3 03             	shl    ebx,0x3
   117a5:	81 eb 40 01 00 00    	sub    ebx,0x140
   117ab:	66 a1 6c 15 00 00    	mov    ax,ds:0x156c
   117b1:	66 0b c0             	or     ax,ax
   117b4:	79 03                	jns    0x117b9
   117b6:	66 33 c0             	xor    ax,ax
   117b9:	66 3b c3             	cmp    ax,bx
   117bc:	7e 03                	jle    0x117c1
   117be:	66 8b c3             	mov    ax,bx
   117c1:	66 a3 6c 15 00 00    	mov    ds:0x156c,ax
   117c7:	66 a3 70 15 00 00    	mov    ds:0x1570,ax
   117cd:	66 25 f8 ff          	and    ax,0xfff8
   117d1:	66 a3 cc 03 00 00    	mov    ds:0x3cc,ax
   117d7:	33 db                	xor    ebx,ebx
   117d9:	66 8b 1d 8c 15 00 00 	mov    bx,WORD PTR ds:0x158c
   117e0:	c1 e3 03             	shl    ebx,0x3
   117e3:	81 eb c8 00 00 00    	sub    ebx,0xc8
   117e9:	66 a1 6e 15 00 00    	mov    ax,ds:0x156e
   117ef:	66 0b c0             	or     ax,ax
   117f2:	79 03                	jns    0x117f7
   117f4:	66 33 c0             	xor    ax,ax
   117f7:	66 3b c3             	cmp    ax,bx
   117fa:	7e 03                	jle    0x117ff
   117fc:	66 8b c3             	mov    ax,bx
   117ff:	66 a3 6e 15 00 00    	mov    ds:0x156e,ax
   11805:	66 a3 72 15 00 00    	mov    ds:0x1572,ax
   1180b:	66 03 05 e2 73 01 00 	add    ax,WORD PTR ds:0x173e2
   11812:	66 25 f8 ff          	and    ax,0xfff8
   11816:	66 a3 ce 03 00 00    	mov    ds:0x3ce,ax
   1181c:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000144a3 <.data+0x44a3>:
   144a3:	e8 f1 d2 ff ff       	call   0x11799
   144a8:	e8 70 d3 ff ff       	call   0x1181d
   144ad:	c6 05 a4 9a 01 00 00 	mov    BYTE PTR ds:0x19aa4,0x0
   144b4:	e8 a9 42 00 00       	call   0x18762
   144b9:	e8 f0 d5 ff ff       	call   0x11aae
   144be:	c6 05 a4 9a 01 00 80 	mov    BYTE PTR ds:0x19aa4,0x80
   144c5:	e8 98 42 00 00       	call   0x18762
   144ca:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0xb
   144d1:	0b 
   144d2:	7d 19                	jge    0x144ed
   144d4:	e8 ca 57 00 00       	call   0x19ca3
   144d9:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0x4
   144e0:	04 
   144e1:	74 05                	je     0x144e8
   144e3:	e8 e0 5a 00 00       	call   0x19fc8
   144e8:	e8 41 58 00 00       	call   0x19d2e
   144ed:	e8 42 bd ff ff       	call   0x10234
   144f2:	c3                   	ret    
   144f3:	e8 a1 d2 ff ff       	call   0x11799
   144f8:	e8 20 d3 ff ff       	call   0x1181d
   144fd:	c6 05 a4 9a 01 00 00 	mov    BYTE PTR ds:0x19aa4,0x0
   14504:	e8 59 42 00 00       	call   0x18762
   14509:	e8 a0 d5 ff ff       	call   0x11aae
   1450e:	c6 05 a4 9a 01 00 80 	mov    BYTE PTR ds:0x19aa4,0x80
   14515:	e8 48 42 00 00       	call   0x18762
   1451a:	e8 15 bd ff ff       	call   0x10234
   1451f:	c3                   	ret    
   14520:	66 33 c0             	xor    ax,ax
   14523:	a0 85 10 00 00       	mov    al,ds:0x1085
   14528:	b3 05                	mov    bl,0x5
   1452a:	f6 e3                	mul    bl
   1452c:	66 03 05 1d 54 00 00 	add    ax,WORD PTR ds:0x541d
   14533:	b3 0a                	mov    bl,0xa
   14535:	f6 f3                	div    bl
   14537:	88 25 1d 54 00 00    	mov    BYTE PTR ds:0x541d,ah
   1453d:	0a c0                	or     al,al
   1453f:	74 0c                	je     0x1454d
   14541:	66 50                	push   ax
   14543:	52                   	push   edx
   14544:	ff d2                	call   edx
   14546:	5a                   	pop    edx
   14547:	66 58                	pop    ax
   14549:	fe c8                	dec    al
   1454b:	75 f4                	jne    0x14541
   1454d:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00014a10 <.data+0x4a10>:
   14a10:	c6 05 b2 10 00 00 00 	mov    BYTE PTR ds:0x10b2,0x0
   14a17:	80 3d 8a 9a 01 00 00 	cmp    BYTE PTR ds:0x19a8a,0x0
   14a1e:	74 29                	je     0x14a49
   14a20:	33 c0                	xor    eax,eax
   14a22:	33 db                	xor    ebx,ebx
   14a24:	8a 1d b2 10 00 00    	mov    bl,BYTE PTR ds:0x10b2
   14a2a:	80 fb 26             	cmp    bl,0x26
   14a2d:	75 09                	jne    0x14a38
   14a2f:	66 c7 05 65 93 01 00 	mov    WORD PTR ds:0x19365,0xffff
   14a36:	ff ff 
   14a38:	80 fb 23             	cmp    bl,0x23
   14a3b:	75 0c                	jne    0x14a49
   14a3d:	66 a1 d0 73 01 00    	mov    ax,ds:0x173d0
   14a43:	66 a3 ce 73 01 00    	mov    ds:0x173ce,ax
   14a49:	80 3d f0 73 01 00 00 	cmp    BYTE PTR ds:0x173f0,0x0
   14a50:	74 14                	je     0x14a66
   14a52:	80 3d b2 10 00 00 00 	cmp    BYTE PTR ds:0x10b2,0x0
   14a59:	75 6a                	jne    0x14ac5
   14a5b:	a0 88 c3 01 00       	mov    al,ds:0x1c388
   14a60:	24 0f                	and    al,0xf
   14a62:	3c 0f                	cmp    al,0xf
   14a64:	74 5f                	je     0x14ac5
   14a66:	66 83 3d 65 93 01 00 	cmp    WORD PTR ds:0x19365,0x0
   14a6d:	00 
   14a6e:	0f 85 da fa ff ff    	jne    0x1454e
   14a74:	66 83 3d ce 73 01 00 	cmp    WORD PTR ds:0x173ce,0x0
   14a7b:	00 
   14a7c:	75 24                	jne    0x14aa2
   14a7e:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0xc
   14a85:	0c 
   14a86:	0f 8d c2 fa ff ff    	jge    0x1454e
   14a8c:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0xb
   14a93:	0b 
   14a94:	74 0c                	je     0x14aa2
   14a96:	66 ff 0d c6 73 01 00 	dec    WORD PTR ds:0x173c6
   14a9d:	e9 19 f5 ff ff       	jmp    0x13fbb
   14aa2:	e8 fc f9 ff ff       	call   0x144a3
   14aa7:	ba 50 4f 00 00       	mov    edx,0x4f50
   14aac:	e8 6f fa ff ff       	call   0x14520
   14ab1:	80 3d b4 10 00 00 00 	cmp    BYTE PTR ds:0x10b4,0x0
   14ab8:	0f 84 59 ff ff ff    	je     0x14a17
   14abe:	c6 05 b4 10 00 00 00 	mov    BYTE PTR ds:0x10b4,0x0
   14ac5:	66 c7 05 60 0a 00 00 	mov    WORD PTR ds:0xa60,0x1
   14acc:	01 00 
   14ace:	66 c7 05 62 0a 00 00 	mov    WORD PTR ds:0xa62,0x0
   14ad5:	00 00 
   14ad7:	e8 89 3b 00 00       	call   0x18665
   14adc:	e8 1d bc ff ff       	call   0x106fe
   14ae1:	c6 05 f0 73 01 00 00 	mov    BYTE PTR ds:0x173f0,0x0
   14ae8:	66 c7 05 63 93 01 00 	mov    WORD PTR ds:0x19363,0xffff
   14aef:	ff ff 
   14af1:	e9 ba fb ff ff       	jmp    0x146b0
   14af6:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00014caf <.data+0x4caf>:
   14caf:	56                   	push   esi
   14cb0:	80 3d f0 73 01 00 00 	cmp    BYTE PTR ds:0x173f0,0x0
   14cb7:	0f 85 06 01 00 00    	jne    0x14dc3
   14cbd:	80 3d 8c 9a 01 00 00 	cmp    BYTE PTR ds:0x19a8c,0x0
   14cc4:	0f 85 f9 00 00 00    	jne    0x14dc3
   14cca:	66 a1 8e 73 01 00    	mov    ax,ds:0x1738e
   14cd0:	80 3d cc 10 00 00 00 	cmp    BYTE PTR ds:0x10cc,0x0
   14cd7:	0f 84 e6 00 00 00    	je     0x14dc3
   14cdd:	8b 35 2a 4f 00 00    	mov    esi,DWORD PTR ds:0x4f2a
   14ce3:	0b f6                	or     esi,esi
   14ce5:	74 0a                	je     0x14cf1
   14ce7:	8b 76 10             	mov    esi,DWORD PTR [esi+0x10]
   14cea:	c7 46 12 62 60 01 00 	mov    DWORD PTR [esi+0x12],0x16062
   14cf1:	e8 ad f7 ff ff       	call   0x144a3
   14cf6:	66 b8 6a 00          	mov    ax,0x6a
   14cfa:	66 03 05 70 15 00 00 	add    ax,WORD PTR ds:0x1570
   14d01:	66 bb 50 00          	mov    bx,0x50
   14d05:	66 03 1d ce 03 00 00 	add    bx,WORD PTR ds:0x3ce
   14d0c:	66 0f b6 0d cb ba 00 	movzx  cx,BYTE PTR ds:0xbacb
   14d13:	00 
   14d14:	66 0f b6 15 ca ba 00 	movzx  dx,BYTE PTR ds:0xbaca
   14d1b:	00 
   14d1c:	e8 78 c0 ff ff       	call   0x10d99
   14d21:	e8 0e b5 ff ff       	call   0x10234
   14d26:	c6 05 cc 10 00 00 00 	mov    BYTE PTR ds:0x10cc,0x0
   14d2d:	66 b9 06 00          	mov    cx,0x6
   14d31:	66 0b c9             	or     cx,cx
   14d34:	78 3b                	js     0x14d71
   14d36:	75 31                	jne    0x14d69
   14d38:	66 c7 05 60 0a 00 00 	mov    WORD PTR ds:0xa60,0x4
   14d3f:	04 00 
   14d41:	66 c7 05 62 0a 00 00 	mov    WORD PTR ds:0xa62,0x0
   14d48:	00 00 
   14d4a:	8b 35 a2 15 00 00    	mov    esi,DWORD PTR ds:0x15a2
   14d50:	e8 76 b8 ff ff       	call   0x105cb
   14d55:	66 83 3d 64 9b 01 00 	cmp    WORD PTR ds:0x19b64,0xffff
   14d5c:	ff 
   14d5d:	74 0a                	je     0x14d69
   14d5f:	e8 c2 09 03 00       	call   0x45726
   14d64:	e8 1e 44 00 00       	call   0x19187
   14d69:	66 83 f9 fe          	cmp    cx,0xfffe
   14d6d:	74 02                	je     0x14d71
   14d6f:	66 49                	dec    cx
   14d71:	80 3d cc 10 00 00 00 	cmp    BYTE PTR ds:0x10cc,0x0
   14d78:	74 b7                	je     0x14d31
   14d7a:	c6 05 cc 10 00 00 00 	mov    BYTE PTR ds:0x10cc,0x0
   14d81:	66 83 3d 64 9b 01 00 	cmp    WORD PTR ds:0x19b64,0xffff
   14d88:	ff 
   14d89:	74 1c                	je     0x14da7
   14d8b:	e8 d7 09 03 00       	call   0x45767
   14d90:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0x4
   14d97:	04 
   14d98:	75 0d                	jne    0x14da7
   14d9a:	b8 1e 00 00 00       	mov    eax,0x1e
   14d9f:	33 d2                	xor    edx,edx
   14da1:	42                   	inc    edx
   14da2:	e8 fc 38 00 00       	call   0x186a3
   14da7:	8b 35 9e 15 00 00    	mov    esi,DWORD PTR ds:0x159e
   14dad:	e8 19 b8 ff ff       	call   0x105cb
   14db2:	c6 05 85 10 00 00 00 	mov    BYTE PTR ds:0x1085,0x0
   14db9:	c6 05 84 10 00 00 00 	mov    BYTE PTR ds:0x1084,0x0
   14dc0:	66 33 c0             	xor    ax,ax
   14dc3:	5e                   	pop    esi
   14dc4:	66 83 3d a1 93 01 00 	cmp    WORD PTR ds:0x193a1,0x0
   14dcb:	00 
   14dcc:	74 0a                	je     0x14dd8
   14dce:	66 ff 0d a1 93 01 00 	dec    WORD PTR ds:0x193a1
   14dd5:	66 33 c0             	xor    ax,ax
   14dd8:	66 a3 90 73 01 00    	mov    ds:0x17390,ax
   14dde:	8a 1d        	mov    bl,BYTE PTR ds:0x1c384

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00013260 <.data+0x3260>:
   13260:	66 83 3d 3e 11 00 00 	cmp    WORD PTR ds:0x113e,0x0
   13267:	00 
   13268:	74 0d                	je     0x13277
   1326a:	80 66 0f 7f          	and    BYTE PTR [esi+0xf],0x7f
   1326e:	66 ff 0d 3e 11 00 00 	dec    WORD PTR ds:0x113e
   13275:	eb 04                	jmp    0x1327b
   13277:	80 4e 0f 80          	or     BYTE PTR [esi+0xf],0x80
   1327b:	e8 73 12 00 00       	call   0x144f3
   13280:	ba 30 27 00 00       	mov    edx,0x2730
   13285:	e8 96 12 00 00       	call   0x14520
   1328a:	e8 2d 52 00 00       	call   0x184bc
   1328f:	80 3d b4 10 00 00 00 	cmp    BYTE PTR ds:0x10b4,0x0
   13296:	74 14                	je     0x132ac
   13298:	e8 c8 53 00 00       	call   0x18665
   1329d:	e8 5c d4 ff ff       	call   0x106fe
   132a2:	ba 69 31 00 00       	mov    edx,0x3169
   132a7:	e9 5b cf ff ff       	jmp    0x10207

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000184bc <.data+0x84bc>:
   184bc:	8a 1d 89 c3 01 00    	mov    bl,BYTE PTR ds:0x1c389
   184c2:	22 1d 84 c3 01 00    	and    bl,BYTE PTR ds:0x1c384
   184c8:	80 f3 ff             	xor    bl,0xff
   184cb:	8a 3d 9a 73 01 00    	mov    bh,BYTE PTR ds:0x1739a
   184d1:	22 3d 9b 73 01 00    	and    bh,BYTE PTR ds:0x1739b
   184d7:	80 f7 ff             	xor    bh,0xff
   184da:	66 33 c0             	xor    ax,ax
   184dd:	be 0a 2b 00 00       	mov    esi,0x2b0a
   184e2:	33 d2                	xor    edx,edx
   184e4:	8a 16                	mov    dl,BYTE PTR [esi]
   184e6:	46                   	inc    esi
   184e7:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   184ee:	76 02                	jbe    0x184f2
   184f0:	0c 01                	or     al,0x1
   184f2:	8a 16                	mov    dl,BYTE PTR [esi]
   184f4:	46                   	inc    esi
   184f5:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   184fc:	76 02                	jbe    0x18500
   184fe:	0c 02                	or     al,0x2
   18500:	8a 16                	mov    dl,BYTE PTR [esi]
   18502:	46                   	inc    esi
   18503:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   1850a:	76 02                	jbe    0x1850e
   1850c:	0c 04                	or     al,0x4
   1850e:	8a 16                	mov    dl,BYTE PTR [esi]
   18510:	46                   	inc    esi
   18511:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   18518:	76 02                	jbe    0x1851c
   1851a:	0c 08                	or     al,0x8
   1851c:	8a 16                	mov    dl,BYTE PTR [esi]
   1851e:	46                   	inc    esi
   1851f:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   18526:	76 02                	jbe    0x1852a
   18528:	0c 20                	or     al,0x20
   1852a:	8a 16                	mov    dl,BYTE PTR [esi]
   1852c:	46                   	inc    esi
   1852d:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   18534:	76 02                	jbe    0x18538
   18536:	0c 10                	or     al,0x10
   18538:	8a 16                	mov    dl,BYTE PTR [esi]
   1853a:	46                   	inc    esi
   1853b:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   18542:	76 02                	jbe    0x18546
   18544:	0c 40                	or     al,0x40
   18546:	8a 16                	mov    dl,BYTE PTR [esi]
   18548:	46                   	inc    esi
   18549:	80 ba b3 10 00 00 05 	cmp    BYTE PTR [edx+0x10b3],0x5
   18550:	76 03                	jbe    0x18555
   18552:	80 cc 01             	or     ah,0x1
   18555:	80 3d 96 73 01 00 00 	cmp    BYTE PTR ds:0x17396,0x0
   1855c:	0f 84 8a 00 00 00    	je     0x185ec
   18562:	66 53                	push   bx
   18564:	66 50                	push   ax
   18566:	e8 3c b1 ff ff       	call   0x136a7
   1856b:	66 33 db             	xor    bx,bx
   1856e:	66 a1 ec 4d 00 00    	mov    ax,ds:0x4dec
   18574:	66 8b 0d f5 4d 00 00 	mov    cx,WORD PTR ds:0x4df5
   1857b:	66 d1 e9             	shr    cx,1
   1857e:	66 3b c1             	cmp    ax,cx
   18581:	7e 03                	jle    0x18586
   18583:	80 cb 08             	or     bl,0x8
   18586:	66 f7 d9             	neg    cx
   18589:	66 3b c1             	cmp    ax,cx
   1858c:	7d 03                	jge    0x18591
   1858e:	80 cb 04             	or     bl,0x4
   18591:	66 a1 ee 4d 00 00    	mov    ax,ds:0x4dee
   18597:	66 8b 0d f7 4d 00 00 	mov    cx,WORD PTR ds:0x4df7
   1859e:	66 d1 e9             	shr    cx,1
   185a1:	66 3b c1             	cmp    ax,cx
   185a4:	7e 03                	jle    0x185a9
   185a6:	80 cb 02             	or     bl,0x2
   185a9:	66 f7 d9             	neg    cx
   185ac:	66 3b c1             	cmp    ax,cx
   185af:	7d 03                	jge    0x185b4
   185b1:	80 cb 01             	or     bl,0x1
   185b4:	a0 f0 4d 00 00       	mov    al,ds:0x4df0
   185b9:	84 05 12 2b 00 00    	test   BYTE PTR ds:0x2b12,al
   185bf:	74 03                	je     0x185c4
   185c1:	80 cb 20             	or     bl,0x20
   185c4:	84 05 13 2b 00 00    	test   BYTE PTR ds:0x2b13,al
   185ca:	74 03                	je     0x185cf
   185cc:	80 cb 10             	or     bl,0x10
   185cf:	84 05 14 2b 00 00    	test   BYTE PTR ds:0x2b14,al
   185d5:	74 03                	je     0x185da
   185d7:	80 cb 40             	or     bl,0x40
   185da:	84 05 15 2b 00 00    	test   BYTE PTR ds:0x2b15,al
   185e0:	74 03                	je     0x185e5
   185e2:	80 cf 01             	or     bh,0x1
   185e5:	66 58                	pop    ax
   185e7:	66 0b c3             	or     ax,bx
   185ea:	66 5b                	pop    bx
   185ec:	56                   	push   esi
   185ed:	80 3d f0 73 01 00 00 	cmp    BYTE PTR ds:0x173f0,0x0
   185f4:	74 22                	je     0x18618
   185f6:	a8 80                	test   al,0x80
   185f8:	74 04                	je     0x185fe
   185fa:	b0 ff                	mov    al,0xff
   185fc:	eb 1a                	jmp    0x18618
   185fe:	8b 35 c0 73 01 00    	mov    esi,DWORD PTR ds:0x173c0
   18604:	8a 06                	mov    al,BYTE PTR [esi]
   18606:	fe 4e 01             	dec    BYTE PTR [esi+0x1]
   18609:	80 7e 01 ff          	cmp    BYTE PTR [esi+0x1],0xff
   1860d:	75 09                	jne    0x18618
   1860f:	83 c6 02             	add    esi,0x2
   18612:	89 35 c0 73 01 00    	mov    DWORD PTR ds:0x173c0,esi
   18618:	5e                   	pop    esi
   18619:	88 25 9a 73 01 00    	mov    BYTE PTR ds:0x1739a,ah
   1861f:	22 e7                	and    ah,bh
   18621:	88 25 99 73 01 00    	mov    BYTE PTR ds:0x17399,ah
   18627:	a2 89 c3 01 00       	mov    ds:0x1c389,al
   1862c:	22 c3                	and    al,bl
   1862e:	a2 88 c3 01 00       	mov    ds:0x1c388,al
   18633:	c1 e0 10             	shl    eax,0x10
   18636:	a0 88 c3 01 00       	mov    al,ds:0x1c388
   1863b:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018762 <.data+0x8762>:
   18762:	60                   	pusha  
   18763:	8b 2d 7c ca 01 00    	mov    ebp,DWORD PTR ds:0x1ca7c
   18769:	c7 05 db 54 00 00 01 	mov    DWORD PTR ds:0x54db,0x1
   18770:	00 00 00 
   18773:	0b ed                	or     ebp,ebp
   18775:	0f 84 26 01 00 00    	je     0x188a1
   1877b:	8a 45 0e             	mov    al,BYTE PTR [ebp+0xe]
   1877e:	24 80                	and    al,0x80
   18780:	3a 05 a4 9a 01 00    	cmp    al,BYTE PTR ds:0x19aa4
   18786:	0f 85 0d 01 00 00    	jne    0x18899
   1878c:	8a 45 0f             	mov    al,BYTE PTR [ebp+0xf]
   1878f:	24 80                	and    al,0x80
   18791:	0f 85 02 01 00 00    	jne    0x18899
   18797:	8a 45 0f             	mov    al,BYTE PTR [ebp+0xf]
   1879a:	24 20                	and    al,0x20
   1879c:	74 49                	je     0x187e7
   1879e:	8a 45 0f             	mov    al,BYTE PTR [ebp+0xf]
   187a1:	24 10                	and    al,0x10
   187a3:	75 24                	jne    0x187c9
   187a5:	80 7d 0c 00          	cmp    BYTE PTR [ebp+0xc],0x0
   187a9:	74 05                	je     0x187b0
   187ab:	fe 4d 0c             	dec    BYTE PTR [ebp+0xc]
   187ae:	eb 37                	jmp    0x187e7
   187b0:	8a 45 0d             	mov    al,BYTE PTR [ebp+0xd]
   187b3:	88 45 0c             	mov    BYTE PTR [ebp+0xc],al
   187b6:	f6 45 0f 08          	test   BYTE PTR [ebp+0xf],0x8
   187ba:	0f 84 d9 00 00 00    	je     0x18899
   187c0:	80 4d 0f 04          	or     BYTE PTR [ebp+0xf],0x4
   187c4:	e9 d0 00 00 00       	jmp    0x18899
   187c9:	80 7d 0c 00          	cmp    BYTE PTR [ebp+0xc],0x0
   187cd:	74 08                	je     0x187d7
   187cf:	fe 4d 0c             	dec    BYTE PTR [ebp+0xc]
   187d2:	e9 c2 00 00 00       	jmp    0x18899
   187d7:	8a 45 0d             	mov    al,BYTE PTR [ebp+0xd]
   187da:	88 45 0c             	mov    BYTE PTR [ebp+0xc],al
   187dd:	f6 45 0f 08          	test   BYTE PTR [ebp+0xf],0x8
   187e1:	74 04                	je     0x187e7
   187e3:	80 65 0f ef          	and    BYTE PTR [ebp+0xf],0xef
   187e7:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
   187ea:	66 8b 0e             	mov    cx,WORD PTR [esi]
   187ed:	83 c6 02             	add    esi,0x2
   187f0:	66 8b 16             	mov    dx,WORD PTR [esi]
   187f3:	f6 45 0f 40          	test   BYTE PTR [ebp+0xf],0x40
   187f7:	75 02                	jne    0x187fb
   187f9:	eb 0e                	jmp    0x18809
   187fb:	66 03 0d 70 15 00 00 	add    cx,WORD PTR ds:0x1570
   18802:	66 03 15 72 15 00 00 	add    dx,WORD PTR ds:0x1572
   18809:	8b 75 12             	mov    esi,DWORD PTR [ebp+0x12]
   1880c:	89 35 9e 9a 01 00    	mov    DWORD PTR ds:0x19a9e,esi
   18812:	66 8b 06             	mov    ax,WORD PTR [esi]
   18815:	66 a3 9c 9a 01 00    	mov    ds:0x19a9c,ax
   1881b:	83 c6 0e             	add    esi,0xe
   1881e:	eb 6f                	jmp    0x1888f
   18820:	66 51                	push   cx
   18822:	66 52                	push   dx
   18824:	55                   	push   ebp
   18825:	56                   	push   esi
   18826:	66 8b c1             	mov    ax,cx
   18829:	66 8b da             	mov    bx,dx
   1882c:	0f b6 4e 05          	movzx  ecx,BYTE PTR [esi+0x5]
   18830:	0f b6 56 04          	movzx  edx,BYTE PTR [esi+0x4]
   18834:	8b f9                	mov    edi,ecx
   18836:	c1 e7 02             	shl    edi,0x2
   18839:	8b bf 4c 11 00 00    	mov    edi,DWORD PTR [edi+0x114c]
   1883f:	c1 e2 03             	shl    edx,0x3
   18842:	83 c2 02             	add    edx,0x2
   18845:	03 fa                	add    edi,edx
   18847:	0f b6 56 04          	movzx  edx,BYTE PTR [esi+0x4]
   1884b:	f6 45 0e 08          	test   BYTE PTR [ebp+0xe],0x8
   1884f:	74 0d                	je     0x1885e
   18851:	66 81 ca 00 80       	or     dx,0x8000
   18856:	66 2b 07             	sub    ax,WORD PTR [edi]
   18859:	66 03 06             	add    ax,WORD PTR [esi]
   1885c:	eb 03                	jmp    0x18861
   1885e:	66 2b 06             	sub    ax,WORD PTR [esi]
   18861:	f6 45 0e 10          	test   BYTE PTR [ebp+0xe],0x10
   18865:	74 0f                	je     0x18876
   18867:	66 81 ca 00 20       	or     dx,0x2000
   1886c:	66 2b 5f 02          	sub    bx,WORD PTR [edi+0x2]
   18870:	66 03 5e 02          	add    bx,WORD PTR [esi+0x2]
   18874:	eb 04                	jmp    0x1887a
   18876:	66 2b 5e 02          	sub    bx,WORD PTR [esi+0x2]
   1887a:	e8 1a 85 ff ff       	call   0x10d99
   1887f:	5e                   	pop    esi
   18880:	5d                   	pop    ebp
   18881:	66 5a                	pop    dx
   18883:	66 59                	pop    cx
   18885:	83 c6 06             	add    esi,0x6
   18888:	66 ff 0d 9c 9a 01 00 	dec    WORD PTR ds:0x19a9c
   1888f:	66 83 3d 9c 9a 01 00 	cmp    WORD PTR ds:0x19a9c,0x0
   18896:	00 
   18897:	75 87                	jne    0x18820
   18899:	8b 6d 04             	mov    ebp,DWORD PTR [ebp+0x4]
   1889c:	e9 d2 fe ff ff       	jmp    0x18773
   188a1:	61                   	popa   
