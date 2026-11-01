#ifndef DOS64_API_H
#define DOS64_API_H

/* Passed to a program's entry point in RCX (Microsoft x64 ABI for PE and ELF).
 * The program runs in ring 0 with full access to the machine; the table is only a convenience.
 * Entry point: int __attribute__((ms_abi)) start(const DOS64_API *Api); the return value is
 * the exit code shown by the shell. Fields are only ever appended; check Size before use. */
/* Colors are straight-alpha 0xAARRGGBB. Alpha is 0 transparent, 255 opaque; blending is source-over.
 * Graphics coordinates are signed pixels (clipped to the selected surface).
 * Drawing goes to a back buffer; call Present() to show it. The text console shares the screen.
 * Layer 0 is the screen-sized opaque base; created layers start transparent and are composited
 * source-over in ascending Z order. Drawing targets the selected layer, with coordinates local to
 * that surface. Opacity is 0..255. Layer calls return 0 (or a handle) on success, -1 on failure. */
typedef unsigned int DOS64_COLOR;

#define DOS64_COLOR_ARGB(A, R, G, B) \
    ((((unsigned int)(A) & 0xFFU) << 24) | (((unsigned int)(R) & 0xFFU) << 16) | \
     (((unsigned int)(G) & 0xFFU) << 8) | ((unsigned int)(B) & 0xFFU))

typedef struct DOS64_RECT {
    int X, Y, Width, Height;
    DOS64_COLOR Color;
} DOS64_RECT;

typedef struct DOS64_GFX {
    unsigned int Width, Height;                                    /* screen size in pixels */
    void (__attribute__((ms_abi)) *SetColor)(DOS64_COLOR Color);
    void (__attribute__((ms_abi)) *Clear)(void);                   /* replace surface contents with the color */
    void (__attribute__((ms_abi)) *PutPixel)(int X, int Y);
    DOS64_COLOR (__attribute__((ms_abi)) *GetPixel)(int X, int Y);   /* 0 outside surface */
    void (__attribute__((ms_abi)) *Line)(int X0, int Y0, int X1, int Y1);
    void (__attribute__((ms_abi)) *Rect)(int X, int Y, int Width, int Height);       /* outline */
    void (__attribute__((ms_abi)) *FillRect)(int X, int Y, int Width, int Height);
    void (__attribute__((ms_abi)) *Circle)(int Cx, int Cy, int Radius);              /* outline */
    void (__attribute__((ms_abi)) *FillCircle)(int Cx, int Cy, int Radius);
    void (__attribute__((ms_abi)) *Present)(void);                 /* show everything drawn so far */
    int (__attribute__((ms_abi)) *CreateLayer)(unsigned int Width, unsigned int Height);
    int (__attribute__((ms_abi)) *DestroyLayer)(int Layer);
    int (__attribute__((ms_abi)) *SelectLayer)(int Layer);
    int (__attribute__((ms_abi)) *SetLayerPosition)(int Layer, int X, int Y);
    int (__attribute__((ms_abi)) *SetLayerOpacity)(int Layer, unsigned int Opacity);
    int (__attribute__((ms_abi)) *SetLayerVisible)(int Layer, int Visible);
    int (__attribute__((ms_abi)) *SetLayerZOrder)(int Layer, int ZOrder);
} DOS64_GFX;

/* Input, never blocking. Call Poll() once per frame/loop: it drains the keyboard and mouse and
 * refreshes the state below. KeyDown is indexed by USB HID usage (0x04 = A, 0x28 = Enter, 0x29 = Esc,
 * 0x4F..0x52 = right/left/down/up, 0xE0..0xE7 = Ctrl/Shift/Alt/GUI left+right, see dos64_input.h).
 * KeyPressed / KeyReleased / ButtonsPressed / ButtonsReleased are set when the transition happened
 * since the previous Poll(), so a quick tap between two polls is never lost. */
typedef struct DOS64_INPUT {
    void (__attribute__((ms_abi)) *Poll)(void);
    int (__attribute__((ms_abi)) *GetChar)(void);   /* next typed ASCII character from the last Polls, or -1 */
    unsigned char KeyDown[256];
    unsigned char KeyPressed[256];
    unsigned char KeyReleased[256];
    unsigned char Modifiers;                        /* HID modifier bitmap: 1 Ctrl, 2 Shift, 4 Alt, 8 GUI (+16 for right) */
    unsigned char Buttons;                          /* bit 0 left, 1 right, 2 middle */
    unsigned char ButtonsPressed;
    unsigned char ButtonsReleased;
    int MouseX, MouseY;                             /* pointer position in screen pixels */
    int MouseDX, MouseDY, Wheel;                    /* movement accumulated since the previous Poll() */
} DOS64_INPUT;

/* Files on DOS64's mounted FAT32 volume or the Windows host filesystem. Paths use '/' or '\\'; relative
 * paths start at the shell/process working directory. FILE handles are opaque; at most 8 may be open and
 * the kernel closes any left open when the program returns. Modes: r w a r+ w+ a+ (b is ignored).
 * Int results are 0 on success and -1 on failure unless stated; LastError is the EFI status. */
