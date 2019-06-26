/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:53:32 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/23 18:53:37 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

typedef struct		s_input
{
	char			last_key_pressed;
	char			keys[300];
	char			mouse_key;
	int				mouse_x;
	int				mouse_y;
}					t_input;

# define KEY_TILDE	50
# define KEY_1		18
# define KEY_2		19
# define KEY_3		20
# define KEY_4		21
# define KEY_5		23
# define KEY_6		22
# define KEY_7		26
# define KEY_8		28
# define KEY_9		25
# define KEY_0		21
# define KEY_MINUS	27
# define KEY_EQUALS	24

# define KEY_A		0
# define KEY_B		11
# define KEY_C		8
# define KEY_D		2
# define KEY_E		14
# define KEY_F		3
# define KEY_G		5
# define KEY_H		4
# define KEY_I		34
# define KEY_J		38
# define KEY_K		40
# define KEY_L		37
# define KEY_M		46
# define KEY_N		45
# define KEY_O		31
# define KEY_P		35
# define KEY_Q		12
# define KEY_R		15
# define KEY_S		1
# define KEY_T		17
# define KEY_U		32
# define KEY_V		9
# define KEY_W		13
# define KEY_X		7
# define KEY_Y		16
# define KEY_Z		6

# define KEY_OPEN_SQUARE_BRACKET	33
# define KEY_CLOSED_SQUARE_BRACKET	30
# define KEY_SEMI_COLON				41
# define KEY_QUOTE					39
# define KEY_BACK_SLASH				42

# define KEY_COMMA			43
# define KEY_PERIOD			47
# define KEY_FORWARD_SLASH	44

# define KEY_LEFT_ARROW		123
# define KEY_RIGHT_ARROW	124
# define KEY_DOWN_ARROW		125
# define KEY_UP_ARROW		126

# define KEY_ENTER			36
# define KEY_TAB			48
# define KEY_SPACE			49
# define KEY_BACKSPACE		51
# define KEY_ESCAPE			53
# define KEY_LEFT_CTRL		256
# define KEY_RIGHT_CTRL		269
# define KEY_LEFT_SHIFT		257
# define KEY_RIGHT_SHIFT	258
# define KEY_LEFT_COMMAND	259
# define KEY_RIGHT_COMMAND	260
# define KEY_CAPS_LOCK		272

#endif
