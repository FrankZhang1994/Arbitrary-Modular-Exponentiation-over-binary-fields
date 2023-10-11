#include<stdio.h>
#include"windows.h"
#define powerinc 0
#define powerdouble 1

int poly131[5] = { 4,18,16,1,0 };
int poly163[5] = { 4,7,6,3,0 };
int poly193[5] = { 2,15,0 };
int poly233[5] = { 2,74,0 };
int poly283[5] = { 4,12,7,5,0 };
int poly409[5] = { 2,87,0 };
int poly571[5] = { 4,10,5,2,0 };

int fileoutput(WORD *table, int current, int field)
{
	int i, j, m, n;
	char fname[64];
	FILE *fp;
	WORD *temp;
	temp = (WORD *)malloc(field * field * sizeof(WORD));
	for (i = 0; i < field; i++)
	{
		temp[i * field + 0] = 0;
	}
	for (i = 0; i < field; i++)
	{
		for (j = 1; j <= table[i * field + 0]; j++)
		{
			m = table[i * field + j];
			n = temp[m * field + 0];
			temp[m * field + n + 1] = i;
			temp[m * field + 0]++;
		}
	}
	printf("\tFormat Altered.\n");
	sprintf_s(fname, 64, "sqr_2_%d.v", current);
	fopen_s(&fp, fname, "w");
	if (fp == NULL) {
		printf("The file can not be opened.\n");
		return 0;
	}
	fprintf(fp, "module sqr_2_%d\n(\n\tinput wire [%d:0] in,\n\toutput wire [%d:0] result\n);\n\n", current, field - 1, field - 1);
	for (i = 0; i < field; i++)
	{
		fprintf(fp, "\tassign result[%d] = ", i);
		for (j = 1; j < temp[i * field + 0]; j++)
		{
			fprintf(fp, "in[%d]^", temp[i * field + j]);
		}
		fprintf(fp, "in[%d];\n", temp[i * field + j]);
	}
	fprintf(fp, "endmodule\n");
	fclose(fp);
	free(temp);
	printf("\tFile Output Succeed.\n");
	return 1;
}

int powergen(WORD *sqr, WORD *in, WORD *out, int field, int current, int type, int output)
{
	int i, j, k, m, n, p, flag;
	for (i = 0; i < field; i++)
	{
		out[i * field + 0] = 0;
		for (j = 1; j <= in[i * field + 0]; j++)
		{
			m = in[i * field + j];
			n = out[i * field + 0];
			out[i * field + 0] += (type ? in[m * field + 0] : sqr[m * field + 0]);
			if (out[i * field + 0] > 2 * field - 1)
			{
				printf("Overflow!\n");
				return 0;
			}
			for (k = 1; k <= (type ? in[m * field + 0] : sqr[m * field + 0]); k++)
			{
				out[i * field + n + k] = (type ? in[m * field + k] : sqr[m * field + k]);
			}
			for (p = 1; p <= out[i * field + 0] - 1; p++)
			{
				flag = 1;
				for (k = p + 1; k <= out[i * field + 0] && flag; k++)
				{
					if (out[i * field + k] == out[i * field + p])
					{
						for (m = k; m <= out[i * field + 0]; m++)
							out[i * field + m] = out[i * field + m + 1];
						out[i * field + 0]--;
						for (m = p; m <= out[i * field + 0]; m++)
							out[i * field + m] = out[i * field + m + 1];
						out[i * field + 0]--;
						flag = 0;
					}
					if (!flag) p--;
				}
			}
		}
	}
	printf("Power_2_%d Done.\n", current);
	if (output) 
		if(!fileoutput(out, current, field)) 
			return 0;
	return 1;
}

