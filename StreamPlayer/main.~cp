#include <string>
#include <conio.h>

#include "control_fmod.h"
#include "refFunctions.h"
using namespace std; 

vector<vector<char> > playList;
int nplay_index=0;
int volume=160;

char *getSpec();
void play(int index);
void addFileToPlayList(char *file);
bool control(int key);
char *getName();

bool isColChange=0;
char Spec[10];
char name[1024];
char name2[30];

int g_bcolor = 0,g_fcolor=15;

vector<char> nameVec;

int main(int argc, char *argv[])
{

	setColor(g_bcolor,g_fcolor);
	char file[512]="New World.mp3";
	if(argc>1)
	{
		for(int i=1;i < argc;i++)
			addFileToPlayList(argv[i]);
	}
	else
	{
		addFileToPlayList(&file[0]);
	}
	play(0);

	char key;
	int i=0;
	do
	{
		if(kbhit())
			{	i=0;
				key=getch();
				if( key > 57 || key == 34 )
				
					i=0;
					while(kbhit())
					{
						if(key!=34)
						{
							file[i]=key;
							i+=1;
						}
						key = getch();
					}

					if(key==34)
						file[i]='\0';
					else
					{
						file[i]=key;
						file[i+1] = '\0';
					}

					if(i>1)
						addFileToPlayList(&file[0]);
					else
					{
						if(control(key))
						{
							printf("               \r");
							Sleep(20);
						}
					}
					
				

			}

		else 
			{
				if( FSOUND_Stream_GetTime(stream)>= FSOUND_Stream_GetLengthMs(stream) )
				{
                   
					if(!control('5'))
						control('7');
						
					Sleep(100);
                    FSOUND_SetVolume(FSOUND_ALL, volume);
				}

			

				printf("%02d:%02d³%02d:%02d ±±± %s ±±± %02d³%02d ±±± Vol:%d%% ±%s\r\r",FSOUND_Stream_GetTime(stream)/1000/60 ,
												FSOUND_Stream_GetTime(stream)/1000%60,
												FSOUND_Stream_GetLengthMs(stream) / 1000 / 60, 
                                                FSOUND_Stream_GetLengthMs(stream) / 1000 % 60,
												getName(),
												nplay_index + 1,
												playList.size(),
												(volume *100 /256),
												getSpec());
												
		Sleep(50);
			}
	} while (key != 27);
	
}

int pos=0;
int isp=0;

char *getName()
{
	isp++;
	if(isp!=4)
	{
		return &name2[0];
	}

	isp=0;
	pos++;
	if(!(pos<nameVec.size() ))
	{
		pos=0;
	}

	for(int i=0;i<24;i++)
	{
		if( (pos+i)<nameVec.size() )
		{
			name2[i]=nameVec[i+pos];
		}
		else
		{
			name2[i]=nameVec[ (i+pos)%nameVec.size() ];
		}
	}

	return &name2[0];
	
}

int spBcol=0,spFcol=0;
int lastVal=0;
char *getSpec()
{
	float *spectrum;
	int val=0;
	float y=0;
	spectrum = FSOUND_DSP_GetSpectrum();	/* returns an array of 512 floats */
    if (!spectrum)
    {
        return 0;
    }

	for(int i=0;i<512;i++)
	{
		y+=spectrum[i]/512.0f;
	}

	val=((int)(y*200.0f*256.0f/(float)volume)) +1;								//(spectrum[256]*100.0f)+1;
	for(int i=0;i<10;i++)
	{
			if(val>i)
			{
				Spec[i]='±';
			}
			else
			{
				Spec[i]=' ';
			}
	}
	
	if(isColChange)
	{

		if( (val-lastVal)>0 )
		{
		    setColor(g_bcolor,15);
        }
        else
        setColor(g_bcolor,g_fcolor);
        
        if((val-lastVal)>5 )
        {
        setColor(8,g_fcolor);
        }
        
        
        lastVal=val;
    }

	Spec[9]='\0';
	return &Spec[0];
}


void play(int index)
{
	char file[512];
	for( size_t i=0;i<playList[index].size();i++ )
	{
		file[i]=playList[index][i];
	}
	file[playList[index].size()]='\0';
	fmod_configer();
	if(file[0]==34)
	{
		file[playList[index].size()]=18;
		open_stream(&file[1]);

	}
	else
		open_stream(&file[0]);
	strcpy(&name[0],FSOUND_Sample_GetName(sptr));
	nameVec.clear();
	int l=0;
	while(name[l]!='\0')
	{
		nameVec.push_back(name[l]);
		l++;
	}
	char cname[1024];
	sprintf(cname,"title %s",name);
	system(cname);

	nameVec.push_back(' ');
	nameVec.push_back('³');
	nameVec.push_back(' ');
	//printf("Name:%s                                             \n",name);
	stream_play(stream);
	FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), TRUE);
}

void addFileToPlayList(char *file)
{
	vector <char> currentFile;
	while(*file!='\0')
	{
		currentFile.push_back(*file);
		file++;
	}
	playList.push_back(currentFile);
}

bool control(int key)
{
	if (key<58)
		key-=48;
//__________________________________________

	if(key=='a'||key=='A' ||key=='s'||key=='S')
	{
		if(key=='a'||key=='A')
		{
			g_bcolor-=1;
			if(g_bcolor<0)
				g_bcolor=15;
		}
		if(key=='s'||key=='S')
		{
			g_bcolor+=1;
			if(g_bcolor>15)
				g_bcolor=0;
		}

		setColor(g_bcolor,g_fcolor);
		return 1;
	}

	if(key=='z'||key=='Z' ||key=='x'||key=='X')
	{
		if(key=='z'||key=='Z')
		{
			g_fcolor-=1;
			if(g_fcolor<0)
				g_fcolor=15;
		}
		if(key=='x'||key=='X')
		{
			g_fcolor+=1;
			if(g_fcolor>15)
				g_fcolor=0;
		}

		setColor(g_bcolor,g_fcolor);
		return 1;
	}
//______________________________________


	if(key=='c' || key == 'C')
	{
		if(isColChange)
		{
			isColChange=false;
			setColor(g_bcolor,g_fcolor);
		}
		else
			isColChange=true;
	}


//_____________________________________


	if(key<=2)
	{
		stream_set_state(key);
		return 1;
	}
	
	if(key==5 & nplay_index + 1 < playList.size())
	{
		nplay_index+=1;
		play(nplay_index);
		return 1;
	}
	
	if(key==4 & nplay_index > 0)
	{
		nplay_index-=1;
		play(nplay_index);
		return 1;
	}
	if(key==7)
	{
		nplay_index=0;
		play(nplay_index);
		return 1;
	}

	if(key==8)
	{
		nplay_index=playList.size()-1;
		play(nplay_index);
		return 1;
	}

	if(key==3)
	{
		if (volume>0)
		{
			volume-=8;
			FSOUND_SetVolume(FSOUND_ALL, volume);
			return 1;
		}
	}
	if(key==6)
	{
		if(volume<256) 
		{
			volume+=8;
			FSOUND_SetVolume(FSOUND_ALL, volume);
			return 1;
		}
	}
	return 0;
}
