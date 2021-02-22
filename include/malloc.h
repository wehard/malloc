/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:58 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/22 16:04:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define NUM_TINY_PAGES 2
# define NUM_SMALL_PAGES 16

# define TINY_ALLOC_SIZE 128
# define SMALL_ALLOC_SIZE 1024

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
	t_alloc_area	area_type;
	void			*data;
	int 			free;
	size_t			size;
	struct s_block *next;
}					t_block;

typedef struct	s_malloc
{
	int			initialized;
	int			page_size;
	t_block		*tiny_blocks;
	void		*tiny_data;
	t_block		*small_blocks;
	void		*small_data;
	t_block		*large_blocks;
	// void		*large_data;
}				t_malloc;

extern t_malloc g_malloc;

void			*ft_malloc(size_t size);
void			*ft_realloc(void *ptr, size_t size);
void			ft_free(void *ptr);
void			show_alloc_mem(void);
void			print_memory(const void *addr, size_t size);

#endif
