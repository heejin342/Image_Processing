#include <stdio.h>
#include <Math.h>
#include <stdlib.h>        //동적할당용
#include <Windows.h>       //bmp파일의 헤더파일 구조체 정보
#pragma warning (disable:4996) 
#define SIZE 3
void ObtainHisto(BYTE * Img, int * Histo, int W, int H) {
	int Size = H * W;
	for (int i = 0; i < Size; i++)
		Histo[Img[i]]++;
	FILE * fp3 = fopen("Newheejin.txt", "wt");
	for (int i = 0; i < 256; i++)
		fprintf(fp3, "%d\t%d\n", i, Histo[i]);
	fclose(fp3);
}
void HistoStretching(BYTE * Image, BYTE * Output, int W, int H, int * Histo, double p) {
	int ImgSize = W * H;
	int High = 0;
	int Low = 0;
	int cnt = 0;
	int Limit = ImgSize * p;
	for (int i = 0; i < 256; i++) {
		cnt += Histo[i];
		if (cnt > ImgSize *p) {
			Low = i;
			break;
		}
	}
	cnt = 0;
	for (int i = 255; i >= 0; i--) {
		cnt += Histo[i];
		if (cnt > ImgSize *p) {
			Low = i;
			break;
		}
	}
	for (int i = 0; i < ImgSize; i++) {
		if (Image[i] < Low) Output[i] = 0;
		else if (Image[i] > High) Output[i] = 255;
		else Output[i] = (BYTE)((Image[i] - Low) / (double)(High - Low)) * 255;  //분모를 강제로 형변환 시켜줌 . 그리고 255 글 곱해줘 
	}
}
void ObtainAccHisto(int * Histo, int * AHisto) {
	AHisto[0] = Histo[0];
	for (int i = 1; i < 256; i++)
		AHisto[i] = AHisto[i - 1] + Histo[i];
}
void HistoEqualization(BYTE *Image, BYTE *Output, int W, int H, int * AHisto,int Gmax) {  //히스토그램 평활화
	int ImgSize = W * H;
	int Nt = ImgSize;
	double NR = Gmax / (double)Nt;
	int NSum[256];      //엔섬은 정규화합 값이 들감
	for (int i = 0; i < 256; i++)
		NSum[i] = (int)(NR * AHisto[i]);
	for (int i = 0; i < ImgSize; i++)
		Output[i] = NSum[Image[i]];
}

void BrightnessCtr(BYTE * In , BYTE * Out , int Val , int W , int H) {    //w,h는 가로와 세로 사이즈임. 특정영역만 밝기를 변경시킬 수 있음
	int Size = H * W;
	for (int i = 0; i < Size; i++) {
		if (In[i] + Val > 255) Out[i] = 255;
		else if (In[i] + Val < 0) Out[i] = 0;
		else Out[i] = In[i] + Val;
	}
}
void ContrastCtr(BYTE* In, BYTE * Out, double Val, int W, int H) {         //val에 실수가 들어갈 수 있어서 더블타입을 써서 표현.
	int Size = H * W;
	for (int i = 0; i < Size; i++) {
		In[i] * Val > 255.0 ? Out[i] = 255 : Out[i] = (BYTE)(In[i] * Val);   //0보다 작은 가능성은 없기 때문에 엘스문 필요없음
	}
}

void Binaryzation(BYTE* In, BYTE * Out, int Th, int W, int H) {         
	int Size = H * W;
	for (int i = 0; i < Size; i++) {
		if (In[i] > Th) Out[i] = 255;
		else Out[i] = 0;
	}
}

