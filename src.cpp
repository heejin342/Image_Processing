#include <stdio.h>
#include <Math.h>
#include <stdlib.h>        //�����Ҵ��
#include <Windows.h>       //bmp������ ������� ����ü ����
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
		else Output[i] = (BYTE)((Image[i] - Low) / (double)(High - Low)) * 255;  //�и� ������ ����ȯ ������ . �׸��� 255 �� ������ 
	}
}
void ObtainAccHisto(int * Histo, int * AHisto) {
	AHisto[0] = Histo[0];
	for (int i = 1; i < 256; i++)
		AHisto[i] = AHisto[i - 1] + Histo[i];
}
void HistoEqualization(BYTE *Image, BYTE *Output, int W, int H, int * AHisto,int Gmax) {  //������׷� ��Ȱȭ
	int ImgSize = W * H;
	int Nt = ImgSize;
	double NR = Gmax / (double)Nt;
	int NSum[256];      //������ ����ȭ�� ���� �鰨
	for (int i = 0; i < 256; i++)
		NSum[i] = (int)(NR * AHisto[i]);
	for (int i = 0; i < ImgSize; i++)
		Output[i] = NSum[Image[i]];
}

void BrightnessCtr(BYTE * In , BYTE * Out , int Val , int W , int H) {    //w,h�� ���ο� ���� ��������. Ư�������� ��⸦ �����ų �� ����
	int Size = H * W;
	for (int i = 0; i < Size; i++) {
		if (In[i] + Val > 255) Out[i] = 255;
		else if (In[i] + Val < 0) Out[i] = 0;
		else Out[i] = In[i] + Val;
	}
}
void ContrastCtr(BYTE* In, BYTE * Out, double Val, int W, int H) {         //val�� �Ǽ��� �� �� �־ ����Ÿ���� �Ἥ ǥ��.
	int Size = H * W;
	for (int i = 0; i < Size; i++) {
		In[i] * Val > 255.0 ? Out[i] = 255 : Out[i] = (BYTE)(In[i] * Val);   //0���� ���� ���ɼ��� ���� ������ ������ �ʿ����
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
   //����ũ�� �������迭�� �޾Ƽ�(m) ���������� �ٲ�
	//const int Size = S;
	int Margin = SIZE / 2;
	double Mask[SIZE][SIZE];
	for (int i = 0; i < SIZE*SIZE; i++) 
		Mask[i/S][i%S] = m[i];   //1������ 2���� �迭�� ��й踦 �Ѱ��� , ���� ���ȣ�� �������� ����ȣ�� ���°���
	double temp = 0.0;
	for (int i = Margin; i < H - Margin; i++) {     //����ũ �߾��� ���ι��� �̵�
		for (int j =  Margin; j < W - Margin; j++) {   //����ũ �߾��� ���ι��� �̵�
														  //������ ����ũ ������� 2�� ���� ���� �Ǿ���Ѵ�. ����ũ �����  5�� ������ 2�� �Ǿ�� �ϰ�, ����ũ ����� 7�̸� , ������3
														  //�׷��� ������ �ʱ�ȭ�� �׷��� �ߴ�.
			for (int m = -Margin; m <= Margin; m++) {    //m�� -1�ϋ��� ����, 0�϶��� �� �ڽ�, 1�϶��� �ؿ��� ����. ����ũ �߾� ���� ���ι��� �ֺ�ȭ�� ����
				for (int n = -Margin; n <= Margin; n++) {//����ũ �߾����������� ���ι��� �ֺ�ȭ�� ����, ���ʿ�������ĳ
					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//���� �������̴ϱ� ���ʿ� ���� �ΰ����� �ĺ�����ѹ��Ȱ���(9���� �������� ������ ����Ǹ� �װ� ���ļ� �Ѱ��� �ճ��� �װ�)
																						//Image[i*W+j] �̰� ����ũ�� ���� ������  ,Mask[m+1][n+1] ������ -1�� ������
				}
			}
			Output[i*W + j] = (BYTE)temp;   //Output[i*W+j] ��� ��ġ
			temp = 0.0;
		}
	}//�̷����ϸ� ������ �������� ��������� �����

}
void HighPassFilter(BYTE *Image, BYTE *Output, int *m, const int S, int W, int H) {
	int Margin = SIZE / 2;
	int Mask[SIZE][SIZE];
	for (int i = 0; i < SIZE*SIZE; i++)
		Mask[i / SIZE][i%SIZE] = m[i];   //1������ 2���� �迭�� ��й踦 �Ѱ��� , ���� ���ȣ�� �������� ����ȣ�� ���°���
	int temp = 0;
	for (int i = Margin; i < H - Margin; i++) {     //����ũ �߾��� ���ι��� �̵�
		for (int j =  Margin; j < W - Margin; j++) {   //����ũ �߾��� ���ι��� �̵�
														  //������ ����ũ ������� 2�� ���� ���� �Ǿ���Ѵ�. ����ũ �����  5�� ������ 2�� �Ǿ�� �ϰ�, ����ũ ����� 7�̸� , ������3
														  //�׷��� ������ �ʱ�ȭ�� �׷��� �ߴ�.
			for (int m = -Margin; m <= Margin; m++) {    //m�� -1�ϋ��� ����, 0�϶��� �� �ڽ�, 1�϶��� �ؿ��� ����. ����ũ �߾� ���� ���ι��� �ֺ�ȭ�� ����
				for (int n = -Margin; n <= Margin; n++) {//����ũ �߾����������� ���ι��� �ֺ�ȭ�� ����, ���ʿ�������ĳ
					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//���� �������̴ϱ� ���ʿ� ���� �ΰ����� �ĺ�����ѹ��Ȱ���(9���� �������� ������ ����Ǹ� �װ� ���ļ� �Ѱ��� �ճ��� �װ�)
																						//Image[i*W+j] �̰� ����ũ�� ���� ������  ,Mask[m+1][n+1] ������ -1�� ������
				}

			}
			//Output[i*W + j] = abs(temp) / 3;   //Output[i*W+j] ��� ��ġ . ��� ���°� 9���� ����ũ ������ ���� 1�� �ȴٴ� �Ҹ���
			Output[i*W + j] = temp;
			temp = 0;
		}
	}
}
void HighPassFilter2(BYTE *Image, BYTE *Output, int *m, const int S, int W, int H) { // ����ũ ���� 1�ΰ�� ����� �Լ�
	int Margin = SIZE / 2;
	int *Temp = (int *)malloc(W*H*sizeof(int));
	double Mask[SIZE][SIZE];
	for (int i = 0; i < SIZE*SIZE; i++)
		Mask[i / SIZE][i%SIZE] = m[i];   //1������ 2���� �迭�� ��й踦 �Ѱ��� , ���� ���ȣ�� �������� ����ȣ�� ���°���
	int Max = -99999; 
	int Min = 99999;
	int temp = 0;
	for (int i =  Margin; i < H - Margin; i++) {     //����ũ �߾��� ���ι��� �̵�
		for (int j = Margin; j < W - Margin; j++) {   //����ũ �߾��� ���ι��� �̵�
														  //������ ����ũ ������� 2�� ���� ���� �Ǿ���Ѵ�. ����ũ �����  5�� ������ 2�� �Ǿ�� �ϰ�, ����ũ ����� 7�̸� , ������3
														  //�׷��� ������ �ʱ�ȭ�� �׷��� �ߴ�.
			for (int m = -Margin; m <= Margin; m++) {    //m�� -1�ϋ��� ����, 0�϶��� �� �ڽ�, 1�϶��� �ؿ��� ����. ����ũ �߾� ���� ���ι��� �ֺ�ȭ�� ����
				for (int n = -Margin; n <= Margin; n++) {//����ũ �߾����������� ���ι��� �ֺ�ȭ�� ����, ���ʿ�������ĳ
					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//���� �������̴ϱ� ���ʿ� ���� �ΰ����� �ĺ�����ѹ��Ȱ���(9���� �������� ������ ����Ǹ� �װ� ���ļ� �Ѱ��� �ճ��� �װ�)
																						//Image[i*W+j] �̰� ����ũ�� ���� ������  ,Mask[m+1][n+1] ������ -1�� ������
				}

			}
			if (temp > Max) Max = temp;
			if (temp < Min) Min = temp;
			Temp[i*W + j] = temp;   //Output[i*W+j] ��� ��ġ . ��� ���°� 9���� ����ũ ������ ���� 1�� �ȴٴ� �Ҹ���
			temp = 0;
		}
	}
	for (int i = 0; i < W*H; i++) {
		Output[i] = (Temp[i] - Min) / (double)(Max - Min) * 255;
	}
	free(Temp);
}

//������� �Է�, ó��, ���
int main() {

	BITMAPFILEHEADER hf;        //14����Ʈ�� BMP �������
	BITMAPINFOHEADER hInfo;     //40����Ʈ�� BMP �������
	RGBQUAD	hRGB[256];			//256*4 ����Ʈ�� �ȷ�Ʈ
	FILE *fp;
	fp = fopen("LENNA.bmp", "rb");          //������ ���¸��� rb. b�� ����Ʈ�� �ǹ� . �޸��� �����Ͱ� �ϵ��ũ�� �ִ� ���� ���Ͽ� ������
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);       //fp�� ����Ű�� ��ġ�κ��� ��Ʈ���������(14����Ʈ) �ѹ��о hf������ �־��
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);	   //���� fp�� 15����Ŵ. �ű⼭���� 40 ����Ʈ��ŭ �ѹ� �о hinfo �� ��ƶ�
	fread(hRGB, sizeof(RGBQUAD), 256, fp);				//4����Ʈ�� 256�� �о hRGB�迭�� ��ƶ�. �迭�� �̸��� �ּҴϱ� �ּұ�ȣ �Ⱥٿ�����
	int ImgSize = hInfo.biWidth * hInfo.biHeight;		//h������� ������ ���� ��������� ���� ��������� ���� ������ ������ ����������

														//�����Ҵ������� �̹����� ȭ�� ������ ����
	BYTE * Image = (BYTE *)malloc(ImgSize);		//ImgSize�� ũ�⸸ŭ �� ������ �����Ҵ��� ����. �о�� �Ҵ��ؾ� �� ũ�Ⱑ �������� ������ �����Ҵ�����
												//BYTE Image[ImgSize]; �� �����ǹ���. �ٵ� �迭�� ũ��� ������ �ȵǾ �̷��� �Ƚ��ذ���
	BYTE * Output = (BYTE *)malloc(ImgSize);    //ImgSize�� ����ó���� ����� ����
	fread(Image, sizeof(BYTE), ImgSize, fp);        //���� fp�� ����Ű�µǼ� BYTE ũ�⸸ŭ ������ ȭ�� ������ �̹����� ��ƶ�
	fclose(fp);                //���ϰ��� ������ ��� �ȴ�. ������ �� ���������ϱ�
