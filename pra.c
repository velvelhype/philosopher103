#include <stdio.h>
#include "libft/libft.h"

int main()
{
	char mes[] = "hall";

	if(ft_strncmp(mes, "hell", ft_strlen(mes)))
		printf("no!\n");
	else
		printf("yes\n");
}