typedef struct DOS64_DIRENT {
    char Name[256];
    unsigned int Size;
    unsigned int IsDirectory;
    unsigned short Date, Time;                     /* last write, FAT encoding: see dos64_fs.h */
} DOS64_DIRENT;

typedef struct DOS64_FS {
    void *(__attribute__((ms_abi)) *Open)(const char *Path, const char *Mode);   /* NULL on failure */
    int (__attribute__((ms_abi)) *Close)(void *File);
    unsigned long long (__attribute__((ms_abi)) *Read)(void *Buffer, unsigned long long Size, unsigned long long Count, void *File);
    unsigned long long (__attribute__((ms_abi)) *Write)(const void *Buffer, unsigned long long Size, unsigned long long Count, void *File);
    int (__attribute__((ms_abi)) *Seek)(void *File, long long Offset, int Whence);   /* signed 64-bit; 0 set, 1 cur, 2 end */
    long long (__attribute__((ms_abi)) *Tell)(void *File);
    int (__attribute__((ms_abi)) *Eof)(void *File);
    int (__attribute__((ms_abi)) *Error)(void *File);
    int (__attribute__((ms_abi)) *Flush)(void *File);                           /* NULL flushes every open file */
    int (__attribute__((ms_abi)) *GetChar)(void *File);                         /* byte or -1 */
    int (__attribute__((ms_abi)) *PutChar)(int Character, void *File);
    int (__attribute__((ms_abi)) *Remove)(const char *Path);
    int (__attribute__((ms_abi)) *Rename)(const char *OldPath, const char *NewPath);
    int (__attribute__((ms_abi)) *MakeDir)(const char *Path);
    int (__attribute__((ms_abi)) *RemoveDir)(const char *Path);
    int (__attribute__((ms_abi)) *ChangeDir)(const char *Path);
    int (__attribute__((ms_abi)) *ReadDir)(unsigned int Index, DOS64_DIRENT *Entry);   /* entry Index of the working directory: 1, or 0 past the end */
    unsigned long long (__attribute__((ms_abi)) *LastError)(void);
} DOS64_FS;

/* Raw access to the whole USB data disk, below the file system: you may overwrite anything,
 * including the partition table and FAT. Sectors are SectorSize bytes. Present is 0 when no
 * disk is attached. Returns 0 on success, otherwise an EFI status. */
typedef struct DOS64_DISK {
    unsigned int Present;
    unsigned int SectorSize;
    unsigned long long SectorCount;
    unsigned long long (__attribute__((ms_abi)) *ReadSectors)(unsigned long long Lba, unsigned long long Count, void *Buffer);
    unsigned long long (__attribute__((ms_abi)) *WriteSectors)(unsigned long long Lba, unsigned long long Count, const void *Buffer);
    unsigned long long (__attribute__((ms_abi)) *Flush)(void);
} DOS64_DISK;

/* Time. Monotonic values come from the calibrated TSC (nanosecond resolution, start near 0 at boot).
 * Now() reads the real-time clock (1 s resolution, UTC as set in firmware). UnixNanoseconds() is the
 * wall clock extended with the TSC, so it is precise to ~ns but only as accurate as the RTC second
 * captured when the program started (up to 1 s off). */
typedef struct DOS64_DATETIME {
    unsigned short Year;
    unsigned char Month, Day, Hour, Minute, Second, Weekday;   /* Weekday 0 = Sunday */
    unsigned int Nanosecond;
} DOS64_DATETIME;

typedef struct DOS64_TIME {
    unsigned long long (__attribute__((ms_abi)) *Ticks)(void);              /* raw TSC */
    unsigned long long TicksPerSecond;
    unsigned long long (__attribute__((ms_abi)) *Nanoseconds)(void);        /* monotonic */
    void (__attribute__((ms_abi)) *DelayNanoseconds)(unsigned long long Ns);   /* busy-wait, no HLT, no polling */
    int (__attribute__((ms_abi)) *Now)(DOS64_DATETIME *Time);               /* 0 on success */
    unsigned long long (__attribute__((ms_abi)) *UnixNanoseconds)(void);    /* since 1970-01-01 UTC, 0 if no clock */
} DOS64_TIME;

/* Audio: 16-bit signed interleaved stereo, 48000 or 44100 Hz, non-blocking ring buffer.
 * Present is 0 when there is no usable output. Open() restarts the stream (returns 0 on success).
 * Write() accepts as many frames as fit and returns that count. The kernel stops audio when the
 * program exits. Volume is 0..100. */
typedef struct DOS64_AUDIO {
    unsigned long long Present;
    int (__attribute__((ms_abi)) *Open)(unsigned int SampleRate);
    unsigned long long (__attribute__((ms_abi)) *Write)(const short *Frames, unsigned long long FrameCount);
    unsigned long long (__attribute__((ms_abi)) *FreeFrames)(void);
    unsigned long long (__attribute__((ms_abi)) *QueuedFrames)(void);
    void (__attribute__((ms_abi)) *Stop)(void);
    void (__attribute__((ms_abi)) *Volume)(unsigned int Percent);
} DOS64_AUDIO;

