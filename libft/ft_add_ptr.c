#include "libft.h"
#include "stdio.h"

void	**ft_add_ptr(void **dptr, void *ptr, int pos)
{
	int	len;
	int	i;
	int	j;
	void	**r;

	if (!dptr)
		return (NULL);
	len = ft_doubleptr_len(dptr);
	if (!ptr || pos < 0 || pos > len)
		return (dptr);
	r = ft_calloc(len + 2, sizeof(void *));
	if (!r)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len + 1)
	{
		if (j == pos)
		{
			r[i++] = (void *)ft_strdup((char *)ptr);
			printf("r[i] = %s, i = %d\n", (char *)r[i - 1], i - 1);
		}
		else
		{
			r[i++] = (void *)ft_strdup((char *)dptr[j]);
			printf("r[i] = %s, i = %d\n", (char *)r[i - 1], i - 1);
		}
		j++;
	}
	r[i] = NULL;
	return ( r);
}