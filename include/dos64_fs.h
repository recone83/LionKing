#ifndef DOS64_FS_H
#define DOS64_FS_H

/* stdio-style file access, directory listing and raw disk access for DOS64 programs.
 * Header-only wrappers over DOS64_API.Fs / DOS64_API.Disk. Call fs_init(Api) first.
 * Names match the C library, so do not combine with another libc. */

#include "dos64_api.h"

typedef void FILE;
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

static const DOS64_API *Dos64Fs;

static inline void fs_init(const DOS64_API *Api)
{
    Dos64Fs = Api;
}

static inline FILE *fopen(const char *Path, const char *Mode) { return Dos64Fs->Fs.Open(Path, Mode); }
static inline int fclose(FILE *File) { return Dos64Fs->Fs.Close(File); }
static inline unsigned long long fread(void *Buffer, unsigned long long Size, unsigned long long Count, FILE *File)
{
    return Dos64Fs->Fs.Read(Buffer, Size, Count, File);
}
static inline unsigned long long fwrite(const void *Buffer, unsigned long long Size, unsigned long long Count, FILE *File)
{
    return Dos64Fs->Fs.Write(Buffer, Size, Count, File);
}
static inline int fseek(FILE *File, long long Offset, int Whence) { return Dos64Fs->Fs.Seek(File, Offset, Whence); }
static inline long long ftell(FILE *File) { return Dos64Fs->Fs.Tell(File); }
static inline int feof(FILE *File) { return Dos64Fs->Fs.Eof(File); }
static inline int ferror(FILE *File) { return Dos64Fs->Fs.Error(File); }
static inline int fflush(FILE *File) { return Dos64Fs->Fs.Flush(File); }
static inline int fgetc(FILE *File) { return Dos64Fs->Fs.GetChar(File); }
static inline int fputc(int Character, FILE *File) { return Dos64Fs->Fs.PutChar(Character, File); }
static inline int remove(const char *Path) { return Dos64Fs->Fs.Remove(Path); }
static inline int rename(const char *OldPath, const char *NewPath) { return Dos64Fs->Fs.Rename(OldPath, NewPath); }
static inline int mkdir(const char *Path) { return Dos64Fs->Fs.MakeDir(Path); }
static inline int rmdir(const char *Path) { return Dos64Fs->Fs.RemoveDir(Path); }
static inline int chdir(const char *Path) { return Dos64Fs->Fs.ChangeDir(Path); }

static inline int fputs(const char *Text, FILE *File)
{
    while (*Text != '\0') {
        if (fputc((unsigned char)*Text++, File) == EOF) {
            return EOF;
        }
    }
    return 0;
}

static inline char *fgets(char *Buffer, int Size, FILE *File)
{
    int Length = 0;
    int Character;

    while (Length < Size - 1 && (Character = fgetc(File)) != EOF) {
        Buffer[Length++] = (char)Character;
        if (Character == '\n') {
            break;
        }
    }
    Buffer[Length] = '\0';
    return Length == 0 ? (char *)0 : Buffer;
}

/* Directory listing: fill Entry with the Index-th entry of the working directory; 0 past the end. */
static inline int readdir(unsigned int Index, DOS64_DIRENT *Entry) { return Dos64Fs->Fs.ReadDir(Index, Entry); }

/* FAT date/time decoding. */
static inline unsigned int fat_year(unsigned short Date) { return 1980u + (Date >> 9); }
static inline unsigned int fat_month(unsigned short Date) { return (Date >> 5) & 15u; }
static inline unsigned int fat_day(unsigned short Date) { return Date & 31u; }
static inline unsigned int fat_hour(unsigned short Time) { return Time >> 11; }
static inline unsigned int fat_minute(unsigned short Time) { return (Time >> 5) & 63u; }
static inline unsigned int fat_second(unsigned short Time) { return (Time & 31u) * 2u; }

/* Raw disk: 0 on success, otherwise an EFI status. */
static inline int disk_present(void) { return (int)Dos64Fs->Disk.Present; }
static inline unsigned int disk_sector_size(void) { return Dos64Fs->Disk.SectorSize; }
static inline unsigned long long disk_sector_count(void) { return Dos64Fs->Disk.SectorCount; }
static inline unsigned long long disk_read(unsigned long long Lba, unsigned long long Count, void *Buffer)
{
    return Dos64Fs->Disk.ReadSectors(Lba, Count, Buffer);
}
static inline unsigned long long disk_write(unsigned long long Lba, unsigned long long Count, const void *Buffer)
{
    return Dos64Fs->Disk.WriteSectors(Lba, Count, Buffer);
}
static inline unsigned long long disk_flush(void) { return Dos64Fs->Disk.Flush(); }

#endif
