
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010010 <.data+0x10>:
   10010:	52                   	push   edx
   10011:	55                   	push   ebp
   10012:	89 e5                	mov    ebp,esp
   10014:	e8 6b 00 00 00       	call   0x10084
   10019:	e8 52 00 00 00       	call   0x10070
   1001e:	e8 1d 07 00 00       	call   0x10740
   10023:	e8 48 0b 00 00       	call   0x10b70
   10028:	b8 04 00 00 00       	mov    eax,0x4
   1002d:	e8 de 21 00 00       	call   0x12210
   10032:	e8 48 8a 00 00       	call   0x18a7f
   10037:	e8 dc 8c 00 00       	call   0x18d18
   1003c:	b4 ff                	mov    ah,0xff
   1003e:	31 d2                	xor    edx,edx
   10040:	88 25 96 73 01 00    	mov    BYTE PTR ds:0x17396,ah
   10046:	e8 2c 36 00 00       	call   0x13677
   1004b:	e8 fc 85 00 00       	call   0x1864c
   10050:	e8 5b 46 00 00       	call   0x146b0
   10055:	b8 11 00 00 00       	mov    eax,0x11
   1005a:	e8 91 01 00 00       	call   0x101f0
   1005f:	5d                   	pop    ebp
   10060:	5a                   	pop    edx
   10061:	c3                   	ret    
	...
   1006e:	00 00                	add    BYTE PTR [eax],al
   10070:	50                   	push   eax
   10071:	53                   	push   ebx
   10072:	51                   	push   ecx
   10073:	52                   	push   edx
   10074:	55                   	push   ebp
   10075:	56                   	push   esi
   10076:	57                   	push   edi
   10077:	e8 30 00 00 00       	call   0x100ac
   1007c:	5f                   	pop    edi
   1007d:	5e                   	pop    esi
   1007e:	5d                   	pop    ebp
   1007f:	5a                   	pop    edx
   10080:	59                   	pop    ecx
   10081:	5b                   	pop    ebx
   10082:	58                   	pop    eax
   10083:	c3                   	ret    
   10084:	50                   	push   eax
   10085:	53                   	push   ebx
   10086:	51                   	push   ecx
   10087:	52                   	push   edx
   10088:	55                   	push   ebp
   10089:	56                   	push   esi
   1008a:	57                   	push   edi
   1008b:	e8 42 00 00 00       	call   0x100d2
   10090:	5f                   	pop    edi
   10091:	5e                   	pop    esi
   10092:	5d                   	pop    ebp
   10093:	5a                   	pop    edx
   10094:	59                   	pop    ecx
   10095:	5b                   	pop    ebx
   10096:	58                   	pop    eax
   10097:	c3                   	ret    
   10098:	50                   	push   eax
   10099:	53                   	push   ebx
   1009a:	51                   	push   ecx
   1009b:	52                   	push   edx
   1009c:	55                   	push   ebp
   1009d:	56                   	push   esi
   1009e:	57                   	push   edi
   1009f:	e8 85 00 00 00       	call   0x10129
   100a4:	5f                   	pop    edi
   100a5:	5e                   	pop    esi
   100a6:	5d                   	pop    ebp
   100a7:	5a                   	pop    edx
   100a8:	59                   	pop    ecx
   100a9:	5b                   	pop    ebx
   100aa:	58                   	pop    eax
   100ab:	c3                   	ret    
   100ac:	66 b8 13 00          	mov    ax,0x13
   100b0:	cd 10                	int    0x10
   100b2:	c6 05 a0 03 00 00 01 	mov    BYTE PTR ds:0x3a0,0x1
   100b9:	83 3d 9c 03 00 00 00 	cmp    DWORD PTR ds:0x39c,0x0
   100c0:	75 0f                	jne    0x100d1
   100c2:	bb 00 0e 01 00       	mov    ebx,0x10e00
   100c7:	e8 fc 00 00 00       	call   0x101c8
   100cc:	a3 9c 03 00 00       	mov    ds:0x39c,eax
   100d1:	c3                   	ret    
   100d2:	66 b8 00 00          	mov    ax,0x0
   100d6:	8e d8                	mov    ds,eax
   100d8:	1e                   	push   ds
   100d9:	66 b8 40 00          	mov    ax,0x40
   100dd:	8e d8                	mov    ds,eax
   100df:	66 bb 49 00          	mov    bx,0x49
   100e3:	67 8a 07             	mov    al,BYTE PTR [bx]
   100e6:	67 8a 67 01          	mov    ah,BYTE PTR [bx+0x1]
   100ea:	66 bb 84 00          	mov    bx,0x84
   100ee:	67 8a 17             	mov    dl,BYTE PTR [bx]
   100f1:	66 bb 62 00          	mov    bx,0x62
   100f5:	67 8a 37             	mov    dh,BYTE PTR [bx]
   100f8:	1f                   	pop    ds
   100f9:	a2 a1 03 00 00       	mov    ds:0x3a1,al
   100fe:	88 25 a2 03 00 00    	mov    BYTE PTR ds:0x3a2,ah
   10104:	88 15 a3 03 00 00    	mov    BYTE PTR ds:0x3a3,dl
   1010a:	88 35 a4 03 00 00    	mov    BYTE PTR ds:0x3a4,dh
   10110:	66 b8 00 03          	mov    ax,0x300
   10114:	8a 3d a4 03 00 00    	mov    bh,BYTE PTR ds:0x3a4
   1011a:	cd 10                	int    0x10
   1011c:	88 35 a5 03 00 00    	mov    BYTE PTR ds:0x3a5,dh
   10122:	88 15 a6 03 00 00    	mov    BYTE PTR ds:0x3a6,dl
   10128:	c3                   	ret    

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

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0001224a <.data+0x224a>:
   1224a:	8b c2                	mov    eax,edx
   1224c:	ba 00 02 00 00       	mov    edx,0x200
   12251:	52                   	push   edx
   12252:	50                   	push   eax
   12253:	e8 97 43 03 00       	call   0x465ef
   12258:	83 c4 08             	add    esp,0x8
   1225b:	83 f8 ff             	cmp    eax,0xffffffff
   1225e:	75 0c                	jne    0x1226c
   12260:	ba 09 1a 00 00       	mov    edx,0x1a09
   12265:	b0 03                	mov    al,0x3
   12267:	e9 9b df ff ff       	jmp    0x10207
   1226c:	a3 bc 19 00 00       	mov    ds:0x19bc,eax
   12271:	ba c8 19 00 00       	mov    edx,0x19c8
   12276:	bb 0b 00 00 00       	mov    ebx,0xb
   1227b:	53                   	push   ebx
   1227c:	52                   	push   edx
   1227d:	50                   	push   eax
   1227e:	e8 fb 45 03 00       	call   0x4687e
   12283:	83 c4 0c             	add    esp,0xc
   12286:	a1 bc 19 00 00       	mov    eax,ds:0x19bc
   1228b:	8b 15 cc 19 00 00    	mov    edx,DWORD PTR ds:0x19cc
   12291:	0f b6 1d f2 03 00 00 	movzx  ebx,BYTE PTR ds:0x3f2
   12298:	53                   	push   ebx
   12299:	52                   	push   edx
   1229a:	50                   	push   eax
   1229b:	e8 9d 45 03 00       	call   0x4683d
   122a0:	83 c4 0c             	add    esp,0xc
   122a3:	33 c9                	xor    ecx,ecx
   122a5:	66 8b 0d d1 19 00 00 	mov    cx,WORD PTR ds:0x19d1
   122ac:	66 41                	inc    cx
   122ae:	6b d9 16             	imul   ebx,ecx,0x16
   122b1:	53                   	push   ebx
   122b2:	e8 11 df ff ff       	call   0x101c8
   122b7:	a3 c0 19 00 00       	mov    ds:0x19c0,eax
   122bc:	8b d0                	mov    edx,eax
   122be:	a1 bc 19 00 00       	mov    eax,ds:0x19bc
   122c3:	5b                   	pop    ebx
   122c4:	53                   	push   ebx
   122c5:	52                   	push   edx
   122c6:	50                   	push   eax
   122c7:	e8 b2 45 03 00       	call   0x4687e
   122cc:	83 c4 0c             	add    esp,0xc
   122cf:	c3                   	ret    

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

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00013677 <.data+0x3677>:
   13677:	66 c7 05 f5 4d 00 00 	mov    WORD PTR ds:0x4df5,0x0
   1367e:	00 00 
   13680:	66 c7 05 f7 4d 00 00 	mov    WORD PTR ds:0x4df7,0x0
   13687:	00 00 
   13689:	e8 19 00 00 00       	call   0x136a7
   1368e:	66 a1 ec 4d 00 00    	mov    ax,ds:0x4dec
   13694:	66 a3 f5 4d 00 00    	mov    ds:0x4df5,ax
   1369a:	66 a1 ee 4d 00 00    	mov    ax,ds:0x4dee
   136a0:	66 a3 f7 4d 00 00    	mov    ds:0x4df7,ax
   136a6:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000101f0 <.data+0x1f0>:
   101f0:	92                   	xchg   edx,eax
   101f1:	eb 14                	jmp    0x10207
   101f3:	50                   	push   eax
   101f4:	53                   	push   ebx
   101f5:	51                   	push   ecx
   101f6:	52                   	push   edx
   101f7:	55                   	push   ebp
   101f8:	56                   	push   esi
   101f9:	57                   	push   edi
   101fa:	e8 35 00 00 00       	call   0x10234
   101ff:	5f                   	pop    edi
   10200:	5e                   	pop    esi
   10201:	5d                   	pop    ebp
   10202:	5a                   	pop    edx
   10203:	59                   	pop    ecx
   10204:	5b                   	pop    ebx
   10205:	58                   	pop    eax
   10206:	c3                   	ret    
   10207:	66 50                	push   ax
   10209:	52                   	push   edx
   1020a:	e8 c1 05 00 00       	call   0x107d0
   1020f:	e8 c9 09 00 00       	call   0x10bdd
   10214:	e8 10 ff ff ff       	call   0x10129
   10219:	58                   	pop    eax
   1021a:	e8 cd 5c 03 00       	call   0x45eec
   1021f:	a1 dc 03 00 00       	mov    eax,ds:0x3dc
   10224:	0b c0                	or     eax,eax
   10226:	74 05                	je     0x1022d
   10228:	e8 bf 5c 03 00       	call   0x45eec
   1022d:	66 58                	pop    ax
   1022f:	e9 e6 5c 03 00       	jmp    0x45f1a

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000144f3 <.data+0x44f3>:
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
   1454e:	83 3d 9c 73 01 00 00 	cmp    DWORD PTR ds:0x1739c,0x0
   14555:	74 12                	je     0x14569
   14557:	8b 35 9c 73 01 00    	mov    esi,DWORD PTR ds:0x1739c
   1455d:	ff d6                	call   esi
   1455f:	c7 05 9c 73 01 00 00 	mov    DWORD PTR ds:0x1739c,0x0
   14566:	00 00 00 
   14569:	66 83 3d 67 93 01 00 	cmp    WORD PTR ds:0x19367,0x0
   14570:	00 
   14571:	74 2e                	je     0x145a1
   14573:	66 c7 05 69 93 01 00 	mov    WORD PTR ds:0x19369,0x0
   1457a:	00 00 
   1457c:	66 c7 05 67 93 01 00 	mov    WORD PTR ds:0x19367,0x0
   14583:	00 00 
   14585:	8b 35 5f 93 01 00    	mov    esi,DWORD PTR ds:0x1935f
   1458b:	66 8b 46 40          	mov    ax,WORD PTR [esi+0x40]
   1458f:	66 8b 1e             	mov    bx,WORD PTR [esi]
   14592:	66 89 1d ac 73 01 00 	mov    WORD PTR ds:0x173ac,bx
   14599:	66 a3 aa 73 01 00    	mov    ds:0x173aa,ax
   1459f:	eb 5c                	jmp    0x145fd
   145a1:	66 83 3d 69 93 01 00 	cmp    WORD PTR ds:0x19369,0x0
   145a8:	00 
   145a9:	74 2e                	je     0x145d9
   145ab:	66 c7 05 69 93 01 00 	mov    WORD PTR ds:0x19369,0x0
   145b2:	00 00 
   145b4:	66 c7 05 67 93 01 00 	mov    WORD PTR ds:0x19367,0x0
   145bb:	00 00 
   145bd:	8b 35 5f 93 01 00    	mov    esi,DWORD PTR ds:0x1935f
   145c3:	66 8b 46 16          	mov    ax,WORD PTR [esi+0x16]
   145c7:	66 8b 1e             	mov    bx,WORD PTR [esi]
   145ca:	66 89 1d ac 73 01 00 	mov    WORD PTR ds:0x173ac,bx
   145d1:	66 a3 aa 73 01 00    	mov    ds:0x173aa,ax
   145d7:	eb 24                	jmp    0x145fd
   145d9:	33 c0                	xor    eax,eax
   145db:	8b 35 5f 93 01 00    	mov    esi,DWORD PTR ds:0x1935f
   145e1:	66 8b 06             	mov    ax,WORD PTR [esi]
   145e4:	83 c6 02             	add    esi,0x2
   145e7:	89 35 5f 93 01 00    	mov    DWORD PTR ds:0x1935f,esi
   145ed:	66 a3 aa 73 01 00    	mov    ds:0x173aa,ax
   145f3:	66 3d ff ff          	cmp    ax,0xffff
   145f7:	0f 84 b3 00 00 00    	je     0x146b0
   145fd:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0x7
   14604:	07 
   14605:	75 09                	jne    0x14610
   14607:	66 c7 05 c8 73 01 00 	mov    WORD PTR ds:0x173c8,0x10
   1460e:	10 00 
   14610:	b8 ff ff ff ff       	mov    eax,0xffffffff
   14615:	e8 9f 49 00 00       	call   0x18fb9
   1461a:	b8 ff ff ff ff       	mov    eax,0xffffffff
   1461f:	33 d2                	xor    edx,edx
   14621:	e8 7d 40 00 00       	call   0x186a3
   14626:	b8 ff ff ff ff       	mov    eax,0xffffffff
   1462b:	33 d2                	xor    edx,edx
   1462d:	42                   	inc    edx
   1462e:	e8 70 40 00 00       	call   0x186a3
   14633:	c6 05 8c 9a 01 00 00 	mov    BYTE PTR ds:0x19a8c,0x0
   1463a:	c7 05 ae 73 01 00 00 	mov    DWORD PTR ds:0x173ae,0x0
   14641:	00 00 00 
   14644:	bf 6d 93 01 00       	mov    edi,0x1936d
   14649:	8b 0d dd 93 01 00    	mov    ecx,DWORD PTR ds:0x193dd
   1464f:	33 c0                	xor    eax,eax
   14651:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   14653:	66 c7 05 65 93 01 00 	mov    WORD PTR ds:0x19365,0x0
   1465a:	00 00 
   1465c:	66 c7 05 ce 73 01 00 	mov    WORD PTR ds:0x173ce,0x64
   14663:	64 00 
   14665:	66 c7 05 ca 73 01 00 	mov    WORD PTR ds:0x173ca,0x0
   1466c:	00 00 
   1466e:	66 c7 05 60 0a 00 00 	mov    WORD PTR ds:0xa60,0x1
   14675:	01 00 
   14677:	66 c7 05 62 0a 00 00 	mov    WORD PTR ds:0xa62,0x0
   1467e:	00 00 
   14680:	e8 79 c0 ff ff       	call   0x106fe
   14685:	e8 2b 3d 00 00       	call   0x183b5
   1468a:	33 c0                	xor    eax,eax
   1468c:	66 a1 aa 73 01 00    	mov    ax,ds:0x173aa
   14692:	48                   	dec    eax
   14693:	d1 e0                	shl    eax,1
   14695:	66 8b 80 81 50 00 00 	mov    ax,WORD PTR [eax+0x5081]
   1469c:	8b c0                	mov    eax,eax
   1469e:	e8 16 49 00 00       	call   0x18fb9
   146a3:	33 c0                	xor    eax,eax
   146a5:	66 a1 aa 73 01 00    	mov    ax,ds:0x173aa
   146ab:	e9 fa 01 00 00       	jmp    0x148aa
   146b0:	66 c7 05 6b 93 01 00 	mov    WORD PTR ds:0x1936b,0x0
   146b7:	00 00 
   146b9:	66 c7 05 b2 73 01 00 	mov    WORD PTR ds:0x173b2,0x1
   146c0:	01 00 
   146c2:	80 3d 7d 9a 01 00 00 	cmp    BYTE PTR ds:0x19a7d,0x0
   146c9:	74 16                	je     0x146e1
   146cb:	79 0b                	jns    0x146d8
   146cd:	66 c7 05 b2 73 01 00 	mov    WORD PTR ds:0x173b2,0x3
   146d4:	03 00 
   146d6:	eb 09                	jmp    0x146e1
   146d8:	66 c7 05 b2 73 01 00 	mov    WORD PTR ds:0x173b2,0x0
   146df:	00 00 
   146e1:	c7 05 ae 73 01 00 00 	mov    DWORD PTR ds:0x173ae,0x0
   146e8:	00 00 00 
   146eb:	e8 19 e1 ff ff       	call   0x12809
   146f0:	e8 cc 41 00 00       	call   0x188c1
   146f5:	e8 bb 3c 00 00       	call   0x183b5
   146fa:	80 3d f1 73 01 00 00 	cmp    BYTE PTR ds:0x173f1,0x0
   14701:	0f 85 a9 00 00 00    	jne    0x147b0
   14707:	b8 ff ff ff ff       	mov    eax,0xffffffff
   1470c:	e8 a8 48 00 00       	call   0x18fb9
   14711:	b8 94 30 01 00       	mov    eax,0x13094
   14716:	e8 4f cd ff ff       	call   0x1146a
   1471b:	b8 a0 00 a0 00       	mov    eax,0xa000a0
   14720:	a3 cb 54 00 00       	mov    ds:0x54cb,eax
   14725:	be 1f 54 00 00       	mov    esi,0x541f
   1472a:	e8 cb 20 00 00       	call   0x167fa
   1472f:	8b 35 84 fa 01 00    	mov    esi,DWORD PTR ds:0x1fa84
   14735:	c7 46 14 35 54 00 00 	mov    DWORD PTR [esi+0x14],0x5435
   1473c:	8b 76 10             	mov    esi,DWORD PTR [esi+0x10]
   1473f:	80 4e 0f 40          	or     BYTE PTR [esi+0xf],0x40
   14743:	66 c7 05 60 0a 00 00 	mov    WORD PTR ds:0xa60,0x1
   1474a:	01 00 
   1474c:	66 c7 05 62 0a 00 00 	mov    WORD PTR ds:0xa62,0x0
   14753:	00 00 
   14755:	8b 35 9e 15 00 00    	mov    esi,DWORD PTR ds:0x159e
   1475b:	e8 6b be ff ff       	call   0x105cb
   14760:	c6 05 85 10 00 00 00 	mov    BYTE PTR ds:0x1085,0x0
   14767:	c6 05 84 10 00 00 00 	mov    BYTE PTR ds:0x1084,0x0
   1476e:	66 c7 05 11 50 00 00 	mov    WORD PTR ds:0x5011,0x82
   14775:	82 00 
   14777:	ba b2 47 00 00       	mov    edx,0x47b2
   1477c:	e8 9f fd ff ff       	call   0x14520
   14781:	8b 3d 9c 03 00 00    	mov    edi,DWORD PTR ds:0x39c
   14787:	b9 80 43 00 00       	mov    ecx,0x4380
   1478c:	33 c0                	xor    eax,eax
   1478e:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   14790:	c6 05 a4 9a 01 00 00 	mov    BYTE PTR ds:0x19aa4,0x0
   14797:	e8 c6 3f 00 00       	call   0x18762
   1479c:	e8 93 ba ff ff       	call   0x10234
   147a1:	66 83 3d 11 50 00 00 	cmp    WORD PTR ds:0x5011,0x0
   147a8:	00 
   147a9:	75 cc                	jne    0x14777
   147ab:	e8 4e bf ff ff       	call   0x106fe
   147b0:	eb 50                	jmp    0x14802
   147b2:	66 83 3d 11 50 00 00 	cmp    WORD PTR ds:0x5011,0x64
   147b9:	64 
   147ba:	7f 34                	jg     0x147f0
   147bc:	66 83 3d 11 50 00 00 	cmp    WORD PTR ds:0x5011,0x50
   147c3:	50 
   147c4:	75 19                	jne    0x147df
   147c6:	b8 45 00 00 00       	mov    eax,0x45
   147cb:	33 d2                	xor    edx,edx
   147cd:	e8 d1 3e 00 00       	call   0x186a3
   147d2:	b8 45 00 00 00       	mov    eax,0x45
   147d7:	33 d2                	xor    edx,edx
   147d9:	42                   	inc    edx
   147da:	e8 c4 3e 00 00       	call   0x186a3
   147df:	8b 35 84 fa 01 00    	mov    esi,DWORD PTR ds:0x1fa84
   147e5:	89 35 94 c3 01 00    	mov    DWORD PTR ds:0x1c394,esi
   147eb:	e8 d0 1a 00 00       	call   0x162c0
   147f0:	66 83 3d 11 50 00 00 	cmp    WORD PTR ds:0x5011,0x0
   147f7:	00 
   147f8:	74 07                	je     0x14801
   147fa:	66 ff 0d 11 50 00 00 	dec    WORD PTR ds:0x5011
   14801:	c3                   	ret    
   14802:	c7 05 5f 93 01 00 19 	mov    DWORD PTR ds:0x1935f,0x5019
   14809:	50 00 00 
   1480c:	bf 6d 93 01 00       	mov    edi,0x1936d
   14811:	8b 0d dd 93 01 00    	mov    ecx,DWORD PTR ds:0x193dd
   14817:	33 c0                	xor    eax,eax
   14819:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   1481b:	e8 95 3b 00 00       	call   0x183b5
   14820:	b8 01 00 00 00       	mov    eax,0x1
   14825:	02 05 8b 9a 01 00    	add    al,BYTE PTR ds:0x19a8b
   1482b:	80 3d f1 73 01 00 00 	cmp    BYTE PTR ds:0x173f1,0x0
   14832:	74 1e                	je     0x14852
   14834:	66 b8 01 00          	mov    ax,0x1
   14838:	80 3d f1 73 01 00 01 	cmp    BYTE PTR ds:0x173f1,0x1
   1483f:	74 11                	je     0x14852
   14841:	66 b8 03 00          	mov    ax,0x3
   14845:	80 3d f1 73 01 00 02 	cmp    BYTE PTR ds:0x173f1,0x2
   1484c:	74 04                	je     0x14852
   1484e:	66 b8 09 00          	mov    ax,0x9
   14852:	50                   	push   eax
   14853:	66 48                	dec    ax
   14855:	66 d1 e0             	shl    ax,1
   14858:	66 8b 80 81 50 00 00 	mov    ax,WORD PTR [eax+0x5081]
   1485f:	8b c0                	mov    eax,eax
   14861:	e8 53 47 00 00       	call   0x18fb9
   14866:	58                   	pop    eax
   14867:	66 c7 05 c8 73 01 00 	mov    WORD PTR ds:0x173c8,0x10
   1486e:	10 00 
   14870:	66 c7 05 ce 73 01 00 	mov    WORD PTR ds:0x173ce,0x14
   14877:	14 00 
   14879:	66 c7 05 d0 73 01 00 	mov    WORD PTR ds:0x173d0,0x4
   14880:	04 00 
   14882:	66 c7 05 c6 73 01 00 	mov    WORD PTR ds:0x173c6,0x3
   14889:	03 00 
   1488b:	80 3d 7d 9a 01 00 00 	cmp    BYTE PTR ds:0x19a7d,0x0
   14892:	74 16                	je     0x148aa
   14894:	79 0b                	jns    0x148a1
   14896:	66 c7 05 c6 73 01 00 	mov    WORD PTR ds:0x173c6,0x9
   1489d:	09 00 
   1489f:	eb 09                	jmp    0x148aa
   148a1:	66 c7 05 c6 73 01 00 	mov    WORD PTR ds:0x173c6,0x1
   148a8:	01 00 
   148aa:	50                   	push   eax
   148ab:	bf 6d 93 01 00       	mov    edi,0x1936d
   148b0:	8b 0d dd 93 01 00    	mov    ecx,DWORD PTR ds:0x193dd
   148b6:	33 c0                	xor    eax,eax
   148b8:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   148ba:	58                   	pop    eax
   148bb:	66 c7 05 65 93 01 00 	mov    WORD PTR ds:0x19365,0x0
   148c2:	00 00 
   148c4:	c7 05 9c 73 01 00 00 	mov    DWORD PTR ds:0x1739c,0x0
   148cb:	00 00 00 
   148ce:	66 3d 04 00          	cmp    ax,0x4
   148d2:	75 10                	jne    0x148e4
   148d4:	66 b8 ff ff          	mov    ax,0xffff
   148d8:	e8 0f ef ff ff       	call   0x137ec
   148dd:	e8 75 59 00 00       	call   0x1a257
   148e2:	eb 51                	jmp    0x14935
   148e4:	e8 87 ee ff ff       	call   0x13770
   148e9:	66 33 c0             	xor    ax,ax
   148ec:	e8 fb ee ff ff       	call   0x137ec
   148f1:	e8 20 ef ff ff       	call   0x13816
   148f6:	e8 a8 fb ff ff       	call   0x144a3
   148fb:	8b 35 f2 73 01 00    	mov    esi,DWORD PTR ds:0x173f2
   14901:	89 35 fa 73 01 00    	mov    DWORD PTR ds:0x173fa,esi
   14907:	e8 cf f0 ff ff       	call   0x139db
   1490c:	8b 35 fa 73 01 00    	mov    esi,DWORD PTR ds:0x173fa
   14912:	66 83 3d aa 73 01 00 	cmp    WORD PTR ds:0x173aa,0xb
   14919:	0b 
   1491a:	7d 14                	jge    0x14930
   1491c:	e8 35 56 00 00       	call   0x19f56
   14921:	e8 ea 53 00 00       	call   0x19d10
   14926:	e8 b5 52 00 00       	call   0x19be0
   1492b:	e8 52 54 00 00       	call   0x19d82
   14930:	e8 56 f0 ff ff       	call   0x1398b
   14935:	e8 69 fb ff ff       	call   0x144a3
   1493a:	66 c7 05 60 0a 00 00 	mov    WORD PTR ds:0xa60,0x1
   14941:	01 00 
   14943:	66 c7 05 62 0a 00 00 	mov    WORD PTR ds:0xa62,0x0
   1494a:	00 00 
   1494c:	8b 35 9e 15 00 00    	mov    esi,DWORD PTR ds:0x159e
   14952:	e8 74 bc ff ff       	call   0x105cb
   14957:	8b 35 f2 73 01 00    	mov    esi,DWORD PTR ds:0x173f2
   1495d:	89 35 fa 73 01 00    	mov    DWORD PTR ds:0x173fa,esi
   14963:	80 3d f1 73 01 00 00 	cmp    BYTE PTR ds:0x173f1,0x0
   1496a:	74 73                	je     0x149df
   1496c:	c7 05 8c c3 01 00 37 	mov    DWORD PTR ds:0x1c38c,0x37
   14973:	00 00 00 
   14976:	c7 05 8d c3 01 00 aa 	mov    DWORD PTR ds:0x1c38d,0xaa
   1497d:	00 00 00 
   14980:	c7 05 8e c3 01 00 0b 	mov    DWORD PTR ds:0x1c38e,0xb
   14987:	00 00 00 
   1498a:	c7 05 8f c3 01 00 4c 	mov    DWORD PTR ds:0x1c38f,0x4c
   14991:	00 00 00 
   14994:	be 33 52 00 00       	mov    esi,0x5233
   14999:	80 3d f1 73 01 00 01 	cmp    BYTE PTR ds:0x173f1,0x1
   149a0:	74 13                	je     0x149b5
   149a2:	be f3 52 00 00       	mov    esi,0x52f3
   149a7:	80 3d f1 73 01 00 02 	cmp    BYTE PTR ds:0x173f1,0x2
   149ae:	74 05                	je     0x149b5
   149b0:	be 63 53 00 00       	mov    esi,0x5363
   149b5:	bf 9f 50 00 00       	mov    edi,0x509f
   149ba:	89 3d c0 73 01 00    	mov    DWORD PTR ds:0x173c0,edi
   149c0:	66 ba 64 00          	mov    dx,0x64
   149c4:	8b 06                	mov    eax,DWORD PTR [esi]
   149c6:	83 c6 04             	add    esi,0x4
   149c9:	89 07                	mov    DWORD PTR [edi],eax
   149cb:	83 c7 04             	add    edi,0x4
   149ce:	66 4a                	dec    dx
   149d0:	79 f2                	jns    0x149c4
   149d2:	fe 0d a0 50 00 00    	dec    BYTE PTR ds:0x50a0
   149d8:	c6 05 f0 73 01 00 01 	mov    BYTE PTR ds:0x173f0,0x1
   149df:	e8 58 3c 00 00       	call   0x1863c
   149e4:	e8 ba fa ff ff       	call   0x144a3
   149e9:	83 3d 03 54 00 00 00 	cmp    DWORD PTR ds:0x5403,0x0
   149f0:	75 08                	jne    0x149fa
   149f2:	89 25 03 54 00 00    	mov    DWORD PTR ds:0x5403,esp
   149f8:	eb 16                	jmp    0x14a10
   149fa:	8b c4                	mov    eax,esp
   149fc:	39 05 03 54 00 00    	cmp    DWORD PTR ds:0x5403,eax
   14a02:	74 0c                	je     0x14a10
   14a04:	ba 07 54 00 00       	mov    edx,0x5407
   14a09:	b0 03                	mov    al,0x3
   14a0b:	e9 f7 b7 ff ff       	jmp    0x10207
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

