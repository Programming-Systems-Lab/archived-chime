/*
    Copyright (C) 1998 by Jorrit Tyberghein and Steve Israelson

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef SCANSTR_H
#define SCANSTR_H

/**
 * Own version of sscanf that is a bit more relaxed towards spaces
 * and also accepts quoted strings (the quotes will not be included into
 * the result string).
 * <p>It supports the following format commands:
 * <dt>%d<dd>	integer number
 * <dt>%f<dd>	floating point
 * <dt>%b<dd>	boolean (0, 1, true, false, yes, no, on, off)
 * <dt>%s<dd>	string (with or without single quotes)
 * <dt>%S<dd>   string (delimited with double quotes)
 *              \n will be converted to a newline
 *              \t will be converted to a tab
 *              \\ produces a \
 *              \" produces a "
 *              all other conbinations of \ are copied.
 * <dt>%D<dd>	list of integers, first argument should be a
 *		pointer to an array of integers, second argument
 *		a pointer to an integer which will contain the
 *		number of elements inserted in the list.
 * <dt>%F<dd>	similarly, a list of floats.
 * <dt>%n<dd>	This returns the amount of the input string
 *              thats been consumed, in characters. Does NOT
 *              increment the return count and does not read
 *              from the input string.
 * </dl>
 * <p>Returns the number of successfully scanned arguments or -1 if there
 * was a mismatch.
 */
int csScanStr (const char* in, const char* format, ...);

#endif // SCANSTR_H
