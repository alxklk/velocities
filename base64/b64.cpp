#include <stdio.h>
#include <string.h>

static const char enctable[64]=
{
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'0','1','2','3','4','5','6','7','8','9','+','/'
};

void Encode3to4(char* src, char* dst)
{
	dst[0]=enctable[(src[0]&0xfc)>>2];
	dst[1]=enctable[((src[0]&0x03)<<4)|((src[1]&0xf0)>>4)];
	dst[2]=enctable[((src[1]&0x0f)<<2)|((src[2]&0xc0)>>6)];
	dst[3]=enctable[(src[2]&0x3f)];
}

int dectable[256];

int Decode4to3(char* src, char* dst)
{
	int dec[4];

	dec[0]=dectable[src[0]];
	dec[1]=dectable[src[1]];
	dec[2]=dectable[src[2]];
	dec[3]=dectable[src[3]];

	dst[0]=(dec[0]<<2)|((dec[1]&0x30)>>4);
	dst[1]=((dec[1]&0x0f)<<4)|((dec[2]&0x3c)>>2);
	dst[2]=((dec[2]&0x03)<<6)|(dec[3]);
}

char stream[4]={0,0,0,0};
int streampos=0;

int DecodeStreamPut(char c, char* dst)
{
	if(dectable[c]>=0)
		stream[streampos++]=c;
	if(streampos==4)
	{
		int res=Decode4to3(stream, dst);
		for(int i=0;i<4;i++)stream[i]=0;
		streampos=0;
		return 1;
	}
	return 0;
}

void printUsage(char* prgname)
{
	printf("Base64 encode or decode file or string\nUse: %s <dec|enc> <string|filename>\n", prgname);
}

void printBase64Error()
{
	printf("Base64 code contains error\n");
}

int main(int argc, char** argv)
{
	if(argc<3)
	{
		printUsage(argv[0]);
		return 1;
	}
	bool decode=false;
	if(!strcmp(argv[1],"dec"))
	{
		decode=true;
		for(int i=0;i<256;i++)
			dectable[i]=-1;
		for(int i=0;i<64;i++)
			dectable[enctable[i]]=i;
	}
	else if(!strcmp(argv[1],"enc"))
	{
		decode=false;
	}
	else
	{
		printUsage(argv[0]);
		return 1;
	}
	char* text=argv[2];
	int len=strlen(text);
	FILE* f=fopen(argv[2], "rb");
	if(f)
	{
		fseek(f, 0, SEEK_END);
		len=ftell(f);
		fseek(f, 0, SEEK_SET);
		text=new char[len+1];
		fread(text,len,1,f);
		fclose(f);
		printf("File %s of length %i\n", argv[1], len);
	}
	else
	{
		printf("String \"%s\" of length %i\n", text, len);
	}

	if(decode)
	{
		FILE* o=fopen("out.dec","wb");
		char dst[3];
		for(int i=0;i<len;i++)
		{
			int res=DecodeStreamPut(text[i], dst);
			if(res)
			{
				printf("%.*s",3,dst);
				fwrite(dst,1,3,o);
			}
		}
		for(int i=0;i<3;i++)
		{
			int res=DecodeStreamPut('A', dst);
			if(res)
			{
				printf("<%.*s>",3,dst);
				fwrite(dst,1,3,o);
			}
		}
		fclose(o);
	}
	else
	{
		int i=0;
		while(1)
		{
			char dst[4];
			if(i+3>len)
			{	if(i==len)
					break;
				char b[3];
				if(i  <len)b[0]=text[i  ];
				if(i+1<len)b[1]=text[i+1];else b[1]=0;
				if(i+2<len)b[2]=text[i+2];else b[2]=0;
				Encode3to4(b, dst);
				printf("%.*s",4,dst);
				break;
			}

			Encode3to4(&text[i], dst);
			printf("%.*s",4,dst);
			i+=3;
		}
	}
	printf("\nOK\n");
	
	return 0;
}