00014f50 <.data+0x4f50>:
   14f50:	66 ff 05 a0 73 01 00 	inc    WORD PTR ds:0x173a0
   14f57:	e8 60 35 00 00       	call   0x184bc
   14f5c:	a3 8c 73 01 00       	mov    ds:0x1738c,eax
   14f61:	8b 35 84 fa 01 00    	mov    esi,DWORD PTR ds:0x1fa84
   14f67:	0b f6                	or     esi,esi
   14f69:	74 4c                	je     0x14fb7
   14f6b:	8b 6e 08             	mov    ebp,DWORD PTR [esi+0x8]
   14f6e:	0b ed                	or     ebp,ebp
   14f70:	74 3c                	je     0x14fae
   14f72:	8b 7d 00             	mov    edi,DWORD PTR [ebp+0x0]
   14f75:	0b ff                	or     edi,edi
   14f77:	74 35                	je     0x14fae
   14f79:	56                   	push   esi
   14f7a:	89 35 94 c3 01 00    	mov    DWORD PTR ds:0x1c394,esi
   14f80:	ff d7                	call   edi
   14f82:	5e                   	pop    esi
   14f83:	3b 35 c1 93 01 00    	cmp    esi,DWORD PTR ds:0x193c1
   14f89:	75 0a                	jne    0x14f95
   14f8b:	a1 94 c3 01 00       	mov    eax,ds:0x1c394
   14f90:	a3 c1 93 01 00       	mov    ds:0x193c1,eax
   14f95:	83 3d 94 c3 01 00 00 	cmp    DWORD PTR ds:0x1c394,0x0
   14f9c:	75 10                	jne    0x14fae
   14f9e:	8b 56 04             	mov    edx,DWORD PTR [esi+0x4]
   14fa1:	e8 48 34 00 00       	call   0x183ee
   14fa6:	8b f2                	mov    esi,edx
   14fa8:	0b f6                	or     esi,esi
   14faa:	74 0b                	je     0x14fb7
   14fac:	eb 07                	jmp    0x14fb5
   14fae:	8b 76 04             	mov    esi,DWORD PTR [esi+0x4]
   14fb1:	0b f6                	or     esi,esi
   14fb3:	74 02                	je     0x14fb7
   14fb5:	eb b4                	jmp    0x14f6b
   14fb7:	c3                   	ret    
