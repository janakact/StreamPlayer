#include <string.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

  #include <windows.h>
  #include <conio.h>

#include "inc/fmod.h"
#include "inc/fmod_errors.h"
int channel = -1;
int g_lenth=0;
long g_pos=0;
FSOUND_STREAM *stream;
FSOUND_SAMPLE *sptr;


void *F_CALLBACKAPI myopen(const char *name)
{
    return (void *)fopen(name, "rb");
}

void F_CALLBACKAPI myclose(void *handle)
{
    fclose((FILE *)handle);
}

int F_CALLBACKAPI myread(void *buffer, int size, void *handle)
{
    return fread(buffer, 1, size, (FILE *)handle);
}

int F_CALLBACKAPI myseek(void *handle, int pos, signed char mode)
{
    return fseek((FILE *)handle, pos, mode);
}

int F_CALLBACKAPI mytell(void *handle)
{
    return ftell((FILE *)handle);
}



signed char F_CALLBACKAPI endcallback(FSOUND_STREAM *stream, void *buff, int len, void *param)
{
    return true;
}

int stream_play(FSOUND_STREAM *Pstream)
{
	channel = FSOUND_Stream_PlayEx(FSOUND_FREE, stream, NULL, true);
	FSOUND_SetPaused(channel, false);
	return 0;
}

int stream_set_state(int key)
{
	if ( channel < 0)
	{
		channel = FSOUND_Stream_PlayEx(FSOUND_FREE, stream, NULL, true);
		FSOUND_SetPaused(channel, false);
	}
	if (key==0)
	{
		FSOUND_SetPaused(channel, !FSOUND_GetPaused(channel));
	}

	else if(key==1)
	{
		FSOUND_Stream_SetTime(stream, FSOUND_Stream_GetTime(stream) - 4000);
	}
	else if(key==2)
	{
		FSOUND_Stream_SetTime(stream, FSOUND_Stream_GetTime(stream) + 4000);
	}
	return 0;
}

int open_stream(char *file)
{
    FSOUND_Stream_SetBufferSize(1000);
	stream = FSOUND_Stream_Open(file, FSOUND_NORMAL | FSOUND_MPEGACCURATE, 0, 0);
    if (!stream)
    {

		FSOUND_Close();
        return 1;
    }

    sptr = FSOUND_Stream_GetSample(stream);
    if (sptr)
    {
        int freq;
        FSOUND_Sample_GetDefaults(sptr, &freq, NULL, NULL, NULL);
    }


}

int fmod_configer()
{

    FSOUND_Close();
    FSOUND_SetOutput(FSOUND_OUTPUT_WINMM);
	FSOUND_SetDriver(0);                    // Select sound card (0 = default)

    if (!FSOUND_Init(44100, 32, 0))
    {
        FSOUND_Close();
        return 1;
	}
}

  












/*

    // OPEN STREAM (use #if 1 for streaming from memory)
    // ==========================================================================================
    stream = FSOUND_Stream_Open(argv[1], FSOUND_NORMAL | FSOUND_MPEGACCURATE, 0, 0);
    if (!stream)
    {
        FSOUND_Close();
        return 1;
    }

    sptr = FSOUND_Stream_GetSample(stream);
    if (sptr)
    {
        int freq;
        FSOUND_Sample_GetDefaults(sptr, &freq, NULL, NULL, NULL);
    }

	_______________________________

   
        if (channel < 0)
        {

            channel = FSOUND_Stream_PlayEx(FSOUND_FREE, stream, NULL, TRUE);
            FSOUND_SetPaused(channel, FALSE);
        }
	
		std::cin >> key;

    Sleep(20);


    FSOUND_Stream_Close(stream);

    FSOUND_Close();
    return 0;

______________________________________

FSOUND_Sample_GetName(sptr);

 if (kbhit())
        {
            key = getch();
            if (key == ' ')
            {
                FSOUND_SetPaused(channel, !FSOUND_GetPaused(channel));
            }
            if (key == 'f')
            {
                FSOUND_Stream_SetTime(stream, FSOUND_Stream_GetTime(stream) + 6000);
            }
        }

        printf("pos %6d/%6d time %02d:%02d/%02d:%02d cpu %5.02f%%   \r", FSOUND_Stream_GetPosition(stream), 
                                                                         FSOUND_Stream_GetLength(stream), 
                                                                         FSOUND_Stream_GetTime(stream) / 1000 / 60, 
                                                                         FSOUND_Stream_GetTime(stream) / 1000 % 60, 
                                                                         FSOUND_Stream_GetLengthMs(stream) / 1000 / 60, 
                                                                         FSOUND_Stream_GetLengthMs(stream) / 1000 % 60, 
                                                                         FSOUND_GetCPUUsage());

        
*/
