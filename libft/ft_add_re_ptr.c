#include "libft.h"

void	**ft_add_re_ptr(void **dptr, void *ptr, int pos)
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
	r = ft_calloc(len + 1, sizeof(void *));
	if (!r)
		return (NULL);
	r[len] = NULL;
	i = 0;
	j = 0;
	while (j < len + 1)
	{
		if (j == pos)
			r[i++] = (void *)ft_strdup((char *)ptr);
		else
			r[i++] = (void *)ft_strdup((char *)dptr[j]);
		j++;
	}
	return (r);
}