/* System status, appended in API version 9. HOST means Windows-managed input;
 * Windows StorageDevices counts accessible volumes, and Partition=0 means unknown. */
#define DOS64_DEVICE_NONE 0
#define DOS64_DEVICE_USB 1
#define DOS64_DEVICE_PS2 2
#define DOS64_DEVICE_HOST 3
#define DOS64_DEVICE_I2C 4

typedef struct DOS64_DRIVE_INFO {
    char Letter;
    char Device[8];
    unsigned char Partition;
    unsigned char Writable;
    unsigned char Current;
    unsigned long long SizeBytes;
} DOS64_DRIVE_INFO;

typedef struct DOS64_SYSTEM {
    unsigned int Keyboard;
    unsigned int Mouse;
    unsigned int StorageDevices;
    int (__attribute__((ms_abi)) *DriveInfo)(unsigned int Index, DOS64_DRIVE_INFO *Info);
} DOS64_SYSTEM;

/* Console styles affect the framebuffer only; Write still logs plain text. */
typedef enum DOS64_TEXT_STYLE {
    DOS64_TEXT_DEFAULT,
    DOS64_TEXT_CYAN,
    DOS64_TEXT_LAVENDER,
    DOS64_TEXT_CORAL,
    DOS64_TEXT_MUTED,
    DOS64_TEXT_SUCCESS
} DOS64_TEXT_STYLE;

typedef unsigned long long DOS64_THREAD;
typedef void *(__attribute__((ms_abi)) *DOS64_THREAD_ENTRY)(void *Argument);

typedef struct DOS64_THREADS {
    DOS64_THREAD (__attribute__((ms_abi)) *Create)(DOS64_THREAD_ENTRY Entry, void *Argument,
                                                  unsigned int StackBytes);
    int (__attribute__((ms_abi)) *Yield)(void);
    int (__attribute__((ms_abi)) *Join)(DOS64_THREAD Thread, void **Result);
    DOS64_THREAD (__attribute__((ms_abi)) *Self)(void);
} DOS64_THREADS;

typedef unsigned long long DOS64_MUTEX;
typedef unsigned long long DOS64_CONDITION;

typedef struct DOS64_SYNC {
    DOS64_MUTEX (__attribute__((ms_abi)) *MutexCreate)(void);
    int (__attribute__((ms_abi)) *MutexDestroy)(DOS64_MUTEX Mutex);
    int (__attribute__((ms_abi)) *MutexLock)(DOS64_MUTEX Mutex);
    int (__attribute__((ms_abi)) *MutexUnlock)(DOS64_MUTEX Mutex);
    DOS64_CONDITION (__attribute__((ms_abi)) *ConditionCreate)(void);
    int (__attribute__((ms_abi)) *ConditionDestroy)(DOS64_CONDITION Condition);
    int (__attribute__((ms_abi)) *ConditionWait)(DOS64_CONDITION Condition, DOS64_MUTEX Mutex);
    int (__attribute__((ms_abi)) *ConditionSignal)(DOS64_CONDITION Condition);
    int (__attribute__((ms_abi)) *ConditionBroadcast)(DOS64_CONDITION Condition);
} DOS64_SYNC;

typedef struct DOS64_API {
    unsigned long long Size;                       /* sizeof(DOS64_API) of the running kernel */
    unsigned long long Version;
    const char *Arguments;                         /* text after the program name, never NULL */
    void (__attribute__((ms_abi)) *Write)(const char *Text);   /* screen + serial + log */
    void (__attribute__((ms_abi)) *Sleep)(unsigned int Milliseconds);
    DOS64_GFX Gfx;
    DOS64_INPUT Input;
    DOS64_FS Fs;
    DOS64_DISK Disk;
    DOS64_TIME Time;
    DOS64_AUDIO Audio;
    DOS64_SYSTEM System;
    /* Version 10+: returns 0 on success, -1 for an unsupported style. */
    int (__attribute__((ms_abi)) *SetTextStyle)(DOS64_TEXT_STYLE Style);
    /* Version 11+: cooperative single-CPU thread lifecycle. */
    DOS64_THREADS Threads;
    /* Version 12+: synchronization; Sleep now blocks only the calling thread. */
    DOS64_SYNC Sync;
    /* Version 13+: draw colored rectangles with one API transition. */
    void (__attribute__((ms_abi)) *FillRects)(const DOS64_RECT *Rectangles, unsigned int Count);
    /* Version 14+: copy an opaque ARGB image (alpha ignored) into the selected surface,
     * nearest-neighbour scaled from SourceWidth x SourceHeight to Width x Height at X,Y.
     * Stride is the source row length in pixels; destination sizes are limited to 65535. */
    void (__attribute__((ms_abi)) *DrawImage)(const DOS64_COLOR *Pixels,
        unsigned int SourceWidth, unsigned int SourceHeight, unsigned int Stride,
        int X, int Y, unsigned int Width, unsigned int Height);
} DOS64_API;

#define DOS64_API_VERSION 14

#endif
