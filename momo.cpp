#include <stdio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996) 
#define SIZE 3

void swap(BYTE *a, BYTE *b) {
	BYTE temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	RGBQUAD	hRGB[256];
	FILE *fp;
	fp = fopen("LENNA.bmp", "rb");
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE * Image = (BYTE *)malloc(ImgSize);
	BYTE * Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	int W = hInfo.biWidth;
	int H = hInfo.biHeight;
	fclose(fp);

	/*for (int i = 0; i < H / 2; i++) {
		for (int j = 0; j < W; j++) {
			swap(&Output[i*W + j], &Output[(H - i - 1)*W + j]);
		}
	}*/
	
	//������ �̵� ,Translation
	/*int Tx = 30;
	int Ty = 20;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i + Ty >= 0 && i + Ty<H && j + Tx >= 0 && j + Tx < W)
				Output[(i + Ty)*W + (j + Tx)] = Image[i*W + j];
		}
	}*///���������� �ϰų�, �̷����ϰ������ Ŭ����ó�� ������� . �ٵ� �̰� �׳� �ܼ��� �����ָ� �Ǳ� ������ Ȧ�� ������ ���� ����
	

	/*
	//������ �̵� ,Translation
	int Tx = 30;
	int Ty = 20;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
		if (i + Ty >= 0 && i + Ty<H && j + Tx >= 0 && j + Tx < W)
			Output[i*W +j] = Image[(i + Ty)*W + (j + Tx)];
		}
	}//���������� �ϰų�, �̷����ϰ������ Ŭ����ó�� �������
	*/




	
	//������ -> ������ 
	//int TmpX, TmpY;
	//double Sx = 1.5;//�̶� ��� �� ����
	//double Sy = 1.5;//���ι��� Ȯ��, ���ι��� ���.
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		TmpX = j * Sx;							
	//		TmpY = i * Sy;							
	//		if (TmpY<H && TmpX < W)      //��� 0���� �۾����� ���� �����ϱ� �̷��Ը� Ŭ����ó��
	//			Output[TmpY*W + TmpX] = Image[i*W + j];              
	//		}
	//}   //����� Ȧ�̻���. ���ι������� Ȯ�밡 �Ǹ鼭 Ȧ�� ����°���. Ȧ�̻���������� ���� ������ -> ������ ����� �ʿ��ϴ�.
	//�����������ϸ� 30�� �ݽð������ �ι��� ������ �ð���� 30�� ������ �ȴ�
	


	//������ -> ������
	int TmpX, TmpY;
	double Sx = 1.5;//�̶� ��� �� ����
	double Sy = 1.5;//���ι��� Ȯ��, ���ι��� ���.
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			TmpX = j / Sx;
			TmpY = i / Sy;							
			if (TmpY < H && TmpX < W)      
				Output[i*W + j] = Image[TmpY*W + TmpX];
		}
	}
	

	//ȸ��  -> ������
	//int angle = 30;
	//double Theta = angle * 3.141592 / 180.0;           //degree �� radian ���κ�ȭ�Ѱ���
	//int TmpX, TmpY;
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {  //������ǥ�� j �ΰ���
	//		TmpX = j * cos(Theta) - i * sin(Theta);
	//		TmpY = j * sin(Theta) + i * cos(Theta);
	//		if (TmpX >= 0 && TmpX < H && TmpY >= 0 && TmpY < W)
	//			Output[TmpY*W + TmpX] = Image[i*W + j];
	//		}
	//}   //�̷����ϸ� 30����ŭ ȸ�� . 0.0�� �پ�����. ���Ʒ� �������ִٴ°� �´°���
	//������ Ȧ�� ���ܼ� ������������ �ؾ��Ѵ�. �ᱹ �̵��� ����� X' Y'�� �ڽ�������� �ι��� ����� �����ָ� ���� ��ǥ�� ����
	//��, 30����ŭ �ݽð��Ű�� ����� ������� ���ؼ� ���ϸ� ���� ����� ����� �ش�. ���󺹱� ��Ű�� �����ΰ�

	
	//������ ���Ʒ��� �������� . �̷��� �ϸ� ���� �پ��ִ°� �ƴ϶� ������ �پ��ְ� �ȴ�.
	for (int i = 0; i < H / 2; i++) {
		for (int j = 0; j < W; j++) {
			swap(&Output[i*W + j], &Output[(H - i - 1)*W + j]);
		}
	}

	/*for (int i = 0; i < W; i++) {
		for (int j = 0; j < H/2; j++) {
			swap(&Output[i*W + j], &Output[(W*i)-1-j]);
		}
	}*/


	//ȸ��  -> ������
	/*int angle = 180;
	double Theta = angle * 3.141592 / 180.0;
	int TmpX, TmpY;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			TmpX = j * cos(Theta) + i * sin(Theta);
			TmpY = -j * sin(Theta) + i * cos(Theta);
			if (TmpX >= 0 &&  TmpY < H && TmpY >= 0 && TmpX < W)
				Output[i*W +j] = Image[TmpY*W + TmpX];
		}
	} */  
	//�̷����ϸ� 30����ŭ ȸ�� . 0.0�� �پ�����. ���Ʒ� �������ִٴ°� �´°���
	//������ Ȧ�� ���ܼ� ������������ �ؾ��Ѵ�. �ᱹ �̵��� ����� X' Y'�� �ڽ�������� �ι��� ����� �����ָ� ���� ��ǥ�� ����
	//��, 30����ŭ �ݽð��Ű�� ����� ������� ���ؼ� ���ϸ� ���� ����� ����� �ش�. ���󺹱� ��Ű�� �����ΰ�
	//�̰� ������ �����

	//������ �߽��� �ƴ�, ������ �߽����� �Ѱ��� Cx,Cy���� ȸ���� �߽����� �ȴ�. 
	//int angle = 30;
	//double Theta = angle * 3.141592 / 180.0;
	//int Cx =  50;
	//int Cy = 50;    //�̰� ȸ������ �߽��̴�.
	//int TmpX;
	//int TmpY;
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		TmpX = cos(Theta)*(j - Cx) + sin(Theta)*(i - Cy) + Cx;
	//		TmpY = -sin(Theta)*(j - Cx) + cos(Theta)*(i - Cy) + Cy;
	//		if (TmpX >= 0 && TmpY < H && TmpY >= 0 && TmpX < W)
	//			Output[i*W + j] = Image[TmpY*W + TmpX];
	//	}
	//}

	//���  -> ������  . �ٵ� �̰� Ȧ���� ������ �ʾ����� ������.
	//double Shx = 0;
	//double Shy = 0.3;  //�¿쿡 ���ֺ��� �ִ� ������ ��Ʋ������. 
	//int TmpX, TmpY;
	//for (int i = 0; i < H; i++) {
	//	for (int j =0; j < W; j++) {
	//		TmpX = j + Shx*i ;
	//		TmpY = Shy*j + i;
	//		if (TmpX >= 0 && TmpY < H && TmpY >= 0 && TmpX < W)
	//			Output[TmpY*W + TmpX] = Image[i*W + j];
	//		}
	//}
	
	//�װ������Ϻ�ȯ��, ȸ���̳� �����ϸ� ���� Ȧ������ ������ ������� �������ڳ�
	//���������� �����ϸ� ���̳� ȸ���ϴ� ��쿡 �ذ����� �ΰ�������. �ϳ��� ��������. �ϳ��� ����������ä��. �����ȭ�Ұ��� ä��ų� ���Ͼ��ϰ�
	//�������� ���� ���� ���ߴ� �����ð��� ����� �� �� ����. ������ ��������� ��

	
	
	
	
	
	
	
	
	
	//���簢�� ����̿��� ���������� ���Ʒ��� ��Ʋ������ ����纯���̵ȴ�.
	//Shy�� 0.3�̰�, �տ��� 0�̸� �¿찡 ���ֺ��� ������ ��Ʋ������.
	//�̰� ���������� �غ�
	//�տ���(�����ϸ���, �����̼�)���� Ȧ���������� ������������ �ߴµ� �̰� ū ������� ���غ�����
	//Ȧ�̻���� ���������� ä��ų�(�����ŷ� ä���, ���Ͼ�) ���������� ����
	//������� 7-2����



	

	

	fp = fopen("ghghghghmoving1.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
	free(Image);
	free(Output);

	return 0;
}