//	int Histo[256] = { 0 };
//	int AHisto[256] = { 0 };

//	ObtainHisto(Image, Histo, hInfo.biWidth, hInfo.biHeight);
//	ObtainAccHisto(Histo, AHisto);
//	HistoEqualization(Image, Output, hInfo.biWidth, hInfo.biHeight, AHisto, 255);
//	HistoStretching(Image, Output,hInfo.biWidth , hInfo.biHeight ,Histo, 0.0 );
//	BrightnessCtr(Image, Output, 100, hInfo.biWidth, hInfo.biHeight);
//  BrightnessCtr(Image, Output, -100, hInfo.biWidth, hInfo.biHeight);
//	ContrastCtr(Image, Output, 1.9, hInfo.biWidth, hInfo.biHeight);
//	Binaryzation(Image, Output, 110, hInfo.biWidth,hInfo.biHeight);   // �Ӱ�ġ�� 110 �϶�


	//	for (int i = 0; i < ImgSize; i++)                  //0~255������ ����ȭ�Ұ��� 255���� ���� ����������
//		if(Image[i] *1.5 > 255.0)     
//			Output[i] = 255;						//Output[0]���� 255�� ������
//		else
//			Output[i] = (BYTE)(Image[i]*1.5) ;

//	for (int i = 0; i < ImgSize; i++)                  //0~255������ ����ȭ�Ұ��� 255���� ���� ����������
//		if (Image[i] * 0.7 > 255.0)
//			Output[i] = 255;						//Output[0]���� 255�� ������
//		else
//			Output[i] = (BYTE)(Image[i] * 0.7);                 1���� ���� ���� ���ؼ� ��ü���� ��Ʈ��Ʈ�� ��Ⱑ �������� ������
//	const int Size = 5;    //����ũ ����� Ű��� Ű����� �� ��������. ������ ����ð��� �������.

	double Mask[SIZE*SIZE];
	for (int i = 0; i < SIZE*SIZE; i++) Mask[i] = 1.0 / (SIZE*SIZE);
	//	= { 0.04,0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04,
	//	0.04, 0.04, 0.04,0.04,0.04
	//};   //3*3�϶��� 0.111�̿��µ�, 5*5�϶��� 0.04 -> ���ؼ� 1������	   . �� ���ڰ� Ŀ���� ������ ���� �о�����.

