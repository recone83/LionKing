
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

0001248f <.data+0x248f>:
   1248f:	57                   	push   edi
   12490:	50                   	push   eax
   12491:	53                   	push   ebx
   12492:	8b d8                	mov    ebx,eax
   12494:	e8 2f dd ff ff       	call   0x101c8
   12499:	a3 fc 19 00 00       	mov    ds:0x19fc,eax
   1249e:	bb 00 8d 00 00       	mov    ebx,0x8d00
   124a3:	e8 20 dd ff ff       	call   0x101c8
   124a8:	a3 f0 19 00 00       	mov    ds:0x19f0,eax
   124ad:	bb 80 46 00 00       	mov    ebx,0x4680
   124b2:	e8 11 dd ff ff       	call   0x101c8
   124b7:	a3 f4 19 00 00       	mov    ds:0x19f4,eax
   124bc:	bb a0 0f 00 00       	mov    ebx,0xfa0
   124c1:	e8 02 dd ff ff       	call   0x101c8
   124c6:	a3 f8 19 00 00       	mov    ds:0x19f8,eax
   124cb:	5b                   	pop    ebx
   124cc:	58                   	pop    eax
   124cd:	5f                   	pop    edi
   124ce:	57                   	push   edi
   124cf:	8b d0                	mov    edx,eax
   124d1:	8b c2                	mov    eax,edx
   124d3:	c7 05 05 1a 00 00 00 	mov    DWORD PTR ds:0x1a05,0x0
   124da:	00 00 00 
   124dd:	8b 35 fc 19 00 00    	mov    esi,DWORD PTR ds:0x19fc
   124e3:	56                   	push   esi
   124e4:	8b 3d fc 19 00 00    	mov    edi,DWORD PTR ds:0x19fc
   124ea:	e8 68 ff ff ff       	call   0x12457
   124ef:	5e                   	pop    esi
   124f0:	5f                   	pop    edi
   124f1:	b0 09                	mov    al,0x9
   124f3:	e8 0c 02 00 00       	call   0x12704
   124f8:	c6 05 00 1a 00 00 00 	mov    BYTE PTR ds:0x1a00,0x0
   124ff:	66 c7 05 df 1a 00 00 	mov    WORD PTR ds:0x1adf,0x100
   12506:	00 01 
   12508:	8b 1d 01 1a 00 00    	mov    ebx,DWORD PTR ds:0x1a01
   1250e:	8a 2d e9 19 00 00    	mov    ch,BYTE PTR ds:0x19e9
   12514:	8a 0d 00 1a 00 00    	mov    cl,BYTE PTR ds:0x1a00
   1251a:	8b 15 05 1a 00 00    	mov    edx,DWORD PTR ds:0x1a05
   12520:	c1 e3 08             	shl    ebx,0x8
   12523:	8a 1e                	mov    bl,BYTE PTR [esi]
   12525:	46                   	inc    esi
   12526:	80 c1 08             	add    cl,0x8
   12529:	0b d2                	or     edx,edx
   1252b:	74 15                	je     0x12542
   1252d:	4a                   	dec    edx
   1252e:	0b d2                	or     edx,edx
   12530:	77 10                	ja     0x12542
   12532:	8b 35 fc 19 00 00    	mov    esi,DWORD PTR ds:0x19fc
   12538:	c7 05 05 1a 00 00 00 	mov    DWORD PTR ds:0x1a05,0x0
   1253f:	00 00 00 
   12542:	3a e9                	cmp    ch,cl
   12544:	7f da                	jg     0x12520
   12546:	89 15 05 1a 00 00    	mov    DWORD PTR ds:0x1a05,edx
   1254c:	2a cd                	sub    cl,ch
   1254e:	8b c3                	mov    eax,ebx
   12550:	d3 e8                	shr    eax,cl
   12552:	66 23 05 ea 19 00 00 	and    ax,WORD PTR ds:0x19ea
   12559:	88 0d 00 1a 00 00    	mov    BYTE PTR ds:0x1a00,cl
   1255f:	89 1d 01 1a 00 00    	mov    DWORD PTR ds:0x1a01,ebx
   12565:	66 a3 e1 1a 00 00    	mov    ds:0x1ae1,ax
   1256b:	66 a3 e5 1a 00 00    	mov    ds:0x1ae5,ax
   12571:	aa                   	stos   BYTE PTR es:[edi],al
   12572:	8b 1d 01 1a 00 00    	mov    ebx,DWORD PTR ds:0x1a01
   12578:	8a 2d e9 19 00 00    	mov    ch,BYTE PTR ds:0x19e9
   1257e:	8a 0d 00 1a 00 00    	mov    cl,BYTE PTR ds:0x1a00
   12584:	8b 15 05 1a 00 00    	mov    edx,DWORD PTR ds:0x1a05
   1258a:	c1 e3 08             	shl    ebx,0x8
   1258d:	8a 1e                	mov    bl,BYTE PTR [esi]
   1258f:	46                   	inc    esi
   12590:	80 c1 08             	add    cl,0x8
   12593:	0b d2                	or     edx,edx
   12595:	74 15                	je     0x125ac
   12597:	4a                   	dec    edx
   12598:	0b d2                	or     edx,edx
   1259a:	77 10                	ja     0x125ac
   1259c:	8b 35 fc 19 00 00    	mov    esi,DWORD PTR ds:0x19fc
   125a2:	c7 05 05 1a 00 00 00 	mov    DWORD PTR ds:0x1a05,0x0
   125a9:	00 00 00 
   125ac:	3a e9                	cmp    ch,cl
   125ae:	7f da                	jg     0x1258a
   125b0:	89 15 05 1a 00 00    	mov    DWORD PTR ds:0x1a05,edx
   125b6:	2a cd                	sub    cl,ch
   125b8:	8b c3                	mov    eax,ebx
   125ba:	d3 e8                	shr    eax,cl
   125bc:	66 23 05 ea 19 00 00 	and    ax,WORD PTR ds:0x19ea
   125c3:	88 0d 00 1a 00 00    	mov    BYTE PTR ds:0x1a00,cl
   125c9:	89 1d 01 1a 00 00    	mov    DWORD PTR ds:0x1a01,ebx
   125cf:	66 a3 e3 1a 00 00    	mov    ds:0x1ae3,ax
   125d5:	66 3b 05 ea 19 00 00 	cmp    ax,WORD PTR ds:0x19ea
   125dc:	0f 84 f9 00 00 00    	je     0x126db
   125e2:	66 3b 05 ec 19 00 00 	cmp    ax,WORD PTR ds:0x19ec
   125e9:	0f 84 10 ff ff ff    	je     0x124ff
   125ef:	8b 2d f8 19 00 00    	mov    ebp,DWORD PTR ds:0x19f8
   125f5:	66 8b d8             	mov    bx,ax
   125f8:	66 3b 05 df 1a 00 00 	cmp    ax,WORD PTR ds:0x1adf
   125ff:	7c 12                	jl     0x12613
   12601:	66 8b 15 e5 1a 00 00 	mov    dx,WORD PTR ds:0x1ae5
   12608:	88 55 00             	mov    BYTE PTR [ebp+0x0],dl
   1260b:	45                   	inc    ebp
   1260c:	66 8b 1d e1 1a 00 00 	mov    bx,WORD PTR ds:0x1ae1
   12613:	66 50                	push   ax
   12615:	66 33 c9             	xor    cx,cx
   12618:	eb 31                	jmp    0x1264b
   1261a:	0f b7 db             	movzx  ebx,bx
   1261d:	8b 15 f4 19 00 00    	mov    edx,DWORD PTR ds:0x19f4
   12623:	8a 04 13             	mov    al,BYTE PTR [ebx+edx*1]
   12626:	88 45 00             	mov    BYTE PTR [ebp+0x0],al
   12629:	45                   	inc    ebp
   1262a:	d1 e3                	shl    ebx,1
   1262c:	8b 15 f0 19 00 00    	mov    edx,DWORD PTR ds:0x19f0
   12632:	66 8b 1c 1a          	mov    bx,WORD PTR [edx+ebx*1]
   12636:	66 41                	inc    cx
   12638:	66 81 f9 a0 0f       	cmp    cx,0xfa0
   1263d:	72 0c                	jb     0x1264b
   1263f:	ba e7 1a 00 00       	mov    edx,0x1ae7
   12644:	b0 03                	mov    al,0x3
   12646:	e9 bc db ff ff       	jmp    0x10207
   1264b:	66 81 fb ff 00       	cmp    bx,0xff
   12650:	7f c8                	jg     0x1261a
   12652:	88 5d 00             	mov    BYTE PTR [ebp+0x0],bl
   12655:	66 0f b6 45 00       	movzx  ax,BYTE PTR [ebp+0x0]
   1265a:	66 a3 e5 1a 00 00    	mov    ds:0x1ae5,ax
   12660:	3b 2d f8 19 00 00    	cmp    ebp,DWORD PTR ds:0x19f8
   12666:	72 07                	jb     0x1266f
   12668:	8a 45 00             	mov    al,BYTE PTR [ebp+0x0]
   1266b:	aa                   	stos   BYTE PTR es:[edi],al
   1266c:	4d                   	dec    ebp
   1266d:	eb f1                	jmp    0x12660
   1266f:	33 ed                	xor    ebp,ebp
   12671:	66 8b 2d df 1a 00 00 	mov    bp,WORD PTR ds:0x1adf
   12678:	66 d1 e5             	shl    bp,1
   1267b:	03 2d f0 19 00 00    	add    ebp,DWORD PTR ds:0x19f0
   12681:	66 a1 e1 1a 00 00    	mov    ax,ds:0x1ae1
   12687:	66 89 45 00          	mov    WORD PTR [ebp+0x0],ax
   1268b:	33 ed                	xor    ebp,ebp
   1268d:	66 8b 2d df 1a 00 00 	mov    bp,WORD PTR ds:0x1adf
   12694:	03 2d f4 19 00 00    	add    ebp,DWORD PTR ds:0x19f4
   1269a:	66 a1 e5 1a 00 00    	mov    ax,ds:0x1ae5
   126a0:	88 45 00             	mov    BYTE PTR [ebp+0x0],al
   126a3:	66 ff 05 df 1a 00 00 	inc    WORD PTR ds:0x1adf
   126aa:	66 a1 df 1a 00 00    	mov    ax,ds:0x1adf
   126b0:	66 3b 05 ee 19 00 00 	cmp    ax,WORD PTR ds:0x19ee
   126b7:	7e 15                	jle    0x126ce
   126b9:	80 3d e9 19 00 00 0e 	cmp    BYTE PTR ds:0x19e9,0xe
   126c0:	7d 0c                	jge    0x126ce
   126c2:	a0 e9 19 00 00       	mov    al,ds:0x19e9
   126c7:	fe c0                	inc    al
   126c9:	e8 36 00 00 00       	call   0x12704
   126ce:	66 58                	pop    ax
   126d0:	66 a3 e1 1a 00 00    	mov    ds:0x1ae1,ax
   126d6:	e9 97 fe ff ff       	jmp    0x12572
   126db:	a1 f0 19 00 00       	mov    eax,ds:0x19f0
   126e0:	e8 fb da ff ff       	call   0x101e0
   126e5:	a1 f4 19 00 00       	mov    eax,ds:0x19f4
   126ea:	e8 f1 da ff ff       	call   0x101e0
   126ef:	a1 f8 19 00 00       	mov    eax,ds:0x19f8
   126f4:	e8 e7 da ff ff       	call   0x101e0
   126f9:	a1 fc 19 00 00       	mov    eax,ds:0x19fc
   126fe:	e8 dd da ff ff       	call   0x101e0
   12703:	c3                   	ret    
   12704:	a2 e9 19 00 00       	mov    ds:0x19e9,al
   12709:	8a c8                	mov    cl,al
   1270b:	66 b8 01 00          	mov    ax,0x1
   1270f:	66 d3 e0             	shl    ax,cl
   12712:	66 48                	dec    ax
   12714:	66 a3 ea 19 00 00    	mov    ds:0x19ea,ax
   1271a:	66 48                	dec    ax
   1271c:	66 a3 ec 19 00 00    	mov    ds:0x19ec,ax
   12722:	66 48                	dec    ax
   12724:	66 a3 ee 19 00 00    	mov    ds:0x19ee,ax
   1272a:	c3                   	ret    
   1272b:	00 00                	add    BYTE PTR [eax],al
   1272d:	00 00                	add    BYTE PTR [eax],al
   1272f:	00 66 ff             	add    BYTE PTR [esi-0x1],ah
   12732:	0d a6 1b         	or     eax,0x1ba6
