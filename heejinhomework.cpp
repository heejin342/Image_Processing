#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning (disable:4996)


void Binarization(BYTE * In, BYTE * Out, int Th, int W, int H) {
	int Size = W * H;
	for (int i = 0; i < Size; i++) {
		if (In[i] > Th)
			Out[i] = 255;
		else
			Out[i] = 0;
	}
}

int DetermThreshold(BYTE * Img, int * Histo, int W, int H) {
    
	int Size = W * H;
	int Tnew = 0;
	int Tinit = 0;
	int max = 0;
	int min = 255;
	int error = 0;

	for (int i = 0; i < Size; i++) {
		if (max < Img[i])
			max = Img[i];
		if (min > Img[i])
			min = Img[i];
	}

	Tinit = (max + min) / 2;
	printf("%d\n\n\n", Tinit);

	do {

		int sumG1 = 0;
		int sumG2 = 0;
		int cntG1 = 0;
		int cntG2 = 0;

		for (int i = 0; i < Size; i++) {
			if (Img[i] <= Tinit) {
				sumG1 += Img[i];
				cntG1++;
			}

			else {
				sumG2 += Img[i];
				cntG2++;
			}
		}
		Tnew =((sumG1 / cntG1) + (sumG2 / cntG2)) / 2;

		printf("%d\n\n\n", Tnew);
 	    
		error = Tinit - Tnew < 0 ? (Tinit - Tnew) * (-1) : Tinit - Tnew;

		Tinit = Tnew;
	
	} while (error >= 3);
	
	return Tnew;

}

void ObtainHisto(BYTE * Img, int * Histo,int W, int H) {

	int Size = H * W;
	for (int i = 0; i < Size; i++) 
		Histo[Img[i]]++;
	FILE * fp3 = fopen("Histoheejin.txt", "wt");
	for (int i = 0; i < 256; i++) 
		fprintf(fp3, "%d\t%d\n", i, Histo[i]);
	fclose(fp3);
	
}

int main() {
	int Histo[256] = { 0 };  
	BITMAPFILEHEADER hf; 
	BITMAPINFOHEADER hInfo; 
	RGBQUAD hRGB[256]; 
	FILE *fp;
	fp = fopen("coin.bmp", "rb");
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE * Image = (BYTE *)malloc(ImgSize);
	BYTE * Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	ObtainHisto(Image, Histo, hInfo.biWidth, hInfo.biHeight);
	int TH = DetermThreshold(Image, Histo, hInfo.biWidth, hInfo.biHeight);
	Binarization(Image, Output, TH , hInfo.biWidth, hInfo.biHeight);

	fp = fopen("output.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
	free(Image);
	free(Output);
	
	printf("자동으로 선택된 임계값 : %d\n", TH);

	int a;
	scanf_s("%d", &a);

	return 0;

}

