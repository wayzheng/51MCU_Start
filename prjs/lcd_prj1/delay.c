void Delay(unsigned int x)	//@11.0592MHz
{
	unsigned char data i, j;

	while(x--) {
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
