
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000122d0 <.data+0x22d0>:
   122d0:	8b f2                	mov    esi,edx
   122d2:	e8 02 01 00 00       	call   0x123d9
   122d7:	73 07                	jae    0x122e0
   122d9:	33 c0                	xor    eax,eax
   122db:	33 db                	xor    ebx,ebx
   122dd:	f8                   	clc    
   122de:	eb 07                	jmp    0x122e7
   122e0:	8b 47 12             	mov    eax,DWORD PTR [edi+0x12]
   122e3:	8b 5f 0e             	mov    ebx,DWORD PTR [edi+0xe]
   122e6:	f9                   	stc    
   122e7:	c3                   	ret    
   122e8:	8b f2                	mov    esi,edx
   122ea:	e8 ea 00 00 00       	call   0x123d9
   122ef:	73 0c                	jae    0x122fd
   122f1:	ba 27 1a 00 00       	mov    edx,0x1a27
   122f6:	b0 01                	mov    al,0x1
   122f8:	e9 0a df ff ff       	jmp    0x10207
   122fd:	57                   	push   edi
   122fe:	a1 bc 19 00 00       	mov    eax,ds:0x19bc
   12303:	8b 15 c4 19 00 00    	mov    edx,DWORD PTR ds:0x19c4
   12309:	0f b6 1d f2 03 00 00 	movzx  ebx,BYTE PTR ds:0x3f2
   12310:	53                   	push   ebx
   12311:	52                   	push   edx
   12312:	50                   	push   eax
   12313:	e8 25 45 03 00       	call   0x4683d
   12318:	83 c4 0c             	add    esp,0xc
   1231b:	5f                   	pop    edi
   1231c:	8b 5f 12             	mov    ebx,DWORD PTR [edi+0x12]
   1231f:	e8 a4 de ff ff       	call   0x101c8
   12324:	eb 35                	jmp    0x1235b
   12326:	57                   	push   edi
   12327:	8b f2                	mov    esi,edx
   12329:	e8 ab 00 00 00       	call   0x123d9
   1232e:	73 0c                	jae    0x1233c
   12330:	ba 4d 1a 00 00       	mov    edx,0x1a4d
   12335:	b0 01                	mov    al,0x1
   12337:	e9 cb de ff ff       	jmp    0x10207
   1233c:	57                   	push   edi
   1233d:	a1 bc 19 00 00       	mov    eax,ds:0x19bc
   12342:	8b 15 c4 19 00 00    	mov    edx,DWORD PTR ds:0x19c4
   12348:	0f b6 1d f2 03 00 00 	movzx  ebx,BYTE PTR ds:0x3f2
   1234f:	53                   	push   ebx
   12350:	52                   	push   edx
   12351:	50                   	push   eax
   12352:	e8 e6 44 03 00       	call   0x4683d
   12357:	83 c4 0c             	add    esp,0xc
   1235a:	5f                   	pop    edi
   1235b:	8a 5f 0d             	mov    bl,BYTE PTR [edi+0xd]
   1235e:	0a db                	or     bl,bl
   12360:	74 15                	je     0x12377
   12362:	fe cb                	dec    bl
   12364:	74 20                	je     0x12386
   12366:	fe cb                	dec    bl
   12368:	74 2c                	je     0x12396
   1236a:	ba 73 1a 00 00       	mov    edx,0x1a73
   1236f:	b0 01                	mov    al,0x1
   12371:	e9 91 de ff ff       	jmp    0x10207
   12376:	c3                   	ret    
   12377:	8b 5f 12             	mov    ebx,DWORD PTR [edi+0x12]
   1237a:	50                   	push   eax
   1237b:	8b f8                	mov    edi,eax
   1237d:	8b c3                	mov    eax,ebx
   1237f:	e8 d3 00 00 00       	call   0x12457
   12384:	58                   	pop    eax
   12385:	c3                   	ret    
   12386:	50                   	push   eax
   12387:	8b 47 0e             	mov    eax,DWORD PTR [edi+0xe]
   1238a:	8b 5f 12             	mov    ebx,DWORD PTR [edi+0x12]
   1238d:	5f                   	pop    edi
   1238e:	57                   	push   edi
   1238f:	e8 fb 00 00 00       	call   0x1248f
   12394:	58                   	pop    eax
   12395:	c3                   	ret    
   12396:	ba 95 1a 00 00       	mov    edx,0x1a95
   1239b:	b0 01                	mov    al,0x1
   1239d:	e9 65 de ff ff       	jmp    0x10207
   123a2:	c3                   	ret    
   123a3:	83 3d bc 19 00 00 00 	cmp    DWORD PTR ds:0x19bc,0x0
   123aa:	74 18                	je     0x123c4
   123ac:	a1 bc 19 00 00       	mov    eax,ds:0x19bc
   123b1:	50                   	push   eax
   123b2:	e8 ab 47 03 00       	call   0x46b62
   123b7:	83 c4 04             	add    esp,0x4
   123ba:	a1 c0 19 00 00       	mov    eax,ds:0x19c0
   123bf:	e8 1c de ff ff       	call   0x101e0
   123c4:	c7 05 bc 19 00 00 00 	mov    DWORD PTR ds:0x19bc,0x0
   123cb:	00 00 00 
   123ce:	c7 05 c0 19 00 00 00 	mov    DWORD PTR ds:0x19c0,0x0
   123d5:	00 00 00 
   123d8:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000123d9 <.data+0x23d9>:
   123d9:	c7 05 c4 19 00 00 0b 	mov    DWORD PTR ds:0x19c4,0xb
   123e0:	00 00 00 
   123e3:	56                   	push   esi
   123e4:	80 3e 61             	cmp    BYTE PTR [esi],0x61
   123e7:	7c 03                	jl     0x123ec
   123e9:	80 2e 20             	sub    BYTE PTR [esi],0x20
   123ec:	46                   	inc    esi
   123ed:	80 7e ff 00          	cmp    BYTE PTR [esi-0x1],0x0
   123f1:	75 f1                	jne    0x123e4
   123f3:	5e                   	pop    esi
   123f4:	8b 3d c0 19 00 00    	mov    edi,DWORD PTR ds:0x19c0
   123fa:	66 8b 0d d1 19 00 00 	mov    cx,WORD PTR ds:0x19d1
   12401:	fc                   	cld    
   12402:	57                   	push   edi
   12403:	56                   	push   esi
   12404:	8a 06                	mov    al,BYTE PTR [esi]
   12406:	46                   	inc    esi
   12407:	0a c0                	or     al,al
   12409:	74 2a                	je     0x12435
   1240b:	3a 07                	cmp    al,BYTE PTR [edi]
   1240d:	75 03                	jne    0x12412
   1240f:	47                   	inc    edi
   12410:	eb f2                	jmp    0x12404
   12412:	5e                   	pop    esi
   12413:	5f                   	pop    edi
   12414:	8b 47 0e             	mov    eax,DWORD PTR [edi+0xe]
   12417:	01 05 c4 19 00 00    	add    DWORD PTR ds:0x19c4,eax
   1241d:	83 c7 16             	add    edi,0x16
   12420:	e2 e0                	loop   0x12402
   12422:	89 35 dc 03 00 00    	mov    DWORD PTR ds:0x3dc,esi
   12428:	ba b9 1a 00 00       	mov    edx,0x1ab9
   1242d:	b0 01                	mov    al,0x1
   1242f:	e9 d3 dd ff ff       	jmp    0x10207
   12434:	c3                   	ret    
   12435:	80 3f 00             	cmp    BYTE PTR [edi],0x0
   12438:	75 d8                	jne    0x12412
   1243a:	5e                   	pop    esi
   1243b:	5f                   	pop    edi
   1243c:	66 b9 16 00          	mov    cx,0x16
   12440:	bd d3 19 00 00       	mov    ebp,0x19d3
   12445:	8a 07                	mov    al,BYTE PTR [edi]
   12447:	47                   	inc    edi
   12448:	88 45 00             	mov    BYTE PTR [ebp+0x0],al
   1244b:	45                   	inc    ebp
   1244c:	66 49                	dec    cx
   1244e:	75 f5                	jne    0x12445
   12450:	bf d3 19 00 00       	mov    edi,0x19d3
   12455:	f8                   	clc    
   12456:	c3                   	ret    
   12457:	8b c8                	mov    ecx,eax
   12459:	81 f9 00 80 00 00    	cmp    ecx,0x8000
   1245f:	7f 04                	jg     0x12465
   12461:	8b c1                	mov    eax,ecx
   12463:	eb 05                	jmp    0x1246a
   12465:	b8 00 80 00 00       	mov    eax,0x8000
   1246a:	50                   	push   eax
   1246b:	51                   	push   ecx
   1246c:	57                   	push   edi
   1246d:	8b d8                	mov    ebx,eax
   1246f:	a1 bc 19 00 00       	mov    eax,ds:0x19bc
   12474:	8b d7                	mov    edx,edi
   12476:	53                   	push   ebx
   12477:	52                   	push   edx
   12478:	50                   	push   eax
   12479:	e8 00 44 03 00       	call   0x4687e
   1247e:	83 c4 0c             	add    esp,0xc
   12481:	5f                   	pop    edi
   12482:	59                   	pop    ecx
   12483:	58                   	pop    eax
   12484:	81 c7 00 80 00 00    	add    edi,0x8000
   1248a:	2b c8                	sub    ecx,eax
   1248c:	75 cb                	jne    0x12459
   1248e:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018350 <.data+0x8350>:
   18350:	55                   	push   ebp
   18351:	33 ff                	xor    edi,edi
   18353:	8b 1d 80 fa 01 00    	mov    ebx,DWORD PTR ds:0x1fa80
   18359:	0b db                	or     ebx,ebx
   1835b:	74 54                	je     0x183b1
   1835d:	8b fb                	mov    edi,ebx
   1835f:	8b 5f 04             	mov    ebx,DWORD PTR [edi+0x4]
   18362:	89 1d 80 fa 01 00    	mov    DWORD PTR ds:0x1fa80,ebx
   18368:	83 3d 84 fa 01 00 00 	cmp    DWORD PTR ds:0x1fa84,0x0
   1836f:	75 15                	jne    0x18386
   18371:	89 3d 84 fa 01 00    	mov    DWORD PTR ds:0x1fa84,edi
   18377:	89 3d 88 fa 01 00    	mov    DWORD PTR ds:0x1fa88,edi
   1837d:	33 db                	xor    ebx,ebx
   1837f:	89 1f                	mov    DWORD PTR [edi],ebx
   18381:	89 5f 04             	mov    DWORD PTR [edi+0x4],ebx
   18384:	eb 18                	jmp    0x1839e
   18386:	8b 2d 88 fa 01 00    	mov    ebp,DWORD PTR ds:0x1fa88
   1838c:	89 7d 04             	mov    DWORD PTR [ebp+0x4],edi
   1838f:	89 2f                	mov    DWORD PTR [edi],ebp
   18391:	c7 47 04 00 00 00 00 	mov    DWORD PTR [edi+0x4],0x0
   18398:	89 3d 88 fa 01 00    	mov    DWORD PTR ds:0x1fa88,edi
   1839e:	89 77 08             	mov    DWORD PTR [edi+0x8],esi
   183a1:	57                   	push   edi
   183a2:	83 c7 0c             	add    edi,0xc
   183a5:	33 c0                	xor    eax,eax
   183a7:	b9 1c 00 00 00       	mov    ecx,0x1c
   183ac:	f3 ab                	rep stos DWORD PTR es:[edi],eax
   183ae:	89 07                	mov    DWORD PTR [edi],eax
   183b0:	5f                   	pop    edi
   183b1:	8b f7                	mov    esi,edi
   183b3:	5d                   	pop    ebp
   183b4:	c3                   	ret    
   183b5:	be 80 ca 01 00       	mov    esi,0x1ca80
   183ba:	8b fe                	mov    edi,esi
   183bc:	81 c7 80 00 00 00    	add    edi,0x80
   183c2:	89 7e 04             	mov    DWORD PTR [esi+0x4],edi
   183c5:	89 37                	mov    DWORD PTR [edi],esi
   183c7:	8b f7                	mov    esi,edi
   183c9:	8b fe                	mov    edi,esi
   183cb:	81 c7 80 00 00 00    	add    edi,0x80
   183d1:	81 ff 80 fa 01 00    	cmp    edi,0x1fa80
   183d7:	75 e9                	jne    0x183c2
   183d9:	c7 05 80 fa 01 00 80 	mov    DWORD PTR ds:0x1fa80,0x1ca80
   183e0:	ca 01 00 
   183e3:	c7 05 84 fa 01 00 00 	mov    DWORD PTR ds:0x1fa84,0x0
   183ea:	00 00 00 
   183ed:	c3                   	ret    
   183ee:	55                   	push   ebp
   183ef:	52                   	push   edx
   183f0:	8b ee                	mov    ebp,esi
   183f2:	8b 7d 00             	mov    edi,DWORD PTR [ebp+0x0]
   183f5:	8b 55 04             	mov    edx,DWORD PTR [ebp+0x4]
   183f8:	0b ff                	or     edi,edi
   183fa:	74 05                	je     0x18401
   183fc:	89 57 04             	mov    DWORD PTR [edi+0x4],edx
   183ff:	eb 06                	jmp    0x18407
   18401:	89 15 84 fa 01 00    	mov    DWORD PTR ds:0x1fa84,edx
   18407:	0b d2                	or     edx,edx
   18409:	74 04                	je     0x1840f
   1840b:	89 3a                	mov    DWORD PTR [edx],edi
   1840d:	eb 08                	jmp    0x18417
   1840f:	8b 45 00             	mov    eax,DWORD PTR [ebp+0x0]
   18412:	a3 88 fa 01 00       	mov    ds:0x1fa88,eax
   18417:	c7 45 00 00 00 00 00 	mov    DWORD PTR [ebp+0x0],0x0
   1841e:	a1 80 fa 01 00       	mov    eax,ds:0x1fa80
   18423:	89 45 04             	mov    DWORD PTR [ebp+0x4],eax
   18426:	0b c0                	or     eax,eax
   18428:	74 08                	je     0x18432
   1842a:	8b 3d 80 fa 01 00    	mov    edi,DWORD PTR ds:0x1fa80
   18430:	89 2f                	mov    DWORD PTR [edi],ebp
   18432:	89 2d 80 fa 01 00    	mov    DWORD PTR ds:0x1fa80,ebp
   18438:	8b c2                	mov    eax,edx
   1843a:	5a                   	pop    edx
   1843b:	5d                   	pop    ebp
   1843c:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000186b0 <.data+0x86b0>:
   186b0:	66 0b c9             	or     cx,cx
   186b3:	74 01                	je     0x186b6
   186b5:	90                   	nop
   186b6:	52                   	push   edx
   186b7:	57                   	push   edi
   186b8:	55                   	push   ebp
   186b9:	8b 2d 78 ca 01 00    	mov    ebp,DWORD PTR ds:0x1ca78
   186bf:	0b ed                	or     ebp,ebp
   186c1:	0f 84 95 00 00 00    	je     0x1875c
   186c7:	8b 55 04             	mov    edx,DWORD PTR [ebp+0x4]
   186ca:	89 15 78 ca 01 00    	mov    DWORD PTR ds:0x1ca78,edx
   186d0:	89 45 08             	mov    DWORD PTR [ebp+0x8],eax
   186d3:	89 5d 0c             	mov    DWORD PTR [ebp+0xc],ebx
   186d6:	89 75 12             	mov    DWORD PTR [ebp+0x12],esi
   186d9:	66 89 4d 10          	mov    WORD PTR [ebp+0x10],cx
   186dd:	8b f5                	mov    esi,ebp
   186df:	8a 45 0d             	mov    al,BYTE PTR [ebp+0xd]
   186e2:	0a c0                	or     al,al
   186e4:	74 07                	je     0x186ed
   186e6:	e8 56 02 00 00       	call   0x18941
   186eb:	eb 05                	jmp    0x186f2
   186ed:	e8 4a 02 00 00       	call   0x1893c
   186f2:	8b fd                	mov    edi,ebp
   186f4:	66 8b 47 10          	mov    ax,WORD PTR [edi+0x10]
   186f8:	8b 1d 7c ca 01 00    	mov    ebx,DWORD PTR ds:0x1ca7c
   186fe:	0b db                	or     ebx,ebx
   18700:	75 15                	jne    0x18717
   18702:	c7 07 00 00 00 00    	mov    DWORD PTR [edi],0x0
   18708:	c7 47 04 00 00 00 00 	mov    DWORD PTR [edi+0x4],0x0
   1870f:	89 3d 7c ca 01 00    	mov    DWORD PTR ds:0x1ca7c,edi
   18715:	eb 45                	jmp    0x1875c
   18717:	8b eb                	mov    ebp,ebx
   18719:	66 3b 45 10          	cmp    ax,WORD PTR [ebp+0x10]
   1871d:	7c 15                	jl     0x18734
   1871f:	8b 5d 04             	mov    ebx,DWORD PTR [ebp+0x4]
   18722:	0b db                	or     ebx,ebx
   18724:	75 f1                	jne    0x18717
   18726:	89 2f                	mov    DWORD PTR [edi],ebp
   18728:	c7 47 04 00 00 00 00 	mov    DWORD PTR [edi+0x4],0x0
   1872f:	89 7d 04             	mov    DWORD PTR [ebp+0x4],edi
   18732:	eb 28                	jmp    0x1875c
   18734:	8b 5d 00             	mov    ebx,DWORD PTR [ebp+0x0]
   18737:	0b db                	or     ebx,ebx
   18739:	74 0f                	je     0x1874a
   1873b:	89 6f 04             	mov    DWORD PTR [edi+0x4],ebp
   1873e:	89 1f                	mov    DWORD PTR [edi],ebx
   18740:	89 7d 00             	mov    DWORD PTR [ebp+0x0],edi
   18743:	8b eb                	mov    ebp,ebx
   18745:	89 7d 04             	mov    DWORD PTR [ebp+0x4],edi
   18748:	eb 12                	jmp    0x1875c
   1874a:	c7 07 00 00 00 00    	mov    DWORD PTR [edi],0x0
   18750:	89 6f 04             	mov    DWORD PTR [edi+0x4],ebp
   18753:	89 7d 00             	mov    DWORD PTR [ebp+0x0],edi
   18756:	89 3d 7c ca 01 00    	mov    DWORD PTR ds:0x1ca7c,edi
   1875c:	8b f7                	mov    esi,edi
   1875e:	5d                   	pop    ebp
   1875f:	5f                   	pop    edi
   18760:	5a                   	pop    edx
   18761:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