void LowPassFilter(BYTE *Image, BYTE *Output, double *m, const int S, int W, int H) {
   //마스크를 일차원배열로 받아서(m) 이차원으로 바꿈
	//const int Size = S;
	int Margin = SIZE / 2;
	double Mask[SIZE][SIZE];
	for (int i = 0; i < SIZE*SIZE; i++) 
		Mask[i/S][i%S] = m[i];   //1차원을 2차원 배열로 재분배를 한거임 , 몫이 행번호로 나머지가 열번호로 들어가는거임
	double temp = 0.0;
	for (int i = Margin; i < H - Margin; i++) {     //마스크 중앙의 세로방향 이동
		for (int j =  Margin; j < W - Margin; j++) {   //마스크 중앙의 가로방향 이동
														  //마진은 마스크 사이즈값을 2로 나눈 몫이 되어야한다. 마스크 사이즈가  5면 마진이 2가 되어야 하고, 마스크 사이즈가 7이면 , 마진이3
														  //그래서 포문에 초기화를 그렇게 했다.
			for (int m = -Margin; m <= Margin; m++) {    //m이 -1일떄는 위에, 0일때는 나 자신, 1일때는 밑에를 뜻함. 마스크 중앙 기준 세로방향 주변화소 접근
				for (int n = -Margin; n <= Margin; n++) {//마스크 중앙을기준으로 가로방향 주변화소 접근, 왼쪽오른쪽일캐
					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//곱의 누적합이니까 안쪽에 포문 두개돌면 컴볼루션한번된거임(9개가 곱해져서 템프에 저장되면 그거 합쳐서 한개의 합나옴 그게)
																						//Image[i*W+j] 이게 마스크의 센터 포지션  ,Mask[m+1][n+1] 시작은 -1로 해줬음
				}
			}
			Output[i*W + j] = (BYTE)temp;   //Output[i*W+j] 가운데 위치
			temp = 0.0;
		}
	}//이렇게하면 영상이 뭉개지고 노이즈들이 사라짐

}
void HighPassFilter(BYTE *Image, BYTE *Output, int *m, const int S, int W, int H) {
	int Margin = SIZE / 2;
	int Mask[SIZE][SIZE];
	for (int i = 0; i < SIZE*SIZE; i++)
		Mask[i / SIZE][i%SIZE] = m[i];   //1차원을 2차원 배열로 재분배를 한거임 , 몫이 행번호로 나머지가 열번호로 들어가는거임
	int temp = 0;
	for (int i = Margin; i < H - Margin; i++) {     //마스크 중앙의 세로방향 이동
		for (int j =  Margin; j < W - Margin; j++) {   //마스크 중앙의 가로방향 이동
														  //마진은 마스크 사이즈값을 2로 나눈 몫이 되어야한다. 마스크 사이즈가  5면 마진이 2가 되어야 하고, 마스크 사이즈가 7이면 , 마진이3
														  //그래서 포문에 초기화를 그렇게 했다.
			for (int m = -Margin; m <= Margin; m++) {    //m이 -1일떄는 위에, 0일때는 나 자신, 1일때는 밑에를 뜻함. 마스크 중앙 기준 세로방향 주변화소 접근
				for (int n = -Margin; n <= Margin; n++) {//마스크 중앙을기준으로 가로방향 주변화소 접근, 왼쪽오른쪽일캐
					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//곱의 누적합이니까 안쪽에 포문 두개돌면 컴볼루션한번된거임(9개가 곱해져서 템프에 저장되면 그거 합쳐서 한개의 합나옴 그게)
																						//Image[i*W+j] 이게 마스크의 센터 포지션  ,Mask[m+1][n+1] 시작은 -1로 해줬음
				}

			}
			//Output[i*W + j] = abs(temp) / 3;   //Output[i*W+j] 가운데 위치 . 가운데 들어가는게 9여서 마스크 값들의 합이 1이 된다는 소리는
			Output[i*W + j] = temp;
			temp = 0;
		}
	}
}
void HighPassFilter2(BYTE *Image, BYTE *Output, int *m, const int S, int W, int H) { // 마스크 합이 1인경우 사용할 함수
	int Margin = SIZE / 2;
	int *Temp = (int *)malloc(W*H*sizeof(int));
	double Mask[SIZE][SIZE];
	for (int i = 0; i < SIZE*SIZE; i++)
		Mask[i / SIZE][i%SIZE] = m[i];   //1차원을 2차원 배열로 재분배를 한거임 , 몫이 행번호로 나머지가 열번호로 들어가는거임
	int Max = -99999; 
	int Min = 99999;
	int temp = 0;
	for (int i =  Margin; i < H - Margin; i++) {     //마스크 중앙의 세로방향 이동
		for (int j = Margin; j < W - Margin; j++) {   //마스크 중앙의 가로방향 이동
														  //마진은 마스크 사이즈값을 2로 나눈 몫이 되어야한다. 마스크 사이즈가  5면 마진이 2가 되어야 하고, 마스크 사이즈가 7이면 , 마진이3
														  //그래서 포문에 초기화를 그렇게 했다.
			for (int m = -Margin; m <= Margin; m++) {    //m이 -1일떄는 위에, 0일때는 나 자신, 1일때는 밑에를 뜻함. 마스크 중앙 기준 세로방향 주변화소 접근
				for (int n = -Margin; n <= Margin; n++) {//마스크 중앙을기준으로 가로방향 주변화소 접근, 왼쪽오른쪽일캐
					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//곱의 누적합이니까 안쪽에 포문 두개돌면 컴볼루션한번된거임(9개가 곱해져서 템프에 저장되면 그거 합쳐서 한개의 합나옴 그게)
																						//Image[i*W+j] 이게 마스크의 센터 포지션  ,Mask[m+1][n+1] 시작은 -1로 해줬음
				}

			}
			if (temp > Max) Max = temp;
			if (temp < Min) Min = temp;
			Temp[i*W + j] = temp;   //Output[i*W+j] 가운데 위치 . 가운데 들어가는게 9여서 마스크 값들의 합이 1이 된다는 소리는
			temp = 0;
		}
	}
	for (int i = 0; i < W*H; i++) {
		Output[i] = (Temp[i] - Min) / (double)(Max - Min) * 255;
	}
	free(Temp);
}

