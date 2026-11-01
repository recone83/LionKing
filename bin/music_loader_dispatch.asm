
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00036e34 <.data+0x26e34>:
   36e34:	56                   	push   esi
   36e35:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   36e39:	8b 74 24 08          	mov    esi,DWORD PTR [esp+0x8]
   36e3d:	6a 62                	push   0x62
   36e3f:	a3 dc 00 02 00       	mov    ds:0x200dc,eax
   36e44:	c7 40 01 00 00 00 00 	mov    DWORD PTR [eax+0x1],0x0
   36e4b:	89 35 cc 00 02 00    	mov    DWORD PTR ds:0x200cc,esi
   36e51:	e8 aa ed ff ff       	call   0x35c00
   36e56:	83 c4 04             	add    esp,0x4
   36e59:	68 03 03 00 00       	push   0x303
   36e5e:	a3 d4 00 02 00       	mov    ds:0x200d4,eax
   36e63:	e8 98 ed ff ff       	call   0x35c00
   36e68:	83 c4 04             	add    esp,0x4
   36e6b:	68 00 01 00 00       	push   0x100
   36e70:	a3 d0 00 02 00       	mov    ds:0x200d0,eax
   36e75:	e8 86 ed ff ff       	call   0x35c00
   36e7a:	83 c4 04             	add    esp,0x4
   36e7d:	a3 d8 00 02 00       	mov    ds:0x200d8,eax
   36e82:	e8 91 f2 ff ff       	call   0x36118
   36e87:	89 c6                	mov    esi,eax
   36e89:	85 c0                	test   eax,eax
   36e8b:	75 1b                	jne    0x36ea8
   36e8d:	e8 96 f5 ff ff       	call   0x36428
   36e92:	89 c6                	mov    esi,eax
   36e94:	85 c0                	test   eax,eax
   36e96:	75 10                	jne    0x36ea8
   36e98:	e8 bb fb ff ff       	call   0x36a58
   36e9d:	89 c6                	mov    esi,eax
   36e9f:	85 c0                	test   eax,eax
   36ea1:	75 05                	jne    0x36ea8
   36ea3:	e8 34 ff ff ff       	call   0x36ddc
   36ea8:	8b 15 d4 00 02 00    	mov    edx,DWORD PTR ds:0x200d4
   36eae:	52                   	push   edx
   36eaf:	e8 68 ed ff ff       	call   0x35c1c
   36eb4:	83 c4 04             	add    esp,0x4
   36eb7:	8b 1d d0 00 02 00    	mov    ebx,DWORD PTR ds:0x200d0
   36ebd:	53                   	push   ebx
   36ebe:	e8 59 ed ff ff       	call   0x35c1c
   36ec3:	83 c4 04             	add    esp,0x4
   36ec6:	8b 0d d8 00 02 00    	mov    ecx,DWORD PTR ds:0x200d8
   36ecc:	51                   	push   ecx
   36ecd:	e8 4a ed ff ff       	call   0x35c1c
   36ed2:	83 c4 04             	add    esp,0x4
   36ed5:	89 f0                	mov    eax,esi
   36ed7:	5e                   	pop    esi
   36ed8:	c3                   	ret    
   36ed9:	8d 40 00             	lea    eax,[eax+0x0]
   36edc:	56                   	push   esi
   36edd:	57                   	push   edi
   36ede:	55                   	push   ebp
   36edf:	83 ec 08             	sub    esp,0x8
   36ee2:	8b 7c 24 18          	mov    edi,DWORD PTR [esp+0x18]
   36ee6:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
   36eea:	6a 5c                	push   0x5c
   36eec:	a3 04 05 02 00       	mov    ds:0x20504,eax
   36ef1:	e8 0a ed ff ff       	call   0x35c00
   36ef6:	89 c6                	mov    esi,eax
   36ef8:	83 c4 04             	add    esp,0x4
   36efb:	89 c5                	mov    ebp,eax
   36efd:	85 c0                	test   eax,eax
   36eff:	75 0f                	jne    0x36f10
   36f01:	c7 05 08 05 02 00 ff 	mov    DWORD PTR ds:0x20508,0xffffffff
   36f08:	ff ff ff 
   36f0b:	e9 eb 00 00 00       	jmp    0x36ffb

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00037d3c <.data+0x27d3c>:
   37d3c:	8b 4c 24 04          	mov    ecx,DWORD PTR [esp+0x4]
   37d40:	8b 5c 24 08          	mov    ebx,DWORD PTR [esp+0x8]
   37d44:	89 da                	mov    edx,ebx
   37d46:	c6 43 5a 7d          	mov    BYTE PTR [ebx+0x5a],0x7d
   37d4a:	89 c8                	mov    eax,ecx
   37d4c:	c6 43 5b 06          	mov    BYTE PTR [ebx+0x5b],0x6
   37d50:	e8 bb f2 ff ff       	call   0x37010
   37d55:	85 c0                	test   eax,eax
   37d57:	7d 01                	jge    0x37d5a
   37d59:	c3                   	ret    
   37d5a:	89 da                	mov    edx,ebx
   37d5c:	89 c8                	mov    eax,ecx
   37d5e:	e8 8d f4 ff ff       	call   0x371f0
   37d63:	85 c0                	test   eax,eax
   37d65:	7d 01                	jge    0x37d68
   37d67:	c3                   	ret    
   37d68:	89 da                	mov    edx,ebx
   37d6a:	89 c8                	mov    eax,ecx
   37d6c:	e8 cb fb ff ff       	call   0x3793c
   37d71:	85 c0                	test   eax,eax
   37d73:	7d 01                	jge    0x37d76
   37d75:	c3                   	ret    
   37d76:	89 da                	mov    edx,ebx
   37d78:	89 c8                	mov    eax,ecx
   37d7a:	e8 ad fc ff ff       	call   0x37a2c
   37d7f:	89 c1                	mov    ecx,eax
   37d81:	85 c0                	test   eax,eax
   37d83:	7d 01                	jge    0x37d86
   37d85:	c3                   	ret    
   37d86:	89 d8                	mov    eax,ebx
   37d88:	e8 57 ff ff ff       	call   0x37ce4
   37d8d:	89 c8                	mov    eax,ecx
   37d8f:	c3                   	ret    
   37d90:	56                   	push   esi
   37d91:	57                   	push   edi
   37d92:	55                   	push   ebp
   37d93:	83 ec 04             	sub    esp,0x4
   37d96:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
   37d9a:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
   37d9e:	6a 5c                	push   0x5c
   37da0:	a3 04 05 02 00       	mov    ds:0x20504,eax
   37da5:	e8 56 de ff ff       	call   0x35c00
   37daa:	89 c7                	mov    edi,eax
   37dac:	83 c4 04             	add    esp,0x4
   37daf:	89 c5                	mov    ebp,eax
   37db1:	85 c0                	test   eax,eax
   37db3:	75 0f                	jne    0x37dc4
   37db5:	c7 05 08 05 02 00 ff 	mov    DWORD PTR ds:0x20508,0xffffffff
   37dbc:	ff ff ff 
   37dbf:	e9 c7 00 00 00       	jmp    0x37e8b
   37dc4:	bb 5c 00 00 00       	mov    ebx,0x5c
   37dc9:	31 d2                	xor    edx,edx
   37dcb:	e8 a0 ef 00 00       	call   0x46d70
   37dd0:	ba a8 01 00 00       	mov    edx,0x1a8
   37dd5:	89 f0                	mov    eax,esi
   37dd7:	e8 03 e3 00 00       	call   0x460df
   37ddc:	89 c6                	mov    esi,eax
   37dde:	85 c0                	test   eax,eax
   37de0:	75 16                	jne    0x37df8
   37de2:	bb fe ff ff ff       	mov    ebx,0xfffffffe
   37de7:	31 fd                	xor    ebp,edi
   37de9:	89 1d 08 05 02 00    	mov    DWORD PTR ds:0x20508,ebx
   37def:	89 e8                	mov    eax,ebp
   37df1:	83 c4 04             	add    esp,0x4
   37df4:	5d                   	pop    ebp
   37df5:	5f                   	pop    edi
   37df6:	5e                   	pop    esi
   37df7:	c3                   	ret    
   37df8:	bb 01 00 00 00       	mov    ebx,0x1
   37dfd:	ba 03 00         	mov    edx,0x3

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00039230 <.data+0x29230>:
   39230:	56                   	push   esi
   39231:	57                   	push   edi
   39232:	8b 74 24 10          	mov    esi,DWORD PTR [esp+0x10]
   39236:	68 00 01 00 00       	push   0x100
   3923b:	e8 c0 c9 ff ff       	call   0x35c00
   39240:	83 c4 04             	add    esp,0x4
   39243:	68 00 02 00 00       	push   0x200
   39248:	a3 98 02 02 00       	mov    ds:0x20298,eax
   3924d:	e8 ae c9 ff ff       	call   0x35c00
   39252:	83 c4 04             	add    esp,0x4
   39255:	68 00 02 00 00       	push   0x200
   3925a:	a3 8c 02 02 00       	mov    ds:0x2028c,eax
   3925f:	e8 9c c9 ff ff       	call   0x35c00
   39264:	83 c4 04             	add    esp,0x4
   39267:	a3 94 02 02 00       	mov    ds:0x20294,eax
   3926c:	89 35 9c 02 02 00    	mov    DWORD PTR ds:0x2029c,esi
   39272:	c7 46 01 00 00 00 00 	mov    DWORD PTR [esi+0x1],0x0
   39279:	31 d2                	xor    edx,edx
   3927b:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   3927f:	89 15 88 02 02 00    	mov    DWORD PTR ds:0x20288,edx
   39285:	a3 90 02 02 00       	mov    ds:0x20290,eax
   3928a:	e8 11 ec ff ff       	call   0x37ea0
   3928f:	89 c6                	mov    esi,eax
   39291:	85 c0                	test   eax,eax
   39293:	7c 44                	jl     0x392d9
   39295:	e8 3a ee ff ff       	call   0x380d4
   3929a:	89 c6                	mov    esi,eax
   3929c:	85 c0                	test   eax,eax
   3929e:	7c 39                	jl     0x392d9
   392a0:	e8 23 f0 ff ff       	call   0x382c8
   392a5:	89 c6                	mov    esi,eax
   392a7:	85 c0                	test   eax,eax
   392a9:	7c 2e                	jl     0x392d9
   392ab:	e8 d0 fc ff ff       	call   0x38f80
   392b0:	89 c6                	mov    esi,eax
   392b2:	85 c0                	test   eax,eax
   392b4:	7c 23                	jl     0x392d9
   392b6:	e8 1d ff ff ff       	call   0x391d8
   392bb:	8b 1d 88 02 02 00    	mov    ebx,DWORD PTR ds:0x20288
   392c1:	a1 9c 02 02 00       	mov    eax,ds:0x2029c
   392c6:	43                   	inc    ebx
   392c7:	8a 50 29             	mov    dl,BYTE PTR [eax+0x29]
   392ca:	39 da                	cmp    edx,ebx
   392cc:	7e 0b                	jle    0x392d9
   392ce:	8a 15 88 02 02 00    	mov    dl,BYTE PTR ds:0x20288
   392d4:	fe c2                	inc    dl
   392d6:	88 50 29             	mov    BYTE PTR [eax+0x29],dl
   392d9:	8b 1d 98 02 02 00    	mov    ebx,DWORD PTR ds:0x20298
   392df:	53                   	push   ebx
   392e0:	e8 37 c9 ff ff       	call   0x35c1c
   392e5:	83 c4 04             	add    esp,0x4
   392e8:	8b 0d 8c 02 02 00    	mov    ecx,DWORD PTR ds:0x2028c
   392ee:	51                   	push   ecx
   392ef:	e8 28 c9 ff ff       	call   0x35c1c
   392f4:	83 c4 04             	add    esp,0x4
   392f7:	8b 3d 94 02 02 00    	mov    edi,DWORD PTR ds:0x20294
   392fd:	57                   	push   edi
   392fe:	e8 19 c9 ff ff       	call   0x35c1c
   39303:	83 c4 04             	add    esp,0x4
   39306:	89 f0                	mov    eax,esi
   39308:	5f                   	pop    edi
   39309:	5e                   	pop    esi
   3930a:	c3                   	ret    
   3930b:	90                   	nop
   3930c:	56                   	push   esi
   3930d:	57                   	push   edi
   3930e:	55                   	push   ebp
   3930f:	83 ec 08             	sub    esp,0x8
   39312:	8b 74 24 18          	mov    esi,DWORD PTR [esp+0x18]
   39316:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
   3931a:	6a 5c                	push   0x5c
   3931c:	a3 04 05 02 00       	mov    ds:0x20504,eax
   39321:	e8 da c8 ff ff       	call   0x35c00
   39326:	89 c7                	mov    edi,eax
   39328:	83 c4 04             	add    esp,0x4
   3932b:	89 c5                	mov    ebp,eax
   3932d:	85 c0                	test   eax,eax
   3932f:	75                 	jne    0x39340

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00039ea0 <.data+0x29ea0>:
   39ea0:	56                   	push   esi
   39ea1:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   39ea5:	8b 74 24 08          	mov    esi,DWORD PTR [esp+0x8]
   39ea9:	68 f1 01 00 00       	push   0x1f1
   39eae:	a3 ac 02 02 00       	mov    ds:0x202ac,eax
   39eb3:	c7 40 01 00 00 00 00 	mov    DWORD PTR [eax+0x1],0x0
   39eba:	31 d2                	xor    edx,edx
   39ebc:	89 35 a4 02 02 00    	mov    DWORD PTR ds:0x202a4,esi
   39ec2:	89 15 b4 02 02 00    	mov    DWORD PTR ds:0x202b4,edx
   39ec8:	e8 33 bd ff ff       	call   0x35c00
   39ecd:	83 c4 04             	add    esp,0x4
   39ed0:	68 00 01 00 00       	push   0x100
   39ed5:	a3 b0 02 02 00       	mov    ds:0x202b0,eax
   39eda:	e8 21 bd ff ff       	call   0x35c00
   39edf:	83 c4 04             	add    esp,0x4
   39ee2:	a3 a8 02 02 00       	mov    ds:0x202a8,eax
   39ee7:	e8 54 f5 ff ff       	call   0x39440
   39eec:	89 c6                	mov    esi,eax
   39eee:	85 c0                	test   eax,eax
   39ef0:	75 26                	jne    0x39f18
   39ef2:	e8 a5 f6 ff ff       	call   0x3959c
   39ef7:	89 c6                	mov    esi,eax
   39ef9:	85 c0                	test   eax,eax
   39efb:	75 1b                	jne    0x39f18
   39efd:	e8 fe f7 ff ff       	call   0x39700
   39f02:	89 c6                	mov    esi,eax
   39f04:	85 c0                	test   eax,eax
   39f06:	75 10                	jne    0x39f18
   39f08:	e8 93 fc ff ff       	call   0x39ba0
   39f0d:	89 c6                	mov    esi,eax
   39f0f:	85 c0                	test   eax,eax
   39f11:	75 05                	jne    0x39f18
   39f13:	e8 30 ff ff ff       	call   0x39e48
   39f18:	8b 1d b0 02 02 00    	mov    ebx,DWORD PTR ds:0x202b0
   39f1e:	53                   	push   ebx
   39f1f:	e8 f8 bc ff ff       	call   0x35c1c
   39f24:	83 c4 04             	add    esp,0x4
   39f27:	8b 0d a8 02 02 00    	mov    ecx,DWORD PTR ds:0x202a8
   39f2d:	51                   	push   ecx
   39f2e:	e8 e9 bc ff ff       	call   0x35c1c
   39f33:	83 c4 04             	add    esp,0x4
   39f36:	89 f0                	mov    eax,esi
   39f38:	5e                   	pop    esi
   39f39:	c3                   	ret    
   39f3a:	8b c0                	mov    eax,eax
   39f3c:	56                   	push   esi
   39f3d:	57                   	push   edi
   39f3e:	55                   	push   ebp
   39f3f:	83 ec 08             	sub    esp,0x8
   39f42:	8b 7c 24 18          	mov    edi,DWORD PTR [esp+0x18]
   39f46:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
   39f4a:	6a 5c                	push   0x5c
   39f4c:	a3 04 05 02 00       	mov    ds:0x20504,eax
   39f51:	e8 aa bc ff ff       	call   0x35c00
   39f56:	89 c6                	mov    esi,eax
   39f58:	83 c4 04             	add    esp,0x4
   39f5b:	89 c5                	mov    ebp,eax
   39f5d:	85 c0                	test   eax,eax
   39f5f:	75                 	jne    0x39f70

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0003ae44 <.data+0x2ae44>:
   3ae44:	8b 4c 24 04          	mov    ecx,DWORD PTR [esp+0x4]
   3ae48:	8b 5c 24 08          	mov    ebx,DWORD PTR [esp+0x8]
   3ae4c:	89 da                	mov    edx,ebx
   3ae4e:	c6 43 5a 7d          	mov    BYTE PTR [ebx+0x5a],0x7d
   3ae52:	89 c8                	mov    eax,ecx
   3ae54:	c6 43 5b 06          	mov    BYTE PTR [ebx+0x5b],0x6
   3ae58:	e8 13 f2 ff ff       	call   0x3a070
   3ae5d:	85 c0                	test   eax,eax
   3ae5f:	74 01                	je     0x3ae62
   3ae61:	c3                   	ret    
   3ae62:	89 da                	mov    edx,ebx
   3ae64:	89 c8                	mov    eax,ecx
   3ae66:	e8 a5 f3 ff ff       	call   0x3a210
   3ae6b:	85 c0                	test   eax,eax
   3ae6d:	74 01                	je     0x3ae70
   3ae6f:	c3                   	ret    
   3ae70:	89 da                	mov    edx,ebx
   3ae72:	89 c8                	mov    eax,ecx
   3ae74:	e8 df fa ff ff       	call   0x3a958
   3ae79:	85 c0                	test   eax,eax
   3ae7b:	74 01                	je     0x3ae7e
   3ae7d:	c3                   	ret    
   3ae7e:	89 da                	mov    edx,ebx
   3ae80:	89 c8                	mov    eax,ecx
   3ae82:	e8 1d fd ff ff       	call   0x3aba4
   3ae87:	85 c0                	test   eax,eax
   3ae89:	74 01                	je     0x3ae8c
   3ae8b:	c3                   	ret    
   3ae8c:	89 d8                	mov    eax,ebx
   3ae8e:	e8 51 ff ff ff       	call   0x3ade4
   3ae93:	31 c0                	xor    eax,eax
   3ae95:	c3                   	ret    
   3ae96:	8b c0                	mov    eax,eax
   3ae98:	56                   	push   esi
   3ae99:	57                   	push   edi
   3ae9a:	55                   	push   ebp
   3ae9b:	83 ec 10             	sub    esp,0x10
   3ae9e:	8b 7c 24 20          	mov    edi,DWORD PTR [esp+0x20]
   3aea2:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
   3aea6:	6a 5c                	push   0x5c
   3aea8:	a3 04 05 02 00       	mov    ds:0x20504,eax
   3aead:	e8 4e ad ff ff       	call   0x35c00
   3aeb2:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
   3aeb6:	83 c4 04             	add    esp,0x4
   3aeb9:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
   3aebd:	85 c0                	test   eax,eax
   3aebf:	75 0f                	jne    0x3aed0
   3aec1:	c7 05 08 05 02 00 ff 	mov    DWORD PTR ds:0x20508,0xffffffff
   3aec8:	ff ff ff 
   3aecb:	e9 18 01 00 00       	jmp    0x3afe8
   3aed0:	bb 5c 00 00 00       	mov    ebx,0x5c
   3aed5:	31 d2                	xor    edx,edx
   3aed7:	e8 94 be 00 00       	call   0x46d70
   3aedc:	ba b8 01 00 00       	mov    edx,0x1b8
   3aee1:	89 f8                	mov    eax,edi
   3aee3:	e8 f7 b1 00 00       	call   0x460df
   3aee8:	89 c5                	mov    ebp,eax
   3aeea:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
   3aeee:	85 c0                	test   eax,eax
   3aef0:	75 11                	jne    0x3af03
   3aef2:	c7 05 08 05 02 00 fe 	mov    DWORD PTR ds:0x20508,0xfffffffe
   3aef9:	ff ff ff 
   3aefc:	83 c4 10             	add    esp,0x10
   3aeff:	5d                   	pop    ebp

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0003c384 <.data+0x2c384>:
   3c384:	04 00                	add    al,0x0
   3c386:	00 31                	add    BYTE PTR [ecx],dh
   3c388:	db c6                	fcmovnb st,st(6)
   3c38a:	07                   	pop    es
   3c38b:	00 e8                	add    al,ch
   3c38d:	26 9e                	es sahf 
   3c38f:	00 00                	add    BYTE PTR [eax],al
   3c391:	89 f1                	mov    ecx,esi
   3c393:	bb 01 00 00 00       	mov    ebx,0x1
   3c398:	ba 04 00 00 00       	mov    edx,0x4
   3c39d:	89 e0                	mov    eax,esp
   3c39f:	e8 3f 9f 00 00       	call   0x462e3
   3c3a4:	8b 14 24             	mov    edx,DWORD PTR [esp]
   3c3a7:	81 fa 4d 2e 4b 2e    	cmp    edx,0x2e4b2e4d
   3c3ad:	74 10                	je     0x3c3bf
   3c3af:	81 fa 46 4c 54 34    	cmp    edx,0x34544c46
   3c3b5:	74 08                	je     0x3c3bf
   3c3b7:	81 fa 4d 21 4b 21    	cmp    edx,0x214b214d
   3c3bd:	75 41                	jne    0x3c400
   3c3bf:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   3c3c3:	8b 4c 24 0c          	mov    ecx,DWORD PTR [esp+0xc]
   3c3c7:	31 db                	xor    ebx,ebx
   3c3c9:	31 d2                	xor    edx,edx
   3c3cb:	c6 45 00 01          	mov    BYTE PTR [ebp+0x0],0x1
   3c3cf:	e8 e3 9d 00 00       	call   0x461b7
   3c3d4:	bb 01 00 00 00       	mov    ebx,0x1
   3c3d9:	ba 14 00 00 00       	mov    edx,0x14
   3c3de:	8d 45 09             	lea    eax,[ebp+0x9]
   3c3e1:	be 40 a7 01 00       	mov    esi,0x1a740
   3c3e6:	e8 f8 9e 00 00       	call   0x462e3
   3c3eb:	b9 04 00 00 00       	mov    ecx,0x4
   3c3f0:	c6 45 1d 00          	mov    BYTE PTR [ebp+0x1d],0x0
   3c3f4:	8d 7d 2a             	lea    edi,[ebp+0x2a]
   3c3f7:	c6 45 29 04          	mov    BYTE PTR [ebp+0x29],0x4
   3c3fb:	e9 5e 01 00 00       	jmp    0x3c55e
   3c400:	8d 47 2a             	lea    eax,[edi+0x2a]
   3c403:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
   3c407:	8d 47 09             	lea    eax,[edi+0x9]
   3c40a:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
   3c40e:	81 fa 46 4c 54 38    	cmp    edx,0x38544c46
   3c414:	75 3a                	jne    0x3c450
   3c416:	89 f0                	mov    eax,esi
   3c418:	31 db                	xor    ebx,ebx
   3c41a:	31 d2                	xor    edx,edx
   3c41c:	c6 07 05             	mov    BYTE PTR [edi],0x5
   3c41f:	e8 93 9d 00 00       	call   0x461b7
   3c424:	89 f1                	mov    ecx,esi
   3c426:	bb 01 00 00 00       	mov    ebx,0x1
   3c42b:	ba 14 00 00 00       	mov    edx,0x14
   3c430:	8b 44 24 08          	mov    eax,DWORD PTR [esp+0x8]
   3c434:	be 40 a7 01 00       	mov    esi,0x1a740
   3c439:	e8 a5 9e 00 00       	call   0x462e3
   3c43e:	c6 47 1d 00          	mov    BYTE PTR [edi+0x1d],0x0
   3c442:	b9 08 00 00 00       	mov    ecx,0x8
   3c447:	c6 47 29 08          	mov    BYTE PTR [edi+0x29],0x8
   3c44b:	e9 0a 01 00 00       	jmp    0x3c55a

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
   3706f:	8a 81 06 01 02 00    	mov    al,BYTE PTR [ecx+0x20106]
   37075:	83 f8 07             	cmp    eax,0x7
   37078:	74 05                	je     0x3707f
   3707a:	83 f8 08             	cmp    eax,0x8
   3707d:	75 04                	jne    0x37083
   3707f:	31 c0                	xor    eax,eax
   37081:	eb 10                	jmp    0x37093
   37083:	83 f8 07             	cmp    eax,0x7
   37086:	7d 05                	jge    0x3708d
   37088:	83 e8 07             	sub    eax,0x7
   3708b:	eb 03                	jmp    0x37090
   3708d:	83 e8 08             	sub    eax,0x8
   37090:	8d 04 c0             	lea    eax,[eax+eax*8]
   37093:	46                   	inc    esi
   37094:	41                   	inc    ecx
   37095:	88 46 29             	mov    BYTE PTR [esi+0x29],al
   37098:	83 f9 20             	cmp    ecx,0x20
   3709b:	7c d0                	jl     0x3706d
   3709d:	a0 02 01 02 00       	mov    al,ds:0x20102
   370a2:	8b 54 24 28          	mov    edx,DWORD PTR [esp+0x28]
   370a6:	a2 25 02 02 00       	mov    ds:0x20225,al
   370ab:	88 42 4a             	mov    BYTE PTR [edx+0x4a],al
   370ae:	31 c0                	xor    eax,eax
   370b0:	6a 41                	push   0x41
   370b2:	a0 02 01 02 00       	mov    al,ds:0x20102
   370b7:	50                   	push   eax
   370b8:	e8 4f eb ff ff       	call   0x35c0c
   370bd:	83 c4 08             	add    esp,0x8
   370c0:	8b 54 24 28          	mov    edx,DWORD PTR [esp+0x28]
   370c4:	89 42 4b             	mov    DWORD PTR [edx+0x4b],eax
   370c7:	85 c0                	test   eax,eax
   370c9:	75 0a                	jne    0x370d5
   370cb:	b8 ff ff ff ff       	mov    eax,0xffffffff
   370d0:	e9 10 01 00 00       	jmp    0x371e5
   370d5:	31 d2                	xor    edx,edx
   370d7:	8a 15 25 02 02 00    	mov    dl,BYTE PTR ds:0x20225
   370dd:	89 d0                	mov    eax,edx
   370df:	c1 e0 06             	shl    eax,0x6
   370e2:	01 d0                	add    eax,edx
   370e4:	8b 54 24 28          	mov    edx,DWORD PTR [esp+0x28]
   370e8:	8b 5a 01             	mov    ebx,DWORD PTR [edx+0x1]
   370eb:	31 ff                	xor    edi,edi
   370ed:	01 c3                	add    ebx,eax
   370ef:	31 f6                	xor    esi,esi
   370f1:	89 5a 01             	mov    DWORD PTR [edx+0x1],ebx
   370f4:	e9 db 00 00 00       	jmp    0x371d4
   370f9:	bb 01 00 00 00       	mov    ebx,0x1
   370fe:	ba 25 00 00 00       	mov    edx,0x25
   37103:	89 e0                	mov    eax,esp
   37105:	89 e9                	mov    ecx,ebp
   37107:	e8 d7 f1 00 00       	call   0x462e3
   3710c:	83 f8 01             	cmp    eax,0x1
   3710f:	74 0e                	je     0x3711f
   37111:	b8 fe ff ff ff       	mov    eax,0xfffffffe
   37116:	83 c4 2c             	add    esp,0x2c
   37119:	5d                   	pop    ebp
   3711a:	5f                   	pop    edi
   3711b:	5e                   	pop    esi
   3711c:	59                   	pop    ecx
   3711d:	5b                   	pop    ebx
   3711e:	c3                   	ret    
   3711f:	8b 4c 24 28          	mov    ecx,DWORD PTR [esp+0x28]
   37123:	8b 49 4b             	mov    ecx,DWORD PTR [ecx+0x4b]
   37126:	bb 16 00 00 00       	mov    ebx,0x16
   3712b:	01 f1                	add    ecx,esi
   3712d:	89 e2                	mov    edx,esp
   3712f:	01 c8                	add    eax,ecx
   37131:	c6 01 00             	mov    BYTE PTR [ecx],0x0
   37134:	e8 13 fd 00 00       	call   0x46e4c
   37139:	bb 0c 00 00 00       	mov    ebx,0xc
   3713e:	89 e2                	mov    edx,esp
   37140:	8d 41 21             	lea    eax,[ecx+0x21]
   37143:	c6 41 17 00          	mov    BYTE PTR [ecx+0x17],0x0
   37147:	e8 00 fd 00 00       	call   0x46e4c
   3714c:	c6 41 2d 00          	mov    BYTE PTR [ecx+0x2d],0x0
   37150:	c7 41 2e 00 00 00 00 	mov    DWORD PTR [ecx+0x2e],0x0
   37157:	8a 44 24 22          	mov    al,BYTE PTR [esp+0x22]
   3715b:	24 0f                	and    al,0xf
   3715d:	25 ff 00 00 00       	and    eax,0xff
   37162:	31 db                	xor    ebx,ebx
   37164:	66 8b 1c 45 ec a6 01 	mov    bx,WORD PTR [eax*2+0x1a6ec]
   3716b:	00 
   3716c:	b8 80 4c 6d 00       	mov    eax,0x6d4c80
   37171:	89 c2                	mov    edx,eax
   37173:	c1 fa 1f             	sar    edx,0x1f
   37176:	f7 fb                	idiv   ebx
   37178:	66 89 41 36          	mov    WORD PTR [ecx+0x36],ax
   3717c:	8a 44 24 23          	mov    al,BYTE PTR [esp+0x23]
   37180:	88 41 38             	mov    BYTE PTR [ecx+0x38],al
   37183:	3c 40                	cmp    al,0x40
   37185:	76 04                	jbe    0x3718b
   37187:	c6 41 38 40          	mov    BYTE PTR [ecx+0x38],0x40
   3718b:	8b 44 24 16          	mov    eax,DWORD PTR [esp+0x16]
   3718f:	89 41 32             	mov    DWORD PTR [ecx+0x32],eax
   37192:	8b 44 24 1a          	mov    eax,DWORD PTR [esp+0x1a]
   37196:	89 41 39             	mov    DWORD PTR [ecx+0x39],eax
   37199:	8b 44 24 1e          	mov    eax,DWORD PTR [esp+0x1e]
   3719d:	66 3d 03 00          	cmp    ax,0x3
   371a1:	73 02                	jae    0x371a5
   371a3:	31 c0                	xor    eax,eax
   371a5:	25 ff ff 00 00       	and    eax,0xffff
   371aa:	8b 51 32             	mov    edx,DWORD PTR [ecx+0x32]
   371ad:	89 41 3d             	mov    DWORD PTR [ecx+0x3d],eax
   371b0:	39 d0                	cmp    eax,edx
   371b2:	76 03                	jbe    0x371b7
   371b4:	89 51 3d             	mov    DWORD PTR [ecx+0x3d],edx
   371b7:	8b 41 39             	mov    eax,DWORD PTR [ecx+0x39]
   371ba:	3b 41 3d             	cmp    eax,DWORD PTR [ecx+0x3d]
   371bd:	76 07                	jbe    0x371c6
   371bf:	c7 41 3d 00 00 00 00 	mov    DWORD PTR [ecx+0x3d],0x0
   371c6:	8b 41 3d             	mov    eax,DWORD PTR [ecx+0x3d]
   371c9:	85 c0                	test   eax,eax
   371cb:	75 03                	jne    0x371d0
   371cd:	89 41 39             	mov    DWORD PTR [ecx+0x39],eax
   371d0:	83 c6 41             	add    esi,0x41
   371d3:	47                   	inc    edi
   371d4:	31 c0                	xor    eax,eax
   371d6:	a0 02 01 02 00       	mov    al,ds:0x20102
   371db:	39 c7                	cmp    edi,eax
   371dd:	0f 8c 16 ff ff ff    	jl     0x370f9
   371e3:	31 c0                	xor    eax,eax
   371e5:	83 c4 2c             	add    esp,0x2c
   371e8:	5d                   	pop    ebp
   371e9:	5f                   	pop    edi
   371ea:	5e                   	pop    esi
   371eb:	59                   	pop    ecx
   371ec:	5b                   	pop    ebx
   371ed:	c3                   	ret    
   371ee:	8b c0                	mov    eax,eax
   371f0:	53                   	push   ebx
   371f1:	51                   	push   ecx
   371f2:	56                   	push   esi
   371f3:	57                   	push   edi
   371f4:	55                   	push   ebp
   371f5:	83 ec 10             	sub    esp,0x10
   371f8:	89 c7                	mov    edi,eax
   371fa:	89 d5                	mov    ebp,edx
   371fc:	68 80 00 00 00       	push   0x80
   37201:	e8 fa e9 ff ff       	call   0x35c00
   37206:	83 c4 04             	add    esp,0x4
   37209:	89 c6                	mov    esi,eax
   3720b:	89 04 24             	mov    DWORD PTR [esp],eax
   3720e:	85 c0                	test   eax,eax
   37210:	75 0a                	jne    0x3721c
   37212:	b8 ff ff ff ff       	mov    eax,0xffffffff
   37217:	e9 b4 01 00 00       	jmp    0x373d0
   3721c:	bb 01 00 00 00       	mov    ebx,0x1
   37221:	ba 80 00 00 00       	mov    edx,0x80
   37226:	89 f9                	mov    ecx,edi
   37228:	e8 b6 f0 00 00       	call   0x462e3
   3722d:	83 f8 01             	cmp    eax,0x1
   37230:	74 0e                	je     0x37240
   37232:	b8 fe ff ff ff       	mov    eax,0xfffffffe
   37237:	83 c4 10             	add    esp,0x10
   3723a:	5d                   	pop    ebp
   3723b:	5f                   	pop    edi
   3723c:	5e                   	pop    esi
   3723d:	59                   	pop    ecx
   3723e:	5b                   	pop    ebx
   3723f:	c3                   	ret    
   37240:	31 c0                	xor    eax,eax
   37242:	a0 ff 00 02 00       	mov    al,ds:0x200ff
   37247:	40                   	inc    eax
   37248:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
   3724c:	89 ea                	mov    edx,ebp
   3724e:	8a 44 24 04          	mov    al,BYTE PTR [esp+0x4]
   37252:	88 42 4f             	mov    BYTE PTR [edx+0x4f],al
   37255:	66 a1 fc 00 02 00    	mov    ax,ds:0x200fc
   3725b:	68 82 00 00 00       	push   0x82
   37260:	66 89 42 54          	mov    WORD PTR [edx+0x54],ax
   37264:	8b 54 24 08          	mov    edx,DWORD PTR [esp+0x8]
   37268:	52                   	push   edx
   37269:	e8 9e e9 ff ff       	call   0x35c0c
   3726e:	89 ea                	mov    edx,ebp
   37270:	89 42 50             	mov    DWORD PTR [edx+0x50],eax
   37273:	8b 45 50             	mov    eax,DWORD PTR [ebp+0x50]
   37276:	83 c4 08             	add    esp,0x8
   37279:	85 c0                	test   eax,eax
   3727b:	75 0e                	jne    0x3728b
   3727d:	b8 ff ff ff ff       	mov    eax,0xffffffff
   37282:	83 c4 10             	add    esp,0x10
   37285:	5d                   	pop    ebp
   37286:	5f                   	pop    edi
   37287:	5e                   	pop    esi
   37288:	59                   	pop    ecx
   37289:	5b                   	pop    ebx
   3728a:	c3                   	ret    
   3728b:	8b 54 24 04          	mov    edx,DWORD PTR [esp+0x4]
   3728f:	89 d0                	mov    eax,edx
   37291:	c1 e0 06             	shl    eax,0x6
   37294:	01 d0                	add    eax,edx
   37296:	89 ea                	mov    edx,ebp
   37298:	01 c0                	add    eax,eax
   3729a:	8b 5a 01             	mov    ebx,DWORD PTR [edx+0x1]
   3729d:	01 c3                	add    ebx,eax
   3729f:	8b 4c 24 04          	mov    ecx,DWORD PTR [esp+0x4]
   372a3:	89 5a 01             	mov    DWORD PTR [edx+0x1],ebx
   372a6:	31 d2                	xor    edx,edx
   372a8:	85 c9                	test   ecx,ecx
   372aa:	7e 18                	jle    0x372c4
   372ac:	b1 01                	mov    cl,0x1
   372ae:	89 f0                	mov    eax,esi
   372b0:	8b 74 24 04          	mov    esi,DWORD PTR [esp+0x4]
   372b4:	31 db                	xor    ebx,ebx
   372b6:	8a 18                	mov    bl,BYTE PTR [eax]
   372b8:	40                   	inc    eax
   372b9:	42                   	inc    edx
   372ba:	88 8b 26 01 02 00    	mov    BYTE PTR [ebx+0x20126],cl
   372c0:	39 f2                	cmp    edx,esi
   372c2:	7c f0                	jl     0x372b4
   372c4:	31 d2                	xor    edx,edx
   372c6:	8a 15 02 01 02 00    	mov    dl,BYTE PTR ds:0x20102
   372cc:	8d 1c d5 00 00 00 00 	lea    ebx,[edx*8+0x0]
   372d3:	01 d3                	add    ebx,edx
   372d5:	c1 e3 02             	shl    ebx,0x2
   372d8:	01 d3                	add    ebx,edx
   372da:	31 d2                	xor    edx,edx
   372dc:	66 8b 15 fc 00 02 00 	mov    dx,WORD PTR ds:0x200fc
   372e3:	8d 04 95 00 00 00 00 	lea    eax,[edx*4+0x0]
   372ea:	29 d0                	sub    eax,edx
   372ec:	c1 e0 06             	shl    eax,0x6
   372ef:	8d 93 c2 00 00 00    	lea    edx,[ebx+0xc2]
   372f5:	01 c2                	add    edx,eax
   372f7:	31 db                	xor    ebx,ebx
   372f9:	89 f8                	mov    eax,edi
   372fb:	e8 b7 ee 00 00       	call   0x461b7
   37300:	31 c0                	xor    eax,eax
   37302:	a0 fe 00 02 00       	mov    al,ds:0x200fe
   37307:	c1 e0 06             	shl    eax,0x6
   3730a:	83 c0 40             	add    eax,0x40
   3730d:	50                   	push   eax
   3730e:	e8 ed e8 ff ff       	call   0x35c00
   37313:	83 c4 04             	add    esp,0x4
   37316:	89 c6                	mov    esi,eax
   37318:	85 c0                	test   eax,eax
   3731a:	75 0e                	jne    0x3732a
   3731c:	b8 ff ff ff ff       	mov    eax,0xffffffff
   37321:	83 c4 10             	add    esp,0x10
   37324:	5d                   	pop    ebp
   37325:	5f                   	pop    edi
   37326:	5e                   	pop    esi
   37327:	59                   	pop    ecx
   37328:	5b                   	pop    ebx
   37329:	c3                   	ret    
   3732a:	31 d2                	xor    edx,edx
   3732c:	8a 15 fe 00 02 00    	mov    dl,BYTE PTR ds:0x200fe
   37332:	bb 01 00 00 00       	mov    ebx,0x1
   37337:	c1 e2 06             	shl    edx,0x6
   3733a:	89 f9                	mov    ecx,edi
   3733c:	83 c2 40             	add    edx,0x40
   3733f:	e8 9f ef 00 00       	call   0x462e3
   37344:	83 f8 01             	cmp    eax,0x1
   37347:	74 0e                	je     0x37357
   37349:	b8 fe ff ff ff       	mov    eax,0xfffffffe
   3734e:	83 c4 10             	add    esp,0x10
   37351:	5d                   	pop    ebp
   37352:	5f                   	pop    edi
   37353:	5e                   	pop    esi
   37354:	59                   	pop    ecx
   37355:	5b                   	pop    ebx
   37356:	c3                   	ret    
   37357:	8b 04 24             	mov    eax,DWORD PTR [esp]
   3735a:	31 ff                	xor    edi,edi
   3735c:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
   37360:	89 7c 24 0c          	mov    DWORD PTR [esp+0xc],edi
   37364:	eb 4a                	jmp    0x373b0
   37366:	8b 5c 24 0c          	mov    ebx,DWORD PTR [esp+0xc]
   3736a:	8b 55 50             	mov    edx,DWORD PTR [ebp+0x50]
   3736d:	01 da                	add    edx,ebx
   3736f:	8b 4c 24 08          	mov    ecx,DWORD PTR [esp+0x8]
   37373:	31 c0                	xor    eax,eax
   37375:	66 c7 02 40 00       	mov    WORD PTR [edx],0x40
   3737a:	31 db                	xor    ebx,ebx
   3737c:	8a 19                	mov    bl,BYTE PTR [ecx]
   3737e:	c1 e3 05             	shl    ebx,0x5
   37381:	01 c3                	add    ebx,eax
   37383:	66 8b 1c 5e          	mov    bx,WORD PTR [esi+ebx*2]
   37387:	83 c2 04             	add    edx,0x4
   3738a:	81 e3 ff ff 00 00    	and    ebx,0xffff
   37390:	40                   	inc    eax
   37391:	89 5a fe             	mov    DWORD PTR [edx-0x2],ebx
   37394:	83 f8 20             	cmp    eax,0x20
   37397:	7c e1                	jl     0x3737a
   37399:	8b 4c 24 08          	mov    ecx,DWORD PTR [esp+0x8]
   3739d:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   373a1:	47                   	inc    edi
   373a2:	41                   	inc    ecx
   373a3:	05 82 00 00 00       	add    eax,0x82
   373a8:	89 4c 24 08          	mov    DWORD PTR [esp+0x8],ecx
   373ac:	89 44 24 0c          	mov    DWORD PTR [esp+0xc],eax
   373b0:	31 c0                	xor    eax,eax
   373b2:	8a 45 4f             	mov    al,BYTE PTR [ebp+0x4f]
   373b5:	39 c7                	cmp    edi,eax
   373b7:	7c ad                	jl     0x37366
   373b9:	56                   	push   esi
   373ba:	e8 5d e8 ff ff       	call   0x35c1c
   373bf:	83 c4 04             	add    esp,0x4
   373c2:	8b 14 24             	mov    edx,DWORD PTR [esp]
   373c5:	52                   	push   edx
   373c6:	e8 51 e8 ff ff       	call   0x35c1c
   373cb:	83 c4 04             	add    esp,0x4
   373ce:	31 c0                	xor    eax,eax
   373d0:	83 c4 10             	add    esp,0x10
   373d3:	5d                   	pop    ebp
   373d4:	5f                   	pop    edi
   373d5:	5e                   	pop    esi
   373d6:	59                   	pop    ecx
   373d7:	5b                   	pop    ebx
   373d8:	c3                   	ret    
   373d9:	8d 40 00             	lea    eax,[eax+0x0]
   373dc:	9d                   	popf   
   373dd:	77 02                	ja     0x373e1
   373df:	00 ed                	add    ch,ch
   373e1:	76 02                	jbe    0x373e5
   373e3:	00 ca                	add    dl,cl
   373e5:	76 02                	jbe    0x373e9
   373e7:	00 aa 78 02 00 12    	add    BYTE PTR [edx+0x12000278],ch
   373ed:	77 02                	ja     0x373f1
   373ef:	00 2d 77 02 00 5d    	add    BYTE PTR ds:0x5d000277,ch
   373f5:	77 02                	ja     0x373f9
   373f7:	00 8d 77 02 00 d0    	add    BYTE PTR [ebp-0x2ffffd89],cl
   373fd:	77 02                	ja     0x37401
   373ff:	00 c0                	add    al,al
   37401:	77 02                	ja     0x37405
   37403:	00 9a 76 02 00 79    	add    BYTE PTR [edx+0x79000276],bl
   37409:	76 02                	jbe    0x3740d
   3740b:	00 aa 78 02 00 89    	add    BYTE PTR [edx-0x76fffd88],ch
   37411:	76 02                	jbe    0x37415
   37413:	00 e2                	add    dl,ah
   37415:	77 02                	ja     0x37419
   37417:	00 3e                	add    BYTE PTR [esi],bh
   37419:	76 02                	jbe    0x3741d
   3741b:	00 fd                	add    ch,bh
   3741d:	77 02                	ja     0x37421
   3741f:	00 1d 78 02 00 2f    	add    BYTE PTR ds:0x2f000278,bl
   37425:	78 02                	js     0x37429
   37427:	00 aa 78 02 00 aa    	add    BYTE PTR [edx-0x55fffd88],ch
   3742d:	78 02                	js     0x37431
   3742f:	00 aa 78 02 00 aa    	add    BYTE PTR [edx-0x55fffd88],ch
   37435:	78 02                	js     0x37439
   37437:	00 aa 78 02 00 75    	add    BYTE PTR [edx+0x75000278],ch
   3743d:	78 02                	js     0x37441
   3743f:	00 0d 78 02 00 3f    	add    BYTE PTR ds:0x3f000278,cl
   37445:	78 02                	js     0x37449
   37447:	00 4c 78 02          	add    BYTE PTR [eax+edi*2+0x2],cl
   3744b:	00 5b 78             	add    BYTE PTR [ebx+0x78],bl
   3744e:	02 00                	add    al,BYTE PTR [eax]
   37450:	68 78 02 00        	push   0x53000278

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0003c2b8 <.data+0x2c2b8>:
   3c2b8:	8b 4c 24 04          	mov    ecx,DWORD PTR [esp+0x4]
   3c2bc:	8b 5c 24 08          	mov    ebx,DWORD PTR [esp+0x8]
   3c2c0:	89 da                	mov    edx,ebx
   3c2c2:	c6 43 5a 7d          	mov    BYTE PTR [ebx+0x5a],0x7d
   3c2c6:	89 c8                	mov    eax,ecx
   3c2c8:	c6 43 5b 06          	mov    BYTE PTR [ebx+0x5b],0x6
   3c2cc:	e8 3f ed ff ff       	call   0x3b010
   3c2d1:	85 c0                	test   eax,eax
   3c2d3:	7d 01                	jge    0x3c2d6
   3c2d5:	c3                   	ret    
   3c2d6:	89 da                	mov    edx,ebx
   3c2d8:	89 c8                	mov    eax,ecx
   3c2da:	e8 29 ef ff ff       	call   0x3b208
   3c2df:	85 c0                	test   eax,eax
   3c2e1:	7d 01                	jge    0x3c2e4
   3c2e3:	c3                   	ret    
   3c2e4:	89 da                	mov    edx,ebx
   3c2e6:	89 c8                	mov    eax,ecx
   3c2e8:	e8 f7 f8 ff ff       	call   0x3bbe4
   3c2ed:	85 c0                	test   eax,eax
   3c2ef:	7d 01                	jge    0x3c2f2
   3c2f1:	c3                   	ret    
   3c2f2:	89 da                	mov    edx,ebx
   3c2f4:	89 c8                	mov    eax,ecx
   3c2f6:	e8 71 fc ff ff       	call   0x3bf6c
   3c2fb:	89 c1                	mov    ecx,eax
   3c2fd:	85 c0                	test   eax,eax
   3c2ff:	7d 01                	jge    0x3c302
   3c301:	c3                   	ret    
   3c302:	89 d8                	mov    eax,ebx
   3c304:	e8 57 ff ff ff       	call   0x3c260
   3c309:	80 3b 04             	cmp    BYTE PTR [ebx],0x4
   3c30c:	75 03                	jne    0x3c311
   3c30e:	c6 03 01             	mov    BYTE PTR [ebx],0x1
   3c311:	89 c8                	mov    eax,ecx
   3c313:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00019a71 <.data+0x9a71>:
   19a71:	56                   	push   esi
   19a72:	57                   	push   edi
   19a73:	55                   	push   ebp
   19a74:	89 e5                	mov    ebp,esp
   19a76:	83 ec 0c             	sub    esp,0xc
   19a79:	8b 45 14             	mov    eax,DWORD PTR [ebp+0x14]
   19a7c:	6a 5c                	push   0x5c
   19a7e:	a3 04 05 02 00       	mov    ds:0x20504,eax
   19a83:	e8 78 c1 01 00       	call   0x35c00
   19a88:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
   19a8b:	83 c4 04             	add    esp,0x4
   19a8e:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
   19a91:	85 c0                	test   eax,eax
   19a93:	75 0f                	jne    0x19aa4
   19a95:	c7 05 08 05 02 00 ff 	mov    DWORD PTR ds:0x20508,0xffffffff
   19a9c:	ff ff ff 
   19a9f:	e9 27 01 00 00       	jmp    0x19bcb
   19aa4:	bb 5c 00 00 00       	mov    ebx,0x5c
   19aa9:	31 d2                	xor    edx,edx
   19aab:	e8 c0 d2 02 00       	call   0x46d70
   19ab0:	8b 45 10             	mov    eax,DWORD PTR [ebp+0x10]
   19ab3:	e8 62 87 ff ff       	call   0x1221a
   19ab8:	a3 7c 9b 01 00       	mov    ds:0x19b7c,eax
   19abd:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
   19ac0:	c6 00 00             	mov    BYTE PTR [eax],0x0
   19ac3:	b9 04 00 00 00       	mov    ecx,0x4
   19ac8:	a1 7c 9b 01 00       	mov    eax,ds:0x19b7c
   19acd:	8d 7d f4             	lea    edi,[ebp-0xc]
   19ad0:	89 c6                	mov    esi,eax
   19ad2:	a3 78 9b 01 00       	mov    ds:0x19b78,eax
   19ad7:	57                   	push   edi
   19ad8:	89 c8                	mov    eax,ecx
   19ada:	c1 e9 02             	shr    ecx,0x2
   19add:	f2 a5                	repnz movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
   19adf:	8a c8                	mov    cl,al
   19ae1:	80 e1 03             	and    cl,0x3
   19ae4:	f2 a4                	repnz movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   19ae6:	5f                   	pop    edi
   19ae7:	83 05 78 9b 01 00 04 	add    DWORD PTR ds:0x19b78,0x4
   19aee:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
   19af1:	25 ff ff ff 00       	and    eax,0xffffff
   19af6:	3d 41 4d 46 00       	cmp    eax,0x464d41
   19afb:	75 72                	jne    0x19b6f
   19afd:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
   19b00:	b9 14 00 00 00       	mov    ecx,0x14
   19b05:	c6 00 03             	mov    BYTE PTR [eax],0x3
   19b08:	8d 78 09             	lea    edi,[eax+0x9]
