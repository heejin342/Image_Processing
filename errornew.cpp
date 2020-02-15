//#include <stdio.h>
//#include <Math.h>
//#include <stdlib.h>       
//#include <Windows.h>       
//#pragma warning (disable:4996) 
//#define SIZE 3
//
//void Erosion(BYTE *Img, BYTE *Out, int W, int H) {
//	����ȭ���̸� �˻�. �ֺ�ȭ�ҵ��� ��� �����̸� ���ΰ� ,�ϳ��� ����̸� ������ ������� �ٲ۴�,
//	for (int i = 1; i < H ; i++) {
//		for (int j = 1; j < W ; j++) {  //�����̶��
//			if (Img[i*W + j] == 255) {
//				if (!(Img[(i - 1)*W + j] == 255 && Img[(i + 1)*W + j] == 255 && Img[i*W + (j + 1)] == 255 && Img[i*W + (j - 1)] == 255))
//				{
//					Out[i*W + j] = 0;
//				}
//				else {
//					Out[i*W + j] = 255;
//				}
//			}
//			else {
//				Out[i*W + j] = 0;
//			}
//
//
//		}
//	}
//
//}
//void Dilation(BYTE *Img, BYTE *Out, int W, int H) {  //�̰� ��â
//	����ȭ���̸� �˻�. �ֺ�ȭ�ҵ��� ��� �����̸� ���ΰ� ,�ϳ��� ����̸� ������ ������� �ٲ۴�,
//	for (int i = 1; i < H ; i++) {
//		for (int j = 1; j < W ; j++) {  //����ε�, �ֺ�ȭ�ҵ� �� ��� �ϳ��� �����̸� ����� �������� �ٲ۴� ����
//			if (Img[i*W + j] == 0) {
//				if (Img[(i - 1)*W + j] == 255 || Img[(i + 1)*W + j] == 255 || Img[i*W + (j + 1)] == 255 || Img[i*W + (j - 1)] == 255)
//				{
//				Out[i*W + j] = 255;
//				}
//				else { //�����̶��
//					Out[i*W + j] = 0;
//				}
//			}
//			else
//				Out[i*W + j] = 255;
//
//		}
//	}
//
//}
//int main() {
//	BITMAPFILEHEADER hf;
//	BITMAPINFOHEADER hInfo;
//	RGBQUAD	hRGB[256];
//	FILE *fp;
//	fp = fopen("dilation.bmp", "rb");
//	if (fp == NULL) return 0;
//	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
//	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
//	int ImgSize = hInfo.biWidth * hInfo.biHeight;
//	BYTE *Image;
//	BYTE * Output;
//	if (hInfo.biBitCount == 8) {  //8�̸� �ε����÷�
//		fread(hRGB, sizeof(RGBQUAD), 256, fp);	//�ȷ�Ʈ�� �׷��� ������ ���� ����
//		Image = (BYTE *)malloc(ImgSize);
//		Output = (BYTE *)malloc(ImgSize);
//		fread(Image, sizeof(BYTE), ImgSize, fp);
//	}
//	else {   //24�̸� Ʈ���÷�
//		Image = (BYTE *)malloc(ImgSize * 3);
//		Output = (BYTE *)malloc(ImgSize * 3);
//		fread(Image, sizeof(BYTE), ImgSize * 3, fp);
//	}
//	int W = hInfo.biWidth;
//	int H = hInfo.biHeight;
//	fclose(fp);
//
//	
//
//
//
//
//
//
//
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//
//	Dilation(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++) Image[i] = Output[i];
//	Dilation(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++) Image[i] = Output[i];
//	Erosion(Image, Output, W, H);  // ��â(������ �ִ��� �ٿ��ְ�)�� ħ�� -> Ŭ��¡
//	Erosion(Image, Output, W, H);
//
//	2�� ������ ħ�� �ι� ��â �ι� �ϸ� �κ��� �Ų��������� ������ �������� ���ܹ���
//
//	
//
//
//
//
//	Ʈ���÷� ������ �׷��̿� �ٸ��� �ȷ�Ʈ ����������, bgr�� �������� ����. 
//
//	fp = fopen("190614_Dilation.bmp", "wb");
//	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
//	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
//	if (hInfo.biBitCount == 8) {
//		fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
//		fwrite(Output, sizeof(BYTE), ImgSize, fp);
//	}
//	else {
//		fwrite(Output, sizeof(BYTE), ImgSize * 3, fp);
//	}
//	fclose(fp);
//	free(Image);
//	free(Output);
//
//
//	int a;
//	scanf_s("%s", &a);
//
//	return 0;
//}
//
//�� ,, �������� ��Ŀ� ���� �̽��鿡 ���� �ǰ� 
//������п� ���� �ڷ� �ö������
//��������ߴ��� ������ �ǹ� ��ĳ ���ڷ� ������ �ϴ���?
//�ڽ��� �������� ������п� ���� ���� �ǰ�
//9�� ����
//**�⸻��縦 ���� �ǵ��
//
//1. �����ڷ�(ppt file)�� ���ַ� �غ�
//
//- ��Ȱ �ӿ� �ʿ��� ���� ������ �������� ���(�̷�)
//
//- �����ð��� ���� �����غ� ��ȸ���� �̽��鿡 ���� ������ �ǰ�
//
//
//
//2. E - campus�� ������ ���� ��������ڷ�
//
//- ������� ������ ���� ��ǥ�� ������ ���
//
//- ������ �������� ���� ��������� ������ ���� ������ Ÿ���� �ǰ�
//
//
//
//
