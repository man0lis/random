//      compare.h
//      
//      Copyright 2010 Robin Nehls <nehls@mi.fu-berlin.de>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

// This functions compares 2 strings and returns how many char are the 
// same in percent. Stings may have different length. In this case chars
// will be compared until one sting runs out of chars
float percent_the_same(char* str1, char* str2);

// This function compares 2 strings and returnes the total of chars each
// pair of chars are appart.
int chars_appart(char* str1, char* str2);

// This funktion returns the levenshtein distance of 2 given strings
int levenshtein_distance(char* str1, char* str2);
