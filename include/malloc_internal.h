/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:12:41 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 11:15:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_INTERNAL_H
# define MALLOC_INTERNAL_H

# include <stdlib.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

# define MAX_TINY 100
# define MAX_SMALL 1024

# define TINY_ALLOC_SIZE 128
# define SMALL_ALLOC_SIZE 1024

typedef enum e_zone
{
	TINY = 1,
	SMALL = 4,
	LARGE = 8
}				t_zone;

typedef struct s_block
{
	void			*data;
	int				free;
	size_t			size;
	struct s_block	*next;
}					t_block;

typedef struct s_malloc
{
	int			initialized;
	int			page_size;
	t_block		*heap_tiny;
	t_block		*heap_small;
	t_block		*heap_large;
}				t_malloc;

extern t_malloc			g_malloc;
extern pthread_mutex_t	g_malloc_mutex;

void	print_memory(const void *addr, size_t size);
size_t	align_size(size_t size);
void	*get_heap(size_t size);
void	*get_block(size_t size, void *heap);

void	init_heap(t_zone zone, t_block **heap);
size_t	calc_heap_size(t_zone zone);
void	*create_heap(size_t size);
void	*allocate_large(size_t size);
#endif
