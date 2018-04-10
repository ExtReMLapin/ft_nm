/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:49:33 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/29 10:58:13 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <ar.h>
# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)
# define AT __FILE__ ":" TOSTRING(__LINE__)
# define COLORS 0

typedef struct				s_section
{
	char					*name;
	unsigned int			nb;
	struct s_section		*next;
}							t_section;

typedef struct				s_lsection
{
	t_section				*first;
	t_section				*last;
}							t_lsection;

typedef struct				s_pack
{
	struct fat_arch_64		*original;
	uint32_t				noriginal;
}							t_pack;

typedef struct				s_env
{
	bool					is64bit;
	bool					isswap;
	bool					isfattype;
	bool					isarchive;
	char					*ptr;
	char					*end;
	t_lsection				*section;
	char					*file_name;
	bool					in_ppc;
	bool					tmp_swap;
}							t_env;

void						mlccmd(t_env *env, uint64_t n_value, char symbol,
	char *name);
t_env						*make_env(char *ptr, char *end, char *name);
void						handle_64(char *adr, char *max,
	bool swap, t_env *env);
void						handle_32(char *adr, char *max,
	bool swap, t_env *env);
void						handle_fat(t_env *env, bool swap);
void						failmessage(char *message);
uint16_t					swap_uint16(uint16_t nb);
uint32_t					swap_uint32(uint32_t nb);
uint64_t					swap_uint64(uint64_t nb);
void						print_hex(uint64_t hex, bool first,
	int how_many_chars, bool blank);
void						otool2(t_env *env, char *ptr, char *max);
bool						check_ar_header(char *ptr);
void						handle_ar(char const *file, char *max,
	t_env *env);
char						*get_cputype(cpu_type_t cputype);
bool						spcpu(struct fat_arch *c, struct fat_arch *arch,
	uint32_t n);
uint32_t					how_many_cpu(struct fat_arch *arch, uint32_t n);
bool						spcpu64(struct fat_arch_64 *c,
	struct fat_arch_64 *arch, uint32_t n);
uint32_t					how_many_cpu64(struct fat_arch_64 *arch,
	uint32_t n);
void						handle_fat32(t_env *env, bool swap);
void						handle_fat64(t_env *env, bool swap);
bool						segfaultcheck(char *ptr, char *end, char *mess);
uint32_t					ar_size(char const *name);
void						read_ranlib(char const *file, char *end,
	uint32_t nbr, t_env *env);
void						ft_putstr(const char *s);
void						ft_putchar(char c);
size_t						ft_strlen(const char *s);
int							strequ(char const *s1, char const *s2);
struct fat_arch_64			*ffcpu(struct fat_arch_64 *a,
	cpu_type_t cpu, uint32_t n);
int							ft_atoi(const char *str);
char						*ft_strchr(const char *s, int c);
int							ft_strcmp(const char *s1, const char *s2);
void						*ft_memcpy(void *dst,
	const void *src, size_t n);
#endif
