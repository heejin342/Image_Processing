#include <stdio.h>
#include <conio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996)
#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a < b) ? a : b)

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
void m_BlobColoring(BYTE* CutImage, int height, int width)
{
	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
	long k;
	short curColor = 0, r, c;
	Out_Area = 1;
	// �������� ����� �޸� �Ҵ�
	short* stackx = new short[height*width];
	short* stacky = new short[height*width];
	short* coloring = new short[height*width];

	int arr_size = height * width;

	// �󺧸��� �ȼ��� �����ϱ� ���� �޸� �Ҵ�
	for (k = 0; k<height*width; k++) coloring[k] = 0;  // �޸� �ʱ�ȭ
	for (i = 0; i<height; i++)
	{
		index = i * width;
		for (j = 0; j<width; j++)
		{
			// �̹� �湮�� ���̰ų� �ȼ����� 255�� �ƴ϶�� ó�� ����
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
						//���� �ȼ��� �����踦 ����� ó�� ����
						if (m<0 || m >= height || n<0 || n >= width) continue;

						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
						{
							coloring[index + n] = curColor; // ���� �󺧷� ��ũ
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

	// ���� ������ ���� ������ ã�Ƴ��� ���� 
	for (i = 1; i <= curColor; i++)
	{
		if (BlobArea[i] >= BlobArea[Out_Area]) Out_Area = i;
	}
	// CutImage �迭 Ŭ����~
	for (k = 0; k < width*height; k++) CutImage[k] = 255;

	// coloring�� ����� �󺧸� ����� (Out_Area�� �����) ������ ���� ū �͸� CutImage�� ����
	for (k = 0; k < width*height; k++)
	{
		if (coloring[k] == Out_Area) CutImage[k] = 0;  // ���� ū �͸� ����

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
void Binarization(BYTE * Output, BYTE * Output2, int W, int H) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (123 < Output[i * W * 3 + j * 3 + 1] && Output[i * W * 3 + j * 3 + 1] < 140 && 118 < Output[i * W * 3 + j * 3] && Output[i * W * 3 + j * 3] < 142) {
				Output2[i * W * 3 + j * 3] = 0;
				Output2[i * W * 3 + j * 3 + 1] = 0;
				Output2[i * W * 3 + j * 3 + 2] = 0;
			}
			else {
				Output2[i * W * 3 + j * 3] = 255;
				Output2[i * W * 3 + j * 3 + 1] = 255;
				Output2[i * W * 3 + j * 3 + 2] = 255;
			}
		}
	}
	//for (int i = 0; i < W*H; i++) {
	//	if (Output[i * 3 + 1] == 0 && Output[i * 3] == 0 && Output[i * 3 + 2] == 0) {
	//		facecnt++;
	//	}
	//}
}

void exel(double **HSI , int W ,int H , int facecnt) {
	FILE * fp3 = fopen("verynew_HSBresult.txt", "wt");
	for (int i = 0; i < facecnt; i++)
		fprintf(fp3, "%.1f\t%f\t%d\n", HSI[i][2]/255 , HSI[i][1] , (BYTE)HSI[i][0]);
	fclose(fp3);
};   

void rgbToHsi(BYTE *facebfR, BYTE *facebfG, BYTE *facebfB, double **HSI , int W, int H , int facecnt) {
	double delta = 0;
	double min = 0;
	double max = 0;

	for (int i = 0; i < facecnt; i++) {
		min = MIN((MIN(facebfR[i], facebfG[i])), facebfB[i]);
		max = MAX((MAX(facebfR[i], facebfG[i])), facebfB[i]);

		HSI[i][2] = max;
		delta = max - min;

		if (max == 0) HSI[i][1] = 0;
		else HSI[i][1] = delta / max;

		if (delta == 0)   HSI[i][0] = 0;
		else {
			if (facebfR[i] == max)
				HSI[i][0] = 60 * ((int)((facebfG[i] - facebfB[i]) / delta) % 6);

			else if (facebfG[i] == max)
				HSI[i][0] = 60 * (((facebfB[i] - facebfR[i]) / delta) + 2);

			else if (facebfB[i] == max)
				HSI[i][0] = (((facebfR[i] - facebfB[i]) / delta) + 4);
		}
	}
};


int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	FILE *fp;
	FILE *fpE;
	fp = fopen("face.bmp", "rb");
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	int W = hInfo.biWidth;
	int H = hInfo.biHeight;
	BYTE *Image = (BYTE *)malloc(W * H * 3);
	BYTE *Output = (BYTE *)malloc(W * H * 3);
	BYTE *Output2 = (BYTE *)malloc(W * H * 3);
	fread(Image, sizeof(BYTE), W * H * 3, fp);

	FILE *f1;
	FILE *f2;
	FILE *f3;
	BYTE *bf1, *bfR, *bfG, *bfB;
	bf1 = (BYTE*)malloc(sizeof(BYTE) * ImgSize * 3);
	bfR = (BYTE*)malloc(sizeof(BYTE) * ImgSize);
	bfG = (BYTE*)malloc(sizeof(BYTE) * ImgSize);
	bfB = (BYTE*)malloc(sizeof(BYTE) * ImgSize);

	fseek(fp, 54, SEEK_SET);
	fread(bf1, sizeof(BYTE), ImgSize * 3, fp);
	fclose(fp);
	int k = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			bfR[k] = bf1[i * W * 3 + j * 3];
			bfG[k] = bf1[i * W * 3 + j * 3 + 1];
			bfB[k] = bf1[i * W * 3 + j * 3 + 2];
			k++;
		}
	}       // --> Ȯ���ϰ� ��ü rgb �� ���´�

	RGBToYCbCrConvertor(Image, Output, W, H);
	Binarization(Output, Output2, W, H );
	m_BlobColoring(Output2, H, W * 3);          // --> 1.�󱼿��� ���� �Ϸ�

	//int facecnt = 0;
	//for (int i = 0; i < W*H; i++) {
	//	if (Output2[i * 3 + 1 ] == 0 && Output2[i * 3 ] == 0 && Output2[i *3 + 2] == 0) {
	//		facecnt++;
	//	}
	//}
	//printf("%d", facecnt);       // �� Ʋ���� ���°Ű���. �ϴ� ����

	int facecnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Output2[i * W * 3 + j * 3] == 0 && Output2[i * W * 3 + j * 3 + 1] == 0 && Output2[i * W * 3 + j * 3 + 2] == 0)
				facecnt++;
		}
	}
	printf("%d", facecnt);         //-> �� ī��Ʈ �ϴ°ű��� �Ϸ�


	int *I_witch = (int*)malloc(sizeof(int) * ImgSize);
	BYTE *facebfR = (BYTE*)malloc(sizeof(BYTE) * ImgSize);
	BYTE *facebfG = (BYTE*)malloc(sizeof(BYTE) * ImgSize);
	BYTE *facebfB = (BYTE*)malloc(sizeof(BYTE) * ImgSize);

	int k3 = 0;
	int k4 = 0;
	f1 = fopen("newRGB all.txt", "wt");
	for (int i =0 ; i < H; i++) {
		for (int j = 0; j < W; j++) {
			k4++;
			if (Output2[i * W * 3 + j * 3] == 0 && Output2[i * W * 3 + j * 3 + 1] == 0 && Output2[i * W * 3 + j * 3 + 2] == 0)
			{
				facebfR[k3] = bfR[k4];
				facebfG[k3] = bfG[k4];
				facebfB[k3] = bfB[k4];
				I_witch[k3] = k4;
				fprintf(f1, "%d\t%d\t%d\t%d\n", facebfR[k3], facebfG[k3], facebfB[k3] , I_witch[k3]);
				k3++;
			}
		}
	}   // --> �� ��ǥ�� ����� ����Ѵ�.


	f1 = fopen("RGB all.txt", "wt");
	for (int i = 0; i < H * W; i++) {
		fprintf(f1, "%d\t%d\t%d\n", bfR[i], bfG[i], bfB[i]);
	}
	//--> ��ü rbg Ȯ�ο�. Ȯ����

	

	f1 = fopen("Red.txt", "wt");
	for (int i = 0; i < facecnt; i++)
		fprintf(f1, "%d\t%d\t%d\n", I_witch[i]/W, I_witch[i]%W,facebfR[i]);   //����Ҷ�, x��ġ , y��ġ , �� ���� ����ϵ���
	//f2 = fopen("Green.txt", "wt");
	//for (int i = 0; i < wrgb; i++)
	//	fprintf(f2, "%d\t%d\n", I_witch[i], facebfG[i]);    //����Ҷ�, x��ġ , y��ġ , �� ���� ����ϵ���
	//f3 = fopen("Blue.txt", "wt");
	//for (int i = 0; i < wrgb; i++)
	//	fprintf(f3, "%d\t%d\n", I_witch[i], facebfB[i]);     //����Ҷ�, x��ġ , y��ġ , �� ���� ����ϵ���



	double **HSI;
	HSI = (double **)malloc(sizeof(double*) * ImgSize);
	for (int i = 0; i < ImgSize; ++i) {
		HSI[i] = (double*)malloc(sizeof(double) * 3);
	}

	rgbToHsi(facebfR, facebfG, facebfB, HSI, W , H , facecnt);        
	exel(HSI,W,H , facecnt);                                       //facecnt �ʿ� ���� ���� ���� . �ϴ��� �׳ɽ��� 


	////��½� v�� 255�� ��������
	//for (int i = 0; i < facecnt; i++) {               //RGB���� ����� ��ġ�� ����ϰ�, HSI�� �·κ��� �������°Ŵϱ� �굵 ��ġ��� -> ��ȯ�� �� ����ϵ���
	//	printf("%5d", HSI[i][0]);                     //����� H ���
	//	printf("%5d", HSI[i][1]);                     //����� S ���
	//	printf("%5d", HSI[i][2] / 255);                     //����� V ���
	//	printf("\n");
	//}
	//printf("%d", facecnt);


	int a = 0;
	scanf_s("%d", &a);


	fpE = fopen("nfinal.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fpE);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fpE);
	fwrite(Output2, sizeof(BYTE), W * H * 3, fpE);
	fclose(fpE);
	fclose(f1);
//	fclose(f2);
//	fclose(f3);
	free(bf1);
	free(Image);
	free(Output);
	free(Output2);
	free(bfR);
	free(bfG);
	free(bfB);
	free(HSI);
	return 0;
}









//rbg ���ٷ� ���� �ƴ��� Ȯ���غ�


// �� �Ǵµ� �ȵǴ°� face �������� RGB�� HSI�� �ٲٴ°� �ȵǴ°� ���� .
// ���� ���� V ���� �´� ������ �𸣰ڴ�.