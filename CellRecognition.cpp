#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	/***********************************ͼ��Ԥ����**********************************/
	Mat img = imread("E:\\����ͼ����\\ori.png");
	imshow("ԭͼ", img);
	Mat gra(img.rows, img.cols, CV_8UC1);//����һ���Ҷ�ͼ
	unsigned char Threshold = 85;//��ֵ����ֵ��С�ڱ�ڴ��ڱ�ף��Գ�����
	unsigned char iGray = 0;
	//תΪ�Ҷ�ͼ
	for (int j = 0; j < img.cols; ++j)
	{
		for (int i = 0; i < img.rows; ++i)
		{
			unsigned char B = img.at<Vec3b>(j, i)[0];
			unsigned char G = img.at<Vec3b>(j, i)[1];
			unsigned char R = img.at<Vec3b>(j, i)[2];
			iGray = 0.299*R + 0.587*G + 0.114*B;//��ͼת�Ҷ�ͼ��ʽ
			//��ֵ��			
			if (iGray < Threshold)
			{
				gra.at<unsigned char>(j, i) = 0;
			}
			else
			{
				gra.at<unsigned char>(j, i) = 255;
			}
		}
	}
	//�����ֽ�
	Mat ini(gra.rows - 3, gra.cols - 2, CV_8UC1);
	for (int j1 = 0; j1 < gra.cols - 2; j1++)
	{
		for (int i1 = 0; i1 < gra.rows - 3; i1++)
		{
			ini.at<uchar>(j1, i1) = gra.at<uchar>(j1, i1);
		}
	}
	imshow("��ֵͼ", ini);
	//imwrite("E:\\����ͼ����\\��ֵͼ.png", ini);
	/************************************ϸ������************************************/
	Mat con(ini.rows, ini.cols, CV_8UC1);
	for (int j2 = 0; j2 < ini.cols; j2++)
	{
		for (int i2 = 0; i2 < ini.rows; i2++)
		{
			if (i2 == ini.rows - 1 || j2 == ini.cols - 1)
				con.at<uchar>(j2, i2) = 255;
			else if (ini.at<uchar>(j2, i2) != ini.at<uchar>(j2, i2 + 1))
				con.at<uchar>(j2, i2) = 0;
			else if (ini.at<uchar>(j2, i2) != ini.at<uchar>(j2 + 1, i2))
				con.at<uchar>(j2, i2) = 0;
			else
				con.at<uchar>(j2, i2) = 255;
		}
	}
	imshow("����", con);
	//imwrite("E:\\����ͼ����\\����.png", con);
	/************************************ϸ���ָ�************************************/
	Mat seg(ini.rows, ini.cols, CV_8UC1);
	int num = 0;
	//��ʼ��Ϊȫ��
	for (int j3 = 0; j3 < ini.cols; j3++)
	{
		for(int i3=0;i3<ini.cols;i3++)
			seg.at<uchar>(j3, i3) = 255;
	}
	//����ͨ
	for (int j3 = 0; j3 < ini.cols; j3++)
	{
		for (int i3 = 0; i3 < ini.rows; i3++)
		{
			if (ini.at <uchar>(j3, i3) != 255)
			{
				if (seg.at<uchar>(j3 - 1, i3) != 255 && seg.at<uchar>(j3, i3 - 1) == 255)
					seg.at<uchar>(j3, i3) = seg.at<uchar>(j3 - 1, i3);
				else if (seg.at<uchar>(j3, i3 - 1) != 255 && seg.at<uchar>(j3 - 1, i3) == 255)
					seg.at<uchar>(j3, i3) = seg.at<uchar>(j3, i3 - 1);
				else if (seg.at<uchar>(j3, i3 - 1) != 255 && seg.at<uchar>(j3 - 1, i3) != 255)
				{
					seg.at<uchar>(j3, i3) = seg.at<uchar>(j3 - 1, i3);
					if (seg.at<uchar>(j3 - 1, i3) != seg.at<uchar>(j3, i3 - 1))
						seg.at<uchar>(j3, i3 - 1) = seg.at<uchar>(j3 - 1, i3);
				}
				else
				{
					num++;
					seg.at<uchar>(j3, i3) = num;
				}

			}
		}
	}
	//���±��
	for (int m = 0; m <= 28; m++)
	{
		for (int j3 = 0; j3 < seg.cols; j3++)
		{
			for (int i3 = 0; i3 < seg.rows; i3++)
			{
				if (seg.at <uchar>(j3, i3) != 255)
				{
					int min = seg.at<uchar>(j3, i3);
					if (seg.at<uchar>(j3 - 1, i3) != 255 && seg.at<uchar>(j3 - 1, i3) < min)
						min = seg.at<uchar>(j3 - 1, i3);
					if (seg.at<uchar>(j3 + 1, i3) != 255 && seg.at<uchar>(j3 + 1, i3) < min)
						min = seg.at<uchar>(j3 + 1, i3);
					if (seg.at<uchar>(j3, i3 - 1) != 255 && seg.at<uchar>(j3, i3 - 1) < min)
						min = seg.at<uchar>(j3, i3 - 1);
					if (seg.at<uchar>(j3, i3 + 1) != 255 && seg.at<uchar>(j3, i3 + 1) < min)
						min = seg.at<uchar>(j3, i3 + 1);
					seg.at<uchar>(j3, i3) = min;
				}
			}
		}
	}
	imshow("���", seg);
	//imwrite("E:\\����ͼ����\\���.png", seg);
	//����Ч��ͼ
	Mat col(seg.rows, seg.cols, CV_8UC3);
	for (int i4 = 0; i4 < seg.rows; i4++)
	{
		for (int j4 = 0; j4 < seg.cols; j4++)
		{
			if (seg.at<uchar>(j4, i4) == 255)
			{
				col.at<Vec3b>(j4, i4)[0] = 255;//B
				col.at<Vec3b>(j4, i4)[1] = 255;//G
				col.at<Vec3b>(j4, i4)[2] = 255;//R
			}
			else
			{
				int color = seg.at<uchar>(j4, i4)*(256 * 256 * 256 - 1) / 21;
				col.at<Vec3b>(j4, i4)[0] = (unsigned char)((color & 0x000000FF));//B
				col.at<Vec3b>(j4, i4)[1] = (unsigned char)((color & 0x0000FF00) >> 8);//G
				col.at<Vec3b>(j4, i4)[2] = (unsigned char)((color & 0x00FF0000) >> 16);//R
			}
		}
	}
	imshow("Ч��ͼ", col);
	//imwrite("E:\\����ͼ����\\Ч��ͼ.png", col);
	/************************************ϸ������************************************/
	int count[255] = { 0 };//��¼ϸ������
	int x[255] = { 0 };//��¼j�ĺ�
	int y[255] = { 0 };//��¼i�ĺ�
	//��������������
	for (int j5 = 0; j5 < seg.cols; j5++)
	{
		for (int i5 = 0; i5 < seg.rows; i5++)
		{
			if (seg.at<uchar>(j5, i5) != 255)
			{
				count[seg.at<uchar>(j5, i5)]++;
				x[seg.at<uchar>(j5, i5)] += j5;
				y[seg.at<uchar>(j5, i5)] += i5;
			}
		}
	}
	//����������
	for (int n = 0; n < 256; n++)
	{
		if (count[n])
		{
			x[n] = x[n] / count[n];
			y[n] = y[n] / count[n];
			col.at<Vec3b>(x[n], y[n])[0] = 255;//B
			col.at<Vec3b>(x[n], y[n])[1] = 255;//G
			col.at<Vec3b>(x[n], y[n])[2] = 255;//R
		}
	}
	imshow("����", col);
	//����uֵ
	double u1[255] = { 0 };//�����11
	double u2[255] = { 0 };//�����20
	double u3[255] = { 0 };//�����02
	double r[255] = { 0 };//����2a
	double r1[255] = { 0 };//���ܽǶ�1
	double r2[255] = { 0 };//���ܽǶ�2
	for (int j6 = 0; j6 < seg.rows; j6++)
	{
		for (int i6 = 0; i6 < seg.cols; i6++)
		{
			if (seg.at<uchar>(j6, i6) != 255)
			{
				u1[seg.at<uchar>(j6, i6)] += ((j6 - x[seg.at<uchar>(j6, i6)])*(i6 - y[seg.at<uchar>(j6, i6)]));
				u2[seg.at<uchar>(j6, i6)] += ((j6 - x[seg.at<uchar>(j6, i6)])*(j6 - x[seg.at<uchar>(j6, i6)]));
				u3[seg.at<uchar>(j6, i6)] += ((i6 - y[seg.at<uchar>(j6, i6)])*(i6 - y[seg.at<uchar>(j6, i6)]));
			}
		}
	}
	//����б��
	int n1[255] = { 0 };//��¼��һ����
	int n2[255] = { 0 };//��¼�������
	for (int n = 0; n < 256; n++)
	{
		if (count[n])
		{
			r[n] =2*u1[n] / (u2[n] - u3[n]);//tan(2a)
			r1[n] = tan(atan(r[n]) / 2);//tan(a);
			r2[n] = tan(atan(r[n]) / 2-3.1415926/2);//tan(a-pi/2);
		}
	}
	
	//��ʮ��ѡ����
	for (int j7 = 0; j7 < col.rows; j7++)
	{
		for (int i7 = 0; i7 < col.cols; i7++)
		{
			int n = seg.at<uchar>(j7, i7);
			if (i7 == round(r1[n] * (j7 - x[n]) + y[n]))//б��1����ɨ��
				n1[n]++;
			if (j7 == round(x[n] + (i7 - y[n]) / r1[n]))//б��2����ɨ��
				n2[n]++;
			if (i7 == round(r2[n] * (j7 - x[n]) + y[n]))//б��1����ɨ��
				n1[n]++;
			if (j7 == round(x[n] + (i7 - y[n]) / r2[n]))//б��2����ɨ��
				n2[n]++;
		}
	}
	//������
	for(int j7=0;j7<col.rows;j7++)
	{
		for (int i7 = 0; i7 < col.cols; i7++)
		{
			int n = seg.at<uchar>(j7, i7);
			if (n1[n] >= n2[n])
			{
				if (i7 == round(r1[n] * (j7 - x[n]) + y[n]))//б��1����ɨ��
				{
					col.at<Vec3b>(j7, i7)[0] = 255;//B
					col.at<Vec3b>(j7, i7)[1] = 255;//G
					col.at<Vec3b>(j7, i7)[2] = 255;//R
				}
				if (j7 == round(x[n] + (i7 - y[n]) / r1[n]))//б��1����ɨ��
				{
					col.at<Vec3b>(j7, i7)[0] = 255;//B
					col.at<Vec3b>(j7, i7)[1] = 255;//G
					col.at<Vec3b>(j7, i7)[2] = 255;//R
				}
			}
			else
			{
				if (i7 == round(r2[n] * (j7 - x[n]) + y[n]))//б��2����ɨ��
				{
					col.at<Vec3b>(j7, i7)[0] = 255;//B
					col.at<Vec3b>(j7, i7)[1] = 255;//G
					col.at<Vec3b>(j7, i7)[2] = 255;//R
				}
				if (j7 == round(x[n] + (i7 - y[n]) / r2[n]))//б��2����ɨ��
				{
					col.at<Vec3b>(j7, i7)[0] = 255;//B
					col.at<Vec3b>(j7, i7)[1] = 255;//G
					col.at<Vec3b>(j7, i7)[2] = 255;//R
				}
			}
		}
	}
	imshow("����", col);
	//imwrite("E:\\����ͼ����\\����.png", col);
	waitKey(0);
}