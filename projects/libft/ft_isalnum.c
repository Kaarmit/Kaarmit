HEADER

int	ft_islanum(int c)
{
	if ((c >= '0' && <= '9') || (c >= 'a' && <= 'z') || (c >= 'A' && <= 'Z'))
		return (1);
	return (0);
}
