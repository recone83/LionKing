
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00045ad4 <.data+0x35ad4>:
   45ad4:	eb 76                	jmp    0x45b4c

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00045b4c <.data+0x35b4c>:
   45b4c:	fb                   	sti    
   45b4d:	83 e4 fc             	and    esp,0xfffffffc
   45b50:	89 e3                	mov    ebx,esp
   45b52:	89 1d 7c c0 01 00    	mov    DWORD PTR ds:0x1c07c,ebx
   45b58:	89 1d 68 c0 01 00    	mov    DWORD PTR ds:0x1c068,ebx
   45b5e:	66 b8 24 00          	mov    ax,0x24
   45b62:	66 a3 74 c0 01 00    	mov    ds:0x1c074,ax
   45b68:	bb 52 41 48 50       	mov    ebx,0x50484152
   45b6d:	29 c0                	sub    eax,eax
   45b6f:	b4 30                	mov    ah,0x30
   45b71:	cd 21                	int    0x21
   45b73:	a2 9f c0 01 00       	mov    ds:0x1c09f,al
   45b78:	88 25 a0 c0 01 00    	mov    BYTE PTR ds:0x1c0a0,ah
   45b7e:	89 c1                	mov    ecx,eax
   45b80:	29 f6                	sub    esi,esi
   45b82:	bf 81 00 00 00       	mov    edi,0x81
   45b87:	c1 e8 10             	shr    eax,0x10
   45b8a:	66 3d 58 44          	cmp    ax,0x4458
   45b8e:	75 3e                	jne    0x45bce
   45b90:	80 eb 30             	sub    bl,0x30
   45b93:	88 d8                	mov    al,bl
   45b95:	b4 00                	mov    ah,0x0
   45b97:	50                   	push   eax
   45b98:	66 8e 05 74 c0 01 00 	data16 mov es,WORD PTR ds:0x1c074
   45b9f:	26 8b 1d 5c 00 00 00 	mov    ebx,DWORD PTR es:0x5c
   45ba6:	81 c3 ff 0f 00 00    	add    ebx,0xfff
   45bac:	81 e3 00 f0 ff ff    	and    ebx,0xfffff000
   45bb2:	89 1d 68 c0 01 00    	mov    DWORD PTR ds:0x1c068,ebx
   45bb8:	c1 eb 0c             	shr    ebx,0xc
   45bbb:	66 8c d8             	mov    ax,ds
   45bbe:	8e c0                	mov    es,eax
   45bc0:	b4 4a                	mov    ah,0x4a
   45bc2:	cd 21                	int    0x21
   45bc4:	58                   	pop    eax
   45bc5:	66 8c db             	mov    bx,ds
   45bc8:	66 b9 2c 00          	mov    cx,0x2c
   45bcc:	eb 38                	jmp    0x45c06
   45bce:	66 3d 43 42          	cmp    ax,0x4243
   45bd2:	75 34                	jne    0x45c08
   45bd4:	89 15 44 c0 01 00    	mov    DWORD PTR ds:0x1c044,edx
   45bda:	89 d6                	mov    esi,edx
   45bdc:	8b 56 1c             	mov    edx,DWORD PTR [esi+0x1c]
   45bdf:	89 e3                	mov    ebx,esp
   45be1:	29 d3                	sub    ebx,edx
   45be3:	b4 4a                	mov    ah,0x4a
   45be5:	cd 21                	int    0x21
   45be7:	66 8c db             	mov    bx,ds
   45bea:	66 8c 1d 74 c0 01 00 	data16 mov WORD PTR ds:0x1c074,ds
   45bf1:	8b 46 10             	mov    eax,DWORD PTR [esi+0x10]
   45bf4:	01 c7                	add    edi,eax
   45bf6:	29 f6                	sub    esi,esi
   45bf8:	66 8b 70 2c          	mov    si,WORD PTR [eax+0x2c]
   45bfc:	c1 e6 04             	shl    esi,0x4
   45bff:	66 8c d9             	mov    cx,ds
   45c02:	b0 09                	mov    al,0x9
   45c04:	b4 00                	mov    ah,0x0
   45c06:	eb 59                	jmp    0x45c61
   45c08:	66 ba 78 00          	mov    dx,0x78
   45c0c:	66 b8 00 ff          	mov    ax,0xff00
   45c10:	cd 21                	int    0x21
   45c12:	3c 00                	cmp    al,0x0
   45c14:	74 34                	je     0x45c4a
   45c16:	66 8c e8             	mov    ax,gs
   45c19:	66 83 f8 00          	cmp    ax,0x0
   45c1d:	74 06                	je     0x45c25
   45c1f:	66 a3 48 c0 01 00    	mov    ds:0x1c048,ax
   45c25:	66 b8 06 00          	mov    ax,0x6
   45c29:	66 8c db             	mov    bx,ds
   45c2c:	cd 31                	int    0x31
   45c2e:	b0 01                	mov    al,0x1
   45c30:	b4 00                	mov    ah,0x0
   45c32:	66 09 ca             	or     dx,cx
   45c35:	74 02                	je     0x45c39
   45c37:	b4 01                	mov    ah,0x1
   45c39:	66 8c 05 74 c0 01 00 	data16 mov WORD PTR ds:0x1c074,es
   45c40:	66 26 8b 0d 2c 00 00 	mov    cx,WORD PTR es:0x2c
   45c47:	00 
   45c48:	eb 17                	jmp    0x45c61
   45c4a:	66 8c da             	mov    dx,ds
   45c4d:	66 b9 24 00          	mov    cx,0x24
   45c51:	8e d9                	mov    ds,ecx
   45c53:	66 b9 2c 00          	mov    cx,0x2c
   45c57:	8e da                	mov    ds,edx
   45c59:	66 bb 17 00          	mov    bx,0x17
   45c5d:	b0 00                	mov    al,0x0
   45c5f:	b4 00                	mov    ah,0x0
   45c61:	a2 96 c0 01 00       	mov    ds:0x1c096,al
   45c66:	88 25 97 c0 01 00    	mov    BYTE PTR ds:0x1c097,ah
   45c6c:	8e c3                	mov    es,ebx
   45c6e:	66 26 8c 1d a9 5d 03 	data16 mov WORD PTR es:0x35da9,ds
   45c75:	00 
   45c76:	89 35 99 c0 01 00    	mov    DWORD PTR ds:0x1c099,esi
   45c7c:	66 89 0d 9d c0 01 00 	mov    WORD PTR ds:0x1c09d,cx
   45c83:	56                   	push   esi
   45c84:	66 8e 05 74 c0 01 00 	data16 mov es,WORD PTR ds:0x1c074
   45c8b:	3e ba b0 05 02 00    	ds mov edx,0x205b0
   45c91:	83 c2 0f             	add    edx,0xf
   45c94:	80 e2 f0             	and    dl,0xf0
   45c97:	29 c9                	sub    ecx,ecx
   45c99:	26 8a 4f ff          	mov    cl,BYTE PTR es:[edi-0x1]
   45c9d:	fc                   	cld    
   45c9e:	b0 20                	mov    al,0x20
   45ca0:	f3 ae                	repz scas al,BYTE PTR es:[edi]
   45ca2:	8d 77 ff             	lea    esi,[edi-0x1]
   45ca5:	89 d7                	mov    edi,edx
   45ca7:	66 8c c3             	mov    bx,es
   45caa:	66 8c da             	mov    dx,ds
   45cad:	8e db                	mov    ds,ebx
   45caf:	8e c2                	mov    es,edx
   45cb1:	74 03                	je     0x45cb6
   45cb3:	41                   	inc    ecx
   45cb4:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   45cb6:	28 c0                	sub    al,al
   45cb8:	aa                   	stos   BYTE PTR es:[edi],al
   45cb9:	aa                   	stos   BYTE PTR es:[edi],al
   45cba:	5e                   	pop    esi
   45cbb:	4f                   	dec    edi
   45cbc:	57                   	push   edi
   45cbd:	52                   	push   edx
   45cbe:	26 66 8e 1d 9d c0 01 	data16 mov ds,WORD PTR es:0x1c09d
   45cc5:	00 
   45cc6:	29 ed                	sub    ebp,ebp
   45cc8:	8b 06                	mov    eax,DWORD PTR [esi]
   45cca:	0d 20 20 20 20       	or     eax,0x20202020
   45ccf:	3d 6e 6f 38 37       	cmp    eax,0x37386f6e
   45cd4:	75 07                	jne    0x45cdd
   45cd6:	80 7e 04 3d          	cmp    BYTE PTR [esi+0x4],0x3d
   45cda:	75 01                	jne    0x45cdd
   45cdc:	45                   	inc    ebp
   45cdd:	80 3e 00             	cmp    BYTE PTR [esi],0x0
   45ce0:	ac                   	lods   al,BYTE PTR ds:[esi]
   45ce1:	75 fa                	jne    0x45cdd
   45ce3:	80 3e 00             	cmp    BYTE PTR [esi],0x0
   45ce6:	75 e0                	jne    0x45cc8
   45ce8:	ac                   	lods   al,BYTE PTR ds:[esi]
   45ce9:	46                   	inc    esi
   45cea:	46                   	inc    esi
   45ceb:	80 3e 00             	cmp    BYTE PTR [esi],0x0
   45cee:	a4                   	movs   BYTE PTR es:[edi],BYTE PTR ds:[esi]
   45cef:	75 fa                	jne    0x45ceb
   45cf1:	1f                   	pop    ds
   45cf2:	5e                   	pop    esi
   45cf3:	89 e3                	mov    ebx,esp
   45cf5:	66 89 2d 94 c0 01 00 	mov    WORD PTR ds:0x1c094,bp
   45cfc:	89 3d 78 c0 01 00    	mov    DWORD PTR ds:0x1c078,edi
   45d02:	89 1d 64 c0 01 00    	mov    DWORD PTR ds:0x1c064,ebx
   45d08:	3e b9 b0 05 02 00    	ds mov ecx,0x205b0
   45d0e:	3e bf 74 c3 01 00    	ds mov edi,0x1c374
   45d14:	29 f9                	sub    ecx,edi
   45d16:	80 3d 96 c0 01 00 01 	cmp    BYTE PTR ds:0x1c096,0x1
   45d1d:	75 0d                	jne    0x45d2c
   45d1f:	81 f9 00 10 00 00    	cmp    ecx,0x1000
   45d25:	76 05                	jbe    0x45d2c
   45d27:	b9 00 10 00 00       	mov    ecx,0x1000
   45d2c:	88 ca                	mov    dl,cl
   45d2e:	c1 e9 02             	shr    ecx,0x2
   45d31:	29 c0                	sub    eax,eax
   45d33:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   45d35:	88 d1                	mov    cl,dl
   45d37:	80 e1 03             	and    cl,0x3
   45d3a:	f3 aa                	rep stos BYTE PTR es:[edi],al
   45d3c:	3e b8 b0 05 02 00    	ds mov eax,0x205b0
   45d42:	83 c0 0f             	add    eax,0xf
   45d45:	24 f0                	and    al,0xf0
   45d47:	a3 6c c0 01 00       	mov    ds:0x1c06c,eax
   45d4c:	89 35 70 c0 01 00    	mov    DWORD PTR ds:0x1c070,esi
   45d52:	b8 ff 00 00 00       	mov    eax,0xff
   45d57:	e8 72 12 00 00       	call   0x46fce
   45d5c:	29 ed                	sub    ebp,ebp
   45d5e:	e8 1c 12 00 00       	call   0x46f7f
   45d63:	eb 23                	jmp    0x45d88

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00046f7f <.data+0x36f7f>:
   46f7f:	52                   	push   edx
   46f80:	55                   	push   ebp
   46f81:	89 e5                	mov    ebp,esp
   46f83:	8b 15 80 c0 01 00    	mov    edx,DWORD PTR ds:0x1c080
   46f89:	83 c2 03             	add    edx,0x3
   46f8c:	80 e2 fc             	and    dl,0xfc
   46f8f:	e8 ca 0e 00 00       	call   0x47e5e
   46f94:	39 c2                	cmp    edx,eax
   46f96:	73 08                	jae    0x46fa0
   46f98:	89 d0                	mov    eax,edx
   46f9a:	29 c4                	sub    esp,eax
   46f9c:	89 e0                	mov    eax,esp
   46f9e:	eb 02                	jmp    0x46fa2
   46fa0:	31 c0                	xor    eax,eax
   46fa2:	8b 15 80 c0 01 00    	mov    edx,DWORD PTR ds:0x1c080
   46fa8:	01 d0                	add    eax,edx
   46faa:	a3 84 c0 01 00       	mov    ds:0x1c084,eax
   46faf:	e8 0f 28 00 00       	call   0x497c3
   46fb4:	8b 15 a0 05 02 00    	mov    edx,DWORD PTR ds:0x205a0
   46fba:	a1 9c 05 02 00       	mov    eax,ds:0x2059c
   46fbf:	e8 4c 90 fc ff       	call   0x10010
   46fc4:	e8 51 ef ff ff       	call   0x45f1a
   46fc9:	89 ec                	mov    esp,ebp
   46fcb:	5d                   	pop    ebp
   46fcc:	5a                   	pop    edx
   46fcd:	c3                   	ret    
   46fce:	56                   	push   esi
   46fcf:	57                   	push   edi
   46fd0:	53                   	push   ebx
   46fd1:	52                   	push   edx
   46fd2:	06                   	push   es
   46fd3:	89 c2                	mov    edx,eax
   46fd5:	3e be 5a c3 01 00    	ds mov esi,0x1c35a
   46fdb:	3e bf 6c c3 01 00    	ds mov edi,0x1c36c
   46fe1:	89 fb                	mov    ebx,edi
   46fe3:	88 d0                	mov    al,dl
   46fe5:	39 fe                	cmp    esi,edi
   46fe7:	73 14                	jae    0x46ffd
   46fe9:	80 3e 02             	cmp    BYTE PTR [esi],0x2
   46fec:	74 0a                	je     0x46ff8
   46fee:	38 46 01             	cmp    BYTE PTR [esi+0x1],al
   46ff1:	77 05                	ja     0x46ff8
   46ff3:	89 f3                	mov    ebx,esi
   46ff5:	8a 46 01             	mov    al,BYTE PTR [esi+0x1]
   46ff8:	83 c6 06             	add    esi,0x6
   46ffb:	eb e8                	jmp    0x46fe5
   46ffd:	39 fb                	cmp    ebx,edi
   46fff:	74 12                	je     0x47013
   47001:	8b 43 02             	mov    eax,DWORD PTR [ebx+0x2]
   47004:	09 c0                	or     eax,eax
   47006:	74 06                	je     0x4700e
   47008:	1e                   	push   ds
   47009:	07                   	pop    es
   4700a:	52                   	push   edx
   4700b:	ff d0                	call   eax
   4700d:	5a                   	pop    edx
   4700e:	c6 03 02             	mov    BYTE PTR [ebx],0x2
   47011:	eb c2                	jmp    0x46fd5
   47013:	07                   	pop    es
   47014:	5a                   	pop    edx
   47015:	5b                   	pop    ebx
   47016:	5f                   	pop    edi
   47017:	5e                   	pop    esi
   47018:	c3                   	ret    

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