//순서대로 입력, 처리, 출력
int main() {

	BITMAPFILEHEADER hf;        //14바이트인 BMP 파일헤더
	BITMAPINFOHEADER hInfo;     //40바이트인 BMP 파일헤더
	RGBQUAD	hRGB[256];			//256*4 바이트인 팔레트
	FILE *fp;
	fp = fopen("LENNA.bmp", "rb");          //레나의 오픈모드는 rb. b는 바이트의 의미 . 메모리의 포인터가 하드디스크에 있는 레나 파일에 접근함
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);       //fp가 가리키는 위치로부터 비트맵파일헤더(14바이트) 한번읽어서 hf변수에 넣어라
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);	   //현재 fp는 15가리킴. 거기서부터 40 바이트만큼 한번 읽어서 hinfo 에 담아라
	fread(hRGB, sizeof(RGBQUAD), 256, fp);				//4바이트씩 256번 읽어서 hRGB배열에 담아라. 배열의 이름이 주소니까 주소기호 안붙여도됌
	int ImgSize = hInfo.biWidth * hInfo.biHeight;		//h인포헤더 변수의 가로 멤버변수와 세로 멤버변수의 곱을 사이즈 변수에 저장해줬음

														//동적할당을통해 이미지의 화소 정보를 저장
	BYTE * Image = (BYTE *)malloc(ImgSize);		//ImgSize의 크기만큼 힙 영역의 동적할당을 해줌. 읽어야 할당해야 할 크기가 정해지기 때문에 동적할당해줘
												//BYTE Image[ImgSize]; 와 같은의미임. 근데 배열의 크기는 변수면 안되어서 이렇게 안써준거임
	BYTE * Output = (BYTE *)malloc(ImgSize);    //ImgSize가 영상처리된 결과를 저장
	fread(Image, sizeof(BYTE), ImgSize, fp);        //현재 fp가 가리키는되서 BYTE 크기만큼 영상의 화소 갯수를 이미지에 담아라
	fclose(fp);                //파일과의 연결을 끊어도 된다. 정보는 다 가져왔으니까
//	int Histo[256] = { 0 };
//	int AHisto[256] = { 0 };

//	ObtainHisto(Image, Histo, hInfo.biWidth, hInfo.biHeight);
//	ObtainAccHisto(Histo, AHisto);
//	HistoEqualization(Image, Output, hInfo.biWidth, hInfo.biHeight, AHisto, 255);
//	HistoStretching(Image, Output,hInfo.biWidth , hInfo.biHeight ,Histo, 0.0 );
//	BrightnessCtr(Image, Output, 100, hInfo.biWidth, hInfo.biHeight);
//  BrightnessCtr(Image, Output, -100, hInfo.biWidth, hInfo.biHeight);
//	ContrastCtr(Image, Output, 1.9, hInfo.biWidth, hInfo.biHeight);
//	Binaryzation(Image, Output, 110, hInfo.biWidth,hInfo.biHeight);   // 임계치가 110 일때


	//	for (int i = 0; i < ImgSize; i++)                  //0~255까지의 영상화소값을 255에서 빼서 반전시켰음
//		if(Image[i] *1.5 > 255.0)     
//			Output[i] = 255;						//Output[0]에는 255가 들어가겠지
//		else
//			Output[i] = (BYTE)(Image[i]*1.5) ;

//	for (int i = 0; i < ImgSize; i++)                  //0~255까지의 영상화소값을 255에서 빼서 반전시켰음
//		if (Image[i] * 0.7 > 255.0)
//			Output[i] = 255;						//Output[0]에는 255가 들어가겠지
//		else
//			Output[i] = (BYTE)(Image[i] * 0.7);                 1보다 작은 수를 곱해서 전체적인 콘트라스트와 밝기가 위에보다 떨어짐
//	const int Size = 5;    //마스크 사이즈를 키우면 키울수록 더 뭉개진다. 하지만 연산시간은 길어진다.

	double Mask[SIZE*SIZE];
	for (int i = 0; i < SIZE*SIZE; i++) Mask[i] = 1.0 / (SIZE*SIZE);
	//	= { 0.04,0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04
	//};   //3*3일때는 0.111이였는데, 5*5일때는 0.04 -> 더해서 1나오게	   . 이 숫자가 커지면 마진의 폭이 넓어진다.

