
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010d10 <.data+0xd10>:
   10d10:	66 3d ff ff          	cmp    ax,0xffff
   10d14:	75 26                	jne    0x10d3c
   10d16:	66 52                	push   dx
   10d18:	66 b9 fa 00          	mov    cx,0xfa
   10d1c:	33 db                	xor    ebx,ebx
   10d1e:	83 bb 4c 11 00 00 00 	cmp    DWORD PTR [ebx+0x114c],0x0
   10d25:	75 05                	jne    0x10d2c
   10d27:	66 33 c9             	xor    cx,cx
   10d2a:	eb 03                	jmp    0x10d2f
   10d2c:	83 c3 04             	add    ebx,0x4
   10d2f:	66 49                	dec    cx
   10d31:	7f eb                	jg     0x10d1e
   10d33:	66 8b c3             	mov    ax,bx
   10d36:	66 c1 e8 02          	shr    ax,0x2
   10d3a:	66 5a                	pop    dx
   10d3c:	66 3d fa 00          	cmp    ax,0xfa
   10d40:	72 0c                	jb     0x10d4e
   10d42:	ba 4c 15 00 00       	mov    edx,0x154c
   10d47:	b0 03                	mov    al,0x3
   10d49:	e9 b9 f4 ff ff       	jmp    0x10207
   10d4e:	66 50                	push   ax
   10d50:	52                   	push   edx
   10d51:	e8 1f 00 00 00       	call   0x10d75
   10d56:	5a                   	pop    edx
   10d57:	66 58                	pop    ax
   10d59:	66 50                	push   ax
   10d5b:	33 f6                	xor    esi,esi
   10d5d:	66 8b f0             	mov    si,ax
   10d60:	c1 e6 02             	shl    esi,0x2
   10d63:	81 c6 4c 11 00 00    	add    esi,0x114c
   10d69:	56                   	push   esi
   10d6a:	e8 79 15 00 00       	call   0x122e8
   10d6f:	5e                   	pop    esi
   10d70:	89 06                	mov    DWORD PTR [esi],eax
   10d72:	66 58                	pop    ax
   10d74:	c3                   	ret    
   10d75:	66 3d fa 00          	cmp    ax,0xfa
   10d79:	73 1d                	jae    0x10d98
   10d7b:	33 f6                	xor    esi,esi
   10d7d:	66 8b f0             	mov    si,ax
   10d80:	c1 e6 02             	shl    esi,0x2
   10d83:	8b 86 4c 11 00 00    	mov    eax,DWORD PTR [esi+0x114c]
   10d89:	c7 86 4c 11 00 00 00 	mov    DWORD PTR [esi+0x114c],0x0
   10d90:	00 00 00 
   10d93:	e8 48 f4 ff ff       	call   0x101e0
   10d98:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00011aae <.data+0x1aae>:
   11aae:	8b 35 90 15 00 00    	mov    esi,DWORD PTR ds:0x1590
   11ab4:	e8 8c 01 00 00       	call   0x11c45
   11ab9:	c3                   	ret    
   11aba:	33 c0                	xor    eax,eax
   11abc:	66 a1 70 15 00 00    	mov    ax,ds:0x1570
   11ac2:	66 25 f8 ff          	and    ax,0xfff8
   11ac6:	a3 da 18 00 00       	mov    ds:0x18da,eax
   11acb:	66 83 3d d6 73 01 00 	cmp    WORD PTR ds:0x173d6,0x0
   11ad2:	00 
   11ad3:	74 1b                	je     0x11af0
   11ad5:	66 a1 d6 73 01 00    	mov    ax,ds:0x173d6
   11adb:	66 05 00 02          	add    ax,0x200
   11adf:	a3 de 18 00 00       	mov    ds:0x18de,eax
   11ae4:	c7 05 e2 18 00 00 80 	mov    DWORD PTR ds:0x18e2,0x80
   11aeb:	00 00 00 
   11aee:	eb 1a                	jmp    0x11b0a
   11af0:	66 a1 8a 15 00 00    	mov    ax,ds:0x158a
   11af6:	66 c1 e0 03          	shl    ax,0x3
   11afa:	a3 de 18 00 00       	mov    ds:0x18de,eax
   11aff:	66 a1 8e 15 00 00    	mov    ax,ds:0x158e
   11b05:	a3 e2 18 00 00       	mov    ds:0x18e2,eax
   11b0a:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00011b0b <.data+0x1b0b>:
   11b0b:	33 c0                	xor    eax,eax
   11b0d:	33 db                	xor    ebx,ebx
   11b0f:	66 8b 1d 72 15 00 00 	mov    bx,WORD PTR ds:0x1572
   11b16:	66 03 1d e2 73 01 00 	add    bx,WORD PTR ds:0x173e2
   11b1d:	66 c1 eb 03          	shr    bx,0x3
   11b21:	66 a1 8e 15 00 00    	mov    ax,ds:0x158e
   11b27:	0f af d8             	imul   ebx,eax
   11b2a:	66 a1 70 15 00 00    	mov    ax,ds:0x1570
   11b30:	66 c1 e8 03          	shr    ax,0x3
   11b34:	66 d1 e0             	shl    ax,1
   11b37:	03 d8                	add    ebx,eax
   11b39:	03 de                	add    ebx,esi
   11b3b:	8b 3d 9c 03 00 00    	mov    edi,DWORD PTR ds:0x39c
   11b41:	66 b9 1a 00          	mov    cx,0x1a
   11b45:	53                   	push   ebx
   11b46:	66 51                	push   cx
   11b48:	57                   	push   edi
   11b49:	e8 6c ff ff ff       	call   0x11aba
   11b4e:	66 b9 27 00          	mov    cx,0x27
   11b52:	33 d2                	xor    edx,edx
   11b54:	66 8b 15 70 15 00 00 	mov    dx,WORD PTR ds:0x1570
   11b5b:	66 83 e2 07          	and    dx,0x7
   11b5f:	75 04                	jne    0x11b65
   11b61:	66 41                	inc    cx
   11b63:	eb 4a                	jmp    0x11baf
   11b65:	66 8b 33             	mov    si,WORD PTR [ebx]
   11b68:	66 8b c6             	mov    ax,si
   11b6b:	81 e6 ff 1f 00 00    	and    esi,0x1fff
   11b71:	66 4e                	dec    si
   11b73:	78 0d                	js     0x11b82
   11b75:	66 25 00 20          	and    ax,0x2000
   11b79:	75 07                	jne    0x11b82
   11b7b:	e8 63 04 00 00       	call   0x11fe3
   11b80:	eb 08                	jmp    0x11b8a
   11b82:	83 c3 02             	add    ebx,0x2
   11b85:	83 c7 08             	add    edi,0x8
   11b88:	2b fa                	sub    edi,edx
   11b8a:	83 05 da 18 00 00 08 	add    DWORD PTR ds:0x18da,0x8
   11b91:	a1 da 18 00 00       	mov    eax,ds:0x18da
   11b96:	3b 05 de 18 00 00    	cmp    eax,DWORD PTR ds:0x18de
   11b9c:	72 11                	jb     0x11baf
   11b9e:	c7 05 da 18 00 00 00 	mov    DWORD PTR ds:0x18da,0x0
   11ba5:	00 00 00 
   11ba8:	a1 e2 18 00 00       	mov    eax,ds:0x18e2
   11bad:	2b d8                	sub    ebx,eax
   11baf:	66 8b 33             	mov    si,WORD PTR [ebx]
   11bb2:	66 8b c6             	mov    ax,si
   11bb5:	81 e6 ff 1f 00 00    	and    esi,0x1fff
   11bbb:	66 4e                	dec    si
   11bbd:	78 11                	js     0x11bd0
   11bbf:	66 25 00 20          	and    ax,0x2000
   11bc3:	75 0b                	jne    0x11bd0
   11bc5:	e8 e4 04 00 00       	call   0x120ae
   11bca:	81 ef 00 0a 00 00    	sub    edi,0xa00
   11bd0:	83 c3 02             	add    ebx,0x2
   11bd3:	83 c7 08             	add    edi,0x8
   11bd6:	83 05 da 18 00 00 08 	add    DWORD PTR ds:0x18da,0x8
   11bdd:	a1 da 18 00 00       	mov    eax,ds:0x18da
   11be2:	3b 05 de 18 00 00    	cmp    eax,DWORD PTR ds:0x18de
   11be8:	72 11                	jb     0x11bfb
   11bea:	c7 05 da 18 00 00 00 	mov    DWORD PTR ds:0x18da,0x0
   11bf1:	00 00 00 
   11bf4:	a1 e2 18 00 00       	mov    eax,ds:0x18e2
   11bf9:	2b d8                	sub    ebx,eax
   11bfb:	66 49                	dec    cx
   11bfd:	75 b0                	jne    0x11baf
   11bff:	33 d2                	xor    edx,edx
   11c01:	66 8b 15 70 15 00 00 	mov    dx,WORD PTR ds:0x1570
   11c08:	66 83 e2 07          	and    dx,0x7
   11c0c:	74 1b                	je     0x11c29
   11c0e:	66 8b 33             	mov    si,WORD PTR [ebx]
   11c11:	66 8b c6             	mov    ax,si
   11c14:	81 e6 ff 1f 00 00    	and    esi,0x1fff
   11c1a:	66 4e                	dec    si
   11c1c:	78 0b                	js     0x11c29
   11c1e:	66 25 00 20          	and    ax,0x2000
   11c22:	75 05                	jne    0x11c29
   11c24:	e8 26 05 00 00       	call   0x1214f
   11c29:	5f                   	pop    edi
   11c2a:	66 59                	pop    cx
   11c2c:	5b                   	pop    ebx
   11c2d:	0f b7 05 8e 15 00 00 	movzx  eax,WORD PTR ds:0x158e
   11c34:	03 d8                	add    ebx,eax
   11c36:	81 c7 00 0a 00 00    	add    edi,0xa00
   11c3c:	66 49                	dec    cx
   11c3e:	0f 85 01 ff ff ff    	jne    0x11b45
   11c44:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00011c45 <.data+0x1c45>:
   11c45:	33 c0                	xor    eax,eax
   11c47:	33 db                	xor    ebx,ebx
   11c49:	66 8b 1d 72 15 00 00 	mov    bx,WORD PTR ds:0x1572
   11c50:	66 03 1d e2 73 01 00 	add    bx,WORD PTR ds:0x173e2
   11c57:	66 c1 eb 03          	shr    bx,0x3
   11c5b:	66 a1 8e 15 00 00    	mov    ax,ds:0x158e
   11c61:	0f af d8             	imul   ebx,eax
   11c64:	66 a1 70 15 00 00    	mov    ax,ds:0x1570
   11c6a:	66 c1 e8 03          	shr    ax,0x3
   11c6e:	66 d1 e0             	shl    ax,1
   11c71:	03 d8                	add    ebx,eax
   11c73:	03 de                	add    ebx,esi
   11c75:	8b 3d 9c 03 00 00    	mov    edi,DWORD PTR ds:0x39c
   11c7b:	66 b9 1a 00          	mov    cx,0x1a
   11c7f:	53                   	push   ebx
   11c80:	66 51                	push   cx
   11c82:	57                   	push   edi
   11c83:	e8 32 fe ff ff       	call   0x11aba
   11c88:	66 b9 27 00          	mov    cx,0x27
   11c8c:	33 d2                	xor    edx,edx
   11c8e:	66 8b 15 70 15 00 00 	mov    dx,WORD PTR ds:0x1570
   11c95:	66 83 e2 07          	and    dx,0x7
   11c99:	75 04                	jne    0x11c9f
   11c9b:	66 41                	inc    cx
   11c9d:	eb 4a                	jmp    0x11ce9
   11c9f:	66 8b 33             	mov    si,WORD PTR [ebx]
   11ca2:	66 8b c6             	mov    ax,si
   11ca5:	81 e6 ff 1f 00 00    	and    esi,0x1fff
   11cab:	66 4e                	dec    si
   11cad:	78 0d                	js     0x11cbc
   11caf:	66 25 00 20          	and    ax,0x2000
   11cb3:	74 07                	je     0x11cbc
   11cb5:	e8 29 03 00 00       	call   0x11fe3
   11cba:	eb 08                	jmp    0x11cc4
   11cbc:	83 c3 02             	add    ebx,0x2
   11cbf:	83 c7 08             	add    edi,0x8
   11cc2:	2b fa                	sub    edi,edx
   11cc4:	83 05 da 18 00 00 08 	add    DWORD PTR ds:0x18da,0x8
   11ccb:	a1 da 18 00 00       	mov    eax,ds:0x18da
   11cd0:	3b 05 de 18 00 00    	cmp    eax,DWORD PTR ds:0x18de
   11cd6:	72 11                	jb     0x11ce9
   11cd8:	c7 05 da 18 00 00 00 	mov    DWORD PTR ds:0x18da,0x0
   11cdf:	00 00 00 
   11ce2:	a1 e2 18 00 00       	mov    eax,ds:0x18e2
   11ce7:	2b d8                	sub    ebx,eax
   11ce9:	66 8b 33             	mov    si,WORD PTR [ebx]
   11cec:	66 8b c6             	mov    ax,si
   11cef:	81 e6 ff 1f 00 00    	and    esi,0x1fff
   11cf5:	66 4e                	dec    si
   11cf7:	78 11                	js     0x11d0a
   11cf9:	66 25 00 20          	and    ax,0x2000
   11cfd:	74 0b                	je     0x11d0a
   11cff:	e8 aa 03 00 00       	call   0x120ae
   11d04:	81 ef 00 0a 00 00    	sub    edi,0xa00
   11d0a:	83 c3 02             	add    ebx,0x2
   11d0d:	83 c7 08             	add    edi,0x8
   11d10:	83 05 da 18 00 00 08 	add    DWORD PTR ds:0x18da,0x8
   11d17:	a1 da 18 00 00       	mov    eax,ds:0x18da
   11d1c:	3b 05 de 18 00 00    	cmp    eax,DWORD PTR ds:0x18de
   11d22:	72 11                	jb     0x11d35
   11d24:	c7 05 da 18 00 00 00 	mov    DWORD PTR ds:0x18da,0x0
   11d2b:	00 00 00 
   11d2e:	a1 e2 18 00 00       	mov    eax,ds:0x18e2
   11d33:	2b d8                	sub    ebx,eax
   11d35:	66 49                	dec    cx
   11d37:	75 b0                	jne    0x11ce9
   11d39:	33 d2                	xor    edx,edx
   11d3b:	66 8b 15 70 15 00 00 	mov    dx,WORD PTR ds:0x1570
   11d42:	66 83 e2 07          	and    dx,0x7
   11d46:	74 1b                	je     0x11d63
   11d48:	66 8b 33             	mov    si,WORD PTR [ebx]
   11d4b:	66 8b c6             	mov    ax,si
   11d4e:	81 e6 ff 1f 00 00    	and    esi,0x1fff
   11d54:	66 4e                	dec    si
   11d56:	78 0b                	js     0x11d63
   11d58:	66 25 00 20          	and    ax,0x2000
   11d5c:	74 05                	je     0x11d63
   11d5e:	e8 ec 03 00 00       	call   0x1214f
   11d63:	5f                   	pop    edi
   11d64:	66 59                	pop    cx
   11d66:	5b                   	pop    ebx
   11d67:	0f b7 05 8e 15 00 00 	movzx  eax,WORD PTR ds:0x158e
   11d6e:	03 d8                	add    ebx,eax
   11d70:	81 c7 00 0a 00 00    	add    edi,0xa00
   11d76:	66 49                	dec    cx
   11d78:	0f 85 01 ff ff ff    	jne    0x11c7f
   11d7e:	c3                   	ret    
   11d7f:	c1               	shl    esi,0x6

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018a7f <.data+0x8a7f>:
   18a7f:	53                   	push   ebx
   18a80:	51                   	push   ecx
   18a81:	52                   	push   edx
   18a82:	56                   	push   esi
   18a83:	57                   	push   edi
   18a84:	55                   	push   ebp
   18a85:	89 e5                	mov    ebp,esp
   18a87:	81 ec 90 00 00 00    	sub    esp,0x90
   18a8d:	81 ed 82 00 00 00    	sub    ebp,0x82
   18a93:	ba 33 01 00 00       	mov    edx,0x133
   18a98:	b8 35 01 00 00       	mov    eax,0x135
   18a9d:	e8 3d d6 02 00       	call   0x460df
   18aa2:	89 c1                	mov    ecx,eax
   18aa4:	85 c0                	test   eax,eax
   18aa6:	0f 84 86 01 00 00    	je     0x18c32
   18aac:	f6 41 0c 10          	test   BYTE PTR [ecx+0xc],0x10
   18ab0:	0f 85 47 01 00 00    	jne    0x18bfd
   18ab6:	ba 64 00 00 00       	mov    edx,0x64
   18abb:	8d 45 f2             	lea    eax,[ebp-0xe]
   18abe:	89 cb                	mov    ebx,ecx
   18ac0:	e8 1c e1 02 00       	call   0x46be1
   18ac5:	30 d2                	xor    dl,dl
   18ac7:	88 55 56             	mov    BYTE PTR [ebp+0x56],dl
   18aca:	8d 45 56             	lea    eax,[ebp+0x56]
   18acd:	50                   	push   eax
   18ace:	68 42 01 00 00       	push   0x142
   18ad3:	8d 45 f2             	lea    eax,[ebp-0xe]
   18ad6:	50                   	push   eax
   18ad7:	e8 bc e1 02 00       	call   0x46c98
   18adc:	83 c4 0c             	add    esp,0xc
   18adf:	ba 45 01 00 00       	mov    edx,0x145
   18ae4:	8d 45 56             	lea    eax,[ebp+0x56]
   18ae7:	e8 d4 e1 02 00       	call   0x46cc0
   18aec:	85 c0                	test   eax,eax
   18aee:	75 1b                	jne    0x18b0b
   18af0:	8d 45 6a             	lea    eax,[ebp+0x6a]
   18af3:	50                   	push   eax
   18af4:	8d 45 56             	lea    eax,[ebp+0x56]
   18af7:	50                   	push   eax
   18af8:	68 4b 01 00 00       	push   0x14b
   18afd:	8d 45 f2             	lea    eax,[ebp-0xe]
   18b00:	50                   	push   eax
   18b01:	e8 92 e1 02 00       	call   0x46c98
   18b06:	83 c4 10             	add    esp,0x10
   18b09:	eb a1                	jmp    0x18aac
   18b0b:	ba 51 01 00 00       	mov    edx,0x151
   18b10:	8d 45 56             	lea    eax,[ebp+0x56]
   18b13:	e8 a8 e1 02 00       	call   0x46cc0
   18b18:	85 c0                	test   eax,eax
   18b1a:	75 10                	jne    0x18b2c
   18b1c:	68 7e 9a 01 00       	push   0x19a7e
   18b21:	8d 45 56             	lea    eax,[ebp+0x56]
   18b24:	50                   	push   eax
   18b25:	68 57 01 00 00       	push   0x157
   18b2a:	eb d1                	jmp    0x18afd
   18b2c:	ba 5d 01 00 00       	mov    edx,0x15d
   18b31:	8d 45 56             	lea    eax,[ebp+0x56]
   18b34:	e8 87 e1 02 00       	call   0x46cc0
   18b39:	85 c0                	test   eax,eax
   18b3b:	75 07                	jne    0x18b44
   18b3d:	68 84 9a 01 00       	push   0x19a84
   18b42:	eb dd                	jmp    0x18b21
   18b44:	31 f6                	xor    esi,esi
   18b46:	e9 a1 00 00 00       	jmp    0x18bec
   18b4b:	89 d3                	mov    ebx,edx
   18b4d:	c1 e3 03             	shl    ebx,0x3
   18b50:	01 d3                	add    ebx,edx
   18b52:	01 db                	add    ebx,ebx
   18b54:	8d 45 56             	lea    eax,[ebp+0x56]
   18b57:	8b 93 b8 9a 01 00    	mov    edx,DWORD PTR [ebx+0x19ab8]
   18b5d:	e8 5e e1 02 00       	call   0x46cc0
   18b62:	85 c0                	test   eax,eax
   18b64:	0f 85 81 00 00 00    	jne    0x18beb
   18b6a:	ba b8 9a 01 00       	mov    edx,0x19ab8
   18b6f:	01 da                	add    edx,ebx
   18b71:	8d 42 0e             	lea    eax,[edx+0xe]
   18b74:	50                   	push   eax
   18b75:	8d 42 0a             	lea    eax,[edx+0xa]
   18b78:	50                   	push   eax
   18b79:	83 c2 06             	add    edx,0x6
   18b7c:	52                   	push   edx
   18b7d:	8d 45 56             	lea    eax,[ebp+0x56]
   18b80:	50                   	push   eax
   18b81:	68 65 01 00 00       	push   0x165
   18b86:	8d 45 f2             	lea    eax,[ebp-0xe]
   18b89:	50                   	push   eax
   18b8a:	e8 09 e1 02 00       	call   0x46c98
   18b8f:	8b 83 be 9a 01 00    	mov    eax,DWORD PTR [ebx+0x19abe]
   18b95:	89 c2                	mov    edx,eax
   18b97:	bf 64 00 00 00       	mov    edi,0x64
   18b9c:	c1 fa 1f             	sar    edx,0x1f
   18b9f:	f7 ff                	idiv   edi
   18ba1:	89 c2                	mov    edx,eax
   18ba3:	bf 0a 00 00 00       	mov    edi,0xa
   18ba8:	c1 fa 1f             	sar    edx,0x1f
   18bab:	f7 ff                	idiv   edi
   18bad:	c1 e2 08             	shl    edx,0x8
   18bb0:	8b 83 be 9a 01 00    	mov    eax,DWORD PTR [ebx+0x19abe]
   18bb6:	89 55 7e             	mov    DWORD PTR [ebp+0x7e],edx
   18bb9:	89 c2                	mov    edx,eax
   18bbb:	c1 fa 1f             	sar    edx,0x1f
   18bbe:	f7 ff                	idiv   edi
   18bc0:	89 c2                	mov    edx,eax
   18bc2:	c1 fa 1f             	sar    edx,0x1f
   18bc5:	f7 ff                	idiv   edi
   18bc7:	8b 45 7e             	mov    eax,DWORD PTR [ebp+0x7e]
   18bca:	c1 e2 04             	shl    edx,0x4
   18bcd:	01 d0                	add    eax,edx
   18bcf:	89 45 7e             	mov    DWORD PTR [ebp+0x7e],eax
   18bd2:	8b 83 be 9a 01 00    	mov    eax,DWORD PTR [ebx+0x19abe]
   18bd8:	89 c2                	mov    edx,eax
   18bda:	c1 fa 1f             	sar    edx,0x1f
   18bdd:	f7 ff                	idiv   edi
   18bdf:	03 55 7e             	add    edx,DWORD PTR [ebp+0x7e]
   18be2:	83 c4 18             	add    esp,0x18
   18be5:	89 93 be 9a 01 00    	mov    DWORD PTR [ebx+0x19abe],edx
   18beb:	46                   	inc    esi
   18bec:	0f bf d6             	movsx  edx,si
   18bef:	83 fa 06             	cmp    edx,0x6
   18bf2:	0f 8c 53 ff ff ff    	jl     0x18b4b
   18bf8:	e9 af fe ff ff       	jmp    0x18aac
   18bfd:	89 c8                	mov    eax,ecx
   18bff:	e8 a9 d8 02 00       	call   0x464ad
   18c04:	31 c9                	xor    ecx,ecx
   18c06:	eb 22                	jmp    0x18c2a
   18c08:	89 c3                	mov    ebx,eax
   18c0a:	c1 e3 03             	shl    ebx,0x3
   18c0d:	01 c3                	add    ebx,eax
   18c0f:	8d 45 6a             	lea    eax,[ebp+0x6a]
   18c12:	8b 14 5d b8 9a 01 00 	mov    edx,DWORD PTR [ebx*2+0x19ab8]
   18c19:	e8 a2 e0 02 00       	call   0x46cc0
   18c1e:	85 c0                	test   eax,eax
   18c20:	75 07                	jne    0x18c29
   18c22:	66 89 0d 66 9b 01 00 	mov    WORD PTR ds:0x19b66,cx
   18c29:	41                   	inc    ecx
   18c2a:	0f bf c1             	movsx  eax,cx
   18c2d:	83 f8 06             	cmp    eax,0x6
   18c30:	7c d6                	jl     0x18c08
   18c32:	8d a5 82 00 00 00    	lea    esp,[ebp+0x82]
   18c38:	5d                   	pop    ebp
   18c39:	5f                   	pop    edi
   18c3a:	5e                   	pop    esi
   18c3b:	5a                   	pop    edx
   18c3c:	59                   	pop    ecx
   18c3d:	5b                   	pop    ebx
   18c3e:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018c3f <.data+0x8c3f>:
   18c3f:	53                   	push   ebx
   18c40:	51                   	push   ecx
   18c41:	52                   	push   edx
   18c42:	55                   	push   ebp
   18c43:	89 e5                	mov    ebp,esp
   18c45:	83 ec 50             	sub    esp,0x50
   18c48:	89 c1                	mov    ecx,eax
   18c4a:	bb 36 00 00 00       	mov    ebx,0x36
   18c4f:	31 d2                	xor    edx,edx
   18c51:	e8 1a e1 02 00       	call   0x46d70
   18c56:	8b 15 64 9b 01 00    	mov    edx,DWORD PTR ds:0x19b64
   18c5c:	c1 fa 10             	sar    edx,0x10
   18c5f:	89 d0                	mov    eax,edx
   18c61:	c1 e0 03             	shl    eax,0x3
   18c64:	01 d0                	add    eax,edx
   18c66:	8a 04 45 bc 9a 01 00 	mov    al,BYTE PTR [eax*2+0x19abc]
   18c6d:	88 01                	mov    BYTE PTR [ecx],al
   18c6f:	8b 15 64 9b 01 00    	mov    edx,DWORD PTR ds:0x19b64
   18c75:	c1 fa 10             	sar    edx,0x10
   18c78:	89 d0                	mov    eax,edx
   18c7a:	c1 e0 03             	shl    eax,0x3
   18c7d:	01 d0                	add    eax,edx
   18c7f:	66 8b 04 45 be 9a 01 	mov    ax,WORD PTR [eax*2+0x19abe]
   18c86:	00 
   18c87:	66 89 41 23          	mov    WORD PTR [ecx+0x23],ax
   18c8b:	8a 01                	mov    al,BYTE PTR [ecx]
   18c8d:	3c 05                	cmp    al,0x5
   18c8f:	72 0e                	jb     0x18c9f
   18c91:	3c 06                	cmp    al,0x6
   18c93:	76 10                	jbe    0x18ca5
   18c95:	3c 08                	cmp    al,0x8
   18c97:	72 16                	jb     0x18caf
   18c99:	3c 0a                	cmp    al,0xa
   18c9b:	76 08                	jbe    0x18ca5
   18c9d:	eb 10                	jmp    0x18caf
   18c9f:	3c 02                	cmp    al,0x2
   18ca1:	73 06                	jae    0x18ca9
   18ca3:	eb 0a                	jmp    0x18caf
   18ca5:	c6 41 2d 02          	mov    BYTE PTR [ecx+0x2d],0x2
   18ca9:	c6 41 2b 01          	mov    BYTE PTR [ecx+0x2b],0x1
   18cad:	eb 08                	jmp    0x18cb7
   18caf:	c6 41 2d 01          	mov    BYTE PTR [ecx+0x2d],0x1
   18cb3:	c6 41 2b 00          	mov    BYTE PTR [ecx+0x2b],0x0
   18cb7:	8b 15 64 9b 01 00    	mov    edx,DWORD PTR ds:0x19b64
   18cbd:	c1 fa 10             	sar    edx,0x10
   18cc0:	89 d0                	mov    eax,edx
   18cc2:	c1 e0 03             	shl    eax,0x3
   18cc5:	01 d0                	add    eax,edx
   18cc7:	8a 04 45 c2 9a 01 00 	mov    al,BYTE PTR [eax*2+0x19ac2]
   18cce:	88 41 25             	mov    BYTE PTR [ecx+0x25],al
   18cd1:	8b 15 64 9b 01 00    	mov    edx,DWORD PTR ds:0x19b64
   18cd7:	c1 fa 10             	sar    edx,0x10
   18cda:	89 d0                	mov    eax,edx
   18cdc:	c1 e0 03             	shl    eax,0x3
   18cdf:	01 d0                	add    eax,edx
   18ce1:	8a 04 45 c6 9a 01 00 	mov    al,BYTE PTR [eax*2+0x19ac6]
   18ce8:	88 41 26             	mov    BYTE PTR [ecx+0x26],al
   18ceb:	89 ec                	mov    esp,ebp
   18ced:	5d                   	pop    ebp
   18cee:	5a                   	pop    edx
   18cef:	59                   	pop    ecx
   18cf0:	5b                   	pop    ebx
   18cf1:	c3                   	ret    
   18cf2:	8b c0                	mov    eax,eax
   18cf4:	c9                   	leave  
   18cf5:	8d 00                	lea    eax,[eax]
   18cf7:	00 dc                	add    ah,bl
   18cf9:	8d 00                	lea    eax,[eax]
   18cfb:	00 ef                	add    bh,ch
   18cfd:	8d 00                	lea    eax,[eax]
   18cff:	00 ef                	add    bh,ch
   18d01:	8d 00                	lea    eax,[eax]
   18d03:	00 ef                	add    bh,ch
   18d05:	8d 00                	lea    eax,[eax]
   18d07:	00 02                	add    BYTE PTR [edx],al
   18d09:	8e 00                	mov    es,WORD PTR [eax]
   18d0b:	00 25 8e 00 00 25    	add    BYTE PTR ds:0x2500008e,ah
   18d11:	8e 00                	mov    es,WORD PTR [eax]
   18d13:	00 14 8e             	add    BYTE PTR [esi+ecx*4],dl
	...

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018d18 <.data+0x8d18>:
   18d18:	53                   	push   ebx
   18d19:	51                   	push   ecx
   18d1a:	52                   	push   edx
   18d1b:	56                   	push   esi
   18d1c:	57                   	push   edi
   18d1d:	55                   	push   ebp
   18d1e:	89 e5                	mov    ebp,esp
   18d20:	83 ec 54             	sub    esp,0x54
   18d23:	a1 64 9b 01 00       	mov    eax,ds:0x19b64
   18d28:	c1 f8 10             	sar    eax,0x10
   18d2b:	83 f8 ff             	cmp    eax,0xffffffff
   18d2e:	0f 84 f4 01 00 00    	je     0x18f28
   18d34:	b8 e2 fa 01 00       	mov    eax,0x1fae2
   18d39:	e8 01 ff ff ff       	call   0x18c3f
   18d3e:	b8 60 8a 00 00       	mov    eax,0x8a60
   18d43:	e8 77 e0 02 00       	call   0x46dbf
   18d48:	31 c0                	xor    eax,eax
   18d4a:	a0 e2 fa 01 00       	mov    al,ds:0x1fae2
   18d4f:	83 f8 0a             	cmp    eax,0xa
   18d52:	75 3b                	jne    0x18d8f
   18d54:	30 e4                	xor    ah,ah
   18d56:	68 e2 fa 01 00       	push   0x1fae2
   18d5b:	88 25 12 fb 01 00    	mov    BYTE PTR ds:0x1fb12,ah
   18d61:	88 25 13 fb 01 00    	mov    BYTE PTR ds:0x1fb13,ah
   18d67:	e8 c1 4e 02 00       	call   0x3dc2d
   18d6c:	83 c4 04             	add    esp,0x4
   18d6f:	85 c0                	test   eax,eax
   18d71:	0f 85 b1 01 00 00    	jne    0x18f28
   18d77:	e8 a4 cf 01 00       	call   0x35d20
   18d7c:	e8 8f 44 02 00       	call   0x3d210
   18d81:	6a 1f                	push   0x1f
   18d83:	6a 00                	push   0x0
   18d85:	68 53 ae 01 00       	push   0x1ae53
   18d8a:	e9 77 01 00 00       	jmp    0x18f06
   18d8f:	bb 12 00 00 00       	mov    ebx,0x12
   18d94:	b8 d0 fa 01 00       	mov    eax,0x1fad0
   18d99:	31 d2                	xor    edx,edx
   18d9b:	e8 d0 df 02 00       	call   0x46d70
   18da0:	c7 45 fc 08 52 00 00 	mov    DWORD PTR [ebp-0x4],0x5208
   18da7:	66 c7 05 d2 fa 01 00 	mov    WORD PTR ds:0x1fad2,0x1
   18dae:	01 00 
   18db0:	8a 15 e2 fa 01 00    	mov    dl,BYTE PTR ds:0x1fae2
   18db6:	fe ca                	dec    dl
   18db8:	80 fa 08             	cmp    dl,0x8
   18dbb:	77 68                	ja     0x18e25
   18dbd:	31 c0                	xor    eax,eax
   18dbf:	88 d0                	mov    al,dl
   18dc1:	2e ff 24 85 f4 8c 00 	jmp    DWORD PTR cs:[eax*4+0x8cf4]
   18dc8:	00 
   18dc9:	bb f0 55 00 00       	mov    ebx,0x55f0
   18dce:	be f2 ff 02 00       	mov    esi,0x2fff2
   18dd3:	66 89 1d 0b fb 01 00 	mov    WORD PTR ds:0x1fb0b,bx
   18dda:	eb 49                	jmp    0x18e25
   18ddc:	b9 f0 55 00 00       	mov    ecx,0x55f0
   18de1:	be 0f 00 03 00       	mov    esi,0x3000f
   18de6:	66 89 0d 0b fb 01 00 	mov    WORD PTR ds:0x1fb0b,cx
   18ded:	eb 36                	jmp    0x18e25
   18def:	bf 44 ac 00 00       	mov    edi,0xac44
   18df4:	be f0 06 03 00       	mov    esi,0x306f0
   18df9:	66 89 3d 0b fb 01 00 	mov    WORD PTR ds:0x1fb0b,di
   18e00:	eb 23                	jmp    0x18e25
   18e02:	b8 44 ac 00 00       	mov    eax,0xac44
   18e07:	be 25 fb 02 00       	mov    esi,0x2fb25
   18e0c:	66 a3 0b fb 01 00    	mov    ds:0x1fb0b,ax
   18e12:	eb 11                	jmp    0x18e25
   18e14:	ba 80 bb 00 00       	mov    edx,0xbb80
   18e19:	be 20 f7 02 00       	mov    esi,0x2f720
   18e1e:	66 89 15 0b fb 01 00 	mov    WORD PTR ds:0x1fb0b,dx
   18e25:	68 e2 fa 01 00       	push   0x1fae2
   18e2a:	56                   	push   esi
   18e2b:	e8 5d a6 02 00       	call   0x4348d
   18e30:	31 db                	xor    ebx,ebx
   18e32:	66 89 1d e0 fa 01 00 	mov    WORD PTR ds:0x1fae0,bx
   18e39:	31 db                	xor    ebx,ebx
   18e3b:	8a 1d 0f fb 01 00    	mov    bl,BYTE PTR ds:0x1fb0f
   18e41:	69 c3 f0 0a 00 00    	imul   eax,ebx,0xaf0
   18e47:	8a 0d 0d fb 01 00    	mov    cl,BYTE PTR ds:0x1fb0d
   18e4d:	8b 55 fc             	mov    edx,DWORD PTR [ebp-0x4]
   18e50:	d3 e0                	shl    eax,cl
   18e52:	0f af d0             	imul   edx,eax
   18e55:	b9 f0 55 00 00       	mov    ecx,0x55f0
   18e5a:	89 d0                	mov    eax,edx
   18e5c:	c1 fa 1f             	sar    edx,0x1f
   18e5f:	f7 f9                	idiv   ecx
   18e61:	be 20 40 00 00       	mov    esi,0x4020
   18e66:	83 c4 08             	add    esp,0x8
   18e69:	89 c7                	mov    edi,eax
   18e6b:	66 a1 d2 fa 01 00    	mov    ax,ds:0x1fad2
   18e71:	31 c9                	xor    ecx,ecx
   18e73:	30 e4                	xor    ah,ah
   18e75:	66 89 0d e0 fa 01 00 	mov    WORD PTR ds:0x1fae0,cx
   18e7c:	24 01                	and    al,0x1
   18e7e:	25 ff ff 00 00       	and    eax,0xffff
   18e83:	74 11                	je     0x18e96
   18e85:	83 fb 01             	cmp    ebx,0x1
   18e88:	75 07                	jne    0x18e91
   18e8a:	be 20 70 00 00       	mov    esi,0x7020
   18e8f:	eb 05                	jmp    0x18e96
   18e91:	be 20 a1 00 00       	mov    esi,0xa120
   18e96:	8d 04 37             	lea    eax,[edi+esi*1]
   18e99:	3d dc ff 00 00       	cmp    eax,0xffdc
   18e9e:	7e 07                	jle    0x18ea7
   18ea0:	bf dc ff 00 00       	mov    edi,0xffdc
   18ea5:	29 f7                	sub    edi,esi
   18ea7:	01 fe                	add    esi,edi
   18ea9:	8d 46 10             	lea    eax,[esi+0x10]
   18eac:	50                   	push   eax
   18ead:	e8 ae cc 01 00       	call   0x35b60
   18eb2:	83 c4 04             	add    esp,0x4
   18eb5:	25 ff ff 00 00       	and    eax,0xffff
   18eba:	56                   	push   esi
   18ebb:	c1 e0 04             	shl    eax,0x4
   18ebe:	50                   	push   eax
   18ebf:	a3 da fa 01 00       	mov    ds:0x1fada,eax
   18ec4:	a3 d6 fa 01 00       	mov    ds:0x1fad6,eax
   18ec9:	e8 cd cc 01 00       	call   0x35b9b
   18ece:	83 c4 08             	add    esp,0x8
   18ed1:	66 a3 d4 fa 01 00    	mov    ds:0x1fad4,ax
   18ed7:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
   18eda:	68 d0 fa 01 00       	push   0x1fad0
   18edf:	66 89 3d de fa 01 00 	mov    WORD PTR ds:0x1fade,di
   18ee6:	66 a3 d0 fa 01 00    	mov    ds:0x1fad0,ax
   18eec:	e8 17 a6 02 00       	call   0x43508
   18ef1:	83 c4 04             	add    esp,0x4
   18ef4:	85 c0                	test   eax,eax
   18ef6:	75 30                	jne    0x18f28
   18ef8:	e8 13 43 02 00       	call   0x3d210
   18efd:	6a 1f                	push   0x1f
   18eff:	6a 00                	push   0x0
   18f01:	68 72 b0 01 00       	push   0x1b072
   18f06:	e8 35 43 02 00       	call   0x3d240
   18f0b:	83 c4 0c             	add    esp,0xc
   18f0e:	6a 00                	push   0x0
   18f10:	e8 77 c4 02 00       	call   0x4538c
   18f15:	83 c4 04             	add    esp,0x4
   18f18:	85 c0                	test   eax,eax
   18f1a:	75 0c                	jne    0x18f28
   18f1c:	66 a1 66 9b 01 00    	mov    ax,ds:0x19b66
   18f22:	66 a3 64 9b 01 00    	mov    ds:0x19b64,ax
   18f28:	89 ec                	mov    esp,ebp
   18f2a:	5d                   	pop    ebp
   18f2b:	5f                   	pop    edi
   18f2c:	5e                   	pop    esi
   18f2d:	5a                   	pop    edx
   18f2e:	59                   	pop    ecx
   18f2f:	5b                   	pop    ebx
   18f30:	c3                   	ret    
