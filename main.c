/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:32:20 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/20 16:14:44 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void search(){
 char **s = ft_split("ok.ok.ok", '.');
 free (s[1]);
 printf("It Is : %s\n", s[2]);
 strlen(s[1]);
}
int main()
{
    search();
    // system("leaks a.out");
}