000188f2 <.data+0x88f2>:
   188f2:	60                   	pusha  
   188f3:	8b ee                	mov    ebp,esi
   188f5:	8b 7d 00             	mov    edi,DWORD PTR [ebp+0x0]
   188f8:	8b 55 04             	mov    edx,DWORD PTR [ebp+0x4]
   188fb:	0b ff                	or     edi,edi
   188fd:	74 05                	je     0x18904
   188ff:	89 57 04             	mov    DWORD PTR [edi+0x4],edx
   18902:	eb 08                	jmp    0x1890c
   18904:	8b 45 04             	mov    eax,DWORD PTR [ebp+0x4]
   18907:	a3 7c ca 01 00       	mov    ds:0x1ca7c,eax
   1890c:	0b d2                	or     edx,edx
   1890e:	74 02                	je     0x18912
   18910:	89 3a                	mov    DWORD PTR [edx],edi
   18912:	c7 45 00 00 00 00 00 	mov    DWORD PTR [ebp+0x0],0x0
   18919:	a1 78 ca 01 00       	mov    eax,ds:0x1ca78
   1891e:	89 45 04             	mov    DWORD PTR [ebp+0x4],eax
   18921:	0b c0                	or     eax,eax
   18923:	74 08                	je     0x1892d
   18925:	8b 15 78 ca 01 00    	mov    edx,DWORD PTR ds:0x1ca78
   1892b:	89 2a                	mov    DWORD PTR [edx],ebp
   1892d:	89 2d 78 ca 01 00    	mov    DWORD PTR ds:0x1ca78,ebp
   18933:	c7 45 08 00 00 00 00 	mov    DWORD PTR [ebp+0x8],0x0
   1893a:	61                   	popa   
   1893b:	c3                   	ret    
   1893c:	80 66 0f df          	and    BYTE PTR [esi+0xf],0xdf
   18940:	c3                   	ret    
   18941:	0a c0                	or     al,al
   18943:	74 03                	je     0x18948
   18945:	88 46 0d             	mov    BYTE PTR [esi+0xd],al
   18948:	80 7e 0d 00          	cmp    BYTE PTR [esi+0xd],0x0
   1894c:	74 04                	je     0x18952
   1894e:	80 4e 0f 20          	or     BYTE PTR [esi+0xf],0x20
   18952:	c3                   	ret    
   18953:	60                   	pusha  
   18954:	8b ee                	mov    ebp,esi
   18956:	83 7e 08 00          	cmp    DWORD PTR [esi+0x8],0x0
   1895a:	0f 84 e4 00 00 00    	je     0x18a44
   18960:	8b f5                	mov    esi,ebp
   18962:	e8 3c ff         	call   0x188a3

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018f31 <.data+0x8f31>:
   18f31:	53                   	push   ebx
   18f32:	51                   	push   ecx
   18f33:	56                   	push   esi
   18f34:	55                   	push   ebp
   18f35:	89 e5                	mov    ebp,esp
   18f37:	89 c6                	mov    esi,eax
   18f39:	a1 62 9b 01 00       	mov    eax,ds:0x19b62
   18f3e:	c1 f8 10             	sar    eax,0x10
   18f41:	83 f8 ff             	cmp    eax,0xffffffff
   18f44:	74 6e                	je     0x18fb4
   18f46:	83 fe 02             	cmp    esi,0x2
   18f49:	7d 69                	jge    0x18fb4
   18f4b:	80 3d 84 9a 01 00 00 	cmp    BYTE PTR ds:0x19a84,0x0
   18f52:	74 60                	je     0x18fb4
   18f54:	8b 1d a8 9a 01 00    	mov    ebx,DWORD PTR ds:0x19aa8
   18f5a:	01 f3                	add    ebx,esi
   18f5c:	83 fa ff             	cmp    edx,0xffffffff
   18f5f:	75 0e                	jne    0x18f6f
   18f61:	53                   	push   ebx
   18f62:	e8 b6 43 02 00       	call   0x3d31d
   18f67:	83 c4 04             	add    esp,0x4
   18f6a:	5d                   	pop    ebp
   18f6b:	5e                   	pop    esi
   18f6c:	59                   	pop    ecx
   18f6d:	5b                   	pop    ebx
   18f6e:	c3                   	ret    
   18f6f:	89 d0                	mov    eax,edx
   18f71:	c1 e0 02             	shl    eax,0x2
   18f74:	01 d0                	add    eax,edx
   18f76:	c1 e0 02             	shl    eax,0x2
   18f79:	29 d0                	sub    eax,edx
   18f7b:	05 18 fb 01 00       	add    eax,0x1fb18
   18f80:	50                   	push   eax
   18f81:	53                   	push   ebx
   18f82:	e8 48 43 02 00       	call   0x3d2cf
   18f87:	83 c4 08             	add    esp,0x8
   18f8a:	a1 a8 9a 01 00       	mov    eax,ds:0x19aa8
   18f8f:	6a 00                	push   0x0
   18f91:	01 f0                	add    eax,esi
   18f93:	50                   	push   eax
   18f94:	e8 33 44 02 00       	call   0x3d3cc
   18f99:	83 c4 08             	add    esp,0x8
   18f9c:	6a 40                	push   0x40
   18f9e:	8b 15 a8 9a 01 00    	mov    edx,DWORD PTR ds:0x19aa8
   18fa4:	68 3c 31 00 00       	push   0x313c
   18fa9:	01 d6                	add    esi,edx
   18fab:	56                   	push   esi
   18fac:	e8 43 43 02 00       	call   0x3d2f4
   18fb1:	83 c4 0c             	add    esp,0xc
   18fb4:	5d                   	pop    ebp
   18fb5:	5e                   	pop    esi
   18fb6:	59                   	pop    ecx
   18fb7:	5b                   	pop    ebx
   18fb8:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00018fb9 <.data+0x8fb9>:
   18fb9:	53                   	push   ebx
   18fba:	51                   	push   ecx
   18fbb:	52                   	push   edx
   18fbc:	56                   	push   esi
   18fbd:	57                   	push   edi
   18fbe:	55                   	push   ebp
   18fbf:	89 e5                	mov    ebp,esp
   18fc1:	89 c7                	mov    edi,eax
   18fc3:	a1 62 9b 01 00       	mov    eax,ds:0x19b62
   18fc8:	c1 f8 10             	sar    eax,0x10
   18fcb:	83 f8 ff             	cmp    eax,0xffffffff
   18fce:	0f 84 40 01 00 00    	je     0x19114
   18fd4:	e8 e1 c6 02 00       	call   0x456ba
   18fd9:	8b 15 cc fa 01 00    	mov    edx,DWORD PTR ds:0x1facc
   18fdf:	52                   	push   edx
   18fe0:	e8 db 3c 02 00       	call   0x3ccc0
   18fe5:	31 db                	xor    ebx,ebx
   18fe7:	83 c4 04             	add    esp,0x4
   18fea:	89 1d cc fa 01 00    	mov    DWORD PTR ds:0x1facc,ebx
   18ff0:	89 1d a8 9a 01 00    	mov    DWORD PTR ds:0x19aa8,ebx
   18ff6:	83 ff ff             	cmp    edi,0xffffffff
   18ff9:	74 5a                	je     0x19055
   18ffb:	80 3d 7e 9a 01 00 00 	cmp    BYTE PTR ds:0x19a7e,0x0
   19002:	74 51                	je     0x19055
   19004:	31 c0                	xor    eax,eax
   19006:	a0 e2 fa 01 00       	mov    al,ds:0x1fae2
   1900b:	83 f8 0a             	cmp    eax,0xa
   1900e:	74 07                	je     0x19017
   19010:	e8 42 aa 02 00       	call   0x43a57
   19015:	eb 16                	jmp    0x1902d
   19017:	31 f6                	xor    esi,esi
   19019:	56                   	push   esi
   1901a:	e8 df 44 02 00       	call   0x3d4fe
   1901f:	83 c4 04             	add    esp,0x4
   19022:	46                   	inc    esi
   19023:	83 fe 0a             	cmp    esi,0xa
   19026:	7c f1                	jl     0x19019
   19028:	e8 7f 4b 02 00       	call   0x3dbac
   1902d:	6a 00                	push   0x0
   1902f:	8b 34 bd 24 9b 01 00 	mov    esi,DWORD PTR [edi*4+0x19b24]
   19036:	56                   	push   esi
   19037:	e8 35 0a 00 00       	call   0x19a71
   1903c:	83 c4 08             	add    esp,0x8
   1903f:	a3 cc fa 01 00       	mov    ds:0x1facc,eax
   19044:	85 c0                	test   eax,eax
   19046:	74 0d                	je     0x19055
   19048:	8a 40 29             	mov    al,BYTE PTR [eax+0x29]
   1904b:	25 ff 00 00 00       	and    eax,0xff
   19050:	a3 a8 9a 01 00       	mov    ds:0x19aa8,eax
   19055:	31 c0                	xor    eax,eax
   19057:	a0 e2 fa 01 00       	mov    al,ds:0x1fae2
   1905c:	83 f8 0a             	cmp    eax,0xa
   1905f:	74 59                	je     0x190ba
   19061:	66 a1 d2 fa 01 00    	mov    ax,ds:0x1fad2
   19067:	30 e4                	xor    ah,ah
   19069:	24 01                	and    al,0x1
   1906b:	25 ff ff 00 00       	and    eax,0xffff
   19070:	74 48                	je     0x190ba
   19072:	31 c0                	xor    eax,eax
   19074:	a0 0f fb 01 00       	mov    al,ds:0x1fb0f
   19079:	83 f8 02             	cmp    eax,0x2
   1907c:	75 3c                	jne    0x190ba
   1907e:	bb 01 00 00 00       	mov    ebx,0x1
   19083:	89 d8                	mov    eax,ebx
   19085:	c1 e0 02             	shl    eax,0x2
   19088:	01 d8                	add    eax,ebx
   1908a:	01 c0                	add    eax,eax
   1908c:	89 c2                	mov    edx,eax
   1908e:	c1 e0 04             	shl    eax,0x4
   19091:	29 d0                	sub    eax,edx
   19093:	89 c2                	mov    edx,eax
   19095:	c1 fa 1f             	sar    edx,0x1f
   19098:	c1 e2 05             	shl    edx,0x5
   1909b:	1b c2                	sbb    eax,edx
   1909d:	c1 f8 05             	sar    eax,0x5
   190a0:	43                   	inc    ebx
   190a1:	66 89 04 5d 88 fa 01 	mov    WORD PTR [ebx*2+0x1fa88],ax
   190a8:	00 
   190a9:	83 fb 21             	cmp    ebx,0x21
   190ac:	7c d5                	jl     0x19083
   190ae:	a1 a8 9a 01 00       	mov    eax,ds:0x19aa8
   190b3:	68 8c fa 01 00       	push   0x1fa8c
   190b8:	eb 07                	jmp    0x190c1
   190ba:	a1 a8 9a 01 00       	mov    eax,ds:0x19aa8
   190bf:	6a 00                	push   0x0
   190c1:	83 c0 02             	add    eax,0x2
   190c4:	50                   	push   eax
   190c5:	6a 00                	push   0x0
   190c7:	e8 21 45 02 00       	call   0x3d5ed
   190cc:	83 c4 0c             	add    esp,0xc
   190cf:	a1 b0 9a 01 00       	mov    eax,ds:0x19ab0
   190d4:	e8 42 00 00 00       	call   0x1911b
   190d9:	a1 b4 9a 01 00       	mov    eax,ds:0x19ab4
   190de:	e8 67 00 00 00       	call   0x1914a
   190e3:	8b 3d cc fa 01 00    	mov    edi,DWORD PTR ds:0x1facc
   190e9:	85 ff                	test   edi,edi
   190eb:	74 0b                	je     0x190f8
   190ed:	6a 01                	push   0x1
   190ef:	57                   	push   edi
   190f0:	e8 5d c5 02 00       	call   0x45652
   190f5:	83 c4 08             	add    esp,0x8
   190f8:	31 f6                	xor    esi,esi
   190fa:	eb 0c                	jmp    0x19108
   190fc:	6a 00                	push   0x0
   190fe:	56                   	push   esi
   190ff:	e8 c8 42 02 00       	call   0x3d3cc
   19104:	83 c4 08             	add    esp,0x8
   19107:	46                   	inc    esi
   19108:	a1 a8 9a 01 00       	mov    eax,ds:0x19aa8
   1910d:	83 c0 02             	add    eax,0x2
   19110:	39 c6                	cmp    esi,eax
   19112:	7c e8                	jl     0x190fc
   19114:	5d                   	pop    ebp
   19115:	5f                   	pop    edi
   19116:	5e                   	pop    esi
   19117:	5a                   	pop    edx
   19118:	59                   	pop    ecx
   19119:	5b                   	pop    ebx
   1911a:	c3                   	ret    

bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00019187 <.data+0x9187>:
   19187:	53                   	push   ebx
   19188:	51                   	push   ecx
   19189:	52                   	push   edx
   1918a:	55                   	push   ebp
   1918b:	89 e5                	mov    ebp,esp
   1918d:	a1 62 9b 01 00       	mov    eax,ds:0x19b62
   19192:	c1 f8 10             	sar    eax,0x10
   19195:	83 f8 ff             	cmp    eax,0xffffffff
   19198:	74 1e                	je     0x191b8
   1919a:	8b 15 a8 9a 01 00    	mov    edx,DWORD PTR ds:0x19aa8
   191a0:	52                   	push   edx
   191a1:	e8 77 41 02 00       	call   0x3d31d
   191a6:	a1 a8 9a 01 00       	mov    eax,ds:0x19aa8
   191ab:	83 c4 04             	add    esp,0x4
   191ae:	40                   	inc    eax
   191af:	50                   	push   eax
   191b0:	e8 68 41 02 00       	call   0x3d31d
   191b5:	83 c4 04             	add    esp,0x4
   191b8:	5d                   	pop    ebp
   191b9:	5a                   	pop    edx
   191ba:	59                   	pop    ecx
   191bb:	5b                   	pop    ebx
   191bc:	c3                   	ret    
