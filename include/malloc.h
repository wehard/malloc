/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:58 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/21 23:54:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>

# define TRUE 1
# define FALSE 0
// # define TINY 2
// # define SMALL 4
// # define LARGE 8
# define NUM_TINY 100
# define NUM_SMALL 100
# define NUM_LARGE 100

# define END -1
# define FREE 0
# define USED 1

typedef enum	e_alloc_area
{
	TINY = 1,
	SMALL = 4,
	LARGE = 8
}				t_alloc_area;

typedef struct		s_block
{
	t_alloc_area	area;
	int 			free;
	size_t			size;
	struct s_block *next;
}					t_block;

typedef struct	s_malloc
{
	int			initialized;
	int			page_size;
	size_t		tiny_size;
	size_t		tiny_left;
	size_t		small_size;
	size_t		large_size;
	t_block		*blocks;
	void		*data;
	void		*small_data;
	void		*large_data;
}				t_malloc;

void			*ft_malloc(size_t size);
void			*ft_realloc(void *ptr, size_t size);
void			ft_free(void *ptr);
void			show_alloc_mem();
void			print_memory(const void *addr, size_t size);

#endif
