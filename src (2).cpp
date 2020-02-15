#include <stdio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996) 
#define SIZE 3
int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	RGBQUAD	hRGB[256];
	FILE *fp;
	fp = fopen("color1.bmp", "rb");
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE *Image;
	BYTE * Output;
	if (hInfo.biBitCount == 8) {  //8�̸� �ε����÷�
		fread(hRGB, sizeof(RGBQUAD), 256, fp);	//�ȷ�Ʈ�� �׷��� ������ ���� ����
		Image = (BYTE *)malloc(ImgSize);
		Output = (BYTE *)malloc(ImgSize);
		fread(Image, sizeof(BYTE), ImgSize, fp);
	}
	else {   //24�̸� Ʈ���÷�
		Image = (BYTE *)malloc(ImgSize * 3);
		Output = (BYTE *)malloc(ImgSize * 3);
		fread(Image, sizeof(BYTE), ImgSize * 3, fp);
	}
	int W = hInfo.biWidth;
	int H = hInfo.biHeight;
	fclose(fp);

	//for (int i = 0; i < ImgSize; i++) {
	//	Output[i*3] = Image[i*3];   //��� ����
	//	Output[i * 3 + 1] = Image[i * 3 + 1]; //�׸� ����
	//	Output[i * 3 + 2] = Image[i * 3 + 2];  //���� ������ ��������, ������⵵�� 
	//}
	//   //	Output[i * 3 + 2] = 255;  //���� ������ ��������, ������⵵��



	//�� �ڵ带 ������ ������ ǥ���Ѱ���
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		Output[i * W * 3 + j * 3] = Image[i * W * 3 + j * 3];   //���λ���� ���� . ������ H�� �״��
	//		Output[i * W * 3 + j * 3 + 1] = Image[i*W * 3 + j * 3 + 1]; 
	//		Output[i * W * 3 + j * 3 + 2] = Image[i*W * 3 + j * 3 + 2];  
	//	}
	//}




	//for (int i = 100; i < 200; i++) {
	//	for (int j = 200; j < 300; j++) {
	//		Output[i * W * 3 + j * 3] = 255;
	//		Output[i * W * 3 + j * 3 + 1] = 255;
	//		Output[i * W * 3 + j * 3 + 2] = 0;
	//	}
	//}


	//���忡�� �þ����� ���� �׶��̼�
	//for (int i = 100; i <101; i++) {
	//	double weight;
	//	for (int j = 0; j < W; j++) {
	//		weight = j / (double)(W-1);
	//		Output[H / 2 * W * 3 + j * 3] = (1-weight)*0 +weight*255;   //����Ʈ ���� ���� 1�̵ǰ�. ����Ʈ�� Ŀ������ �ڿ����� �������°� Ŀ���� �׶��̼�
	//		Output[H / 2 * W * 3 + j * 3 + 1] = (1 - weight) * 0 + weight * 255;
	//		Output[H / 2 * W * 3 + j * 3 + 2] = (1 - weight) * 255 + weight * 0;
	//	}
	//}


	for (int i = 0; i < H; i++) {
		double weight;
		for (int j = 0; j < W; j++) {
			if (0 < i && i <= H / 3) {
				weight = j / (double)(W - 1);
				Output[3 * W * i + j * 3] = (1 - weight) * 255 + weight * 0;
				Output[3 * W * i + j * 3 + 1] = (1 - weight) * 0 + weight * 255;
				Output[3 * W * i + j * 3 + 2] = (1 - weight) * 0 + weight * 255;
			}
			else if (H / 3 < i && i <= H / 3 * 2) {
				weight = j / (double)(W - 1);
				Output[3 * W * i + j * 3] = (1 - weight) * 0 + weight * 255;
				Output[3 * W * i + j * 3 + 1] = (1 - weight) * 255 + weight * 0;
				Output[3 * W * i + j * 3 + 2] = (1 - weight) * 0 + weight * 255;
			}
			else if (H / 3 * 2 < i && i <= H) {
				weight = j / (double)(W - 1);
				Output[3 * W * i + j * 3] = (1 - weight) * 0 + weight * 255;
				Output[3 * W * i + j * 3 + 1] = (1 - weight) * 0 + weight * 255;
				Output[3 * W * i + j * 3 + 2] = (1 - weight) * 255 + weight * 0;
			}

		}
	}




	//Ʈ���÷� ������ �׷��̿� �ٸ��� �ȷ�Ʈ ����������, bgr�� �������� ����. 

	fp = fopen("22final_TEST.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	if (hInfo.biBitCount == 8) {
		fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
		fwrite(Output, sizeof(BYTE), ImgSize, fp);
	}
	else {
		fwrite(Output, sizeof(BYTE), ImgSize * 3, fp);
	}
	fclose(fp);
	free(Image);
	free(Output);

	return 0;
}

