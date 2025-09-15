#include "../minishell.h"

char	**ft_expand_wildcard(char **token, char *wildcard, int pos, int *wc_len)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	char	*wc;
	char	*t;

	if (!token || !wildcard)
		return (token);
	dir_stream = opendir(".");
	if (!dir_stream)
	{
		perror("opendir");
		return (token);
	}
	wc = ft_strdup(token[pos]);
	while (1)
	{
		dir = readdir(dir_stream);
		if (!dir)
			break ;
		if (ft_match_wildcard(dir->d_name, wc))
		{
			if (*wc_len == 0)
				t = (char **)ft_add_re_ptr((void **)token, dir->d_name, pos);
			else
				t = (char **)ft_add_ptr((void **)token, dir->d_name, pos);
			ft_free_d(token);
			token = t;
			*wc_len = *wc_len + 1;
		}
	}
	closedir(dir_stream);
	free(wc);
	return (token);
}

int	ft_match_wildcard(char *str, char *wildcard)
{
	size_t	i;
	size_t	j;
	size_t	i_anchor;
	size_t	j_after_asterisk;

    if (!str || !wildcard || (str[0] == '.' && wildcard[0] != '.'))
		return (0);
    i = 0;
	j = 0;
	i_anchor = 0;
	j_after_asterisk = 0;
    while (str[i])
    {
        if (wildcard[j] == '*')
        {
			while (wildcard[j] == '*')
				j++;
			if (!wildcard[j])
				return (1);
			j_after_asterisk = j;
			i_anchor = i;
			continue;
        }
        if (wildcard[j] == str[i])
        {
			i++;
			j++;
			continue;
		}
        if (j_after_asterisk)
        {
			i_anchor++;
			i = i_anchor;
			j = j_after_asterisk;
			continue;
		}
		return (0);
    }
    while (wildcard[j] == '*')
		j++;
    return (wildcard[j] == '\0');
}