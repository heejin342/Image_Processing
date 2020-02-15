//�̰� ����ؾ��� !!!!!!!!!!!!!!!!!!!


#include <stdio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996) 
#define SIZE 3

void swap(BYTE *a, BYTE *b) {   //���Ҹ����ִ� �Լ�
	BYTE temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//������ ���������ص��ȴ�. ��� ���۳������ �̵�����ͺ��� �ƽ����͸� �̿��ϴ°� ����, ��Ʈ����� �ִٸ� �����͸� �Ἥ ���� �������߿� �������� �Ͼ���� �ɷ��� �� �ְԲ��ϸ� ����� ���� �������ó�� ���� ������ 
void Sorting(BYTE * Arr) { 
	for (int i = 0; i < 8; i++) {  
		//�Ǻ��� �ε���. �Ѱ������� ���Ұ� ��� ����.
		for (int j = i + 1; j < 9; j++) { 
			//�񱳴�� �ε��� . ����������� �װź��� ������
			if (Arr[i] > Arr[j]) swap(&Arr[i], &Arr[j]);   
			//�ǹ����� Ŭ���� ���� ����������� . 
			//���� i�� ���� j����  ũ�� �迭�� ��(&)�� ��������� �Ѵ�. ���������̴ϱ� ! 
			//�̶� &�� ���۷��������� �Ѱܾ���
		}
	}
}//����������ִ��Լ�. �޵�ȸ޽�忡�� �����Լ��� ȣ���Ұ���
BYTE Median(BYTE * arr) {
	Sorting(arr);
	return arr[4];    //�߰� ���� 4��° �ε�������, ���� �Լ� ȣ������ ,4��° ���� �������ָ� �ȴ�.
}//�߰��� ��ȯ �Լ�
void Binarization(BYTE * Input, BYTE * Output, int Th, int W, int H)
{
	int Size = W * H;
	for (int i = 0; i < Size; i++)
	{
		if (Input[i] > Th) Output[i] = 255;
		else Output[i] = 0;
	}
}
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

// GlassFire �˰����� �̿��� �󺧸� �Լ�
void m_BlobColoring(BYTE* CutImage, int height, int width)
{
	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
	long k;
	short curColor = 0, r, c;
	//	BYTE** CutImage2;
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

	// ����� ȭ�Ұ����� ����Ǿ��ִµ�, ���� ���� ������ ���� ������ ã�Ƴ��� ����  !!!!!!!!!!!!
	for(i=1; i<=curColor; i++)
	{
		if(BlobArea[i]>=BlobArea[Out_Area]) Out_Area = i;
	}
 	// CutImage �迭 Ŭ����~
	for (k = 0; k < width*height; k++) CutImage[k] = 255;

	// coloring�� ����� �󺧸� ����� (Out_Area�� �����) ������ ���� ū �͸� CutImage�� ����
	for (k = 0; k < width*height; k++)
	{
		if(coloring[k] == Out_Area) CutImage[k] = 0;  // ���� ū �͸� ����
		//CutImage[k] = (unsigned char)(coloring[k] * grayGap);     //�󺧸��� ��ü�� ����ϴ°� �ƴ϶� �� ū�͸� ����ϰԲ� �ּ�����
	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
// �󺧸� �� ���� ���� ������ ���ؼ��� �̾Ƴ��� �ڵ� ����



int main() {
	BITMAPFILEHEADER hf;       
	BITMAPINFOHEADER hInfo;     
	RGBQUAD	hRGB[256];			
	FILE *fp;
//	fp = fopen("lenna_noise.bmp", "rb");          
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
	
	//ó��
	int W = hInfo.biWidth, H = hInfo.biHeight;
	
	Binarization(Image, Output, 100, W, H);
	
	m_BlobColoring(Output, H, W);    //m ��¼�� �Լ��� ���μ��ΰ� �Ųٷ� ���� ������� �Լ��� .�̰� �׷��� ���̾� �󺧸� �Լ��� . �̰��ϸ� ����� �İ��� �и��� �ǰ�, ����ϴ°� �����߿� ���� ū����


	//----------> ���� ������ ������ �Լ� . �̰��ϸ� �Ʊ� �ּ�ó���������Ƿ� �������߿� ���� ū�� ������ش�. �̰� th ���� 100���� ����������
	for (int i = 0; i < H - 1; i++) {   // �ƿ�ǲ���� ���� ������ ����. �̰��Ҷ� ��¿�input���� �ٲ��ش�
		for (int j = 1; j < W; j++) {
			if (Output[i*W + j] == 255) {    // ����ȭ�Ȱ� 255 �� ����ȭ�Ҷ�� �ǹ��� -> �׶��� ������ �˻�  . 
				if (!(Output[(i - 1)*W + j] == 255 &&
					Output[(i + 1)*W + j] == 255 &&
					Output[i*W + (j + 1)] == 255 &&        
					Output[i*W + (j - 1)] == 255)) {  //�̰� �� �ƴϸ� ��谡 �ƴѰ���. �� 255��� ������ ��谡 �ƴ� ������. �׷��� ��!�� �Ἥ �ٲ������
					Image[i*W + j] = 255;           //���ڵ��  m�Լ� ȣ�� �Ŀ� �Ͼ��. ���⼭ ���ϰ��� �� ���� ���̹Ƿ�, �� �۾��� �����ָ� ������ ��谡 �Ͼ���
					//�̰� ���������� ���κи� 255�� �Ͼ�� ���شٴ°��� . ���� �ƿ�ǲ���� ���������� ���µ�, �̹����� ��������ų�ſ��� ����� Image�� ����ؾ��� ������
				}   // ���� ������ ��谡 �ȳ��ü�������.���� �콼�κ� . ������پ˾Ƽ� ���� �Ͼ�� ó���Ѱ���. ����ȭ�� ����ϰԵǸ� ������� ����ũ ���°ź��� �̷��� ���������� �̿��ϴ°� �� ����ϱ���.
			}
		}
	}  //��������  4neiborhood�� �Ѱ���.    


 /*   //->>>>>>�߰��� ���͸����� ���� ��������� ����� ���ִ� �Լ�
	BYTE temp[9];  //ȭ�Ұ��� ����� �Ŵϱ� ����Ʈ Ÿ������ 
	int Margin = SIZE / 2;
	for(int i = 0; i < H - Margin; i++) {
	for (int j = Margin; j < W - Margin ; j++) {    //9���� ������ ���������� ȭ�Ұ��� �����Ѵ�.
		    temp[0] = Image[(i-1)*W + j-1];   
			temp[1] = Image[(i - 1)*W + j];
			temp[2] = Image[(i - 1)*W + j+1];  
			temp[3] = Image[i*W + j-1];
			temp[4] = Image[i*W + j];   //����
			temp[5] = Image[i*W + j+1];
			temp[6] = Image[(i+1)*W + j-1];
			temp[7] = Image[(i+1)*W + j];
			temp[8] = Image[(i+1)*W + j+1];
			Output[i*W+j] = Median(temp); //temp �� ���� �� �̵�� ���� ��ȯ���ִ� �Լ�
		}
	}
	//�̰�� ��äȭ���� �׸��� ���´�. ����� �������������� �� �����ִ� ���� ������ �ص� �̵��
	//���̿����� �������. 9���߿� 4�� �̻��� ������ �����ص� ����� �̵������ ���õǴ°���
	//����� ���̲��ִٴ°� ���������� ȭ�������� ���� �սǵǾ��մٴ� ����
*/



	//��ºκ�
	fp = fopen("1�������⿵��.bmp", "wb");               
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);		
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);		
//	fwrite(Image, sizeof(BYTE), ImgSize, fp);
	fwrite(Image, sizeof(BYTE), ImgSize, fp);    //���� ������ ������ �̰��̿�
	fclose(fp);					
	free(Image);				
	free(Output);
	return 0;
}



//����
//����ȭ�ؼ� ������ ���ߴµ�, �� ���׶���� �����߽��� ���ؼ� ��� ���� ���� ���� ������ �ִ� ȭ���� x�� x ��ǥ���� 
//�� ���ϰ�, y�� y ��ǥ���� �ٴ��ؼ� �װ� ������ ������ �����߽���
//�����߽� ������ ���� ����ȯ ���Ѽ� ������ 
//�� ���� ���� �Ͼ�� ũ�ν� ǥ�ø� ��
    //��������� �Ҷ��� �̷��� ���������� �ι�Ʈ ��Ų������ �󺧸��ؾ���
    //for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Output[i];   //��溸�� ������ ��ο� �� �����

