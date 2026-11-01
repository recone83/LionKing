#ifndef DOS64_AUDIO_STREAM_H
#define DOS64_AUDIO_STREAM_H

#include "dos64_audio.h"
#include "dos64_queue.h"

typedef struct WAV_STREAM {
    const DOS64_API *Api;
    WAV *Wav;
    DOS64_QUEUE Commands;
    unsigned int CommandStorage;
    DOS64_THREAD Worker;
    int Finished, Failed;
} WAV_STREAM;

static void *__attribute__((ms_abi)) wav_stream_worker(void *Argument)
{
    WAV_STREAM *Stream = Argument;
    WAV *Wav = Stream->Wav;
    int Exhausted = 0;

    for (;;) {
        unsigned int Command;
        int Status = queue_try_receive(&Stream->Commands, &Command);
        if (Status == QUEUE_OK || Status == QUEUE_CLOSED) { break; }
        if (Status == QUEUE_ERROR) { Stream->Failed = 1; break; }
        if (Wav->OutPos == Wav->OutCount && !Exhausted) {
            Exhausted = !wav_generate(Wav);
            if ((Wav->File && ferror(Wav->File)) || Wav->ReadFailed) {
                Stream->Api->Write("AUDIO STREAM FAILED: WAV read\n");
                Stream->Failed = 1;
                break;
            }
        }
        if (Wav->OutPos < Wav->OutCount) {
            unsigned long long Available = Stream->Api->Audio.FreeFrames();
            unsigned int Want = Wav->OutCount - Wav->OutPos;
            if (Available < Want) { Want = (unsigned int)Available; }
            if (Want) {
                unsigned long long Taken = Stream->Api->Audio.Write(Wav->Out + Wav->OutPos * 2, Want);
                if (!Taken || Taken > Want) {
                    Stream->Api->Write("AUDIO STREAM FAILED: audio write\n");
                    Stream->Failed = 1;
                    break;
                }
                Wav->OutPos += (unsigned int)Taken;
            }
        } else if (Exhausted && Stream->Api->Audio.QueuedFrames() == 0) { break; }
        /* One bounded decode/write batch per turn; never monopolize the scheduler. */
        Stream->Api->Sleep(1);
    }
    Stream->Finished = 1;
    return 0;
}

/* Zero-initialize Stream. Wav must have a file or PCM source; one audio owner is supported. */
static inline int wav_stream_start(WAV_STREAM *Stream, const DOS64_API *Api, WAV *Wav)
{
    if (!Stream || !Wav || (!Wav->File && !Wav->Samples) || thread_sync_init(Api) != 0 ||
        !Api->Audio.Present || !Api->Audio.Open || !Api->Audio.Write ||
        !Api->Audio.FreeFrames || !Api->Audio.QueuedFrames || !Api->Audio.Stop ||
        (Wav->File && (!Api->Fs.Read || !Api->Fs.Error)) ||
        Stream->Worker || Stream->Commands.Mutex) {
        if (Api && Api->Write) { Api->Write("AUDIO STREAM FAILED: invalid stream or unavailable API\n"); }
        return -1;
    }
    Stream->Api = Api;
    Stream->Wav = Wav;
    Stream->Finished = Stream->Failed = 0;
    if (queue_init(&Stream->Commands, Api, &Stream->CommandStorage, 1,
                   sizeof(Stream->CommandStorage)) != QUEUE_OK) { return -1; }
    audio_init(Api);
    if (wav_start(Wav) != 0) {
        Api->Write("AUDIO STREAM FAILED: audio open\n");
        (void)queue_destroy(&Stream->Commands);
        return -1;
    }
    Stream->Worker = Api->Threads.Create(wav_stream_worker, Stream, 0);
    if (!Stream->Worker) {
        Api->Write("AUDIO STREAM FAILED: worker create\n");
        Api->Audio.Stop();
        (void)queue_destroy(&Stream->Commands);
        return -1;
    }
    return 0;
}

/* Cooperative status snapshot: 0 running, 1 finished, -1 failed. Does not switch. */
static inline int wav_stream_status(const WAV_STREAM *Stream)
{
    if (!Stream || !Stream->Api || !Stream->Worker) {
        if (Stream && Stream->Api) { Stream->Api->Write("AUDIO STREAM FAILED: inactive status query\n"); }
        return -1;
    }
    return Stream->Failed ? -1 : Stream->Finished;
}

/* Cancels if still playing, joins before stopping audio. Caller closes the WAV afterwards. */
static inline int wav_stream_stop(WAV_STREAM *Stream)
{
    if (!Stream || !Stream->Api || !Stream->Worker) {
        if (Stream && Stream->Api) { Stream->Api->Write("AUDIO STREAM FAILED: inactive stop\n"); }
        return -1;
    }
    if (queue_close(&Stream->Commands) != QUEUE_OK) { return -1; }
    if (Stream->Api->Threads.Join(Stream->Worker, 0) != 0) { return -1; }
    Stream->Worker = 0;
    Stream->Api->Audio.Stop();
    if (queue_destroy(&Stream->Commands) != QUEUE_OK) { return -1; }
    return Stream->Failed ? -1 : 0;
}

#endif