int main()
{
	WORD *a;
	WORD *b;
	WORD *c; 
	int i, j, k, m, flag, temp;
	int seq[20];
	int powernum[40];
	int *poly;
	int field;
	printf("Please input m for GF(2^m):");
	scanf_s("%d", &field, 5);
	printf("\n");
	if (field == 131) poly = poly131; 
	else if (field == 163) poly = poly163;
	else if (field == 193) poly = poly193;
	else if (field == 233) poly = poly233;
	else if (field == 283) poly = poly283;
	else if (field == 409) poly = poly409;
	else if (field == 571) poly = poly571;
	else {
		printf("Binary field not supported.\n");
		system("pause");
		return 0;
	}
	a = (WORD *)malloc(field * field * sizeof(WORD));
	b = (WORD *)malloc(field * field * 2 * sizeof(WORD));
	c = (WORD *)malloc(field * field * 2 * sizeof(WORD));
	//Initialize
	for (i = 0, temp = field - 1;; i++) {
		if (temp / 2) {
			temp = temp / 2;
			seq[i + 1] = temp;
		}
		else break;
	}
	seq[0] = i;
	for (j = 1; i > 1; i--) {
		powernum[j] = seq[i];
		if (2 * seq[i] != seq[i - 1]) {
			j++;
			powernum[j] = 2 * seq[i];
		}
		j++;
	}
	powernum[j] = seq[1];
	powernum[0] = j;
	//SQR
	//i:input,a[i]:output affected by input
	if (poly[0] == 2) {
		for (i = 0; i < field; i++)
		{
			if (2 * i <= field - 1) {
				a[i * field + 1] = 2 * i;
				a[i * field + 0] = 1;
			}
			else if (2 * i <= 2 * field - 1 - poly[1]) {
				a[i * field + 1] = 2 * i - field + poly[1];
				a[i * field + 2] = 2 * i - field + poly[2];
				a[i * field + 0] = 2;
			}
			else {
				a[i * field + 1] = 2 * i - field + poly[2];
				a[i * field + 2] = 2 * i + poly[1] + poly[1] - 2 * field;
				a[i * field + 3] = 2 * i + poly[1] + poly[2] - 2 * field;
				a[i * field + 0] = 3;
			}
			for (j = 1; j <= a[i * field + 0] - 1; j++)
			{
				flag = 1;
				for (k = j + 1; k <= a[i * field + 0] && flag; k++)
				{
					if (a[i * field + k] == a[i * field + j])
					{
						for (m = k; m <= a[i * field + 0]; m++)
							a[i * field + m] = a[i * field + m + 1];
						a[i * field + 0]--;
						for (m = j; m <= a[i * field + 0]; m++)
							a[i * field + m] = a[i * field + m + 1];
						a[i * field + 0]--;
						flag = 0;
					}
				}
				if (!flag) j--;
			}
		}
	}
	else if (poly[0] == 4) {
		for (i = 0; i < field; i++)
		{
			if (2 * i <= field - 1) {
				a[i * field + 1] = 2 * i;
				a[i * field + 0] = 1;
			}
			else if (2 * i <= 2 * field - 1 - poly[1]) {
				a[i * field + 1] = 2 * i - field + poly[1];
				a[i * field + 2] = 2 * i - field + poly[2];
				a[i * field + 3] = 2 * i - field + poly[3];
				a[i * field + 4] = 2 * i - field + poly[4];
				a[i * field + 0] = 4;
			}
			else if (2 * i <= 2 * field - 1 - poly[2]) {
				a[i * field + 1] = 2 * i - field + poly[2];
				a[i * field + 2] = 2 * i - field + poly[3];
				a[i * field + 3] = 2 * i - field + poly[4];
				a[i * field + 4] = 2 * i + poly[1] + poly[1] - 2 * field;
				a[i * field + 5] = 2 * i + poly[1] + poly[2] - 2 * field;
				a[i * field + 6] = 2 * i + poly[1] + poly[3] - 2 * field;
				a[i * field + 7] = 2 * i + poly[1] + poly[4] - 2 * field;
				a[i * field + 0] = 7;
			}
			else if (2 * i <= 2 * field - 1 - poly[3]) {
				a[i * field + 1] = 2 * i - field + poly[3];
				a[i * field + 2] = 2 * i - field + poly[4];
				a[i * field + 3] = 2 * i + poly[1] + poly[1] - 2 * field;
				a[i * field + 4] = 2 * i + poly[1] + poly[2] - 2 * field;
				a[i * field + 5] = 2 * i + poly[1] + poly[3] - 2 * field;
				a[i * field + 6] = 2 * i + poly[1] + poly[4] - 2 * field;
				a[i * field + 7] = 2 * i + poly[2] + poly[1] - 2 * field;
				a[i * field + 8] = 2 * i + poly[2] + poly[2] - 2 * field;
				a[i * field + 9] = 2 * i + poly[2] + poly[3] - 2 * field;
				a[i * field + 10] = 2 * i + poly[2] + poly[4] - 2 * field;
				a[i * field + 0] = 10;
			}
			else {
				a[i * field + 1] = 2 * i - field + poly[4];
				a[i * field + 2] = 2 * i + poly[1] + poly[1] - 2 * field;
				a[i * field + 3] = 2 * i + poly[1] + poly[2] - 2 * field;
				a[i * field + 4] = 2 * i + poly[1] + poly[3] - 2 * field;
				a[i * field + 5] = 2 * i + poly[1] + poly[4] - 2 * field;
				a[i * field + 6] = 2 * i + poly[2] + poly[1] - 2 * field;
				a[i * field + 7] = 2 * i + poly[2] + poly[2] - 2 * field;
				a[i * field + 8] = 2 * i + poly[2] + poly[3] - 2 * field;
				a[i * field + 9] = 2 * i + poly[2] + poly[4] - 2 * field;
				a[i * field + 10] = 2 * i + poly[3] + poly[1] - 2 * field;
				a[i * field + 11] = 2 * i + poly[3] + poly[2] - 2 * field;
				a[i * field + 12] = 2 * i + poly[3] + poly[3] - 2 * field;
				a[i * field + 13] = 2 * i + poly[3] + poly[4] - 2 * field;
				a[i * field + 0] = 13;
			}
			for (j = 1; j <= a[i * field + 0] - 1; j++)
			{
				flag = 1;
				for (k = j + 1; k <= a[i * field + 0] && flag; k++)
				{
					if (a[i * field + k] == a[i * field + j])
					{
						for (m = k; m <= a[i * field + 0]; m++)
							a[i * field + m] = a[i * field + m + 1];
						a[i * field + 0]--;
						for (m = j; m <= a[i * field + 0]; m++)
							a[i * field + m] = a[i * field + m + 1];
						a[i * field + 0]--;
						flag = 0;
					}
				}
				if (!flag) j--;
			}
		}
	}
	else {
		printf("Error.\n");
		system("pause");
		return 0;
	}
	printf("Power_2_1 Done.\n");
	if (!fileoutput(a, powernum[1], field)) {
		system("pause");
		return 0;
	}
	for (i = 2; i <= powernum[0]; i++) {
		if (powernum[i] % 2) temp = powerinc;
		else temp = powerdouble;
		flag = 0;
		for (j = 1; j <= seq[0]; j++) {
			if (powernum[i] == seq[j]) flag = 1;
		}
		if (i == 2) {
			if (!powergen(a, a, b, field, powernum[i], temp, flag)) {
				system("pause");
				return 0;
			}
		}
		else if (i % 2) {
			if (!powergen(a, b, c, field, powernum[i], temp, flag)) {
				system("pause");
				return 0;
			}
		}
		else {
			if (!powergen(a, c, b, field, powernum[i], temp, flag)) {
				system("pause");
				return 0;
			}
		}
			
	}
	printf("All required units generated.\n");
	system("pause");
	return 0;
}


