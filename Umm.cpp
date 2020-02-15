#include <stdio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996) 
#define SIZE 3
int push(short *stackx, short *stacky, int arr_size, short vx, short vy, int *top)
{
	if (*top >= arr_size) return(-1);
	(*top)++;
	stackx[*top] = vx;
	stacky[*top] = vy;
	return(1);
}
int pop(short *stackx, short *stacky, short *vx, short *vy, int *top)
{
	if (*top == 0) return(-1);
	*vx = stackx[*top];
	*vy = stacky[*top];
	(*top)--;
	return(1);
}
// GlassFire 알고리즘을 이용한 라벨링 함수
void m_BlobColoring(BYTE* CutImage, int height, int width)
{
	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
	long k;
	short curColor = 0, r, c;
	//	BYTE** CutImage2;
	Out_Area = 1;


	// 스택으로 사용할 메모리 할당
	short* stackx = new short[height*width];
	short* stacky = new short[height*width];
	short* coloring = new short[height*width];

	int arr_size = height * width;

	// 라벨링된 픽셀을 저장하기 위해 메모리 할당

	for (k = 0; k<height*width; k++) coloring[k] = 0;  // 메모리 초기화

	for (i = 0; i<height; i++)
	{
		index = i * width;
		for (j = 0; j<width; j++)
		{
			// 이미 방문한 점이거나 픽셀값이 255가 아니라면 처리 안함
			if (coloring[index + j] != 0 || CutImage[index + j] != 255) continue;
			r = i; c = j; top = 0; area = 1;
			curColor++;

			while (1)
			{
			GRASSFIRE:
				for (m = r - 1; m <= r + 1; m++)
				{
					index = m * width;
					for (n = c - 1; n <= c + 1; n++)
					{
						//관심 픽셀이 영상경계를 벗어나면 처리 안함
						if (m<0 || m >= height || n<0 || n >= width) continue;

						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
						{
							coloring[index + n] = curColor; // 현재 라벨로 마크
							if (push(stackx, stacky, arr_size, (short)m, (short)n, &top) == -1) continue;
							r = m; c = n; area++;
							goto GRASSFIRE;
						}
					}
				}
				if (pop(stackx, stacky, &r, &c, &top) == -1) break;
			}
			if (curColor<1000) BlobArea[curColor] = area;
		}
	}

	float grayGap = 255.0f / (float)curColor;

	// 가장 면적이 넓은 영역을 찾아내기 위함 
	for (i = 1; i <= curColor; i++)
	{
		if (BlobArea[i] >= BlobArea[Out_Area]) Out_Area = i;
	}
	// CutImage 배열 클리어~
	for (k = 0; k < width*height; k++) CutImage[k] = 255;

	// coloring에 저장된 라벨링 결과중 (Out_Area에 저장된) 영역이 가장 큰 것만 CutImage에 저장
	for (k = 0; k < width*height; k++)
	{
		if (coloring[k] == Out_Area) CutImage[k] = 0;  // 가장 큰 것만 저장
													   //CutImage[k] = (unsigned char)(coloring[k] * grayGap);
	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
void RGBToYCbCrConvertor(BYTE *Image, BYTE *Output, int W, int H) {

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			Output[i*W * 3 + j * 3 + 2] = (0.299 * (double)Image[i*W * 3 + j * 3 + 2]) + (0.587 * (double)Image[i*W * 3 + j * 3 + 1]) + (0.114 * (double)Image[i*W * 3 + j * 3]) + 0;
			Output[i*W * 3 + j * 3 + 1] = (-0.16874 * (double)Image[i*W * 3 + j * 3 + 2]) + (-0.3313 * (double)Image[i*W * 3 + j * 3 + 1]) + (0.5 * (double)Image[i*W * 3 + j * 3]) + 128;
			Output[i*W * 3 + j * 3] = (0.5 * (double)Image[i*W * 3 + j * 3 + 2]) + (-0.4187 * (double)Image[i*W * 3 + j * 3 + 1]) + (-0.0813 * (double)Image[i*W * 3 + j * 3]) + 128;
		}
	}
}
void Binarization(BYTE * Input ,BYTE * Output,int W, int H){
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (123 < Input[i * W * 3 + j * 3 + 1] && Input[i * W * 3 + j * 3 + 1] < 140 && 118 < Input[i * W * 3 + j * 3] && Input[i * W * 3 + j * 3] < 142) {
				Output[i * W * 3 + j * 3] = 0;
				Output[i * W * 3 + j * 3 + 1] = 0;
				Output[i * W * 3 + j * 3 + 2] = 0;
			}
			else {
				Output[i * W * 3 + j * 3] = 255;
				Output[i * W * 3 + j * 3 + 1] = 255;
				Output[i * W * 3 + j * 3 + 2] = 255;
			}
		}
	}
}



int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	RGBQUAD	hRGB[256];

	FILE *fp;
	fp = fopen("face.bmp", "rb");
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE *Image;
	BYTE * Output;
	BYTE * Output2 = (BYTE *)malloc(ImgSize);
	if (hInfo.biBitCount == 8) {  //8이면 인덱스컬러
		fread(hRGB, sizeof(RGBQUAD), 256, fp);	//팔레트는 그레이 영상일 떄만 있음
		Image = (BYTE *)malloc(ImgSize);
		Output = (BYTE *)malloc(ImgSize);
		fread(Image, sizeof(BYTE), ImgSize, fp);
	}
	else {   //24이면 트루컬러
		Image = (BYTE *)malloc(ImgSize * 3);
		Output = (BYTE *)malloc(ImgSize * 3);
		fread(Image, sizeof(BYTE), ImgSize * 3, fp);
	}
	int W = hInfo.biWidth;
	int H = hInfo.biHeight;
	BYTE * X_witch = (BYTE *)malloc(ImgSize);
	BYTE * Y_witch = (BYTE *)malloc(ImgSize);
	fclose(fp);


	int minX = 99999999;
	int maxX = 0;
	int minY = 99999999;
	int maxY = 0;



	RGBToYCbCrConvertor(Image, Output, W, H);  
	Binarization(Output,Output, W, H);
	m_BlobColoring(Output, H, W*3);

	for (int i = 0; i < H*W; i++) {
		if (Output[i*3] == 0 && Output[i*3+1]==0 && Output[i*3+2]==0) {
			X_witch[i] = i % W;
			if (X_witch[i] < minX)
				minX = X_witch[i];
			else if(maxX < X_witch[i])
				maxX = X_witch[i];
	
			Y_witch[i] = i / W;
			if (Y_witch[i] < minY)
				minY = Y_witch[i];
			else if (maxY < Y_witch[i])
				maxY = Y_witch[i];
		}
	}
	
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == minY || i == maxY) {
				if (minX < j && j < maxX) {
					Image[i*W * 3 + j * 3] = 0;
					Image[i*W * 3 + j * 3 + 1] = 0;
					Image[i*W * 3 + j * 3 + 2] = 255;
				}
			}
			else if (j == maxX || j == minX) {
				if (minY < i && i < maxY) {
					Image[i*W * 3 + j * 3] = 0;
					Image[i*W * 3 + j * 3 + 1] = 0;
					Image[i*W * 3 + j * 3 + 2] = 255;
				}
			}
	
		}
	}


	 

	fp = fopen("hihifinal.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	if (hInfo.biBitCount == 8) {
		fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
		fwrite(Output, sizeof(BYTE), ImgSize, fp);
	}
	else {
		fwrite(Output, sizeof(BYTE), ImgSize * 3, fp);
	}

	fclose(fp);
	free(Image);
	free(Output);
	free(X_witch);
	free(Y_witch);
}
