
bin/obj1_code.bin:     file format binary


Disassembly of section .data:

00011d7f <.data+0x1d7f>:
   11d7f:	c1 e6 06             	shl    esi,0x6
   11d82:	03 35 82 15 00 00    	add    esi,DWORD PTR ds:0x1582
   11d88:	66 8b 03             	mov    ax,WORD PTR [ebx]
   11d8b:	66 25 00 c0          	and    ax,0xc000
   11d8f:	66 0b c0             	or     ax,ax
   11d92:	75 28                	jne    0x11dbc
   11d94:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11d9a:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11da0:	03 f2                	add    esi,edx
   11da2:	b9 08 00 00 00       	mov    ecx,0x8
   11da7:	2b ca                	sub    ecx,edx
   11da9:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   11dab:	81 c7 38 01 00 00    	add    edi,0x138
   11db1:	03 fa                	add    edi,edx
   11db3:	66 48                	dec    ax
   11db5:	75 e9                	jne    0x11da0
   11db7:	e9 92 00 00 00       	jmp    0x11e4e
   11dbc:	66 3d 00 80          	cmp    ax,0x8000
   11dc0:	75 30                	jne    0x11df2
   11dc2:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11dc8:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11dce:	83 c6 07             	add    esi,0x7
   11dd1:	2b f2                	sub    esi,edx
   11dd3:	b1 08                	mov    cl,0x8
   11dd5:	2a ca                	sub    cl,dl
   11dd7:	8a 26                	mov    ah,BYTE PTR [esi]
   11dd9:	88 27                	mov    BYTE PTR [edi],ah
   11ddb:	4e                   	dec    esi
   11ddc:	47                   	inc    edi
   11ddd:	fe c9                	dec    cl
   11ddf:	75 f6                	jne    0x11dd7
   11de1:	83 c6 10             	add    esi,0x10
   11de4:	81 c7 38 01 00 00    	add    edi,0x138
   11dea:	03 fa                	add    edi,edx
   11dec:	fe c8                	dec    al
   11dee:	75 e1                	jne    0x11dd1
   11df0:	eb 5c                	jmp    0x11e4e
   11df2:	66 3d 00 40          	cmp    ax,0x4000
   11df6:	75 2b                	jne    0x11e23
   11df8:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11dfe:	83 c6 38             	add    esi,0x38
   11e01:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11e07:	03 f2                	add    esi,edx
   11e09:	b9 08 00 00 00       	mov    ecx,0x8
   11e0e:	2b ca                	sub    ecx,edx
   11e10:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   11e12:	83 ee 10             	sub    esi,0x10
   11e15:	81 c7 38 01 00 00    	add    edi,0x138
   11e1b:	03 fa                	add    edi,edx
   11e1d:	66 48                	dec    ax
   11e1f:	75 e6                	jne    0x11e07
   11e21:	eb 2b                	jmp    0x11e4e
   11e23:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11e29:	83 c6 3f             	add    esi,0x3f
   11e2c:	2b 35 78 15 00 00    	sub    esi,DWORD PTR ds:0x1578
   11e32:	2b f2                	sub    esi,edx
   11e34:	b1 08                	mov    cl,0x8
   11e36:	2a ca                	sub    cl,dl
   11e38:	8a 26                	mov    ah,BYTE PTR [esi]
   11e3a:	88 27                	mov    BYTE PTR [edi],ah
   11e3c:	4e                   	dec    esi
   11e3d:	47                   	inc    edi
   11e3e:	fe c9                	dec    cl
   11e40:	75 f6                	jne    0x11e38
   11e42:	81 c7 38 01 00 00    	add    edi,0x138
   11e48:	03 fa                	add    edi,edx
   11e4a:	fe c8                	dec    al
   11e4c:	75 e4                	jne    0x11e32
   11e4e:	c3                   	ret    
   11e4f:	c1 e6 06             	shl    esi,0x6
   11e52:	03 35 82 15 00 00    	add    esi,DWORD PTR ds:0x1582
   11e58:	66 8b 03             	mov    ax,WORD PTR [ebx]
   11e5b:	66 25 00 c0          	and    ax,0xc000
   11e5f:	66 0b c0             	or     ax,ax
   11e62:	75 2c                	jne    0x11e90
   11e64:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11e6a:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11e70:	8b 16                	mov    edx,DWORD PTR [esi]
   11e72:	89 17                	mov    DWORD PTR [edi],edx
   11e74:	83 c6 04             	add    esi,0x4
   11e77:	83 c7 04             	add    edi,0x4
   11e7a:	8b 16                	mov    edx,DWORD PTR [esi]
   11e7c:	89 17                	mov    DWORD PTR [edi],edx
   11e7e:	83 c6 04             	add    esi,0x4
   11e81:	81 c7 3c 01 00 00    	add    edi,0x13c
   11e87:	fe c8                	dec    al
   11e89:	75 e5                	jne    0x11e70
   11e8b:	e9 87 00 00 00       	jmp    0x11f17
   11e90:	66 3d 00 80          	cmp    ax,0x8000
   11e94:	75 2a                	jne    0x11ec0
   11e96:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11e9c:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11ea2:	83 c6 07             	add    esi,0x7
   11ea5:	b4 08                	mov    ah,0x8
   11ea7:	8a 16                	mov    dl,BYTE PTR [esi]
   11ea9:	88 17                	mov    BYTE PTR [edi],dl
   11eab:	4e                   	dec    esi
   11eac:	47                   	inc    edi
   11ead:	fe cc                	dec    ah
   11eaf:	75 f6                	jne    0x11ea7
   11eb1:	83 c6 10             	add    esi,0x10
   11eb4:	81 c7 38 01 00 00    	add    edi,0x138
   11eba:	fe c8                	dec    al
   11ebc:	75 e7                	jne    0x11ea5
   11ebe:	eb 57                	jmp    0x11f17
   11ec0:	66 3d 00 40          	cmp    ax,0x4000
   11ec4:	75 2c                	jne    0x11ef2
   11ec6:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11ecc:	83 c6 38             	add    esi,0x38
   11ecf:	2b 35 78 15 00 00    	sub    esi,DWORD PTR ds:0x1578
   11ed5:	8b 16                	mov    edx,DWORD PTR [esi]
   11ed7:	89 17                	mov    DWORD PTR [edi],edx
   11ed9:	83 c6 04             	add    esi,0x4
   11edc:	83 c7 04             	add    edi,0x4
   11edf:	8b 16                	mov    edx,DWORD PTR [esi]
   11ee1:	89 17                	mov    DWORD PTR [edi],edx
   11ee3:	83 ee 0c             	sub    esi,0xc
   11ee6:	81 c7 3c 01 00 00    	add    edi,0x13c
   11eec:	fe c8                	dec    al
   11eee:	75 e5                	jne    0x11ed5
   11ef0:	eb 25                	jmp    0x11f17
   11ef2:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11ef8:	83 c6 3f             	add    esi,0x3f
   11efb:	2b 35 78 15 00 00    	sub    esi,DWORD PTR ds:0x1578
   11f01:	b4 08                	mov    ah,0x8
   11f03:	8a 16                	mov    dl,BYTE PTR [esi]
   11f05:	88 17                	mov    BYTE PTR [edi],dl
   11f07:	4e                   	dec    esi
   11f08:	47                   	inc    edi
   11f09:	fe cc                	dec    ah
   11f0b:	75 f6                	jne    0x11f03
   11f0d:	81 c7 38 01 00 00    	add    edi,0x138
   11f13:	fe c8                	dec    al
   11f15:	75 ea                	jne    0x11f01
   11f17:	c3                   	ret    
   11f18:	c1 e6 06             	shl    esi,0x6
   11f1b:	03 35 82 15 00 00    	add    esi,DWORD PTR ds:0x1582
   11f21:	66 8b 03             	mov    ax,WORD PTR [ebx]
   11f24:	66 25 00 c0          	and    ax,0xc000
   11f28:	66 0b c0             	or     ax,ax
   11f2b:	75 2a                	jne    0x11f57
   11f2d:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11f33:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11f39:	8b ca                	mov    ecx,edx
   11f3b:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   11f3d:	b9 08 00 00 00       	mov    ecx,0x8
   11f42:	2b ca                	sub    ecx,edx
   11f44:	03 f1                	add    esi,ecx
   11f46:	03 f9                	add    edi,ecx
   11f48:	81 c7 38 01 00 00    	add    edi,0x138
   11f4e:	66 48                	dec    ax
   11f50:	75 e7                	jne    0x11f39
   11f52:	e9 8b 00 00 00       	jmp    0x11fe2
   11f57:	66 3d 00 80          	cmp    ax,0x8000
   11f5b:	75 2e                	jne    0x11f8b
   11f5d:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11f63:	03 35 78 15 00 00    	add    esi,DWORD PTR ds:0x1578
   11f69:	83 c6 07             	add    esi,0x7
   11f6c:	8a ca                	mov    cl,dl
   11f6e:	8a 26                	mov    ah,BYTE PTR [esi]
   11f70:	88 27                	mov    BYTE PTR [edi],ah
   11f72:	4e                   	dec    esi
   11f73:	47                   	inc    edi
   11f74:	fe c9                	dec    cl
   11f76:	75 f6                	jne    0x11f6e
   11f78:	03 f2                	add    esi,edx
   11f7a:	83 c6 08             	add    esi,0x8
   11f7d:	2b fa                	sub    edi,edx
   11f7f:	81 c7 40 01 00 00    	add    edi,0x140
   11f85:	fe c8                	dec    al
   11f87:	75 e3                	jne    0x11f6c
   11f89:	eb 57                	jmp    0x11fe2
   11f8b:	66 3d 00 40          	cmp    ax,0x4000
   11f8f:	75 26                	jne    0x11fb7
   11f91:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11f97:	83 c6 38             	add    esi,0x38
   11f9a:	2b 35 78 15 00 00    	sub    esi,DWORD PTR ds:0x1578
   11fa0:	8b ca                	mov    ecx,edx
   11fa2:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
   11fa4:	2b f2                	sub    esi,edx
   11fa6:	83 ee 08             	sub    esi,0x8
   11fa9:	2b fa                	sub    edi,edx
   11fab:	81 c7 40 01 00 00    	add    edi,0x140
   11fb1:	66 48                	dec    ax
   11fb3:	75 eb                	jne    0x11fa0
   11fb5:	eb 2b                	jmp    0x11fe2
   11fb7:	66 a1 7c 15 00 00    	mov    ax,ds:0x157c
   11fbd:	83 c6 3f             	add    esi,0x3f
   11fc0:	2b 35 78 15 00 00    	sub    esi,DWORD PTR ds:0x1578
   11fc6:	b1 08                	mov    cl,0x8
   11fc8:	2a ca                	sub    cl,dl
   11fca:	8a 26                	mov    ah,BYTE PTR [esi]
   11fcc:	88 27                	mov    BYTE PTR [edi],ah
   11fce:	4e                   	dec    esi
   11fcf:	47                   	inc    edi
   11fd0:	fe c9                	dec    cl
   11fd2:	75 f6                	jne    0x11fca
   11fd4:	2b f2                	sub    esi,edx
   11fd6:	81 c7 38 01 00 00    	add    edi,0x138
   11fdc:	03 fa                	add    edi,edx
   11fde:	fe c8                	dec    al
   11fe0:	75 e4                	jne    0x11fc6
   11fe2:	c3                   	ret    
   11fe3:	c1 e6 06             	shl    esi,0x6
   11fe6:	03 35 82 15 00 00    	add    esi,DWORD PTR ds:0x1582
   11fec:	66 8b 03             	mov    ax,WORD PTR [ebx]
   11fef:	66 25 00 c0          	and    ax,0xc000
   11ff3:	66 51                	push   cx
   11ff5:	b5 08                	mov    ch,0x8
   11ff7:	66 0b c0             	or     ax,ax
   11ffa:	75 25                	jne    0x12021
   11ffc:	03 f2                	add    esi,edx
   11ffe:	b1 08                	mov    cl,0x8
   12000:	2a ca                	sub    cl,dl
   12002:	8a 06                	mov    al,BYTE PTR [esi]
   12004:	0a c0                	or     al,al
   12006:	74 02                	je     0x1200a
   12008:	88 07                	mov    BYTE PTR [edi],al
   1200a:	46                   	inc    esi
   1200b:	47                   	inc    edi
   1200c:	fe c9                	dec    cl
   1200e:	75 f2                	jne    0x12002
   12010:	81 c7 38 01 00 00    	add    edi,0x138
   12016:	03 fa                	add    edi,edx
   12018:	fe cd                	dec    ch
   1201a:	75 e0                	jne    0x11ffc
   1201c:	e9 7f 00 00 00       	jmp    0x120a0
   12021:	66 3d 00 80          	cmp    ax,0x8000
   12025:	75 28                	jne    0x1204f
   12027:	83 c6 07             	add    esi,0x7
   1202a:	2b f2                	sub    esi,edx
   1202c:	b1 08                	mov    cl,0x8
   1202e:	2a ca                	sub    cl,dl
   12030:	8a 06                	mov    al,BYTE PTR [esi]
   12032:	0a c0                	or     al,al
   12034:	74 02                	je     0x12038
   12036:	88 07                	mov    BYTE PTR [edi],al
   12038:	4e                   	dec    esi
   12039:	47                   	inc    edi
   1203a:	fe c9                	dec    cl
   1203c:	75 f2                	jne    0x12030
   1203e:	83 c6 10             	add    esi,0x10
   12041:	81 c7 38 01 00 00    	add    edi,0x138
   12047:	03 fa                	add    edi,edx
   12049:	fe cd                	dec    ch
   1204b:	75 dd                	jne    0x1202a
   1204d:	eb 51                	jmp    0x120a0
   1204f:	66 3d 00 40          	cmp    ax,0x4000
   12053:	75 28                	jne    0x1207d
   12055:	83 c6 38             	add    esi,0x38
   12058:	03 f2                	add    esi,edx
   1205a:	b1 08                	mov    cl,0x8
   1205c:	2a ca                	sub    cl,dl
   1205e:	8a 06                	mov    al,BYTE PTR [esi]
   12060:	0a c0                	or     al,al
   12062:	74 02                	je     0x12066
   12064:	88 07                	mov    BYTE PTR [edi],al
   12066:	46                   	inc    esi
   12067:	47                   	inc    edi
   12068:	fe c9                	dec    cl
   1206a:	75 f2                	jne    0x1205e
   1206c:	83 ee 10             	sub    esi,0x10
   1206f:	81 c7 38 01 00 00    	add    edi,0x138
   12075:	03 fa                	add    edi,edx
   12077:	fe cd                	dec    ch
   12079:	75 dd                	jne    0x12058
   1207b:	eb 23                	jmp    0x120a0
   1207d:	83 c6 3f             	add    esi,0x3f
   12080:	2b f2                	sub    esi,edx
   12082:	b1 08                	mov    cl,0x8
   12084:	2a ca                	sub    cl,dl
   12086:	8a 06                	mov    al,BYTE PTR [esi]
   12088:	0a c0                	or     al,al
   1208a:	74 02                	je     0x1208e
   1208c:	88 07                	mov    BYTE PTR [edi],al
   1208e:	4e                   	dec    esi
   1208f:	47                   	inc    edi
   12090:	fe c9                	dec    cl
   12092:	75 f2                	jne    0x12086
   12094:	81 c7 38 01 00 00    	add    edi,0x138
   1209a:	03 fa                	add    edi,edx
   1209c:	fe cd                	dec    ch
   1209e:	75 e0                	jne    0x12080
   120a0:	66 59                	pop    cx
   120a2:	83 c3 02             	add    ebx,0x2
   120a5:	2b fa                	sub    edi,edx
   120a7:	81 ef f8 09 00 00    	sub    edi,0x9f8
   120ad:	c3                   	ret    
   120ae:	c1 e6 06             	shl    esi,0x6
   120b1:	03 35 82 15 00 00    	add    esi,DWORD PTR ds:0x1582
   120b7:	66 8b 03             	mov    ax,WORD PTR [ebx]
   120ba:	66 25 00 c0          	and    ax,0xc000
   120be:	b6 08                	mov    dh,0x8
   120c0:	66 0b c0             	or     ax,ax
   120c3:	75 1c                	jne    0x120e1
   120c5:	b2 08                	mov    dl,0x8
   120c7:	8a 06                	mov    al,BYTE PTR [esi]
   120c9:	0a c0                	or     al,al
   120cb:	74 02                	je     0x120cf
   120cd:	88 07                	mov    BYTE PTR [edi],al
   120cf:	46                   	inc    esi
   120d0:	47                   	inc    edi
   120d1:	fe ca                	dec    dl
   120d3:	75 f2                	jne    0x120c7
   120d5:	81 c7 38 01 00 00    	add    edi,0x138
   120db:	fe ce                	dec    dh
   120dd:	75 e6                	jne    0x120c5
   120df:	eb 6d                	jmp    0x1214e
   120e1:	66 3d 00 80          	cmp    ax,0x8000
   120e5:	75 22                	jne    0x12109
   120e7:	83 c6 07             	add    esi,0x7
   120ea:	b2 08                	mov    dl,0x8
   120ec:	8a 06                	mov    al,BYTE PTR [esi]
   120ee:	0a c0                	or     al,al
   120f0:	74 02                	je     0x120f4
   120f2:	88 07                	mov    BYTE PTR [edi],al
   120f4:	4e                   	dec    esi
   120f5:	47                   	inc    edi
   120f6:	fe ca                	dec    dl
   120f8:	75 f2                	jne    0x120ec
   120fa:	83 c6 10             	add    esi,0x10
   120fd:	81 c7 38 01 00 00    	add    edi,0x138
   12103:	fe ce                	dec    dh
   12105:	75 e3                	jne    0x120ea
   12107:	eb 45                	jmp    0x1214e
   12109:	66 3d 00 40          	cmp    ax,0x4000
   1210d:	75 22                	jne    0x12131
   1210f:	83 c6 38             	add    esi,0x38
   12112:	b2 08                	mov    dl,0x8
   12114:	8a 06                	mov    al,BYTE PTR [esi]
   12116:	0a c0                	or     al,al
   12118:	74 02                	je     0x1211c
   1211a:	88 07                	mov    BYTE PTR [edi],al
   1211c:	46                   	inc    esi
   1211d:	47                   	inc    edi
   1211e:	fe ca                	dec    dl
   12120:	75 f2                	jne    0x12114
   12122:	83 ee 10             	sub    esi,0x10
   12125:	81 c7 38 01 00 00    	add    edi,0x138
   1212b:	fe ce                	dec    dh
   1212d:	75 e3                	jne    0x12112
   1212f:	eb 1d                	jmp    0x1214e
   12131:	83 c6 3f             	add    esi,0x3f
   12134:	b2 08                	mov    dl,0x8
   12136:	8a 06                	mov    al,BYTE PTR [esi]
   12138:	0a c0                	or     al,al
   1213a:	74 02                	je     0x1213e
   1213c:	88 07                	mov    BYTE PTR [edi],al
   1213e:	4e                   	dec    esi
   1213f:	47                   	inc    edi
   12140:	fe ca                	dec    dl
   12142:	75 f2                	jne    0x12136
   12144:	81 c7 38 01 00 00    	add    edi,0x138
   1214a:	fe ce                	dec    dh
   1214c:	75 e6                	jne    0x12134
   1214e:	c3                   	ret    
   1214f:	c1 e6 06             	shl    esi,0x6
   12152:	03 35 82 15 00 00    	add    esi,DWORD PTR ds:0x1582
   12158:	66 8b 03             	mov    ax,WORD PTR [ebx]
   1215b:	66 25 00 c0          	and    ax,0xc000
   1215f:	b5 08                	mov    ch,0x8
   12161:	66 0b c0             	or     ax,ax
   12164:	75 23                	jne    0x12189
   12166:	8a ca                	mov    cl,dl
   12168:	8a 06                	mov    al,BYTE PTR [esi]
   1216a:	0a c0                	or     al,al
   1216c:	74 02                	je     0x12170
   1216e:	88 07                	mov    BYTE PTR [edi],al
   12170:	46                   	inc    esi
   12171:	47                   	inc    edi
   12172:	fe c9                	dec    cl
   12174:	75 f2                	jne    0x12168
   12176:	2b f2                	sub    esi,edx
   12178:	83 c6 08             	add    esi,0x8
   1217b:	2b fa                	sub    edi,edx
   1217d:	81 c7 40 01 00 00    	add    edi,0x140
   12183:	fe cd                	dec    ch
   12185:	75 df                	jne    0x12166
   12187:	eb 7c                	jmp    0x12205
   12189:	66 3d 00 80          	cmp    ax,0x8000
   1218d:	75 26                	jne    0x121b5
   1218f:	83 c6 07             	add    esi,0x7
   12192:	8a ca                	mov    cl,dl
   12194:	8a 06                	mov    al,BYTE PTR [esi]
   12196:	0a c0                	or     al,al
   12198:	74 02                	je     0x1219c
   1219a:	88 07                	mov    BYTE PTR [edi],al
   1219c:	4e                   	dec    esi
   1219d:	47                   	inc    edi
   1219e:	fe c9                	dec    cl
   121a0:	75 f2                	jne    0x12194
   121a2:	03 f2                	add    esi,edx
   121a4:	83 c6 08             	add    esi,0x8
   121a7:	2b fa                	sub    edi,edx
   121a9:	81 c7 40 01 00 00    	add    edi,0x140
   121af:	fe cd                	dec    ch
   121b1:	75 df                	jne    0x12192
   121b3:	eb 50                	jmp    0x12205
   121b5:	66 3d 00 40          	cmp    ax,0x4000
   121b9:	75 26                	jne    0x121e1
   121bb:	83 c6 38             	add    esi,0x38
   121be:	8a ca                	mov    cl,dl
   121c0:	8a 06                	mov    al,BYTE PTR [esi]
   121c2:	0a c0                	or     al,al
   121c4:	74 02                	je     0x121c8
   121c6:	88 07                	mov    BYTE PTR [edi],al
   121c8:	46                   	inc    esi
   121c9:	47                   	inc    edi
   121ca:	fe c9                	dec    cl
   121cc:	75 f2                	jne    0x121c0
   121ce:	2b f2                	sub    esi,edx
   121d0:	83 ee 08             	sub    esi,0x8
   121d3:	2b fa                	sub    edi,edx
   121d5:	81 c7 40 01 00 00    	add    edi,0x140
   121db:	fe cd                	dec    ch
   121dd:	75 df                	jne    0x121be
   121df:	eb 24                	jmp    0x12205
   121e1:	83 c6 3f             	add    esi,0x3f
   121e4:	8a ca                	mov    cl,dl
   121e6:	8a 06                	mov    al,BYTE PTR [esi]
   121e8:	0a c0                	or     al,al
   121ea:	74 02                	je     0x121ee
   121ec:	88 07                	mov    BYTE PTR [edi],al
   121ee:	4e                   	dec    esi
   121ef:	47                   	inc    edi
   121f0:	fe c9                	dec    cl
   121f2:	75 f2                	jne    0x121e6
   121f4:	03 f2                	add    esi,edx
   121f6:	83 ee 08             	sub    esi,0x8
   121f9:	2b fa                	sub    edi,edx
   121fb:	81 c7 40 01 00 00    	add    edi,0x140
   12201:	fe cd                	dec    ch
   12203:	75 df                	jne    0x121e4
   12205:	c3                   	ret    