//	const int Size = 5;
//	double Mask[SIZE * SIZE];
//	for (int i = 0; i < SIZE * SIZE; i++) Mask[i] = 1.0 / (SIZE * SIZE);
	int m[SIZE*SIZE] = { -1, -1, -1,
								0,0,0,
								1,1,1 };   //위에서 아래를 봤을때 밝기가 변하는 경계갑 검출하는거임, 어깨의 윗부분이 진하지만, 옆에는 아님 .가로의 경계검출
//	LowPassFilter(Image, Output, Mask, SIZE, hInfo.biWidth, hInfo.biHeight);
//	HighPassFilter(Image, Output, Mask, SIZE, hInfo.biWidth, hInfo.biHeight);
	HighPassFilter2(Image, Output, m, SIZE, hInfo.biWidth, hInfo.biHeight);

//	int Margin = SIZE / 2;
//	int H = hInfo.biHeight;
//	int W = hInfo.biWidth;
//	double Mask[SIZE][SIZE];
//	for (int i = 0; i < SIZE*SIZE; i++)
//		Mask[i / SIZE][i%SIZE] = m[i];   //1차원을 2차원 배열로 재분배를 한거임 , 몫이 행번호로 나머지가 열번호로 들어가는거임
//	int temp = 0;
//	int W = hInfo.biHeight * hInfo.biWidth;
//	for (int i = 0 + Margin; i < H - Margin; i++) {     //마스크 중앙의 세로방향 이동
//		for (int j = 0 + M argin; j < W - Margin; j++) {   //마스크 중앙의 가로방향 이동
//														  //마진은 마스크 사이즈값을 2로 나눈 몫이 되어야한다. 마스크 사이즈가  5면 마진이 2가 되어야 하고, 마스크 사이즈가 7이면 , 마진이3
//														  //그래서 포문에 초기화를 그렇게 했다.
//			for (int m = -Margin; m <= Margin; m++) {    //m이 -1일떄는 위에, 0일때는 나 자신, 1일때는 밑에를 뜻함. 마스크 중앙 기준 세로방향 주변화소 접근
//				for (int n = -Margin; n <= Margin; n++) {//마스크 중앙을기준으로 가로방향 주변화소 접근, 왼쪽오른쪽일캐
//					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//곱의 누적합이니까 안쪽에 포문 두개돌면 컴볼루션한번된거임(9개가 곱해져서 템프에 저장되면 그거 합쳐서 한개의 합나옴 그게)
//																						//Image[i*W+j] 이게 마스크의 센터 포지션  ,Mask[m+1][n+1] 시작은 -1로 해줬음
//				}
//
//			}
//			Output[i*W + j] = abs(temp) / 3;   //Output[i*W+j] 가운데 위치      , 가운데 8이들어가는 커널은 8을 곱해야해. 그래서 하이패스 필터가 귀찮음
//			temp = 0;
//		}
//	}

//출력
	fp = fopen("output2.bmp", "wb");               //output 파일을 생성해주겠음 . 그 위치를 fp가 가리킴
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);		//fp변수에 있는 내용을 현재 가리키는데에 1바이트씩 14번 파일헤더에 저장
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);		//rgb배열정보를 256번기록해
	fwrite(Output, sizeof(BYTE), ImgSize, fp);		//반전처리된 화소정보를 파일로 내보낸다. 
	fclose(fp);					//파일포인터 끊어주고
	free(Image);				//동적할당 했던거 free로 끊어준다.
	free(Output);
	return 0;
}

//도수들의 합은 전체 픽셀 갯수임;




//X마스크 Y 마스크  합치는게 과제
//머지함수만들음. 소벨Y, 소벨x 두개의 밝기를 픽셀마다 비교해서 센화소값을 택하면 됨 (3*3)
//프림은	범위아 0~765 였는데 이건 다를거임. 이거 고려해봐

//소벨 마스크를 써서 x,y 경계합쳐서 이진화까진 해서 이진화 하는 함수는 마ㄴ들어놈
//이미ㅣ라는 배열에 있는 화소값을 소벨 엑스용 배열이 있어얗고, 와이하는 결과하는 배열
//이걸 머지할때 필요한 배열
//아웃풋할때 필요한 배열
