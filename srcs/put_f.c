/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffood <ffood@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:04:21 by htrent            #+#    #+#             */
/*   Updated: 2020/02/06 17:08:38 by ffood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

typedef	struct	s_float
{
	unsigned	m : 23;
	unsigned	e : 8;
	unsigned	s : 1;
}				t_float;

typedef	struct	s_double
{
	unsigned long long	m : 52;
	unsigned long long	e : 11;
	unsigned long long	s : 1;
}				t_double;

union	u_number
{
	t_double		bits;
	double 			num;
};

union code
{
	t_double	p;
	struct{
		unsigned long long a0 : 1;
		unsigned long long a1 : 1;
		unsigned long long  a2 : 1;
		unsigned long long  a3 : 1;
		unsigned long long  a4 : 1;
		unsigned long long  a5 : 1;
		unsigned long long  a6 : 1;
		unsigned long long  a7 : 1;
		unsigned long long  a8 : 1;
		unsigned long long  a9 : 1;
		unsigned long long  a10 : 1;
		unsigned long long  a11 : 1;
		unsigned long long  a12 : 1;
		unsigned long long  a13 : 1;
		unsigned long long  a14 : 1;
		unsigned long long  a15 : 1;
		unsigned long long  a16 : 1;
		unsigned long long  a17 : 1;
		unsigned long long  a18 : 1;
		unsigned long long  a19 : 1;
		unsigned long long  a20 : 1;
		unsigned long long  a21 : 1;
		unsigned long long  a22 : 1;
		unsigned long long  a23 : 1;
		unsigned long long  a24 : 1;
		unsigned long long  a25 : 1;
		unsigned long long  a26 : 1;
		unsigned long long  a27 : 1;
		unsigned long long  a28 : 1;
		unsigned long long  a29 : 1;
		unsigned long long  a30 : 1;
		unsigned long long  a31 : 1;
		unsigned long long  a32 : 1;
		unsigned long long  a33 : 1;
		unsigned long long  a34 : 1;
		unsigned long long  a35 : 1;
		unsigned long long  a36 : 1;
		unsigned long long  a37 : 1;
		unsigned long long  a38 : 1;
		unsigned long long  a39 : 1;
		unsigned long long  a40 : 1;
		unsigned long long  a41 : 1;
		unsigned long long  a42 : 1;
		unsigned long long  a43 : 1;
		unsigned long long  a44 : 1;
		unsigned long long  a45 : 1;
		unsigned long long  a46 : 1;
		unsigned long long  a47 : 1;
		unsigned long long  a48 : 1;
		unsigned long long  a49 : 1;
		unsigned long long  a50 : 1;
		unsigned long long  a51 : 1;
		unsigned long long  a52 : 1;
		unsigned long long  a53 : 1;
		unsigned long long  a54 : 1;
		unsigned long long  a55 : 1;
		unsigned long long  a56 : 1;
		unsigned long long  a57 : 1;
		unsigned long long  a58 : 1;
		unsigned long long  a59 : 1;
		unsigned long long  a60 : 1;
		unsigned long long  a61 : 1;
		unsigned long long  a62 : 1;
		unsigned long long  a63 : 1;
	} byte;
};

void	print_buf1(char big[NUM_SIZE])
{
	int i;

	i = NUM_SIZE - 1;
	ft_putstr("BUF1:\"");
	while (big[i] != -1)
		i--;
	i++;
	while (i < NUM_SIZE)
		ft_putchar(big[i++] + '0');
	ft_putstr("\"\n");
}

void	print_buf2(char big[NUM_SIZE])
{
	int i;

	i = 0;
	ft_putstr("BUF2:\"");
	while (big[i] != -1)
		ft_putchar(big[i++] + '0');
	ft_putstr("\"\n");
}


void	add_pow_two(char big_num[NUM_SIZE], int power)
{
	char	big_two[NUM_SIZE];
	int i;
	int j;
	int flag;
	int prev_flag;
	unsigned long long int number;

	j = NUM_SIZE - 1;
	i = 0;
	flag = 0;
	prev_flag = 0;
	ft_memset(big_two, -1, NUM_SIZE);
	if (power < 64)
	{
		number = (unsigned long long)1 << power;
		while (number > 0)
		{
			if (big_num[j] == -1)
				big_num[j] = 0;
			if (flag)
				big_num[j]++;
			if ((big_num[j] + (number % 10)) > 9)
				flag = 1;
			else
				flag = 0;
			big_num[j] = (big_num[j] + number % 10) % 10;
			number /= 10;
			j--;
		}
		if (flag)
			big_num[j] = (big_num[j] == -1) ? 1 : big_num[j] + 1;
	}
	else
	{
		number = (unsigned long long)1 << 63;

		while (number > 0) //number to array
		{
			big_two[j--] = number % 10;
			number = number / 10;
		}

		while (i < power - 63) //array power
		{
			j = NUM_SIZE - 1;
			prev_flag = 0;
			flag = 0;
			while (big_two[j] != -1) //array * 2
			{
				if (big_two[j] * 2 > 9)
					flag = 1;
				big_two[j] = (big_two[j] * 2) % 10;
				if (prev_flag)
					big_two[j]++;
				prev_flag = flag;
				flag = 0;
				j--;
			}
			if (prev_flag)
				big_two[j] = 1;
			i++;
		}

		j = NUM_SIZE - 1;
		while (big_two[j] != -1) //array's summary
		{
			if (big_num[j] == -1)
				big_num[j]++;
			if ((big_num[j] + big_two[j]) > 9)
				flag = 1;
			big_num[j] = (big_num[j] + big_two[j]) % 10;
			if (prev_flag)
				big_num[j]++;
			prev_flag = flag;
			flag = 0;
			j--;
		}
		if (prev_flag)
			big_num[j] = 1;
	}
	//print_buf1(big_num);
}

void	add_pow_five(char big_num[NUM_SIZE], int power)
{
	char	big_five[NUM_SIZE];
	int		i;
	int		j;
	int 	prev_power;
	int flag;
	int digit;
	int prev_flag;
	int prev_digit;
	unsigned long long int number;

	prev_power = power;
	j = NUM_SIZE - 1;
	i = 0;
	flag = 0;
	prev_flag = 0;
	ft_memset(big_five, -1, NUM_SIZE);
	if (power < 28)
	{
		big_five[NUM_SIZE - 1]  = 1;
		while (power > 0)
		{
			j = NUM_SIZE - 1;
			flag = 0;
			prev_flag = 0;
			while (big_five[j] != -1)
			{
				if ((big_five[j] * 5) > 9)
				{
					flag = 1;
					digit = (big_five[j] * 5) / 10;
				}
				big_five[j] = (big_five[j] * 5) % 10;
				if (prev_flag)
				{
					if (big_five[j] + prev_digit > 9)
						digit += (big_five[j] + prev_digit) / 10;
					big_five[j] = (big_five[j] + prev_digit) % 10;
				}
				prev_flag = flag;
				prev_digit = digit;
				flag = 0;
				j--;
			}
			if (prev_flag)
				big_five[j] = prev_digit;
			power--;
			//print_buf1(big_five);
		}
		//print_buf1(big_five);
	}
	else
	{
		number = POW_5_27;
		j = NUM_SIZE - 1;
		while (number > 0) //number to array
		{
			big_five[j--] = number % 10;
			number = number / 10;
		}
		//print_buf1(big_five);
		while (power - 27 > 0)
		{
			j = NUM_SIZE - 1;
			flag = 0;
			prev_flag = 0;
			while (big_five[j] != -1)
			{
				if ((big_five[j] * 5) > 9)
				{
					flag = 1;
					digit = (big_five[j] * 5) / 10;
				}
				big_five[j] = (big_five[j] * 5) % 10;
				if (prev_flag)
				{
					if (big_five[j] + prev_digit > 9)
						digit += (big_five[j] + prev_digit) / 10;
					big_five[j] = (big_five[j] + prev_digit) % 10;
				}
				prev_flag = flag;
				prev_digit = digit;
				flag = 0;
				j--;
			}
			if (prev_flag)
				big_five[j] = prev_digit;
			power--;
			//print_buf1(big_five);
		}
	}

	i = 0;
	while (big_five[i] == -1) //для кол-ва цифр
		i++;

	i = NUM_SIZE - i; //кол-во цифр
	j = 0;
	//while (j < i)  /////////////////////////////////// ЭТО МОЖНО СДЕЛАТЬ СРАЗУ В ЦИКЛЕ
	//{
	//	big_num[j] += (big_num[j] == -1) ? 1 : 0; //зануляем цифры без значений, доводим до "столбика"
	//	j++;
	//}
	flag = 0;
	prev_flag = 0;
	j = NUM_SIZE - 1; //с конца берем из big_five
	i = (prev_power > i) ? prev_power : i;
	i--; // с конца берем из big_num; вычитаем чтобы подвести к цифре, тк кол-во цифр на 1 больше (массив начинается с 0)
	while (big_five[j] != -1)
	{
		if (big_num[i] == -1)
			big_num[i] = 0;
		if ((big_num[i] + big_five[j]) > 9)
			flag = 1;
		big_num[i] = (big_num[i] + big_five[j]) % 10;
		if (prev_flag)
		{
			if (big_num[i] + 1 > 9)
				flag = 1;
			big_num[i] = (big_num[i] + 1) % 10;
		}
		prev_flag = flag;
		flag = 0;
		i--;
		j--;
	}
	while (prev_flag)
	{
		prev_flag = (big_num[i] + 1 > 9) ? 1 : 0;	
		big_num[i] = (big_num[i] + 1) % 10;
		i--;
	}
}

int		put_data_f(t_printf *data, int *k)
{
	long double num;
	union u_number number;
	union code c;
	char	big_num1[NUM_SIZE]; //целая часть
	char	big_num2[NUM_SIZE]; //дробная часть

	//unsigned long long t;
	int i;
	int e;

	ft_memset(big_num1, -1, NUM_SIZE);
	ft_memset(big_num2, -1, NUM_SIZE);
	if (data->size == L_SIZE)
		num = (double) va_arg(data->params, double);
	else if (data->size == LL_SIZE)
		num = (long double) va_arg(data->params, long double);
	else
		num = (double) va_arg(data->params, double);
	number.num = num;
	c.p = number.bits;

	printf(  "\n63 | 62  61  60  59  58  57  56  55  54  "
		     "53  52 | 51  50  49  48  47  46  45  44  "
	         "43  42  41  40  39  38  37  36  35  34  "
		     "33  32  31  30  29  28  27  26  25  24  "
	         "23  22  21  20  19  18  17  16  15  14  "
		     "13  12  11  10  9  8  7  6  5  4  "
	         "3  2  1  0 \n");
	printf(  "%d  | %d   %d   %d   %d   %d   %d   %d   %d   %d   "
		     "%d   %d  | %d   %d   %d   %d   %d   %d   %d   %d   "
	         "%d   %d   %d   %d   %d   %d   %d   %d   %d   %d   "
		     "%d   %d   %d   %d   %d   %d   %d   %d   %d   %d   "
	         "%d   %d   %d   %d   %d   %d   %d   %d   %d   %d   "
		     "%d   %d   %d   %d   %d  %d  %d  %d  %d  %d  "
	         "%d  %d  %d  %d\n",
			 c.byte.a63, c.byte.a62, c.byte.a61, c.byte.a60, c.byte.a59, c.byte.a58, c.byte.a57, c.byte.a56, c.byte.a55, c.byte.a54,
			 c.byte.a53, c.byte.a52, c.byte.a51, c.byte.a50, c.byte.a49, c.byte.a48, c.byte.a47, c.byte.a46, c.byte.a45, c.byte.a44,
	         c.byte.a43, c.byte.a42, c.byte.a41, c.byte.a40, c.byte.a39, c.byte.a38, c.byte.a37, c.byte.a36, c.byte.a35, c.byte.a34,
			 c.byte.a33, c.byte.a32, c.byte.a31, c.byte.a30, c.byte.a29, c.byte.a28, c.byte.a27, c.byte.a26, c.byte.a25, c.byte.a24,
	         c.byte.a23, c.byte.a22, c.byte.a21, c.byte.a20, c.byte.a19, c.byte.a18, c.byte.a17, c.byte.a16, c.byte.a15, c.byte.a14,
	         c.byte.a13, c.byte.a12, c.byte.a11, c.byte.a10, c.byte.a9, c.byte.a8, c.byte.a7, c.byte.a6, c.byte.a5, c.byte.a4,
	         c.byte.a3, c.byte.a2, c.byte.a1, c.byte.a0);

	//i = 0;
	//while (i < 11)
	//{
	//	e += ((number.bits.e >> i) & 1) << i;
	//	i++;
	//}
	i = 1;
	e = number.bits.e - 1023;
	printf("e: %d\n", e);
	if (e >= 0) // целая часть
		add_pow_two(big_num1, e);
	if (e < 0)
		add_pow_five(big_num2, e);
	while (i < 53)
	{
		printf("e-i: %d, %llu\n", (e - i), (number.bits.m >> (52 - i)) & 1);
		if (e - i < 0)
		{
			if ((number.bits.m >> (52 - i)) & 1)
				add_pow_five(big_num2, -(e - i));
		}
		else if (e - i >= 0)
		{
			if ((number.bits.m >> (52 - i)) & 1)
				add_pow_two(big_num1, e - i);
		}
		print_buf1(big_num1);
		print_buf2(big_num2);
		i++;
	}
	print_buf1(big_num1);
	print_buf2(big_num2);
	//add_pow_five(big_num, 100);
	//print_buf(big_num);
	//printf("\"e: %d f: %f\"", e, f);
	(*k)++;
	return (0);
}




/*
 * 	c.p = number.bits;
	printf("\n31 \t 30 \t 29 \t 28 \t 27 \t 26 \t 25 \t 24 \t 23 \t 22 \t 21 \t 20 \t 19 \t 18 \t 17 \t 16 \t 15 \t 14 \t 13 \t 12 \t 11 \t 10 \t 9 \t 8 \t 7 \t 6 \t 5 \t 4 \t 3 \t 2 \t 1 \t 0 \n");
	printf("%d \t %d \t %d \t %d \t %d \t "
		   "%d \t %d \t %d \t %d \t %d \t "
           "%d \t %d \t %d \t %d \t %d \t "
           "%d \t %d \t %d \t %d \t %d \t "
           "%d \t %d \t %d \t %d \t %d \t "
		   "%d \t %d \t %d \t %d \t %d \t %d \t %d\n",
		   c.byte.a31, c.byte.a30, c.byte.a29, c.byte.a28, c.byte.a27,
		   c.byte.a26, c.byte.a25, c.byte.a24, c.byte.a23, c.byte.a22,
		   c.byte.a21, c.byte.a20, c.byte.a19, c.byte.a18, c.byte.a17,
		   c.byte.a16, c.byte.a15, c.byte.a14, c.byte.a13, c.byte.a12,
		   c.byte.a11, c.byte.a10, c.byte.a9, c.byte.a8, c.byte.a7,
		   c.byte.a6, c.byte.a5, c.byte.a4, c.byte.a3, c.byte.a2, c.byte.a1, c.byte.a0);
 */

/*
#include <stdio.h>

struct point
{
    unsigned int x:5;   // 0-31
    unsigned int y:3;   // 0-7
};

union code
{
    struct point p;
    struct{
        unsigned a0:1;
        unsigned a1:1;
        unsigned a2:1;
        unsigned a3:1;
        unsigned a4:1;
        unsigned a5:1;
        unsigned a6:1;
        unsigned a7:1;
    } byte;
};


int main(void)
{
    struct point center = {2, 5};
    union code c;
    c.p = center;
    printf("7 \t 6 \t 5 \t 4 \t 3 \t 2 \t 1 \t 0 \n");
    printf("%d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \n",
            c.byte.a7, c.byte.a6, c.byte.a5, c.byte.a4,
            c.byte.a3, c.byte.a2, c.byte.a1, c.byte.a0);
    return 0;
}
 */