//	const int Size = 5;
//	double Mask[SIZE * SIZE];
//	for (int i = 0; i < SIZE * SIZE; i++) Mask[i] = 1.0 / (SIZE * SIZE);
	int m[SIZE*SIZE] = { -1, -1, -1,
								0,0,0,
								1,1,1 };   //������ �Ʒ��� ������ ��Ⱑ ���ϴ� ��谩 �����ϴ°���, ����� ���κ��� ��������, ������ �ƴ� .������ ������
//	LowPassFilter(Image, Output, Mask, SIZE, hInfo.biWidth, hInfo.biHeight);
//	HighPassFilter(Image, Output, Mask, SIZE, hInfo.biWidth, hInfo.biHeight);
	HighPassFilter2(Image, Output, m, SIZE, hInfo.biWidth, hInfo.biHeight);

//	int Margin = SIZE / 2;
//	int H = hInfo.biHeight;
//	int W = hInfo.biWidth;
//	double Mask[SIZE][SIZE];
//	for (int i = 0; i < SIZE*SIZE; i++)
//		Mask[i / SIZE][i%SIZE] = m[i];   //1������ 2���� �迭�� ��й踦 �Ѱ��� , ���� ���ȣ�� �������� ����ȣ�� ���°���
//	int temp = 0;
//	int W = hInfo.biHeight * hInfo.biWidth;
//	for (int i = 0 + Margin; i < H - Margin; i++) {     //����ũ �߾��� ���ι��� �̵�
//		for (int j = 0 + M argin; j < W - Margin; j++) {   //����ũ �߾��� ���ι��� �̵�
//														  //������ ����ũ ������� 2�� ���� ���� �Ǿ���Ѵ�. ����ũ �����  5�� ������ 2�� �Ǿ�� �ϰ�, ����ũ ����� 7�̸� , ������3
//														  //�׷��� ������ �ʱ�ȭ�� �׷��� �ߴ�.
//			for (int m = -Margin; m <= Margin; m++) {    //m�� -1�ϋ��� ����, 0�϶��� �� �ڽ�, 1�϶��� �ؿ��� ����. ����ũ �߾� ���� ���ι��� �ֺ�ȭ�� ����
//				for (int n = -Margin; n <= Margin; n++) {//����ũ �߾����������� ���ι��� �ֺ�ȭ�� ����, ���ʿ�������ĳ
//					temp += (Image[(i + m)*W + (j + n)] * Mask[m + Margin][n + Margin]);//���� �������̴ϱ� ���ʿ� ���� �ΰ����� �ĺ�����ѹ��Ȱ���(9���� �������� ������ ����Ǹ� �װ� ���ļ� �Ѱ��� �ճ��� �װ�)
//																						//Image[i*W+j] �̰� ����ũ�� ���� ������  ,Mask[m+1][n+1] ������ -1�� ������
//				}
//
//			}
//			Output[i*W + j] = abs(temp) / 3;   //Output[i*W+j] ��� ��ġ      , ��� 8�̵��� Ŀ���� 8�� ���ؾ���. �׷��� �����н� ���Ͱ� ������
//			temp = 0;
//		}
//	}

