#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** creat_2darray(int raw,int col);
int display(int** a,int raw,int col)
{
	int i,j;
	for(i=0;i<raw;i++)
		for(j=0;j<col;j++)
			printf("%d\t",a[i][j]);

	return 0;
}

int main(int argc,char *argv[])
{
	int **mat;
	int r,c,i,j,n_b=0,n_a=0,th,clut_A[100000],clut_B[100000],tot_A=0,tot_B=0;
	FILE *fp, *data;
	float dev_A=0.0, dev_B=0.0, mean_A, mean_B, ratio, d, sdev_A,sdev_B,temp;

	for(i=0;i<argc;i++)
		printf("%s\n",argv[i]);
	
	fp = fopen("1.txt","r");
	
	r=198;
	c=200;
	printf("%d %d\n",r,c);

	mat = creat_2darray(r,c);

	for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(j==c-1)
					fscanf(fp,"%d\n",&mat[i][j]);
				else
					fscanf(fp,"%d\t",&mat[i][j]);
			}
	fclose(fp);
	
	data = fopen("result.txt","w");
	for(th=0;th<256;th++)
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(th>=mat[i][j])
				{
					clut_A[n_a]=mat[i][j];
					n_a++;
					tot_A = tot_A + mat[i][j];
				}
				else
				{
					clut_B[n_b]=mat[i][j];
					n_b++;
					tot_B = tot_B + mat[i][j];
				}
			}
		
		mean_A = (float)tot_A/n_a;
		mean_B = (float)tot_B/n_b;
	
		for(i=0;i<n_a;i++)
			dev_A = dev_A+((float)clut_A[i]-mean_A)*((float)clut_A[i]-mean_A);
		for(i=0;i<n_b;i++)
			dev_B = dev_B+((float)clut_B[i]-mean_B)*((float)clut_B[i]-mean_B);

		sdev_A = (float)sqrt(dev_A/n_a);
		sdev_B = (float)sqrt(dev_B/n_b);
	
		d = (abs(mean_A-mean_B))/(float)sqrt(sdev_A*sdev_A+sdev_B*sdev_B);
		ratio = (float)n_a/n_b;
		fprintf(data,"%d\t%f\t%f\n",th,ratio,d);
		printf("%d\t%d\t%d\t%f\t%f\t%d\t%d\n",th,tot_A,tot_B,sdev_A,sdev_B,n_a,n_b);
		n_a=0;
		n_b=0;
		tot_A=0;
		tot_B=0;
		dev_A=0.0;
		dev_B=0.0;
	}
		fclose(data);
		
	return 0;
}

int** creat_2darray(int raw,int col)
{
	int **a,i;

	a = (int**)malloc(raw * sizeof(int*));

	for(i=0;i<raw;i++)
		a[i] = (int*)malloc(col * sizeof(int));

	return (a);
}
