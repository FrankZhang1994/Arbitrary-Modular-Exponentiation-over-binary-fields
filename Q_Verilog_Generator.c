#include<stdio.h>
#include"windows.h"

int poly163[5] = { 4,7,6,3,0 };
int poly283[5] = { 4,12,7,5,0 };
int poly571[5] = { 4,10,5,2,0 };


// verilog output
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

		// printf("\tassign result[%d] = ", i);
		// for (j = 1; j < temp[i * field + 0]; j++)
		// {
		// 	printf("in[%d]^", temp[i * field + j]);
		// }
		// printf("in[%d];\n", temp[i * field + j]);
	}
	fprintf(fp, "endmodule\n");
	fclose(fp);
	free(temp);
	printf("\tFile Output Succeed.\n");
	return 1;
}


// sqr generate
int sqrgen(WORD *sqr, WORD *in, WORD *out, int field)
{
	int i, j, k, m, n, p, flag;
	for (i = 0; i < field; i++)
	{
		out[i * field + 0] = 0;
		for (j = 1; j <= in[i * field + 0]; j++)
		{
			m = in[i * field + j];
			n = out[i * field + 0];
			out[i * field + 0] += sqr[m * field + 0];
			if (out[i * field + 0] > 2 * field - 1)
			{
				printf("Overflow!\n");
				return 0;
			}
			for (k = 1; k <= sqr[m * field + 0]; k++)
			{
				out[i * field + n + k] = sqr[m * field + k];
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
}



int main()
{
    // initial parameter
	int field, exponent;
    int *poly;
	printf("Please input m for GF(2^m):");
    scanf_s("%d", &field);
	printf("\n");

    printf("Please input exponent for Q:");
    scanf_s("%d", &exponent);
	printf("\n");

	if (field == 163) poly = poly163;
	else if (field == 283) poly = poly283;
	else if (field == 571) poly = poly571;
	else {
		printf("Binary field not supported.\n");
		system("pause");
		return 0;
	}


    // initial Q
	WORD *a;
	WORD *b;
	WORD *c;

	a = (WORD *)malloc(field * field * sizeof(WORD));
	// b = (WORD *)malloc(field * field * 2 * sizeof(WORD));
	// c = (WORD *)malloc(field * field * 2 * sizeof(WORD));
	b = (WORD *)malloc(field * field * sizeof(WORD));
	c = (WORD *)malloc(field * field * sizeof(WORD));

    // generate Q
    int i, j, k, m, flag;

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


    // generate sqr
    for (i = 0; i < field; i++)
	{
		for (j = 0; j < field; j++)
		{
			b[i * field + j] = a[i * field + j];
		}
	}

    for (k = 1; k < exponent; k++)
    {
		for (i = 0; i < field; i++)
		{
			for (j = 0; j < field; j++)
			{
				c[i * field + j] = 0;
			}
		}
		sqrgen(a, b, c, field);
		for (i = 0; i < field; i++)
		{
			for (j = 0; j < field; j++)
			{
				b[i * field + j] = c[i * field + j];
			}
		}
    }

    fileoutput(c, exponent, field);








    return 0;
}