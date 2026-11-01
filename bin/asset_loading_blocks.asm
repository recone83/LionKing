
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010d99 <.data+0xd99>:
   10d99:	66 2b 05 70 15 00 00 	sub    ax,WORD PTR ds:0x1570
   10da0:	66 2b 1d ce 03 00 00 	sub    bx,WORD PTR ds:0x3ce
   10da7:	66 a3 3c 15 00 00    	mov    ds:0x153c,ax
   10dad:	66 89 1d 3e 15 00 00 	mov    WORD PTR ds:0x153e,bx
   10db4:	66 89 0d 40 15 00 00 	mov    WORD PTR ds:0x1540,cx
   10dbb:	66 89 15 42 15 00 00 	mov    WORD PTR ds:0x1542,dx
   10dc2:	33 f6                	xor    esi,esi
   10dc4:	66 8b f1             	mov    si,cx
   10dc7:	c1 e6 02             	shl    esi,0x2
   10dca:	8b b6 4c 11 00 00    	mov    esi,DWORD PTR [esi+0x114c]
   10dd0:	0b f6                	or     esi,esi
   10dd2:	75 01                	jne    0x10dd5
   10dd4:	c3                   	ret    
   10dd5:	66 81 e2 ff 1f       	and    dx,0x1fff
   10dda:	66 3b 16             	cmp    dx,WORD PTR [esi]
   10ddd:	72 01                	jb     0x10de0
   10ddf:	c3                   	ret    
   10de0:	8b fe                	mov    edi,esi
   10de2:	33 c9                	xor    ecx,ecx
   10de4:	66 c1 e2 03          	shl    dx,0x3
   10de8:	66 8b ca             	mov    cx,dx
   10deb:	83 c1 02             	add    ecx,0x2
   10dee:	03 f9                	add    edi,ecx
   10df0:	66 8b 0f             	mov    cx,WORD PTR [edi]
   10df3:	66 89 0d 44 15 00 00 	mov    WORD PTR ds:0x1544,cx
   10dfa:	66 8b 4f 02          	mov    cx,WORD PTR [edi+0x2]
   10dfe:	66 89 0d 46 15 00 00 	mov    WORD PTR ds:0x1546,cx
   10e05:	03 77 04             	add    esi,DWORD PTR [edi+0x4]
   10e08:	c7 05 48 15 00 00 40 	mov    DWORD PTR ds:0x1548,0x140
   10e0f:	01 00 00 
   10e12:	66 f7 05 42 15 00 00 	test   WORD PTR ds:0x1542,0x2000
   10e19:	00 20 
   10e1b:	74 10                	je     0x10e2d
   10e1d:	66 03 d9             	add    bx,cx
   10e20:	66 01 0d 3e 15 00 00 	add    WORD PTR ds:0x153e,cx
   10e27:	f7 1d 48 15 00 00    	neg    DWORD PTR ds:0x1548
   10e2d:	0f bf cb             	movsx  ecx,bx
   10e30:	c1 e1 06             	shl    ecx,0x6
   10e33:	8b d1                	mov    edx,ecx
   10e35:	c1 e1 02             	shl    ecx,0x2
   10e38:	03 d1                	add    edx,ecx
   10e3a:	0f bf c8             	movsx  ecx,ax
   10e3d:	03 d1                	add    edx,ecx
   10e3f:	03 15 9c 03 00 00    	add    edx,DWORD PTR ds:0x39c
   10e45:	66 8b cb             	mov    cx,bx
   10e48:	83 3d 48 15 00 00 00 	cmp    DWORD PTR ds:0x1548,0x0
   10e4f:	78 09                	js     0x10e5a
   10e51:	66 03 0d 46 15 00 00 	add    cx,WORD PTR ds:0x1546
   10e58:	eb 07                	jmp    0x10e61
   10e5a:	66 2b 1d 46 15 00 00 	sub    bx,WORD PTR ds:0x1546
   10e61:	66 3b 1d 3a 15 00 00 	cmp    bx,WORD PTR ds:0x153a
   10e68:	0f 8d 8a 00 00 00    	jge    0x10ef8
   10e6e:	66 3b 0d 36 15 00 00 	cmp    cx,WORD PTR ds:0x1536
   10e75:	0f 8e 7d 00 00 00    	jle    0x10ef8
   10e7b:	66 3b 0d 3a 15 00 00 	cmp    cx,WORD PTR ds:0x153a
   10e82:	0f 8d a8 00 00 00    	jge    0x10f30
   10e88:	66 3b 1d 36 15 00 00 	cmp    bx,WORD PTR ds:0x1536
   10e8f:	0f 8c 9b 00 00 00    	jl     0x10f30
   10e95:	66 8b c8             	mov    cx,ax
   10e98:	66 3b 0d 38 15 00 00 	cmp    cx,WORD PTR ds:0x1538
   10e9f:	7d 57                	jge    0x10ef8
   10ea1:	66 03 0d 44 15 00 00 	add    cx,WORD PTR ds:0x1544
   10ea8:	66 3b 0d 34 15 00 00 	cmp    cx,WORD PTR ds:0x1534
   10eaf:	7e 47                	jle    0x10ef8
   10eb1:	66 3b 0d 38 15 00 00 	cmp    cx,WORD PTR ds:0x1538
   10eb8:	7d 76                	jge    0x10f30
   10eba:	66 3b 05 34 15 00 00 	cmp    ax,WORD PTR ds:0x1534
   10ec1:	7c 6d                	jl     0x10f30
   10ec3:	66 d1 15 42 15 00 00 	rcl    WORD PTR ds:0x1542,1
   10eca:	72 2d                	jb     0x10ef9
   10ecc:	66 d1 15 42 15 00 00 	rcl    WORD PTR ds:0x1542,1
   10ed3:	72 5a                	jb     0x10f2f
   10ed5:	33 c9                	xor    ecx,ecx
   10ed7:	8a 0e                	mov    cl,BYTE PTR [esi]
   10ed9:	80 f9 ff             	cmp    cl,0xff
   10edc:	74 1a                	je     0x10ef8
   10ede:	46                   	inc    esi
   10edf:	33 c0                	xor    eax,eax
   10ee1:	8a 06                	mov    al,BYTE PTR [esi]
   10ee3:	46                   	inc    esi
   10ee4:	8b f8                	mov    edi,eax
   10ee6:	0f af 3d 48 15 00 00 	imul   edi,DWORD PTR ds:0x1548
   10eed:	03 fa                	add    edi,edx
   10eef:	03 f9                	add    edi,ecx
   10ef1:	8a 0e                	mov    cl,BYTE PTR [esi]
   10ef3:	46                   	inc    esi
   10ef4:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   10ef6:	eb df                	jmp    0x10ed7
   10ef8:	c3                   	ret    
   10ef9:	33 c0                	xor    eax,eax
   10efb:	66 a1 44 15 00 00    	mov    ax,ds:0x1544
   10f01:	03 d0                	add    edx,eax
   10f03:	33 c9                	xor    ecx,ecx
   10f05:	8a 0e                	mov    cl,BYTE PTR [esi]
   10f07:	80 f9 ff             	cmp    cl,0xff
   10f0a:	74 22                	je     0x10f2e
   10f0c:	46                   	inc    esi
   10f0d:	33 c0                	xor    eax,eax
   10f0f:	8a 06                	mov    al,BYTE PTR [esi]
   10f11:	46                   	inc    esi
   10f12:	8b f8                	mov    edi,eax
   10f14:	0f af 3d 48 15 00 00 	imul   edi,DWORD PTR ds:0x1548
   10f1b:	03 fa                	add    edi,edx
   10f1d:	2b f9                	sub    edi,ecx
   10f1f:	8a 0e                	mov    cl,BYTE PTR [esi]
   10f21:	46                   	inc    esi
   10f22:	8a 06                	mov    al,BYTE PTR [esi]
   10f24:	88 07                	mov    BYTE PTR [edi],al
   10f26:	46                   	inc    esi
   10f27:	4f                   	dec    edi
   10f28:	fe c9                	dec    cl
   10f2a:	75 f6                	jne    0x10f22
   10f2c:	eb d7                	jmp    0x10f05
   10f2e:	c3                   	ret    
   10f2f:	c3                   	ret    
   10f30:	66 d1 15 42 15 00 00 	rcl    WORD PTR ds:0x1542,1
   10f37:	0f 82 ae 00 00 00    	jb     0x10feb
   10f3d:	66 d1 15 42 15 00 00 	rcl    WORD PTR ds:0x1542,1
   10f44:	0f 82 a0 00 00 00    	jb     0x10fea
   10f4a:	33 db                	xor    ebx,ebx
   10f4c:	33 c0                	xor    eax,eax
   10f4e:	33 c9                	xor    ecx,ecx
   10f50:	8a 06                	mov    al,BYTE PTR [esi]
   10f52:	3c ff                	cmp    al,0xff
   10f54:	0f 84 8f 00 00 00    	je     0x10fe9
   10f5a:	46                   	inc    esi
   10f5b:	8a 0e                	mov    cl,BYTE PTR [esi]
   10f5d:	46                   	inc    esi
   10f5e:	66 8b 1d 3e 15 00 00 	mov    bx,WORD PTR ds:0x153e
   10f65:	8b f9                	mov    edi,ecx
   10f67:	0f af 3d 48 15 00 00 	imul   edi,DWORD PTR ds:0x1548
   10f6e:	83 3d 48 15 00 00 00 	cmp    DWORD PTR ds:0x1548,0x0
   10f75:	78 05                	js     0x10f7c
   10f77:	66 03 d9             	add    bx,cx
   10f7a:	eb 03                	jmp    0x10f7f
   10f7c:	66 2b d9             	sub    bx,cx
   10f7f:	66 3b 1d 36 15 00 00 	cmp    bx,WORD PTR ds:0x1536
   10f86:	7c 57                	jl     0x10fdf
   10f88:	66 3b 1d 3a 15 00 00 	cmp    bx,WORD PTR ds:0x153a
   10f8f:	7d 4e                	jge    0x10fdf
   10f91:	66 8b 1d 3c 15 00 00 	mov    bx,WORD PTR ds:0x153c
   10f98:	66 03 d8             	add    bx,ax
   10f9b:	66 3b 1d 38 15 00 00 	cmp    bx,WORD PTR ds:0x1538
   10fa2:	7d 3b                	jge    0x10fdf
   10fa4:	03 fa                	add    edi,edx
   10fa6:	33 c9                	xor    ecx,ecx
   10fa8:	8a 0e                	mov    cl,BYTE PTR [esi]
   10faa:	56                   	push   esi
   10fab:	66 3b 1d 34 15 00 00 	cmp    bx,WORD PTR ds:0x1534
   10fb2:	7d 14                	jge    0x10fc8
   10fb4:	66 2b 1d 34 15 00 00 	sub    bx,WORD PTR ds:0x1534
   10fbb:	66 f7 db             	neg    bx
   10fbe:	66 2b cb             	sub    cx,bx
   10fc1:	7e 1b                	jle    0x10fde
   10fc3:	66 03 c3             	add    ax,bx
   10fc6:	03 f3                	add    esi,ebx
   10fc8:	66 03 d9             	add    bx,cx
   10fcb:	66 2b 1d 38 15 00 00 	sub    bx,WORD PTR ds:0x1538
   10fd2:	7e 05                	jle    0x10fd9
   10fd4:	66 2b cb             	sub    cx,bx
   10fd7:	7e 05                	jle    0x10fde
   10fd9:	46                   	inc    esi
   10fda:	03 f8                	add    edi,eax
   10fdc:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   10fde:	5e                   	pop    esi
   10fdf:	8a 06                	mov    al,BYTE PTR [esi]
   10fe1:	46                   	inc    esi
   10fe2:	03 f0                	add    esi,eax
   10fe4:	e9 63 ff ff ff       	jmp    0x10f4c
   10fe9:	c3                   	ret    
   10fea:	c3                   	ret    
   10feb:	33 c0                	xor    eax,eax
   10fed:	66 a1 44 15 00 00    	mov    ax,ds:0x1544
   10ff3:	66 01 05 3c 15 00 00 	add    WORD PTR ds:0x153c,ax
   10ffa:	03 d0                	add    edx,eax
   10ffc:	33 db                	xor    ebx,ebx
   10ffe:	33 c0                	xor    eax,eax
   11000:	33 c9                	xor    ecx,ecx
   11002:	8a 06                	mov    al,BYTE PTR [esi]
   11004:	3c ff                	cmp    al,0xff
   11006:	0f 84 91 00 00 00    	je     0x1109d
   1100c:	46                   	inc    esi
   1100d:	8a 0e                	mov    cl,BYTE PTR [esi]
   1100f:	46                   	inc    esi
   11010:	66 8b 1d 3e 15 00 00 	mov    bx,WORD PTR ds:0x153e
   11017:	8b f9                	mov    edi,ecx
   11019:	0f af 3d 48 15 00 00 	imul   edi,DWORD PTR ds:0x1548
   11020:	83 3d 48 15 00 00 00 	cmp    DWORD PTR ds:0x1548,0x0
   11027:	78 05                	js     0x1102e
   11029:	66 03 d9             	add    bx,cx
   1102c:	eb 03                	jmp    0x11031
   1102e:	66 2b d9             	sub    bx,cx
   11031:	66 3b 1d 36 15 00 00 	cmp    bx,WORD PTR ds:0x1536
   11038:	7c 59                	jl     0x11093
   1103a:	66 3b 1d 3a 15 00 00 	cmp    bx,WORD PTR ds:0x153a
   11041:	7d 50                	jge    0x11093
   11043:	03 fa                	add    edi,edx
   11045:	33 c9                	xor    ecx,ecx
   11047:	8a 0e                	mov    cl,BYTE PTR [esi]
   11049:	56                   	push   esi
   1104a:	66 8b 1d 3c 15 00 00 	mov    bx,WORD PTR ds:0x153c
   11051:	66 2b d8             	sub    bx,ax
   11054:	66 3b 1d 38 15 00 00 	cmp    bx,WORD PTR ds:0x1538
   1105b:	7c 17                	jl     0x11074
   1105d:	66 2b 1d 38 15 00 00 	sub    bx,WORD PTR ds:0x1538
   11064:	66 2b cb             	sub    cx,bx
   11067:	7e 29                	jle    0x11092
   11069:	03 c3                	add    eax,ebx
   1106b:	03 f3                	add    esi,ebx
   1106d:	66 8b 1d 38 15 00 00 	mov    bx,WORD PTR ds:0x1538
   11074:	66 2b d9             	sub    bx,cx
   11077:	66 2b 1d 34 15 00 00 	sub    bx,WORD PTR ds:0x1534
   1107e:	7d 05                	jge    0x11085
   11080:	66 03 cb             	add    cx,bx
   11083:	7e 0d                	jle    0x11092
   11085:	46                   	inc    esi
   11086:	2b f8                	sub    edi,eax
   11088:	8a 06                	mov    al,BYTE PTR [esi]
   1108a:	46                   	inc    esi
   1108b:	4f                   	dec    edi
   1108c:	88 07                	mov    BYTE PTR [edi],al
   1108e:	fe c9                	dec    cl
   11090:	75 f6                	jne    0x11088
   11092:	5e                   	pop    esi
   11093:	8a 06                	mov    al,BYTE PTR [esi]
   11095:	46                   	inc    esi
   11096:	03 f0                	add    esi,eax
   11098:	e9 61 ff ff ff       	jmp    0x10ffe
   1109d:	c3                   	ret    
   1109e:	aa                   	stos   BYTE PTR es:[edi],al
   1109f:	11 00                	adc    DWORD PTR [eax],eax
   110a1:	00 b9 11 00 00 c0    	add    BYTE PTR [ecx-0x3fffffef],bh
   110a7:	11 00                	adc    DWORD PTR [eax],eax
   110a9:	00 d1                	add    cl,dl
   110ab:	11 00                	adc    DWORD PTR [eax],eax
   110ad:	00 d8                	add    al,bl
   110af:	11 00                	adc    DWORD PTR [eax],eax
   110b1:	00 f3                	add    bl,dh
   110b3:	11 00                	adc    DWORD PTR [eax],eax
   110b5:	00 1b                	add    BYTE PTR [ebx],bl
   110b7:	12 00                	adc    al,BYTE PTR [eax]
   110b9:	00 22                	add    BYTE PTR [edx],ah
   110bb:	12 00                	adc    al,BYTE PTR [eax]
   110bd:	00 ca                	add    dl,cl
   110bf:	11 00                	adc    DWORD PTR [eax],eax
   110c1:	00 4a 12             	add    BYTE PTR [edx+0x12],cl
   110c4:	00 00                	add    BYTE PTR [eax],al
   110c6:	65 12 00             	adc    al,BYTE PTR gs:[eax]
   110c9:	00 7b 12             	add    BYTE PTR [ebx+0x12],bh
   110cc:	00 00                	add    BYTE PTR [eax],al
   110ce:	8e 12                	mov    ss,WORD PTR [edx]
   110d0:	00 00                	add    BYTE PTR [eax],al
   110d2:	a4                   	movs   BYTE PTR es:[edi],BYTE PTR ds:[esi]
   110d3:	12 00                	adc    al,BYTE PTR [eax]
   110d5:	00 53 51             	add    BYTE PTR [ebx+0x51],dl
   110d8:	52                   	push   edx

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000110d9 <.data+0x10d9>:
   110d9:	55                   	push   ebp
   110da:	89 e5                	mov    ebp,esp
   110dc:	83 ec 14             	sub    esp,0x14
   110df:	89 c3                	mov    ebx,eax
   110e1:	31 d2                	xor    edx,edx
   110e3:	eb 06                	jmp    0x110eb
   110e5:	e8 f8 fb ff ff       	call   0x10ce2
   110ea:	42                   	inc    edx
   110eb:	0f bf c2             	movsx  eax,dx
   110ee:	3d f4 01 00 00       	cmp    eax,0x1f4
   110f3:	7c f0                	jl     0x110e5
   110f5:	8b 15 86 15 00 00    	mov    edx,DWORD PTR ds:0x1586
   110fb:	85 d2                	test   edx,edx
   110fd:	74 0f                	je     0x1110e
   110ff:	89 d0                	mov    eax,edx
   11101:	31 c9                	xor    ecx,ecx
   11103:	e8 ac f0 ff ff       	call   0x101b4
   11108:	89 0d 86 15 00 00    	mov    DWORD PTR ds:0x1586,ecx
   1110e:	83 fb 0a             	cmp    ebx,0xa
   11111:	7d 1a                	jge    0x1112d
   11113:	8d 43 01             	lea    eax,[ebx+0x1]
   11116:	50                   	push   eax
   11117:	68 24 00 00 00       	push   0x24
   1111c:	8d 45 ec             	lea    eax,[ebp-0x14]
   1111f:	50                   	push   eax
   11120:	e8 55 5a 03 00       	call   0x46b7a
   11125:	83 c4 0c             	add    esp,0xc
   11128:	8d 45 ec             	lea    eax,[ebp-0x14]
   1112b:	eb 05                	jmp    0x11132
   1112d:	b8 30 00 00 00       	mov    eax,0x30
   11132:	e8 68 04 00 00       	call   0x1159f
   11137:	ba 01 00 00 00       	mov    edx,0x1
   1113c:	31 c0                	xor    eax,eax
   1113e:	e8 02 05 00 00       	call   0x11645
   11143:	a1 e8 73 01 00       	mov    eax,ds:0x173e8
   11148:	e8 67 f0 ff ff       	call   0x101b4
   1114d:	b8 3a 00 00 00       	mov    eax,0x3a
   11152:	ba 46 00 00 00       	mov    edx,0x46
   11157:	e8 be 10 00 00       	call   0x1221a
   1115c:	a3 e8 73 01 00       	mov    ds:0x173e8,eax
   11161:	31 c0                	xor    eax,eax
   11163:	e8 68 fb ff ff       	call   0x10cd0
   11168:	ba 52 00 00 00       	mov    edx,0x52
   1116d:	b8 01 00 00 00       	mov    eax,0x1
   11172:	e8 59 fb ff ff       	call   0x10cd0
   11177:	83 fb 06             	cmp    ebx,0x6
   1117a:	7d 07                	jge    0x11183
   1117c:	b8 4c 74 00 00       	mov    eax,0x744c
   11181:	eb 05                	jmp    0x11188
   11183:	b8 48 8a 00 00       	mov    eax,0x8a48
   11188:	e8 73 02 00 00       	call   0x11400
   1118d:	b8 1c b0 00 00       	mov    eax,0xb01c
   11192:	e8 69 02 00 00       	call   0x11400
   11197:	83 fb 0d             	cmp    ebx,0xd
   1119a:	0f 87 1d 01 00 00    	ja     0x112bd
   111a0:	89 d8                	mov    eax,ebx
   111a2:	2e ff 24 85 9e 10 00 	jmp    DWORD PTR cs:[eax*4+0x109e]
   111a9:	00 
   111aa:	b8 fc a1 00 00       	mov    eax,0xa1fc
   111af:	e8 4c 02 00 00       	call   0x11400
   111b4:	e9 04 01 00 00       	jmp    0x112bd
   111b9:	b8 2c c1 00 00       	mov    eax,0xc12c
   111be:	eb ef                	jmp    0x111af
   111c0:	b8 44 ce 00 00       	mov    eax,0xce44
   111c5:	e8 36 02 00 00       	call   0x11400
   111ca:	b8 bc 04 01 00       	mov    eax,0x104bc
   111cf:	eb de                	jmp    0x111af
   111d1:	b8 f0 d6 00 00       	mov    eax,0xd6f0
   111d6:	eb d7                	jmp    0x111af
   111d8:	b8 44 e3 00 00       	mov    eax,0xe344
   111dd:	e8 1e 02 00 00       	call   0x11400
   111e2:	b8 b8 24 01 00       	mov    eax,0x124b8
   111e7:	e8 14 02 00 00       	call   0x11400
   111ec:	b8 44 27 01 00       	mov    eax,0x12744
   111f1:	eb bc                	jmp    0x111af
   111f3:	b8 44 e3 00 00       	mov    eax,0xe344
   111f8:	e8 03 02 00 00       	call   0x11400
   111fd:	b8 d0 e3 00 00       	mov    eax,0xe3d0
   11202:	e8 f9 01 00 00       	call   0x11400
   11207:	b8 5b 00 00 00       	mov    eax,0x5b
   1120c:	e8 09 10 00 00       	call   0x1221a
   11211:	a3 86 15 00 00       	mov    ds:0x1586,eax
   11216:	e9 a2 00 00 00       	jmp    0x112bd
   1121b:	b8 f8 f0 00 00       	mov    eax,0xf0f8
   11220:	eb 8d                	jmp    0x111af
   11222:	b8 44 e3 00 00       	mov    eax,0xe344
   11227:	e8 d4 01 00 00       	call   0x11400
   1122c:	b8 f8 f0 00 00       	mov    eax,0xf0f8
   11231:	e8 ca 01 00 00       	call   0x11400
   11236:	b8 bc 04 01 00       	mov    eax,0x104bc
   1123b:	e8 c0 01 00 00       	call   0x11400
   11240:	b8 4c 74 00 00       	mov    eax,0x744c
   11245:	e9 65 ff ff ff       	jmp    0x111af
   1124a:	b8 bc 04 01 00       	mov    eax,0x104bc
   1124f:	e8 ac 01 00 00       	call   0x11400
   11254:	b8 3c 11 01 00       	mov    eax,0x1113c
   11259:	e8 a2 01 00 00       	call   0x11400
   1125e:	b8 66 00 00 00       	mov    eax,0x66
   11263:	eb a7                	jmp    0x1120c
   11265:	b8 88 20 01 00       	mov    eax,0x12088
   1126a:	ba 05 00 00 00       	mov    edx,0x5
   1126f:	e8 8c 01 00 00       	call   0x11400
   11274:	b8 04 00 00 00       	mov    eax,0x4
   11279:	eb 3d                	jmp    0x112b8
   1127b:	b8 88 20 01 00       	mov    eax,0x12088
   11280:	ba 01 00 00 00       	mov    edx,0x1
   11285:	e8 76 01 00 00       	call   0x11400
   1128a:	31 c0                	xor    eax,eax
   1128c:	eb 2a                	jmp    0x112b8
   1128e:	b8 88 20 01 00       	mov    eax,0x12088
   11293:	ba 01 00 00 00       	mov    edx,0x1
   11298:	e8 63 01 00 00       	call   0x11400
   1129d:	b8 02 00 00 00       	mov    eax,0x2
   112a2:	eb 14                	jmp    0x112b8
   112a4:	b8 88 20 01 00       	mov    eax,0x12088
   112a9:	ba 01 00 00 00       	mov    edx,0x1
   112ae:	e8 4d 01 00 00       	call   0x11400
   112b3:	b8 03 00 00 00       	mov    eax,0x3
   112b8:	e8 88 03 00 00       	call   0x11645
   112bd:	b8 fc a1 00 00       	mov    eax,0xa1fc
   112c2:	e8 39 01 00 00       	call   0x11400
   112c7:	89 d8                	mov    eax,ebx
   112c9:	e8 40 00 00 00       	call   0x1130e
   112ce:	89 ec                	mov    esp,ebp
   112d0:	5d                   	pop    ebp
   112d1:	5a                   	pop    edx
   112d2:	59                   	pop    ecx
   112d3:	5b                   	pop    ebx
   112d4:	c3                   	ret    
   112d5:	90                   	nop
   112d6:	5b                   	pop    ebx
   112d7:	13 00                	adc    eax,DWORD PTR [eax]
   112d9:	00 65 13             	add    BYTE PTR [ebp+0x13],ah
   112dc:	00 00                	add    BYTE PTR [eax],al
   112de:	6f                   	outs   dx,DWORD PTR ds:[esi]
   112df:	13 00                	adc    eax,DWORD PTR [eax]
   112e1:	00 83 13 00 00 8a    	add    BYTE PTR [ebx-0x75ffffed],al
   112e7:	13 00                	adc    eax,DWORD PTR [eax]
   112e9:	00 a5 13 00 00 c0    	add    BYTE PTR [ebp-0x3fffffed],ah
   112ef:	13 00                	adc    eax,DWORD PTR [eax]
   112f1:	00 c7                	add    bh,al
   112f3:	13 00                	adc    eax,DWORD PTR [eax]
   112f5:	00 5b 13             	add    BYTE PTR [ebx+0x13],bl
   112f8:	00 00                	add    BYTE PTR [eax],al
   112fa:	d8 13                	fcom   DWORD PTR [ebx]
   112fc:	00 00                	add    BYTE PTR [eax],al
   112fe:	e9 13 00 00 e9       	jmp    0xe9011316
   11303:	13 00                	adc    eax,DWORD PTR [eax]
   11305:	00 e9                	add    cl,ch
   11307:	13 00                	adc    eax,DWORD PTR [eax]
   11309:	00 f0                	add    al,dh
   1130b:	13 00                	adc    eax,DWORD PTR [eax]
	...

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0001130e <.data+0x130e>:
   1130e:	53                   	push   ebx
   1130f:	51                   	push   ecx
   11310:	52                   	push   edx
   11311:	56                   	push   esi
   11312:	55                   	push   ebp
   11313:	89 e5                	mov    ebp,esp
   11315:	89 c1                	mov    ecx,eax
   11317:	31 db                	xor    ebx,ebx
   11319:	89 d8                	mov    eax,ebx
   1131b:	c1 e0 02             	shl    eax,0x2
   1131e:	01 d8                	add    eax,ebx
   11320:	c1 e0 02             	shl    eax,0x2
   11323:	29 d8                	sub    eax,ebx
   11325:	31 f6                	xor    esi,esi
   11327:	89 c2                	mov    edx,eax
   11329:	8b 80 18 fb 01 00    	mov    eax,DWORD PTR [eax+0x1fb18]
   1132f:	43                   	inc    ebx
   11330:	e8 7f ee ff ff       	call   0x101b4
   11335:	89 b2 18 fb 01 00    	mov    DWORD PTR [edx+0x1fb18],esi
   1133b:	83 fb 4b             	cmp    ebx,0x4b
   1133e:	7c d9                	jl     0x11319
   11340:	b8 30 2f 01 00       	mov    eax,0x12f30
   11345:	e8 20 01 00 00       	call   0x1146a
   1134a:	83 f9 0d             	cmp    ecx,0xd
   1134d:	0f 87 a7 00 00 00    	ja     0x113fa
   11353:	2e ff 24 8d d6 12 00 	jmp    DWORD PTR cs:[ecx*4+0x12d6]
   1135a:	00 
   1135b:	b8 8c 2f 01 00       	mov    eax,0x12f8c
   11360:	e9 90 00 00 00       	jmp    0x113f5
   11365:	b8 b0 2f 01 00       	mov    eax,0x12fb0
   1136a:	e9 86 00 00 00       	jmp    0x113f5
   1136f:	b8 8c 2f 01 00       	mov    eax,0x12f8c
   11374:	e8 f1 00 00 00       	call   0x1146a
   11379:	b8 d4 2f 01 00       	mov    eax,0x12fd4
   1137e:	e9 72 00 00 00       	jmp    0x113f5
   11383:	b8 f8 2f 01 00       	mov    eax,0x12ff8
   11388:	eb 6b                	jmp    0x113f5
   1138a:	b8 8c 2f 01 00       	mov    eax,0x12f8c
   1138f:	e8 d6 00 00 00       	call   0x1146a
   11394:	b8 04 30 01 00       	mov    eax,0x13004
   11399:	e8 cc 00 00 00       	call   0x1146a
   1139e:	b8 94 30 01 00       	mov    eax,0x13094
   113a3:	eb 50                	jmp    0x113f5
   113a5:	b8 b0 2f 01 00       	mov    eax,0x12fb0
   113aa:	e8 bb 00 00 00       	call   0x1146a
   113af:	b8 04 30 01 00       	mov    eax,0x13004
   113b4:	e8 b1 00 00 00       	call   0x1146a
   113b9:	b8 18 30 01 00       	mov    eax,0x13018
   113be:	eb d9                	jmp    0x11399
   113c0:	b8 34 30 01 00       	mov    eax,0x13034
   113c5:	eb d2                	jmp    0x11399
   113c7:	b8 8c 2f 01 00       	mov    eax,0x12f8c
   113cc:	e8 99 00 00 00       	call   0x1146a
   113d1:	b8 48 30 01 00       	mov    eax,0x13048
   113d6:	eb 1d                	jmp    0x113f5
   113d8:	b8 8c 2f 01 00       	mov    eax,0x12f8c
   113dd:	e8 88 00 00 00       	call   0x1146a
   113e2:	b8 64 30 01 00       	mov    eax,0x13064
   113e7:	eb 0c                	jmp    0x113f5
   113e9:	b8 70 30 01 00       	mov    eax,0x13070
   113ee:	eb 05                	jmp    0x113f5
   113f0:	b8 70 30 01 00       	mov    eax,0x13070
   113f5:	e8 70 00 00 00       	call   0x1146a
   113fa:	5d                   	pop    ebp
   113fb:	5e                   	pop    esi
   113fc:	5a                   	pop    edx
   113fd:	59                   	pop    ecx
   113fe:	5b                   	pop    ebx
   113ff:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00011400 <.data+0x1400>:
   11400:	53                   	push   ebx
   11401:	51                   	push   ecx
   11402:	52                   	push   edx
   11403:	56                   	push   esi
   11404:	57                   	push   edi
   11405:	55                   	push   ebp
   11406:	89 e5                	mov    ebp,esp
   11408:	83 ec 14             	sub    esp,0x14
   1140b:	8d 58 04             	lea    ebx,[eax+0x4]
   1140e:	0f bf 30             	movsx  esi,WORD PTR [eax]
   11411:	8b 38                	mov    edi,DWORD PTR [eax]
   11413:	31 c9                	xor    ecx,ecx
   11415:	c1 ff 10             	sar    edi,0x10
   11418:	eb 43                	jmp    0x1145d
   1141a:	31 c0                	xor    eax,eax
   1141c:	40                   	inc    eax
   1141d:	8a 13                	mov    dl,BYTE PTR [ebx]
   1141f:	88 54 28 eb          	mov    BYTE PTR [eax+ebp*1-0x15],dl
   11423:	43                   	inc    ebx
   11424:	83 f8 08             	cmp    eax,0x8
   11427:	7c f3                	jl     0x1141c
   11429:	b8 08 00 00 00       	mov    eax,0x8
   1142e:	30 d2                	xor    dl,dl
   11430:	88 54 28 ec          	mov    BYTE PTR [eax+ebp*1-0x14],dl
   11434:	31 d2                	xor    edx,edx
   11436:	8a 54 28 eb          	mov    dl,BYTE PTR [eax+ebp*1-0x15]
   1143a:	48                   	dec    eax
   1143b:	83 fa 20             	cmp    edx,0x20
   1143e:	75 04                	jne    0x11444
   11440:	85 c0                	test   eax,eax
   11442:	7f ea                	jg     0x1142e
   11444:	ba 72 00 00 00       	mov    edx,0x72
   11449:	8d 45 ec             	lea    eax,[ebp-0x14]
   1144c:	e8 59 57 03 00       	call   0x46baa
   11451:	8d 55 ec             	lea    edx,[ebp-0x14]
   11454:	8d 04 0e             	lea    eax,[esi+ecx*1]
   11457:	e8 74 f8 ff ff       	call   0x10cd0
   1145c:	41                   	inc    ecx
   1145d:	39 f9                	cmp    ecx,edi
   1145f:	7c b9                	jl     0x1141a
   11461:	89 ec                	mov    esp,ebp
   11463:	5d                   	pop    ebp
   11464:	5f                   	pop    edi
   11465:	5e                   	pop    esi
   11466:	5a                   	pop    edx
   11467:	59                   	pop    ecx
   11468:	5b                   	pop    ebx
   11469:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0001146a <.data+0x146a>:
   1146a:	53                   	push   ebx
   1146b:	51                   	push   ecx
   1146c:	52                   	push   edx
   1146d:	56                   	push   esi
   1146e:	57                   	push   edi
   1146f:	55                   	push   ebp
   11470:	89 e5                	mov    ebp,esp
   11472:	83 ec 1c             	sub    esp,0x1c
   11475:	8b 15 62 9b 01 00    	mov    edx,DWORD PTR ds:0x19b62
   1147b:	c1 fa 10             	sar    edx,0x10
   1147e:	83 fa ff             	cmp    edx,0xffffffff
   11481:	0f 84 0f 01 00 00    	je     0x11596
   11487:	0f bf 10             	movsx  edx,WORD PTR [eax]
   1148a:	89 55 fc             	mov    DWORD PTR [ebp-0x4],edx
   1148d:	8b 10                	mov    edx,DWORD PTR [eax]
   1148f:	8d 70 04             	lea    esi,[eax+0x4]
   11492:	c1 fa 10             	sar    edx,0x10
   11495:	31 ff                	xor    edi,edi
   11497:	89 55 f8             	mov    DWORD PTR [ebp-0x8],edx
   1149a:	e9 a0 00 00 00       	jmp    0x1153f
   1149f:	31 c0                	xor    eax,eax
   114a1:	40                   	inc    eax
   114a2:	8a 16                	mov    dl,BYTE PTR [esi]
   114a4:	88 54 28 e3          	mov    BYTE PTR [eax+ebp*1-0x1d],dl
   114a8:	46                   	inc    esi
   114a9:	83 f8 08             	cmp    eax,0x8
   114ac:	7c f3                	jl     0x114a1
   114ae:	ba 08 00 00 00       	mov    edx,0x8
   114b3:	30 e4                	xor    ah,ah
   114b5:	88 64 2a e4          	mov    BYTE PTR [edx+ebp*1-0x1c],ah
   114b9:	31 c0                	xor    eax,eax
   114bb:	8a 44 2a e3          	mov    al,BYTE PTR [edx+ebp*1-0x1d]
   114bf:	4a                   	dec    edx
   114c0:	83 f8 20             	cmp    eax,0x20
   114c3:	75 04                	jne    0x114c9
   114c5:	85 d2                	test   edx,edx
   114c7:	7f ea                	jg     0x114b3
   114c9:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
   114cc:	89 c2                	mov    edx,eax
   114ce:	c1 e2 02             	shl    edx,0x2
   114d1:	01 c2                	add    edx,eax
   114d3:	c1 e2 02             	shl    edx,0x2
   114d6:	29 c2                	sub    edx,eax
   114d8:	8b 82 18 fb 01 00    	mov    eax,DWORD PTR [edx+0x1fb18]
   114de:	e8 d1 ec ff ff       	call   0x101b4
   114e3:	8d 45 e4             	lea    eax,[ebp-0x1c]
   114e6:	e8 2f 0d 00 00       	call   0x1221a
   114eb:	89 82 18 fb 01 00    	mov    DWORD PTR [edx+0x1fb18],eax
   114f1:	8d 45 e4             	lea    eax,[ebp-0x1c]
   114f4:	31 db                	xor    ebx,ebx
   114f6:	e8 3b 0d 00 00       	call   0x12236
   114fb:	89 82 1c fb 01 00    	mov    DWORD PTR [edx+0x1fb1c],eax
   11501:	89 9a 20 fb 01 00    	mov    DWORD PTR [edx+0x1fb20],ebx
   11507:	89 9a 24 fb 01 00    	mov    DWORD PTR [edx+0x1fb24],ebx
   1150d:	30 db                	xor    bl,bl
   1150f:	88 9a 28 fb 01 00    	mov    BYTE PTR [edx+0x1fb28],bl
   11515:	30 ff                	xor    bh,bh
   11517:	8b 82 1c fb 01 00    	mov    eax,DWORD PTR [edx+0x1fb1c]
   1151d:	66 89 9a 29 fb 01 00 	mov    WORD PTR [edx+0x1fb29],bx
   11524:	50                   	push   eax
   11525:	8b 9a 18 fb 01 00    	mov    ebx,DWORD PTR [edx+0x1fb18]
   1152b:	53                   	push   ebx
   1152c:	53                   	push   ebx
   1152d:	6a 00                	push   0x0
   1152f:	e8 a1 bf 02 00       	call   0x3d4d5
   11534:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
   11537:	47                   	inc    edi
   11538:	40                   	inc    eax
   11539:	83 c4 10             	add    esp,0x10
   1153c:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
   1153f:	3b 7d f8             	cmp    edi,DWORD PTR [ebp-0x8]
   11542:	0f 8c 57 ff ff ff    	jl     0x1149f
   11548:	bb 7c 1e 00 00       	mov    ebx,0x1e7c
   1154d:	b9 68 54 00 00       	mov    ecx,0x5468
   11552:	be 52 31 00 00       	mov    esi,0x3152
   11557:	bf de 9b 00 00       	mov    edi,0x9bde
   1155c:	89 1d 21 fd 01 00    	mov    DWORD PTR ds:0x1fd21,ebx
   11562:	89 0d 25 fd 01 00    	mov    DWORD PTR ds:0x1fd25,ecx
   11568:	89 35 5a fd 01 00    	mov    DWORD PTR ds:0x1fd5a,esi
   1156e:	89 3d 5e fd 01 00    	mov    DWORD PTR ds:0x1fd5e,edi
   11574:	89 1d cc fd 01 00    	mov    DWORD PTR ds:0x1fdcc,ebx
   1157a:	89 0d d0 fd 01 00    	mov    DWORD PTR ds:0x1fdd0,ecx
   11580:	bb 72 1e 00 00       	mov    ebx,0x1e72
   11585:	b9 e0 38 00 00       	mov    ecx,0x38e0
   1158a:	89 1d 8a fe 01 00    	mov    DWORD PTR ds:0x1fe8a,ebx
   11590:	89 0d 8e fe 01 00    	mov    DWORD PTR ds:0x1fe8e,ecx
   11596:	89 ec                	mov    esp,ebp
   11598:	5d                   	pop    ebp
   11599:	5f                   	pop    edi
   1159a:	5e                   	pop    esi
   1159b:	5a                   	pop    edx
   1159c:	59                   	pop    ecx
   1159d:	5b                   	pop    ebx
   1159e:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00010cd0 <.data+0xcd0>:
   10cd0:	53                   	push   ebx
   10cd1:	51                   	push   ecx
   10cd2:	52                   	push   edx
   10cd3:	55                   	push   ebp
   10cd4:	56                   	push   esi
   10cd5:	57                   	push   edi
   10cd6:	e8 35 00 00 00       	call   0x10d10
   10cdb:	5f                   	pop    edi
   10cdc:	5e                   	pop    esi
   10cdd:	5d                   	pop    ebp
   10cde:	5a                   	pop    edx
   10cdf:	59                   	pop    ecx
   10ce0:	5b                   	pop    ebx
   10ce1:	c3                   	ret    
   10ce2:	50                   	push   eax
   10ce3:	53                   	push   ebx
   10ce4:	51                   	push   ecx
   10ce5:	52                   	push   edx
   10ce6:	55                   	push   ebp
   10ce7:	56                   	push   esi
   10ce8:	57                   	push   edi
   10ce9:	e8 87 00 00 00       	call   0x10d75
   10cee:	5f                   	pop    edi
   10cef:	5e                   	pop    esi
   10cf0:	5d                   	pop    ebp
   10cf1:	5a                   	pop    edx
   10cf2:	59                   	pop    ecx
   10cf3:	5b                   	pop    ebx
   10cf4:	58                   	pop    eax
   10cf5:	c3                   	ret    
   10cf6:	50                   	push   eax
   10cf7:	53                   	push   ebx
   10cf8:	51                   	push   ecx
   10cf9:	52                   	push   edx
   10cfa:	55                   	push   ebp
   10cfb:	56                   	push   esi
   10cfc:	57                   	push   edi
   10cfd:	66 87 da             	xchg   dx,bx
   10d00:	66 87 ca             	xchg   dx,cx
   10d03:	e8 91 00 00 00       	call   0x10d99
   10d08:	5f                   	pop    edi
   10d09:	5e                   	pop    esi
   10d0a:	5d                   	pop    ebp
   10d0b:	5a                   	pop    edx
   10d0c:	59                   	pop    ecx
   10d0d:	5b                   	pop    ebx
   10d0e:	58                   	pop    eax
   10d0f:	c3                   	ret    