//���
	fp = fopen("output2.bmp", "wb");               //output ������ �������ְ��� . �� ��ġ�� fp�� ����Ŵ
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);		//fp������ �ִ� ������ ���� ����Ű�µ��� 1����Ʈ�� 14�� ��������� ����
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);		//rgb�迭������ 256�������
	fwrite(Output, sizeof(BYTE), ImgSize, fp);		//����ó���� ȭ�������� ���Ϸ� ��������. 
	fclose(fp);					//���������� �����ְ�
	free(Image);				//�����Ҵ� �ߴ��� free�� �����ش�.
	free(Output);
	return 0;
}

//�������� ���� ��ü �ȼ� ������;




//X����ũ Y ����ũ  ��ġ�°� ����
//�����Լ�������. �Һ�Y, �Һ�x �ΰ��� ��⸦ �ȼ����� ���ؼ� ��ȭ�Ұ��� ���ϸ� �� (3*3)
//������	������ 0~765 ���µ� �̰� �ٸ�����. �̰� ����غ�

//�Һ� ����ũ�� �Ἥ x,y ������ļ� ����ȭ���� �ؼ� ����ȭ �ϴ� �Լ��� ��������
//�̹̤Ӷ�� �迭�� �ִ� ȭ�Ұ��� �Һ� ������ �迭�� �־���, �����ϴ� ����ϴ� �迭
//�̰� �����Ҷ� �ʿ��� �迭
//�ƿ�ǲ�Ҷ� �ʿ��� �迭
